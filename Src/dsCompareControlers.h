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

  Please read the "readme" file in the root directory of this
  package for more copyright and license information.
****************************************************************************/
//---------------------------------------------------------------------------
#ifndef SM_DS_COMPARE_CONTROLERS_H
#define SM_DS_COMPARE_CONTROLERS_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include <functional>
#include "dsBuffer.h"
#include "dsIndex.h"
//---------------------------------------------------------------------------
namespace ds
{

namespace detail
{

//***********************************************************************
//******    SortControler
//***********************************************************************
class SortControler : public std::binary_function<const cData::value_type&, const cData::value_type&, bool>
{
private:
    cSortCompareBase    *mCompare;
public:
    CDFASTCALL SortControler( cSortCompareBase_ptr& cmp_func )
        : mCompare(cmp_func.get())                                                          {} // empty
    result_type FASTCALL operator()( first_argument_type item1, second_argument_type item2 ) const
    {
        return ( mCompare->compare( item1->GetActiveData(), item2->GetActiveData() ) );
    };
};

//***********************************************************************
//******    FindControler
//***********************************************************************
class FindControler : public std::unary_function<const cData::value_type&, bool>
{
private:
    cSortCompareBase    *mCompare;
    cRawBuffer          *mItem2;
public:
    CDFASTCALL FindControler( cSortCompareBase_ptr& cmp_func, cRawBuffer& item2 )
        : mCompare(cmp_func.get()), mItem2(&item2)                                          {} // empty
    result_type FASTCALL operator()( argument_type item ) const
    {
        return ( mCompare->compare( item->GetActiveData(), *mItem2 ) );
    };
};

////***********************************************************************
////******    FilterControler
////***********************************************************************
class FilterControler : public std::unary_function<const cData::value_type&, bool>
{
private:
    cFilterCompareBase      *mCompare;
public:
    CDFASTCALL FilterControler( cFilterCompareBase_ptr& cmp_func )
        : mCompare(cmp_func.get())
    {
    }
    result_type FASTCALL operator()( argument_type item ) const
    {
        return ( mCompare->compare( item->GetActiveData() ) );
    };
};

}; // detail

}; // ds

//---------------------------------------------------------------------------
#endif
