#include "uSub.h"
#include <sstream>

// utility functions

ds::cDateTime FASTCALL DayOfWeek( const ds::cDateTime& date_time )      // external
{
    return ( 0 );
}

int FASTCALL WeekOfYear( const ds::cDateTime& date_time )
{
    return ( 0 );
}

int FASTCALL GetParameter_integer( const char *name )
{
    return ( 0 );
}

ds_string FASTCALL GetParameter_string( const char *name )
{
    return ( 0 );
}

bool FASTCALL IsProcuctionLight()
{
    return ( false );
}

ds_string FASTCALL SQLFormatDateTime( const ds::cDateTime& date )
{
    return ( "" );
}

ds_string FASTCALL PDNFormatInSQL( const ds_string& aFormat, const std::vector<int> ids, const ds_string& aConjet )
{
    return ( "" );
}

ds_string FASTCALL AddToWhereClause( const ds_string& aWhereClause, const ds_string& aExpr )
{
    if ( aExpr.empty() )
        return ( aWhereClause );
    if ( aWhereClause.empty() )
        return ( ds_string( "(" ).append( aExpr ).append( ")" ) );
    else
        return ( ds_string( aWhereClause ).append( " AND (" ).append( aExpr ).append( ")" ) );
}

ds_string FASTCALL BuildWhereClauseOne( const ds_string& prefix, const WhereAtom& atom )
{
    std::ostringstream   ostr;

    switch ( atom.Value().VarType() )
    {
        case ds::vtNull :
            ostr << prefix.c_str() << atom.FieldName().c_str() << ' '
                 << (atom.OperStr().empty() ? "IS" : atom.OperStr().c_str()) << " NULL";
            break;
        case ds::vtShort :
            ostr << prefix.c_str() << atom.FieldName().c_str() << ' '
                 << (atom.OperStr().empty() ? "=" : atom.OperStr().c_str()) << atom.Value().AsShort();
            break;
        case ds::vtInteger :
            ostr << prefix.c_str() << atom.FieldName().c_str() << ' '
                 << (atom.OperStr().empty() ? "=" : atom.OperStr().c_str()) << atom.Value().AsInt();
            break;
        case ds::vtLong :
            ostr << prefix.c_str() << atom.FieldName().c_str() << ' '
                 << (atom.OperStr().empty() ? "=" : atom.OperStr().c_str()) << atom.Value().AsLong();
            break;
        case ds::vtDouble :
            ostr << prefix.c_str() << atom.FieldName().c_str() << ' '
                 << (atom.OperStr().empty() ? "=" : atom.OperStr().c_str()) << atom.Value().AsDouble();
            break;
        case ds::vtString :
            ostr << prefix.c_str() << atom.FieldName().c_str() << ' '
                 << (atom.OperStr().empty() ? "=" : atom.OperStr().c_str()) << atom.Value().AsString().c_str();
            break;
        default :
            throw PDNException( "Unsupported Variant type" );
    }
    return ( ostr.str().c_str() );
}

ds_string FASTCALL BuildWhereClause( const WhereAtom& atom )
{
    return ( BuildWhereClause( OpenWhereExpression( atom ) ) );
}

ds_string FASTCALL BuildWhereClause( const OpenWhereExpression& expression )
{
    ds_string   result;
    ds_string   prefix;

    for ( int n = 0 ; n < expression.GetCount() ; ++n )
    {
        result += BuildWhereClauseOne( prefix, *(expression.GetArray()[n]) );
        if ( prefix.empty() )
            prefix = "\r\nAND ";
    }

    return ( "" );
}

//***********************************************************************
//******    TItem
//***********************************************************************
CDFASTCALL TItem::TItem( int mciid, const ds_string& dfvcode1, const ds_string& dfvcode2, const ds_string& dfvcode3,
                         const ds_string& dfvcode4, const ds_string& dfvcode5, const ds_string& dfvcode6, const ds_string& dfvcode7 )
    : MCIID(mciid), DFVCODE1(dfvcode1), DFVCODE2(dfvcode2), DFVCODE3(dfvcode3), DFVCODE4(dfvcode4),
      DFVCODE5(dfvcode5), DFVCODE6(dfvcode6), DFVCODE7(dfvcode7) 
{
}
//***********************************************************************
//******    WhereAtom
//***********************************************************************
CDFASTCALL WhereAtom::WhereAtom( const ds_string& field_name, const ds_string& oper_str, const ds::Variant& value )
    : mFieldName(field_name), mOperStr(oper_str), mValue(value)
{
}

CDFASTCALL WhereAtom::WhereAtom( const char *field_name, const ds_string& oper_str, const ds::Variant& value )
    : mFieldName(field_name), mOperStr(oper_str), mValue(value)
{
}

CDFASTCALL WhereAtom::WhereAtom( const ds_string& field_name, const char *oper_str, const ds::Variant& value )
    : mFieldName(field_name), mOperStr(oper_str), mValue(value)
{
}

CDFASTCALL WhereAtom::WhereAtom( const char *field_name, const char *oper_str, const ds::Variant& value )
    : mFieldName(field_name), mOperStr(oper_str), mValue(value)
{
}
