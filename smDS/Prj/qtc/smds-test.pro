TARGET = smds-test
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

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

LIBS += -L$$_PRO_FILE_PWD_/$$PATH_SUFFIX -lsmds -ldl

INCLUDEPATH += ../../Test \
               ../../Src \
               /home/sam/src/boost \
               /home/sam/src/libs/ccLib/Src

SOURCES += ../../Test/main_exe.cpp \
           ../../Test/uCompileTest.cpp \
           ../../Test/uConnectionStrings.cpp \
           ../../Test/uProfile.cpp \
           ../../Test/uProfile1.cpp \
           ../../Test/uTables.cpp \
           ../../Test/uTest.cpp \
           ../../Test/uUntypedTest.cpp

HEADERS += ../../Test/uCompileTest.h \
           ../../Test/uConnectionStrings.h \
           ../../Test/uProfile.h \
           ../../Test/uProfile1.h \
           ../../Test/uTables.h \
           ../../Test/uTest.h \
           ../../Test/uUntypedTest.h \
           ../../Test/pre_test.h

