#### Version 0.1.3
This release is focused on the back-end. The new and from now on the only back-end provided uses ODBC. For now it supports 3.x ODBC drivers.

The data types supported is almost complete (with the exception of Unicode strings and blobs).

Some changes were made to better support Linux compilation. It is now actively compiled on SUSE Linux 10.1 with the CodeBlocks IDE and GCC 4.1.0.

Additionally an sql script is provided in the form of a series of insert statements for testing purposes with other databases.

#### Version 0.1.2
This release contains a lot of changes (notifications, range iterators, ability to delete records). See the change log for more info.

Unfortunately I hadn't had the time to make a decent back-end. The current ones are extremely slow and are of no use on Linux. Scheduled for next release together with resolving / saving changes.

#### Version 0.1.1
This is a minor release to support gcc and Linux (see the change log). 

The state will remain pre-alpha until the back end interfaces are stabilized, a switch is made to the SOCI back ends (so that gcc-Linux support is complete), implementation of “delete record” and “apply to database” are completed.

#### Version 0.1
This is the first release of the "fast memory dataset" project. The project is in "the proof of concept" state and much remains to be done (changes can not be applied on the database, no xml serialization, poorly organized code etc.).

The sole purpose of the this release is to ease people that are interested for such a project in any way, to review the code and possibly comment on it.

Visit regularly the project web page as new documentation (architecture, involved classes and their public interface, a simple tutorial) and articles are on their way.

Comments, propositions and (constructive) criticism are very much needed.
