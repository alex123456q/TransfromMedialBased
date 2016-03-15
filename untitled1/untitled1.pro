#-------------------------------------------------
#
# Project created by QtCreator 2015-10-20T14:26:28
#
#-------------------------------------------------

QT       += core gui\
            qt3support

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled1
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    SkeletonDemoGUI/SkeletonLib/BSTrans.cpp \
    SkeletonDemoGUI/SkeletonLib/ContourTracer.cpp \
    SkeletonDemoGUI/SkeletonLib/Geometry.cpp \
    SkeletonDemoGUI/SkeletonLib/SpanTree.cpp \
    SkeletonDemoGUI/SkeletonLib/StructureSkel.cpp \
    SkeletonDemoGUI/SkeletonLib/StructureTD.cpp \
    SkeletonDemoGUI/SkeletonLib/TreeAVL.cpp \
    SkeletonDemoGUI/SkeletonLib/TriDel.cpp \
    PaintFig.cpp \
    SkeletProcess.cpp \
    MoveSkeletW.cpp

HEADERS  += mainwindow.h \
    TransformMedialBased.h \
    Running.h \
    SkeletonDemoGUI/SkeletonLib/BitRaster.h \
    SkeletonDemoGUI/SkeletonLib/BSTrans.h \
    SkeletonDemoGUI/SkeletonLib/ContourTracer.h \
    SkeletonDemoGUI/SkeletonLib/Geometry.h \
    SkeletonDemoGUI/SkeletonLib/LinkedList.h \
    SkeletonDemoGUI/SkeletonLib/SpanTree.h \
    SkeletonDemoGUI/SkeletonLib/StructureSkel.h \
    SkeletonDemoGUI/SkeletonLib/StructureTD.h \
    SkeletonDemoGUI/SkeletonLib/TreeAVL.h \
    SkeletonDemoGUI/SkeletonLib/TriDel.h \
    PaintFig.h \
    MyWidget.h \
    SkeletProcess.h \
    MoveSkeletW.h

FORMS    += mainwindow.ui

IMAGES = images/down.png \
         images/left.png
