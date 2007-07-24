/****************************************************************************
  smds - the openSource Memory DataSet

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Please read the "Doc\License.txt" for more copyright and license
  information.
****************************************************************************/
//---------------------------------------------------------------------------
#if ! defined (SM_DS_BUFFER_H)
#define SM_DS_BUFFER_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include <vector>
#include <iterator>
#include <limits>
#include "dsSmartPtr.h"
#include <boost/scoped_array.hpp>
#include <boost/shared_ptr.hpp>
#include "dsUtils.h"
#include "dsTypes.h"
#include "dsFields.h"
#include "dsDateTime.h"
#include "dsGUID.h"
#include "dsExceptions.h"
#include "dsVariant.h"
#include "dsCompare.h"
//---------------------------------------------------------------------------
namespace smds
{

class Table;
class cTableReader;

enum cUpdateStatus { usUnmodified, usInserted, usModified, usDeleted };

inline cStream& FASTCALL operator << ( cStream& st, const cUpdateStatus a )     { return ( st.WriteBuffer( &a, sizeof(cUpdateStatus) ) ); }
inline cStream& FASTCALL operator >> ( cStream& st, cUpdateStatus& a )          { return ( st.ReadBuffer( &a, sizeof(cUpdateStatus) ) ); }

namespace detail
{

//***********************************************************************
//******    cRawBuffer
//***********************************************************************
class cRawBuffer
{
public:
    typedef std::size_t     size_type;
private:
    typedef unsigned char   quantum;            // bits collection quantum ????
    enum { quantum_bits = std::numeric_limits<quantum>::digits };

    friend class Table;
    friend class DoubleBuffer;
    friend class cTableReader;

    boost::scoped_array<char>   mData;
    quantum                     *mNullBits;

    template <class T> T FASTCALL buffer_field_cast( int offset ) const
    {
        return reinterpret_cast<T>( raw_data() + offset );
    }

    var_blob_type ** FASTCALL blob_ptr_ptr( int offset ) const
    {
        return buffer_field_cast<var_blob_type **>( offset );
    }

    ds_string ** FASTCALL string_ptr_ptr( int offset ) const
    {
        return buffer_field_cast<ds_string **>( offset );
    }

    ds_wstring ** FASTCALL wstring_ptr_ptr( int offset ) const
    {
        return buffer_field_cast<ds_wstring **>( offset );
    }

    size_type FASTCALL CalcBufferSize( size_type buffer_size, size_type field_count )
    {
        return ( buffer_size + field_count / quantum_bits + sizeof(quantum) );
    }

    void FASTCALL InitNullBits( size_type field_count, bool value )
    {
        std::memset( mNullBits, value ? -1 : 0, field_count / quantum_bits + sizeof(quantum) );
    }

    void FASTCALL calc_pos_mask( std::size_t bit_idx, std::size_t& quantum_idx, quantum& mask ) const
    {
        quantum_idx = (bit_idx / quantum_bits);
        mask = static_cast<quantum>(0x80 >> (bit_idx % quantum_bits));
    }

    bool FASTCALL TestBit( std::size_t bit_num ) const
    {
        std::size_t     quantum_idx;
        quantum         mask;

        calc_pos_mask( bit_num, quantum_idx, mask );
        return ( (mNullBits[quantum_idx] & mask) != 0 );
    }

    void FASTCALL SetBit( std::size_t bit_num, bool value )
    {
        std::size_t     quantum_idx;
        quantum         mask;

        calc_pos_mask( bit_num, quantum_idx, mask );
        if ( value )
            mNullBits[quantum_idx] |= mask;
        else
            mNullBits[quantum_idx] &= static_cast<quantum>(~mask);      // static_cast for BCB warning
    }

    static ds_string& FASTCALL empty_string();

    void FASTCALL swap( cRawBuffer& other )
    {
        mData.swap( other.mData );
        std::swap( mNullBits, other.mNullBits );
    }
    // noncopyable
    CDFASTCALL cRawBuffer( const cRawBuffer& src );
    cRawBuffer& FASTCALL operator=( const cRawBuffer& src );
private:
    CDFASTCALL cRawBuffer( cFieldDefs *field_defs, bool init )
        : mData(), mNullBits()
    {
        if ( init )
            construct( field_defs );
    }
    CDFASTCALL ~cRawBuffer()
    {
    }
    bool FASTCALL is_empty() const                                  { return ( mData == 0 ); }
    void FASTCALL construct( cFieldDefs *field_defs )
    {
        size_type   buffer_size = field_defs->BufferSize();
        size_type   field_count = field_defs->Count();

        if ( is_empty() )
        {
            mData.reset( new char[CalcBufferSize( buffer_size, field_count )] );
            std::memset( mData.get(), 0, buffer_size );
        }
        mNullBits = reinterpret_cast<quantum *>(mData.get()) + buffer_size;
        InitNullBits( field_count, true );
    }
    void FASTCALL copy_construct( cFieldDefs *field_defs, const cRawBuffer& src )
    {
        size_type   buffer_size = field_defs->BufferSize();
        size_type   field_count = field_defs->Count();
        size_type   combined_buffer_size = CalcBufferSize( buffer_size, field_count );

        if ( is_empty() )
            mData.reset( new char[combined_buffer_size] );
        mNullBits = reinterpret_cast<quantum *>(mData.get()) + buffer_size;
        std::memmove( mData.get(), src.mData.get(), combined_buffer_size );

        for ( cFieldDefs::iterator n = field_defs->begin(), eend = field_defs->end() ; n != eend ; ++n )
        {
            if ( n->DataType() == ftBlob )
                *blob_ptr_ptr( n->Offset() ) = 0;
            else if ( n->DataType() == ftWString )
                *wstring_ptr_ptr( n->Offset() ) = 0;
            else if ( n->DataType() == ftString )
                *string_ptr_ptr( n->Offset() ) = 0;
        }

        try
        {
            for ( cFieldDefs::iterator n = field_defs->begin(), eend = field_defs->end() ; n != eend ; ++n )
            {
                if ( n->DataType() == ftBlob )
                {
                    if ( *src.blob_ptr_ptr( n->Offset() ) )
                        *blob_ptr_ptr( n->Offset() ) = new var_blob_type( **src.blob_ptr_ptr( n->Offset() ) );
                }
                else if ( n->DataType() == ftWString )
                {
                    if ( *src.wstring_ptr_ptr( n->Offset() ) )
                        *wstring_ptr_ptr( n->Offset() ) = new ds_wstring( **src.wstring_ptr_ptr( n->Offset() ) );
                }
                else if ( n->DataType() == ftString )
                {
                    if ( *src.string_ptr_ptr( n->Offset() ) )
                        *string_ptr_ptr( n->Offset() ) = new ds_string( **src.string_ptr_ptr( n->Offset() ) );
                }
            }
        }
        catch ( ... )
        {
            destroy( field_defs );
            throw;
        }
    }

    void FASTCALL destroy( cFieldDefs *field_defs )
    {
        if ( ! is_empty() )
        {
            for ( cFieldDefs::iterator n = field_defs->begin(), eend = field_defs->end() ; n != eend ; ++n )
            {
                if ( n->DataType() == ftBlob )
                {
                    if ( var_blob_type **data = blob_ptr_ptr( n->Offset() ) )
                    {
                        delete *data;
                        *data = 0;
                    }
                }
                else if ( n->DataType() == ftWString )
                {
                    if ( ds_wstring **data = wstring_ptr_ptr( n->Offset() ) )
                    {
                        delete *data;
                        *data = 0;
                    }
                }
                else if ( n->DataType() == ftString )
                {
                    if ( ds_string **data = string_ptr_ptr( n->Offset() ) )
                    {
                        delete *data;
                        *data = 0;
                    }
                }
            }
            mData.reset( 0 );
        }
        mNullBits = 0;
    }
    void FASTCALL SetNull( const cFieldDef& field_def, bool value )             ; // { mNull[field_def.Index()] = value; }
    void FASTCALL SetNull( const cFieldDef_& field_def, bool value )            ; // { mNull[field_def.mIndex] = value; }

    char * FASTCALL raw_data() const                                            { return ( mData.get() ); }
public:
    bool FASTCALL IsNull( const cFieldDef& field_def ) const            ; // { return ( mNull[field_def.Index()] ); }
    bool FASTCALL IsNull( const cFieldDef_& field_def ) const           ; // { return ( mNull[field_def.mIndex] ); }
    void FASTCALL Nullify( const cFieldDef& field_def )                 ; // { mNull[field_def.Index()] = true; }
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
    bool FASTCALL ReadBool( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return false;
#endif
        return *(buffer_field_cast<bool *>(field_def.Offset()));
    }
//---------------------------------------------------------------------------
    char FASTCALL ReadByte( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return 0;
#endif
        return *(buffer_field_cast<char *>(field_def.Offset()));
    }
//---------------------------------------------------------------------------
//    wchar_t FASTCALL ReadWChar( const cFieldDef& field_def ) const
//    {
//        if ( IsNull( field_def ) )
//#if defined SM_DS_NULL_VALUE_EXCEPTION
//            throw eNullFieldValue();
//#else
//            return 0;
//#endif
//        return *(buffer_field_cast<wchar_t *>(field_def.Offset()));
//    }
//---------------------------------------------------------------------------
    short FASTCALL ReadShort( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return 0;
#endif
        return *(buffer_field_cast<short *>(field_def.Offset()));
    }
//---------------------------------------------------------------------------
    int FASTCALL ReadInteger( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return 0;
#endif
        return *(buffer_field_cast<int *>(field_def.Offset()));
    }
//---------------------------------------------------------------------------
    long long FASTCALL ReadLongLong( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return 0;
#endif
        return *(buffer_field_cast<long long *>(field_def.Offset()));
    }
//---------------------------------------------------------------------------
    double FASTCALL ReadFloat( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return *(buffer_field_cast<double *>(field_def.Offset()));
    }
//---------------------------------------------------------------------------
    dbDate FASTCALL ReadDate( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return dbDateTime();
#endif
        return detail::CreateDbDate( *(buffer_field_cast<detail::dbDate_Internal *>(field_def.Offset())) );
    }
//---------------------------------------------------------------------------
    dbTime FASTCALL ReadTime( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return dbDateTime();
#endif
        return detail::CreateDbTime( *(buffer_field_cast<detail::dbTime_Internal *>(field_def.Offset())) );
    }
//---------------------------------------------------------------------------
    dbDateTime FASTCALL ReadDateTime( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return dbDateTime();
#endif
        return detail::CreateDbDateTime( *(buffer_field_cast<detail::dbDateTime_Internal *>(field_def.Offset())) );
    }
//---------------------------------------------------------------------------
    const ds_string& FASTCALL ReadString( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return empty_string();
#endif
        return **string_ptr_ptr( field_def.Offset() );
    }
//---------------------------------------------------------------------------
    Variant FASTCALL ReadVariant( const cFieldDef& field_def ) const;
//---------------------------------------------------------------------------
    void FASTCALL WriteBool( const cFieldDef& field_def, bool value )
    {
        *(buffer_field_cast<bool *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteByte( const cFieldDef& field_def, char value )
    {
        *(buffer_field_cast<char *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    //void FASTCALL WriteWChar( const cFieldDef& field_def, wchar_t value )
    //{
    //    *(buffer_field_cast<wchar_t *>(field_def.Offset())) = value;
    //    SetNull( field_def, false );
    //}
    void FASTCALL WriteShort( const cFieldDef& field_def, short value )
    {
        *(buffer_field_cast<short *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteInteger( const cFieldDef& field_def, int value )
    {
        *(buffer_field_cast<int *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteLongLong( const cFieldDef& field_def, long long value )
    {
        *(buffer_field_cast<long long *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteFloat( const cFieldDef& field_def, double value )
    {
        *(buffer_field_cast<double *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteDate( const cFieldDef& field_def, const dbDate& value )
    {
        *(buffer_field_cast<detail::dbDate_Internal *>(field_def.Offset())) = value.AsInternal();
        SetNull( field_def, false );
    }
    void FASTCALL WriteDate( const cFieldDef& field_def, const detail::dbDate_Internal& value )
    {
        *(buffer_field_cast<detail::dbDate_Internal *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteTime( const cFieldDef& field_def, const dbTime& value )
    {
        *(buffer_field_cast<detail::dbTime_Internal *>(field_def.Offset())) = value.AsInternal();
        SetNull( field_def, false );
    }
    void FASTCALL WriteTime( const cFieldDef& field_def, const detail::dbTime_Internal& value )
    {
        *(buffer_field_cast<detail::dbTime_Internal *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteDateTime( const cFieldDef& field_def, const detail::dbDateTime_Internal& value )
    {
        *(buffer_field_cast<detail::dbDateTime_Internal *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteDateTime( const cFieldDef& field_def, const dbDateTime& value )
    {
        *(buffer_field_cast<detail::dbDateTime_Internal *>(field_def.Offset())) = value.AsInternal();
        SetNull( field_def, false );
    }
    void FASTCALL WriteGUID( const cFieldDef& field_def, const detail::dbGUID_Internal& value )
    {
        *(buffer_field_cast<detail::dbGUID_Internal *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteGUID( const cFieldDef& field_def, const dbGUID& value )
    {
        *(buffer_field_cast<detail::dbGUID_Internal *>(field_def.Offset())) = value.AsInternal();
        SetNull( field_def, false );
    }
    void FASTCALL WriteString( const cFieldDef& field_def, const ds_string& value )
    {
        ds_string   **data = string_ptr_ptr( field_def.Offset() );

        if ( *data == 0 )
            *data = new ds_string( value );
        else
            (*data)->assign( value, 0, field_def.DataSize() );
        SetNull( field_def, false );
    }
    void FASTCALL WriteString( const cFieldDef& field_def, const char *value )
    {
        ds_string   **data = string_ptr_ptr( field_def.Offset() );

        if ( *data == 0 )
            *data = new ds_string( value );
        else
            (*data)->assign( value, std::min<ds_string::size_type>( std::strlen( value ), field_def.DataSize() ) );
        SetNull( field_def, false );
    }
    void FASTCALL WriteVariant( const cFieldDef& field_def, const Variant& value );
//---------------------------------------------------------------------------
    bool FASTCALL ReadBool( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return false;
#endif
        return *(buffer_field_cast<bool *>(field_def.mOffset));
    }
//---------------------------------------------------------------------------
    char FASTCALL ReadByte( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return 0;
#endif
        return *(buffer_field_cast<char *>(field_def.mOffset));
    }
//---------------------------------------------------------------------------
//    wchar_t FASTCALL ReadWChar( const cFieldDef_& field_def ) const
//    {
//        if ( IsNull( field_def ) )
//#if defined SM_DS_NULL_VALUE_EXCEPTION
//            throw eNullFieldValue();
//#else
//            return 0;
//#endif
//        return *(buffer_field_cast<wchar_t *>(field_def.mOffset));
//    }
//---------------------------------------------------------------------------
    short FASTCALL ReadShort( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return 0;
#endif
        return *(buffer_field_cast<short *>(field_def.mOffset));
    }
//---------------------------------------------------------------------------
    int FASTCALL ReadInteger( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return 0;
#endif
        return *(buffer_field_cast<int *>(field_def.mOffset));
    }
//---------------------------------------------------------------------------
    long long FASTCALL ReadLongLong( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return 0;
#endif
        return *(buffer_field_cast<long long *>(field_def.mOffset));
    }
//---------------------------------------------------------------------------
    double FASTCALL ReadFloat( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return 0;
#endif
        return *(buffer_field_cast<double *>(field_def.mOffset));
    }
//---------------------------------------------------------------------------
    dbDate FASTCALL ReadDate( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return dbDateTime();
#endif
        return CreateDbDate( *(buffer_field_cast<detail::dbDate_Internal *>(field_def.mOffset)) );
    }
//---------------------------------------------------------------------------
    dbTime FASTCALL ReadTime( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return dbDateTime();
#endif
        return CreateDbTime( *(buffer_field_cast<detail::dbTime_Internal *>(field_def.mOffset)) );
    }
//---------------------------------------------------------------------------
    dbDateTime FASTCALL ReadDateTime( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return dbDateTime();
#endif
        return detail::CreateDbDateTime( *(buffer_field_cast<detail::dbDateTime_Internal *>(field_def.mOffset)) );
    }
//---------------------------------------------------------------------------
    const ds_string& FASTCALL ReadString( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return empty_string();
#endif
        return **string_ptr_ptr( field_def.mOffset );
    }
//---------------------------------------------------------------------------
    void FASTCALL WriteBool( const cFieldDef_& field_def, bool value )
    {
        *(buffer_field_cast<bool *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteByte( const cFieldDef_& field_def, char value )
    {
        *(buffer_field_cast<char *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    //void FASTCALL WriteWChar( const cFieldDef_& field_def, wchar_t value )
    //{
    //    *(buffer_field_cast<wchar_t *>(field_def.mOffset)) = value;
    //    SetNull( field_def, false );
    //}
    void FASTCALL WriteShort( const cFieldDef_& field_def, short value )
    {
        *(buffer_field_cast<short *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteInteger( const cFieldDef_& field_def, int value )
    {
        *(buffer_field_cast<int *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteLongLong( const cFieldDef_& field_def, long long value )
    {
        *(buffer_field_cast<long long *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteFloat( const cFieldDef_& field_def, double value )
    {
        *(buffer_field_cast<double *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteDate( const cFieldDef_& field_def, const dbDate& value )
    {
        *(buffer_field_cast<detail::dbDate_Internal *>(field_def.mOffset)) = value.AsInternal();
        SetNull( field_def, false );
    }
    void FASTCALL WriteTime( const cFieldDef_& field_def, const dbTime& value )
    {
        *(buffer_field_cast<detail::dbTime_Internal *>(field_def.mOffset)) = value.AsInternal();
        SetNull( field_def, false );
    }
    void FASTCALL WriteDateTime( const cFieldDef_& field_def, const dbDateTime& value )
    {
        *(buffer_field_cast<detail::dbDateTime_Internal *>(field_def.mOffset)) = value.AsInternal();
        SetNull( field_def, false );
    }
    void FASTCALL WriteString( const cFieldDef_& field_def, const ds_string& value )
    {
        ds_string   **data = string_ptr_ptr( field_def.mOffset );

        if ( *data == 0 )
            *data = new ds_string( value );
        else
            (*data)->assign( value, 0, field_def.mDataSize );
        SetNull( field_def, false );
    }
    void FASTCALL WriteString( const cFieldDef_& field_def, const char *value )
    {
        ds_string   **data = string_ptr_ptr( field_def.mOffset );

        if ( *data == 0 )
            *data = new ds_string( value );
        else
            (*data)->assign( value, std::min<ds_string::size_type>( std::strlen( value ), field_def.mDataSize ) );
        SetNull( field_def, false );
    }
//---------------------------------------------------------------------------
    bool FASTCALL ReadBoolNN( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<bool *>(field_def.Offset()));
    }
    char FASTCALL ReadByteNN( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<char *>(field_def.Offset()));
    }
    short FASTCALL ReadShortNN( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<short *>(field_def.Offset()));
    }
    int FASTCALL ReadIntegerNN( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<int *>(field_def.Offset()));
    }
    long long FASTCALL ReadLongLongNN( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<long long *>(field_def.Offset()));
    }
    double FASTCALL ReadFloatNN( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<double *>(field_def.Offset()));
    }
    dbDate FASTCALL ReadDateNN( const cFieldDef& field_def ) const
    {
        return CreateDbDate( *(buffer_field_cast<detail::dbDate_Internal *>(field_def.Offset())) );
    }
    const detail::dbDate_Internal& FASTCALL ReadDateNNref( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<detail::dbDate_Internal *>(field_def.Offset()));
    }
    dbTime FASTCALL ReadTimeNN( const cFieldDef& field_def ) const
    {
        return CreateDbTime( *(buffer_field_cast<detail::dbTime_Internal *>(field_def.Offset())) );
    }
    const detail::dbTime_Internal& FASTCALL ReadTimeNNref( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<detail::dbTime_Internal *>(field_def.Offset()));
    }
    dbDateTime FASTCALL ReadDateTimeNN( const cFieldDef& field_def ) const
    {
        return detail::CreateDbDateTime( *(buffer_field_cast<detail::dbDateTime_Internal *>(field_def.Offset())) );
    }
    const detail::dbDateTime_Internal& FASTCALL ReadDateTimeNNref( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<detail::dbDateTime_Internal *>(field_def.Offset()));
    }
    dbGUID FASTCALL ReadGUIDNN( const cFieldDef& field_def ) const
    {
        return detail::CreateDbGUID( *(buffer_field_cast<detail::dbGUID_Internal *>(field_def.Offset())) );
    }
    const detail::dbGUID_Internal& FASTCALL ReadGUIDNNref( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<detail::dbGUID_Internal *>(field_def.Offset()));
    }
    const ds_string& FASTCALL ReadStringNN( const cFieldDef& field_def ) const
    {
        return **string_ptr_ptr( field_def.Offset() );
    }
};

//***********************************************************************
//******    DoubleBuffer
//***********************************************************************
class DoubleBuffer
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
{
private:
    cRawBuffer              mOriginalData;
    cRawBuffer              mModifiedData;
    cUpdateStatus           mUpdateStatus;
    cFieldDefs              *mFieldDefs;
    //cRawBuffer::size_type   mSize;
    //cRawBuffer::size_type   mFieldCount;

    const cRawBuffer& FASTCALL GetReadRow() const       { return ( GetActiveData() ); }
    cRawBuffer& FASTCALL GetUpdateRow()                 { return ( GetUpdateData() ); }
    // noncopyable
    CDFASTCALL DoubleBuffer( const DoubleBuffer& src );
    DoubleBuffer& FASTCALL operator=( const DoubleBuffer& src );

    cRawBuffer& FASTCALL GetModifiedData()              { return ( mModifiedData ); }
    const cRawBuffer& FASTCALL GetModifiedData() const  { return ( mModifiedData ); }
    cRawBuffer& FASTCALL GetUpdateData()
    {
        if ( mUpdateStatus == usUnmodified )
            mModifiedData.copy_construct( mFieldDefs, GetOriginalData() );
        return GetModifiedData();
    }
    void FASTCALL UpdateRecordStatus()
    {
        if ( mUpdateStatus == usUnmodified )
            mUpdateStatus = usModified;
    }
public:
    // the 'bool unmodified' parameter if false means 'inserted'
    //CDFASTCALL DoubleBuffer( cRawBuffer::size_type buffer_size, cRawBuffer::size_type field_count, bool unmodified );
    CDFASTCALL DoubleBuffer( cFieldDefs *field_defs, bool unmodified );
    CDFASTCALL ~DoubleBuffer();
    cRawBuffer& FASTCALL GetOriginalData()              { return ( mOriginalData ); }
    const cRawBuffer& FASTCALL GetOriginalData() const  { return ( mOriginalData ); }
    cUpdateStatus FASTCALL GetUpdateStatus() const      { return ( mUpdateStatus ); }

    cRawBuffer& FASTCALL GetActiveData()
    {
        if ( mUpdateStatus == usUnmodified )
            return GetOriginalData();
        else
        {
            BOOST_ASSERT( ! GetModifiedData().is_empty() );
            return GetModifiedData();
        }
    }
    const cRawBuffer& FASTCALL GetActiveData() const
    {
        if ( mUpdateStatus == usUnmodified )
            return GetOriginalData();
        else
        {
            BOOST_ASSERT( ! GetModifiedData().is_empty() );
            return GetModifiedData();
        }
    }

    void FASTCALL CommitUpdates();

    bool FASTCALL IsNull( const cFieldDef& field_def ) const                    { return GetReadRow().IsNull( field_def ); }
    bool FASTCALL IsNull( const cFieldDef_& field_def ) const                   { return GetReadRow().IsNull( field_def ); }
    void FASTCALL Nullify( const cFieldDef& field_def )                         { GetUpdateRow().Nullify( field_def ); }

    bool FASTCALL ReadBool( const cFieldDef& field_def ) const                  { return GetReadRow().ReadBool( field_def ); }
    char FASTCALL ReadByte( const cFieldDef& field_def ) const                  { return GetReadRow().ReadByte( field_def ); }
    short FASTCALL ReadShort( const cFieldDef& field_def ) const                { return GetReadRow().ReadShort( field_def ); }
    int FASTCALL ReadInteger( const cFieldDef& field_def ) const                { return GetReadRow().ReadInteger( field_def ); }
    long long FASTCALL ReadLongLong( const cFieldDef& field_def ) const         { return GetReadRow().ReadLongLong( field_def ); }
    double FASTCALL ReadFloat( const cFieldDef& field_def ) const               { return GetReadRow().ReadFloat( field_def ); }
    dbDate FASTCALL ReadDate( const cFieldDef& field_def ) const                { return GetReadRow().ReadDate( field_def ); }
    dbTime FASTCALL ReadTime( const cFieldDef& field_def ) const                { return GetReadRow().ReadTime( field_def ); }
    dbDateTime FASTCALL ReadDateTime( const cFieldDef& field_def ) const        { return GetReadRow().ReadDateTime( field_def ); }
    ds_string FASTCALL ReadString( const cFieldDef& field_def ) const           { return GetReadRow().ReadString( field_def ); }

    void FASTCALL WriteBool( const cFieldDef& field_def, bool value )
    {
        GetUpdateRow().WriteBool( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteByte( const cFieldDef& field_def, char value )
    {
        GetUpdateRow().WriteByte( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteShort( const cFieldDef& field_def, short value )
    {
        GetUpdateRow().WriteShort( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteInteger( const cFieldDef& field_def, int value )
    {
        GetUpdateRow().WriteInteger( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteLongLong( const cFieldDef& field_def, long long value )
    {
        GetUpdateRow().WriteLongLong( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteFloat( const cFieldDef& field_def, double value )
    {
        GetUpdateRow().WriteFloat( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteDate( const cFieldDef& field_def, const dbDate& value )
    {
        GetUpdateRow().WriteDate( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteTime( const cFieldDef& field_def, const dbTime& value )
    {
        GetUpdateRow().WriteTime( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteDateTime( const cFieldDef& field_def, const dbDateTime& value )
    {
        GetUpdateRow().WriteDateTime( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteString(const cFieldDef& field_def, const ds_string& value )
    {
        GetUpdateRow().WriteString( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteString( const cFieldDef& field_def, const char *value )
    {
        GetUpdateRow().WriteString( field_def, value );
        UpdateRecordStatus();
    }

    bool FASTCALL ReadBool( const cFieldDef_& field_def ) const                 { return GetReadRow().ReadBool( field_def ); }
    char FASTCALL ReadByte( const cFieldDef_& field_def ) const                 { return GetReadRow().ReadByte( field_def ); }
    short FASTCALL ReadShort( const cFieldDef_& field_def ) const               { return GetReadRow().ReadShort( field_def ); }
    int FASTCALL ReadInteger( const cFieldDef_& field_def ) const               { return GetReadRow().ReadInteger( field_def ); }
    long long FASTCALL ReadLongLong( const cFieldDef_& field_def ) const        { return GetReadRow().ReadLongLong( field_def ); }
    double FASTCALL ReadFloat( const cFieldDef_& field_def ) const              { return GetReadRow().ReadFloat( field_def ); }
    dbDate FASTCALL ReadDate( const cFieldDef_& field_def ) const               { return GetReadRow().ReadDate( field_def ); }
    dbTime FASTCALL ReadTime( const cFieldDef_& field_def ) const               { return GetReadRow().ReadTime( field_def ); }
    dbDateTime FASTCALL ReadDateTime( const cFieldDef_& field_def ) const       { return GetReadRow().ReadDateTime( field_def ); }
    ds_string FASTCALL ReadString( const cFieldDef_& field_def ) const          { return GetReadRow().ReadString( field_def ); }

    void FASTCALL WriteBool( const cFieldDef_& field_def, bool value )
    {
        GetUpdateRow().WriteBool( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteByte( const cFieldDef_& field_def, char value )
    {
        GetUpdateRow().WriteByte( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteShort( const cFieldDef_& field_def, short value )
    {
        GetUpdateRow().WriteShort( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteInteger( const cFieldDef_& field_def, int value )
    {
        GetUpdateRow().WriteInteger( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL DoubleBuffer::WriteLongLong( const cFieldDef_& field_def, long long value )
    {
        GetUpdateRow().WriteLongLong( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteFloat( const cFieldDef_& field_def, double value )
    {
        GetUpdateRow().WriteFloat( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteDate( const cFieldDef_& field_def, const dbDate& value )
    {
        GetUpdateRow().WriteDate( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteTime( const cFieldDef_& field_def, const dbTime& value )
    {
        GetUpdateRow().WriteTime( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteDateTime( const cFieldDef_& field_def, const dbDateTime& value )
    {
        GetUpdateRow().WriteDateTime( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteString(const cFieldDef_& field_def, const ds_string& value )
    {
        GetUpdateRow().WriteString( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL WriteString( const cFieldDef_& field_def, const char *value )
    {
        GetUpdateRow().WriteString( field_def, value );
        UpdateRecordStatus();
    }
};

//***********************************************************************
//******    DataRelation
//***********************************************************************
/*
class DataRelation
{
private:
    DataRelation        *mRelation;
    IDataNotify         *mDataNotify;
    void FASTCALL RemoveRelation( DataRelation *relation )
    {
        while ( relation->mRelation != this )
            relation = relation->mRelation;
        relation->mRelation = mRelation;
    }
public:
    CDFASTCALL DataRelation()
        : mRelation(this), mDataNotify(0)
    {
    }
    CDFASTCALL ~DataRelation()
    {
        RemoveRelation( this );
    }
    void FASTCALL AddRelation( DataRelation *new_data )
    {
        new_data->mRelation = mRelation;
        mRelation = new_data;
    }
};
*/

//***********************************************************************
//******    Data
//***********************************************************************
#if defined(SM_DS_ENABLE_NOTIFY)
class IDataNotify;
#endif

class Data;
typedef shared_ptr<Data>    spData;

class Data
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
{
private:
    typedef shared_ptr<DoubleBuffer>                            spDoubleBuffer;
public:
    typedef std::vector<spDoubleBuffer>                         container;
    typedef container::value_type                               value_type;
    typedef container::size_type                                size_type;
    typedef container::iterator                                 iterator;
    typedef std::pair<bool,size_type>                           locate_result;
    typedef std::pair<bool,std::pair<size_type,size_type> >     range_result;
private:
    typedef boost::shared_ptr<container>                        deleted_container;
    typedef boost::shared_ptr<int>                              lock_counter;
private:
    container               mData;
    spFieldDefs             mFieldDefs;         // this is shared among all related "Data"s
    deleted_container       mDeleted;           // this is shared among all related "Data"s
#if defined(SM_DS_ENABLE_NOTIFY)
    lock_counter            mLockCount;         // this is shared among all related "Data"s
    Data                    *mRelatedData;      // related "Data ring". Sorted or part of this data
    IDataNotify             *mTableNotify;
#endif

    container& FASTCALL GetContainer()                              { return ( mData ); }
    void FASTCALL Find_0( const Data::value_type& double_buffer, spSortCompare& compare,
                          iterator begin, iterator end, locate_result& result );
    void FASTCALL Find( const OpenValues& values, spSortCompare& compare,
                        iterator begin, iterator end, locate_result& result );
    void FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields,
                          iterator begin, iterator end, locate_result& result );
#if defined(SM_DS_ENABLE_NOTIFY)
    // relation managment
    void FASTCALL NotifyRecordAdded( const value_type& value );
    void FASTCALL NotifyRecordDeleted( const value_type& value );
    void FASTCALL NotifyUpdateLockReleased();

    void FASTCALL RemoveRelation( Data *relation )
    {
        while ( relation->mRelatedData != this )
            relation = relation->mRelatedData;
        relation->mRelatedData = mRelatedData;
    }
    void FASTCALL AddRelation( Data *new_data )
    {
        new_data->mRelatedData = mRelatedData;
        mRelatedData = new_data;
    }
    void FASTCALL GetNotifies( std::vector<IDataNotify *>& notifies );
#endif
    // noncopyable
    CDFASTCALL Data( const Data& src );
    Data& FASTCALL operator=( const Data& src );

#if defined(SM_DS_ENABLE_NOTIFY)
    CDFASTCALL Data( const spFieldDefs& field_defs, const deleted_container& deleted, lock_counter lock_count, IDataNotify *i_notify );
#else
    CDFASTCALL Data( const spFieldDefs& field_defs, const deleted_container& deleted );
#endif
public:
#if defined(SM_DS_ENABLE_NOTIFY)
    CDFASTCALL Data( IDataNotify *i_notify );
    CDFASTCALL Data( const cFieldDefs_& field_defs, IDataNotify *i_notify );
#else
    CDFASTCALL Data();
    CDFASTCALL Data( const cFieldDefs_& field_defs );
#endif
    CDFASTCALL ~Data();

    // IDataNotify * FASTCALL GetTableNotify()                         { return mTableNotify; }
    // void FASTCALL SetTableNotify( IDataNotify *i_notify )           { mTableNotify = IDataNotify; }

    int FASTCALL AddBuffer_ptr( const value_type& value );
    void FASTCALL InsertBuffer_ptr( const value_type& value, spSortCompare& compare );
    void FASTCALL DeleteBuffer_ptr( const value_type& value );
    int FASTCALL AddBuffer( const value_type& value );
    void FASTCALL Delete( int idx );

    // relation managment
#if defined(SM_DS_ENABLE_NOTIFY)
    void FASTCALL NotifyOpened();
    void FASTCALL NotifyClosed();
    void FASTCALL LockUpdates();
    void FASTCALL UnlockUpdates();
#endif

    value_type FASTCALL NewBuffer_usUnmodified();
    value_type FASTCALL NewBuffer_usInserted();

    bool FASTCALL is_empty() const                                  { return mData.empty(); }
    size_type FASTCALL size() const                                 { return mData.size(); }
    const value_type& FASTCALL operator[]( size_type idx ) const    { return mData[idx]; }

#if defined(SM_DS_ENABLE_NOTIFY)
    spData FASTCALL Clone_All( IDataNotify *i_notify );
#else
    spData FASTCALL Clone_All();
#endif
    void FASTCALL Sort( const SortControler& cmp );

    void FASTCALL Clear();
    void FASTCALL CommitUpdates();

    void FASTCALL AddField( const ds_string& name, cFieldKind kind, cFieldDataType data_type, unsigned int size );

    const spFieldDefs& FASTCALL GetFieldDefs() const                { return mFieldDefs; }
    const cFieldDef& FieldByName( const ds_string& field_name )     { return mFieldDefs->FieldByName( field_name ); }
    const cFieldDef& FieldByName( const char *field_name )          { return mFieldDefs->FieldByName( field_name ); }

    void FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields, locate_result& result );
    void FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields, size_type start, size_type end, locate_result& result );
    void FASTCALL Find( const OpenValues& values, spSortCompare& compare, locate_result& result );
    void FASTCALL Find( const OpenValues& values, spSortCompare& compare, size_type start, size_type end, locate_result& result );
    void FASTCALL GetRange( const OpenRangeValues& values, spSortCompare& compare, range_result& result );
};

#if defined(SM_DS_ENABLE_NOTIFY)
//***********************************************************************
//******    IDataNotify
//***********************************************************************
class IDataNotify
{
public:
    virtual void FASTCALL RecordAdded( const Data::value_type& value, bool locked ) = 0;
    virtual void FASTCALL RecordDeleted( const Data::value_type& value ) = 0;
    virtual void FASTCALL DataOpened( Data& data ) = 0;
    virtual void FASTCALL DataClosed() = 0;
    virtual void FASTCALL UpdateLockReleased() = 0;
    virtual CDFASTCALL ~IDataNotify()                       {} // empty
};
#endif

//---------------------------------------------------------------------------

}; // namespace detail

}; // namespace smds
//---------------------------------------------------------------------------
#endif

