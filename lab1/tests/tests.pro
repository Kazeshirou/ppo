include(../common.pri)
include(../app.pri)

QT += core testlib location gui widgets

TARGET = tests
TEMPLATE = app

SOURCES += \
    main.cpp \
    testgpxparser.cpp \
    ../src/gpxparser.cpp \
    testcoder.cpp \
    ../src/coder.cpp \
    ../src/georoute.cpp

HEADERS += \
    testgpxparser.h \
    ../src/gpxparser.h \
    testcoder.h \
    ../src/coder.h \
    ../src/georoute.h



