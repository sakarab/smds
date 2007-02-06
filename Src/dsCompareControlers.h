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
