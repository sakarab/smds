Small, simple and incomplete tutorial.

This document is unfinished 

In this tutorial we deal with a database that has a sigle table named tblFiles with this fields:

```
CREATE TABLE tblFiles
(
    FileID INTEGER,
    PathID INTEGER,
    LongFileName STRING(255),
    fSize INTEGER,
    fDate TIMESTAMP,
    Description STRING(255),
    zipID INTEGER
)
```

Initialization.
The first thing to do is to select the database engine and connect to the database:

```
spModuleLoader      module_loader = GetOsModuleLoader( SM_DS_TEST_BACKEND );
DbEngine            engine( module_loader );
Database            database = engine.NewConnection( ODBC_Access_DirData_Conn );
```

Working with typed datasets.
Declaring the typed datasets involves declaring a bunch of structures and static data which form the metadata information of the dataset. These, in general, do not concern the users of the library. The final declaration will be something like this (well, for the example database table of this tutorial is exactly like this):

```
typedef smds::cuTable<tblFiles_rec>    tblFiles;
typedef smds::shared_ptr<tblFiles>     tblFiles_ptr;
```

You can have a look in “Test/uTables.h” and “Test/uTables.cpp” to get a feeling how these declarations and definitions look like, but this is not mandatory as they can (will) be generated form a utility program supplied with the library.

Having now the declaration of the table working with it is straight forward:

Create an instance and open the dataset:

```
tblFiles_ptr    ds( new tblFiles() );

ds->Open( database, 0 );
```

Serially locate a record where, for example the PathID field has value 27.

```
tblFiles::iterator      iter = ds->GetIterator();

while ( ! iter.eof() )
{
    if ( ! iter->PathID_IsNull() && iter->GetPathID() == 27 )
        break;
    ++iter;
}
if ( ! iter.eof() )
{
    //  found. do something with it
}
else
{
    // not found. Possibly report an error
}
```

Create an index on "PathID" and "fSize" fields

```
tblFiles::index_ptr     idx = ds->NewIndex( OpenIndexFields( cIndexField( "PathID" ), cIndexField( "fSize" ) ) );
```

Find - binary search - a record where the field PathID has value 27 and the field fSize has value 45000

```
tblFiles::index::iterator   idx_it = idx->Find( OpenValues( 27, 45000 ) );

if ( ! idx_it.eof() )
{
    //  found. do something with it
}
else
{
    // not found. Possibly report an error
}
```

The following code (a snippet from “Test/uTest.cpp”) checks if the index is really indexed. In fact return the number of “unordered” adjusent records.

```
int Check_Order( tblFiles::iterator ptr1 )
{
    int     result = 0;

    // point to the first record
    ptr1.First();

    // return if the dataset is empty
    if ( ptr1.eof() )
        return result;

    // create a new iterator and point to the next (second) record
    tblFiles::iterator      ptr2 = ptr1;
    ptr2.Next();

    // iterate the dataset counting the non-ordered records
    while ( ! ptr2.eof() )
    {
        if ( ptr1->GetPathID() > ptr2->GetPathID() )
            ++result;
        ++ptr1;
        ++ptr2;
    }
    return ( result );
}
```

Adding a record is equally easy

```
// create the record
tblFiles::record    new_record = ds->NewRecord();

// set some field values
new_record->SetFileID( 15 );
new_record->SetPathID( 45 );
new_record->SetfSize( 30000 );
new_record->SetDescription( "record description" );

// and finally add the record
ds->AddRecord( new_record );
```
