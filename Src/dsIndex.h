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
#ifndef SM_DS_INDEX_H
#define SM_DS_INDEX_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include <vector>
#include "dsTypes.h"
#include "dsUtils.h"
#include "dsFields.h"
//---------------------------------------------------------------------------

namespace ds
{

class cRawBuffer;

//***********************************************************************
//******    cSortCompareBase
//***********************************************************************
class cSortCompareBase
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
{
private:
    friend class cTablebase;
    friend class cIndex;
    friend class cData;
    // non copyable
    CDFASTCALL cSortCompareBase( const cSortCompareBase& src );
    cSortCompareBase& FASTCALL operator=( const cSortCompareBase& src );
protected:
    cFieldDefs              *mFieldDefs;
    virtual void FASTCALL Initialize( const cFieldDefs_ptr& field_defs );
    virtual bool FASTCALL do_compare_1( cRawBuffer *item1, cRawBuffer *item2 ) = 0;
public:
    CDFASTCALL cSortCompareBase()
        : mFieldDefs(0)                                             {}  // empty
    virtual CDFASTCALL ~cSortCompareBase();
    bool FASTCALL compare( cRawBuffer& item1, cRawBuffer& item2 )
    {
#if defined SM_DS_DEBUG
        ++CompareInvocationCount;
#endif
        return ( do_compare_1( &item1, &item2 ) );
    }
#if defined SM_DS_DEBUG
    static int  CompareInvocationCount;
#endif
};

//***********************************************************************
//******    cCompareStd
//***********************************************************************
typedef int (FASTCALL *CompareFunction)( cRawBuffer *mItem1, cRawBuffer *mItem2, const cFieldDef& field );

//***********************************************************************
//******    cIndexSortCompareStd
//***********************************************************************
class cIndexSortCompareStd : public cSortCompareBase
{
private:
    class cFieldMapItem
    {
    public:
        cIndexField         *mIndexField;
        const cFieldDef     *mField;
        CompareFunction     mCmpFunc;
        CDFASTCALL cFieldMapItem( cIndexField *index_field, const cFieldDef& field, CompareFunction cmp_func )
            : mIndexField(index_field), mField(&field), mCmpFunc(cmp_func)
        {
        }
    };

    std::vector<cIndexField>                mIndexFields;
    std::vector<cFieldMapItem>              mFieldMap;
    std::vector<cIndexField>::size_type     mCompareFieldCount;
    // non copyable
    CDFASTCALL cIndexSortCompareStd( const cIndexSortCompareStd& src );
    cIndexSortCompareStd& FASTCALL operator=( const cIndexSortCompareStd& src );
public:
    class CompareFieldCountGuard
    {
    private:
        cIndexSortCompareStd                    *mIndexSortCompareStd;
        std::vector<cIndexField>::size_type     mOldCompareFieldCount;
    public:
        CDFASTCALL CompareFieldCountGuard( cIndexSortCompareStd& guarded, std::vector<cIndexField>::size_type new_count )
            : mIndexSortCompareStd(&guarded), mOldCompareFieldCount(guarded.mCompareFieldCount)
        {
            guarded.mCompareFieldCount = new_count;
        }
        CDFASTCALL ~CompareFieldCountGuard()
        {
            mIndexSortCompareStd->mCompareFieldCount = mOldCompareFieldCount;
        }
    };

    friend class CompareFieldCountGuard;

protected:
    virtual void FASTCALL Initialize( const cFieldDefs_ptr& field_defs );
    virtual bool FASTCALL do_compare_1( cRawBuffer *item1, cRawBuffer *item2 );
public:
    CDFASTCALL cIndexSortCompareStd( const cIndexField& index_field );
    CDFASTCALL cIndexSortCompareStd( const OpenIndexFields& index_fields );
    virtual CDFASTCALL ~cIndexSortCompareStd();
    const std::vector<cIndexField>& FASTCALL GetIndexFields() const             { return ( mIndexFields ); }
};

//***********************************************************************
//******    cFindCompareStd
//***********************************************************************
class cFindCompareStd : public cSortCompareBase
{
private:
    class cFieldMapItem
    {
    public:
        cFindField          *mFindField;
        const cFieldDef     *mField;
        CompareFunction     mCmpFunc;
        CDFASTCALL cFieldMapItem( cFindField *find_field, const cFieldDef& field, CompareFunction cmp_func )
            : mFindField(find_field), mField(&field), mCmpFunc(cmp_func)
        {
        }
    };
    std::vector<cFindField>         mFindFields;
    std::vector<cFieldMapItem>      mFieldMap;
protected:
    virtual void FASTCALL Initialize( const cFieldDefs_ptr& field_defs );
    virtual bool FASTCALL do_compare_1( cRawBuffer *item1, cRawBuffer *item2 );
public:
    CDFASTCALL cFindCompareStd( const cFindField& find_field );
    CDFASTCALL cFindCompareStd( const OpenFindFields& find_fields );
    virtual CDFASTCALL ~cFindCompareStd();
};

//***********************************************************************
//******    cFilterCompareBase
//***********************************************************************
class cFilterCompareBase
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
{
private:
    friend class cTablebase;
    friend class cIndex;
    // non copyable
    CDFASTCALL cFilterCompareBase( const cFilterCompareBase& src );
    cFilterCompareBase& FASTCALL operator=( const cFilterCompareBase& src );
protected:
    cFieldDefs              *mFieldDefs;

    virtual void FASTCALL Initialize( const cFieldDefs_ptr& );      // no_op
    virtual bool FASTCALL do_compare_1( cRawBuffer *item1 ) = 0;
public:
    CDFASTCALL cFilterCompareBase()
        : mFieldDefs(0)                                             {} // empty
    virtual CDFASTCALL ~cFilterCompareBase();
    bool FASTCALL compare( cRawBuffer& item1 )
    {
        return ( do_compare_1( &item1 ) );
    }
};

//---------------------------------------------------------------------------
typedef shared_ptr<cSortCompareBase>        cSortCompareBase_ptr;
typedef shared_ptr<cFilterCompareBase>      cFilterCompareBase_ptr;
//---------------------------------------------------------------------------

};
//---------------------------------------------------------------------------
#endif
