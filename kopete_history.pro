QT += xml \
    xmlpatterns \
    dbus
TARGET = kopete_history
TEMPLATE = app
SOURCES += src/*.cpp tests/src/*.cpp
HEADERS += src/*.h
FORMS += forms/*.ui

