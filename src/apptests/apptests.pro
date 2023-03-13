QT += testlib
QT += gui widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

DEPENDPATH += $$PWD/../app
INCLUDEPATH += $$PWD/../app

include(../app/lib/json/json.pri)
include(../app/utils.pri)


SOURCES += \
    tst_utils.cpp

