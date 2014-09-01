#include "stdafx.h"
#include "Form1.h"
#include <windows.h>
#include <vector>

using namespace DotNetCppDS;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	System::Threading::Thread::CurrentThread->ApartmentState = System::Threading::ApartmentState::STA;
	Application::Run(new frmMain());
	return 0;
}

void frmMain::do_btnRun_Click( System::Windows::Forms::ListView *lv )
{
    extern void DoCppJob( std::vector<int>& vec );

    std::vector<int>     file_ids;

    DoCppJob( file_ids );

    for ( unsigned int n = 0 ; n < file_ids.size() ; ++n )
    {
        Int32   aa = file_ids[n];

        lv->Items->Add( aa.ToString() );
    }
}
