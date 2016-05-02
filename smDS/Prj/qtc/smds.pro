#-------------------------------------------------
#
# Project created by QtCreator 2016-04-29T11:45:48
#
#-------------------------------------------------

QT       -= gui

TARGET = smds
TEMPLATE = lib
CONFIG += staticlib
DEFINES += LINUX
DEFINES += NO_FASTCALL
DEFINES += NO_CDFASTCALL
DEFINES += NO_STDCALL

CONFIG(debug, debug|release) {
    PATH_SUFFIX = Debug
} else {
    PATH_SUFFIX = Release
}

OBJECTS_DIR = $$_PRO_FILE_PWD_/$$PATH_SUFFIX/$$TARGET-obj

INCLUDEPATH += ../../Src \
               /home/sam/src/boost \
               /home/sam/src/libs/ccLib/Src \
               /home/usr/include

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
           ../../Src/Linux/mlLinuxSo.cpp \
           ../../Src/dsVariant.cpp

HEADERS += ../../Src/dsBuffer.h \
           ../../Src/dsCommon.h \
           ../../Src/dsCompare.h \
           ../../Src/dsCompareControlers.h \
           ../../Src/dsConfig.h \
           ../../Src/dsConn.h \
           ../../Src/dsConn_Intf.h \
           ../../Src/dsData.h \
           ../../Src/dsDateTime.h \
           ../../Src/dsExceptions.h \
           ../../Src/dsFields.h \
           ../../Src/dsGUID.h \
           ../../Src/dsIndex.h \
           ../../Src/dsModuleLoad.h \
           ../../Src/dsODBCtypes.h \
           ../../Src/dsRecord.h \
           ../../Src/dsSerialization.h \
           ../../Src/dsSmartPtr.h \
           ../../Src/dsStream.h \
           ../../Src/dsString.h \
           ../../Src/dsSysOpen.h \
           ../../Src/dsTypedData.h \
           ../../Src/dsTypes.h \
           ../../Src/dsUtils.h \
           ../../Src/Linux/mlLinuxSo.h \
           ../../Src/dsVariant.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
