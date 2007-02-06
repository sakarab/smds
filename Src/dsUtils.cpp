//---------------------------------------------------------------------------
#pragma hdrstop

#include "dsUtils.h"
//---------------------------------------------------------------------------
namespace ds
{
//***********************************************************************
//******    cFindField
//***********************************************************************
CDFASTCALL cFindField::cFindField( const ds_string& field_name )
    : mFieldName(field_name), mCaseOption(CaseSensitive)
{
}

CDFASTCALL cFindField::cFindField( const ds_string& field_name, CaseOption case_option )
    : mFieldName(field_name), mCaseOption(case_option)
{
}

CDFASTCALL cFindField::cFindField( const char *field_name )
    : mFieldName(field_name), mCaseOption(CaseSensitive)
{
}

CDFASTCALL cFindField::cFindField( const char *field_name, CaseOption case_option )
    : mFieldName(field_name), mCaseOption(case_option)
{
}

//***********************************************************************
//******    cIndexField
//***********************************************************************

//***********************************************************************
//******    cRangeValues
//***********************************************************************
CDFASTCALL cRangeValues::cRangeValues( const Variant& start_value, const Variant& end_value )
    : mDoubleValues( start_value, end_value )
{
}

////***********************************************************************
////******    cLocateParam
////***********************************************************************
//CDFASTCALL cLocateParam::cLocateParam( const Variant& value, const ds_string& field_name )
//    : mValue(value), mFieldName(field_name), mCaseOption(CaseSensitive)
//{
//}
//
//CDFASTCALL cLocateParam::cLocateParam( const Variant& value, const ds_string& field_name, CaseOption case_option )
//    : mValue(value), mFieldName(field_name), mCaseOption(case_option)
//{
//}
//
//CDFASTCALL cLocateParam::cLocateParam( const Variant& value, const char *field_name )
//    : mValue(value), mFieldName(field_name), mCaseOption(CaseSensitive)
//{
//}
//
//CDFASTCALL cLocateParam::cLocateParam( const Variant& value, const char *field_name, CaseOption case_option )
//    : mValue(value), mFieldName(field_name), mCaseOption(case_option)
//{
//}
//
////***********************************************************************
////******    cIndexParam
////***********************************************************************
//CDFASTCALL cIndexParam::cIndexParam( const ds_string& field_name )
//    : mFieldName(field_name), mCaseOption(CaseSensitive), mOrderOptions(Ascending)
//{
//}
//
//CDFASTCALL cIndexParam::cIndexParam( const ds_string& field_name, CaseOption case_option )
//    : mFieldName(field_name), mCaseOption(case_option), mOrderOptions(Ascending)
//{
//}
//
//CDFASTCALL cIndexParam::cIndexParam( const ds_string& field_name, OrderOptions order_options )
//    : mFieldName(field_name), mCaseOption(CaseSensitive), mOrderOptions(order_options)
//{
//}
//
//CDFASTCALL cIndexParam::cIndexParam( const ds_string& field_name, CaseOption case_option, OrderOptions order_options )
//    : mFieldName(field_name), mCaseOption(case_option), mOrderOptions(order_options)
//{
//}
//
//CDFASTCALL cIndexParam::cIndexParam( const char *field_name )
//    : mFieldName(field_name), mCaseOption(CaseSensitive), mOrderOptions(Ascending)
//{
//}
//
//CDFASTCALL cIndexParam::cIndexParam( const char *field_name, CaseOption case_option )
//    : mFieldName(field_name), mCaseOption(case_option), mOrderOptions(Ascending)
//{
//}
//
//CDFASTCALL cIndexParam::cIndexParam( const char *field_name, OrderOptions order_options )
//    : mFieldName(field_name), mCaseOption(CaseSensitive), mOrderOptions(order_options)
//{
//}
//
//CDFASTCALL cIndexParam::cIndexParam( const char *field_name, CaseOption case_option, OrderOptions order_options )
//    : mFieldName(field_name), mCaseOption(case_option), mOrderOptions(order_options)
//{
//}

};
//---------------------------------------------------------------------------

