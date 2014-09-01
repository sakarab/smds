#ifndef PRN_OBOM_HPP
#define PRN_OBOM_HPP

#include <dsConfig.h>
#include <ssport.h>
#include "uTables.h"
#include "uCustomTables.h"
#include "uSub.h"

// has no AdjustReadRow
class oBom
{
private:
    //tblBOM              pkData;
    ds_string           fMessage;
    std::vector<int>    fItemList;
public:
    CDFASTCALL oBom();
    void FASTCALL GetData( tblBOM& ds_bom, tblBMA& ds_bma, const char * where_clause );
    void FASTCALL InitBOmCache( tblBOM& ds_bom, tblBMA& ds_bma );
    void FASTCALL FixClientDataset( ds::cTable& tbl );
    void FASTCALL FixDataset( tblFirstScanDataset& dsMCIFromClient, bool direction, ds::cIndex_ptr& out );
    void FASTCALL FixDatasetDown( TItem aItem, ds::cTable& dsClientData, bool aBOMCalculation, int& aParentID,
                                  bool aPutInCycle, int aUNIIDA, int aUNIIDB, tblBOM& pkData );
    bool FASTCALL CheckItemInCycle( const TItem& aItem );
    ds::cTable::iterator FASTCALL InsertInDatasetsDown( bool aBOMInsertion, int aParentID, ds::cTable& dsClientData, const TItem& aItem,
                                                        bool aPutInCycle, int aUniidA, int aUniidB, tblBOM& pkData );
};

#endif
