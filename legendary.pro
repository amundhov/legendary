QT       -= core
QT       -= gui

TARGET = legendary
CONFIG += console
CONFIG += debug
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    cube.cpp \
    engine.cpp \
    file.cpp \
    glrender.cpp \
    msg.cpp \
    rtt.cpp \
    c3dsparser.cpp \
    rawtexture.cpp \
    vboobject.cpp \
    c3dsobject.cpp \
    material.cpp

OTHER_FILES += \
    README \
    debug.log \
    chunks.def \
    cube.3ds \
    shaders/frag-bloom.glsl

HEADERS += \
    cube.h \
    engine.h \
    file.h \
    glrender.h \
    msg.h \
    rtt.h \
    types.h \
    c3dsparser.h \
    rawtexture.h \
    vboobject.h \
    c3dsobject.h \
    material.h

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
