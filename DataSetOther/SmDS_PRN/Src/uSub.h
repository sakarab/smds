//---------------------------------------------------------------------------
#ifndef PRN_SUB_H
#define PRN_SUB_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include <ssport.h>
#include "dsDateTime.h"
#include "dsTypes.h"
#include "dsVariant.h"
#include "dsSysOpen.h"
#include <dsExceptions.h>
//---------------------------------------------------------------------------
class PDNException : public ds::eExceptionBase
{
public:
    CDFASTCALL PDNException() : ds::eExceptionBase()                                              {} // empty
    CDFASTCALL PDNException( const char *message ) : ds::eExceptionBase(message)                  {} // empty
    CDFASTCALL PDNException( const ds_string& message ) : ds::eExceptionBase(message)             {} // empty
};

class PDNCycle : public PDNException
{
public:
    CDFASTCALL PDNCycle() : PDNException()                                              {} // empty
    CDFASTCALL PDNCycle( const char *message ) : PDNException(message)                  {} // empty
    CDFASTCALL PDNCycle( const ds_string& message ) : PDNException(message)             {} // empty
};

ds::cDateTime FASTCALL DayOfWeek( const ds::cDateTime& date_time );     // external
int FASTCALL WeekOfYear( const ds::cDateTime& date_time );              // external

const int iDefPDNCALID = -1;
const int INVALIDID = 0;

int FASTCALL GetParameter_integer( const char *name );
ds_string FASTCALL GetParameter_string( const char *name );
bool FASTCALL IsProcuctionLight();
ds_string FASTCALL AddToWhereClause( const ds_string& aWhereClause, const ds_string& aExpr );
ds_string FASTCALL SQLFormatDateTime( const ds::cDateTime& date );
ds_string FASTCALL PDNFormatInSQL( const ds_string& aFormat, const std::vector<int> ids, const ds_string& aConjet );

struct TItem
{
    int         MCIID;
    ds_string   DFVCODE1, DFVCODE2, DFVCODE3;
    ds_string   DFVCODE4, DFVCODE5, DFVCODE6, DFVCODE7;
    CDFASTCALL TItem( int mciid, const ds_string& dfvcode1, const ds_string& dfvcode2, const ds_string& dfvcode3,
                      const ds_string& dfvcode4, const ds_string& dfvcode5, const ds_string& dfvcode6, const ds_string& dfvcode7 );
};

//***********************************************************************
//******    WhereAtom
//***********************************************************************
class WhereAtom
{
private:
    ds_string       mFieldName;
    ds_string       mOperStr;
    ds::Variant     mValue;
public:
    CDFASTCALL WhereAtom( const ds_string& field_name, const ds_string& oper_str, const ds::Variant& value );
    CDFASTCALL WhereAtom( const char *field_name, const ds_string& oper_str, const ds::Variant& value );
    CDFASTCALL WhereAtom( const ds_string& field_name, const char *oper_str, const ds::Variant& value );
    CDFASTCALL WhereAtom( const char *field_name, const char *oper_str, const ds::Variant& value );
    const ds_string& FASTCALL FieldName() const           { return ( mFieldName ); }
    const ds_string& FASTCALL OperStr() const             { return ( mOperStr ); }
    const ds::Variant& FASTCALL Value() const             { return ( mValue ); }
};

typedef ds::detail::OpenArray<WhereAtom>    OpenWhereExpression;

ds_string FASTCALL BuildWhereClause( const WhereAtom& atom );
ds_string FASTCALL BuildWhereClause( const OpenWhereExpression& expression );

//---------------------------------------------------------------------------
#endif
