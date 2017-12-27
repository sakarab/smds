# smds
**smds** is an in memory dataset implementation, coded in C++. It's main goals are portability, performance and type safety. It is free software distributed under the GNU General Public License ([GPL](http://www.gnu.org/licenses/gpl.html)).

The library consists of a set of classes and utility functions to assist the manipulation of relational data (either generated and persisted on ordinary files, or retrieved from a database).

Additions and deletions of records and modifications of field values are all done in memory. The end result of the whole process can then be applied back to the database.
