The library and the test program are compiled and tested with C++Builder 6 and Visual Studio 2003 and 2005. It is only compiled with CodeBlocks using MinGW on windows and GCC on Linux.

The “Prj” directory contains all the projects and project groups / solutions / workspaces (PSW) whatever every development environment calls it.

* “bcb6” for Borland C++ 6.
* “cbl” for CodeBlocks on Linux.
* “cbw” for CodeBlocks on Windows.
* “vs2003” for Visual Studio 2003
* “vs2005” for Visual Studio 2005

Every PSW contains three projects. The library, the ODBC back-end and a test program.

Additionally, smds depends on the following libraries

* boost
* Loki

You can eliminate the dependency on Loki if you wish. See below controlling compilation.
On Linux you will probably need to install an ODBC library. unixODBC (currently the Linux compilation is tested with it and it seems that it is more widely available on Linux distributions) or iODBC. Don't forget to install the development library packages.

#### Compiling with C++Builder 6.

In Tool/Environment Options/Environment Variables create a new variable named BOOST_INC that points to the directory the boost library is installed.
Build all the projects.

#### Compiling with Visual Studio 2003
Open the solution. You will need to change the directories that point to boost and loki libraries.
Build all the projects.
You must first make the Loki library or directly use the relevant source files in the projects.

#### Compiling with Visual Studio 2005

Open the project property sheets “Rel.vsprops” and “Dbg.vsprops”. In there, point the BOOST_INC and LOKI_INC macros to the boost and loki installation directories respectively (this can be done also from inside the IDE, opening the “Property Manager” and changing the properties in the Rel and Dbg property sheets). Build all the projects.
You must first make the Loki library or directly use the relevant source files in the projects.

#### Compiling with GCC (CodeBlocks – Windows and Linux)

Create an environment variable, in the CodeBlocks IDE, named BOOST_INC that points to the directory the boost library is installed. Load the CodeBlocks workspace and compile all projects contained in it.
You must have MinGW installed on windows.

#### Controlling compilation.

The compilation of the library can be changed from a couple of defines. All of them are in “Src/dsConfig.h”.

SM_DS_DEFAULT_SHARED_PTR
SM_DS_USE_BOOST_SMART_PTR
SM_DS_USE_LOKI_SHARED_PTR
SM_DS_USE_SMALL_SHARED_PTR

The dependency on the Loki library can be changed or eliminated with these. To do so, comment  SM_DS_DEFAULT_SHARED_PTR and uncomment one of the three below it.

* SM_DS_DEFAULT_SHARED_PTR is the ... default. This will select an appropriate smart pointer depending on the compiler used.
* Defining SM_DS_USE_BOOST_SMART_PTR selects boost::shared_ptr<>
* Defining SM_DS_USE_LOKI_SHARED_PTR selects Loki::SmartPtr<>
* Defining SM_DS_USE_SMALL_SHARED_PTR selects boost::shared_in_ptr<>. The source code for this smart pointer (not distributed as part of the main boost library) is already included in the project.

SM_DS_NULL_VALUE_EXCEPTION

Controls the behaviour of the library when reading a NULL field value via a typed iterator.
When defined (default) it throws eNullFieldValue exception. If not defined it returns the “default” value of the field type (for integral types zero, for strings an empty string etc.).

SM_DS_ENABLE_NOTIFY

When defined (the default) the code responsible for notifications between tables and indexes is included. You can exclude this code all together to get a performance boost by undefining this symbol.

SM_DS_FAST_ITERATORS

Undefined by default. If defined iterators are a bit faster, but also a bit less safe.

BOOST_SP_DISABLE_THREADS

The library by default has no multithreading support, so it also disables the boost::smart_ptr<> multithreading support. In case it is needed, an additional step that must be taken, beyond the IDE setting changes (using multithreaded runtime libraries for example), is to comment BOOST_SP_DISABLE_THREADS.
