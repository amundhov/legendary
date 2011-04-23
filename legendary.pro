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
    material.cpp \
    msg.cpp \
    rtt.cpp \
    vbo_object.cpp \
    c3dsparser.cpp \
    c3ds_object.cpp \
    rawtexture.cpp \
    texture.cpp

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
    material.h \
    msg.h \
    rtt.h \
    types.h \
    vbo_object.h \
    c3dsparser.h \
    c3ds_object.h \
    rawtexture.h \
    texture.h

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
