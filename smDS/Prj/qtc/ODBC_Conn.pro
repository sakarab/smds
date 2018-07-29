#-------------------------------------------------
#
# Project created by QtCreator 2016-05-02T21:57:38
#
#-------------------------------------------------

QT       -= core gui

TARGET = ODBC_Conn
TEMPLATE = lib
CONFIG += dll

DEFINES += ODBC_CONN_LIBRARY
DEFINES += NO_FASTCALL
DEFINES += NO_CDFASTCALL
DEFINES += NO_STDCALL

include (user_config.pri)

#QMAKE_CXXFLAGS += -fvisibility=hidden -fvisibility-inlines-hidden
#QMAKE_LFLAGS_SHLIB += -fvisibility=hidden -fvisibility-inlines-hidden

CONFIG(debug, debug|release) {
    PATH_SUFFIX = ../qtc-Debug
} else {
    PATH_SUFFIX = ../qtc-Release
}

OBJECTS_DIR = $$_PRO_FILE_PWD_/$$PATH_SUFFIX/$$TARGET-obj

INCLUDEPATH += ../../Src \
               ../../include \
               $$ROOT_BOOST \
               $$ROOT_CCLIB/include

unix {
    DEFINES += LINUX
    INCLUDEPATH += /usr/include
    INCLUDEPATH += /usr/include/iodbc
    LIBS += -liodbc
}
win32 {
    DEFINES -= UNICODE
    LIBS += -lodbc32
}

SOURCES += ../../Src/ODBC_Conn.cpp \
           ../../Src/ODBC_Sub.cpp

HEADERS += ../../Src/ODBC_Sub.h \
           ../../Src/odbc_conn_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
