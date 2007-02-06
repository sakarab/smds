What is memDS?
--------------

memDS is an in memory dataset/recordset written in standard C++. Suppots the 
disconected model of database table manipulation. Up to now I am aware of two 
main branches of imlementations. First is the Delphi's TDataset derived line of 
imlementations and second M$ .NET DataSet.

Rationale
---------

Both mentioned above imlementations have a number of disadvantages (and of 
course advantages ... but let's concentrate on the disadvantages so it is 
easier for me to reason about this library :-) ).

The TDataset derived imlementation's problems
1. Performance. They are anacceptablly slow. 
2. Non portable. They are based on TDataset which is written in Pascal.

The M$ .NET DataSet problems
1. To much information exposure. The Dataset rows can be accesed by integer 
index for example.
2. Non portable. You must use .NET runtime.


Both use proprietary libraries

I need a memory dataset for my C++ projects. The ones I know (Delphi's 
TClientDataset, freeware or commericial third party implimentaions based on 
Delphi's TDataset

Main goals
----------
1. Performance.
2. Type safity
3. Portability

Current State
-------------

At this stage the labrary is in a "prouf on concept" state. The data retrieval 
interface is not good and the imlementation is based on proprietary code (BDE, 
ADO), there is no resolver implimantation, the serialization was coded in five 
minitues (take into account that I am not a fast typist :-) ).

Just write something to change it

