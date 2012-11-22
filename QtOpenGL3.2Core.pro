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

mac{
    eval(QT_MAJOR_VERSION = "4") {
        LIBS += -framework Foundation -framework Cocoa
        OBJECTIVE_SOURCES  +=  core_profile_attributes.mm
    }
}

TARGET = QtOpenGL32Core
TEMPLATE = app


SOURCES += main.cpp \
    GLWidget.cpp

HEADERS  += \
    GLWidget.h \
    Core3_2_context.h

OTHER_FILES += \
    simple.frag \
    simple.vert

RESOURCES += \
    core-profile.qrc
