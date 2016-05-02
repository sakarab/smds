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

#include "pre_test.h"
#include "uTables.h"
//---------------------------------------------------------------------------

using namespace smds;
using namespace smds::detail;

//***********************************************************************
//******    tblLocation
//***********************************************************************
struct tblLocation_map
{
    int     LocationID_;
    short   LocTypeID_;
    short   IsUser_;
    int     SerialNo_;
    wchar_t Drive_[2];
};

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
struct tblFiles_map
{
    int                                 FileID_;
    int                                 PathID_;
    ds_string                           *LongFileName_;
    int                                 fSize_;
    smds::detail::dbDateTime_Internal   fDate_;
    ds_string                           *Description_;
    int                                 zipID_;
};

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

//***********************************************************************
//******    tblSLD
//***********************************************************************
//const cFieldDef_  tblSLD_data::tblSLD_Fields[] =
//{
//    {   0,  offsetof(tblSLD_map,DOCID_),                        "DOCID",                        fkData,  ftInteger,      4 },
//    {   1,  offsetof(tblSLD_map,DOTID_),                        "DOTID",                        fkData,  ftInteger,      4 },
//    {   2,  offsetof(tblSLD_map,FIYID_),                        "FIYID",                        fkData,  ftInteger,      4 },
//    {   3,  offsetof(tblSLD_map,PERID_),                        "PERID",                        fkData,  ftInteger,      4 },
//    {   4,  offsetof(tblSLD_map,DOSID_),                        "DOSID",                        fkData,  ftInteger,      4 },
//    {   5,  offsetof(tblSLD_map,DOSCODE_),                      "DOSCODE",                      fkData,  ftString,       4 },
//    {   6,  offsetof(tblSLD_map,DOCNUMBER_),                    "DOCNUMBER",                    fkData,  ftInteger,      4 },
//    {   7,  offsetof(tblSLD_map,DOCJRNAA_),                     "DOCJRNAA",                     fkData,  ftInteger,      4 },
//    {   8,  offsetof(tblSLD_map,DOCKATAHORISISDATE_),           "DOCKATAHORISISDATE",           fkData,  ftDateTime,     8 },
//    {   9,  offsetof(tblSLD_map,DOCENIMEROSISDATE_),            "DOCENIMEROSISDATE",            fkData,  ftDateTime,     8 },
//    {  10,  offsetof(tblSLD_map,DOCEKDOSISDATE_),               "DOCEKDOSISDATE",               fkData,  ftDateTime,     8 },
//    {  11,  offsetof(tblSLD_map,DOCREASON_),                    "DOCREASON",                    fkData,  ftString,     100 },
//    {  12,  offsetof(tblSLD_map,DOCCOMMENT_),                   "DOCCOMMENT",                   fkData,  ftString,     255 },
//    {  13,  offsetof(tblSLD_map,DOCCANENIM_),                   "DOCCANENIM",                   fkData,  ftShort,        2 },
//    {  14,  offsetof(tblSLD_map,DOCCANCANCEL_),                 "DOCCANCANCEL",                 fkData,  ftShort,        2 },
//    {  15,  offsetof(tblSLD_map,DOCCANCELSTATUS_),              "DOCCANCELSTATUS",              fkData,  ftString,       1 },
//    {  16,  offsetof(tblSLD_map,DOCIDAKIROMENO_),               "DOCIDAKIROMENO",               fkData,  ftInteger,      4 },
//    {  17,  offsetof(tblSLD_map,DOCIDAKIROTIKO_),               "DOCIDAKIROTIKO",               fkData,  ftInteger,      4 },
//    {  18,  offsetof(tblSLD_map,DMIID_),                        "DMIID",                        fkData,  ftInteger,      4 },
//    {  19,  offsetof(tblSLD_map,TDOGROSSRETAIL_),               "TDOGROSSRETAIL",               fkData,  ftShort,        2 },
//    {  20,  offsetof(tblSLD_map,TDOOTHERNUMBER_),               "TDOOTHERNUMBER",               fkData,  ftString,      20 },
//    {  21,  offsetof(tblSLD_map,TDOOTHERDATE_),                 "TDOOTHERDATE",                 fkData,  ftDateTime,     8 },
//    {  22,  offsetof(tblSLD_map,TDOEKTELESISDATE_),             "TDOEKTELESISDATE",             fkData,  ftDateTime,     8 },
//    {  23,  offsetof(tblSLD_map,DSTDESCR_),                     "DSTDESCR",                     fkData,  ftString,      50 },
//    {  24,  offsetof(tblSLD_map,PPSDESCR_),                     "PPSDESCR",                     fkData,  ftString,      50 },
//    {  25,  offsetof(tblSLD_map,ORGDESCR_),                     "ORGDESCR",                     fkData,  ftString,      50 },
//    {  26,  offsetof(tblSLD_map,TPMID_),                        "TPMID",                        fkData,  ftInteger,      4 },
//    {  27,  offsetof(tblSLD_map,TPTID_),                        "TPTID",                        fkData,  ftInteger,      4 },
//    {  28,  offsetof(tblSLD_map,SHVID_),                        "SHVID",                        fkData,  ftInteger,      4 },
//    {  29,  offsetof(tblSLD_map,WRHID_),                        "WRHID",                        fkData,  ftInteger,      4 },
//    {  30,  offsetof(tblSLD_map,TRAID_),                        "TRAID",                        fkData,  ftInteger,      4 },
//    {  31,  offsetof(tblSLD_map,TXOCODE_),                      "TXOCODE",                      fkData,  ftString,       4 },
//    {  32,  offsetof(tblSLD_map,TDOTRANSPORTREMARKS_),          "TDOTRANSPORTREMARKS",          fkData,  ftString,     255 },
//    {  33,  offsetof(tblSLD_map,ADRIDLOGISTIRIOU_),             "ADRIDLOGISTIRIOU",             fkData,  ftInteger,      4 },
//    {  34,  offsetof(tblSLD_map,ADRIDPROORISMOU_),              "ADRIDPROORISMOU",              fkData,  ftInteger,      4 },
//    {  35,  offsetof(tblSLD_map,TDOSENDTIME_),                  "TDOSENDTIME",                  fkData,  ftDateTime,     8 },
//    {  36,  offsetof(tblSLD_map,TDOVATSTATUS_),                 "TDOVATSTATUS",                 fkData,  ftString,       9 },
//    {  37,  offsetof(tblSLD_map,TDOLEEAFM_),                    "TDOLEEAFM",                    fkData,  ftString,      12 },
//    {  38,  offsetof(tblSLD_map,TDOLEEADT_),                    "TDOLEEADT",                    fkData,  ftString,      20 },
//    {  39,  offsetof(tblSLD_map,TDOLEEADTKIND_),                "TDOLEEADTKIND",                fkData,  ftString,       2 },
//    {  40,  offsetof(tblSLD_map,TDOADDRESS_),                   "TDOADDRESS",                   fkData,  ftString,     100 },
//    {  41,  offsetof(tblSLD_map,CURID_),                        "CURID",                        fkData,  ftInteger,      4 },
//    {  42,  offsetof(tblSLD_map,TDOEQVTYPE_),                   "TDOEQVTYPE",                   fkData,  ftString,       1 },
//    {  43,  offsetof(tblSLD_map,TDOEQUIVALENCE_),               "TDOEQUIVALENCE",               fkData,  ftDouble,       8 },
//    {  44,  offsetof(tblSLD_map,TDODUEDAYS_),                   "TDODUEDAYS",                   fkData,  ftInteger,      4 },
//    {  45,  offsetof(tblSLD_map,TDOGRACEDAYS_),                 "TDOGRACEDAYS",                 fkData,  ftInteger,      4 },
//    {  46,  offsetof(tblSLD_map,SLMID_),                        "SLMID",                        fkData,  ftInteger,      4 },
//    {  47,  offsetof(tblSLD_map,TDOTRADERDISCPCNT_),            "TDOTRADERDISCPCNT",            fkData,  ftDouble,       8 },
//    {  48,  offsetof(tblSLD_map,TDOQTYA_),                      "TDOQTYA",                      fkData,  ftDouble,       8 },
//    {  49,  offsetof(tblSLD_map,TDOQTYB_),                      "TDOQTYB",                      fkData,  ftDouble,       8 },
//    {  50,  offsetof(tblSLD_map,TDOTRANSFQTYA_),                "TDOTRANSFQTYA",                fkData,  ftDouble,       8 },
//    {  51,  offsetof(tblSLD_map,TDOTRANSFQTYB_),                "TDOTRANSFQTYB",                fkData,  ftDouble,       8 },
//    {  52,  offsetof(tblSLD_map,TDOQTYDISCA_),                  "TDOQTYDISCA",                  fkData,  ftDouble,       8 },
//    {  53,  offsetof(tblSLD_map,TDOQTYDISCB_),                  "TDOQTYDISCB",                  fkData,  ftDouble,       8 },
//    {  54,  offsetof(tblSLD_map,TDOTRADERDISC_),                "TDOTRADERDISC",                fkData,  ftDouble,       8 },
//    {  55,  offsetof(tblSLD_map,TDOTRADERDISCBC_),              "TDOTRADERDISCBC",              fkData,  ftDouble,       8 },
//    {  56,  offsetof(tblSLD_map,TDOPAYMENTDISC_),               "TDOPAYMENTDISC",               fkData,  ftDouble,       8 },
//    {  57,  offsetof(tblSLD_map,TDOPAYMENTDISCBC_),             "TDOPAYMENTDISCBC",             fkData,  ftDouble,       8 },
//    {  58,  offsetof(tblSLD_map,TDOSTOCKDISC_),                 "TDOSTOCKDISC",                 fkData,  ftDouble,       8 },
//    {  59,  offsetof(tblSLD_map,TDOSTOCKDISCBC_),               "TDOSTOCKDISCBC",               fkData,  ftDouble,       8 },
//    {  60,  offsetof(tblSLD_map,TDOPRICELISTDISC_),             "TDOPRICELISTDISC",             fkData,  ftDouble,       8 },
//    {  61,  offsetof(tblSLD_map,TDOPRICELISTDISCBC_),           "TDOPRICELISTDISCBC",           fkData,  ftDouble,       8 },
//    {  62,  offsetof(tblSLD_map,TDOEXTRADISC_),                 "TDOEXTRADISC",                 fkData,  ftDouble,       8 },
//    {  63,  offsetof(tblSLD_map,TDOEXTRADISCBC_),               "TDOEXTRADISCBC",               fkData,  ftDouble,       8 },
//    {  64,  offsetof(tblSLD_map,TDONETSTOCK_),                  "TDONETSTOCK",                  fkData,  ftDouble,       8 },
//    {  65,  offsetof(tblSLD_map,TDONETSTOCKBC_),                "TDONETSTOCKBC",                fkData,  ftDouble,       8 },
//    {  66,  offsetof(tblSLD_map,TDONETGIFT_),                   "TDONETGIFT",                   fkData,  ftDouble,       8 },
//    {  67,  offsetof(tblSLD_map,TDONETGIFTBC_),                 "TDONETGIFTBC",                 fkData,  ftDouble,       8 },
//    {  68,  offsetof(tblSLD_map,TDONETSURCHARGE_),              "TDONETSURCHARGE",              fkData,  ftDouble,       8 },
//    {  69,  offsetof(tblSLD_map,TDONETSURCHARGEBC_),            "TDONETSURCHARGEBC",            fkData,  ftDouble,       8 },
//    {  70,  offsetof(tblSLD_map,TDONETOTHER_),                  "TDONETOTHER",                  fkData,  ftDouble,       8 },
//    {  71,  offsetof(tblSLD_map,TDONETOTHERBC_),                "TDONETOTHERBC",                fkData,  ftDouble,       8 },
//    {  72,  offsetof(tblSLD_map,TDONETTAX_),                    "TDONETTAX",                    fkData,  ftDouble,       8 },
//    {  73,  offsetof(tblSLD_map,TDONETTAXBC_),                  "TDONETTAXBC",                  fkData,  ftDouble,       8 },
//    {  74,  offsetof(tblSLD_map,TDOGROSSVALUE_),                "TDOGROSSVALUE",                fkData,  ftDouble,       8 },
//    {  75,  offsetof(tblSLD_map,TDOGROSSVALUEBC_),              "TDOGROSSVALUEBC",              fkData,  ftDouble,       8 },
//    {  76,  offsetof(tblSLD_map,TDOVATSTOCK_),                  "TDOVATSTOCK",                  fkData,  ftDouble,       8 },
//    {  77,  offsetof(tblSLD_map,TDOVATSTOCKBC_),                "TDOVATSTOCKBC",                fkData,  ftDouble,       8 },
//    {  78,  offsetof(tblSLD_map,TDOVATGIFT_),                   "TDOVATGIFT",                   fkData,  ftDouble,       8 },
//    {  79,  offsetof(tblSLD_map,TDOVATGIFTBC_),                 "TDOVATGIFTBC",                 fkData,  ftDouble,       8 },
//    {  80,  offsetof(tblSLD_map,TDOVATSURCHARGE_),              "TDOVATSURCHARGE",              fkData,  ftDouble,       8 },
//    {  81,  offsetof(tblSLD_map,TDOVATSURCHARGEBC_),            "TDOVATSURCHARGEBC",            fkData,  ftDouble,       8 },
//    {  82,  offsetof(tblSLD_map,TDOVATOTHER_),                  "TDOVATOTHER",                  fkData,  ftDouble,       8 },
//    {  83,  offsetof(tblSLD_map,TDOVATOTHERBC_),                "TDOVATOTHERBC",                fkData,  ftDouble,       8 },
//    {  84,  offsetof(tblSLD_map,TDOVATTAX_),                    "TDOVATTAX",                    fkData,  ftDouble,       8 },
//    {  85,  offsetof(tblSLD_map,TDOVATTAXBC_),                  "TDOVATTAXBC",                  fkData,  ftDouble,       8 },
//    {  86,  offsetof(tblSLD_map,PTPIDPAYMENT_),                 "PTPIDPAYMENT",                 fkData,  ftInteger,      4 },
//    {  87,  offsetof(tblSLD_map,PMTIDPAYMENT_),                 "PMTIDPAYMENT",                 fkData,  ftInteger,      4 },
//    {  88,  offsetof(tblSLD_map,DOCIDPAYMENT_),                 "DOCIDPAYMENT",                 fkData,  ftInteger,      4 },
//    {  89,  offsetof(tblSLD_map,TDOPAYMENT_),                   "TDOPAYMENT",                   fkData,  ftDouble,       8 },
//    {  90,  offsetof(tblSLD_map,TDOPAYMENTBC_),                 "TDOPAYMENTBC",                 fkData,  ftDouble,       8 },
//    {  91,  offsetof(tblSLD_map,TDONETKRATISI_),                "TDONETKRATISI",                fkData,  ftDouble,       8 },
//    {  92,  offsetof(tblSLD_map,TDONETKRATISIBC_),              "TDONETKRATISIBC",              fkData,  ftDouble,       8 },
//    {  93,  offsetof(tblSLD_map,TDOTRADERBALANCEBEFORE_),       "TDOTRADERBALANCEBEFORE",       fkData,  ftDouble,       8 },
//    {  94,  offsetof(tblSLD_map,TDOTRADERBALANCEAFTER_),        "TDOTRADERBALANCEAFTER",        fkData,  ftDouble,       8 },
//    {  95,  offsetof(tblSLD_map,TDOCANTRANSF_),                 "TDOCANTRANSF",                 fkData,  ftShort,        2 },
//    {  96,  offsetof(tblSLD_map,TDOADVANCE_),                   "TDOADVANCE",                   fkData,  ftDouble,       8 },
//    {  97,  offsetof(tblSLD_map,TDOADVANCEBC_),                 "TDOADVANCEBC",                 fkData,  ftDouble,       8 },
//    {  98,  offsetof(tblSLD_map,TDOADVANCEUSAGE_),              "TDOADVANCEUSAGE",              fkData,  ftDouble,       8 },
//    {  99,  offsetof(tblSLD_map,TDOADVANCEUSAGEBC_),            "TDOADVANCEUSAGEBC",            fkData,  ftDouble,       8 },
//    { 100,  offsetof(tblSLD_map,CDZID_),                        "CDZID",                        fkData,  ftInteger,      4 },
//    { 101,  offsetof(tblSLD_map,PTPIDDOCTYPE_),                 "PTPIDDOCTYPE",                 fkData,  ftInteger,      4 },
//    { 102,  offsetof(tblSLD_map,LEEIDRECEIVER_),                "LEEIDRECEIVER",                fkData,  ftInteger,      4 },
//    { 103,  offsetof(tblSLD_map,ADRIDRECEIVER_),                "ADRIDRECEIVER",                fkData,  ftInteger,      4 },
//    { 104,  offsetof(tblSLD_map,PMTIDADVANCE_),                 "PMTIDADVANCE",                 fkData,  ftInteger,      4 },
//    { 105,  offsetof(tblSLD_map,DOCIDADVANCE_),                 "DOCIDADVANCE",                 fkData,  ftInteger,      4 },
//    { 106,  offsetof(tblSLD_map,TDOPAYMENTDISCPCNT_),           "TDOPAYMENTDISCPCNT",           fkData,  ftDouble,       8 },
//    { 107,  offsetof(tblSLD_map,TTYIDTRADER_),                  "TTYIDTRADER",                  fkData,  ftInteger,      4 },
//    { 108,  offsetof(tblSLD_map,TTYIDSALESMAN_),                "TTYIDSALESMAN",                fkData,  ftInteger,      4 },
//    { 109,  offsetof(tblSLD_map,TTYIDSTOCKITEM_),               "TTYIDSTOCKITEM",               fkData,  ftInteger,      4 },
//    { 110,  offsetof(tblSLD_map,TDOVATINCLUDED_),               "TDOVATINCLUDED",               fkData,  ftShort,        2 },
//    { 111,  offsetof(tblSLD_map,PTPIDTRADER_),                  "PTPIDTRADER",                  fkData,  ftInteger,      4 },
//    { 112,  offsetof(tblSLD_map,SYS_USRID_),                    "SYS_USRID",                    fkData,  ftInteger,      4 },
//    { 113,  offsetof(tblSLD_map,SYS_LUPD_),                     "SYS_LUPD",                     fkData,  ftDateTime,     8 },
//    { 114,  offsetof(tblSLD_map,SYS_INS_),                      "SYS_INS",                      fkData,  ftDateTime,     8 },
//    { 115,  offsetof(tblSLD_map,TDOKEEPPRICESTRANSF_),          "TDOKEEPPRICESTRANSF",          fkData,  ftString,       4 },
//    { 116,  offsetof(tblSLD_map,TDOTRADERBALANCEBEFOREBC_),     "TDOTRADERBALANCEBEFOREBC",     fkData,  ftDouble,       8 },
//    { 117,  offsetof(tblSLD_map,TDOTRADERBALANCEAFTERBC_),      "TDOTRADERBALANCEAFTERBC",      fkData,  ftDouble,       8 },
//    { 118,  offsetof(tblSLD_map,SLMIDCOLLECTOR_),               "SLMIDCOLLECTOR",               fkData,  ftInteger,      4 },
//    { 119,  offsetof(tblSLD_map,DOCIDPREDICTION_),              "DOCIDPREDICTION",              fkData,  ftInteger,      4 },
//    { 120,  offsetof(tblSLD_map,TDOISPREDICTION_),              "TDOISPREDICTION",              fkData,  ftShort,        2 },
//    { 121,  offsetof(tblSLD_map,TTYIDASSETITEM_),               "TTYIDASSETITEM",               fkData,  ftInteger,      4 },
//    { 122,  offsetof(tblSLD_map,TDOAUDITEQUIVALENCE_),          "TDOAUDITEQUIVALENCE",          fkData,  ftDouble,       8 },
//    { 123,  offsetof(tblSLD_map,TDOAUDITEQVONEBASED_),          "TDOAUDITEQVONEBASED",          fkData,  ftShort,        2 },
//    { 124,  offsetof(tblSLD_map,TDODASMEQUIVALENCE_),           "TDODASMEQUIVALENCE",           fkData,  ftDouble,       8 },
//    { 125,  offsetof(tblSLD_map,SLDCASHIER_),                   "SLDCASHIER",                   fkData,  ftInteger,      4 },
//    { 126,  offsetof(tblSLD_map,VERID_),                        "VERID",                        fkData,  ftInteger,      4 },
//    { 127,  offsetof(tblSLD_map,SLDDISCOUNTPOLICY_),            "SLDDISCOUNTPOLICY",            fkData,  ftDouble,       8 },
//    { 128,  offsetof(tblSLD_map,SLDDISCOUNTPOLICYBC_),          "SLDDISCOUNTPOLICYBC",          fkData,  ftDouble,       8 },
//    { 129,  offsetof(tblSLD_map,TDODETAILTRMTOTAL_),            "TDODETAILTRMTOTAL",            fkData,  ftDouble,       8 },
//    { 130,  offsetof(tblSLD_map,TDODETAILTRMTOTALBC_),          "TDODETAILTRMTOTALBC",          fkData,  ftDouble,       8 },
//    { 131,  offsetof(tblSLD_map,CONID_),                        "CONID",                        fkData,  ftInteger,      4 },
//    { 132,  offsetof(tblSLD_map,DOCIDTRIANGLE_),                "DOCIDTRIANGLE",                fkData,  ftInteger,      4 },
//    { 133,  offsetof(tblSLD_map,TRIANGLESUBSYSID_),             "TRIANGLESUBSYSID",             fkData,  ftShort,        2 },
//    { 134,  offsetof(tblSLD_map,DOCIDTRIANGLEFROM_),            "DOCIDTRIANGLEFROM",            fkData,  ftInteger,      4 },
//    { 135,  offsetof(tblSLD_map,TRIANGLESUBSYSIDFROM_),         "TRIANGLESUBSYSIDFROM",         fkData,  ftShort,        2 },
//    { 136,  offsetof(tblSLD_map,TRAIDPRINCIPAL_),               "TRAIDPRINCIPAL",               fkData,  ftInteger,      4 },
//    { 137,  offsetof(tblSLD_map,PRTID_),                        "PRTID",                        fkData,  ftInteger,      4 },
//    { 138,  offsetof(tblSLD_map,ADRIDDELIVERY_),                "ADRIDDELIVERY",                fkData,  ftInteger,      4 },
//    { 139,  offsetof(tblSLD_map,SLDPROCESSDATE_),               "SLDPROCESSDATE",               fkData,  ftDateTime,     8 },
//    { 140,  offsetof(tblSLD_map,TDOCOLONNUMBER_),               "TDOCOLONNUMBER",               fkData,  ftInteger,      4 },
//    { 141,  offsetof(tblSLD_map,TDOQTYAGUARANTEE_),             "TDOQTYAGUARANTEE",             fkData,  ftDouble,       8 },
//    { 142,  offsetof(tblSLD_map,TDOQTYBGUARANTEE_),             "TDOQTYBGUARANTEE",             fkData,  ftDouble,       8 },
//    { 143,  offsetof(tblSLD_map,TDOGUARANTEERECEIVEDVALUE_),    "TDOGUARANTEERECEIVEDVALUE",    fkData,  ftDouble,       8 },
//    { 144,  offsetof(tblSLD_map,TDOGUARANTEERECEIVEDVALUEBC_),  "TDOGUARANTEERECEIVEDVALUEBC",  fkData,  ftDouble,       8 },
//    { 145,  offsetof(tblSLD_map,TDOGUARANTEERETURNEDVALUE_),    "TDOGUARANTEERETURNEDVALUE",    fkData,  ftDouble,       8 },
//    { 146,  offsetof(tblSLD_map,TDOGUARANTEERETURNEDVALUEBC_),  "TDOGUARANTEERETURNEDVALUEBC",  fkData,  ftDouble,       8 },
//    { 147,  offsetof(tblSLD_map,TTYIDTRADERGUARANTEE_),         "TTYIDTRADERGUARANTEE",         fkData,  ftInteger,      4 },
//    { 148,  offsetof(tblSLD_map,TTYIDSTOCKITEMGUARANTEE_),      "TTYIDSTOCKITEMGUARANTEE",      fkData,  ftInteger,      4 },
//    { 149,  offsetof(tblSLD_map,ADRIDBRANCH_),                  "ADRIDBRANCH",                  fkData,  ftInteger,      4 },
//    { 150,  offsetof(tblSLD_map,TDOTRANSFORMEDCANCELED_),       "TDOTRANSFORMEDCANCELED",       fkData,  ftShort,        2 },
//    { 151,  offsetof(tblSLD_map,TDOTRADERTRANSSIGN_),           "TDOTRADERTRANSSIGN",           fkData,  ftShort,        2 },
//    { 152,  offsetof(tblSLD_map,TDOGUARANTEETRADERTRANSSIGN_),  "TDOGUARANTEETRADERTRANSSIGN",  fkData,  ftShort,        2 },
//    { 153,  offsetof(tblSLD_map,TDOPOLICYDISCOUNT_),            "TDOPOLICYDISCOUNT",            fkData,  ftDouble,       8 },
//    { 154,  offsetof(tblSLD_map,TDOPOLICYDISCOUNTBC_),          "TDOPOLICYDISCOUNTBC",          fkData,  ftDouble,       8 },
//    { 155,  offsetof(tblSLD_map,TDOTRANSDISCOUNT_),             "TDOTRANSDISCOUNT",             fkData,  ftDouble,       8 },
//    { 156,  offsetof(tblSLD_map,TDOTRANSDISCOUNTBC_),           "TDOTRANSDISCOUNTBC",           fkData,  ftDouble,       8 },
//    { 157,  offsetof(tblSLD_map,DIPIDTRANSACTION_),             "DIPIDTRANSACTION",             fkData,  ftInteger,      4 },
//    { 158,  offsetof(tblSLD_map,BRAID_),                        "BRAID",                        fkData,  ftInteger,      4 },
//    { 159,  offsetof(tblSLD_map,TRMID_),                        "TRMID",                        fkData,  ftInteger,      4 },
//    { 160,  offsetof(tblSLD_map,TDOCOPYTRMID_),                 "TDOCOPYTRMID",                 fkData,  ftShort,        2 },
//    { 161,  offsetof(tblSLD_map,TDOPAYMENTSTARTDATE_),          "TDOPAYMENTSTARTDATE",          fkData,  ftDateTime,     8 },
//    { 162,  offsetof(tblSLD_map,TDOACCEPTDAYS_),                "TDOACCEPTDAYS",                fkData,  ftInteger,      4 },
//    { 163,  offsetof(tblSLD_map,TDODRIVECURID_),                "TDODRIVECURID",                fkData,  ftInteger,      4 },
//    { 164,  offsetof(tblSLD_map,TDOTRADERCURID_),               "TDOTRADERCURID",               fkData,  ftInteger,      4 },
//    { 165,  offsetof(tblSLD_map,TDOTRADEREQUIVALENCE_),         "TDOTRADEREQUIVALENCE",         fkData,  ftDouble,       8 },
//    { 166,  offsetof(tblSLD_map,TDOTRADEREQVTYPE_),             "TDOTRADEREQVTYPE",             fkData,  ftString,       1 },
//    { 167,  offsetof(tblSLD_map,TDOTRADERAUDITEQUIVALENCE_),    "TDOTRADERAUDITEQUIVALENCE",    fkData,  ftDouble,       8 },
//    { 168,  offsetof(tblSLD_map,TDOTRAAUDITEQVONEBASED_),       "TDOTRAAUDITEQVONEBASED",       fkData,  ftShort,        2 },
//    { 169,  offsetof(tblSLD_map,SLDDELIVERYPLACE_),             "SLDDELIVERYPLACE",             fkData,  ftString,     255 },
//};
//
//const smds::detail::cFieldDefs_  tblSLD_data::tblSLD_FieldDef =
//{
//    sizeof(tblSLD_map),
//    sizeof(tblSLD_Fields)/sizeof(tblSLD_Fields[0]),
//    "SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s",
//    "SLD",
//    tblSLD_Fields
//};
//
//const smds::detail::cFieldDefs_& FASTCALL tblSLD_rec::GetFieldDefs()  { return ( tblSLD_FieldDef ); }
//---------------------------------------------------------------------------

