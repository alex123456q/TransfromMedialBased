HEADERS += \
    SkeletonLib/BitRaster.h \
    SkeletonLib/BSTrans.h \
    SkeletonLib/ContourTracer.h \
    SkeletonLib/Geometry.h \
    SkeletonLib/LinkedList.h \
    SkeletonLib/SpanTree.h \
    SkeletonLib/StructureSkel.h \
    SkeletonLib/StructureTD.h \
    SkeletonLib/TreeAVL.h \
    SkeletonLib/TriDel.h \
    skeletondemogui.h

SOURCES += \
    SkeletonLib/ContourTracer.cpp \
    SkeletonLib/Geometry.cpp \
    SkeletonLib/SpanTree.cpp \
    SkeletonLib/StructureSkel.cpp \
    SkeletonLib/StructureTD.cpp \
    SkeletonLib/TreeAVL.cpp \
    SkeletonLib/TriDel.cpp \
    skeletondemogui.cpp \
    SkeletonLib/BSTrans.cpp \
    main2.cpp

RESOURCES += \
    skeletondemogui.qrc

FORMS += \
    skeletondemogui.ui

CONFIG += qt
#CONFIG += c++11

QT += core gui widgets
