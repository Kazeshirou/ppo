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
    treemodelitem.cpp \
    treemodel.cpp \
    treeview.cpp \
    commanddirector.cpp \
    command.cpp \
    presenter.cpp \
    model.cpp

HEADERS += \
    mainwindow.h \
    gpxparser.h \
    coder.h \
    treemodelitem.h \
    treemodel.h \
    georoute.h \
    treeview.h \
    commanddirector.h \
    command.h \
    presenter.h \
    model.h

FORMS += \
    mainwindow.ui

