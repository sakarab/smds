#-------------------------------------------------
#
# Project created by QtCreator 2016-05-02T21:57:38
#
#-------------------------------------------------

QT       -= gui

TARGET = ODBC_Conn
TEMPLATE = lib
CONFIG += dll

DEFINES += ODBC_CONN_LIBRARY
DEFINES += LINUX
DEFINES += NO_FASTCALL
DEFINES += NO_CDFASTCALL
DEFINES += NO_STDCALL

#QMAKE_CXXFLAGS += -fvisibility=hidden -fvisibility-inlines-hidden
#QMAKE_LFLAGS_SHLIB += -fvisibility=hidden -fvisibility-inlines-hidden

CONFIG(debug, debug|release) {
    PATH_SUFFIX = Debug
} else {
    PATH_SUFFIX = Release
}

OBJECTS_DIR = $$_PRO_FILE_PWD_/$$PATH_SUFFIX/$$TARGET-obj

LIBS += -liodbc

INCLUDEPATH += ../../Src \
               /home/sam/src/boost \
               /home/sam/src/libs/ccLib/Src \
               /home/usr/include

SOURCES += ../../Src/ODBC_Conn.cpp \
           ../../Src/ODBC_Sub.cpp

HEADERS += ../../Src/ODBC_Sub.h \
           ../../Src/odbc_conn_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
