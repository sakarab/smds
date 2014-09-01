#ifndef PRN_OCAL_HPP
#define PRN_OCAL_HPP

#include <dsConfig.h>
#include <ssport.h>
#include "uTables.h"

ds::Variant FASTCALL GetCALValidDates( int aCALID, const ds::cDateTime& aDateFrom,
                                       const ds::cDateTime& aDateTo );

#endif