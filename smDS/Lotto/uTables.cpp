//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "uTables.h"
//---------------------------------------------------------------------------

using namespace smds;
using namespace smds::detail;

//***********************************************************************
//******    tblFiles
//***********************************************************************
const cFieldDef_     DRAWS_data::DRAWS_Fields[] =
{
    { 0, offsetof(DRAWS_map,ID_),       "ID",       fkData, ftInteger,  4 },
    { 1, offsetof(DRAWS_map,DDate_),    "DDate",    fkData, ftDateTime, 8 },
    { 2, offsetof(DRAWS_map,Num_1_),    "Num_1",    fkData, ftChar,     1 },
    { 3, offsetof(DRAWS_map,Num_2_),    "Num_2",    fkData, ftChar,     1 },
    { 4, offsetof(DRAWS_map,Num_3_),    "Num_3",    fkData, ftChar,     1 },
    { 5, offsetof(DRAWS_map,Num_4_),    "Num_4",    fkData, ftChar,     1 },
    { 6, offsetof(DRAWS_map,Num_5_),    "Num_5",    fkData, ftChar,     1 },
    { 7, offsetof(DRAWS_map,Num_6_),    "Num_6",    fkData, ftChar,     1 },
};

const cFieldDefs_    DRAWS_data::DRAWS_FieldDef =
{
    sizeof(DRAWS_map),
    sizeof(DRAWS_Fields)/sizeof(DRAWS_Fields[0]),
    "SELECT ID, DDate, Num_1, Num_2, Num_3, Num_4, Num_5, Num_6 FROM DRAWS",
    "DRAWS",
    DRAWS_Fields
};

const cFieldDefs_& FASTCALL DRAWS_rec::GetFieldDefs()                   { return ( DRAWS_FieldDef ); }
//---------------------------------------------------------------------------

