//---------------------------------------------------------------------------
#ifndef uSubH
#define uSubH
//---------------------------------------------------------------------------
#include <DB.hpp>
#include <DBTables.hpp>
#include <vector>
//---------------------------------------------------------------------------
template <class T> class OpenGuard
{
private:
    T   *mObject;
public:
    __fastcall OpenGuard( T *obj ) : mObject(obj)       { mObject->Open(); }
    __fastcall ~OpenGuard()                             { mObject->Close(); }
};

template <class T> class DisableControlsGuard
{
private:
    T   *mObject;
public:
    __fastcall DisableControlsGuard( T *obj ) : mObject(obj)        { mObject->DisableControls(); }
    __fastcall ~DisableControlsGuard()                              { mObject->EnableControls(); }
};
//---------------------------------------------------------------------------
namespace sub
{

void __fastcall Run( TFields *fields, const AnsiString& prefix, const AnsiString& table_name,
                     std::vector<AnsiString>& h );

void __fastcall RunQuery( TQuery *query, const AnsiString& prefix, const AnsiString& table_name,
                          const AnsiString& query_str, std::vector<AnsiString>& h );

};
//---------------------------------------------------------------------------
#endif
