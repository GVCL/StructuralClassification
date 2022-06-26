TEMPLATE = app
TARGET = saliencyvis
QT += core \
    gui \
    opengl \
    network \
    xml

OBJECTS_DIR=obj #Intermediate object files directory
MOC_DIR=obj #Intermediate moc files directory


HEADERS += \
    src/vis.h \
    src/TreeWidget.h \
    src/Strucparam.h \
    src/ParameterWidget.h \
    src/mainwindow.h \
    src/glwidget.h \
    src/FastTrackball.h \
    src/doubleSlider.h \
    src/common_datatype.h \
    src/Color.h

SOURCES += \
    src/XmdvTool.cpp \
    src/vis.cpp \
    src/TreeWidget.cpp \
    src/Strucparam.cpp \
    src/ParameterWidget.cpp \
    src/mainwindow.cpp \
    src/glwidget.cpp \
    src/FastTrackball.cpp \
    src/doubleSlider.cpp \
    src/Color.cpp


INCLUDEPATH += src

QMAKE_CXXFLAGS += -g -Wno-deprecated -fPIC


INCLUDEPATH += /usr/include  -I/usr/include/teem

QMAKE_LIBDIR += /usr/local/lib /usr/lib /usr/local/lib/Teem-1.12.0
LIBS += -lGL -lGLU -lteem






