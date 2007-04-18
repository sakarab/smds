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
#ifndef __GNUG__
#pragma hdrstop
#endif

#include "dsUtils.h"
//---------------------------------------------------------------------------
namespace smds
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

