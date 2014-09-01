//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("smDSb5libTest.res");
USEFORM("..\..\Test\FMain.cpp", frmMain);
USEUNIT("..\..\Test\uTest.cpp");
USELIB("smDSb5lib.lib");
USEUNIT("..\..\Test\bcbTest.cpp");
USEUNIT("..\..\Test\uTables.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TfrmMain), &frmMain);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
