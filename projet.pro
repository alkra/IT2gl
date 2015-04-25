TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/main.cpp \
    _api/src/CArc.cpp \
    _api/src/CData2i.cpp \
    _api/src/CDonneesGraphe.cpp \
    _api/src/CGraphe.cpp \
    _api/src/CPoint3f.cpp \
    _api/src/CPointAnnexe.cpp \
    _api/src/CSegment.cpp \
    _api/src/CSommet.cpp \
    src/config.cpp \
    src/dessin.cpp

OTHER_FILES +=

HEADERS += \
    _api/src/CArc.h \
    _api/src/CData2i.h \
    _api/src/CDonneesGraphe.h \
    _api/src/CGraphe.h \
    _api/src/consts.h \
    _api/src/CPoint3f.h \
    _api/src/CPointAnnexe.h \
    _api/src/CSegment.h \
    _api/src/CSommet.h \
    src/alban.h \
    src/config.h \
    src/dessin.h \
    src/tests.h

LIBS += -lGL \
    -lGLU \
    -lglut
