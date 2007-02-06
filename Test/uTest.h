//---------------------------------------------------------------------------
#ifndef uTestH
#define uTestH
//---------------------------------------------------------------------------
#include <dsData.h>
#include "uTables.h"
//#include "dsSmartPtr.h"
//---------------------------------------------------------------------------
tblFiles_ptr GetTblFiles();
void Test( tblFiles_ptr ds );
void Test( tblLocation_ptr ds );
void Test( const ds::cTable& ds );
int DoDsDataTest();
//---------------------------------------------------------------------------
#endif
