//---------------------------------------------------------------------------
#pragma hdrstop

#include "uTables.h"
//---------------------------------------------------------------------------

//***********************************************************************
//******    tblCAN
//***********************************************************************
const ds::cFieldDef_  tblCAN_data::tblCAN_Fields[] =
{
    {   0,  offsetof(tblCAN_map,CANID_),         "CANID",         ds::fkData,  ds::ftInteger,      4 },
    {   1,  offsetof(tblCAN_map,CALID_),         "CALID",         ds::fkData,  ds::ftInteger,      4 },
    {   2,  offsetof(tblCAN_map,CANDAY_),        "CANDAY",        ds::fkData,  ds::ftShort,        2 },
    {   3,  offsetof(tblCAN_map,CANSTARTTIME_),  "CANSTARTTIME",  ds::fkData,  ds::ftDateTime,     8 },
    {   4,  offsetof(tblCAN_map,CANDURATION_),   "CANDURATION",   ds::fkData,  ds::ftDouble,       8 },
    {   5,  offsetof(tblCAN_map,SHTID_),         "SHTID",         ds::fkData,  ds::ftInteger,      4 },
    {   6,  offsetof(tblCAN_map,SHTCODE_),       "SHTCODE",       ds::fkData,  ds::ftString,      20 },
};

const ds::cFieldDefs_  tblCAN_data::tblCAN_FieldDef =
{
    sizeof(tblCAN_map),
    sizeof(tblCAN_Fields)/sizeof(tblCAN_Fields[0]),
    "SELECT CANID, CALID, CANDAY, CANSTARTTIME, CANDURATION, SHTID, SHTCODE FROM PDC_CAN",
    "CAN",
    tblCAN_Fields
};

const ds::cFieldDefs_& FASTCALL tblCAN_rec::GetFieldDefs()  { return ( tblCAN_FieldDef ); }
//***********************************************************************
//******    tblCEX
//***********************************************************************
const ds::cFieldDef_  tblCEX_data::tblCEX_Fields[] =
{
    {   0,  offsetof(tblCEX_map,CEXID_),           "CEXID",           ds::fkData,  ds::ftInteger,      4 },
    {   1,  offsetof(tblCEX_map,CALID_),           "CALID",           ds::fkData,  ds::ftInteger,      4 },
    {   2,  offsetof(tblCEX_map,CEXDATE_),         "CEXDATE",         ds::fkData,  ds::ftDateTime,     8 },
    {   3,  offsetof(tblCEX_map,CEXDURATION_),     "CEXDURATION",     ds::fkData,  ds::ftDouble,       8 },
    {   4,  offsetof(tblCEX_map,CEXSTARTTIME_),    "CEXSTARTTIME",    ds::fkData,  ds::ftDateTime,     8 },
    {   5,  offsetof(tblCEX_map,SHTID_),           "SHTID",           ds::fkData,  ds::ftInteger,      4 },
    {   6,  offsetof(tblCEX_map,SHTCODE_),         "SHTCODE",         ds::fkData,  ds::ftString,      20 },
    {   7,  offsetof(tblCEX_map,SHTDESCRIPTION_),  "SHTDESCRIPTION",  ds::fkData,  ds::ftString,      40 },
};

const ds::cFieldDefs_  tblCEX_data::tblCEX_FieldDef =
{
    sizeof(tblCEX_map),
    sizeof(tblCEX_Fields)/sizeof(tblCEX_Fields[0]),
    "SELECT CEXID, CALID, CEXDATE, CEXDURATION, CEXSTARTTIME, SHTID, SHTCODE, SHTDESCRIPTION FROM PDC_CEX",
    "CEX",
    tblCEX_Fields
};

const ds::cFieldDefs_& FASTCALL tblCEX_rec::GetFieldDefs()  { return ( tblCEX_FieldDef ); }
//***********************************************************************
//******    tblHLD
//***********************************************************************
const ds::cFieldDef_  tblHLD_data::tblHLD_Fields[] =
{
    {   0,  offsetof(tblHLD_map,HLDID_),           "HLDID",           ds::fkData,  ds::ftInteger,      4 },
    {   1,  offsetof(tblHLD_map,HLDCODE_),         "HLDCODE",         ds::fkData,  ds::ftString,      20 },
    {   2,  offsetof(tblHLD_map,HLDDESCRIPTION_),  "HLDDESCRIPTION",  ds::fkData,  ds::ftString,      40 },
    {   3,  offsetof(tblHLD_map,HLDDATE_),         "HLDDATE",         ds::fkData,  ds::ftDateTime,     8 },
};

const ds::cFieldDefs_  tblHLD_data::tblHLD_FieldDef =
{
    sizeof(tblHLD_map),
    sizeof(tblHLD_Fields)/sizeof(tblHLD_Fields[0]),
    "SELECT HLDID, HLDCODE, HLDDESCRIPTION, HLDDATE FROM HLD",
    "HLD",
    tblHLD_Fields
};

const ds::cFieldDefs_& FASTCALL tblHLD_rec::GetFieldDefs()  { return ( tblHLD_FieldDef ); }
//***********************************************************************
//******    tblBOM
//***********************************************************************
const ds::cFieldDef_  tblBOM_data::tblBOM_Fields[] =
{
    {   0,  offsetof(tblBOM_map,BOMID_),                "BOMID",                ds::fkData,  ds::ftInteger,      4 },
    {   1,  offsetof(tblBOM_map,BOMCODE_),              "BOMCODE",              ds::fkData,  ds::ftString,      20 },
    {   2,  offsetof(tblBOM_map,BOMDESCRIPTION_),       "BOMDESCRIPTION",       ds::fkData,  ds::ftString,      40 },
    {   3,  offsetof(tblBOM_map,BOMREFQUANTITY_),       "BOMREFQUANTITY",       ds::fkData,  ds::ftDouble,       8 },
    {   4,  offsetof(tblBOM_map,BOMREFQUANTITYB_),      "BOMREFQUANTITYB",      ds::fkData,  ds::ftDouble,       8 },
    {   5,  offsetof(tblBOM_map,BOMQUANTITYDEP_),       "BOMQUANTITYDEP",       ds::fkData,  ds::ftShort,        2 },
    {   6,  offsetof(tblBOM_map,BOMTYPE_),              "BOMTYPE",              ds::fkData,  ds::ftShort,        2 },
    {   7,  offsetof(tblBOM_map,MCIID_),                "MCIID",                ds::fkData,  ds::ftInteger,      4 },
    {   8,  offsetof(tblBOM_map,CODCODE_),              "CODCODE",              ds::fkData,  ds::ftString,      30 },
    {   9,  offsetof(tblBOM_map,ITMNAME_),              "ITMNAME",              ds::fkData,  ds::ftString,      60 },
    {  10,  offsetof(tblBOM_map,DFVCODE1_),             "DFVCODE1",             ds::fkData,  ds::ftString,      20 },
    {  11,  offsetof(tblBOM_map,DFVCODE2_),             "DFVCODE2",             ds::fkData,  ds::ftString,      20 },
    {  12,  offsetof(tblBOM_map,DFVCODE3_),             "DFVCODE3",             ds::fkData,  ds::ftString,      20 },
    {  13,  offsetof(tblBOM_map,DFVCODE4_),             "DFVCODE4",             ds::fkData,  ds::ftString,      20 },
    {  14,  offsetof(tblBOM_map,DFVCODE5_),             "DFVCODE5",             ds::fkData,  ds::ftString,      20 },
    {  15,  offsetof(tblBOM_map,DFVCODE6_),             "DFVCODE6",             ds::fkData,  ds::ftString,      20 },
    {  16,  offsetof(tblBOM_map,DFVCODE7_),             "DFVCODE7",             ds::fkData,  ds::ftString,      20 },
    {  17,  offsetof(tblBOM_map,TSFID_),                "TSFID",                ds::fkData,  ds::ftInteger,      4 },
    {  18,  offsetof(tblBOM_map,TSFCODE_),              "TSFCODE",              ds::fkData,  ds::ftString,      20 },
    {  19,  offsetof(tblBOM_map,TSFDESCRIPTION_),       "TSFDESCRIPTION",       ds::fkData,  ds::ftString,      40 },
    {  20,  offsetof(tblBOM_map,ROTID_),                "ROTID",                ds::fkData,  ds::ftInteger,      4 },
    {  21,  offsetof(tblBOM_map,ROTCODE_),              "ROTCODE",              ds::fkData,  ds::ftString,      20 },
    {  22,  offsetof(tblBOM_map,ROTDESCRIPTION_),       "ROTDESCRIPTION",       ds::fkData,  ds::ftString,      40 },
    {  23,  offsetof(tblBOM_map,WRHID_),                "WRHID",                ds::fkData,  ds::ftInteger,      4 },
    {  24,  offsetof(tblBOM_map,BOMISACTIVE_),          "BOMISACTIVE",          ds::fkData,  ds::ftShort,        2 },
    {  25,  offsetof(tblBOM_map,WRHCODE_),              "WRHCODE",              ds::fkData,  ds::ftString,       4 },
    {  26,  offsetof(tblBOM_map,WRHNAME_),              "WRHNAME",              ds::fkData,  ds::ftString,      40 },
    {  27,  offsetof(tblBOM_map,UNISHORTNAMEA_),        "UNISHORTNAMEA",        ds::fkData,  ds::ftString,       4 },
    {  28,  offsetof(tblBOM_map,UNISHORTNAMEB_),        "UNISHORTNAMEB",        ds::fkData,  ds::ftString,       4 },
    {  29,  offsetof(tblBOM_map,BOMVALSTARTDATE_),      "BOMVALSTARTDATE",      ds::fkData,  ds::ftDateTime,     8 },
    {  30,  offsetof(tblBOM_map,BOMVALENDDATE_),        "BOMVALENDDATE",        ds::fkData,  ds::ftDateTime,     8 },
    {  31,  offsetof(tblBOM_map,BOMDIFFICULTYFACTOR_),  "BOMDIFFICULTYFACTOR",  ds::fkData,  ds::ftDouble,       8 },
    {  32,  offsetof(tblBOM_map,UNINAMEA_),             "UNINAMEA",             ds::fkData,  ds::ftString,      30 },
    {  33,  offsetof(tblBOM_map,UNINAMEB_),             "UNINAMEB",             ds::fkData,  ds::ftString,      30 },
    {  34,  offsetof(tblBOM_map,BTGID_),                "BTGID",                ds::fkData,  ds::ftInteger,      4 },
    {  35,  offsetof(tblBOM_map,BTGCODE_),              "BTGCODE",              ds::fkData,  ds::ftString,      20 },
    {  36,  offsetof(tblBOM_map,BTGDESCRIPTION_),       "BTGDESCRIPTION",       ds::fkData,  ds::ftString,      40 },
    {  37,  offsetof(tblBOM_map,DFTID_),                "DFTID",                ds::fkData,  ds::ftInteger,      4 },
    {  38,  offsetof(tblBOM_map,DFAID1_),               "DFAID1",               ds::fkData,  ds::ftInteger,      4 },
    {  39,  offsetof(tblBOM_map,DFAID2_),               "DFAID2",               ds::fkData,  ds::ftInteger,      4 },
    {  40,  offsetof(tblBOM_map,DFAID3_),               "DFAID3",               ds::fkData,  ds::ftInteger,      4 },
    {  41,  offsetof(tblBOM_map,DFAID4_),               "DFAID4",               ds::fkData,  ds::ftInteger,      4 },
    {  42,  offsetof(tblBOM_map,DFAID5_),               "DFAID5",               ds::fkData,  ds::ftInteger,      4 },
    {  43,  offsetof(tblBOM_map,DFAID6_),               "DFAID6",               ds::fkData,  ds::ftInteger,      4 },
    {  44,  offsetof(tblBOM_map,DFAID7_),               "DFAID7",               ds::fkData,  ds::ftInteger,      4 },
    {  45,  offsetof(tblBOM_map,UNIIDA_),               "UNIIDA",               ds::fkData,  ds::ftInteger,      4 },
    {  46,  offsetof(tblBOM_map,UNIIDB_),               "UNIIDB",               ds::fkData,  ds::ftInteger,      4 },
    {  47,  offsetof(tblBOM_map,BOMISRECYCLE_),         "BOMISRECYCLE",         ds::fkData,  ds::ftShort,        2 },
};

const ds::cFieldDefs_  tblBOM_data::tblBOM_FieldDef =
{
    sizeof(tblBOM_map),
    sizeof(tblBOM_Fields)/sizeof(tblBOM_Fields[0]),
    "SELECT BOMID, BOMCODE, BOMDESCRIPTION, BOMREFQUANTITY, BOMREFQUANTITYB, BOMQUANTITYDEP, BOMTYPE,"
    "       MCIID, CODCODE, ITMNAME, DFVCODE1, DFVCODE2, DFVCODE3, DFVCODE4, DFVCODE5, DFVCODE6,"
    "       DFVCODE7, TSFID, TSFCODE, TSFDESCRIPTION, ROTID, ROTCODE, ROTDESCRIPTION, WRHID, BOMISACTIVE,"
    "       WRHCODE, WRHNAME, UNISHORTNAMEA, UNISHORTNAMEB, BOMVALSTARTDATE, BOMVALENDDATE,"
    "       BOMDIFFICULTYFACTOR, UNINAMEA, UNINAMEB, BTGID, BTGCODE, BTGDESCRIPTION, DFTID, DFAID1, DFAID2,"
    "       DFAID3, DFAID4, DFAID5, DFAID6, DFAID7, UNIIDA, UNIIDB, BOMISRECYCLE "
    "FROM PDC_BOM",
    "BOM",
    tblBOM_Fields
};

const ds::cFieldDefs_& FASTCALL tblBOM_rec::GetFieldDefs()  { return ( tblBOM_FieldDef ); }
//***********************************************************************
//******    tblBMA
//***********************************************************************
const ds::cFieldDef_  tblBMA_data::tblBMA_Fields[] =
{
    {   0,  offsetof(tblBMA_map,BMAID_),             "BMAID",             ds::fkData,  ds::ftInteger,     4 },
    {   1,  offsetof(tblBMA_map,BOMID_),             "BOMID",             ds::fkData,  ds::ftInteger,     4 },
    {   2,  offsetof(tblBMA_map,BMAQUANTITYA_),      "BMAQUANTITYA",      ds::fkData,  ds::ftDouble,      8 },
    {   3,  offsetof(tblBMA_map,BMAQUANTITYB_),      "BMAQUANTITYB",      ds::fkData,  ds::ftDouble,      8 },
    {   4,  offsetof(tblBMA_map,BMALOSS_),           "BMALOSS",           ds::fkData,  ds::ftDouble,      8 },
    {   5,  offsetof(tblBMA_map,BMALOSSTYPE_),       "BMALOSSTYPE",       ds::fkData,  ds::ftShort,       2 },
    {   6,  offsetof(tblBMA_map,BMAINSTRUCTIONS_),   "BMAINSTRUCTIONS",   ds::fkData,  ds::ftString,     50 },
    {   7,  offsetof(tblBMA_map,BMAQUANTIZETYPE_),   "BMAQUANTIZETYPE",   ds::fkData,  ds::ftShort,       2 },
    {   8,  offsetof(tblBMA_map,BMASIGNIFICANCE_),   "BMASIGNIFICANCE",   ds::fkData,  ds::ftDouble,      8 },
    {   9,  offsetof(tblBMA_map,MCIID_),             "MCIID",             ds::fkData,  ds::ftInteger,     4 },
    {  10,  offsetof(tblBMA_map,CODCODE_),           "CODCODE",           ds::fkData,  ds::ftString,     30 },
    {  11,  offsetof(tblBMA_map,ITMNAME_),           "ITMNAME",           ds::fkData,  ds::ftString,     60 },
    {  12,  offsetof(tblBMA_map,DFVCODE1_),          "DFVCODE1",          ds::fkData,  ds::ftString,     20 },
    {  13,  offsetof(tblBMA_map,DFVCODE2_),          "DFVCODE2",          ds::fkData,  ds::ftString,     20 },
    {  14,  offsetof(tblBMA_map,DFVCODE3_),          "DFVCODE3",          ds::fkData,  ds::ftString,     20 },
    {  15,  offsetof(tblBMA_map,DFVCODE4_),          "DFVCODE4",          ds::fkData,  ds::ftString,     20 },
    {  16,  offsetof(tblBMA_map,DFVCODE5_),          "DFVCODE5",          ds::fkData,  ds::ftString,     20 },
    {  17,  offsetof(tblBMA_map,DFVCODE6_),          "DFVCODE6",          ds::fkData,  ds::ftString,     20 },
    {  18,  offsetof(tblBMA_map,DFVCODE7_),          "DFVCODE7",          ds::fkData,  ds::ftString,     20 },
    {  19,  offsetof(tblBMA_map,WRHID_),             "WRHID",             ds::fkData,  ds::ftInteger,     4 },
    {  20,  offsetof(tblBMA_map,WRHCODE_),           "WRHCODE",           ds::fkData,  ds::ftString,      4 },
    {  21,  offsetof(tblBMA_map,WRHNAME_),           "WRHNAME",           ds::fkData,  ds::ftString,     40 },
    {  22,  offsetof(tblBMA_map,ROTID_),             "ROTID",             ds::fkData,  ds::ftInteger,     4 },
    {  23,  offsetof(tblBMA_map,ROAID_),             "ROAID",             ds::fkData,  ds::ftInteger,     4 },
    {  24,  offsetof(tblBMA_map,OPRCODE_),           "OPRCODE",           ds::fkData,  ds::ftString,     20 },
    {  25,  offsetof(tblBMA_map,OPRDESCRIPTION_),    "OPRDESCRIPTION",    ds::fkData,  ds::ftString,     40 },
    {  26,  offsetof(tblBMA_map,ROALINENO_),         "ROALINENO",         ds::fkData,  ds::ftInteger,     4 },
    {  27,  offsetof(tblBMA_map,BMACONSREPTYPE_),    "BMACONSREPTYPE",    ds::fkData,  ds::ftShort,       2 },
    {  28,  offsetof(tblBMA_map,WRHIDCONS_),         "WRHIDCONS",         ds::fkData,  ds::ftInteger,     4 },
    {  29,  offsetof(tblBMA_map,WRHCONSCODE_),       "WRHCONSCODE",       ds::fkData,  ds::ftString,      4 },
    {  30,  offsetof(tblBMA_map,WRHCONSNAME_),       "WRHCONSNAME",       ds::fkData,  ds::ftString,     40 },
    {  31,  offsetof(tblBMA_map,UNISHORTNAMEA_),     "UNISHORTNAMEA",     ds::fkData,  ds::ftString,      4 },
    {  32,  offsetof(tblBMA_map,UNISHORTNAMEB_),     "UNISHORTNAMEB",     ds::fkData,  ds::ftString,      4 },
    {  33,  offsetof(tblBMA_map,BMANETQUANTITYA_),   "BMANETQUANTITYA",   ds::fkData,  ds::ftDouble,      8 },
    {  34,  offsetof(tblBMA_map,BMANETQUANTITYB_),   "BMANETQUANTITYB",   ds::fkData,  ds::ftDouble,      8 },
    {  35,  offsetof(tblBMA_map,BMACOSTBEHAVIOUR_),  "BMACOSTBEHAVIOUR",  ds::fkData,  ds::ftInteger,     4 },
    {  36,  offsetof(tblBMA_map,DFTID_),             "DFTID",             ds::fkData,  ds::ftInteger,     4 },
    {  37,  offsetof(tblBMA_map,DFAID1_),            "DFAID1",            ds::fkData,  ds::ftInteger,     4 },
    {  38,  offsetof(tblBMA_map,DFAID2_),            "DFAID2",            ds::fkData,  ds::ftInteger,     4 },
    {  39,  offsetof(tblBMA_map,DFAID3_),            "DFAID3",            ds::fkData,  ds::ftInteger,     4 },
    {  40,  offsetof(tblBMA_map,DFAID4_),            "DFAID4",            ds::fkData,  ds::ftInteger,     4 },
    {  41,  offsetof(tblBMA_map,DFAID5_),            "DFAID5",            ds::fkData,  ds::ftInteger,     4 },
    {  42,  offsetof(tblBMA_map,DFAID6_),            "DFAID6",            ds::fkData,  ds::ftInteger,     4 },
    {  43,  offsetof(tblBMA_map,DFAID7_),            "DFAID7",            ds::fkData,  ds::ftInteger,     4 },
    {  44,  offsetof(tblBMA_map,BMADFAID1SLAVE_),    "BMADFAID1SLAVE",    ds::fkData,  ds::ftShort,       2 },
    {  45,  offsetof(tblBMA_map,BMADFAID2SLAVE_),    "BMADFAID2SLAVE",    ds::fkData,  ds::ftShort,       2 },
    {  46,  offsetof(tblBMA_map,BMADFAID3SLAVE_),    "BMADFAID3SLAVE",    ds::fkData,  ds::ftShort,       2 },
    {  47,  offsetof(tblBMA_map,BMADFAID4SLAVE_),    "BMADFAID4SLAVE",    ds::fkData,  ds::ftShort,       2 },
    {  48,  offsetof(tblBMA_map,BMADFAID5SLAVE_),    "BMADFAID5SLAVE",    ds::fkData,  ds::ftShort,       2 },
    {  49,  offsetof(tblBMA_map,BMADFAID6SLAVE_),    "BMADFAID6SLAVE",    ds::fkData,  ds::ftShort,       2 },
    {  50,  offsetof(tblBMA_map,BMADFAID7SLAVE_),    "BMADFAID7SLAVE",    ds::fkData,  ds::ftShort,       2 },
    {  51,  offsetof(tblBMA_map,UNIIDA_),            "UNIIDA",            ds::fkData,  ds::ftInteger,     4 },
    {  52,  offsetof(tblBMA_map,UNIIDB_),            "UNIIDB",            ds::fkData,  ds::ftInteger,     4 },
    {  53,  offsetof(tblBMA_map,BMALINENO_),         "BMALINENO",         ds::fkData,  ds::ftInteger,     4 },
    {  54,  offsetof(tblBMA_map,BMAISRECYCLE_),      "BMAISRECYCLE",      ds::fkData,  ds::ftShort,       2 },
};

const ds::cFieldDefs_  tblBMA_data::tblBMA_FieldDef =
{
    sizeof(tblBMA_map),
    sizeof(tblBMA_Fields)/sizeof(tblBMA_Fields[0]),
    "SELECT BMAID, BOMID, BMAQUANTITYA, BMAQUANTITYB, BMALOSS, BMALOSSTYPE, BMAINSTRUCTIONS, BMAQUANTIZETYPE,"
    "       BMASIGNIFICANCE, MCIID, CODCODE, ITMNAME, DFVCODE1, DFVCODE2, DFVCODE3, DFVCODE4, DFVCODE5,"
    "       DFVCODE6, DFVCODE7, WRHID, WRHCODE, WRHNAME, ROTID, ROAID, OPRCODE, OPRDESCRIPTION, ROALINENO,"
    "       BMACONSREPTYPE, WRHIDCONS, WRHCONSCODE, WRHCONSNAME, UNISHORTNAMEA, UNISHORTNAMEB,"
    "       BMANETQUANTITYA, BMANETQUANTITYB, BMACOSTBEHAVIOUR, DFTID, DFAID1, DFAID2, DFAID3, DFAID4, DFAID5,"
    "       DFAID6, DFAID7, BMADFAID1SLAVE, BMADFAID2SLAVE, BMADFAID3SLAVE, BMADFAID4SLAVE, BMADFAID5SLAVE,"
    "       BMADFAID6SLAVE, BMADFAID7SLAVE, UNIIDA, UNIIDB, BMALINENO, BMAISRECYCLE "
    "FROM PDC_BMA",
    "BMA",
    tblBMA_Fields
};

const ds::cFieldDefs_& FASTCALL tblBMA_rec::GetFieldDefs()  { return ( tblBMA_FieldDef ); }
//***********************************************************************
//******    tblSPN
//***********************************************************************
const ds::cFieldDef_  tblSPN_data::tblSPN_Fields[] =
{
    {   0,  offsetof(tblSPN_map,MCIID_),             "MCIID",             ds::fkData,  ds::ftInteger,     4 },
    {   1,  offsetof(tblSPN_map,SPNPRODTYPE_),       "SPNPRODTYPE",       ds::fkData,  ds::ftShort,       2 },
    {   2,  offsetof(tblSPN_map,SPNCONSREPTYPE_),    "SPNCONSREPTYPE",    ds::fkData,  ds::ftShort,       2 },
    {   3,  offsetof(tblSPN_map,SPNPRODREPTYPE_),    "SPNPRODREPTYPE",    ds::fkData,  ds::ftShort,       2 },
    {   4,  offsetof(tblSPN_map,SPNTIMEREPTYPE_),    "SPNTIMEREPTYPE",    ds::fkData,  ds::ftShort,       2 },
    {   5,  offsetof(tblSPN_map,SPNLLC_),            "SPNLLC",            ds::fkData,  ds::ftInteger,     4 },
    {   6,  offsetof(tblSPN_map,CODCODE_),           "CODCODE",           ds::fkData,  ds::ftString,     30 },
    {   7,  offsetof(tblSPN_map,ITMNAME_),           "ITMNAME",           ds::fkData,  ds::ftString,     60 },
    {   8,  offsetof(tblSPN_map,PICID_),             "PICID",             ds::fkData,  ds::ftInteger,     4 },
    {   9,  offsetof(tblSPN_map,PICCODE_),           "PICCODE",           ds::fkData,  ds::ftString,     25 },
    {  10,  offsetof(tblSPN_map,PICDESCRIPTION_),    "PICDESCRIPTION",    ds::fkData,  ds::ftString,     40 },
    {  11,  offsetof(tblSPN_map,UNISHORTNAMEA_),     "UNISHORTNAMEA",     ds::fkData,  ds::ftString,      4 },
    {  12,  offsetof(tblSPN_map,UNISHORTNAMEB_),     "UNISHORTNAMEB",     ds::fkData,  ds::ftString,      4 },
    {  13,  offsetof(tblSPN_map,SPNDFVGROUP_),       "SPNDFVGROUP",       ds::fkData,  ds::ftShort,       2 },
    {  14,  offsetof(tblSPN_map,SPNCOSTBEHAVIOUR_),  "SPNCOSTBEHAVIOUR",  ds::fkData,  ds::ftInteger,     4 },
    {  15,  offsetof(tblSPN_map,SPNORDERTRACKING_),  "SPNORDERTRACKING",  ds::fkData,  ds::ftShort,       2 },
};

const ds::cFieldDefs_  tblSPN_data::tblSPN_FieldDef =
{
    sizeof(tblSPN_map),
    sizeof(tblSPN_Fields)/sizeof(tblSPN_Fields[0]),
    "SELECT MCIID, SPNPRODTYPE, SPNCONSREPTYPE, SPNPRODREPTYPE, SPNTIMEREPTYPE, SPNLLC, CODCODE, ITMNAME,"
    "       PICID, PICCODE, PICDESCRIPTION, UNISHORTNAMEA, UNISHORTNAMEB, SPNDFVGROUP, SPNCOSTBEHAVIOUR,"
    "       SPNORDERTRACKING "
    "FROM PDC_SPN",
    "SPN",
    tblSPN_Fields
};

const ds::cFieldDefs_& FASTCALL tblSPN_rec::GetFieldDefs()  { return ( tblSPN_FieldDef ); }
//***********************************************************************
//******    tblAIP
//***********************************************************************
const ds::cFieldDef_  tblAIP_data::tblAIP_Fields[] =
{
    {   0,  offsetof(tblAIP_map,MCIID_),           "MCIID",           ds::fkData,  ds::ftInteger,     4 },
    {   1,  offsetof(tblAIP_map,DFVCODE1_),        "DFVCODE1",        ds::fkData,  ds::ftString,     20 },
    {   2,  offsetof(tblAIP_map,DFVCODE2_),        "DFVCODE2",        ds::fkData,  ds::ftString,     20 },
    {   3,  offsetof(tblAIP_map,DFVCODE3_),        "DFVCODE3",        ds::fkData,  ds::ftString,     20 },
    {   4,  offsetof(tblAIP_map,DFVCODE4_),        "DFVCODE4",        ds::fkData,  ds::ftString,     20 },
    {   5,  offsetof(tblAIP_map,DFVCODE5_),        "DFVCODE5",        ds::fkData,  ds::ftString,     20 },
    {   6,  offsetof(tblAIP_map,DFVCODE6_),        "DFVCODE6",        ds::fkData,  ds::ftString,     20 },
    {   7,  offsetof(tblAIP_map,DFVCODE7_),        "DFVCODE7",        ds::fkData,  ds::ftString,     20 },
    {   8,  offsetof(tblAIP_map,PICID_),           "PICID",           ds::fkData,  ds::ftInteger,     4 },
    {   9,  offsetof(tblAIP_map,PICCODE_),         "PICCODE",         ds::fkData,  ds::ftString,     25 },
    {  10,  offsetof(tblAIP_map,PICDESCRIPTION_),  "PICDESCRIPTION",  ds::fkData,  ds::ftString,     40 },
};

const ds::cFieldDefs_  tblAIP_data::tblAIP_FieldDef =
{
    sizeof(tblAIP_map),
    sizeof(tblAIP_Fields)/sizeof(tblAIP_Fields[0]),
    "SELECT MCIID, DFVCODE1, DFVCODE2, DFVCODE3, DFVCODE4, DFVCODE5, DFVCODE6, DFVCODE7, PICID, PICCODE, PICDESCRIPTION "
    "FROM PDC_AIP",
    "AIP",
    tblAIP_Fields
};

const ds::cFieldDefs_& FASTCALL tblAIP_rec::GetFieldDefs()  { return ( tblAIP_FieldDef ); }
//***********************************************************************
//******    tblPIC
//***********************************************************************
const ds::cFieldDef_  tblPIC_data::tblPIC_Fields[] =
{
    {   0,  offsetof(tblPIC_map,PICID_),              "PICID",              ds::fkData,  ds::ftInteger,     4 },
    {   1,  offsetof(tblPIC_map,PICCODE_),            "PICCODE",            ds::fkData,  ds::ftString,     25 },
    {   2,  offsetof(tblPIC_map,PICDESCRIPTION_),     "PICDESCRIPTION",     ds::fkData,  ds::ftString,     40 },
    {   3,  offsetof(tblPIC_map,PICQTYSAFETYSTOCK_),  "PICQTYSAFETYSTOCK",  ds::fkData,  ds::ftDouble,      8 },
    {   4,  offsetof(tblPIC_map,PICLEADTIME_),        "PICLEADTIME",        ds::fkData,  ds::ftInteger,     4 },
    {   5,  offsetof(tblPIC_map,PICLOTPOLICY_),       "PICLOTPOLICY",       ds::fkData,  ds::ftShort,       2 },
    {   6,  offsetof(tblPIC_map,PICLOTQTY_),          "PICLOTQTY",          ds::fkData,  ds::ftDouble,      8 },
};

const ds::cFieldDefs_  tblPIC_data::tblPIC_FieldDef =
{
    sizeof(tblPIC_map),
    sizeof(tblPIC_Fields)/sizeof(tblPIC_Fields[0]),
    "SELECT PICID, PICCODE, PICDESCRIPTION, PICQTYSAFETYSTOCK, PICLEADTIME, PICLOTPOLICY, PICLOTQTY "
    "FROM PIC",
    "PIC",
    tblPIC_Fields
};

const ds::cFieldDefs_& FASTCALL tblPIC_rec::GetFieldDefs()  { return ( tblPIC_FieldDef ); }
//***********************************************************************
//******    tblPRN
//***********************************************************************
const ds::cFieldDef_  tblPRN_data::tblPRN_Fields[] =
{
    {   0,  offsetof(tblPRN_map,PRNID_),             "PRNID",             ds::fkData,  ds::ftInteger,      4 },
    {   1,  offsetof(tblPRN_map,PRNCODE_),           "PRNCODE",           ds::fkData,  ds::ftString,      30 },
    {   2,  offsetof(tblPRN_map,MCIID_),             "MCIID",             ds::fkData,  ds::ftInteger,      4 },
    {   3,  offsetof(tblPRN_map,CODCODE_),           "CODCODE",           ds::fkData,  ds::ftString,      30 },
    {   4,  offsetof(tblPRN_map,ITMNAME_),           "ITMNAME",           ds::fkData,  ds::ftString,      60 },
    {   5,  offsetof(tblPRN_map,DFVCODE1_),          "DFVCODE1",          ds::fkData,  ds::ftString,      20 },
    {   6,  offsetof(tblPRN_map,DFVCODE2_),          "DFVCODE2",          ds::fkData,  ds::ftString,      20 },
    {   7,  offsetof(tblPRN_map,DFVCODE3_),          "DFVCODE3",          ds::fkData,  ds::ftString,      20 },
    {   8,  offsetof(tblPRN_map,DFVCODE4_),          "DFVCODE4",          ds::fkData,  ds::ftString,      20 },
    {   9,  offsetof(tblPRN_map,DFVCODE5_),          "DFVCODE5",          ds::fkData,  ds::ftString,      20 },
    {  10,  offsetof(tblPRN_map,DFVCODE6_),          "DFVCODE6",          ds::fkData,  ds::ftString,      20 },
    {  11,  offsetof(tblPRN_map,DFVCODE7_),          "DFVCODE7",          ds::fkData,  ds::ftString,      20 },
    {  12,  offsetof(tblPRN_map,PRNTOTQUANTITY_),    "PRNTOTQUANTITY",    ds::fkData,  ds::ftDouble,       8 },
    {  13,  offsetof(tblPRN_map,PRNTOTQUANTITYB_),   "PRNTOTQUANTITYB",   ds::fkData,  ds::ftDouble,       8 },
    {  14,  offsetof(tblPRN_map,PRNREMQUANTITY_),    "PRNREMQUANTITY",    ds::fkData,  ds::ftDouble,       8 },
    {  15,  offsetof(tblPRN_map,PRNREMQUANTITYB_),   "PRNREMQUANTITYB",   ds::fkData,  ds::ftDouble,       8 },
    {  16,  offsetof(tblPRN_map,PRNEARLDELIVDATE_),  "PRNEARLDELIVDATE",  ds::fkData,  ds::ftDateTime,     8 },
    {  17,  offsetof(tblPRN_map,PRNLATEDELIVDATE_),  "PRNLATEDELIVDATE",  ds::fkData,  ds::ftDateTime,     8 },
    {  18,  offsetof(tblPRN_map,PRNPRIORITY_),       "PRNPRIORITY",       ds::fkData,  ds::ftShort,        2 },
    {  19,  offsetof(tblPRN_map,BOMID_),             "BOMID",             ds::fkData,  ds::ftInteger,      4 },
    {  20,  offsetof(tblPRN_map,BOMCODE_),           "BOMCODE",           ds::fkData,  ds::ftString,      20 },
    {  21,  offsetof(tblPRN_map,BOMDESCRIPTION_),    "BOMDESCRIPTION",    ds::fkData,  ds::ftString,      40 },
    {  22,  offsetof(tblPRN_map,BTGCODE_),           "BTGCODE",           ds::fkData,  ds::ftString,      20 },
    {  23,  offsetof(tblPRN_map,BTGDESCRIPTION_),    "BTGDESCRIPTION",    ds::fkData,  ds::ftString,      40 },
    {  24,  offsetof(tblPRN_map,WRHID_),             "WRHID",             ds::fkData,  ds::ftInteger,      4 },
    {  25,  offsetof(tblPRN_map,PRNDESCRIPTION_),    "PRNDESCRIPTION",    ds::fkData,  ds::ftString,      40 },
    {  26,  offsetof(tblPRN_map,WRHCODE_),           "WRHCODE",           ds::fkData,  ds::ftString,       4 },
    {  27,  offsetof(tblPRN_map,WRHNAME_),           "WRHNAME",           ds::fkData,  ds::ftString,      40 },
    {  28,  offsetof(tblPRN_map,PRNSTATUS_),         "PRNSTATUS",         ds::fkData,  ds::ftShort,        2 },
    {  29,  offsetof(tblPRN_map,MRPQUANTITYA_),      "MRPQUANTITYA",      ds::fkData,  ds::ftDouble,       8 },
    {  30,  offsetof(tblPRN_map,MRPQUANTITYB_),      "MRPQUANTITYB",      ds::fkData,  ds::ftDouble,       8 },
    {  31,  offsetof(tblPRN_map,MPSQUANTITYA_),      "MPSQUANTITYA",      ds::fkData,  ds::ftDouble,       8 },
    {  32,  offsetof(tblPRN_map,MPSQUANTITYB_),      "MPSQUANTITYB",      ds::fkData,  ds::ftDouble,       8 },
    {  33,  offsetof(tblPRN_map,UNISHORTNAMEA_),     "UNISHORTNAMEA",     ds::fkData,  ds::ftString,       4 },
    {  34,  offsetof(tblPRN_map,UNISHORTNAMEB_),     "UNISHORTNAMEB",     ds::fkData,  ds::ftString,       4 },
    {  35,  offsetof(tblPRN_map,UNIIDA_),            "UNIIDA",            ds::fkData,  ds::ftInteger,      4 },
    {  36,  offsetof(tblPRN_map,UNIIDB_),            "UNIIDB",            ds::fkData,  ds::ftInteger,      4 },
    {  37,  offsetof(tblPRN_map,PRNSTARTWEEK_),      "PRNSTARTWEEK",      ds::fkData,  ds::ftDouble,       8 },
    {  38,  offsetof(tblPRN_map,PRNENDWEEK_),        "PRNENDWEEK",        ds::fkData,  ds::ftDouble,       8 },
    {  39,  offsetof(tblPRN_map,PRNCOMMENT_),        "PRNCOMMENT",        ds::fkData,  ds::ftString,     255 },
};

const ds::cFieldDefs_  tblPRN_data::tblPRN_FieldDef =
{
    sizeof(tblPRN_map),
    sizeof(tblPRN_Fields)/sizeof(tblPRN_Fields[0]),
    "SELECT PRNID, PRNCODE, MCIID, CODCODE, ITMNAME, DFVCODE1, DFVCODE2, DFVCODE3, DFVCODE4, DFVCODE5,"
    "       DFVCODE6, DFVCODE7, PRNTOTQUANTITY, PRNTOTQUANTITYB, PRNREMQUANTITY, PRNREMQUANTITYB,"
    "       PRNEARLDELIVDATE, PRNLATEDELIVDATE, PRNPRIORITY, BOMID, BOMCODE, BOMDESCRIPTION, BTGCODE,"
    "       BTGDESCRIPTION, WRHID, PRNDESCRIPTION, WRHCODE, WRHNAME, PRNSTATUS, MRPQUANTITYA, MRPQUANTITYB,"
    "       MPSQUANTITYA, MPSQUANTITYB, UNISHORTNAMEA, UNISHORTNAMEB, UNIIDA, UNIIDB,"
    "       0.0 AS PRNSTARTWEEK, 0.0 AS PRNENDWEEK, PRNCOMMENT "
    "FROM PDC_PRN",
    "PRN",
    tblPRN_Fields
};

const ds::cFieldDefs_& FASTCALL tblPRN_rec::GetFieldDefs()  { return ( tblPRN_FieldDef ); }
//---------------------------------------------------------------------------
