//---------------------------------------------------------------------------
#pragma hdrstop

#include "smdsDataset.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TsmdsDataset::TsmdsDataset( TComponent *aOwner )
    : TDataSet(aOwner), FTable(new smds::Table())
{
}
//---------------------------------------------------------------------------
__fastcall TsmdsDataset::~TsmdsDataset()
{
}
//---------------------------------------------------------------------------
TGetResult __fastcall TsmdsDataset::GetRecord(char * Buffer, TGetMode GetMode, bool DoCheck)
{
}
//---------------------------------------------------------------------------
void __fastcall TsmdsDataset::InternalClose()
{
}
//---------------------------------------------------------------------------
void __fastcall TsmdsDataset::InternalHandleException()
{
}
//---------------------------------------------------------------------------
void __fastcall TsmdsDataset::InternalInitFieldDefs()
{
}
//---------------------------------------------------------------------------
void __fastcall TsmdsDataset::InternalOpen()
{
}
//---------------------------------------------------------------------------
bool __fastcall TsmdsDataset::IsCursorOpen()
{
}
//---------------------------------------------------------------------------

