#-------------------------------------------------
#
# Project created by QtCreator 2016-04-29T11:45:48
#
#-------------------------------------------------

QT       -= gui

TARGET = smds
TEMPLATE = lib
CONFIG += staticlib
DEFINES += NO_FASTCALL
DEFINES += NO_CDFASTCALL
DEFINES += NO_STDCALL

include (user_config.pri)

CONFIG(debug, debug|release) {
    PATH_SUFFIX = ../qtc-Debug
} else {
    PATH_SUFFIX = ../qtc-Release
}

OBJECTS_DIR = $$_PRO_FILE_PWD_/$$PATH_SUFFIX/$$TARGET-obj

INCLUDEPATH += ../../Src \
               ../../include \
               $$ROOT_BOOST \
               $$ROOT_LOKI\include \
               $$ROOT_CCLIB/include

unix {
    DEFINES += LINUX
    INCLUDEPATH += /usr/include
    INCLUDEPATH += /usr/include/iodbc
}
win32 {
    DEFINES -= UNICODE
}

SOURCES += ../../Src/dsBuffer.cpp \
           ../../Src/dsCompare.cpp \
           ../../Src/dsCompareControlers.cpp \
           ../../Src/dsConn.cpp \
           ../../Src/dsData.cpp \
           ../../Src/dsDateTime.cpp \
           ../../Src/dsExceptions.cpp \
           ../../Src/dsFields.cpp \
           ../../Src/dsGUID.cpp \
           ../../Src/dsIndex.cpp \
           ../../Src/dsModuleLoad.cpp \
           ../../Src/dsRecord.cpp \
           ../../Src/dsSerialization.cpp \
           ../../Src/dsStream.cpp \
           ../../Src/dsString.cpp \
           ../../Src/dsUtils.cpp \
           ../../Src/dsVariant.cpp

unix {
    SOURCES += ../../Src/Linux/mlLinuxSo.cpp
}
win32 {
    SOURCES += ../../Src/Win32/mlWinDll.cpp
}

HEADERS += ../../include/dsBuffer.h \
           ../../include/dsCommon.h \
           ../../include/dsCompare.h \
           ../../include/dsCompareControlers.h \
           ../../include/dsConfig.h \
           ../../include/dsConn.h \
           ../../include/dsConn_Intf.h \
           ../../include/dsData.h \
           ../../include/dsDateTime.h \
           ../../include/dsExceptions.h \
           ../../include/dsFields.h \
           ../../include/dsGUID.h \
           ../../include/dsIndex.h \
           ../../include/dsModuleLoad.h \
           ../../include/dsODBCtypes.h \
           ../../include/dsRecord.h \
           ../../include/dsSerialization.h \
           ../../include/dsSmartPtr.h \
           ../../include/dsStream.h \
           ../../include/dsString.h \
           ../../include/dsSysOpen.h \
           ../../include/dsTypedData.h \
           ../../include/dsTypes.h \
           ../../include/dsUtils.h \
           ../../include/Linux/mlLinuxSo.h \
           ../../include/dsVariant.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
