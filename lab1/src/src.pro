include(../common.pri)
include(../app.pri)

QT += core gui widgets positioning

TARGET = routes
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    gpxparser.cpp \
    coder.cpp \
    commanddirector.cpp \
    command.cpp \
    presenter.cpp \
    model.cpp \
    treewidget.cpp

HEADERS += \
    mainwindow.h \
    gpxparser.h \
    coder.h \
    georoute.h \
    commanddirector.h \
    command.h \
    presenter.h \
    model.h \
    treewidget.h

FORMS += \
    mainwindow.ui

