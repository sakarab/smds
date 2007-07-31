#include <iostream>
#include "uTest.h"
#include "uProfile.h"
#include "uUntypedTest.h"
#include "uConnectionStrings.h"

#if defined (_MSC_VER)
    #include <malloc.h>
#endif

#include <fstream>

using namespace smds;

//--------------------------------------------------------------------
void __fastcall dsDatasetModify( tblFiles::iterator ds, const ds_string& descr )
{
    //ds_string   descr( "File" );

    ds.First();
    for ( int n = 0 ; ! ds.eof() ; ++ds, ++n )
    {
        ds->SetFileID( n );
        ds->SetPathID( n );
        ds->SetDescription( descr );
    }
}

bool HasAlienChars( const ds_string& str )
{
    for ( int n = 0, eend = str.size() ; n < eend ; ++n )
        if ( str[n] < 0 )
            return true;
    return false;
}

void CreateInsertSqls( tblFiles_ptr ds )
{
    std::ofstream           os( "insert.sql" );
    tblFiles::iterator      rec = ds->GetIterator();

    for ( int n = 0, eend = ds->RecordCount() ; n < eend ; ++n, ++rec )
    {
        if ( ! rec->LongFileName_IsNull() && HasAlienChars( rec->GetLongFileName() ) )
            std::cout << "LongFileName : " << rec->GetFileID() << '\n';
        if ( ! rec->Description_IsNull() && HasAlienChars( rec->GetDescription() ) )
            std::cout << "Description : " << rec->GetFileID() << '\n';

        os << "insert into tblFiles (FileID,PathID,LongFileName,fSize,fDate,Description,zipID) values (";

        if ( rec->FileID_IsNull() )
            os << "NULL";
        else
            os << rec->GetFileID();
        os << ", ";

        if ( rec->PathID_IsNull() )
            os << "NULL";
        else
            os << rec->GetPathID();
        os << ", ";

        if ( rec->LongFileName_IsNull() )
            os << "NULL";
        else
            os << "\"" << rec->GetLongFileName().c_str() << "\"";
        os << ", ";

        if ( rec->fSize_IsNull() )
            os << "NULL";
        else
            os << rec->GetfSize();
        os << ", ";

        if ( rec->fDate_IsNull() )
            os << "NULL";
        else
        {
            std::tm     tm = rec->GetfDate().AsTM();

            char    buff[100];

            std::sprintf( buff, "'%d-%d-%d'", tm.tm_year, tm.tm_mon, tm.tm_mday );
            os << buff;
        }
        os << ", ";

        if ( rec->Description_IsNull() )
            os << "NULL";
        else
            os << "\"" << rec->GetDescription().c_str() << "\"";
        os << ", ";

        if ( rec->zipID_IsNull() )
            os << "NULL";
        else
            os << rec->GetzipID();
        os << ");\n";
    }
}

void Output( tblFiles_ptr ds ) // const ds::cFieldDefs_& field_defs, tblFiles::record_ptr rec )
{
    const spFieldDefs&      field_defs = ds->GetFieldDefs();

    for ( cFieldDefs::const_iterator n = field_defs->begin() ; n != field_defs->end() ; ++n )
        std::cout << n->Name().c_str() << '\n';
    std::cout << std::endl;

    tblFiles::iterator      rec = ds->GetIterator();

    rec.OldValues().FieldByName( "fSize" )->AsBoolean();
    rec.FieldByName( "fSize" )->AsBoolean( true );
    dsDatasetModify( rec, ds_string( "File" ) );

    rec.First();

    for ( int n = 0 ; n < 10 && ! rec.eof() ; ++n, ++rec )
    {
        if ( rec->FileID_IsNull() )
            std::cout << "";
        else
            std::cout << rec->GetFileID();
        std::cout << ", ";

        if ( rec->PathID_IsNull() )
            std::cout << "";
        else
            std::cout << rec->GetPathID();
        std::cout << ", ";

        if ( rec->LongFileName_IsNull() )
            std::cout << "";
        else
            std::cout << rec->GetLongFileName().c_str();
        std::cout << ", ";

        if ( rec->fSize_IsNull() )
            std::cout << "";
        else
            std::cout << rec->GetfSize();
        std::cout << ", ";

        std::cout << ", ";

        if ( rec->Description_IsNull() )
            std::cout << "";
        else
            std::cout << rec->GetDescription().c_str();
        std::cout << ", ";

        if ( rec->zipID_IsNull() )
            std::cout << "";
        else
            std::cout << rec->GetzipID();
        std::cout << '\n';
    }
}

namespace
{

void FASTCALL ErrorReporter_( void *user_data, const char *error )
{
}

};

int main()
{
#if defined (_MSC_VER)
    _set_sbh_threshold( 1016 );     // run normal speed when debuger is present
#endif

	try
	{
        shared_ptr<WinDllML>    module_loader( new WinDllML( SM_DS_TEST_BACKEND ) );
        DbEngine                engine( module_loader );
        Database                database = engine.NewConnection( ODBC_Access_DirData_Conn );

        TestAlign();

        tblFiles_ptr    files = GetTblFiles( database );

        CreateInsertSqls( files );
        Test( files, ErrorReporter_, 0 );
        Output( files );
        RunProfile( database );
        UntypedTest( database );

        std::cout << "press enter" << std::endl;

        char    ch;

        std::cin.get( ch );
	}
	catch ( std::exception& e )
	{
		::MessageBox( 0, e.what(), 0, MB_OK );
	}
    return 0;
}

