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

#include "dsIndex.h"
#include "dsExceptions.h"
#include "dsCompareControlers.h"
#include <set>
//---------------------------------------------------------------------------
namespace smds
{
//---------------------------------------------------------------------------
//***********************************************************************
//******    cSortCompareBase
//***********************************************************************
CDFASTCALL cSortCompareBase::~cSortCompareBase()
{
}

void FASTCALL cSortCompareBase::Initialize( const cFieldDefs_ptr& field_defs )
{
#if defined SM_DS_DEBUG
    CompareInvocationCount = 0;
#endif
    mFieldDefs = field_defs.get();
}

#if defined SM_DS_DEBUG
int cSortCompareBase::CompareInvocationCount = 0;
#endif

//***********************************************************************
//******    Comparison functions
//***********************************************************************

namespace detail
{

int FASTCALL CmpBool( cRawBuffer *mItem1, cRawBuffer *mItem2, const cFieldDef& field )
{
    return ( mItem1->ReadBoolNN( field ) - mItem2->ReadBoolNN( field ) );
}

int FASTCALL CmpChar( cRawBuffer *mItem1, cRawBuffer *mItem2, const cFieldDef& field )
{
    return ( mItem1->ReadCharNN( field ) - mItem2->ReadCharNN( field ) );
}

int FASTCALL CmpWChar( cRawBuffer *mItem1, cRawBuffer *mItem2, const cFieldDef& field )
{
    return ( mItem1->ReadWCharNN( field ) - mItem2->ReadWCharNN( field ) );
}

int FASTCALL CmpShort( cRawBuffer *mItem1, cRawBuffer *mItem2, const cFieldDef& field )
{
    return ( mItem1->ReadShortNN( field ) - mItem2->ReadShortNN( field ) );
}

int FASTCALL CmpInteger( cRawBuffer *mItem1, cRawBuffer *mItem2, const cFieldDef& field )
{
    return ( mItem1->ReadIntegerNN( field ) - mItem2->ReadIntegerNN( field ) );
}

int FASTCALL CmpLong( cRawBuffer *mItem1, cRawBuffer *mItem2, const cFieldDef& field )
{
    return ( mItem1->ReadLongNN( field ) - mItem2->ReadLongNN( field ) );
}

int FASTCALL CmpFloat( cRawBuffer *mItem1, cRawBuffer *mItem2, const cFieldDef& field )
{
    double  val = mItem1->ReadFloatNN( field ) - mItem2->ReadFloatNN( field );
    int     result = 0;

    if ( val < 0 )
        --result;
    else if ( val > 0 )
        ++result;
    return ( result );
}

int FASTCALL CmpDate( cRawBuffer *mItem1, cRawBuffer *mItem2, const cFieldDef& field )
{
    double  val = mItem1->ReadFloatNN( field ) - mItem2->ReadFloatNN( field );
    int     result = 0;

    if ( val < 0 )
        --result;
    else if ( val > 0 )
        ++result;
    return ( result );
}

int FASTCALL CmpString( cRawBuffer *mItem1, cRawBuffer *mItem2, const cFieldDef& field )
{
    return ( strcmp( mItem1->ReadStringNN( field ).c_str(), mItem2->ReadStringNN( field ).c_str() ) );
}

int FASTCALL CmpString_i( cRawBuffer *mItem1, cRawBuffer *mItem2, const cFieldDef& field )
{
    return ( StringCompare( mItem1->ReadStringNN( field ), mItem2->ReadStringNN( field ) ) );
}

CompareFunction FASTCALL GetCompareFunction( const cFieldDef& field, cFindField::CaseOption case_option )
{
    switch ( field.DataType() )
    {
        case ftBool         : return ( CmpBool );
        case ftChar         : return ( CmpChar );
        case ftWChar        : return ( CmpWChar );
        case ftShort        : return ( CmpShort );
        case ftInteger      : return ( CmpInteger );
        case ftLong         : return ( CmpLong );
        case ftDouble       : return ( CmpFloat );
        case ftDateTime     : return ( CmpDate );
        case ftString       : return ( case_option == cFindField::CaseSensitive ? CmpString : CmpString_i );
        case ftWString      : throw eNotApplicableOperation();
        default             : throw eNotApplicableOperation();
    }
}

}; // namespace detail

//***********************************************************************
//******    cIndexSortCompareStd
//***********************************************************************
CDFASTCALL cIndexSortCompareStd::cIndexSortCompareStd( const cIndexField& index_field )
    : mIndexFields(), mFieldMap(), mCompareFieldCount(1)
{
    mIndexFields.push_back( index_field );
}

CDFASTCALL cIndexSortCompareStd::cIndexSortCompareStd( const OpenIndexFields& index_fields )
    : mIndexFields(), mFieldMap(), mCompareFieldCount(index_fields.GetCount())
{
    const cIndexField     **ptr = index_fields.GetArray();

    for ( int n = 0, eend = index_fields.GetCount() ; n < eend ; ++n )
    {
        mIndexFields.push_back( **ptr );
        ++ptr;
    }
}

CDFASTCALL cIndexSortCompareStd::~cIndexSortCompareStd()
{
}

void FASTCALL cIndexSortCompareStd::Initialize( const cFieldDefs_ptr& field_defs )
{
    cSortCompareBase::Initialize( field_defs );
    for ( std::vector<cIndexField>::iterator n = mIndexFields.begin(), eend = mIndexFields.end() ; n != eend ; ++n )
    {
        const cFieldDef&    field_def = field_defs->FieldByName( n->GetFieldName() );

        mFieldMap.push_back( cFieldMapItem( &(*n), field_def,
                                            detail::GetCompareFunction( field_def, n->GetCaseOption() ) ) );
    }
}

bool FASTCALL cIndexSortCompareStd::do_compare_1( cRawBuffer *item1, cRawBuffer *item2 )
{
    std::vector<cFieldMapItem>::value_type  *first = &mFieldMap[0];
    std::vector<cFieldMapItem>::value_type  *last  = first + mCompareFieldCount;
    int                                     result;

    do
    {
        bool    is_null_1 = item1->IsNull( *(first->mField) );
        bool    is_null_2 = item2->IsNull( *(first->mField) );

        result = is_null_1 - is_null_2;
        if ( result == 0 && !is_null_1 )
            result = first->mCmpFunc( item1, item2, *(first->mField) );
        if ( first->mIndexField->GetOrderOptions() == cIndexField::Descending )
            result = -result;
    }
    while ( result == 0 && ++first != last );
    return ( result < 0 );
}

//***********************************************************************
//******    cFindCompareStd
//***********************************************************************
CDFASTCALL cFindCompareStd::cFindCompareStd( const cFindField& find_field )
    : mFindFields(), mFieldMap()
{
    mFindFields.push_back( find_field );
}

CDFASTCALL cFindCompareStd::cFindCompareStd( const OpenFindFields& find_fields )
    : mFindFields(), mFieldMap()
{
    const cFindField        **ptr = find_fields.GetArray();

    for ( int n = 0, eend = find_fields.GetCount() ; n < eend ; ++n )
    {
        mFindFields.push_back( **ptr );
        ++ptr;
    }
}

CDFASTCALL cFindCompareStd::~cFindCompareStd()
{
}

void FASTCALL cFindCompareStd::Initialize( const cFieldDefs_ptr& field_defs )
{
    cSortCompareBase::Initialize( field_defs );
    for ( std::vector<cFindField>::iterator n = mFindFields.begin(), eend = mFindFields.end() ; n != eend ; ++n )
    {
        const cFieldDef&    field_def = field_defs->FieldByName( n->GetFieldName() );

        mFieldMap.push_back( cFieldMapItem( &(*n), field_def,
                                            detail::GetCompareFunction( field_def, n->GetCaseOption() ) ) );
    }
}

bool FASTCALL cFindCompareStd::do_compare_1( cRawBuffer *item1, cRawBuffer *item2 )
{
    std::vector<cFieldMapItem>::iterator    first = mFieldMap.begin();
    std::vector<cFieldMapItem>::iterator    last  = mFieldMap.end();
    int                                     result;

    do
    {
        bool    is_null_1 = item1->IsNull( *(first->mField) );
        bool    is_null_2 = item2->IsNull( *(first->mField) );

        result = is_null_1 - is_null_2;
        if ( result == 0 && !is_null_1 )
            result = first->mCmpFunc( item1, item2, *(first->mField) );
    }
    while ( result == 0 && ++first != last );
    return ( result == 0 );
}

//***********************************************************************
//******    cFilterCompareBase
//***********************************************************************
CDFASTCALL cFilterCompareBase::~cFilterCompareBase()
{
}

void FASTCALL cFilterCompareBase::Initialize( const cFieldDefs_ptr& )
{
}

//---------------------------------------------------------------------------
//void FASTCALL cIndex::Construct( cData_ptr& data )
//{
//    typedef std::multiset<cData::size_type, SortControler>       sorted_list;
//
//    SortControler    cc = SortControler( mCompare, data );
//
//    cc.Initialize( data->GetFieldDefs() );
//
//    std::vector<cData::size_type>   aa;
//
//    for ( cData::size_type n = 0, eend = data->size() ; n < eend ; ++n )
//        aa.push_back( n );
//
//    sorted_list     list = sorted_list( aa.begin(), aa.end(), cc );
//
//    //list.insert( aa.begin(), aa.end() );
//    for ( sorted_list::iterator n = list.begin(), eend = list.end() ; n != eend ; ++n )
//        mContainer->push_back( (*data)[*n] );
//
//    //for ( cData::size_type n = 0, eend = data->size() ; n < eend ; ++n )
//    //   list.insert( n );
//    //for ( sorted_list::iterator n = list.begin(), eend = list.end() ; n != eend ; ++n )
//    //   mContainer->push_back( (*data)[*n] );
//}
//---------------------------------------------------------------------------

/*
//***********************************************************************
//******    cIndexes
//***********************************************************************
CDFASTCALL cIndexes::cIndexes()
{
}

CDFASTCALL cIndexes::~cIndexes()
{
}

void FASTCALL cIndexes::clear()
{
    mContainer.clear();
}

//---------------------------------------------------------------------------
class SortCompareIndexBy_Name : public std::binary_function<const shared_ptr<cIndex>&, const shared_ptr<cIndex>&, bool>
{
public:
    result_type FASTCALL operator()( first_argument_type idx1, second_argument_type idx2 )
    {
        return ( idx1->GetName() < idx2->GetName() );
    }
};

class FindCompareIndexBy_Name : public std::binary_function<const shared_ptr<cIndex>&, const char * const, bool>
{
public:
    result_type FASTCALL operator()( first_argument_type idx1, second_argument_type idx2 )
    {
        return ( idx1->GetName() < idx2 );
    }
};
//---------------------------------------------------------------------------
cIndex& FASTCALL cIndexes::AddIndex( const shared_ptr<cIndex>& index )
{
    iterator    idx_ptr = find_index( index->GetName() );

    if ( idx_ptr != mContainer.end() && (*idx_ptr)->GetName() == index->GetName() )
        throw eNameUnique();

    mContainer.insert( idx_ptr, index );
    return ( *index );
}

cIndexes::iterator FASTCALL cIndexes::find_index( const char *name )
{
    return ( std::lower_bound( mContainer.begin(), mContainer.end(), name, FindCompareIndexBy_Name() ) );
}

cIndexes::iterator FASTCALL cIndexes::find_index( const ds_string& name )
{
    return ( find_index( name.c_str() ) );
}

cIndex& FASTCALL cIndexes::index_by_name( const char *name )
{
    iterator    result = find_index( name );

    if ( result == mContainer.end() )
        throw eIndexNotFound();
    return ( *(*result) );
}

cIndex& FASTCALL cIndexes::index_by_name( const ds_string& name )
{
    return ( index_by_name( name.c_str() ) );
}
*/

//---------------------------------------------------------------------------
};
//---------------------------------------------------------------------------

