# CONFIG += console

QT += datavisualization

# qml quick

TEMPLATE = app

TARGET = even-boffin

INCLUDEPATH += ./include

# QMAKE_CXXFLAGS += -std=c++11

# The .cpp file which was generated for your project. Feel free to hack it.

win32 {
    INCLUDEPATH += $$(BOOST_ROOT)
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
            src\Logger.cxx\
            src\Config.cxx\
            src\Controller.cxx \
            src\Application.cxx \
            src\SignalHandler.cxx \
            src\BoffinApp.cxx

HEADERS += include\datasource.h \
            include\Node.hxx \
            include\NodeNetwork.hxx\
            include\Logger.hxx\
            include\Network.hxx\
            include\Value.hxx\
            include\Config.hxx\
            include\Controller.hxx \
            include\Controller.hxx \
            include\Application.hxx \
            include\SignalHandler.hxx \
            include\BoffinApp.hxx \
            ../include/core/Core.hxx \
            ../include/core/Defines.hxx

RESOURCES += even-boffin.qrc

OTHER_FILES += doc/src/* \
               doc/images/* \
               qml/boffin/*


#DESTDIR = dist
OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc
UI_DIR = .ui
