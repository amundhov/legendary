#-------------------------------------------------
#
# Project created by QtCreator 2010-07-28T21:59:19
#
#-------------------------------------------------

QT       -= core

QT       -= gui

TARGET = legendary
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += debug

TEMPLATE = app


SOURCES += \
    base_texture.cpp \
    cube.cpp \
    engine.cpp \
    file.cpp \
    glrender.cpp \
    material.cpp \
    msg.cpp \
    rtt.cpp \
    texture.cpp \
    vbo_object.cpp \
    c3dsparser.cpp \
    c3ds_object.cpp

OTHER_FILES += \
    README \
    debug.log \
    chunks.def \
    cube.3ds

HEADERS += \
    base_texture.h \
    cube.h \
    engine.h \
    file.h \
    glrender.h \
    material.h \
    msg.h \
    rtt.h \
    texture.h \
    types.h \
    vbo_object.h \
    c3dsparser.h \
    c3ds_object.h

win32 {
    HEADERS += win.h
    SOURCES += win.cpp
    LIBS    += -lopengl32 \
            -lglew32s
}

unix {
    HEADERS += linux.h \
               sound.h \
               fht.h
    SOURCES += linux.cpp \
               sound.cpp \
               fht.cpp
    LIBS    += -lX11 \
               -lGLEW \
               -lvorbisfile \
               -lasound
}
