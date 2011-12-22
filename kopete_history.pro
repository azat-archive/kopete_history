# -------------------------------------------------
# Project created by QtCreator 2011-12-15T11:31:21
# -------------------------------------------------
QT += xml \
    xmlpatterns \
    dbus
TARGET = kopete_history
TEMPLATE = app
SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/merger.cpp
HEADERS += src/mainwindow.h \
    src/merger.h \
    src/mergerexception.h
FORMS += forms/mainwindow.ui
