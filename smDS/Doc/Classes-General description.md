Incomplete description of some main classes.

#### Table

A table (class smds::Table) represents one table of in-memory relational data. The data is local to the application in which it resides, but can be populated from a database using the appropriate back end data provider.

The schema, or structure of a table is represented by columns (smds::cFieldDefs). You define the schema of a table using smds::cFieldDef objects. The columns in a table can map to columns in a database table or contain calculated values.

In addition to a schema, a table must also have rows to contain and order data. The smds::Table::iterator class represents the actual data contained in a table. You use the smds::Table::iterator and its methods to retrieve, evaluate, and manipulate the data in a table. As you access and change the data within a row, the smds::Table::iterator object maintains both its current and original state (field values).

A table has methods to add, locate (searches serially) and delete records. Adding field definitions is also done via the table class.

#### Index

A table can create ordered “views” of the data it contains, in effect creating indexes (class smds::Index). These indexes have the same schema and contain the same data as the generating table. Changes made to their data are reflected back to the table it created them.

The index class provides methods to find (binary search) a record. Navigation to the ordered data is done with the help of smds::Index::iterator objects.

#### Iterator

smds iterators are not exactly the same thing as STL iterators. They do fulfill the basic requirement to “almost behave like a pointer”, but their public interface is richer then the standard ones and cannot be used in most standard algorithms.

The general convention is that using the class member notation (.) someone has access to the iterator methods. Using the pointer notation (->) someone has access to row columns. Iterators have methods to relocate themselves (iterator.First(), iterator.Last()), switch to the original row data (iterator.OldValues()), get a field's value (iterator.FieldByName()), check for navigational end (iterator.eof()), provide the record count (iterator.RecordCount()) and provide checked methods of the increment and decrement operators (iterator.Prev(),  iterator.Next()).

Iterators are sometimes invalid or become invalid after some action on the object they were created from. In any case an iterator is invalid if iterator.eof() returns true. When we delete a record, an iterator is invalidated if it pointed the last record before the delete, else it is not invalid but the record it is pointing to is undefined. The same can happen for an Index::iterator when for some reason changes the ordering of the index or the value of a field that the ordering depends on.

See also Typed-Untyped.

#### Back end

A set of interfaces (classes with only pure virtual methods) define the way the library interacts with data providers. Data providers are separate code that implement the specifics of database connection and data retrieval.
