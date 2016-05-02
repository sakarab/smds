#ifndef ODBC_CONN_GLOBAL_H
#define ODBC_CONN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ODBC_CONN_LIBRARY)
#  define ODBC_CONNSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ODBC_CONNSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ODBC_CONN_GLOBAL_H
