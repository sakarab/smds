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
#include "dsSmartPtr.h"
#include <boost/scoped_array.hpp>
#include "dsUtils.h"
#include "dsTypes.h"
#include "dsFields.h"
#include "dsDateTime.h"
#include "dsExceptions.h"
#include "dsVariant.h"
#include "dsIndex.h"
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
    typedef unsigned char   quantum;

    friend class Table;
    friend class cDoubleBuffer;
    friend class cTableReader;

    boost::scoped_array<char>   mData;
    quantum                     *mNullBits;

    template <class T> T buffer_field_cast( int offset ) const
    {
        return ( reinterpret_cast<T>( raw_data() + offset ) );
    }

    size_type FASTCALL CalcBufferSize( size_type buffer_size, size_type field_count )
    {
        return ( buffer_size + field_count/sizeof(quantum)+1 );
    }
    void FASTCALL InitNullBits( size_type field_count, bool value )
    {
        std::memset( mNullBits, value ? -1 : 0, field_count/sizeof(quantum)+1 );
    }
    void FASTCALL calc_pos_mask( std::size_t bit_idx, std::size_t& quantum_idx, quantum& mask ) const
    {
        quantum_idx = bit_idx / sizeof(quantum);
        mask = static_cast<quantum>(0x80 >> (bit_idx % sizeof(quantum)));
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
#ifndef SM_DS_STRING_AS_STRING
    void FASTCALL WriteStringLen( int offset, const char *value, int len, int max_len )
    {
        std::memcpy( buffer_field_cast<char *>(offset), value, std::min<int>( len, max_len ) );
        if ( len < max_len )
            *(buffer_field_cast<char *>(offset) + len) = 0;
    }

    int FASTCALL BufferStringLen( const char *value, int max_len ) const
    {
        const char  *pos = value;

        while ( max_len-- > 0 )
            if ( *pos++ == 0 )
                break;
        return ( pos - value );
    }
#endif
#ifdef SM_DS_STRING_AS_STRING
    static ds_string& FASTCALL empty_string();
#endif
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
        : mData()
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
            for ( cFieldDefs::iterator n = field_defs->begin(), eend = field_defs->end() ; n != eend ; ++n )
            {
                if ( n->DataType() == ftBlob )
                    new (buffer_field_cast<var_blob_type *>(n->Offset()))var_blob_type();
#ifdef SM_DS_STRING_AS_STRING
                else if ( n->DataType() == ftWString )
                    new (buffer_field_cast<ds_wstring *>(n->Offset()))ds_wstring();
                else if ( n->DataType() == ftString )
                    new (buffer_field_cast<ds_string *>(n->Offset()))ds_string();
#endif
            }
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
                new (buffer_field_cast<var_blob_type *>(n->Offset()))var_blob_type( *(src.buffer_field_cast<var_blob_type *>(n->Offset())) );
#ifdef SM_DS_STRING_AS_STRING
            else if ( n->DataType() == ftWString )
                new (buffer_field_cast<ds_wstring *>(n->Offset()))ds_wstring( *(src.buffer_field_cast<ds_wstring *>(n->Offset())) );
            else if ( n->DataType() == ftString )
                new (buffer_field_cast<ds_string *>(n->Offset()))ds_string( *(src.buffer_field_cast<ds_string *>(n->Offset())) );
#endif
        }
    }
    void FASTCALL destroy( cFieldDefs *field_defs )
    {
        if ( ! is_empty() )
        {
            for ( cFieldDefs::iterator n = field_defs->begin(), eend = field_defs->end() ; n != eend ; ++n )
            {
                if ( n->DataType() == ftBlob )
                    buffer_field_cast<var_blob_type *>(n->Offset())->~var_blob_type();
#ifdef SM_DS_STRING_AS_STRING
                else if ( n->DataType() == ftWString )
                    buffer_field_cast<ds_wstring *>(n->Offset())->~ds_wstring();
                else if ( n->DataType() == ftString )
                    buffer_field_cast<ds_string *>(n->Offset())->~ds_string();
#endif
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
    bool FASTCALL ReadBool( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<bool *>(field_def.Offset())) );
    }
    char FASTCALL ReadChar( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<char *>(field_def.Offset())) );
    }
    wchar_t FASTCALL ReadWChar( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<wchar_t *>(field_def.Offset())) );
    }
    short FASTCALL ReadShort( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<short *>(field_def.Offset())) );
    }
    int FASTCALL ReadInteger( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<int *>(field_def.Offset())) );
    }
    long FASTCALL ReadLong( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<long *>(field_def.Offset())) );
    }
    double FASTCALL ReadFloat( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<double *>(field_def.Offset())) );
    }
    cDateTime FASTCALL ReadDate( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( cDateTime( *(buffer_field_cast<cDateTime *>(field_def.Offset())) ) );
    }

#ifdef SM_DS_STRING_AS_STRING
    const ds_string& FASTCALL ReadString( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<ds_string *>(field_def.Offset())) );
    }
#else
    ds_string FASTCALL ReadString( const cFieldDef& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( ds_string( buffer_field_cast<const char *>(field_def.Offset()),
                            BufferStringLen( buffer_field_cast<const char *>(field_def.Offset()), field_def.Size_() ) ) );
    }
#endif
    Variant FASTCALL ReadVariant( const cFieldDef& field_def ) const;
//---------------------------------------------------------------------------
    void FASTCALL WriteBool( const cFieldDef& field_def, bool value )
    {
        *(buffer_field_cast<bool *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteChar( const cFieldDef& field_def, char value )
    {
        *(buffer_field_cast<char *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteWChar( const cFieldDef& field_def, wchar_t value )
    {
        *(buffer_field_cast<wchar_t *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
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
    void FASTCALL WriteLong( const cFieldDef& field_def, long value )
    {
        *(buffer_field_cast<long *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteFloat( const cFieldDef& field_def, double value )
    {
        *(buffer_field_cast<double *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteDate( const cFieldDef& field_def, const cDateTime& value )
    {
        *(buffer_field_cast<cDateTime *>(field_def.Offset())) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteString( const cFieldDef& field_def, const ds_string& value )
    {
#ifdef SM_DS_STRING_AS_STRING
        (buffer_field_cast<ds_string *>(field_def.Offset()))->assign( value, 0, field_def.DataSize_() );
#else
        WriteStringLen( field_def.Offset(), value.c_str(), value.size(), field_def.Size_() );
#endif
        SetNull( field_def, false );
    }
    void FASTCALL WriteString( const cFieldDef& field_def, const char *value )
    {
#ifdef SM_DS_STRING_AS_STRING
        (buffer_field_cast<ds_string *>(field_def.Offset()))->assign( value, std::min<ds_string::size_type>( std::strlen( value ), field_def.DataSize_() ) );
#else
        WriteStringLen( field_def.Offset(), value, std::strlen( value ), field_def.Size_() );
#endif
        SetNull( field_def, false );
    }
    void FASTCALL WriteVariant( const cFieldDef& field_def, const Variant& value );
//---------------------------------------------------------------------------
    bool FASTCALL ReadBool( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<bool *>(field_def.mOffset)) );
    }
    char FASTCALL ReadChar( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<char *>(field_def.mOffset)) );
    }
    wchar_t FASTCALL ReadWChar( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<wchar_t *>(field_def.mOffset)) );
    }
    short FASTCALL ReadShort( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<short *>(field_def.mOffset)) );
    }
    int FASTCALL ReadInteger( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<int *>(field_def.mOffset)) );
    }
    long FASTCALL ReadLong( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<long *>(field_def.mOffset)) );
    }
    double FASTCALL ReadFloat( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<double *>(field_def.mOffset)) );
    }
    cDateTime FASTCALL ReadDate( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( cDateTime( *(buffer_field_cast<cDateTime *>(field_def.mOffset)) ) );
    }

#ifdef SM_DS_STRING_AS_STRING
    const ds_string& FASTCALL ReadString( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( *(buffer_field_cast<ds_string *>(field_def.mOffset)) );
    }
#else
    ds_string FASTCALL ReadString( const cFieldDef_& field_def ) const
    {
        if ( IsNull( field_def ) )
            throw eNullFieldValue();
        return ( ds_string( buffer_field_cast<const char *>(field_def.mOffset),
                            BufferStringLen( buffer_field_cast<const char *>(field_def.mOffset), field_def.mSize ) ) );
    }
#endif
//---------------------------------------------------------------------------
    void FASTCALL WriteBool( const cFieldDef_& field_def, bool value )
    {
        *(buffer_field_cast<bool *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteChar( const cFieldDef_& field_def, char value )
    {
        *(buffer_field_cast<char *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteWChar( const cFieldDef_& field_def, wchar_t value )
    {
        *(buffer_field_cast<wchar_t *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
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
    void FASTCALL WriteLong( const cFieldDef_& field_def, long value )
    {
        *(buffer_field_cast<long *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteFloat( const cFieldDef_& field_def, double value )
    {
        *(buffer_field_cast<double *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteDate( const cFieldDef_& field_def, const cDateTime& value )
    {
        *(buffer_field_cast<cDateTime *>(field_def.mOffset)) = value;
        SetNull( field_def, false );
    }
    void FASTCALL WriteString( const cFieldDef_& field_def, const ds_string& value )
    {
#ifdef SM_DS_STRING_AS_STRING
        (buffer_field_cast<ds_string *>(field_def.mOffset))->assign( value, 0, field_def.mSize );
#else
        WriteStringLen( field_def.mOffset, value.c_str(), value.size(), field_def.mSize );
#endif
        SetNull( field_def, false );
    }
    void FASTCALL WriteString( const cFieldDef_& field_def, const char *value )
    {
#ifdef SM_DS_STRING_AS_STRING
        (buffer_field_cast<ds_string *>(field_def.mOffset))->assign( value, std::min<ds_string::size_type>( std::strlen( value ), field_def.mSize ) );
#else
        WriteStringLen( field_def.mOffset, value, std::strlen( value ), field_def.mSize );
#endif
        SetNull( field_def, false );
    }
//---------------------------------------------------------------------------
    bool FASTCALL ReadBoolNN( const cFieldDef& field_def ) const
    {
        return ( *(buffer_field_cast<bool *>(field_def.Offset())) );
    }
    char FASTCALL ReadCharNN( const cFieldDef& field_def ) const
    {
        return ( *(buffer_field_cast<char *>(field_def.Offset())) );
    }
    wchar_t FASTCALL ReadWCharNN( const cFieldDef& field_def ) const
    {
        return ( *(buffer_field_cast<wchar_t *>(field_def.Offset())) );
    }
    short FASTCALL ReadShortNN( const cFieldDef& field_def ) const
    {
        return ( *(buffer_field_cast<short *>(field_def.Offset())) );
    }
    int FASTCALL ReadIntegerNN( const cFieldDef& field_def ) const
    {
        return ( *(buffer_field_cast<int *>(field_def.Offset())) );
    }
    long FASTCALL ReadLongNN( const cFieldDef& field_def ) const
    {
        return ( *(buffer_field_cast<long *>(field_def.Offset())) );
    }
    double FASTCALL ReadFloatNN( const cFieldDef& field_def ) const
    {
        return ( *(buffer_field_cast<double *>(field_def.Offset())) );
    }
    cDateTime FASTCALL ReadDateNN( const cFieldDef& field_def ) const
    {
        return ( cDateTime( *(buffer_field_cast<cDateTime *>(field_def.Offset())) ) );
    }
#ifdef SM_DS_STRING_AS_STRING
    const ds_string& FASTCALL ReadStringNN( const cFieldDef& field_def ) const
    {
        return ( *(buffer_field_cast<ds_string *>(field_def.Offset())) );
    }
#else
    ds_string FASTCALL ReadStringNN( const cFieldDef& field_def ) const
    {
        return ( ds_string( buffer_field_cast<const char *>(field_def.Offset()),
                            BufferStringLen( buffer_field_cast<const char *>(field_def.Offset()), field_def.Size_() ) ) );
    }
#endif
};

//***********************************************************************
//******    cDoubleBuffer
//***********************************************************************
class cDoubleBuffer
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
    CDFASTCALL cDoubleBuffer( const cDoubleBuffer& src );
    cDoubleBuffer& FASTCALL operator=( const cDoubleBuffer& src );

    cRawBuffer& FASTCALL GetModifiedData()              { return ( mModifiedData ); }
    const cRawBuffer& FASTCALL GetModifiedData() const  { return ( mModifiedData ); }
    cRawBuffer& FASTCALL GetUpdateData()
    {
        if ( mUpdateStatus == usUnmodified )
            mModifiedData.copy_construct( mFieldDefs, GetOriginalData() );
        return ( GetModifiedData() );
    }
    void FASTCALL UpdateRecordStatus()
    {
        if ( mUpdateStatus == usUnmodified )
            mUpdateStatus = usModified;
    }
public:
    // the 'bool unmodified' parameter if false means 'inserted'
    //CDFASTCALL cDoubleBuffer( cRawBuffer::size_type buffer_size, cRawBuffer::size_type field_count, bool unmodified );
    CDFASTCALL cDoubleBuffer( cFieldDefs *field_defs, bool unmodified );
    CDFASTCALL ~cDoubleBuffer();
    cRawBuffer& FASTCALL GetOriginalData()              { return ( mOriginalData ); }
    const cRawBuffer& FASTCALL GetOriginalData() const  { return ( mOriginalData ); }
    cUpdateStatus FASTCALL GetUpdateStatus() const      { return ( mUpdateStatus ); }

    cRawBuffer& FASTCALL GetActiveData()
    {
        if ( mUpdateStatus == usUnmodified )
            return ( GetOriginalData() );
        else
        {
            BOOST_ASSERT( ! GetModifiedData().is_empty() );
            return ( GetModifiedData() );
        }
    }
    const cRawBuffer& FASTCALL GetActiveData() const
    {
        if ( mUpdateStatus == usUnmodified )
            return ( GetOriginalData() );
        else
        {
            BOOST_ASSERT( ! GetModifiedData().is_empty() );
            return ( GetModifiedData() );
        }
    }

    void FASTCALL CommitUpdates();

    bool FASTCALL IsNull( const cFieldDef& field_def ) const                    { return ( GetReadRow().IsNull( field_def ) ); }
    bool FASTCALL IsNull( const cFieldDef_& field_def ) const                   { return ( GetReadRow().IsNull( field_def ) ); }
    void FASTCALL Nullify( const cFieldDef& field_def )                         { return ( GetUpdateRow().Nullify( field_def ) ); }

    bool FASTCALL ReadBool( const cFieldDef& field_def ) const                  { return ( GetReadRow().ReadBool( field_def ) ); }
    char FASTCALL ReadChar( const cFieldDef& field_def ) const                  { return ( GetReadRow().ReadChar( field_def ) ); }
    wchar_t FASTCALL ReadWChar( const cFieldDef& field_def ) const              { return ( GetReadRow().ReadWChar( field_def ) ); }
    short FASTCALL ReadShort( const cFieldDef& field_def ) const                { return ( GetReadRow().ReadShort( field_def ) ); }
    int FASTCALL ReadInteger( const cFieldDef& field_def ) const                { return ( GetReadRow().ReadInteger( field_def ) ); }
    long FASTCALL ReadLong( const cFieldDef& field_def ) const                  { return ( GetReadRow().ReadLong( field_def ) ); }
    double FASTCALL ReadFloat( const cFieldDef& field_def ) const               { return ( GetReadRow().ReadFloat( field_def ) ); }
    cDateTime FASTCALL ReadDate( const cFieldDef& field_def ) const             { return ( GetReadRow().ReadDate( field_def ) ); }
    ds_string FASTCALL ReadString( const cFieldDef& field_def ) const           { return ( GetReadRow().ReadString( field_def ) ); }

    void FASTCALL cDoubleBuffer::WriteBool( const cFieldDef& field_def, bool value )
    {
        GetUpdateRow().WriteBool( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteChar( const cFieldDef& field_def, char value )
    {
        GetUpdateRow().WriteChar( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteWChar( const cFieldDef& field_def, wchar_t value )
    {
        GetUpdateRow().WriteWChar( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteShort( const cFieldDef& field_def, short value )
    {
        GetUpdateRow().WriteShort( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteInteger( const cFieldDef& field_def, int value )
    {
        GetUpdateRow().WriteInteger( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteLong( const cFieldDef& field_def, long value )
    {
        GetUpdateRow().WriteLong( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteFloat( const cFieldDef& field_def, double value )
    {
        GetUpdateRow().WriteFloat( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteDate( const cFieldDef& field_def, const cDateTime& value )
    {
        GetUpdateRow().WriteDate( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteString(const cFieldDef& field_def, const ds_string& value )
    {
        GetUpdateRow().WriteString( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteString( const cFieldDef& field_def, const char *value )
    {
        GetUpdateRow().WriteString( field_def, value );
        UpdateRecordStatus();
    }

    bool FASTCALL ReadBool( const cFieldDef_& field_def ) const                  { return ( GetReadRow().ReadBool( field_def ) ); }
    char FASTCALL ReadChar( const cFieldDef_& field_def ) const                  { return ( GetReadRow().ReadChar( field_def ) ); }
    wchar_t FASTCALL ReadWChar( const cFieldDef_& field_def ) const              { return ( GetReadRow().ReadWChar( field_def ) ); }
    short FASTCALL ReadShort( const cFieldDef_& field_def ) const                { return ( GetReadRow().ReadShort( field_def ) ); }
    int FASTCALL ReadInteger( const cFieldDef_& field_def ) const                { return ( GetReadRow().ReadInteger( field_def ) ); }
    long FASTCALL ReadLong( const cFieldDef_& field_def ) const                  { return ( GetReadRow().ReadLong( field_def ) ); }
    double FASTCALL ReadFloat( const cFieldDef_& field_def ) const               { return ( GetReadRow().ReadFloat( field_def ) ); }
    cDateTime FASTCALL ReadDate( const cFieldDef_& field_def ) const             { return ( GetReadRow().ReadDate( field_def ) ); }
    ds_string FASTCALL ReadString( const cFieldDef_& field_def ) const           { return ( GetReadRow().ReadString( field_def ) ); }

    void FASTCALL cDoubleBuffer::WriteBool( const cFieldDef_& field_def, bool value )
    {
        GetUpdateRow().WriteBool( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteChar( const cFieldDef_& field_def, char value )
    {
        GetUpdateRow().WriteChar( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteWChar( const cFieldDef_& field_def, wchar_t value )
    {
        GetUpdateRow().WriteWChar( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteShort( const cFieldDef_& field_def, short value )
    {
        GetUpdateRow().WriteShort( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteInteger( const cFieldDef_& field_def, int value )
    {
        GetUpdateRow().WriteInteger( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteLong( const cFieldDef_& field_def, long value )
    {
        GetUpdateRow().WriteLong( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteFloat( const cFieldDef_& field_def, double value )
    {
        GetUpdateRow().WriteFloat( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteDate( const cFieldDef_& field_def, const cDateTime& value )
    {
        GetUpdateRow().WriteDate( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteString(const cFieldDef_& field_def, const ds_string& value )
    {
        GetUpdateRow().WriteString( field_def, value );
        UpdateRecordStatus();
    }
    void FASTCALL cDoubleBuffer::WriteString( const cFieldDef_& field_def, const char *value )
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
class IDataNotify;
class Data;
typedef shared_ptr<Data>    spData;

class Data
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
{
private:
    typedef shared_ptr< cDoubleBuffer >     cDoubleBuffer_ptr;
    typedef cDoubleBuffer_ptr               cData_value_type;
public:
    typedef std::vector< cDoubleBuffer_ptr >                    container;
    typedef container::value_type                               value_type;
    typedef container::size_type                                size_type;
    typedef container::iterator                                 iterator;
    typedef std::pair<bool,size_type>                           locate_result;
    typedef std::pair<bool,std::pair<size_type,size_type> >     range_result;
private:
    container           mData;
    cFieldDefs_ptr      mFieldDefs;
    Data                *mRelatedData;      // related "Data ring". Sorted or part of this data
    IDataNotify         *mTableNotify;

    container& FASTCALL GetContainer()                              { return ( mData ); }
    void FASTCALL Find_0( const Data::value_type& double_buffer, spSortCompare& compare,
                          iterator begin, iterator end, locate_result& result );
    void FASTCALL Find( const OpenValues& values, spSortCompare& compare,
                        iterator begin, iterator end, locate_result& result );
    void FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields,
                          iterator begin, iterator end, locate_result& result );
    // relation managment
    void FASTCALL NotifyRecordAdded( const value_type& value );
    void FASTCALL NotifyRecordDeleted();

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
    // noncopyable
    CDFASTCALL Data( const Data& src );
    Data& FASTCALL operator=( const Data& src );
public:
    CDFASTCALL Data( IDataNotify *i_notify );
    CDFASTCALL Data( const cFieldDefs_& field_defs, IDataNotify *i_notify );
    CDFASTCALL Data( const cFieldDefs_ptr& field_defs, IDataNotify *i_notify );
    CDFASTCALL ~Data();

    // IDataNotify * FASTCALL GetTableNotify()                         { return mTableNotify; }
    // void FASTCALL SetTableNotify( IDataNotify *i_notify )           { mTableNotify = IDataNotify; }

    int FASTCALL AddBuffer_ptr( const value_type& value );

    value_type FASTCALL NewBuffer_usUnmodified();
    value_type FASTCALL NewBuffer_usInserted();

    bool FASTCALL is_empty() const                                  { return mData.empty(); }
    size_type FASTCALL size() const                                 { return mData.size(); }
    const value_type& FASTCALL operator[]( size_type idx ) const    { return mData[idx]; }

    spData FASTCALL Clone_All( IDataNotify *i_notify );
    void FASTCALL Sort( const SortControler& cmp );

    void FASTCALL Clear();
    void FASTCALL CommitUpdates();

    void FASTCALL AddField( const ds_string& name, cFieldKind kind, cFieldDataType data_type, unsigned short size );

    const cFieldDefs_ptr& FASTCALL GetFieldDefs() const             { return mFieldDefs; }
    const cFieldDef& FieldByName( const ds_string& field_name )     { return mFieldDefs->FieldByName( field_name ); }
    const cFieldDef& FieldByName( const char *field_name )          { return mFieldDefs->FieldByName( field_name ); }

    void FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields, locate_result& result );
    void FASTCALL Locate( const OpenValues& values, const OpenFindFields& fields, size_type start, size_type end, locate_result& result );
    void FASTCALL Find( const OpenValues& values, spSortCompare& compare, locate_result& result );
    void FASTCALL Find( const OpenValues& values, spSortCompare& compare, size_type start, size_type end, locate_result& result );
    void FASTCALL GetRange( const OpenRangeValues& values, spSortCompare& compare, range_result& result );
};

//***********************************************************************
//******    IDataNotify
//***********************************************************************
class IDataNotify
{
public:
    virtual void FASTCALL RecordAdded( const Data::value_type& value ) = 0;
    virtual void FASTCALL RecordDeleted() = 0;
    virtual CDFASTCALL ~IDataNotify()               {} // empty
};

//---------------------------------------------------------------------------

}; // namespace detail

}; // namespace smds
//---------------------------------------------------------------------------
#endif

