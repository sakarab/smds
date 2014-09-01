#include "oPrn.hpp"
#include "oCal.hpp"
#include "oBom.hpp"
#include "main_dll.hpp"
#include "uSub.h"
#include <sstream>

using namespace ds;

const char rs_NoGeneralCalendarFound[] = "Δεν έχετε δηλώσει γενικό ημερολόγιο στις Παραμέτρους Παραγωγής";

enum TProductionNeedStatus { prnsNull, prnsMPS, prnsMRP, prnsCRP, prnsFP, prnsWOR };

const char *ProductionNeedStatusValues[prnsWOR+1] = { "", "1", "2", "3", "4", "5" };

CDFASTCALL oPrn::oPrn( int StartWeek_, int EndWeek_, unsigned short StartYear_, unsigned short EndYear_,
                       bool aWillCalcPDO_, bool aWillCalcSafStock_, double aMRSStartDate_,
                       double aMRSEndDate_, int aMRSMODE_ )
    : StartWeek(StartWeek_), EndWeek(EndWeek_), StartYear(StartYear_), EndYear(EndYear_),
      aWillCalcPDO(aWillCalcPDO_), aWillCalcSafStock(aWillCalcSafStock_), aMRSStartDate(aMRSStartDate_),
      aMRSEndDate(aMRSEndDate_), aMRSMODE(static_cast<TMRPScenarioMode>(aMRSMODE_)),
      aErrorLog(),
      aLoopCount(1), aHasCalcProdinSenario(false), aHasCalcFromCommercial(false), aFirstTime(true),
      aStartDate(), aEndDate(), aPRNIDNotMet(),
      dsCAL(), dsSPN(), dsAIP(), dsPIC(), dsAccum(), dsMRN(), dsBOM(), dsBMA(), pkData(),
      dsFirstScanDataset(), dsHelpDataset(), dsHelpDatasetDetail(), dsHelpDatasetDetailRELPO(), dsPEGGING(),
      dsFromPriorLevel(), dsFromPriorLevelDetail(), dsFromCurrentLevel(), dsFromPrnLevel(), dsFromPrnLevelDetail()
{
    aMrsDayMode = aMRSMODE == mrsmDay;
}

void FASTCALL oPrn::AdjustReadRow()
{
}

ds::Variant FASTCALL oPrn::GetCalendarServiceData()
{
    int     aCalID;

    if ( IsProcuctionLight() )
        aCalID = iDefPDNCALID;
    else
        aCalID = GetParameter_integer( "PDNCALID" );
    if ( aCalID == INVALIDID )
        throw PDNException( rs_NoGeneralCalendarFound );
    return ( GetCALValidDates( aCalID, aStartDate, aEndDate ) );
}

void FASTCALL oPrn::FixConstantDatasets()
{
    if ( aMrsDayMode )
    {
        aStartDate = ds::cDateTime( aMRSStartDate );
        aEndDate = ds::cDateTime( aMRSEndDate );

        ds::Variant     aa = GetCalendarServiceData();
        tblCAL          local_dsCAL;

        ds::cTableWriter::SetTableData( local_dsCAL, aa );
        dsCAL = local_dsCAL.NewIndex( ds::cIndexField( "CALDATE" ) );
    }
    else
    {
        aCanDays = GetCanDays();
        aWeekCount = CheckAndCalcWeekVariables( StartYear, EndYear, StartWeek, EndWeek, aStartDate, aEndDate );
    }
    oBom    bom;
    
    bom.InitBOmCache( dsBOM, dsBMA );
    //
    dsSPN.Open( *Database, 0 );
    dsAIP.Open( *Database, 0 );
    dsPIC.Open( *Database, 0 );

    dsAccum.AddField( "MCIID", ds::fkData, ds::ftInteger, 0 );
    dsAccum.AddField( "DFVCODE1", ds::fkData, ds::ftString, 20 );
    dsAccum.AddField( "DFVCODE2", ds::fkData, ds::ftString, 20 );
    dsAccum.AddField( "DFVCODE3", ds::fkData, ds::ftString, 20 );
    dsAccum.AddField( "DFVCODE4", ds::fkData, ds::ftString, 20 );
    dsAccum.AddField( "DFVCODE5", ds::fkData, ds::ftString, 20 );
    dsAccum.AddField( "DFVCODE6", ds::fkData, ds::ftString, 20 );
    dsAccum.AddField( "DFVCODE7", ds::fkData, ds::ftString, 20 );
    dsAccum.AddField( "WRHQTY", ds::fkData, ds::ftDouble, 0 );

    dsMRN.AddField( "PRNID", ds::fkData, ds::ftInteger, 0 );
    dsMRN.AddField( "MCIID", ds::fkData, ds::ftInteger, 0 );
    dsMRN.AddField( "DFVCODE1", ds::fkData, ds::ftString, 20 );
    dsMRN.AddField( "DFVCODE2", ds::fkData, ds::ftString, 20 );
    dsMRN.AddField( "DFVCODE3", ds::fkData, ds::ftString, 20 );
    dsMRN.AddField( "DFVCODE4", ds::fkData, ds::ftString, 20 );
    dsMRN.AddField( "DFVCODE5", ds::fkData, ds::ftString, 20 );
    dsMRN.AddField( "DFVCODE6", ds::fkData, ds::ftString, 20 );
    dsMRN.AddField( "DFVCODE7", ds::fkData, ds::ftString, 20 );
    dsMRN.AddField( "WEEK", ds::fkData, ds::ftInteger, 0 );
    dsMRN.AddField( "YEAR", ds::fkData, ds::ftInteger, 0 );
    dsMRN.AddField( "DATE", ds::fkData, ds::ftDateTime, 0);  
    dsMRN.AddField( "NEEDEDQTY", ds::fkData, ds::ftDouble, 0 );
    dsMRN.AddField( "EXISTQTY", ds::fkData, ds::ftDouble, 0 );
}

int FASTCALL oPrn::GetCanDays()
{
    int     aCalID;

    if ( IsProcuctionLight() )
        aCalID = iDefPDNCALID;
    else
        aCalID = GetParameter_integer( "PDNCALID" );
    if ( aCalID == INVALIDID )
        throw PDNException( "" );

    //(SEnApplication as ISenSQLBroker).
    //     GetSQLValues('Company',
    //                  Format('SELECT COUNT(*) FROM CAN WHERE CALID = %d', [aCalid]),
    //                  unAssigned,
    //                  aValues);
    //Result := aValues;

    std::ostringstream  qstr( "SELECT COUNT(*) FROM CAN WHERE CALID = " );

    qstr << aCalID;

    ds::cTable  tblTmp;

    tblTmp.AddField( "COUNT", ds::fkData, ds::ftInteger, 0 );
    tblTmp.Open( *Database, qstr.str().c_str() );

    ds::cTable::iterator    tmp_iter = tblTmp.GetIterator();

    return ( tmp_iter.FieldByName( "COUNT" )->AsInteger() );
}

int FASTCALL oPrn::CheckAndCalcWeekVariables( int aStartYear, int aEndYear, int aStartWeek, int aEndWeek,
                                              ds::cDateTime& aStartDate, ds::cDateTime& aEndDate )
{
    // pending
    return ( 0 );
}

void FASTCALL oPrn::FixDatasets()
{
    ds_string   stempWhere;
    // pending
    //stempWhere := AddToWhereClause(EmptyStr, BuildWhereClause('PRNLATEDELIVDATE', '>=', aStartDate));
    //stempWhere := AddToWhereClause(stempWhere, Format('%s < %s', ['PRNLATEDELIVDATE', SQLFormatDateTime(aEndDate+1)]));
    //stempWhere := AddToWhereClause(stempWhere, BuildWhereClause('MPSQUANTITYA', '>', 0));
    //stempWhere := AddToWhereClause(stempWhere, BuildWhereClause('PRNSTATUS', ProductionNeedStatusValues[prnsMPS]));
    stempWhere = AddToWhereClause( "", BuildWhereClause( WhereAtom( "PRNLATEDELIVDATE", ">=", aStartDate ) ) );

    std::ostringstream  where_c( "PRNLATEDELIVDATE" );

    where_c << " < " << SQLFormatDateTime( aEndDate + 1 ).c_str();

    stempWhere = AddToWhereClause( stempWhere, where_c.str().c_str() );
    stempWhere = AddToWhereClause( stempWhere, BuildWhereClause( WhereAtom( "MPSQUANTITYA", ">", 0 ) ) );
    stempWhere = AddToWhereClause( stempWhere, BuildWhereClause( WhereAtom( "PRNSTATUS", ">", ds_string( ProductionNeedStatusValues[prnsMPS] ) ) ) );
    if ( ! aPRNIDNotMet.empty() )
        stempWhere = AddToWhereClause( stempWhere, PDNFormatInSQL( "PRNID NOT IN (%s)", aPRNIDNotMet, "AND" ) );

    pkData.Open( *Database, stempWhere.c_str() ) ;
    tblPRN::iterator    prn_iter = pkData.GetIterator();
    for ( int n = 0 ; n < pkData.RecordCount() ; ++n )
    {
        prn_iter->SetPRNSTARTWEEK( WeekOfYear( prn_iter->GetPRNEARLDELIVDATE() ) );
        prn_iter->SetPRNENDWEEK( WeekOfYear( prn_iter->GetPRNLATEDELIVDATE() ) );
        ++prn_iter;
    }
    dsFirstScanDataset.Clear();
    dsHelpDataset.Clear();
    dsHelpDatasetDetail.Clear();
    dsHelpDatasetDetailRELPO.Clear();
    dsPEGGING.Clear();
    dsFromPriorLevel.Clear();
    dsFromPriorLevelDetail.Clear();
    dsFromCurrentLevel.Clear();
    dsFromPrnLevel.Clear();
    dsFromPrnLevelDetail.Clear();
}

void FASTCALL oPrn::FixPRNEarlDelivDate()
{
    ds::cDateTime   aPRNLATEDELIVDATE;

    tblPRN::iterator    iter = pkData.GetIterator();

    while ( ! iter.eof() )
    {
        aPRNLATEDELIVDATE = CalcNewDateWithLeadTime( dsCAL, iter->GetPRNLATEDELIVDATE(), 0 );
        ++iter;
    }
    pkData.CommitUpdates();
}

ds::cDateTime FASTCALL oPrn::CalcNewDateWithLeadTime( const tblCAL::index_ptr& ds_cal, const ds::cDateTime& aDateTime, int aLEADTIME )
{
    ds::cDateTime       result = aDateTime;
    tblCAL::iterator    cal_iter = ds_cal->Find( aDateTime );

    if ( aLEADTIME == 0 && cal_iter.eof() )
        return ( result );

    ds::cDateTime       aCurDate;

    if ( ! ds_cal->Find( aDateTime, cal_iter ) )
    {
        cal_iter.First();
        aCurDate = cal_iter->GetCALDATE();
        while ( ! cal_iter.eof() )
        {
            if ( cal_iter->GetCALDATE() < aDateTime )
                aCurDate = cal_iter->GetCALDATE();
            else
                break;
            ++cal_iter;
        }
    }
    else
        aCurDate = aDateTime;
    cal_iter = ds_cal->Find( aCurDate );
    if ( aLEADTIME == 0 )
        result = aCurDate;
    else
    {
        for ( int i = 1 ; i <= aLEADTIME ; ++i )
        {
            if ( cal_iter.bof() )
                result -= 1;
            else
            {
                --cal_iter;
                result = cal_iter->GetCALDATE();
            }
        }
    }
    return ( result );
}

ds::Variant FASTCALL oPrn::CheckBOMS()
{
    tblPRN::iterator    prn_iter = pkData.GetIterator();

    while ( ! prn_iter.eof() )
    {
        dsBOM.Locate( prn_iter->GetBOMID(), "BOMID" );
        ++prn_iter;
    }
    return ( Variant() );
}

ds::Variant FASTCALL oPrn::GetDataForFirstScan()
{
    std::vector<TItem>      fItemList;
    tblPRN::iterator        prn_iter = pkData.GetIterator();

    while ( ! prn_iter.eof() )
    {
        int                             aPICID = INVALIDID;
        tblFirstScanDataset::iterator   fsd_iter = dsFirstScanDataset.Locate
            ( 
                OpenValues( prn_iter->GetMCIID(), prn_iter->GetDFVCODE1(), prn_iter->GetDFVCODE2(),
                            prn_iter->GetDFVCODE3(), prn_iter->GetDFVCODE4(), prn_iter->GetDFVCODE5(),
                            prn_iter->GetDFVCODE6(), prn_iter->GetDFVCODE7() ),
                OpenFindFields( "MCIID", "DFVCODE1", "DFVCODE2", "DFVCODE3", "DFVCODE4", "DFVCODE5", "DFVCODE6", "DFVCODE7" )
            );

        if ( ! LocateSucceeded( fsd_iter ) )
        {
            tblSPN::iterator    spn_iter = dsSPN.Locate( prn_iter->GetMCIID(), "MCIID" );

            if ( LocateSucceeded( spn_iter ) )
            {
                tblFirstScanDataset::record     fsd_new = dsFirstScanDataset.NewRecord();

                fsd_new->SetMCIID( prn_iter->GetMCIID() ); 
                fsd_new->SetDFVCODE1( prn_iter->GetDFVCODE1() ); 
                fsd_new->SetDFVCODE2( prn_iter->GetDFVCODE2() ); 
                fsd_new->SetDFVCODE3( prn_iter->GetDFVCODE3() ); 
                fsd_new->SetDFVCODE4( prn_iter->GetDFVCODE4() ); 
                fsd_new->SetDFVCODE5( prn_iter->GetDFVCODE5() ); 
                fsd_new->SetDFVCODE6( prn_iter->GetDFVCODE6() ); 
                fsd_new->SetDFVCODE7( prn_iter->GetDFVCODE7() );
                fsd_new->SetLLC( spn_iter->GetSPNLLC() );

                tblAIP::iterator    aip_iter = dsAIP.Locate
                    ( 
                        OpenValues( prn_iter->GetMCIID(), prn_iter->GetDFVCODE1(), prn_iter->GetDFVCODE2(),
                                    prn_iter->GetDFVCODE3(), prn_iter->GetDFVCODE4(), prn_iter->GetDFVCODE5(),
                                    prn_iter->GetDFVCODE6(), prn_iter->GetDFVCODE7() ),
                        OpenFindFields( "MCIID", "DFVCODE1", "DFVCODE2", "DFVCODE3", "DFVCODE4", "DFVCODE5", "DFVCODE6", "DFVCODE7" )
                    );

                if ( LocateSucceeded( aip_iter ) )
                    aPICID = aip_iter->GetPICID();
                if ( aPICID == INVALIDID )
                    aPICID = spn_iter->GetPICID();
                if ( aPICID != INVALIDID )
                {
                    tblPIC::iterator    pic_iter = dsPIC.Locate( aPICID, cFindField( "PICID" ) );

                    fsd_new->SetLOTSIZE( pic_iter->GetPICLOTQTY() );
                    fsd_new->SetLEADTIME( pic_iter->GetPICLEADTIME() );
                    fsd_new->SetSAFETYSTOCK( aWillCalcSafStock ? pic_iter->GetPICQTYSAFETYSTOCK() : 0 );
                    fsd_new->SetLOTPOLICY( pic_iter->GetPICLOTPOLICY() );
                }
                else
                {
                    fsd_new->SetLOTSIZE( 0 );
                    fsd_new->SetLEADTIME( 0 );
                    fsd_new->SetSAFETYSTOCK( 0 );
                    fsd_new->SetLOTPOLICY( 0 );
                }
                dsFirstScanDataset.AddRecord( fsd_new );
            }
            else
            {
                fItemList.push_back( TItem( prn_iter->GetMCIID(), prn_iter->GetDFVCODE1(), prn_iter->GetDFVCODE2(),
                                            prn_iter->GetDFVCODE3(), prn_iter->GetDFVCODE4(), prn_iter->GetDFVCODE5(),
                                            prn_iter->GetDFVCODE6(), prn_iter->GetDFVCODE7() ) );
            }
        }
        ++prn_iter;
    }
    oBom    bom;

    bom.FixDataset( dsFirstScanDataset, true, dsWholeStructure );

    return ( Variant() );
}

bool FASTCALL oPrn::DoCalculateMRPSchedulingForAPeriod()
{
    FixConstantDatasets();
    aCurrentCount = 1;
    aNextCount = 0;
    while ( aCurrentCount != aNextCount )
    {
        aCurrentCount = aNextCount;
        try
        {
            FixDatasets();
            if ( aMrsDayMode )
                FixPRNEarlDelivDate();
            if ( aFirstTime )
            {
                aFirstTime = false;
                aErrorLog = CheckBOMS();
                if ( ! aErrorLog.IsNull() )
                    return ( false );
            }
            aErrorLog = GetDataForFirstScan();
            if ( ! aErrorLog.IsNull() )
                return ( false );
        }
        catch ( const PDNCycle& )
        {
            aNextCount = aPRNIDNotMet.size();
            ++aLoopCount;
        }
    }

    return ( true );
}
