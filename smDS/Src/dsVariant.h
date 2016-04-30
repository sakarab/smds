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
#include <boost/variant.hpp>

namespace smds
{

enum VariantTypeID
{
    vtNull, vtBool, vtByte, vtShort, vtInteger, vtLong,
    vtLongLong, vtDouble, vtDate, vtTime, vtDateTime, vtGUID, vtString, vtWString, vtBlob
};

typedef std::vector<char>   var_blob_type;

//***********************************************************************
//******    Variant
//***********************************************************************
class Variant
{
private:
    typedef boost::variant<bool, char, short, int, long, long long, double,
                           unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long,
                           dbDate, dbTime, dbDateTime, dbGUID, ds_string, ds_wstring, var_blob_type>   VariantType;
private:
    friend class cVariantStreamBuffer;

    VariantTypeID       mVariantType;
    VariantType         mData;
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
