#-------------------------------------------------
#
# Project created by QtCreator 2010-07-28T21:59:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = legendary
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    vbo_object.cpp \
    texture.cpp \
    file.cpp \
    rtt.cpp \
    obj.cpp \
    msg.cpp \
    material.cpp \
    glrender.cpp \
    engine.cpp \
    cube.cpp \
#    c3dsparser.cpp \
    base_texture.cpp

OTHER_FILES += \
    README \
    debug.log \
    chunks.def \

HEADERS += \
    vbo_object.h \
    types.h \
    texture.h \
    rtt.h \
    file.h \
    obj.h \
    msg.h \
    material.h \
    glrender.h \
    engine.h \
    cube.h \
#    c3dsparser.h \
    base_texture.h

win32 {
    HEADERS += win.h
    SOURCES += win.cpp
    LIBS    += -lopengl32 \
            -lglew32s
}

unix {
    HEADERS += linux.h
    SOURCES += linux.cpp
    LIBS    += -lX11 \
               -lGLEW
}
