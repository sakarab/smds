#include "oBom.hpp"
#include "main_dll.hpp"
#include <sstream>

using namespace ds;

CDFASTCALL oBom::oBom()
    : /*pkData(),*/ fMessage(), fItemList()
{
}

void FASTCALL oBom::GetData( tblBOM& ds_bom, tblBMA& ds_bma, const char * where_clause )
{
    ds_bom.Open( *Database, where_clause );

    std::ostringstream  qstr;

    qstr << "(BOMID IN (SELECT BOMID FROM PDC_BOM WHERE " << where_clause << "))";
    ds_bma.Open( *Database, qstr.str().c_str() );
}

void FASTCALL oBom::InitBOmCache( tblBOM& ds_bom, tblBMA& ds_bma )
{
    GetData( ds_bom, ds_bma, "(BOMISACTIVE = 1) AND (BOMTYPE = 1) AND (BOMISRECYCLE = 0)" );
    //ds_bom.Open( *Database, "(BOMISACTIVE = 1) AND (BOMTYPE = 1) AND (BOMISRECYCLE = 0)" );
    //ds_bma.Open( *Database, "(BOMID IN (SELECT BOMID FROM PDC_BOM WHERE (BOMISACTIVE = 1) AND (BOMTYPE = 1) AND (BOMISRECYCLE = 0)))" );
}

void FASTCALL oBom::FixClientDataset( ds::cTable& tbl )
{
    tbl.AddField( "ID", ds::fkData, ds::ftInteger, 0 );
    tbl.AddField( "PARENTID", ds::fkData, ds::ftInteger, 0 );
    tbl.AddField( "BOMID", ds::fkData, ds::ftInteger, 0 );
    tbl.AddField( "BMAID", ds::fkData, ds::ftInteger, 0 );
    tbl.AddField( "MCIID", ds::fkData, ds::ftInteger, 0 );
    tbl.AddField( "DFVCODE1", ds::fkData, ds::ftString, 20 );
    tbl.AddField( "DFVCODE2", ds::fkData, ds::ftString, 20 );
    tbl.AddField( "DFVCODE3", ds::fkData, ds::ftString, 20 );
    tbl.AddField( "DFVCODE4", ds::fkData, ds::ftString, 20 );
    tbl.AddField( "DFVCODE5", ds::fkData, ds::ftString, 20 );
    tbl.AddField( "DFVCODE6", ds::fkData, ds::ftString, 20 );
    tbl.AddField( "DFVCODE7", ds::fkData, ds::ftString, 20 );
    tbl.AddField( "QUANTITYA", ds::fkData, ds::ftDouble, 0 );
    tbl.AddField( "UNIIDA", ds::fkData, ds::ftInteger, 0 );
    tbl.AddField( "UNIIDB", ds::fkData, ds::ftInteger, 0 );

    // ID is the autoinc field
}

void FASTCALL FixDataForReturn( std::vector<int>::iterator n )
{
}

bool FASTCALL oBom::CheckItemInCycle( const TItem& aItem )
{
    if ( fItemList.size() > 0 )
    {
        for ( std::vector<int>::iterator n = fItemList.begin(), eend = fItemList.end() ; n != eend ; ++n )
        {
            if ( *n == aItem.MCIID )
            {
                fItemList.push_back( aItem.MCIID );
                FixDataForReturn( n );
                return ( true );
            }
        }
    }
    return ( false );
}

cTable::iterator FASTCALL oBom::InsertInDatasetsDown( bool aBOMInsertion, int aParentID, cTable& dsClientData, const TItem& aItem,
                                                      bool aPutInCycle, int aUniidA, int aUniidB, tblBOM& pkData )
{
    cRecord             new_rec = dsClientData.NewRecord();
    tblBOM::iterator    pkData_iter = pkData.GetIterator();

    if ( aParentID < 0 )
        new_rec.FieldByName( "PARENTID" )->AsInteger( aParentID );
    if ( aBOMInsertion )
    {
        new_rec.FieldByName( "BOMID" )->AsInteger( pkData_iter->GetBOMID() );
        new_rec.FieldByName( "MCIID" )->AsInteger( aItem.MCIID );
        new_rec.FieldByName( "DFVCODE1" )->AsString( aItem.DFVCODE1 );
        new_rec.FieldByName( "DFVCODE2" )->AsString( aItem.DFVCODE2 );
        new_rec.FieldByName( "DFVCODE3" )->AsString( aItem.DFVCODE3 );
        new_rec.FieldByName( "DFVCODE4" )->AsString( aItem.DFVCODE4 );
        new_rec.FieldByName( "DFVCODE5" )->AsString( aItem.DFVCODE5 );
        new_rec.FieldByName( "DFVCODE6" )->AsString( aItem.DFVCODE6 );
        new_rec.FieldByName( "DFVCODE7" )->AsString( aItem.DFVCODE7 );
        new_rec.FieldByName( "QUANTITYA" )->AsDouble( pkData_iter->GetBOMREFQUANTITY() );
        if ( aPutInCycle )
            fItemList.push_back( aItem.MCIID );
    }
    else
    {
        // pending
        fItemList.push_back( aItem.MCIID );
    }
    new_rec.FieldByName( "UNIIDA" )->AsInteger( aUniidA );
    if ( aUniidB != INVALIDID )
        new_rec.FieldByName( "UNIIDB" )->AsInteger( aUniidB );

    return ( dsClientData.AddRecord( new_rec ) );
}

void FASTCALL oBom::FixDatasetDown( TItem aItem, cTable& dsClientData, bool aBOMCalculation, int& aParentID,
                                    bool aPutInCycle, int aUNIIDA, int aUNIIDB, tblBOM& pkData )
{
    if ( aBOMCalculation )
    {
        if ( CheckItemInCycle( aItem )  )
            throw PDNException( fMessage );

        cTable::iterator    dsClientData_iter = InsertInDatasetsDown( false, aParentID, dsClientData, aItem, true, aUNIIDA, aUNIIDB, pkData );
        int                 aNewParentID = dsClientData_iter.FieldByName( "ID" )->AsInteger();

        FixDatasetDown( aItem, dsClientData, false, aNewParentID, false, aUNIIDA, aUNIIDB, pkData );
        if ( ! fItemList.empty() )
            fItemList.pop_back();
    }
    else
    {
    }
}

void FASTCALL FixDatasetUp( TItem aItem, cTable& dsClientData, int& aParentID )
{
}

void FASTCALL oBom::FixDataset( tblFirstScanDataset& dsMCIFromClient, bool direction, ds::cIndex_ptr& out )
{
    cTable      dsClientData;

    FixClientDataset( dsClientData );

    tblBOM      ds_bom;
    tblBMA      ds_bma;

    GetData( ds_bom, ds_bma, BuildWhereClause( OpenWhereExpression( WhereAtom( "BOMISACTIVE", "", 1 ),
                                                                    WhereAtom( "BOMTYPE", "", ds_string( "1" ) ),
                                                                    WhereAtom( "BOMTYPE", "", 0 ) ) ).c_str() );
    //pkData.Open( *Database, BuildWhereClause( OpenWhereExpression( WhereAtom( "BOMISACTIVE", "", 1 ),
    //                                                               WhereAtom( "BOMTYPE", "", ds_string( "1" ) ),
    //                                                               WhereAtom( "BOMTYPE", "", 0 ) ) ).c_str() );
    if ( direction )
    {
        tblFirstScanDataset::iterator   mci_iter = dsMCIFromClient.GetIterator();

        while ( ! mci_iter.eof() )
        {
            int     aTempID = 0;
            TItem   aCurrentItem( mci_iter->GetMCIID(), mci_iter->GetDFVCODE1(), mci_iter->GetDFVCODE2(),
                                  mci_iter->GetDFVCODE3(), mci_iter->GetDFVCODE4(), mci_iter->GetDFVCODE5(),
                                  mci_iter->GetDFVCODE6(), mci_iter->GetDFVCODE7() );

            FixDatasetDown( aCurrentItem, dsClientData, false, aTempID, true, INVALIDID, INVALIDID, ds_bom );
            ++mci_iter;
        }
    }
    else
    {
        tblFirstScanDataset::iterator   mci_iter = dsMCIFromClient.GetIterator();

        while ( ! mci_iter.eof() )
        {
            int     aTempID = 0;
            TItem   aCurrentItem( mci_iter->GetMCIID(), mci_iter->GetDFVCODE1(), mci_iter->GetDFVCODE2(),
                                  mci_iter->GetDFVCODE3(), mci_iter->GetDFVCODE4(), mci_iter->GetDFVCODE5(),
                                  mci_iter->GetDFVCODE6(), mci_iter->GetDFVCODE7() );

            fItemList.clear();
            FixDatasetUp( aCurrentItem, dsClientData, aTempID );
            ++mci_iter;
        }
    }
}
