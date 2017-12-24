
#### Next version
* Resolving
* SQL parameters
* Serialization

####Version 0.1.3 – Date 2007-08-07
* Profiling test program. 
* ODBC (version 3.x) back-end 
* Changes in supported field types.
* SM_DS_STRING_AS_STRING define eliminated.
* Linux compilation
* Better untyped dataset support.
* Numerous bug fixes

#### Version 0.1.2 – Date 2007-05-24
* Extensive refactoring (class relationship changes, moved some classes in detail namespace etc).
* Class renaming (cTable to Table, cIndex to Index, cSortCompareBase_ptr to spSortCompare etc).
* Added range iterators.
* Notification mechanism (incomplete – missing field value change notifications). Can be disabled un-defining SM_DS_ENABLE_NOTIFY.
* Compilation option "SM_DS_FAST_ITERATORS" added (not really any faster, except when copying iterators).
* Deleting records is now possible.
* Visual Studio 2003 solution and projects added.
* Iterators now have more operator overloads: op++(int), op--(int), op+=(int), op-=(int), op+(int) and op-(int).

#### Version 0.1.1 – Date 2007-04-21
* GCC (mingw) compilation.
* Directory reconstruction.
* Added CodeBlocks project.
* Changed namespace from "ds" to "smds".
