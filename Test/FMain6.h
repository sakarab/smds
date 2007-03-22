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
#ifndef FMain6H
#define FMain6H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBClient.hpp>
#include <DBCtrls.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Provider.hpp>
//---------------------------------------------------------------------------
#include "uTables.h"
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TButton *Button1;
    TButton *Button2;
    TDBNavigator *DBNavigator1;
    TDBEdit *DBEdit1;
    TDBEdit *DBEdit2;
    TListView *lvList;
    TADOConnection *ADOConnection;
    TADOQuery *ADOQuery;
    TClientDataSet *ClientDataSet;
    TDataSetProvider *DataSetProvider;
    TDatabase *Database;
    TQuery *Query;
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall lvListData(TObject *Sender, TListItem *Item);
private:	// User declarations
    tblFiles_ptr    mFiles;
public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
