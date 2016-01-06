TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/main.cpp \
    src/dessin.cpp \
    src/train.cpp \
    src/wagon.cpp \
    src/_api/CArc.cpp \
    src/_api/CData2i.cpp \
    src/_api/CDonneesGraphe.cpp \
    src/_api/CGraphe.cpp \
    src/_api/CPoint3f.cpp \
    src/_api/CPointAnnexe.cpp \
    src/_api/CSegment.cpp \
    src/_api/CSommet.cpp

OTHER_FILES +=

HEADERS += \
    src/config.h \
    src/dessin.h \
    src/tests.h \
    src/train.h \
    src/wagon.h \
    src/_api/CArc.h \
    src/_api/CData2i.h \
    src/_api/CDonneesGraphe.h \
    src/_api/CGraphe.h \
    src/_api/consts.h \
    src/_api/CPoint3f.h \
    src/_api/CPointAnnexe.h \
    src/_api/CSegment.h \
    src/_api/CSommet.h

linux {
    LIBS += -lGL \
        -lGLU \
        -lglut
}

windows {
    LIBS += -lopengl32 -lglu32 -lfreeglut
}
