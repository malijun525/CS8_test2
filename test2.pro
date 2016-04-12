TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    bst.cpp \
    heap.cpp \
    research_bst.cpp \
    research_heap.cpp

HEADERS += \
    bst.h \
    heap.h \
    node_heap.h \
    node_bst.h \
    research_bst.h \
    research_heap.h \
    drive.h

