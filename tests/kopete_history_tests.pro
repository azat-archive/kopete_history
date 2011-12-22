QT += xml \
    xmlpatterns \
    dbus \
    testlib
CONFIG += qtestlib

TARGET = kopete_history_tests
SOURCES += src/testmerger.cpp ../src/merger.cpp
HEADERS += ../src/merger.h

target.path = ./
sources.files = $$SOURCES *.pro
sources.path = ./
INSTALLS += target sources
