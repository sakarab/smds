#include <uTest.h>
#include <iostream>
#include <malloc.h>

using namespace smds;
using namespace smds::detail;

//--------------------------------------------------------------------
class InitOle
{
private:
	bool	inited;
public:
    InitOle()
		: inited(SUCCEEDED(::CoInitialize(0)))
	{
	}
    ~InitOle()
	{
		if ( inited )
			::CoUninitialize();
	}
};

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
    const cFieldDefs_ptr&   field_defs = ds->GetFieldDefs();

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

int main()
{
    _set_sbh_threshold( 1016 );

    InitOle		guard;

	try
	{
        tblFiles_ptr    files = GetTblFiles();

        Test( files );
        Output( files );
	}
	catch ( std::exception& e )
	{
		::MessageBox( 0, e.what(), 0, MB_OK );
	}
	return 0;
}
