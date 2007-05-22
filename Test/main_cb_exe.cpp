#include <iostream>
#include <uTest.h>

using namespace smds;

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

void Output( tblFiles_ptr ds ) // const ds::cFieldDefs_& field_defs, tblFiles::record_ptr rec )
{
    const spFieldDefs&      field_defs = ds->GetFieldDefs();

    for ( cFieldDefs::const_iterator n = field_defs->begin() ; n != field_defs->end() ; ++n )
        std::cout << n->Name().c_str();
    std::cout << std::endl;

    tblFiles::iterator      rec = ds->GetIterator();

    rec.OldValues().FieldByName( "fSize" )->AsBoolean();
    rec.FieldByName( "fSize" )->AsBoolean( true );
    dsDatasetModify( rec, ds_string( "File" ) );

    rec.First();

    for ( int n = 0 ; n < 10 && ! rec.eof() ; ++n )
    {
        if ( rec->FileID_IsNull() )
            std::cout << "";
        else
            std::cout << rec->GetFileID();

        if ( rec->PathID_IsNull() )
            std::cout << "";
        else
            std::cout << rec->GetPathID();

        if ( rec->LongFileName_IsNull() )
            std::cout << "";
        else
            std::cout << rec->GetLongFileName().c_str();

        if ( rec->fSize_IsNull() )
            std::cout << "";
        else
            std::cout << rec->GetfSize();

        std::cout << " ";

        if ( rec->Description_IsNull() )
            std::cout << "";
        else
            std::cout << rec->GetDescription().c_str();

        if ( rec->zipID_IsNull() )
            std::cout << "";
        else
            std::cout << rec->GetzipID();
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
	try
	{
        tblFiles_ptr    files = GetTblFiles();

        Test( files, ErrorReporter_, 0 );
        Output( files );
	}
	catch ( std::exception& e )
	{
		::MessageBox( 0, e.what(), 0, MB_OK );
	}
	return 0;
}
