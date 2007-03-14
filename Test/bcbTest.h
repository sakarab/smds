//---------------------------------------------------------------------------
#ifndef bcbTestH
#define bcbTestH
//---------------------------------------------------------------------------
#include <ComCtrls.hpp>
#include <ADODB.hpp>
#include <DBClient.hpp>
#include <Provider.hpp>
#include "uTables.h"
//---------------------------------------------------------------------------
void __fastcall FillList( TListView *lv, const ds::cFieldDefs_& field_defs, tblFiles_ptr dataset );
void __fastcall DoFetch( TADOQuery *ADOQuery, TDataSetProvider* Provider, TClientDataSet *ClientDataSet );
//---------------------------------------------------------------------------
#endif
