#-------------------------------------------------
#
# Project created by QtCreator 2012-11-12T18:07:16
#
#-------------------------------------------------

QT += core gui
QT += widgets
QT += opengl

win32:INCLUDEPATH *= "C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Include"
win32:LIBS *= "C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Lib\glew32.lib"

mac:LIBS += -framework Foundation -framework Cocoa
mac:OBJECTIVE_SOURCES  +=  core_profile_attributes.mm

TARGET = QtOpenGL32Core
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

OTHER_FILES += \
    simple.frag \
    simple.vert

RESOURCES += \
    core-profile.qrc
