TEMPLATE = app
TARGET = tensorvis
QT += core \
    gui \
    opengl \
    network \
    xml

OBJECTS_DIR=obj #Intermediate object files directory
MOC_DIR=obj #Intermediate moc files directory

HEADERS += \
    src/Classification/Processing.h \
    src/Classification/pcl_common.h \
    src/Classification/FileRead.h \
    src/Classification/eig3.h \
    src/Classification/Display.h \
    src/Classification/data_type.h \
    src/Classification/cutil_math.h \
    src/Classification/Color.h \
    src/main/TreeWidget.h \
    src/main/Strucparam.h \
    src/main/ParameterWidget.h \
    src/main/mainwindow.h \
    src/main/glwidget.h \
    src/main/FastTrackball.h \
    src/main/doubleSlider.h \
    src/Classification/tensor3dVoting.h \
    src/Classification/OctreeSerial.h \
    src/Classification/octree_pointcloud.h \
    src/Classification/octree_pointcloud.h

SOURCES += \
    src/Classification/Processing.cpp \
    src/Classification/FileRead.cpp \
    src/Classification/Display.cpp \
    src/Classification/Color.cpp \
    src/main/XmdvTool.cpp \
    src/main/TreeWidget.cpp \
    src/main/Strucparam.cpp \
    src/main/ParameterWidget.cpp \
    src/main/mainwindow.cpp \
    src/main/glwidget.cpp \
    src/main/FastTrackball.cpp \
    src/main/doubleSlider.cpp \
    src/Classification/tensor3dVoting.cpp \
    src/Classification/OctreeSerial.cpp \
    src/Classification/octree_pointcloud.cpp



INCLUDEPATH += src

QMAKE_CXXFLAGS += -g -Wno-deprecated -fPIC


INCLUDEPATH += /usr/local/cuda-5.5/include /usr/include /usr/local/include/pcl-1.7 /usr/include/eigen3 -I/usr/include/teem

QMAKE_LIBDIR += /usr/local/cuda-5.5/lib64 /usr/local/lib /usr/lib /usr/local/lib/Teem-1.12.0

LIBS += -lboost_system -lpcl_common -lpcl_io_ply -lpcl_io -lpcl_kdtree -lpcl_keypoints -lpcl_octree -lpcl_filters
LIBS += -lpcl_search -lpcl_filters -lpcl_segmentation -lpcl_features -lpcl_search -lGL -lGLU
LIBS += -lteem


LIBS    += -lcudart
LIBS    += -lpcl_gpu_containers -lpcl_gpu_features -lpcl_gpu_octree -lpcl_gpu_surface -lpcl_gpu_utils





















