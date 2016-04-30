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
#include "dsExceptions.h"

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

    template <class TYPE, VariantTypeID TYPEID> TYPE strict_get() const
    {
        if ( TYPEID != mVariantType )
            throw eVariantConversion();
        return boost::get<TYPE>( mData );
    }

    Variant( void *dummy );          // ambiguity baster
    Variant( const void *dummy );    // ambiguity baster
public:
    Variant()                            : mVariantType(vtNull), mData()                             {} // empty
    Variant( bool value )                : mVariantType(vtBool), mData(value)                        {} // empty
    Variant( char value )                : mVariantType(vtByte), mData(value)                        {} // empty
    Variant( unsigned char value )       : mVariantType(vtByte), mData(value)                        {} // empty
    Variant( short value )               : mVariantType(vtShort), mData(value)                       {} // empty
    Variant( unsigned short value )      : mVariantType(vtShort), mData(value)                       {} // empty
    Variant( int value )                 : mVariantType(vtInteger), mData(value)                     {} // empty
    Variant( unsigned int value )        : mVariantType(vtInteger), mData(value)                     {} // empty
    Variant( long value )                : mVariantType(vtLong), mData(value)                        {} // empty
    Variant( unsigned long value )       : mVariantType(vtLong), mData(value)                        {} // empty
    Variant( long long value )           : mVariantType(vtLongLong), mData(value)                    {} // empty
    Variant( unsigned long long value )  : mVariantType(vtLongLong), mData(value)                    {} // empty
    Variant( double value )              : mVariantType(vtDouble), mData(value)                      {} // empty
    Variant( const dbDate& value );
    Variant( const dbTime& value );
    Variant( const dbDateTime& value );
    Variant( const dbGUID& value );
    Variant( const char *value );
    Variant( const ds_string& value );
    Variant( const wchar_t *value );
    Variant( const ds_wstring& value );
    Variant( const var_blob_type& value );

    Variant( const Variant& src );
    ~Variant();
    Variant& operator = ( const Variant& src );

    bool IsNull() const                        { return ( mVariantType == vtNull ); }
    VariantTypeID VarType() const              { return mVariantType; }

    bool AsBool() const;
    char AsByte() const;
    short AsShort() const;
    int AsInt() const;
    long AsLong() const;
    long long AsLongLong() const;
    double AsDouble() const;
    dbDate AsDate() const;
    dbTime AsTime() const;
    dbDateTime AsDateTime() const;
    dbGUID AsGUID() const;
    ds_string AsString() const;
    // ds_string WString() const;

    static Variant VarBlobCreate();
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
