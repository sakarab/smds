//---------------------------------------------------------------------------
#pragma hdrstop

#include "uCustomTables.h"
//---------------------------------------------------------------------------

//***********************************************************************
//******    tblFirstScanDataset
//***********************************************************************
const ds::cFieldDef_  tblFirstScanDataset_data::tblFirstScanDataset_Fields[] =
{
    {   0,  offsetof(tblFirstScanDataset_map,MCIID_),        "MCIID",        ds::fkData,  ds::ftInteger,     4 },
    {   1,  offsetof(tblFirstScanDataset_map,DFVCODE1_),     "DFVCODE1",     ds::fkData,  ds::ftString,     20 },
    {   2,  offsetof(tblFirstScanDataset_map,DFVCODE2_),     "DFVCODE2",     ds::fkData,  ds::ftString,     20 },
    {   3,  offsetof(tblFirstScanDataset_map,DFVCODE3_),     "DFVCODE3",     ds::fkData,  ds::ftString,     20 },
    {   4,  offsetof(tblFirstScanDataset_map,DFVCODE4_),     "DFVCODE4",     ds::fkData,  ds::ftString,     20 },
    {   5,  offsetof(tblFirstScanDataset_map,DFVCODE5_),     "DFVCODE5",     ds::fkData,  ds::ftString,     20 },
    {   6,  offsetof(tblFirstScanDataset_map,DFVCODE6_),     "DFVCODE6",     ds::fkData,  ds::ftString,     20 },
    {   7,  offsetof(tblFirstScanDataset_map,DFVCODE7_),     "DFVCODE7",     ds::fkData,  ds::ftString,     20 },
    {   8,  offsetof(tblFirstScanDataset_map,LLC_),          "LLC",          ds::fkData,  ds::ftDouble,      8 },
    {   9,  offsetof(tblFirstScanDataset_map,LOTSIZE_),      "LOTSIZE",      ds::fkData,  ds::ftDouble,      8 },
    {  10,  offsetof(tblFirstScanDataset_map,LEADTIME_),     "LEADTIME",     ds::fkData,  ds::ftDouble,      8 },
    {  11,  offsetof(tblFirstScanDataset_map,SAFETYSTOCK_),  "SAFETYSTOCK",  ds::fkData,  ds::ftDouble,      8 },
    {  12,  offsetof(tblFirstScanDataset_map,LOTPOLICY_),    "LOTPOLICY",    ds::fkData,  ds::ftDouble,      8 },
};

const ds::cFieldDefs_  tblFirstScanDataset_data::tblFirstScanDataset_FieldDef =
{
    sizeof(tblFirstScanDataset_map),
    sizeof(tblFirstScanDataset_Fields)/sizeof(tblFirstScanDataset_Fields[0]),
    "SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s",
    "FirstScanDataset",
    tblFirstScanDataset_Fields
};

const ds::cFieldDefs_& FASTCALL tblFirstScanDataset_rec::GetFieldDefs()  { return ( tblFirstScanDataset_FieldDef ); }
//***********************************************************************
//******    tblHelpDataset
//***********************************************************************
const ds::cFieldDef_  tblHelpDataset_data::tblHelpDataset_Fields[] =
{
    {   0,  offsetof(tblHelpDataset_map,ID_),          "ID",          ds::fkData,  ds::ftInteger,      4 },
    {   1,  offsetof(tblHelpDataset_map,MCIID_),       "MCIID",       ds::fkData,  ds::ftInteger,      4 },
    {   2,  offsetof(tblHelpDataset_map,DFVCODE1_),    "DFVCODE1",    ds::fkData,  ds::ftString,      20 },
    {   3,  offsetof(tblHelpDataset_map,DFVCODE2_),    "DFVCODE2",    ds::fkData,  ds::ftString,      20 },
    {   4,  offsetof(tblHelpDataset_map,DFVCODE3_),    "DFVCODE3",    ds::fkData,  ds::ftString,      20 },
    {   5,  offsetof(tblHelpDataset_map,DFVCODE4_),    "DFVCODE4",    ds::fkData,  ds::ftString,      20 },
    {   6,  offsetof(tblHelpDataset_map,DFVCODE5_),    "DFVCODE5",    ds::fkData,  ds::ftString,      20 },
    {   7,  offsetof(tblHelpDataset_map,DFVCODE6_),    "DFVCODE6",    ds::fkData,  ds::ftString,      20 },
    {   8,  offsetof(tblHelpDataset_map,DFVCODE7_),    "DFVCODE7",    ds::fkData,  ds::ftString,      20 },
    {   9,  offsetof(tblHelpDataset_map,WEEK_),        "WEEK",        ds::fkData,  ds::ftInteger,      4 },
    {  10,  offsetof(tblHelpDataset_map,YEAR_),        "YEAR",        ds::fkData,  ds::ftInteger,      4 },
    {  11,  offsetof(tblHelpDataset_map,GROSSREQ_),    "GROSSREQ",    ds::fkData,  ds::ftDouble,       8 },
    {  12,  offsetof(tblHelpDataset_map,SCHEDREQ_),    "SCHEDREQ",    ds::fkData,  ds::ftDouble,       8 },
    {  13,  offsetof(tblHelpDataset_map,PROJONHAND_),  "PROJONHAND",  ds::fkData,  ds::ftDouble,       8 },
    {  14,  offsetof(tblHelpDataset_map,NETREQ_),      "NETREQ",      ds::fkData,  ds::ftDouble,       8 },
    {  15,  offsetof(tblHelpDataset_map,REQPO_),       "REQPO",       ds::fkData,  ds::ftDouble,       8 },
    {  16,  offsetof(tblHelpDataset_map,RELPO_),       "RELPO",       ds::fkData,  ds::ftDouble,       8 },
    {  17,  offsetof(tblHelpDataset_map,PROJAVBAL_),   "PROJAVBAL",   ds::fkData,  ds::ftDouble,       8 },
    {  18,  offsetof(tblHelpDataset_map,EXPECTED_),    "EXPECTED",    ds::fkData,  ds::ftDouble,       8 },
    {  19,  offsetof(tblHelpDataset_map,TIED_),        "TIED",        ds::fkData,  ds::ftDouble,       8 },
    {  20,  offsetof(tblHelpDataset_map,DAYS_),        "DAYS",        ds::fkData,  ds::ftInteger,      4 },
    {  21,  offsetof(tblHelpDataset_map,DATE_),        "DATE",        ds::fkData,  ds::ftDateTime,     8 },
};

const ds::cFieldDefs_  tblHelpDataset_data::tblHelpDataset_FieldDef =
{
    sizeof(tblHelpDataset_map),
    sizeof(tblHelpDataset_Fields)/sizeof(tblHelpDataset_Fields[0]),
    "SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s",
    "HelpDataset",
    tblHelpDataset_Fields
};

const ds::cFieldDefs_& FASTCALL tblHelpDataset_rec::GetFieldDefs()  { return ( tblHelpDataset_FieldDef ); }
//***********************************************************************
//******    tblHelpDatasetDetail
//***********************************************************************
const ds::cFieldDef_  tblHelpDatasetDetail_data::tblHelpDatasetDetail_Fields[] =
{
    {   0,  offsetof(tblHelpDatasetDetail_map,ID_),       "ID",       ds::fkData,  ds::ftInteger,     4 },
    {   1,  offsetof(tblHelpDatasetDetail_map,DOCID_),    "DOCID",    ds::fkData,  ds::ftInteger,     4 },
    {   2,  offsetof(tblHelpDatasetDetail_map,LINENO_),   "LINENO",   ds::fkData,  ds::ftInteger,     4 },
    {   3,  offsetof(tblHelpDatasetDetail_map,INITQTY_),  "INITQTY",  ds::fkData,  ds::ftDouble,      8 },
};

const ds::cFieldDefs_  tblHelpDatasetDetail_data::tblHelpDatasetDetail_FieldDef =
{
    sizeof(tblHelpDatasetDetail_map),
    sizeof(tblHelpDatasetDetail_Fields)/sizeof(tblHelpDatasetDetail_Fields[0]),
    "SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s",
    "HelpDatasetDetail",
    tblHelpDatasetDetail_Fields
};

const ds::cFieldDefs_& FASTCALL tblHelpDatasetDetail_rec::GetFieldDefs()  { return ( tblHelpDatasetDetail_FieldDef ); }
//***********************************************************************
//******    tblHelpDatasetDetailRELPO
//***********************************************************************
const ds::cFieldDef_  tblHelpDatasetDetailRELPO_data::tblHelpDatasetDetailRELPO_Fields[] =
{
    {   0,  offsetof(tblHelpDatasetDetailRELPO_map,ID_),      "ID",      ds::fkData,  ds::ftInteger,     4 },
    {   1,  offsetof(tblHelpDatasetDetailRELPO_map,DOCID_),   "DOCID",   ds::fkData,  ds::ftInteger,     4 },
    {   2,  offsetof(tblHelpDatasetDetailRELPO_map,LINENO_),  "LINENO",  ds::fkData,  ds::ftInteger,     4 },
};

const ds::cFieldDefs_  tblHelpDatasetDetailRELPO_data::tblHelpDatasetDetailRELPO_FieldDef =
{
    sizeof(tblHelpDatasetDetailRELPO_map),
    sizeof(tblHelpDatasetDetailRELPO_Fields)/sizeof(tblHelpDatasetDetailRELPO_Fields[0]),
    "SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s",
    "HelpDatasetDetailRELPO",
    tblHelpDatasetDetailRELPO_Fields
};

const ds::cFieldDefs_& FASTCALL tblHelpDatasetDetailRELPO_rec::GetFieldDefs()  { return ( tblHelpDatasetDetailRELPO_FieldDef ); }
//***********************************************************************
//******    tblPEGGING
//***********************************************************************
const ds::cFieldDef_  tblPEGGING_data::tblPEGGING_Fields[] =
{
    {   0,  offsetof(tblPEGGING_map,PEGID_),        "PEGID",        ds::fkData,  ds::ftInteger,      4 },
    {   1,  offsetof(tblPEGGING_map,MCIID_),        "MCIID",        ds::fkData,  ds::ftInteger,      4 },
    {   2,  offsetof(tblPEGGING_map,DFVCODE1_),     "DFVCODE1",     ds::fkData,  ds::ftString,      20 },
    {   3,  offsetof(tblPEGGING_map,DFVCODE2_),     "DFVCODE2",     ds::fkData,  ds::ftString,      20 },
    {   4,  offsetof(tblPEGGING_map,DFVCODE3_),     "DFVCODE3",     ds::fkData,  ds::ftString,      20 },
    {   5,  offsetof(tblPEGGING_map,DFVCODE4_),     "DFVCODE4",     ds::fkData,  ds::ftString,      20 },
    {   6,  offsetof(tblPEGGING_map,DFVCODE5_),     "DFVCODE5",     ds::fkData,  ds::ftString,      20 },
    {   7,  offsetof(tblPEGGING_map,DFVCODE6_),     "DFVCODE6",     ds::fkData,  ds::ftString,      20 },
    {   8,  offsetof(tblPEGGING_map,DFVCODE7_),     "DFVCODE7",     ds::fkData,  ds::ftString,      20 },
    {   9,  offsetof(tblPEGGING_map,SRCMCIID_),     "SRCMCIID",     ds::fkData,  ds::ftInteger,      4 },
    {  10,  offsetof(tblPEGGING_map,SRCDFVCODE1_),  "SRCDFVCODE1",  ds::fkData,  ds::ftString,      20 },
    {  11,  offsetof(tblPEGGING_map,SRCDFVCODE2_),  "SRCDFVCODE2",  ds::fkData,  ds::ftString,      20 },
    {  12,  offsetof(tblPEGGING_map,SRCDFVCODE3_),  "SRCDFVCODE3",  ds::fkData,  ds::ftString,      20 },
    {  13,  offsetof(tblPEGGING_map,SRCDFVCODE4_),  "SRCDFVCODE4",  ds::fkData,  ds::ftString,      20 },
    {  14,  offsetof(tblPEGGING_map,SRCDFVCODE5_),  "SRCDFVCODE5",  ds::fkData,  ds::ftString,      20 },
    {  15,  offsetof(tblPEGGING_map,SRCDFVCODE6_),  "SRCDFVCODE6",  ds::fkData,  ds::ftString,      20 },
    {  16,  offsetof(tblPEGGING_map,SRCDFVCODE7_),  "SRCDFVCODE7",  ds::fkData,  ds::ftString,      20 },
    {  17,  offsetof(tblPEGGING_map,PRNID_),        "PRNID",        ds::fkData,  ds::ftInteger,      4 },
    {  18,  offsetof(tblPEGGING_map,WEEK_),         "WEEK",         ds::fkData,  ds::ftInteger,      4 },
    {  19,  offsetof(tblPEGGING_map,YEAR_),         "YEAR",         ds::fkData,  ds::ftInteger,      4 },
    {  20,  offsetof(tblPEGGING_map,REQQTY_),       "REQQTY",       ds::fkData,  ds::ftDouble,       8 },
    {  21,  offsetof(tblPEGGING_map,DATE_),         "DATE",         ds::fkData,  ds::ftDateTime,     8 },
};

const ds::cFieldDefs_  tblPEGGING_data::tblPEGGING_FieldDef =
{
    sizeof(tblPEGGING_map),
    sizeof(tblPEGGING_Fields)/sizeof(tblPEGGING_Fields[0]),
    "SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s",
    "PEGGING",
    tblPEGGING_Fields
};

const ds::cFieldDefs_& FASTCALL tblPEGGING_rec::GetFieldDefs()  { return ( tblPEGGING_FieldDef ); }
//***********************************************************************
//******    tblFromPriorLevel
//***********************************************************************
const ds::cFieldDef_  tblFromPriorLevel_data::tblFromPriorLevel_Fields[] =
{
    {   0,  offsetof(tblFromPriorLevel_map,ID_),        "ID",        ds::fkData,  ds::ftInteger,      4 },
    {   1,  offsetof(tblFromPriorLevel_map,MCIID_),     "MCIID",     ds::fkData,  ds::ftInteger,      4 },
    {   2,  offsetof(tblFromPriorLevel_map,DFVCODE1_),  "DFVCODE1",  ds::fkData,  ds::ftString,      20 },
    {   3,  offsetof(tblFromPriorLevel_map,DFVCODE2_),  "DFVCODE2",  ds::fkData,  ds::ftString,      20 },
    {   4,  offsetof(tblFromPriorLevel_map,DFVCODE3_),  "DFVCODE3",  ds::fkData,  ds::ftString,      20 },
    {   5,  offsetof(tblFromPriorLevel_map,DFVCODE4_),  "DFVCODE4",  ds::fkData,  ds::ftString,      20 },
    {   6,  offsetof(tblFromPriorLevel_map,DFVCODE5_),  "DFVCODE5",  ds::fkData,  ds::ftString,      20 },
    {   7,  offsetof(tblFromPriorLevel_map,DFVCODE6_),  "DFVCODE6",  ds::fkData,  ds::ftString,      20 },
    {   8,  offsetof(tblFromPriorLevel_map,DFVCODE7_),  "DFVCODE7",  ds::fkData,  ds::ftString,      20 },
    {   9,  offsetof(tblFromPriorLevel_map,WEEK_),      "WEEK",      ds::fkData,  ds::ftInteger,      4 },
    {  10,  offsetof(tblFromPriorLevel_map,YEAR_),      "YEAR",      ds::fkData,  ds::ftInteger,      4 },
    {  11,  offsetof(tblFromPriorLevel_map,QTY_),       "QTY",       ds::fkData,  ds::ftDouble,       8 },
    {  12,  offsetof(tblFromPriorLevel_map,DAYS_),      "DAYS",      ds::fkData,  ds::ftInteger,      4 },
    {  13,  offsetof(tblFromPriorLevel_map,DATE_),      "DATE",      ds::fkData,  ds::ftDateTime,     8 },
};

const ds::cFieldDefs_  tblFromPriorLevel_data::tblFromPriorLevel_FieldDef =
{
    sizeof(tblFromPriorLevel_map),
    sizeof(tblFromPriorLevel_Fields)/sizeof(tblFromPriorLevel_Fields[0]),
    "SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s",
    "FromPriorLevel",
    tblFromPriorLevel_Fields
};

const ds::cFieldDefs_& FASTCALL tblFromPriorLevel_rec::GetFieldDefs()  { return ( tblFromPriorLevel_FieldDef ); }
//***********************************************************************
//******    tblFromPriorLevelDetail
//***********************************************************************
const ds::cFieldDef_  tblFromPriorLevelDetail_data::tblFromPriorLevelDetail_Fields[] =
{
    {   0,  offsetof(tblFromPriorLevelDetail_map,ID_),      "ID",      ds::fkData,  ds::ftInteger,     4 },
    {   1,  offsetof(tblFromPriorLevelDetail_map,DOCID_),   "DOCID",   ds::fkData,  ds::ftInteger,     4 },
    {   2,  offsetof(tblFromPriorLevelDetail_map,LINENO_),  "LINENO",  ds::fkData,  ds::ftInteger,     4 },
};

const ds::cFieldDefs_  tblFromPriorLevelDetail_data::tblFromPriorLevelDetail_FieldDef =
{
    sizeof(tblFromPriorLevelDetail_map),
    sizeof(tblFromPriorLevelDetail_Fields)/sizeof(tblFromPriorLevelDetail_Fields[0]),
    "SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s",
    "FromPriorLevelDetail",
    tblFromPriorLevelDetail_Fields
};

const ds::cFieldDefs_& FASTCALL tblFromPriorLevelDetail_rec::GetFieldDefs()  { return ( tblFromPriorLevelDetail_FieldDef ); }
//***********************************************************************
//******    tblFromCurrentLevel
//***********************************************************************
const ds::cFieldDef_  tblFromCurrentLevel_data::tblFromCurrentLevel_Fields[] =
{
    {   0,  offsetof(tblFromCurrentLevel_map,ID_),        "ID",        ds::fkData,  ds::ftInteger,      4 },
    {   1,  offsetof(tblFromCurrentLevel_map,MCIID_),     "MCIID",     ds::fkData,  ds::ftInteger,      4 },
    {   2,  offsetof(tblFromCurrentLevel_map,DFVCODE1_),  "DFVCODE1",  ds::fkData,  ds::ftString,      20 },
    {   3,  offsetof(tblFromCurrentLevel_map,DFVCODE2_),  "DFVCODE2",  ds::fkData,  ds::ftString,      20 },
    {   4,  offsetof(tblFromCurrentLevel_map,DFVCODE3_),  "DFVCODE3",  ds::fkData,  ds::ftString,      20 },
    {   5,  offsetof(tblFromCurrentLevel_map,DFVCODE4_),  "DFVCODE4",  ds::fkData,  ds::ftString,      20 },
    {   6,  offsetof(tblFromCurrentLevel_map,DFVCODE5_),  "DFVCODE5",  ds::fkData,  ds::ftString,      20 },
    {   7,  offsetof(tblFromCurrentLevel_map,DFVCODE6_),  "DFVCODE6",  ds::fkData,  ds::ftString,      20 },
    {   8,  offsetof(tblFromCurrentLevel_map,DFVCODE7_),  "DFVCODE7",  ds::fkData,  ds::ftString,      20 },
    {   9,  offsetof(tblFromCurrentLevel_map,WEEK_),      "WEEK",      ds::fkData,  ds::ftInteger,      4 },
    {  10,  offsetof(tblFromCurrentLevel_map,YEAR_),      "YEAR",      ds::fkData,  ds::ftInteger,      4 },
    {  11,  offsetof(tblFromCurrentLevel_map,QTY_),       "QTY",       ds::fkData,  ds::ftDouble,       8 },
    {  12,  offsetof(tblFromCurrentLevel_map,DAYS_),      "DAYS",      ds::fkData,  ds::ftInteger,      4 },
    {  13,  offsetof(tblFromCurrentLevel_map,DATE_),      "DATE",      ds::fkData,  ds::ftDateTime,     8 },
};

const ds::cFieldDefs_  tblFromCurrentLevel_data::tblFromCurrentLevel_FieldDef =
{
    sizeof(tblFromCurrentLevel_map),
    sizeof(tblFromCurrentLevel_Fields)/sizeof(tblFromCurrentLevel_Fields[0]),
    "SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s",
    "FromCurrentLevel",
    tblFromCurrentLevel_Fields
};

const ds::cFieldDefs_& FASTCALL tblFromCurrentLevel_rec::GetFieldDefs()  { return ( tblFromCurrentLevel_FieldDef ); }
//***********************************************************************
//******    tblFromPrnLevel
//***********************************************************************
const ds::cFieldDef_  tblFromPrnLevel_data::tblFromPrnLevel_Fields[] =
{
    {   0,  offsetof(tblFromPrnLevel_map,ID_),        "ID",        ds::fkData,  ds::ftInteger,      4 },
    {   1,  offsetof(tblFromPrnLevel_map,MCIID_),     "MCIID",     ds::fkData,  ds::ftInteger,      4 },
    {   2,  offsetof(tblFromPrnLevel_map,DFVCODE1_),  "DFVCODE1",  ds::fkData,  ds::ftString,      20 },
    {   3,  offsetof(tblFromPrnLevel_map,DFVCODE2_),  "DFVCODE2",  ds::fkData,  ds::ftString,      20 },
    {   4,  offsetof(tblFromPrnLevel_map,DFVCODE3_),  "DFVCODE3",  ds::fkData,  ds::ftString,      20 },
    {   5,  offsetof(tblFromPrnLevel_map,DFVCODE4_),  "DFVCODE4",  ds::fkData,  ds::ftString,      20 },
    {   6,  offsetof(tblFromPrnLevel_map,DFVCODE5_),  "DFVCODE5",  ds::fkData,  ds::ftString,      20 },
    {   7,  offsetof(tblFromPrnLevel_map,DFVCODE6_),  "DFVCODE6",  ds::fkData,  ds::ftString,      20 },
    {   8,  offsetof(tblFromPrnLevel_map,DFVCODE7_),  "DFVCODE7",  ds::fkData,  ds::ftString,      20 },
    {   9,  offsetof(tblFromPrnLevel_map,WEEK_),      "WEEK",      ds::fkData,  ds::ftInteger,      4 },
    {  10,  offsetof(tblFromPrnLevel_map,YEAR_),      "YEAR",      ds::fkData,  ds::ftInteger,      4 },
    {  11,  offsetof(tblFromPrnLevel_map,QTY_),       "QTY",       ds::fkData,  ds::ftDouble,       8 },
    {  12,  offsetof(tblFromPrnLevel_map,DAYS_),      "DAYS",      ds::fkData,  ds::ftInteger,      4 },
    {  13,  offsetof(tblFromPrnLevel_map,DATE_),      "DATE",      ds::fkData,  ds::ftDateTime,     8 },
};

const ds::cFieldDefs_  tblFromPrnLevel_data::tblFromPrnLevel_FieldDef =
{
    sizeof(tblFromPrnLevel_map),
    sizeof(tblFromPrnLevel_Fields)/sizeof(tblFromPrnLevel_Fields[0]),
    "SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s",
    "FromPrnLevel",
    tblFromPrnLevel_Fields
};

const ds::cFieldDefs_& FASTCALL tblFromPrnLevel_rec::GetFieldDefs()  { return ( tblFromPrnLevel_FieldDef ); }
//***********************************************************************
//******    tblFromPrnLevelDetail
//***********************************************************************
const ds::cFieldDef_  tblFromPrnLevelDetail_data::tblFromPrnLevelDetail_Fields[] =
{
    {   0,  offsetof(tblFromPrnLevelDetail_map,ID_),      "ID",      ds::fkData,  ds::ftInteger,     4 },
    {   1,  offsetof(tblFromPrnLevelDetail_map,DOCID_),   "DOCID",   ds::fkData,  ds::ftInteger,     4 },
    {   2,  offsetof(tblFromPrnLevelDetail_map,LINENO_),  "LINENO",  ds::fkData,  ds::ftInteger,     4 },
};

const ds::cFieldDefs_  tblFromPrnLevelDetail_data::tblFromPrnLevelDetail_FieldDef =
{
    sizeof(tblFromPrnLevelDetail_map),
    sizeof(tblFromPrnLevelDetail_Fields)/sizeof(tblFromPrnLevelDetail_Fields[0]),
    "SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s",
    "FromPrnLevelDetail",
    tblFromPrnLevelDetail_Fields
};

const ds::cFieldDefs_& FASTCALL tblFromPrnLevelDetail_rec::GetFieldDefs()  { return ( tblFromPrnLevelDetail_FieldDef ); }
//***********************************************************************
//******    tblCAL
//***********************************************************************
const ds::cFieldDef_  tblCAL_data::tblCAL_Fields[] =
{
    {   0,  offsetof(tblCAL_map,CALDATE_),  "CALDATE",  ds::fkData,  ds::ftDateTime,     8 },
};

const ds::cFieldDefs_  tblCAL_data::tblCAL_FieldDef =
{
    sizeof(tblCAL_map),
    sizeof(tblCAL_Fields)/sizeof(tblCAL_Fields[0]),
    "SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s",
    "CAL",
    tblCAL_Fields
};

const ds::cFieldDefs_& FASTCALL tblCAL_rec::GetFieldDefs()  { return ( tblCAL_FieldDef ); }
//---------------------------------------------------------------------------
