#ifndef PRN_OPRN_HPP
#define PRN_OPRN_HPP

#include <dsConfig.h>
#include <ssport.h>
#include <dsDateTime.h>
#include <dsVariant.h>
#include <dsData.h>
#include "uTables.h"
#include "uCustomTables.h"

class oPrn
{
private:
    enum      TMRPScenarioMode { mrsmNull, mrsmWeek, mrsmDay };
private:
    int                 StartWeek, EndWeek;
    unsigned short      StartYear, EndYear;
    bool                aWillCalcPDO, aWillCalcSafStock;
    double              aMRSStartDate, aMRSEndDate;         // TDateTime
    TMRPScenarioMode    aMRSMODE;                           // TMRPScenarioMode
    ds::Variant         aErrorLog;                          // out aErrorLog : variant;
    // Globals - lazy initialized
    bool                aMrsDayMode;
    int                 aCanDays, aWeekCount;
    int                 aCurrentCount, aNextCount;
    // Globals - properly initialized
    int                 aLoopCount;
    bool                aHasCalcProdinSenario, aHasCalcFromCommercial, aFirstTime;
    ds::cDateTime       aStartDate, aEndDate;
    std::vector<int>    aPRNIDNotMet;
    tblCAL::index_ptr   dsCAL;
    tblSPN              dsSPN;
    tblAIP              dsAIP;
    tblPIC              dsPIC;
    ds::cTable          dsAccum;
    ds::cTable          dsMRN;
    tblBOM              dsBOM;
    tblBMA              dsBMA;
    tblPRN                      pkData;
    tblFirstScanDataset         dsFirstScanDataset;
    tblHelpDataset              dsHelpDataset;
    tblHelpDatasetDetail        dsHelpDatasetDetail;
    tblHelpDatasetDetailRELPO   dsHelpDatasetDetailRELPO;
    tblPEGGING                  dsPEGGING;
    tblFromPriorLevel           dsFromPriorLevel;
    tblFromPriorLevelDetail     dsFromPriorLevelDetail;
    tblFromCurrentLevel         dsFromCurrentLevel;
    tblFromPrnLevel             dsFromPrnLevel;
    tblFromPrnLevelDetail       dsFromPrnLevelDetail;
    ds::cIndex_ptr              dsWholeStructure;

    ds::Variant FASTCALL GetCalendarServiceData();
    void FASTCALL FixConstantDatasets();
    void FASTCALL FixDatasets();
    void FASTCALL FixPRNEarlDelivDate();
    ds::cDateTime FASTCALL CalcNewDateWithLeadTime( const tblCAL::index_ptr& ds_cal, const ds::cDateTime& aDateTime, int aLEADTIME );
    ds::Variant FASTCALL CheckBOMS();
    ds::Variant FASTCALL GetDataForFirstScan();
    int FASTCALL GetCanDays();
    int FASTCALL CheckAndCalcWeekVariables( int aStartYear, int aEndYear, int aStartWeek, int aEndWeek,
                                            ds::cDateTime& aStartDate, ds::cDateTime& aEndDate );
    // PDC support
    void FASTCALL AdjustReadRow();
public:
    CDFASTCALL oPrn( int StartWeek_, int EndWeek_,
                     unsigned short StartYear_, unsigned short EndYear_,
                     bool aWillCalcPDO_, bool aWillCalcSafStock_,
                     double aMRSStartDate_, double aMRSEndDate_,    // TDateTime
                     int aMRSMODE_                                  // TMRPScenarioMode
                   );
    bool FASTCALL DoCalculateMRPSchedulingForAPeriod();
};

#endif