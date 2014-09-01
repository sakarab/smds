#include "oPrn.hpp"
#include <dsData.h>

//this is simply to test the transfer procedure with C++builder
//#include "oCal.hpp"

ds::cDatabase   *Database;

extern "C"
{

#ifdef _MSC_VER
__declspec(dllexport)
#endif
bool CalculateMRPSchedulingForAPeriod
            (
                int StartWeek, int EndWeek,
                unsigned short StartYear, unsigned short EndYear,
                bool aWillCalcPDO, bool aWillCalcSafStock,
                double aMRSStartDate, double aMRSEndDate,    // TDateTime
                int aMRSMODE                                 // TMRPScenarioMode
            ) 
{
    ds::cDbEngine       transport = ds::SelectDbEngine( "SAS" );
    ds::cDatabase       connection = transport.NewConnection( "COMPANY" );

    Database = &connection;

    //this is simply to test the transfer procedure with C++builder
    //GetCALValidDates( -1, ds::cDateTime( aMRSStartDate ), ds::cDateTime( aMRSEndDate ) );

    oPrn    prn( StartWeek, EndWeek, StartYear, EndYear, aWillCalcPDO, aWillCalcSafStock,
                 aMRSStartDate, aMRSEndDate, aMRSMODE );

    return prn.DoCalculateMRPSchedulingForAPeriod();
}

};
