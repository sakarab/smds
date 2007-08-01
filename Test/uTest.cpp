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
#include "uTest.h"
#include "dsIndex.h"
#include "dsVariant.h"
#include "dsSysOpen.h"
#include "dsExceptions.h"
//---------------------------------------------------------------------------
#include <iostream>
#include <boost/type_traits.hpp>

using namespace smds;

template <std::size_t offset, class T> class aligned_offset
{
private:
    enum { modulo = offset % boost::alignment_of<T>::value };
public:
    enum { value = (modulo == 0 ? offset : offset + boost::alignment_of<T>::value - modulo) };
};


const int prev_offset = 8;
const int end_offset = prev_offset + sizeof(int);
//const int aa = new_offset + boost::alignment_of<int>::value - (new_offset % boost::alignment_of<int>::value);
const int bb = aligned_offset< end_offset, int >::value;

/*
template
<
    int index_,
    const char *name_,
    smds::cFieldKind field_kind_,
    smds::cFieldDataType field_data_type_,
    std::size_t size_
>
struct field_def
{
    enum { index = index_ };
    typedef field_kind;
    typedef field_data_type;
};
*/

template <smds::cFieldDataType field_data_type, std::size_t data_size> struct field_trait       {}; // empty

template <std::size_t data_size> struct field_trait<ftBool, data_size>
{
    typedef bool    type;
    enum { size = sizeof(type) };
};

template <std::size_t data_size> struct field_trait<ftByte, data_size>
{
    typedef char    type;
    enum { size = sizeof(type) };
};

template <std::size_t data_size> struct field_trait<ftShort, data_size>
{
    typedef short   type;
    enum { size = sizeof(type) };
};

template <std::size_t data_size> struct field_trait<ftInteger, data_size>
{
    typedef int     type;
    enum { size = sizeof(type) };
};

template <std::size_t data_size> struct field_trait<ftLongLong, data_size>
{
    typedef long long   type;
    enum { size = sizeof(type) };
};

template <std::size_t data_size> struct field_trait<ftDouble, data_size>
{
    typedef double  type;
    enum { size = sizeof(type) };
};

template <std::size_t data_size> struct field_trait<ftDate, data_size>
{
    typedef detail::dbDate_Internal     type;
    enum { size = sizeof(type) };
};

template <std::size_t data_size> struct field_trait<ftTime, data_size>
{
    typedef detail::dbTime_Internal     type;
    enum { size = sizeof(type) };
};

template <std::size_t data_size> struct field_trait<ftDateTime, data_size>
{
    typedef detail::dbDateTime_Internal     type;
    enum { size = sizeof(type) };
};

template <std::size_t data_size> struct field_trait<ftGUID, data_size>
{
    typedef detail::dbGUID_Internal     type;
    enum { size = sizeof(type) };
};

template <std::size_t data_size> struct field_trait<ftString, data_size>
{
    typedef ds_string *     type;
    enum { size = data_size };
};

//template <> struct field_trait<ftWString>   { enum { size = sizeof(short) };  typedef short   type; };
//template <> struct field_trait<ftBlob>      { enum { size = sizeof(short) };  typedef short   type; };

int cc = field_trait<ftShort,0>::size;

#define SM_DS_FIELD_0( array_name, index, name, field_kind, field_data_type, size_ ) \
    { index, \
      0, \
      name, \
      field_kind, \
      field_data_type, \
      field_trait<field_data_type, size_>::size }

#define SM_DS_FIELD( array_name, index, name, field_kind, field_data_type, size_ ) \
    { index, \
      aligned_offset<array_name[index-1].mOffset, field_trait<field_data_type, size_>::type>::value, \
      name, \
      field_kind, \
      field_data_type, \
      field_trait<field_data_type, size_>::size }

const detail::cFieldDef_     tblDummy_Fields[] =
{
    { 0, 0, "LocationID", fkData, ftInteger,  4 },
    { 1, tblDummy_Fields[0].mOffset + 5,  "LocTypeID",  fkData, ftShort,    2 },
    { 2, tblDummy_Fields[1].mOffset + 5,  "IsUser",     fkData, ftShort,    2 },
    { 3, tblDummy_Fields[2].mOffset + 5,  "SerialNo",   fkData, ftInteger,  4 },
    { 4, tblDummy_Fields[3].mOffset + 5,  "Drive",      fkData, ftString,   4 }
};

struct tblFiles_mapmap
{
    int                                 FileID_;
    int                                 PathID_;
    ds_string                           *LongFileName_;
    int                                 fSize_;
    smds::detail::dbDateTime_Internal   fDate_;
    ds_string                           *Description_;
    int                                 zipID_;
};

const detail::cFieldDef_     tblFiles_Fields[] =
{
    { 0, offsetof(tblFiles_mapmap,FileID_),       "FileID",       fkData, ftInteger,    4 },
    { 1, offsetof(tblFiles_mapmap,PathID_),       "PathID",       fkData, ftInteger,    4 },
    { 2, offsetof(tblFiles_mapmap,LongFileName_), "LongFileName", fkData, ftString,   255 },
    { 3, offsetof(tblFiles_mapmap,fSize_),        "fSize",        fkData, ftInteger,    4 },
    { 4, offsetof(tblFiles_mapmap,fDate_),        "fDate",        fkData, ftDateTime,   8 },
    { 5, offsetof(tblFiles_mapmap,Description_),  "Description",  fkData, ftString,   255 },
    { 6, offsetof(tblFiles_mapmap,zipID_),        "zipID",        fkData, ftInteger,    4 },
};

/*
const detail::cFieldDef_     tblFiles_Fields_2[] =
{
    SM_DS_FIELD_0( tblFiles_Fields_2, 0, "FileID", fkData, ftInteger, 0 ),
    SM_DS_FIELD  ( tblFiles_Fields_2, 1, "PathID", fkData, ftInteger, 0 ),
    SM_DS_FIELD  ( tblFiles_Fields_2, 2, "LongFileName", fkData, ftString, 255 ),
    SM_DS_FIELD  ( tblFiles_Fields_2, 3, "fSize", fkData, ftInteger, 0 ),
    SM_DS_FIELD  ( tblFiles_Fields_2, 4, "fDate", fkData, ftDateTime, 0 ),
    SM_DS_FIELD  ( tblFiles_Fields_2, 5, "Description", fkData, ftString, 255 ),
    SM_DS_FIELD  ( tblFiles_Fields_2, 6, "zipID", fkData, ftInteger, 0 )
};
*/

void TestAlign()
{
    std::cout << "alignment = " << boost::alignment_of<int>::value << " offset = " << bb << '\n';

    //for ( int n = 0 ; n < 5 ; ++n )
    //    std::cout << n << " " << tblDummy_Fields[n].mOffset << '\n';

}

//***********************************************************************
//******    GetTblFiles
//***********************************************************************
tblFiles_ptr GetTblFiles( Database& database )
{
    tblFiles_ptr    result( new tblFiles() );

    result->Open( database, 0 );

    return result;
}

//***********************************************************************
//******    WhileLoop
//***********************************************************************
void FASTCALL WhileLoop( record_iterator ptr )
{
    while ( ! ptr.eof() )
        ++ptr;
}
//***********************************************************************
//******    ForLoop
//***********************************************************************
void FASTCALL ForLoop( record_iterator ptr )
{
    for ( int n = 0, end = ptr.RecordCount() ; n < end ; ++n )
        ++ptr;
}
//***********************************************************************
//******    CheckNull
//***********************************************************************
int FASTCALL CountNulls( tblFiles::iterator ptr )
{
    int     result = 0;

    ptr.First();
    for ( int n = 0, end = ptr.RecordCount() ; n < end ; ++n, ++ptr )
        if ( ptr->zipID_IsNull() )
            ++result;
    return ( result );
}
//***********************************************************************
//******    CreateIndex
//***********************************************************************
//class idx_ByLocationID : public tblLocation::index_sort_compare
//{
//protected:
//    virtual bool FASTCALL typed_compare( const tblLocation::raw& item1, const tblLocation::raw& item2 )
//    {
//        return ( item1.GetLocationID() > item2.GetLocationID() );
//    }
//};

cIndex_ptr FASTCALL CreateIndex_g1( spTable uds )
//ds::cIndex_ptr FASTCALL CreateIndex_g1( tblFiles_ptr uds )
{
    return ( uds->NewIndex( cIndexField( "PathID", cIndexField::Descending ) ) );
}

int AdjusentCount( Index::iterator ptr1 )
{
    int     result = 0;

    if ( ptr1.RecordCount() <= 1 )
        return result;

    ptr1.First();

    Index::iterator    ptr2 = ptr1;

    ptr2.Next();
    while ( ! ptr2.eof() )
    {
        if ( ptr1.FieldByName( "PathID" )->AsInteger() == ptr2.FieldByName( "PathID" )->AsInteger() )
            ++result;
        ++ptr1;
        ++ptr2;
    }
    return result;
}

int FASTCALL Check_Order_g1( Index::iterator ptr1 )
{
    int     result = 0;

    ptr1.First();

    Index::iterator    ptr2 = ptr1;

    ptr2.Next();
    while ( ! ptr2.eof() )
    {
        if ( ptr1.FieldByName( "PathID" )->AsInteger() < ptr2.FieldByName( "PathID" )->AsInteger() )
            ++result;
        ++ptr1;
        ++ptr2;
    }
    return ( result );
}

tblFiles::index_ptr FASTCALL CreateIndex_g2( tblFiles_ptr uds )
{
    return ( uds->NewIndex( OpenIndexFields( cIndexField( "PathID" ), cIndexField( "fSize" ) ) ) );
}

cIndex_ptr FASTCALL CreateIndex_g22( tblFiles_ptr uds )
{
    return ( uds->NewIndex( spFieldSortCompare( new FieldSortCompare(
        OpenIndexFields( cIndexField( "PathID" ), cIndexField( "fSize" ) ) ) ) ) );
}

int FASTCALL Check_Order_g2( Index::iterator ptr1 )
{
    int     result = 0;

    ptr1.First();

    Index::iterator    ptr2 = ptr1;

    ptr2.Next();

    while ( ! ptr2.eof() )
    {
        if ( ptr1.FieldByName( "PathID" )->AsInteger() > ptr2.FieldByName( "PathID" )->AsInteger() )
            ++result;
        else if ( ptr1.FieldByName( "PathID" )->AsInteger() == ptr2.FieldByName( "PathID" )->AsInteger() )
            if ( ptr1.FieldByName( "fSize" )->AsInteger() >= ptr2.FieldByName( "fSize" )->AsInteger() )
                ++result;
        ++ptr1;
        ++ptr2;
    }
    return ( result );
}

class idx_ByPathID : public tblFiles::sort_compare
{
private:
    // non copyable
    CDFASTCALL idx_ByPathID( const idx_ByPathID& src );
    idx_ByPathID& FASTCALL operator=( const idx_ByPathID& src );
protected:
    virtual bool FASTCALL typed_compare( const tblFiles::raw& item1, const tblFiles::raw& item2 )
    {
        return ( item1.GetPathID() < item2.GetPathID() );
    }
public:
    CDFASTCALL idx_ByPathID()
        : tblFiles::sort_compare()
    {
    }
};

tblFiles::index_ptr FASTCALL CreateIndex_f1( tblFiles_ptr uds )
{
    return ( uds->NewIndex( spSortCompare( new idx_ByPathID() ) ) );
}

int FASTCALL Check_Order_f1( tblFiles::index::iterator ptr1 )
{
    int     result = 0;

    ptr1.First();
    if ( ptr1.eof() )
        return result;

    tblFiles::index::iterator      ptr2 = ptr1;

    ptr2.Next();
    while ( ! ptr2.eof() )
    {
        if ( ptr1->GetPathID() > ptr2->GetPathID() )
            ++result;
        ++ptr1;
        ++ptr2;
    }
    return ( result );
}

//***********************************************************************
//******    dsDatasetModify
//***********************************************************************
void FASTCALL dsDatasetModify_1( tblFiles::iterator ds, const ds_string& descr )
{
    ds.First();
    for ( int n = 0, end = ds.RecordCount() ; n < end ; ++n, ++ds )
    {
        ds->SetFileID( n );
        ds->SetfSize( n );
        ds->SetDescription( descr );
    }
}

void FASTCALL dsDatasetModify_2( tblFiles::iterator ds, const ds_string& descr )
{
    ds.Last();
    ds.First();
    for ( int n = 0, end = ds.RecordCount() ; n < end ; ++n, ++ds )
    {
        ds->SetFileID( n );
        ds->SetfSize( n );
        ds->SetDescription( descr );
    }
    ds.Last();
}

void FASTCALL dsDatasetModify( tblFiles::iterator ds )
{
    ds_string   sstr( 200, 'h' );

    dsDatasetModify_1( ds, sstr );
    dsDatasetModify_2( ds, sstr );
}

//***********************************************************************
//******    AddRecords
//***********************************************************************
void FASTCALL AddRecords( tblFiles_ptr ds )
{
    UpdateLocker    lock( ds ); 

    for ( int n = 0 ; n < 20000 ; ++n )
    {
        tblFiles::record    new_record = ds->NewRecord();

        new_record->SetFileID( n );
        new_record->SetPathID( n );
        new_record->SetfSize( n );
        new_record->SetDescription( "record description" );
        ds->AddRecord( new_record );
    }
}

//***********************************************************************
//******    LocateRecord
//***********************************************************************
void FASTCALL LocateRecord( tblFiles_ptr ds )
{
    tblFiles::iterator  iter = ds->Locate( OpenValues( 19999, 19998 ),
                                           OpenFindFields( "FileID", "PathID" ) );
}

//***********************************************************************
//******    FindRecord
//***********************************************************************
Index::iterator FASTCALL FindRecord_g2( cIndex_ptr idx )
{
    return ( idx->Find( OpenValues( Variant( 18999 ), Variant( 18999 ) ) ) );
}

//***********************************************************************
//******    CompileTest
//***********************************************************************
void FASTCALL CompileTest( tblFiles_ptr ds )
{
    tblFiles::iterator      data_iter = ds->GetIterator();

    data_iter.First();
    if ( ! data_iter.eof() )
    {
        data_iter->SetFileID( 5 );
        data_iter.OldValues()->GetFileID();

        data_iter.OldValues().FieldByName( "fSize" )->AsBoolean();
        data_iter.FieldByName( "fSize" )->AsBoolean( true );
    }
}

//***********************************************************************
//******    TestVariant
//***********************************************************************
Variant FASTCALL TestVariant()
{
    //ds::Variant     a( static_cast<unsigned short>(sizeof(Variant)) );
    Variant         a( sizeof(Variant) );
    bool            b = a.AsBool();
    ds_string       ss = "22";
    Variant         c( ss );

    if ( c.AsBool() == true )
        return ( Variant( b ) );

    if ( false == c.AsBool() && b )
        return ( Variant( b ) );

    return ( a );
}

int FASTCALL foo( Index::iterator iter )
{
    Index::iterator     aa = ++iter;
    Table::iterator     bb = aa;
    Table::iterator     cc = ++bb;

    if ( ! iter.eof() )
        return ( iter.FieldByName( "PathID" )->AsInteger() + iter.FieldByName( "fSize" )->AsInteger() );
    else
        return ( 0 );
}

int FASTCALL foo1( tblFiles::iterator iter )
{
    tblFiles::iterator   aa = ++iter;
    tblFiles::iterator   bb = iter + 1;

    if ( ! iter.eof() )
        return ( iter.FieldByName( "PathID" )->AsInteger() + iter.FieldByName( "fSize" )->AsInteger() );
    else
        return ( 0 );
}

int FASTCALL foo2( tblFiles::index::iterator iter )
{
    tblFiles::index::iterator   aa = ++iter;
    tblFiles::index::iterator   bb = iter + 1;
    // tblFiles::iterator          cc( ++aa );
    // tblFiles::iterator          dd = cc + 1;

    if ( ! iter.eof() )
        return ( iter.FieldByName( "PathID" )->AsInteger() + iter.FieldByName( "fSize" )->AsInteger() );
    else
        return ( 0 );
}

//***********************************************************************
//******    Test
//***********************************************************************
void Test( tblFiles_ptr ds, ErrorReporter error_reporter, void *user_data )
{
    tblFiles::iterator      iter = ds->GetIterator();

    WhileLoop( iter );
    ForLoop( iter );
    dsDatasetModify( iter );
    CountNulls( iter );
    foo1( iter );

    int             unorder_count;

    //unorder_count = Check_Order_f1( ds->GetIterator() );
    //if ( unorder_count != 0 )
    //    foo();

    tblFiles::index_ptr     files_idx;

    files_idx = CreateIndex_f1( ds );
    unorder_count = Check_Order_f1( files_idx->GetIterator() );
    if ( unorder_count != 0 )
        error_reporter( user_data, "" );

    foo2( files_idx->GetIterator() );

    tblFiles::index::range_iterator     riter = files_idx->GetRangeIterator( cRangeValues( 54, 56 ) );

    while ( ! riter.eof() )
        ++riter;

    cIndex_ptr  idx;

    idx = CreateIndex_g1( ds );
    unorder_count = Check_Order_g1( idx->GetIterator() );
    if ( unorder_count != 0 )
        error_reporter( user_data, "" );

    idx = CreateIndex_g2( ds );
    unorder_count = Check_Order_g2( idx->GetIterator() );
    if ( unorder_count != 0 )
        error_reporter( user_data, "" );

    AddRecords( ds );

    idx = CreateIndex_g2( ds );
    unorder_count = Check_Order_g2( idx->GetIterator() );
    if ( unorder_count != 0 )
        error_reporter( user_data, "" );

    for ( int n = 0 ; n < 100 ; ++n )
        foo( FindRecord_g2( idx ) );

    //idx = CreateIndex_g22( ds );
    //unorder_count = Check_Order_g2( idx->GetIterator() );
    //if ( unorder_count != 0 )
    //    foo();

    LocateRecord( ds );

    CompileTest( ds );
    TestVariant();

    //Variant     packet = cTableReader::GetTablePacket( ds );

    //cTableWriter::SetTableData( ds, packet );
}

//---------------------------------------------------------------------------
