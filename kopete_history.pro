# -------------------------------------------------
# Project created by QtCreator 2011-12-15T11:31:21
# -------------------------------------------------
QT += xml \
    xmlpatterns \
    testlib \
    dbus
TARGET = kopete_history
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    merger.cpp
HEADERS += mainwindow.h \
    merger.h \
    mergerexception.h
FORMS += mainwindow.ui
