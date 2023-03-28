QT       += core gui multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Define git info
GIT_HASH="\\\"$$system(git -C \""$$_PRO_FILE_PWD_"\" rev-parse --short HEAD)\\\""
GIT_BRANCH="\\\"$$system(git -C \""$$_PRO_FILE_PWD_"\" rev-parse --abbrev-ref HEAD)\\\""
BUILD_TIMESTAMP="\\\"$$system(date -u +\""%Y-%m-%dT%H:%M:%SUTC\"")\\\""
DEFINES += GIT_HASH=$$GIT_HASH GIT_BRANCH=$$GIT_BRANCH BUILD_TIMESTAMP=$$BUILD_TIMESTAMP


# Set program version
VERSION = 1.0.0
DEFINES += VERSIONSTR=\\\"$${VERSION}\\\"

# Set Application name
APPLICATION_FULLNAME= MagicCut
DEFINES += APPLICATION_FULLNAME=\\\"$${APPLICATION_FULLNAME}\\\"

# Set Target name
TARGET = $${APPLICATION_FULLNAME}

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

include(lib/json/json.pri)
include(lib/ffprobe/ffprobe.pri)
include(utils.pri)
include(widgets/widgets.pri)


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mediainfoviewer.cpp \
    medialibrary.cpp \
    medialoader.cpp \
    mediaplayer.cpp \
    timeline.cpp

HEADERS += \
    externals/Cachier/cachier.h \
    filterablesortfilterproxymodel.h \
    mainwindow.h \
    mediainfoviewer.h \
    medialibrary.h \
    medialoader.h \
    mediaplayer.h \
    timeline.h

FORMS += \
    mainwindow.ui \
    mediainfoviewer.ui \
    medialibrary.ui \
    timeline.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
