#include <uTest.h>
#include <iostream>
#include <malloc.h>
/*
class A
{
    friend class B;
    int a;
};

class B
{
    friend class C;
};

class D : public B
{
    void f( A *p )
    {
        p->a++;
    }
};
//--------------------------------------------------------------------
class BaseClass
{
public:
    void    BaseFunc( void ) {}
};

class DerivedClass: private BaseClass
{
    //using BaseClass::BaseFunc;	//* Make BaseFunc private!
    friend class FriendClass;	//* But allow this class access
};

class FinalClass: public DerivedClass { };

class FriendClass
{
    FinalClass *mpFinal;
public:
    FriendClass( FinalClass *ApDerived )    { mpFinal = ApDerived; }
	//* Compiler Error: 'BaseClass::BaseFunc()' is not accessible
	//* in function FriendClass::CallBaseFunc()
	void CallBaseFunc( void ) { mpFinal->BaseFunc(); }
};

void testFunc( void )
{
	FinalClass final;
	FriendClass friendOf( &final );

	friendOf.CallBaseFunc();
}
*/
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
    const ds::cFieldDefs_ptr&   field_defs = ds->GetFieldDefs();

    for ( ds::cFieldDefs::const_iterator n = field_defs->begin() ; n != field_defs->end() ; ++n )
        std::cout << n->Name().c_str();
    std::cout << std::endl;

    tblFiles::iterator      rec = ds->GetIterator();

    rec.OldValues().FieldByName( "fSize" )->AsBoolean();
    rec.FieldByName( "fSize" )->AsBoolean( true );
    dsDatasetModify( rec, ds_string( "File" ) );

    rec.First();

    for ( int n = 0 ; n < 10 && ! rec.eof() ; ++n )
    {
        std::cout << rec->GetFileID(); // << " ";
        std::cout << rec->GetPathID(); // << " ";
        std::cout << rec->GetLongFileName().c_str(); // << " ";
        std::cout << rec->GetfSize(); // << " ";
        std::cout << " ";
        std::cout << rec->GetDescription().c_str(); // << " ";
        std::cout << rec->GetzipID(); // << " ";
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
