TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += _WIN32_WINDOWS
DEFINES += _CRT_SECURE_NO_WARNINGS

SOURCES += \
	main.cpp \
    kalgoritm.cpp \
    kstring.cpp \
    kregexp.cpp \
    clogreader.cpp

HEADERS += \
    kalgoritm.h \
    karray.h \
    kstring.h \
    kregexp.h \
    clogreader.h
