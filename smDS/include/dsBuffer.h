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
#include <cstring>
//---------------------------------------------------------------------------
namespace smds
{

class Table;
class cTableReader;

enum cUpdateStatus { usUnmodified, usInserted, usModified, usDeleted };

inline cStream& operator << ( cStream& st, const cUpdateStatus a )     { return ( st.WriteBuffer( &a, sizeof(cUpdateStatus) ) ); }
inline cStream& operator >> ( cStream& st, cUpdateStatus& a )          { return ( st.ReadBuffer( &a, sizeof(cUpdateStatus) ) ); }

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
    friend class smds::cTableReader;

    class NullBits
    {
    public:
        static void Init( quantum *bits, size_type field_count, bool value )
        {
            std::memset( bits, value ? -1 : 0, field_count / quantum_bits + sizeof(quantum) );
        }
        static void calc_pos_mask( std::size_t bit_idx, std::size_t& quantum_idx, quantum& mask )
        {
            quantum_idx = (bit_idx / quantum_bits);
            mask = static_cast<quantum>(0x80 >> (bit_idx % quantum_bits));
        }
        static bool TestBit( quantum *bits, std::size_t bit_num )
        {
            std::size_t     quantum_idx;
            quantum         mask;

            calc_pos_mask( bit_num, quantum_idx, mask );
            return ( (bits[quantum_idx] & mask) != 0 );
        }
        static void SetBit( quantum *bits, std::size_t bit_num, bool value )
        {
            std::size_t     quantum_idx;
            quantum         mask;

            calc_pos_mask( bit_num, quantum_idx, mask );
            if ( value )
                bits[quantum_idx] |= mask;
            else
                bits[quantum_idx] &= static_cast<quantum>(~mask);      // static_cast for BCB warning
        }
    };

    boost::scoped_array<char>   mData;
    quantum                     *mNullBits;

    template <class T> T buffer_field_cast( int offset ) const
    {
        return reinterpret_cast<T>( raw_data() + offset );
    }

    var_blob_type ** blob_ptr_ptr( int offset ) const
    {
        return buffer_field_cast<var_blob_type **>( offset );
    }

    ds_string ** string_ptr_ptr( int offset ) const
    {
        return buffer_field_cast<ds_string **>( offset );
    }

    ds_wstring ** wstring_ptr_ptr( int offset ) const
    {
        return buffer_field_cast<ds_wstring **>( offset );
    }

    size_type CalcBufferSize( size_type buffer_size, size_type field_count )
    {
        return ( buffer_size + field_count / quantum_bits + sizeof(quantum) );
    }

    static ds_string& empty_string();

    void swap( cRawBuffer& other )
    {
        mData.swap( other.mData );
        std::swap( mNullBits, other.mNullBits );
    }
    // noncopyable
    cRawBuffer( const cRawBuffer& src );
    cRawBuffer& operator=( const cRawBuffer& src );
private:
    cRawBuffer( cFieldDefs *field_defs, bool init )
        : mData(), mNullBits()
    {
        if ( init )
            construct( field_defs );
    }
    ~cRawBuffer()
    {
    }
    bool is_empty() const                                  { return ( mData == 0 ); }
    void construct( cFieldDefs *field_defs )
    {
        size_type   buffer_size = field_defs->BufferSize();
        size_type   field_count = field_defs->Count();

        if ( is_empty() )
        {
            mData.reset( new char[CalcBufferSize( buffer_size, field_count )] );
            std::memset( mData.get(), 0, buffer_size );
        }
        mNullBits = reinterpret_cast<quantum *>(mData.get()) + buffer_size;
        NullBits::Init( mNullBits, field_count, true );
    }
    void copy_construct( cFieldDefs *field_defs, const cRawBuffer& src )
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

    void destroy( cFieldDefs *field_defs )
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
    void SetNull( const cFieldDef& field_def, bool value )             ; // { mNull[field_def.Index()] = value; }
    void SetNull( const cFieldDef_& field_def, bool value )            ; // { mNull[field_def.mIndex] = value; }

    char * raw_data() const                                            { return ( mData.get() ); }
//---------------------------------------------------------------------------
    template <class T> T& value_reader( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return T();
#endif
        return *(buffer_field_cast<T *>(field_def.Offset()));
    }
    template <class T> T& value_reader( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
#if defined SM_DS_NULL_VALUE_EXCEPTION
            throw eNullFieldValue();
#else
            return T();
#endif
        return *(buffer_field_cast<T *>(field_def.mOffset));
    }
//---------------------------------------------------------------------------
public:
    bool IsNull( const cFieldDef& field_def ) const            ; // { return ( mNull[field_def.Index()] ); }
    bool IsNull( const cFieldDef_& field_def ) const           ; // { return ( mNull[field_def.mIndex] ); }
    void Nullify( const cFieldDef& field_def )                 ; // { mNull[field_def.Index()] = true; }
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
    bool ReadBool( const cFieldDef& field_def ) const
    {
        return value_reader<bool>( field_def );
    }
//---------------------------------------------------------------------------
    char ReadByte( const cFieldDef& field_def ) const
    {
        return value_reader<char>( field_def );
    }
//---------------------------------------------------------------------------
    short ReadShort( const cFieldDef& field_def ) const
    {
        return value_reader<short>( field_def );
    }
//---------------------------------------------------------------------------
    int ReadInteger( const cFieldDef& field_def ) const
    {
        return value_reader<int>( field_def );
    }
//---------------------------------------------------------------------------
    long long ReadLongLong( const cFieldDef& field_def ) const
    {
        return value_reader<long long>( field_def );
    }
//---------------------------------------------------------------------------
    double ReadFloat( const cFieldDef& field_def ) const
    {
        return value_reader<double>( field_def );
    }
//---------------------------------------------------------------------------
    dbDate ReadDate( const cFieldDef& field_def ) const
    {
        return CreateDbDate( value_reader<dbDate_Internal>( field_def ) );
    }
//---------------------------------------------------------------------------
    dbTime ReadTime( const cFieldDef& field_def ) const
    {
        return CreateDbTime( value_reader<dbTime_Internal>( field_def ) );
    }
//---------------------------------------------------------------------------
    dbDateTime ReadDateTime( const cFieldDef& field_def ) const
    {
        return CreateDbDateTime( value_reader<dbDateTime_Internal>( field_def ) );
    }
//---------------------------------------------------------------------------
    const ds_string& ReadString( const cFieldDef& field_def ) const
    {
        return *value_reader<ds_string *>( field_def );
    }
//---------------------------------------------------------------------------
    Variant ReadVariant( const cFieldDef& field_def ) const;
//---------------------------------------------------------------------------
    void WriteBool( const cFieldDef& field_def, bool value )
    {
        *(buffer_field_cast<bool *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void WriteByte( const cFieldDef& field_def, char value )
    {
        *(buffer_field_cast<char *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void WriteShort( const cFieldDef& field_def, short value )
    {
        *(buffer_field_cast<short *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void WriteInteger( const cFieldDef& field_def, int value )
    {
        *(buffer_field_cast<int *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void WriteLongLong( const cFieldDef& field_def, long long value )
    {
        *(buffer_field_cast<long long *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void WriteFloat( const cFieldDef& field_def, double value )
    {
        *(buffer_field_cast<double *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void WriteDate( const cFieldDef& field_def, const dbDate& value )
    {
        *(buffer_field_cast<dbDate_Internal *>(field_def.Offset())) = value.AsInternal();
        SetNull( field_def, false );
    }
    void WriteDate( const cFieldDef& field_def, const dbDate_Internal& value )
    {
        *(buffer_field_cast<dbDate_Internal *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void WriteTime( const cFieldDef& field_def, const dbTime& value )
    {
        *(buffer_field_cast<dbTime_Internal *>(field_def.Offset())) = value.AsInternal();
        SetNull( field_def, false );
    }
    void WriteTime( const cFieldDef& field_def, const dbTime_Internal& value )
    {
        *(buffer_field_cast<dbTime_Internal *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void WriteDateTime( const cFieldDef& field_def, const dbDateTime_Internal& value )
    {
        *(buffer_field_cast<dbDateTime_Internal *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void WriteDateTime( const cFieldDef& field_def, const dbDateTime& value )
    {
        *(buffer_field_cast<dbDateTime_Internal *>(field_def.Offset())) = value.AsInternal();
        SetNull( field_def, false );
    }
    void WriteGUID( const cFieldDef& field_def, const dbGUID_Internal& value )
    {
        *(buffer_field_cast<dbGUID_Internal *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void WriteGUID( const cFieldDef& field_def, const dbGUID& value )
    {
        *(buffer_field_cast<dbGUID_Internal *>(field_def.Offset())) = value.AsInternal();
        SetNull( field_def, false );
    }
    void WriteString( const cFieldDef& field_def, const ds_string& value )
    {
        ds_string   **data = string_ptr_ptr( field_def.Offset() );

        if ( *data == 0 )
            *data = new ds_string( value );
        else
            (*data)->assign( value, 0, field_def.DataSize() );
        SetNull( field_def, false );
    }
    void WriteString( const cFieldDef& field_def, const char *value )
    {
        ds_string   **data = string_ptr_ptr( field_def.Offset() );

        if ( *data == 0 )
            *data = new ds_string( value );
        else
            (*data)->assign( value, std::min<ds_string::size_type>( std::strlen( value ), field_def.DataSize() ) );
        SetNull( field_def, false );
    }
    void WriteVariant( const cFieldDef& field_def, const Variant& value );
//---------------------------------------------------------------------------
    bool ReadBool( const cFieldDef_& field_def ) const
    {
        return value_reader<bool>( field_def );
    }
//---------------------------------------------------------------------------
    char ReadByte( const cFieldDef_& field_def ) const
    {
        return value_reader<char>( field_def );
    }
//---------------------------------------------------------------------------
    short ReadShort( const cFieldDef_& field_def ) const
    {
        return value_reader<short>( field_def );
    }
//---------------------------------------------------------------------------
    int ReadInteger( const cFieldDef_& field_def ) const
    {
        return value_reader<int>( field_def );
    }
//---------------------------------------------------------------------------
    long long ReadLongLong( const cFieldDef_& field_def ) const
    {
        return value_reader<long long>( field_def );
    }
//---------------------------------------------------------------------------
    double ReadFloat( const cFieldDef_& field_def ) const
    {
        return value_reader<double>( field_def );
    }
//---------------------------------------------------------------------------
    dbDate ReadDate( const cFieldDef_& field_def ) const
    {
        return CreateDbDate( value_reader<dbDate_Internal>( field_def ) );
    }
//---------------------------------------------------------------------------
    dbTime ReadTime( const cFieldDef_& field_def ) const
    {
        return CreateDbTime( value_reader<dbTime_Internal>( field_def ) );
    }
//---------------------------------------------------------------------------
    dbDateTime ReadDateTime( const cFieldDef_& field_def ) const
    {
        return CreateDbDateTime( value_reader<dbDateTime_Internal>( field_def ) );
    }
//---------------------------------------------------------------------------
    const ds_string& ReadString( const cFieldDef_& field_def ) const
    {
        return *value_reader<ds_string *>( field_def );
    }
//---------------------------------------------------------------------------
    void WriteBool( const cFieldDef_& field_def, bool value )
    {
        *(buffer_field_cast<bool *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void WriteByte( const cFieldDef_& field_def, char value )
    {
        *(buffer_field_cast<char *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void WriteShort( const cFieldDef_& field_def, short value )
    {
        *(buffer_field_cast<short *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void WriteInteger( const cFieldDef_& field_def, int value )
    {
        *(buffer_field_cast<int *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void WriteLongLong( const cFieldDef_& field_def, long long value )
    {
        *(buffer_field_cast<long long *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void WriteFloat( const cFieldDef_& field_def, double value )
    {
        *(buffer_field_cast<double *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void WriteDate( const cFieldDef_& field_def, const dbDate& value )
    {
        *(buffer_field_cast<dbDate_Internal *>(field_def.mOffset)) = value.AsInternal();
        SetNull( field_def, false );
    }
    void WriteTime( const cFieldDef_& field_def, const dbTime& value )
    {
        *(buffer_field_cast<dbTime_Internal *>(field_def.mOffset)) = value.AsInternal();
        SetNull( field_def, false );
    }
    void WriteDateTime( const cFieldDef_& field_def, const dbDateTime& value )
    {
        *(buffer_field_cast<dbDateTime_Internal *>(field_def.mOffset)) = value.AsInternal();
        SetNull( field_def, false );
    }
    void WriteString( const cFieldDef_& field_def, const ds_string& value )
    {
        ds_string   **data = string_ptr_ptr( field_def.mOffset );

        if ( *data == 0 )
            *data = new ds_string( value );
        else
            (*data)->assign( value, 0, field_def.mDataSize );
        SetNull( field_def, false );
    }
    void WriteString( const cFieldDef_& field_def, const char *value )
    {
        ds_string   **data = string_ptr_ptr( field_def.mOffset );

        if ( *data == 0 )
            *data = new ds_string( value );
        else
            (*data)->assign( value, std::min<ds_string::size_type>( std::strlen( value ), field_def.mDataSize ) );
        SetNull( field_def, false );
    }
//---------------------------------------------------------------------------
    bool ReadBoolNN( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<bool *>(field_def.Offset()));
    }
    char ReadByteNN( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<char *>(field_def.Offset()));
    }
    short ReadShortNN( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<short *>(field_def.Offset()));
    }
    int ReadIntegerNN( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<int *>(field_def.Offset()));
    }
    long long ReadLongLongNN( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<long long *>(field_def.Offset()));
    }
    double ReadFloatNN( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<double *>(field_def.Offset()));
    }
    dbDate ReadDateNN( const cFieldDef& field_def ) const
    {
        return CreateDbDate( *(buffer_field_cast<dbDate_Internal *>(field_def.Offset())) );
    }
    const dbDate_Internal& ReadDateNNref( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<dbDate_Internal *>(field_def.Offset()));
    }
    dbTime ReadTimeNN( const cFieldDef& field_def ) const
    {
        return CreateDbTime( *(buffer_field_cast<dbTime_Internal *>(field_def.Offset())) );
    }
    const dbTime_Internal& ReadTimeNNref( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<dbTime_Internal *>(field_def.Offset()));
    }
    dbDateTime ReadDateTimeNN( const cFieldDef& field_def ) const
    {
        return CreateDbDateTime( *(buffer_field_cast<dbDateTime_Internal *>(field_def.Offset())) );
    }
    const dbDateTime_Internal& ReadDateTimeNNref( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<dbDateTime_Internal *>(field_def.Offset()));
    }
    dbGUID ReadGUIDNN( const cFieldDef& field_def ) const
    {
        return dbGUID( *(buffer_field_cast<dbGUID_Internal *>(field_def.Offset())) );
    }
    const dbGUID_Internal& ReadGUIDNNref( const cFieldDef& field_def ) const
    {
        return *(buffer_field_cast<dbGUID_Internal *>(field_def.Offset()));
    }
    const ds_string& ReadStringNN( const cFieldDef& field_def ) const
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

    const cRawBuffer& GetReadRow() const       { return ( GetActiveData() ); }
    cRawBuffer& GetUpdateRow()                 { return ( GetUpdateData() ); }
    // noncopyable
    DoubleBuffer( const DoubleBuffer& src );
    DoubleBuffer& operator=( const DoubleBuffer& src );

    cRawBuffer& GetModifiedData()              { return ( mModifiedData ); }
    const cRawBuffer& GetModifiedData() const  { return ( mModifiedData ); }
    cRawBuffer& GetUpdateData()
    {
        if ( mUpdateStatus == usUnmodified )
            mModifiedData.copy_construct( mFieldDefs, GetOriginalData() );
        return GetModifiedData();
    }
    void UpdateRecordStatus()
    {
        if ( mUpdateStatus == usUnmodified )
            mUpdateStatus = usModified;
    }
public:
    // the 'bool unmodified' parameter if false means 'inserted'
    //DoubleBuffer( cRawBuffer::size_type buffer_size, cRawBuffer::size_type field_count, bool unmodified );
    DoubleBuffer( cFieldDefs *field_defs, bool unmodified );
    ~DoubleBuffer();
    cRawBuffer& GetOriginalData()              { return ( mOriginalData ); }
    const cRawBuffer& GetOriginalData() const  { return ( mOriginalData ); }
    cUpdateStatus GetUpdateStatus() const      { return ( mUpdateStatus ); }

    cRawBuffer& GetActiveData()
    {
        if ( mUpdateStatus == usUnmodified )
            return GetOriginalData();
        else
        {
            BOOST_ASSERT( ! GetModifiedData().is_empty() );
            return GetModifiedData();
        }
    }
    const cRawBuffer& GetActiveData() const
    {
        if ( mUpdateStatus == usUnmodified )
            return GetOriginalData();
        else
        {
            BOOST_ASSERT( ! GetModifiedData().is_empty() );
            return GetModifiedData();
        }
    }

    void CommitUpdates();

    bool IsNull( const cFieldDef& field_def ) const                    { return GetReadRow().IsNull( field_def ); }
    bool IsNull( const cFieldDef_& field_def ) const                   { return GetReadRow().IsNull( field_def ); }
    void Nullify( const cFieldDef& field_def )                         { GetUpdateRow().Nullify( field_def ); }

    bool ReadBool( const cFieldDef& field_def ) const                  { return GetReadRow().ReadBool( field_def ); }
    char ReadByte( const cFieldDef& field_def ) const                  { return GetReadRow().ReadByte( field_def ); }
    short ReadShort( const cFieldDef& field_def ) const                { return GetReadRow().ReadShort( field_def ); }
    int ReadInteger( const cFieldDef& field_def ) const                { return GetReadRow().ReadInteger( field_def ); }
    long long ReadLongLong( const cFieldDef& field_def ) const         { return GetReadRow().ReadLongLong( field_def ); }
    double ReadFloat( const cFieldDef& field_def ) const               { return GetReadRow().ReadFloat( field_def ); }
    dbDate ReadDate( const cFieldDef& field_def ) const                { return GetReadRow().ReadDate( field_def ); }
    dbTime ReadTime( const cFieldDef& field_def ) const                { return GetReadRow().ReadTime( field_def ); }
    dbDateTime ReadDateTime( const cFieldDef& field_def ) const        { return GetReadRow().ReadDateTime( field_def ); }
    ds_string ReadString( const cFieldDef& field_def ) const           { return GetReadRow().ReadString( field_def ); }
    Variant ReadVariant( const cFieldDef& field_def ) const            { return GetReadRow().ReadVariant( field_def ); }

    void WriteBool( const cFieldDef& field_def, bool value )
    {
        GetUpdateRow().WriteBool( field_def, value );
        UpdateRecordStatus();
    }
    void WriteByte( const cFieldDef& field_def, char value )
    {
        GetUpdateRow().WriteByte( field_def, value );
        UpdateRecordStatus();
    }
    void WriteShort( const cFieldDef& field_def, short value )
    {
        GetUpdateRow().WriteShort( field_def, value );
        UpdateRecordStatus();
    }
    void WriteInteger( const cFieldDef& field_def, int value )
    {
        GetUpdateRow().WriteInteger( field_def, value );
        UpdateRecordStatus();
    }
    void WriteLongLong( const cFieldDef& field_def, long long value )
    {
        GetUpdateRow().WriteLongLong( field_def, value );
        UpdateRecordStatus();
    }
    void WriteFloat( const cFieldDef& field_def, double value )
    {
        GetUpdateRow().WriteFloat( field_def, value );
        UpdateRecordStatus();
    }
    void WriteDate( const cFieldDef& field_def, const dbDate& value )
    {
        GetUpdateRow().WriteDate( field_def, value );
        UpdateRecordStatus();
    }
    void WriteTime( const cFieldDef& field_def, const dbTime& value )
    {
        GetUpdateRow().WriteTime( field_def, value );
        UpdateRecordStatus();
    }
    void WriteDateTime( const cFieldDef& field_def, const dbDateTime& value )
    {
        GetUpdateRow().WriteDateTime( field_def, value );
        UpdateRecordStatus();
    }
    void WriteString(const cFieldDef& field_def, const ds_string& value )
    {
        GetUpdateRow().WriteString( field_def, value );
        UpdateRecordStatus();
    }
    void WriteString( const cFieldDef& field_def, const char *value )
    {
        GetUpdateRow().WriteString( field_def, value );
        UpdateRecordStatus();
    }

    void WriteVariant( const cFieldDef& field_def, const Variant& value )
    {
        GetUpdateRow().WriteVariant( field_def, value );
        UpdateRecordStatus();
    }

    bool ReadBool( const cFieldDef_& field_def ) const                 { return GetReadRow().ReadBool( field_def ); }
    char ReadByte( const cFieldDef_& field_def ) const                 { return GetReadRow().ReadByte( field_def ); }
    short ReadShort( const cFieldDef_& field_def ) const               { return GetReadRow().ReadShort( field_def ); }
    int ReadInteger( const cFieldDef_& field_def ) const               { return GetReadRow().ReadInteger( field_def ); }
    long long ReadLongLong( const cFieldDef_& field_def ) const        { return GetReadRow().ReadLongLong( field_def ); }
    double ReadFloat( const cFieldDef_& field_def ) const              { return GetReadRow().ReadFloat( field_def ); }
    dbDate ReadDate( const cFieldDef_& field_def ) const               { return GetReadRow().ReadDate( field_def ); }
    dbTime ReadTime( const cFieldDef_& field_def ) const               { return GetReadRow().ReadTime( field_def ); }
    dbDateTime ReadDateTime( const cFieldDef_& field_def ) const       { return GetReadRow().ReadDateTime( field_def ); }
    ds_string ReadString( const cFieldDef_& field_def ) const          { return GetReadRow().ReadString( field_def ); }

    void WriteBool( const cFieldDef_& field_def, bool value )
    {
        GetUpdateRow().WriteBool( field_def, value );
        UpdateRecordStatus();
    }
    void WriteByte( const cFieldDef_& field_def, char value )
    {
        GetUpdateRow().WriteByte( field_def, value );
        UpdateRecordStatus();
    }
    void WriteShort( const cFieldDef_& field_def, short value )
    {
        GetUpdateRow().WriteShort( field_def, value );
        UpdateRecordStatus();
    }
    void WriteInteger( const cFieldDef_& field_def, int value )
    {
        GetUpdateRow().WriteInteger( field_def, value );
        UpdateRecordStatus();
    }
    void WriteLongLong( const cFieldDef_& field_def, long long value )
    {
        GetUpdateRow().WriteLongLong( field_def, value );
        UpdateRecordStatus();
    }
    void WriteFloat( const cFieldDef_& field_def, double value )
    {
        GetUpdateRow().WriteFloat( field_def, value );
        UpdateRecordStatus();
    }
    void WriteDate( const cFieldDef_& field_def, const dbDate& value )
    {
        GetUpdateRow().WriteDate( field_def, value );
        UpdateRecordStatus();
    }
    void WriteTime( const cFieldDef_& field_def, const dbTime& value )
    {
        GetUpdateRow().WriteTime( field_def, value );
        UpdateRecordStatus();
    }
    void WriteDateTime( const cFieldDef_& field_def, const dbDateTime& value )
    {
        GetUpdateRow().WriteDateTime( field_def, value );
        UpdateRecordStatus();
    }
    void WriteString(const cFieldDef_& field_def, const ds_string& value )
    {
        GetUpdateRow().WriteString( field_def, value );
        UpdateRecordStatus();
    }
    void WriteString( const cFieldDef_& field_def, const char *value )
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
    void RemoveRelation( DataRelation *relation )
    {
        while ( relation->mRelation != this )
            relation = relation->mRelation;
        relation->mRelation = mRelation;
    }
public:
    DataRelation()
        : mRelation(this), mDataNotify(0)
    {
    }
    ~DataRelation()
    {
        RemoveRelation( this );
    }
    void AddRelation( DataRelation *new_data )
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

    container& GetContainer()                              { return ( mData ); }
    void Find_0( const Data::value_type& double_buffer, spSortCompare& compare,
                          iterator begin, iterator end, locate_result& result );
    void Find( const OpenValues& values, spSortCompare& compare,
                        iterator begin, iterator end, locate_result& result );
    void Locate( const OpenValues& values, const OpenFindFields& fields,
                          iterator begin, iterator end, locate_result& result );
#if defined(SM_DS_ENABLE_NOTIFY)
    // relation managment
    void NotifyRecordAdded( const value_type& value );
    void NotifyRecordDeleted( const value_type& value );
    void NotifyUpdateLockReleased();

    void RemoveRelation( Data *relation )
    {
        while ( relation->mRelatedData != this )
            relation = relation->mRelatedData;
        relation->mRelatedData = mRelatedData;
    }
    void AddRelation( Data *new_data )
    {
        new_data->mRelatedData = mRelatedData;
        mRelatedData = new_data;
    }
    void GetNotifies( std::vector<IDataNotify *>& notifies );
#endif
    // noncopyable
    Data( const Data& src );
    Data& operator=( const Data& src );

#if defined(SM_DS_ENABLE_NOTIFY)
    Data( const spFieldDefs& field_defs, const deleted_container& deleted, lock_counter lock_count, IDataNotify *i_notify );
#else
    Data( const spFieldDefs& field_defs, const deleted_container& deleted );
#endif
public:
#if defined(SM_DS_ENABLE_NOTIFY)
    Data( IDataNotify *i_notify );
    Data( const cFieldDefs_& field_defs, IDataNotify *i_notify );
#else
    Data();
    Data( const cFieldDefs_& field_defs );
#endif
    ~Data();

    // IDataNotify * GetTableNotify()                         { return mTableNotify; }
    // void SetTableNotify( IDataNotify *i_notify )           { mTableNotify = IDataNotify; }

    int AddBuffer_ptr( const value_type& value );
    void InsertBuffer_ptr( const value_type& value, spSortCompare& compare );
    void DeleteBuffer_ptr( const value_type& value );
    int AddBuffer( const value_type& value );
    void Delete( int idx );

    // relation managment
#if defined(SM_DS_ENABLE_NOTIFY)
    void NotifyOpened();
    void NotifyClosed();
    void LockUpdates();
    void UnlockUpdates();
#endif

    value_type NewBuffer_usUnmodified();
    value_type NewBuffer_usInserted();

    bool is_empty() const                                  { return mData.empty(); }
    size_type size() const                                 { return mData.size(); }
    const value_type& operator[]( size_type idx ) const    { return mData[idx]; }

#if defined(SM_DS_ENABLE_NOTIFY)
    spData Clone_All( IDataNotify *i_notify );
#else
    spData Clone_All();
#endif
    void Sort( const SortControler& cmp );

    void Clear();
    void CommitUpdates();

    void AddField( const std_string& name, cFieldKind kind, cFieldDataType data_type, unsigned int size );

    const spFieldDefs& GetFieldDefs() const                         { return mFieldDefs; }
    const cFieldDef& FieldByName( const std_string& field_name )    { return mFieldDefs->FieldByName( field_name ); }
    const cFieldDef& FieldByName( const std_char *field_name )      { return mFieldDefs->FieldByName( field_name ); }

    void Locate( const OpenValues& values, const OpenFindFields& fields, locate_result& result );
    void Locate( const OpenValues& values, const OpenFindFields& fields, size_type start, size_type end, locate_result& result );
    void Find( const OpenValues& values, spSortCompare& compare, locate_result& result );
    void Find( const OpenValues& values, spSortCompare& compare, size_type start, size_type end, locate_result& result );
    void GetRange( const OpenRangeValues& values, spSortCompare& compare, range_result& result );
};

#if defined(SM_DS_ENABLE_NOTIFY)
//***********************************************************************
//******    IDataNotify
//***********************************************************************
class IDataNotify
{
public:
    virtual void RecordAdded( const Data::value_type& value, bool locked ) = 0;
    virtual void RecordDeleted( const Data::value_type& value ) = 0;
    virtual void DataOpened( Data& data ) = 0;
    virtual void DataClosed() = 0;
    virtual void UpdateLockReleased() = 0;
    virtual ~IDataNotify()                       {} // empty
};
#endif

//---------------------------------------------------------------------------

} // namespace detail

} // namespace smds
//---------------------------------------------------------------------------
#endif

