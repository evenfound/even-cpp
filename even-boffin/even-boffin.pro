# CONFIG += console

QT += datavisualization

# qml quick

TEMPLATE = app

TARGET = even-boffin

INCLUDEPATH += ./include ../include/core

# QMAKE_CXXFLAGS += -std=c++11

# The .cpp file which was generated for your project. Feel free to hack it.

win32 {
    INCLUDEPATH += $$(BOOST_ROOT)
}

CONFIG(debug, debug|release) {
    win32:      LIBS += -L$$PWD/../prerequisites/QtWebApp/build/debug/                              -lQtWebAppd1
    mac:        LIBS += -L$$PWD/../build-QtWebApp-Desktop_Qt_5_7_0_clang_64bit-Debug/               -lQtWebApp_debug
    unix:!mac:  LIBS += -L$$PWD/../build-QtWebApp-Desktop_Qt_5_7_0_GCC_64bit-Debug/                 -lQtWebAppd
}


unix {
    LIBS += -lboost_system -lboost_thread -lboost_date_time
}

SOURCES += src\main.cpp \
            src\datasource.cpp \
            src\Node.cxx \
            src\NodeNetwork.cxx\
            src\Network.cxx\
            src\Value.cxx\
            src\BoffinApp.cxx \
            src\Config.cxx \
            src\Controller.cxx \
            ../src/core/Application.cxx \
            ../src/core/SignalHandler.cxx \
            ../src/core/Logger.cxx


HEADERS += include/datasource.h \
            include/Node.hxx \
            include/NodeNetwork.hxx\
            include/Network.hxx\
            include/Value.hxx\
            include/Config.hxx \
            include/Controller.hxx \
            include/Controller.hxx \
            include/BoffinApp.hxx \
            ../include/core/Core.hxx \
            ../include/core/Defines.hxx \
            ../include/core/Logger.hxx \
            ../include/core/Application.hxx
            ../include/core/SignalHandler.hxx \

RESOURCES += even-boffin.qrc

OTHER_FILES += doc/src/* \
               doc/images/* \
               qml/boffin/*


#DESTDIR = dist
OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc
UI_DIR = .ui
