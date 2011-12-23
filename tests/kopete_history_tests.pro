QT += xml \
    xmlpatterns \
    dbus \
    testlib
CONFIG += qtestlib

TARGET = kopete_history_tests
SOURCES += src/testmerger.cpp ../src/merger.cpp
HEADERS += ../src/merger.h
DEFINES += QT_TEST_PROJECT=1

target.path = ./
sources.files = $$SOURCES *.pro
sources.path = ./
INSTALLS += target sources
