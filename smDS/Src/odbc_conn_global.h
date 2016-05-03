#ifndef ODBC_CONN_GLOBAL_H
#define ODBC_CONN_GLOBAL_H

//#include <QtCore/qglobal.h>
#include <boost/predef.h>

#if (BOOST_OS_WINDOWS == BOOST_VERSION_NUMBER_AVAILABLE)
#    define Q_DECL_EXPORT     __declspec(dllexport)
#    define Q_DECL_IMPORT     __declspec(dllimport)
#elif (BOOST_OS_LINUX == BOOST_VERSION_NUMBER_AVAILABLE)
#    define Q_DECL_EXPORT     __attribute__((visibility("default")))
#    define Q_DECL_IMPORT     __attribute__((visibility("default")))
#    define Q_DECL_HIDDEN     __attribute__((visibility("hidden")))
#endif


#if defined(ODBC_CONN_LIBRARY)
#  define ODBC_CONNSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ODBC_CONNSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ODBC_CONN_GLOBAL_H
