The library provides the ability to work in two modes of table/index instances which can be intermixed. **Typed** and **Untyped**.

#### Untyped mode.

In this mode references to table columns are made by column name and the actual data type is unknown at compile time. Example code snippet:

```
using namespace smds;

void foo()
{
    Table::iterator    ptr1 = ...
    Table::iterator    ptr2 = ...
    int                id_one = ptr1.FieldByName( "PathID" )->AsInteger();
    int                id_two = ptr2.FieldByName( "PathID" )->AsInteger();

    if ( idone == idtwo )
    {
        // do something
    }
    else
    {
        // do something else
    }
}
```

In the code above the iterator performs a named search to find the referenced field (here “PathID”) and is told to convert its value to an int. In this case it works as the PathID field actually is of integer type. In case it wasn't the library would convert the field value to an integer if possible else it would report an error.

On the other hand “typed” means that the raw structure is known and we access it's columns by name. Example code snippet (the functionally equivalent of the above code):

```
using namespace ds;

typedef cuTable<T>    tblFiles;

void foo()
{
    tblFiles::iterator   ptr1 = ...
    tblFiles::iterator   ptr2 = ...
    int                  idone = ptr1->GetPathID();
    int                  idtwo = ptr2->GetPathID();

    if ( ptr1->GetPathID() == ptr2->GetPathID() )
    {
        // do something
    }
    else
    {
        // do something else
    }
}
```
