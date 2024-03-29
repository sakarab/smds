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
#if ! defined (SM_DS_UTILS_H)
#define SM_DS_UTILS_H

#include "dsConfig.h"
#include "dsTypes.h"
#include "dsSysOpen.h"
#include "dsVariant.h"
#include <cpp_string.h>

//#if ! defined (ARRAY_COUNT)
//    #define ARRAY_COUNT(a)      (sizeof(a)/sizeof(a[0]))
//#endif

namespace smds
{

//***********************************************************************
//******    cFindField
//***********************************************************************
class cFindField
{
public:
    enum CaseOption { CaseSensitive, CaseInsensitive };
private:
    std_string      mFieldName;
    CaseOption      mCaseOption;
public:
    CDFASTCALL cFindField( const std_string& field_name );
    CDFASTCALL cFindField( const std_string& field_name, CaseOption case_option );
    CDFASTCALL cFindField( const std_char *field_name );
    CDFASTCALL cFindField( const std_char *field_name, CaseOption case_option );

    const std_string& GetFieldName() const              { return ( mFieldName ); }
    CaseOption GetCaseOption() const                    { return ( mCaseOption ); }
};

//***********************************************************************
//******    cIndexField
//***********************************************************************
class cIndexField : public cFindField
{
public:
    enum OrderOptions { Ascending, Descending };
private:
    OrderOptions    mOrderOptions;
public:
    CDFASTCALL cIndexField( const std_string& field_name )
        : cFindField( field_name ), mOrderOptions(Ascending)                        {}  // empty
    CDFASTCALL cIndexField( const std_string& field_name, CaseOption case_option )
        : cFindField( field_name, case_option ), mOrderOptions(Ascending)           {}  // empty
    CDFASTCALL cIndexField( const std_string& field_name, OrderOptions order_options )
        : cFindField( field_name ), mOrderOptions(order_options)                    {}  // empty
    CDFASTCALL cIndexField( const std_string& field_name, OrderOptions order_options, CaseOption case_option )
        : cFindField( field_name, case_option ), mOrderOptions(order_options)       {}  // empty
    CDFASTCALL cIndexField( const std_char *field_name )
        : cFindField( field_name ), mOrderOptions(Ascending)                        {}  // empty
    CDFASTCALL cIndexField( const std_char *field_name, CaseOption case_option )
        : cFindField( field_name, case_option ), mOrderOptions(Ascending)           {}  // empty
    CDFASTCALL cIndexField( const std_char *field_name, OrderOptions order_options )
        : cFindField( field_name ), mOrderOptions(order_options)                    {}  // empty
    CDFASTCALL cIndexField( const std_char *field_name, OrderOptions order_options, CaseOption case_option )
        : cFindField( field_name, case_option ), mOrderOptions(order_options)       {}  // empty

    OrderOptions GetOrderOptions() const                { return ( mOrderOptions ); }
};

//***********************************************************************
//******    cRangeValues
//***********************************************************************
class cRangeValues
{
private:
    detail::OpenArray<Variant>      mDoubleValues;
    // non copyable
#ifdef __GNUG__
public:
#endif
    CDFASTCALL cRangeValues( const cRangeValues& src );
    cRangeValues& FASTCALL operator=( const cRangeValues& src );
#ifdef __GNUG__
private:
#endif
public:
    CDFASTCALL cRangeValues( const Variant& start_value, const Variant& end_value );

    const Variant& First() const            { return ( *(mDoubleValues.GetArray()[0]) ); }
    const Variant& Second() const           { return ( *(mDoubleValues.GetArray()[1]) ); }
};

typedef detail::OpenArray<cFindField>       OpenFindFields;
typedef detail::OpenArray<cIndexField>      OpenIndexFields;
typedef detail::OpenArray<Variant>          OpenValues;
typedef detail::OpenArray<cRangeValues>     OpenRangeValues;

} // namespace smds

#endif
