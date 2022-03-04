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
#include "pre_smDS.h"
#include "dsUtils.h"
//---------------------------------------------------------------------------
namespace smds
{

//***********************************************************************
//******    cFindField
//***********************************************************************
CDFASTCALL cFindField::cFindField( const std_string& field_name )
    : mFieldName(field_name), mCaseOption(CaseSensitive)
{
}

CDFASTCALL cFindField::cFindField( const std_string& field_name, CaseOption case_option )
    : mFieldName(field_name), mCaseOption(case_option)
{
}

CDFASTCALL cFindField::cFindField( const std_char *field_name )
    : mFieldName(field_name), mCaseOption(CaseSensitive)
{
}

CDFASTCALL cFindField::cFindField( const std_char *field_name, CaseOption case_option )
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

}; // namespace smds
//---------------------------------------------------------------------------

