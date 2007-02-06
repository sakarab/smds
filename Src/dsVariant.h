//---------------------------------------------------------------------------
#ifndef SM_DS_VARIANT_H
#define SM_DS_VARIANT_H
//---------------------------------------------------------------------------

#include "dsConfig.h"
#include <dsTypes.h>
#include "dsDateTime.h"
#include <vector>
#include "dsStream.h"

namespace ds
{

enum cVariantType   { vtNull, vtBool, vtChar, vtWChar, vtShort, vtInteger, vtLong, vtDouble, vtDateTime, vtString, vtWString, vtBlob };
typedef std::vector<char>   var_blob_type;

namespace detail
{

//***********************************************************************
//******    varTag
//***********************************************************************
union varTag
{
    // NullType        mNull;
    bool            mBool;
    char            mChar;
    unsigned char   mUChar;
    wchar_t         mWChar;
    short           mShort;
    unsigned short  mUShort;
    int             mInt;
    unsigned int    mUInt;
    long            mLong;
    unsigned long   mULong;
    double          mDouble;
    char            mDateTime[sizeof(cDateTime)];
    char            mString[sizeof(ds_string)];
    char            mWString[sizeof(ds_wstring)];
    char            mBlob[sizeof(var_blob_type)];
    CDFASTCALL varTag()                            /* : mNull() */        {}
    CDFASTCALL varTag( bool value )                : mBool(value)       {}
    CDFASTCALL varTag( char value )                : mChar(value)       {}
    CDFASTCALL varTag( unsigned char value )       : mUChar(value)      {}
    CDFASTCALL varTag( wchar_t value )             : mWChar(value)      {}
    CDFASTCALL varTag( short value )               : mShort(value)      {}
    CDFASTCALL varTag( unsigned short value )      : mUShort(value)     {}
    CDFASTCALL varTag( int value )                 : mInt(value)        {}
    CDFASTCALL varTag( unsigned int value )        : mUInt(value)       {}
    CDFASTCALL varTag( long value )                : mLong(value)       {}
    CDFASTCALL varTag( unsigned long value )       : mULong(value)      {}
    CDFASTCALL varTag( double value )              : mDouble(value)     {}
    CDFASTCALL varTag( const cDateTime& value )                         { ConstructDateTime( value ); }
    CDFASTCALL varTag( const ds_string& value )                         { ConstructString( value ); }
    CDFASTCALL varTag( const ds_wstring& value )                        { ConstructWString( value ); }

    void FASTCALL ConstructDateTime( const cDateTime& value )           { new(&mDateTime[0])cDateTime(value); }
    void FASTCALL ConstructString( const ds_string& value )             { new(&mString[0])ds_string(value); }
    void FASTCALL ConstructWString( const ds_wstring& value )           { new(&mWString[0])ds_wstring(value); }
    void FASTCALL ConstructBlob( const std::vector<char>& value )       { new(&mBlob[0])var_blob_type(value); }

    void FASTCALL DestructDateTime()                    { (reinterpret_cast<cDateTime *>(&mDateTime[0]))->~cDateTime(); }
    void FASTCALL DestructString()                      { (reinterpret_cast<ds_string *>(&mString[0]))->~ds_string(); }
    void FASTCALL DestructWString()                     { (reinterpret_cast<ds_wstring *>(&mWString[0]))->~ds_wstring(); }
    void FASTCALL DestructBlob()                        { (reinterpret_cast<var_blob_type *>(&mBlob[0]))->~var_blob_type(); }

    const cDateTime& FASTCALL GetDateTime() const       { return ( *reinterpret_cast<const cDateTime *>(&mDateTime[0]) ); }
    const ds_string& FASTCALL GetString() const         { return ( *reinterpret_cast<const ds_string *>(&mString[0]) ); }
    const ds_wstring& FASTCALL GetWString() const       { return ( *reinterpret_cast<const ds_wstring *>(&mWString[0]) ); }
    const std::vector<char>& FASTCALL GetBlob() const   { return ( *reinterpret_cast<const var_blob_type *>(&mBlob[0]) ); }
    std::vector<char>& FASTCALL GetBlob()               { return ( *reinterpret_cast<var_blob_type *>(mBlob) ); }
};

}; // namespace detail

//***********************************************************************
//******    Variant
//***********************************************************************
class Variant
{
private:
    friend class cVariantStreamBuffer;

    cVariantType    mVariantType;
    detail::varTag  mData;
    void FASTCALL ConstructByType( const Variant& src );             // the source type
    void FASTCALL DestructByType();                                  // "this" type
    long FASTCALL ToLongType() const;
    long FASTCALL StringToLong( const ds_string& sstr ) const;
    // long FASTCALL StringToLong( const ds_wstring& sstr ) const;
    double FASTCALL StringToDouble( const ds_string& sstr ) const;
    // double FASTCALL StringToDouble( const ds_wstring& sstr ) const;
    ds_wstring StringToWString( const ds_string& sstr ) const;
    ds_string WStringToString( const ds_wstring& sstr ) const;
    CDFASTCALL Variant( void *dummy );          // ambiguity baster
    CDFASTCALL Variant( const void *dummy );    // ambiguity baster
public:
    CDFASTCALL Variant()                            : mVariantType(vtNull), mData()                             {} // empty
    CDFASTCALL Variant( bool value )                : mVariantType(vtBool), mData(value)                        {} // empty
    CDFASTCALL Variant( char value )                : mVariantType(vtChar), mData(value)                        {} // empty
    CDFASTCALL Variant( unsigned char value )       : mVariantType(vtChar), mData(static_cast<char>(value))     {} // empty
    CDFASTCALL Variant( wchar_t value )             : mVariantType(vtWChar), mData(value)                       {} // empty
    CDFASTCALL Variant( short value )               : mVariantType(vtShort), mData(value)                       {} // empty
    CDFASTCALL Variant( unsigned short value )      : mVariantType(vtShort), mData(static_cast<short>(value))   {} // empty
    CDFASTCALL Variant( int value )                 : mVariantType(vtInteger), mData(value)                     {} // empty
    CDFASTCALL Variant( unsigned int value )        : mVariantType(vtInteger), mData(static_cast<int>(value))   {} // empty
    CDFASTCALL Variant( long value )                : mVariantType(vtLong), mData(value)                        {} // empty
    CDFASTCALL Variant( unsigned long value )       : mVariantType(vtLong), mData(static_cast<long>(value))     {} // empty
    CDFASTCALL Variant( double value )              : mVariantType(vtDouble), mData(value)                      {} // empty
    CDFASTCALL Variant( const cDateTime& value );
    CDFASTCALL Variant( const ds_string& value );
    CDFASTCALL Variant( const ds_wstring& value );

    CDFASTCALL Variant( const Variant& src );
    CDFASTCALL ~Variant();
    Variant& FASTCALL operator = ( const Variant& src );

    bool FASTCALL IsNull() const                    { return ( mVariantType == vtNull ); }
    cVariantType VarType() const                    { return ( mVariantType ); }

    bool FASTCALL Variant::AsBool() const           { return ( ToLongType() != 0 ); }
    char FASTCALL Variant::AsChar() const           { return ( static_cast<char>(ToLongType()) ); }
    wchar_t FASTCALL Variant::AsWChar() const       { return ( static_cast<wchar_t>(ToLongType()) ); }
    short FASTCALL Variant::AsShort() const         { return ( static_cast<short>(ToLongType()) ); }
    int FASTCALL Variant::AsInt() const             { return ( static_cast<int>(ToLongType()) ); }
    long FASTCALL Variant::AsLong() const           { return ( ToLongType() ); }
    double FASTCALL AsDouble() const;
    cDateTime FASTCALL AsDateTime() const;
    ds_string FASTCALL AsString() const;
    ds_string FASTCALL AsWString() const;

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
