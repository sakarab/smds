As one of the goals of this project is to create a fast dataset, profiling is performed regularly to spot inefficiencies in the code.

The performance of the library is dependent on the compiler (its optimization ability) and the STL implementation used. For the following figures, the compiler delivering the best performance was chosen.

* PC configuration:
* CPU : Intel pentium 2.8 GHz
* Memory : 2GB
* OS : WinXP SP2 (hyper-threading enabled)

#### Timing

| Function Name | Time (msecs)|
|---------------|------------:|
| profile::FindRecord_Two | 6,99 |
| profile::LocateRecord_Two | 7,97 |
| profile::CreateIndex_OneInt | 20,28 |
| profile::CreateIndex_OneIntCustom | 21,88 |
| profile::AddRecords_NoIndex | 36,61 |
| profile::CreateIndex_TwoInts | 55,06 |
| profile::ModifyDataset | 103,44 |
| profile::AddRecords_OneIndex | 123,67 |
| profile::FillTable | 435,57 |

The code of the timed functions are in Src/uProfile1.cpp. A brief description of what each function does follows:

* profile::FindRecord_Two : Searches an index, sorted on two fields, for two integer values in the key fields, with a pair of values that matches and another one that does not. This is performed in a loop 1000 times. Overall 2000 search operations.
* profile::LocateRecord_Two : Searches a table serially for two integer values.
* profile::CreateIndex_OneInt : Creates an index sorted on one integer field in descending order.
* profile::CreateIndex_OneIntCustom : Creates an index sorted on one integer field using a custom sort function.
* profile::AddRecords_NoIndex : Adds 20000 records in a table. No index is created for the table at that time.
* profile::CreateIndex_TwoInts : Creates an index sorted on two integer fields. Ascending order on the first field descending on the second.
* profile::ModifyDataset : Changes two integer and one string fields in a table.
* profile::AddRecords_OneIndex : Adds 20000 records in a table. An index sorted on one integer field is already created for the table.
* profile::FillTable : Get the table data from the back-end.

All operations are done on a table / index containing 36292 records.
