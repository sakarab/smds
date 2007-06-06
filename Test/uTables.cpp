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

#include "uTables.h"
//---------------------------------------------------------------------------

using namespace smds;
using namespace smds::detail;

//***********************************************************************
//******    tblLocation
//***********************************************************************
const cFieldDef_     tblLocation_data::tblLocation_Fields[] =
{
    { 0, offsetof(tblLocation_map,LocationID_), "LocationID", fkData, ftInteger,  4 },
    { 1, offsetof(tblLocation_map,LocTypeID_),  "LocTypeID",  fkData, ftShort,    2 },
    { 2, offsetof(tblLocation_map,IsUser_),     "IsUser",     fkData, ftShort,    2 },
    { 3, offsetof(tblLocation_map,SerialNo_),   "SerialNo",   fkData, ftInteger,  4 },
    { 4, offsetof(tblLocation_map,Drive_),      "Drive",      fkData, ftString,   4 }
};

const cFieldDefs_    tblLocation_data::tblLocation_FieldDef =
{
    sizeof(tblLocation_map),
    sizeof(tblLocation_Fields)/sizeof(tblLocation_Fields[0]),
    //"SELECT LocationID, LocTypeID, IsUser, SerialNo, Drive FROM %s %s",
    "LocationID, LocTypeID, IsUser, SerialNo, Drive",
    "tblLocation",
    tblLocation_Fields
};

const cFieldDefs_& FASTCALL tblLocation_rec::GetFieldDefs()             { return ( tblLocation_FieldDef ); }

//***********************************************************************
//******    tblFiles
//***********************************************************************
const cFieldDef_     tblFiles_data::tblFiles_Fields[] =
{
    { 0, offsetof(tblFiles_map,FileID_),       "FileID",       fkData, ftInteger,    4 },
    { 1, offsetof(tblFiles_map,PathID_),       "PathID",       fkData, ftInteger,    4 },
    { 2, offsetof(tblFiles_map,LongFileName_), "LongFileName", fkData, ftString,   255 },
    { 3, offsetof(tblFiles_map,fSize_),        "fSize",        fkData, ftInteger,    4 },
    { 4, offsetof(tblFiles_map,fDate_),        "fDate",        fkData, ftDateTime,   8 },
    { 5, offsetof(tblFiles_map,Description_),  "Description",  fkData, ftString,   255 },
    { 6, offsetof(tblFiles_map,zipID_),        "zipID",        fkData, ftInteger,    4 },
};

const cFieldDefs_    tblFiles_data::tblFiles_FieldDef =
{
    sizeof(tblFiles_map),
    sizeof(tblFiles_Fields)/sizeof(tblFiles_Fields[0]),
    //"SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s",
    "SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM tblFiles",
    "tblFiles",
    tblFiles_Fields
};

const cFieldDefs_& FASTCALL tblFiles_rec::GetFieldDefs()                    { return ( tblFiles_FieldDef ); }

/*
int FASTCALL tblFiles_rec::GetFileID() const                                { return ( ReadInteger( tblFiles_Fields[0] ) ); }
void FASTCALL tblFiles_rec::SetFileID( int value )                          { WriteInteger( tblFiles_Fields[0], value ); }
int FASTCALL tblFiles_rec::GetPathID() const                                { return ( ReadInteger( tblFiles_Fields[1] ) ); }
void FASTCALL tblFiles_rec::SetPathID( int value )                          { WriteInteger( tblFiles_Fields[1], value ); }
ds_string FASTCALL tblFiles_rec::GetLongFileName() const                    { return ( ReadString( tblFiles_Fields[2] ) ); }
void FASTCALL tblFiles_rec::SetLongFileName( const ds_string& value )       { WriteString( tblFiles_Fields[2], value ); }
void FASTCALL tblFiles_rec::SetLongFileName( const char *value )            { WriteString( tblFiles_Fields[2], value ); }
int  FASTCALL tblFiles_rec::GetfSize() const                                { return ( ReadInteger( tblFiles_Fields[3] ) ); }
void FASTCALL tblFiles_rec::SetfSize( int value )                           { WriteInteger( tblFiles_Fields[3], value ); }
ds::cDateTime FASTCALL tblFiles_rec::GetfDate() const                       { return ( ReadDate( tblFiles_Fields[4] ) ); }
void FASTCALL tblFiles_rec::SetfDate( const ds::cDateTime& value )          { WriteDate( tblFiles_Fields[4], value ); }
ds_string FASTCALL tblFiles_rec::GetDescription() const                     { return ( ReadString( tblFiles_Fields[5] ) ); }
void FASTCALL tblFiles_rec::SetDescription( const ds_string& value )        { WriteString( tblFiles_Fields[5], value ); }
void FASTCALL tblFiles_rec::SetDescription( const char *value )             { WriteString( tblFiles_Fields[5], value ); }
int  FASTCALL tblFiles_rec::GetzipID() const                                { return ( ReadInteger( tblFiles_Fields[6] ) ); }
void FASTCALL tblFiles_rec::SetzipID( int value )                           { WriteInteger( tblFiles_Fields[6], value ); }
*/

//***********************************************************************
//******    tblSLD
//***********************************************************************
/*
const smds::cFieldDef_  tblSLD_data::tblSLD_Fields[] =
{
    {   0,  offsetof(tblSLD_map,DOCID_),                        "DOCID",                        smds::fkData,  smds::ftInteger,      4 },
    {   1,  offsetof(tblSLD_map,DOTID_),                        "DOTID",                        smds::fkData,  smds::ftInteger,      4 },
    {   2,  offsetof(tblSLD_map,FIYID_),                        "FIYID",                        smds::fkData,  smds::ftInteger,      4 },
    {   3,  offsetof(tblSLD_map,PERID_),                        "PERID",                        smds::fkData,  smds::ftInteger,      4 },
    {   4,  offsetof(tblSLD_map,DOSID_),                        "DOSID",                        smds::fkData,  smds::ftInteger,      4 },
    {   5,  offsetof(tblSLD_map,DOSCODE_),                      "DOSCODE",                      smds::fkData,  smds::ftString,       4 },
    {   6,  offsetof(tblSLD_map,DOCNUMBER_),                    "DOCNUMBER",                    smds::fkData,  smds::ftInteger,      4 },
    {   7,  offsetof(tblSLD_map,DOCJRNAA_),                     "DOCJRNAA",                     smds::fkData,  smds::ftInteger,      4 },
    {   8,  offsetof(tblSLD_map,DOCKATAHORISISDATE_),           "DOCKATAHORISISDATE",           smds::fkData,  smds::ftDateTime,     8 },
    {   9,  offsetof(tblSLD_map,DOCENIMEROSISDATE_),            "DOCENIMEROSISDATE",            smds::fkData,  smds::ftDateTime,     8 },
    {  10,  offsetof(tblSLD_map,DOCEKDOSISDATE_),               "DOCEKDOSISDATE",               smds::fkData,  smds::ftDateTime,     8 },
    {  11,  offsetof(tblSLD_map,DOCREASON_),                    "DOCREASON",                    smds::fkData,  smds::ftString,     100 },
    {  12,  offsetof(tblSLD_map,DOCCOMMENT_),                   "DOCCOMMENT",                   smds::fkData,  smds::ftString,     255 },
    {  13,  offsetof(tblSLD_map,DOCCANENIM_),                   "DOCCANENIM",                   smds::fkData,  smds::ftShort,        2 },
    {  14,  offsetof(tblSLD_map,DOCCANCANCEL_),                 "DOCCANCANCEL",                 smds::fkData,  smds::ftShort,        2 },
    {  15,  offsetof(tblSLD_map,DOCCANCELSTATUS_),              "DOCCANCELSTATUS",              smds::fkData,  smds::ftString,       1 },
    {  16,  offsetof(tblSLD_map,DOCIDAKIROMENO_),               "DOCIDAKIROMENO",               smds::fkData,  smds::ftInteger,      4 },
    {  17,  offsetof(tblSLD_map,DOCIDAKIROTIKO_),               "DOCIDAKIROTIKO",               smds::fkData,  smds::ftInteger,      4 },
    {  18,  offsetof(tblSLD_map,DMIID_),                        "DMIID",                        smds::fkData,  smds::ftInteger,      4 },
    {  19,  offsetof(tblSLD_map,TDOGROSSRETAIL_),               "TDOGROSSRETAIL",               smds::fkData,  smds::ftShort,        2 },
    {  20,  offsetof(tblSLD_map,TDOOTHERNUMBER_),               "TDOOTHERNUMBER",               smds::fkData,  smds::ftString,      20 },
    {  21,  offsetof(tblSLD_map,TDOOTHERDATE_),                 "TDOOTHERDATE",                 smds::fkData,  smds::ftDateTime,     8 },
    {  22,  offsetof(tblSLD_map,TDOEKTELESISDATE_),             "TDOEKTELESISDATE",             smds::fkData,  smds::ftDateTime,     8 },
    {  23,  offsetof(tblSLD_map,DSTDESCR_),                     "DSTDESCR",                     smds::fkData,  smds::ftString,      50 },
    {  24,  offsetof(tblSLD_map,PPSDESCR_),                     "PPSDESCR",                     smds::fkData,  smds::ftString,      50 },
    {  25,  offsetof(tblSLD_map,ORGDESCR_),                     "ORGDESCR",                     smds::fkData,  smds::ftString,      50 },
    {  26,  offsetof(tblSLD_map,TPMID_),                        "TPMID",                        smds::fkData,  smds::ftInteger,      4 },
    {  27,  offsetof(tblSLD_map,TPTID_),                        "TPTID",                        smds::fkData,  smds::ftInteger,      4 },
    {  28,  offsetof(tblSLD_map,SHVID_),                        "SHVID",                        smds::fkData,  smds::ftInteger,      4 },
    {  29,  offsetof(tblSLD_map,WRHID_),                        "WRHID",                        smds::fkData,  smds::ftInteger,      4 },
    {  30,  offsetof(tblSLD_map,TRAID_),                        "TRAID",                        smds::fkData,  smds::ftInteger,      4 },
    {  31,  offsetof(tblSLD_map,TXOCODE_),                      "TXOCODE",                      smds::fkData,  smds::ftString,       4 },
    {  32,  offsetof(tblSLD_map,TDOTRANSPORTREMARKS_),          "TDOTRANSPORTREMARKS",          smds::fkData,  smds::ftString,     255 },
    {  33,  offsetof(tblSLD_map,ADRIDLOGISTIRIOU_),             "ADRIDLOGISTIRIOU",             smds::fkData,  smds::ftInteger,      4 },
    {  34,  offsetof(tblSLD_map,ADRIDPROORISMOU_),              "ADRIDPROORISMOU",              smds::fkData,  smds::ftInteger,      4 },
    {  35,  offsetof(tblSLD_map,TDOSENDTIME_),                  "TDOSENDTIME",                  smds::fkData,  smds::ftDateTime,     8 },
    {  36,  offsetof(tblSLD_map,TDOVATSTATUS_),                 "TDOVATSTATUS",                 smds::fkData,  smds::ftString,       9 },
    {  37,  offsetof(tblSLD_map,TDOLEEAFM_),                    "TDOLEEAFM",                    smds::fkData,  smds::ftString,      12 },
    {  38,  offsetof(tblSLD_map,TDOLEEADT_),                    "TDOLEEADT",                    smds::fkData,  smds::ftString,      20 },
    {  39,  offsetof(tblSLD_map,TDOLEEADTKIND_),                "TDOLEEADTKIND",                smds::fkData,  smds::ftString,       2 },
    {  40,  offsetof(tblSLD_map,TDOADDRESS_),                   "TDOADDRESS",                   smds::fkData,  smds::ftString,     100 },
    {  41,  offsetof(tblSLD_map,CURID_),                        "CURID",                        smds::fkData,  smds::ftInteger,      4 },
    {  42,  offsetof(tblSLD_map,TDOEQVTYPE_),                   "TDOEQVTYPE",                   smds::fkData,  smds::ftString,       1 },
    {  43,  offsetof(tblSLD_map,TDOEQUIVALENCE_),               "TDOEQUIVALENCE",               smds::fkData,  smds::ftDouble,       8 },
    {  44,  offsetof(tblSLD_map,TDODUEDAYS_),                   "TDODUEDAYS",                   smds::fkData,  smds::ftInteger,      4 },
    {  45,  offsetof(tblSLD_map,TDOGRACEDAYS_),                 "TDOGRACEDAYS",                 smds::fkData,  smds::ftInteger,      4 },
    {  46,  offsetof(tblSLD_map,SLMID_),                        "SLMID",                        smds::fkData,  smds::ftInteger,      4 },
    {  47,  offsetof(tblSLD_map,TDOTRADERDISCPCNT_),            "TDOTRADERDISCPCNT",            smds::fkData,  smds::ftDouble,       8 },
    {  48,  offsetof(tblSLD_map,TDOQTYA_),                      "TDOQTYA",                      smds::fkData,  smds::ftDouble,       8 },
    {  49,  offsetof(tblSLD_map,TDOQTYB_),                      "TDOQTYB",                      smds::fkData,  smds::ftDouble,       8 },
    {  50,  offsetof(tblSLD_map,TDOTRANSFQTYA_),                "TDOTRANSFQTYA",                smds::fkData,  smds::ftDouble,       8 },
    {  51,  offsetof(tblSLD_map,TDOTRANSFQTYB_),                "TDOTRANSFQTYB",                smds::fkData,  smds::ftDouble,       8 },
    {  52,  offsetof(tblSLD_map,TDOQTYDISCA_),                  "TDOQTYDISCA",                  smds::fkData,  smds::ftDouble,       8 },
    {  53,  offsetof(tblSLD_map,TDOQTYDISCB_),                  "TDOQTYDISCB",                  smds::fkData,  smds::ftDouble,       8 },
    {  54,  offsetof(tblSLD_map,TDOTRADERDISC_),                "TDOTRADERDISC",                smds::fkData,  smds::ftDouble,       8 },
    {  55,  offsetof(tblSLD_map,TDOTRADERDISCBC_),              "TDOTRADERDISCBC",              smds::fkData,  smds::ftDouble,       8 },
    {  56,  offsetof(tblSLD_map,TDOPAYMENTDISC_),               "TDOPAYMENTDISC",               smds::fkData,  smds::ftDouble,       8 },
    {  57,  offsetof(tblSLD_map,TDOPAYMENTDISCBC_),             "TDOPAYMENTDISCBC",             smds::fkData,  smds::ftDouble,       8 },
    {  58,  offsetof(tblSLD_map,TDOSTOCKDISC_),                 "TDOSTOCKDISC",                 smds::fkData,  smds::ftDouble,       8 },
    {  59,  offsetof(tblSLD_map,TDOSTOCKDISCBC_),               "TDOSTOCKDISCBC",               smds::fkData,  smds::ftDouble,       8 },
    {  60,  offsetof(tblSLD_map,TDOPRICELISTDISC_),             "TDOPRICELISTDISC",             smds::fkData,  smds::ftDouble,       8 },
    {  61,  offsetof(tblSLD_map,TDOPRICELISTDISCBC_),           "TDOPRICELISTDISCBC",           smds::fkData,  smds::ftDouble,       8 },
    {  62,  offsetof(tblSLD_map,TDOEXTRADISC_),                 "TDOEXTRADISC",                 smds::fkData,  smds::ftDouble,       8 },
    {  63,  offsetof(tblSLD_map,TDOEXTRADISCBC_),               "TDOEXTRADISCBC",               smds::fkData,  smds::ftDouble,       8 },
    {  64,  offsetof(tblSLD_map,TDONETSTOCK_),                  "TDONETSTOCK",                  smds::fkData,  smds::ftDouble,       8 },
    {  65,  offsetof(tblSLD_map,TDONETSTOCKBC_),                "TDONETSTOCKBC",                smds::fkData,  smds::ftDouble,       8 },
    {  66,  offsetof(tblSLD_map,TDONETGIFT_),                   "TDONETGIFT",                   smds::fkData,  smds::ftDouble,       8 },
    {  67,  offsetof(tblSLD_map,TDONETGIFTBC_),                 "TDONETGIFTBC",                 smds::fkData,  smds::ftDouble,       8 },
    {  68,  offsetof(tblSLD_map,TDONETSURCHARGE_),              "TDONETSURCHARGE",              smds::fkData,  smds::ftDouble,       8 },
    {  69,  offsetof(tblSLD_map,TDONETSURCHARGEBC_),            "TDONETSURCHARGEBC",            smds::fkData,  smds::ftDouble,       8 },
    {  70,  offsetof(tblSLD_map,TDONETOTHER_),                  "TDONETOTHER",                  smds::fkData,  smds::ftDouble,       8 },
    {  71,  offsetof(tblSLD_map,TDONETOTHERBC_),                "TDONETOTHERBC",                smds::fkData,  smds::ftDouble,       8 },
    {  72,  offsetof(tblSLD_map,TDONETTAX_),                    "TDONETTAX",                    smds::fkData,  smds::ftDouble,       8 },
    {  73,  offsetof(tblSLD_map,TDONETTAXBC_),                  "TDONETTAXBC",                  smds::fkData,  smds::ftDouble,       8 },
    {  74,  offsetof(tblSLD_map,TDOGROSSVALUE_),                "TDOGROSSVALUE",                smds::fkData,  smds::ftDouble,       8 },
    {  75,  offsetof(tblSLD_map,TDOGROSSVALUEBC_),              "TDOGROSSVALUEBC",              smds::fkData,  smds::ftDouble,       8 },
    {  76,  offsetof(tblSLD_map,TDOVATSTOCK_),                  "TDOVATSTOCK",                  smds::fkData,  smds::ftDouble,       8 },
    {  77,  offsetof(tblSLD_map,TDOVATSTOCKBC_),                "TDOVATSTOCKBC",                smds::fkData,  smds::ftDouble,       8 },
    {  78,  offsetof(tblSLD_map,TDOVATGIFT_),                   "TDOVATGIFT",                   smds::fkData,  smds::ftDouble,       8 },
    {  79,  offsetof(tblSLD_map,TDOVATGIFTBC_),                 "TDOVATGIFTBC",                 smds::fkData,  smds::ftDouble,       8 },
    {  80,  offsetof(tblSLD_map,TDOVATSURCHARGE_),              "TDOVATSURCHARGE",              smds::fkData,  smds::ftDouble,       8 },
    {  81,  offsetof(tblSLD_map,TDOVATSURCHARGEBC_),            "TDOVATSURCHARGEBC",            smds::fkData,  smds::ftDouble,       8 },
    {  82,  offsetof(tblSLD_map,TDOVATOTHER_),                  "TDOVATOTHER",                  smds::fkData,  smds::ftDouble,       8 },
    {  83,  offsetof(tblSLD_map,TDOVATOTHERBC_),                "TDOVATOTHERBC",                smds::fkData,  smds::ftDouble,       8 },
    {  84,  offsetof(tblSLD_map,TDOVATTAX_),                    "TDOVATTAX",                    smds::fkData,  smds::ftDouble,       8 },
    {  85,  offsetof(tblSLD_map,TDOVATTAXBC_),                  "TDOVATTAXBC",                  smds::fkData,  smds::ftDouble,       8 },
    {  86,  offsetof(tblSLD_map,PTPIDPAYMENT_),                 "PTPIDPAYMENT",                 smds::fkData,  smds::ftInteger,      4 },
    {  87,  offsetof(tblSLD_map,PMTIDPAYMENT_),                 "PMTIDPAYMENT",                 smds::fkData,  smds::ftInteger,      4 },
    {  88,  offsetof(tblSLD_map,DOCIDPAYMENT_),                 "DOCIDPAYMENT",                 smds::fkData,  smds::ftInteger,      4 },
    {  89,  offsetof(tblSLD_map,TDOPAYMENT_),                   "TDOPAYMENT",                   smds::fkData,  smds::ftDouble,       8 },
    {  90,  offsetof(tblSLD_map,TDOPAYMENTBC_),                 "TDOPAYMENTBC",                 smds::fkData,  smds::ftDouble,       8 },
    {  91,  offsetof(tblSLD_map,TDONETKRATISI_),                "TDONETKRATISI",                smds::fkData,  smds::ftDouble,       8 },
    {  92,  offsetof(tblSLD_map,TDONETKRATISIBC_),              "TDONETKRATISIBC",              smds::fkData,  smds::ftDouble,       8 },
    {  93,  offsetof(tblSLD_map,TDOTRADERBALANCEBEFORE_),       "TDOTRADERBALANCEBEFORE",       smds::fkData,  smds::ftDouble,       8 },
    {  94,  offsetof(tblSLD_map,TDOTRADERBALANCEAFTER_),        "TDOTRADERBALANCEAFTER",        smds::fkData,  smds::ftDouble,       8 },
    {  95,  offsetof(tblSLD_map,TDOCANTRANSF_),                 "TDOCANTRANSF",                 smds::fkData,  smds::ftShort,        2 },
    {  96,  offsetof(tblSLD_map,TDOADVANCE_),                   "TDOADVANCE",                   smds::fkData,  smds::ftDouble,       8 },
    {  97,  offsetof(tblSLD_map,TDOADVANCEBC_),                 "TDOADVANCEBC",                 smds::fkData,  smds::ftDouble,       8 },
    {  98,  offsetof(tblSLD_map,TDOADVANCEUSAGE_),              "TDOADVANCEUSAGE",              smds::fkData,  smds::ftDouble,       8 },
    {  99,  offsetof(tblSLD_map,TDOADVANCEUSAGEBC_),            "TDOADVANCEUSAGEBC",            smds::fkData,  smds::ftDouble,       8 },
    { 100,  offsetof(tblSLD_map,CDZID_),                        "CDZID",                        smds::fkData,  smds::ftInteger,      4 },
    { 101,  offsetof(tblSLD_map,PTPIDDOCTYPE_),                 "PTPIDDOCTYPE",                 smds::fkData,  smds::ftInteger,      4 },
    { 102,  offsetof(tblSLD_map,LEEIDRECEIVER_),                "LEEIDRECEIVER",                smds::fkData,  smds::ftInteger,      4 },
    { 103,  offsetof(tblSLD_map,ADRIDRECEIVER_),                "ADRIDRECEIVER",                smds::fkData,  smds::ftInteger,      4 },
    { 104,  offsetof(tblSLD_map,PMTIDADVANCE_),                 "PMTIDADVANCE",                 smds::fkData,  smds::ftInteger,      4 },
    { 105,  offsetof(tblSLD_map,DOCIDADVANCE_),                 "DOCIDADVANCE",                 smds::fkData,  smds::ftInteger,      4 },
    { 106,  offsetof(tblSLD_map,TDOPAYMENTDISCPCNT_),           "TDOPAYMENTDISCPCNT",           smds::fkData,  smds::ftDouble,       8 },
    { 107,  offsetof(tblSLD_map,TTYIDTRADER_),                  "TTYIDTRADER",                  smds::fkData,  smds::ftInteger,      4 },
    { 108,  offsetof(tblSLD_map,TTYIDSALESMAN_),                "TTYIDSALESMAN",                smds::fkData,  smds::ftInteger,      4 },
    { 109,  offsetof(tblSLD_map,TTYIDSTOCKITEM_),               "TTYIDSTOCKITEM",               smds::fkData,  smds::ftInteger,      4 },
    { 110,  offsetof(tblSLD_map,TDOVATINCLUDED_),               "TDOVATINCLUDED",               smds::fkData,  smds::ftShort,        2 },
    { 111,  offsetof(tblSLD_map,PTPIDTRADER_),                  "PTPIDTRADER",                  smds::fkData,  smds::ftInteger,      4 },
    { 112,  offsetof(tblSLD_map,SYS_USRID_),                    "SYS_USRID",                    smds::fkData,  smds::ftInteger,      4 },
    { 113,  offsetof(tblSLD_map,SYS_LUPD_),                     "SYS_LUPD",                     smds::fkData,  smds::ftDateTime,     8 },
    { 114,  offsetof(tblSLD_map,SYS_INS_),                      "SYS_INS",                      smds::fkData,  smds::ftDateTime,     8 },
    { 115,  offsetof(tblSLD_map,TDOKEEPPRICESTRANSF_),          "TDOKEEPPRICESTRANSF",          smds::fkData,  smds::ftString,       4 },
    { 116,  offsetof(tblSLD_map,TDOTRADERBALANCEBEFOREBC_),     "TDOTRADERBALANCEBEFOREBC",     smds::fkData,  smds::ftDouble,       8 },
    { 117,  offsetof(tblSLD_map,TDOTRADERBALANCEAFTERBC_),      "TDOTRADERBALANCEAFTERBC",      smds::fkData,  smds::ftDouble,       8 },
    { 118,  offsetof(tblSLD_map,SLMIDCOLLECTOR_),               "SLMIDCOLLECTOR",               smds::fkData,  smds::ftInteger,      4 },
    { 119,  offsetof(tblSLD_map,DOCIDPREDICTION_),              "DOCIDPREDICTION",              smds::fkData,  smds::ftInteger,      4 },
    { 120,  offsetof(tblSLD_map,TDOISPREDICTION_),              "TDOISPREDICTION",              smds::fkData,  smds::ftShort,        2 },
    { 121,  offsetof(tblSLD_map,TTYIDASSETITEM_),               "TTYIDASSETITEM",               smds::fkData,  smds::ftInteger,      4 },
    { 122,  offsetof(tblSLD_map,TDOAUDITEQUIVALENCE_),          "TDOAUDITEQUIVALENCE",          smds::fkData,  smds::ftDouble,       8 },
    { 123,  offsetof(tblSLD_map,TDOAUDITEQVONEBASED_),          "TDOAUDITEQVONEBASED",          smds::fkData,  smds::ftShort,        2 },
    { 124,  offsetof(tblSLD_map,TDODASMEQUIVALENCE_),           "TDODASMEQUIVALENCE",           smds::fkData,  smds::ftDouble,       8 },
    { 125,  offsetof(tblSLD_map,SLDCASHIER_),                   "SLDCASHIER",                   smds::fkData,  smds::ftInteger,      4 },
    { 126,  offsetof(tblSLD_map,VERID_),                        "VERID",                        smds::fkData,  smds::ftInteger,      4 },
    { 127,  offsetof(tblSLD_map,SLDDISCOUNTPOLICY_),            "SLDDISCOUNTPOLICY",            smds::fkData,  smds::ftDouble,       8 },
    { 128,  offsetof(tblSLD_map,SLDDISCOUNTPOLICYBC_),          "SLDDISCOUNTPOLICYBC",          smds::fkData,  smds::ftDouble,       8 },
    { 129,  offsetof(tblSLD_map,TDODETAILTRMTOTAL_),            "TDODETAILTRMTOTAL",            smds::fkData,  smds::ftDouble,       8 },
    { 130,  offsetof(tblSLD_map,TDODETAILTRMTOTALBC_),          "TDODETAILTRMTOTALBC",          smds::fkData,  smds::ftDouble,       8 },
    { 131,  offsetof(tblSLD_map,CONID_),                        "CONID",                        smds::fkData,  smds::ftInteger,      4 },
    { 132,  offsetof(tblSLD_map,DOCIDTRIANGLE_),                "DOCIDTRIANGLE",                smds::fkData,  smds::ftInteger,      4 },
    { 133,  offsetof(tblSLD_map,TRIANGLESUBSYSID_),             "TRIANGLESUBSYSID",             smds::fkData,  smds::ftShort,        2 },
    { 134,  offsetof(tblSLD_map,DOCIDTRIANGLEFROM_),            "DOCIDTRIANGLEFROM",            smds::fkData,  smds::ftInteger,      4 },
    { 135,  offsetof(tblSLD_map,TRIANGLESUBSYSIDFROM_),         "TRIANGLESUBSYSIDFROM",         smds::fkData,  smds::ftShort,        2 },
    { 136,  offsetof(tblSLD_map,TRAIDPRINCIPAL_),               "TRAIDPRINCIPAL",               smds::fkData,  smds::ftInteger,      4 },
    { 137,  offsetof(tblSLD_map,PRTID_),                        "PRTID",                        smds::fkData,  smds::ftInteger,      4 },
    { 138,  offsetof(tblSLD_map,ADRIDDELIVERY_),                "ADRIDDELIVERY",                smds::fkData,  smds::ftInteger,      4 },
    { 139,  offsetof(tblSLD_map,SLDPROCESSDATE_),               "SLDPROCESSDATE",               smds::fkData,  smds::ftDateTime,     8 },
    { 140,  offsetof(tblSLD_map,TDOCOLONNUMBER_),               "TDOCOLONNUMBER",               smds::fkData,  smds::ftInteger,      4 },
    { 141,  offsetof(tblSLD_map,TDOQTYAGUARANTEE_),             "TDOQTYAGUARANTEE",             smds::fkData,  smds::ftDouble,       8 },
    { 142,  offsetof(tblSLD_map,TDOQTYBGUARANTEE_),             "TDOQTYBGUARANTEE",             smds::fkData,  smds::ftDouble,       8 },
    { 143,  offsetof(tblSLD_map,TDOGUARANTEERECEIVEDVALUE_),    "TDOGUARANTEERECEIVEDVALUE",    smds::fkData,  smds::ftDouble,       8 },
    { 144,  offsetof(tblSLD_map,TDOGUARANTEERECEIVEDVALUEBC_),  "TDOGUARANTEERECEIVEDVALUEBC",  smds::fkData,  smds::ftDouble,       8 },
    { 145,  offsetof(tblSLD_map,TDOGUARANTEERETURNEDVALUE_),    "TDOGUARANTEERETURNEDVALUE",    smds::fkData,  smds::ftDouble,       8 },
    { 146,  offsetof(tblSLD_map,TDOGUARANTEERETURNEDVALUEBC_),  "TDOGUARANTEERETURNEDVALUEBC",  smds::fkData,  smds::ftDouble,       8 },
    { 147,  offsetof(tblSLD_map,TTYIDTRADERGUARANTEE_),         "TTYIDTRADERGUARANTEE",         smds::fkData,  smds::ftInteger,      4 },
    { 148,  offsetof(tblSLD_map,TTYIDSTOCKITEMGUARANTEE_),      "TTYIDSTOCKITEMGUARANTEE",      smds::fkData,  smds::ftInteger,      4 },
    { 149,  offsetof(tblSLD_map,ADRIDBRANCH_),                  "ADRIDBRANCH",                  smds::fkData,  smds::ftInteger,      4 },
    { 150,  offsetof(tblSLD_map,TDOTRANSFORMEDCANCELED_),       "TDOTRANSFORMEDCANCELED",       smds::fkData,  smds::ftShort,        2 },
    { 151,  offsetof(tblSLD_map,TDOTRADERTRANSSIGN_),           "TDOTRADERTRANSSIGN",           smds::fkData,  smds::ftShort,        2 },
    { 152,  offsetof(tblSLD_map,TDOGUARANTEETRADERTRANSSIGN_),  "TDOGUARANTEETRADERTRANSSIGN",  smds::fkData,  smds::ftShort,        2 },
    { 153,  offsetof(tblSLD_map,TDOPOLICYDISCOUNT_),            "TDOPOLICYDISCOUNT",            smds::fkData,  smds::ftDouble,       8 },
    { 154,  offsetof(tblSLD_map,TDOPOLICYDISCOUNTBC_),          "TDOPOLICYDISCOUNTBC",          smds::fkData,  smds::ftDouble,       8 },
    { 155,  offsetof(tblSLD_map,TDOTRANSDISCOUNT_),             "TDOTRANSDISCOUNT",             smds::fkData,  smds::ftDouble,       8 },
    { 156,  offsetof(tblSLD_map,TDOTRANSDISCOUNTBC_),           "TDOTRANSDISCOUNTBC",           smds::fkData,  smds::ftDouble,       8 },
    { 157,  offsetof(tblSLD_map,DIPIDTRANSACTION_),             "DIPIDTRANSACTION",             smds::fkData,  smds::ftInteger,      4 },
    { 158,  offsetof(tblSLD_map,BRAID_),                        "BRAID",                        smds::fkData,  smds::ftInteger,      4 },
    { 159,  offsetof(tblSLD_map,TRMID_),                        "TRMID",                        smds::fkData,  smds::ftInteger,      4 },
    { 160,  offsetof(tblSLD_map,TDOCOPYTRMID_),                 "TDOCOPYTRMID",                 smds::fkData,  smds::ftShort,        2 },
    { 161,  offsetof(tblSLD_map,TDOPAYMENTSTARTDATE_),          "TDOPAYMENTSTARTDATE",          smds::fkData,  smds::ftDateTime,     8 },
    { 162,  offsetof(tblSLD_map,TDOACCEPTDAYS_),                "TDOACCEPTDAYS",                smds::fkData,  smds::ftInteger,      4 },
    { 163,  offsetof(tblSLD_map,TDODRIVECURID_),                "TDODRIVECURID",                smds::fkData,  smds::ftInteger,      4 },
    { 164,  offsetof(tblSLD_map,TDOTRADERCURID_),               "TDOTRADERCURID",               smds::fkData,  smds::ftInteger,      4 },
    { 165,  offsetof(tblSLD_map,TDOTRADEREQUIVALENCE_),         "TDOTRADEREQUIVALENCE",         smds::fkData,  smds::ftDouble,       8 },
    { 166,  offsetof(tblSLD_map,TDOTRADEREQVTYPE_),             "TDOTRADEREQVTYPE",             smds::fkData,  smds::ftString,       1 },
    { 167,  offsetof(tblSLD_map,TDOTRADERAUDITEQUIVALENCE_),    "TDOTRADERAUDITEQUIVALENCE",    smds::fkData,  smds::ftDouble,       8 },
    { 168,  offsetof(tblSLD_map,TDOTRAAUDITEQVONEBASED_),       "TDOTRAAUDITEQVONEBASED",       smds::fkData,  smds::ftShort,        2 },
    { 169,  offsetof(tblSLD_map,SLDDELIVERYPLACE_),             "SLDDELIVERYPLACE",             smds::fkData,  smds::ftString,     255 },
};

const smds::cFieldDefs_  tblSLD_data::tblSLD_FieldDef =
{
    sizeof(tblSLD_map),
    sizeof(tblSLD_Fields)/sizeof(tblSLD_Fields[0]),
    "SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s",
    "SLD",
    tblSLD_Fields
};

const smds::cFieldDefs_& FASTCALL tblSLD_rec::GetFieldDefs()  { return ( tblSLD_FieldDef ); }
*/
//---------------------------------------------------------------------------

