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
#ifndef SM_DS_VARIANT_H
#define SM_DS_VARIANT_H
//---------------------------------------------------------------------------

#include "dsConfig.h"
#include "dsTypes.h"
#include "dsDateTime.h"
#include "dsGUID.h"
#include <vector>
#include "dsStream.h"

namespace smds
{

enum VariantTypeID
{
    vtNull, vtBool, vtByte, vtShort, vtInteger, vtLong,
    vtLongLong, vtDouble, vtDate, vtTime, vtDateTime, vtGUID, vtString, vtWString, vtBlob
};

typedef std::vector<char>   var_blob_type;

namespace detail
{

//***********************************************************************
//******    varTag
//***********************************************************************
union varTag
{
    // NullType        mNull;
    bool                mBool;
    char                mByte;
    short               mShort;
    int                 mInt;
    long                mLong;
    long long           mLongLong;
    double              mDouble;
    dbDate              mDate;
    dbTime              mTime;
    dbDateTime          mDateTime;
    dbGUID              mGUID;
    char                mString[sizeof(ds_string)];
    char                mWString[sizeof(ds_wstring)];
    char                mBlob[sizeof(var_blob_type)];
    CDFASTCALL varTag()                            /* : mNull() */        {}
    CDFASTCALL varTag( bool value )                : mBool(value)       {}
    CDFASTCALL varTag( char value )                : mByte(value)       {}
    CDFASTCALL varTag( unsigned char value )       : mByte(value)       {}
    CDFASTCALL varTag( short value )               : mShort(value)      {}
    CDFASTCALL varTag( unsigned short value )      : mShort(value)      {}
    CDFASTCALL varTag( int value )                 : mInt(value)        {}
    CDFASTCALL varTag( unsigned int value )        : mInt(value)        {}
    CDFASTCALL varTag( long value )                : mLong(value)       {}
    CDFASTCALL varTag( unsigned long value )       : mLong(value)       {}
    CDFASTCALL varTag( long long value )           : mLongLong(value)   {}
    CDFASTCALL varTag( unsigned long long value )  : mLongLong(value)   {}
    CDFASTCALL varTag( double value )              : mDouble(value)     {}
    CDFASTCALL varTag( const dbDate& value )       : mDate(value)       {}
    CDFASTCALL varTag( const dbTime& value )       : mTime(value)       {}
    CDFASTCALL varTag( const dbDateTime& value )   : mDateTime(value)   {}
    CDFASTCALL varTag( const dbGUID& value )       : mGUID(value)       {}

    CDFASTCALL varTag( const ds_string& value )                         { ConstructString( value ); }
    CDFASTCALL varTag( const ds_wstring& value )                        { ConstructWString( value ); }
    CDFASTCALL varTag( const var_blob_type& value )                     { ConstructBlob( value ); }

    void FASTCALL ConstructString( const ds_string& value )             { new(&mString[0])ds_string(value); }
    void FASTCALL ConstructWString( const ds_wstring& value )           { new(&mWString[0])ds_wstring(value); }
    void FASTCALL ConstructBlob( const std::vector<char>& value )       { new(&mBlob[0])var_blob_type(value); }

    void FASTCALL DestructString()                      { (reinterpret_cast<ds_string *>(&mString[0]))->~ds_string(); }
    void FASTCALL DestructWString()                     { (reinterpret_cast<ds_wstring *>(&mWString[0]))->~ds_wstring(); }
    void FASTCALL DestructBlob()                        { (reinterpret_cast<var_blob_type *>(&mBlob[0]))->~var_blob_type(); }

    const ds_string& FASTCALL GetString() const         { return ( *reinterpret_cast<const ds_string *>(&mString[0]) ); }
    const ds_wstring& FASTCALL GetWString() const       { return ( *reinterpret_cast<const ds_wstring *>(&mWString[0]) ); }
    const std::vector<char>& FASTCALL GetBlob() const   { return ( *reinterpret_cast<const var_blob_type *>(&mBlob[0]) ); }
    std::vector<char>& FASTCALL GetBlob()               { return ( *reinterpret_cast<var_blob_type *>(mBlob) ); }   // sam. reconsider
};

} // namespace detail

//***********************************************************************
//******    Variant
//***********************************************************************
class Variant
{
private:
    friend class cVariantStreamBuffer;

    VariantTypeID       mVariantType;
    detail::varTag      mData;
    void FASTCALL ConstructByType( const Variant& src );             // the source type
    void FASTCALL DestructByType();                                  // "this" type
    long FASTCALL ToLongType() const;
    long long FASTCALL ToLongLongType() const;
    long FASTCALL StringToLong( const ds_string& sstr ) const;
    // long FASTCALL StringToLong( const ds_wstring& sstr ) const;
    double FASTCALL StringToDouble( const ds_string& sstr ) const;
    // double FASTCALL StringToDouble( const ds_wstring& sstr ) const;
    // ds_wstring StringToWString( const ds_string& sstr ) const;
    // ds_string WStringToString( const ds_wstring& sstr ) const;
    CDFASTCALL Variant( void *dummy );          // ambiguity baster
    CDFASTCALL Variant( const void *dummy );    // ambiguity baster
public:
    CDFASTCALL Variant()                            : mVariantType(vtNull), mData()                             {} // empty
    CDFASTCALL Variant( bool value )                : mVariantType(vtBool), mData(value)                        {} // empty
    CDFASTCALL Variant( char value )                : mVariantType(vtByte), mData(value)                        {} // empty
    CDFASTCALL Variant( unsigned char value )       : mVariantType(vtByte), mData(value)                        {} // empty
    CDFASTCALL Variant( short value )               : mVariantType(vtShort), mData(value)                       {} // empty
    CDFASTCALL Variant( unsigned short value )      : mVariantType(vtShort), mData(value)                       {} // empty
    CDFASTCALL Variant( int value )                 : mVariantType(vtInteger), mData(value)                     {} // empty
    CDFASTCALL Variant( unsigned int value )        : mVariantType(vtInteger), mData(value)                     {} // empty
    CDFASTCALL Variant( long value )                : mVariantType(vtLong), mData(value)                        {} // empty
    CDFASTCALL Variant( unsigned long value )       : mVariantType(vtLong), mData(value)                        {} // empty
    CDFASTCALL Variant( long long value )           : mVariantType(vtLongLong), mData(value)                    {} // empty
    CDFASTCALL Variant( unsigned long long value )  : mVariantType(vtLongLong), mData(value)                    {} // empty
    CDFASTCALL Variant( double value )              : mVariantType(vtDouble), mData(value)                      {} // empty
    CDFASTCALL Variant( const dbDate& value );
    CDFASTCALL Variant( const dbTime& value );
    CDFASTCALL Variant( const dbDateTime& value );
    CDFASTCALL Variant( const dbGUID& value );
    CDFASTCALL Variant( const char *value );
    CDFASTCALL Variant( const ds_string& value );
    CDFASTCALL Variant( const wchar_t *value );
    CDFASTCALL Variant( const ds_wstring& value );
    CDFASTCALL Variant( const var_blob_type& value );

    CDFASTCALL Variant( const Variant& src );
    CDFASTCALL ~Variant();
    Variant& FASTCALL operator = ( const Variant& src );

    bool FASTCALL IsNull() const                        { return ( mVariantType == vtNull ); }
    VariantTypeID VarType() const                       { return mVariantType; }

    bool FASTCALL AsBool() const                        { return ( ToLongType() != 0 ); }
    char FASTCALL AsByte() const                        { return static_cast<char>(ToLongType()); }
    short FASTCALL AsShort() const                      { return static_cast<short>(ToLongType()); }
    int FASTCALL AsInt() const                          { return static_cast<int>(ToLongType()); }
    long FASTCALL AsLong() const                        { return ToLongType(); }
    long long FASTCALL AsLongLong() const               { return ToLongLongType(); }
    double FASTCALL AsDouble() const;
    dbDate FASTCALL AsDate() const;
    dbTime FASTCALL AsTime() const;
    dbDateTime FASTCALL AsDateTime() const;
    dbGUID FASTCALL AsGUID() const;
    ds_string FASTCALL AsString() const;
    // ds_string FASTCALL AsWString() const;

    static Variant FASTCALL VarBlobCreate();
};

//***********************************************************************
//******    cVariantStreamBuffer
//***********************************************************************
class cVariantStreamBuffer : public cAttachedStreamBuffer
{
public:
    CDFASTCALL cVariantStreamBuffer( Variant& variant );
    CDFASTCALL ~cVariantStreamBuffer();
};

//***********************************************************************
//******    cVariantStream
//***********************************************************************
class cVariantStream : public cStream
{
public:
	CDFASTCALL cVariantStream( Variant& variant );
	CDFASTCALL ~cVariantStream();
};

};
//---------------------------------------------------------------------------
#endif
