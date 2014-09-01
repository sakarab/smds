#include "oCal.hpp"
#include "main_dll.hpp"
#include <vector>
#include "uSub.h"
#include "uCustomTables.h"

using namespace ds;

Variant FASTCALL GetCALValidDates( int aCALID, const cDateTime& aDateFrom, const cDateTime& aDateTo )
{
    if ( aCALID == 0 )
        return ( Variant() );

    cDateTime           aStartDate = aDateFrom.Date(),
                        aEndDate = aDateTo.Date();

    tblCAN                              cdsCAN;
    cdsCAN.Open( *Database, 0 );
    tblCAN::index_ptr                   cdsCAN_idx = cdsCAN.NewIndex( cIndexField( "CALID" ) );
    tblCAN::index::range_iterator       can_iter = cdsCAN_idx->GetRangeIterator( cRangeValues( aCALID, aCALID ) );

    tblCEX                              cdsCEX;
    cdsCEX.Open( *Database, 0 );
    tblCEX::index_ptr                   cdsCEX_idx = cdsCEX.NewIndex( cIndexField( "CALID" ) );
    tblCEX::index::range_iterator       cex_iter = cdsCEX_idx->GetRangeIterator( cRangeValues( aCALID, aCALID ) );

    tblHLD                              cdsHLD;
    cdsHLD.Open( *Database, 0 ); // (Session.CreateObject('THolidaysSrv') as ISEnServerPDC).LoadRecords('') 

    tblCAL                              dsCAL;
    cDateTime                           aCurrentDate = aStartDate;
    tblHLD::iterator                    hld_iter = cdsHLD.GetIterator();

    while ( aCurrentDate <= aEndDate )
    {
        if ( ! cdsHLD.Locate( aCurrentDate, "HLDDATE", hld_iter ) &&
             ! cdsCEX.Locate( aCurrentDate, "CEXDATE", cex_iter ) )
        {
            cDateTime   aCurrentWeekDay = DayOfWeek( aCurrentDate );

            if ( cdsCAN.Locate( aCurrentWeekDay, "CANDAY", can_iter ) )
            {
                tblCAL::record      new_rec = dsCAL.NewRecord();

                new_rec->SetCALDATE( aCurrentDate );
            }
        }
        aCurrentDate = aCurrentDate.AsDouble() + 1;
    }
    return ( cTableReader::GetTablePacket( dsCAL ) );
}
