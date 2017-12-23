TEMPLATE = app
TARGET = Gl
QT       += core gui
QT += widgets
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QT += opengl
LIBS += -lGLEW
LIBS += -lGL -lGLU -lglut
LIBS += -lglfw3
LIBS += -lX11 -lXrandr -lXinerama -lXxf86vm -lXcursor -lpthread -ldl

SOURCES += \
    main.c \
    init_func.c \
    function.c \
    list.c \
    import_export.c

HEADERS += \
    glodal_types.h \
    function.h \
    list.h \
    import_export.h
