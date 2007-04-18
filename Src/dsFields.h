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
#if ! defined (SM_DS_FIELDS_H)
#define SM_DS_FIELDS_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include "dsTypes.h"
#include "dsUtils.h"
#include <vector>
#include <list>
#include "dsSmartPtr.h"
#include "dsStream.h"

namespace smds
{

// cFieldKind_sync
enum cFieldKind         { fkData, fkInternalCalc };
// cFieldDataType_sync
enum cFieldDataType     { ftBool, ftChar, ftWChar, ftShort, ftInteger, ftLong, ftDouble, ftDateTime, ftString, ftWString, ftBlob };

inline cStream& FASTCALL operator << ( cStream& st, const cFieldKind a )        { return ( st.WriteBuffer( &a, sizeof(cFieldKind) ) ); }
inline cStream& FASTCALL operator << ( cStream& st, const cFieldDataType a )    { return ( st.WriteBuffer( &a, sizeof(cFieldDataType) ) ); }
inline cStream& FASTCALL operator >> ( cStream& st, cFieldKind& a )             { return ( st.ReadBuffer( &a, sizeof(cFieldKind) ) ); }
inline cStream& FASTCALL operator >> ( cStream& st, cFieldDataType& a )         { return ( st.ReadBuffer( &a, sizeof(cFieldDataType) ) ); }

//***********************************************************************
//******    cFieldDef_
//***********************************************************************
class cFieldDef_
{
public:
    unsigned short      mIndex;
    int                 mOffset;
    const char *        mName;
    cFieldKind          mKind;
    cFieldDataType      mDataType;
    unsigned short      mSize;
};

//***********************************************************************
//******    cFieldDefs_
//***********************************************************************
struct cFieldDefs_
{
    typedef const cFieldDef_ *   const_iterator;

    int                 mBufferSize;
    int                 mCount;
    const char          *mSql;
    const char          *mTableName;
    const cFieldDef_    *mFieldDefs;
    //int                 mBlobCount;
    //const cFieldDef     *mBlobFieldDefs;
};

//***********************************************************************
//******    cFieldDef
//***********************************************************************
class cFieldDef
{
private:
    friend cStream& FASTCALL operator << ( cStream& st, const cFieldDef a );
    friend cStream& FASTCALL operator >> ( cStream& st, cFieldDef& a );
    friend class cTableWriter;

    unsigned short      mIndex;
    int                 mOffset;
    ds_string           mName;
    cFieldKind          mKind;
    cFieldDataType      mDataType;
    unsigned short      mSize_;
#ifdef SM_DS_STRING_AS_STRING
    unsigned short      mDataSize_;
#endif
    CDFASTCALL cFieldDef()                                      {} // empty
    // noncopyable
    //FASTCALL cFieldDef( const cFieldDef& src );
    //cFieldDef& FASTCALL operator=( const cFieldDef& src );
public:
    CDFASTCALL cFieldDef( unsigned short idx, int offset, const ds_string& name,
                          cFieldKind kind, cFieldDataType data_type, unsigned short size );
    CDFASTCALL ~cFieldDef();
    bool FASTCALL operator == ( const cFieldDef& other ) const;
    bool FASTCALL operator != ( const cFieldDef& other ) const          { return ( !(*this == other) ); }
    unsigned short FASTCALL Index() const                               { return ( mIndex ); }
    int FASTCALL Offset() const                                         { return ( mOffset ); }
    const ds_string& FASTCALL Name() const                              { return ( mName ); }
    cFieldKind FASTCALL Kind() const                                    { return ( mKind ); }
    cFieldDataType FASTCALL DataType() const                            { return ( mDataType ); }
    unsigned short FASTCALL Size_() const                               { return ( mSize_ ); }
#ifdef SM_DS_STRING_AS_STRING
    unsigned short FASTCALL DataSize_() const                           { return ( mDataSize_ ); }
#endif
};

cStream& FASTCALL operator << ( cStream& st, const cFieldDef a );
cStream& FASTCALL operator >> ( cStream& st, cFieldDef& a );

//***********************************************************************
//******    cFieldDefs
//***********************************************************************

namespace detail
{

class cFieldNameMap
{
private:
    const ds_string     *mFieldName;
    const cFieldDef     *mFieldDef;
public:
    CDFASTCALL cFieldNameMap( const ds_string& field_name )
        : mFieldName(&field_name), mFieldDef(0)
    {
    }
    CDFASTCALL cFieldNameMap( const ds_string& field_name, const cFieldDef& field_def )
        : mFieldName(&field_name), mFieldDef(&field_def)
    {
    }
    const ds_string& FASTCALL FieldName() const      { return ( *mFieldName ); }
    const cFieldDef& FASTCALL FieldDef() const       { return ( *mFieldDef ); }
};

};  // namespace detail

class cFieldDefs
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
{
private:
    typedef std::list< cFieldDef >                      cFieldDefContainer;
    typedef std::vector< detail::cFieldNameMap >        cFieldDefSortedContainer;
private:
    int                         mBufferSize;
    cFieldDefContainer          mFieldDefs;
    cFieldDefSortedContainer    mFieldDefSorted;

    const cFieldDef FASTCALL MakeFieldDef( const ds_string& name, cFieldKind kind, cFieldDataType data_type, unsigned short size );
    void FASTCALL ConstructSorted();
    // non copyable
    CDFASTCALL cFieldDefs( const cFieldDefs& src );
    cFieldDefs& FASTCALL operator=( const cFieldDefs& src );
public:
    typedef cFieldDefContainer::iterator            iterator;
    typedef cFieldDefContainer::const_iterator      const_iterator;
public:
    CDFASTCALL cFieldDefs();
    CDFASTCALL cFieldDefs( const cFieldDefs_& field_defs );
    CDFASTCALL ~cFieldDefs();
    void FASTCALL swap( cFieldDefs& src );

    iterator FASTCALL begin()                                       { return ( mFieldDefs.begin() ); }
    iterator FASTCALL end()                                         { return ( mFieldDefs.end() ); }
    const_iterator FASTCALL begin() const                           { return ( mFieldDefs.begin() ); }
    const_iterator FASTCALL end() const                             { return ( mFieldDefs.end() ); }
    int FASTCALL BufferSize() const                                 { return ( mBufferSize ); }
    int FASTCALL Count() const                                      { return ( mFieldDefSorted.size() ); }

    //bool FASTCALL equal( const cFieldDefs& field_defs ) const;
    //const cFieldDef& FASTCALL Fields( int idx ) const;
    const cFieldDef& FASTCALL AddField( const ds_string& name, cFieldKind kind, cFieldDataType data_type, unsigned short size );
    const cFieldDef& FASTCALL FieldByName( const ds_string& field_name ) const;
    const cFieldDef& FASTCALL FieldByName( const char *field_name ) const;
};

typedef shared_ptr<cFieldDefs>      cFieldDefs_ptr;                      

};

//---------------------------------------------------------------------------
#endif

