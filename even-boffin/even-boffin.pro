TARGET = even-boffin
TEMPLATE = app
QT += core network
#CONFIG += console

INCLUDEPATH += ./include \
    $$PWD/../include/core \
    $$PWD/../include/web \
    $$PWD/../prerequisites/QtWebApp/QtWebApp \
    $$PWD/../prerequisites/QtWebApp/QtWebApp/templateengine \
    $$PWD/../prerequisites/QtWebApp/QtWebApp/qtwebsockets/src/websockets


# Directory where the debug version of the shared library (*.dll or *.so) is stored, and base name of the file.
CONFIG(debug, debug|release) {
    win32:      LIBS += -L$$PWD/../bin/ -lqtwebappd1
    mac:        LIBS += -L$$PWD/../bin/ -lqtwebappd_debug
    unix:!mac:  LIBS += -L$$PWD/../bin/ -lqtwebappd
}

win32 {
   DEFINES += QTWEBAPPLIB_IMPORT
}

SOURCES += src\main.cpp \
            src\Node.cxx \
            src\NodeNetwork.cxx\
            src\Network.cxx\
            src\BoffinApp.cxx \
            $$PWD/../src/core/Value.cxx\
            $$PWD/../src/core/Controller.cxx \
            $$PWD/../src/core/Config.cxx \
            $$PWD/../src/core/Application.cxx \
            $$PWD/../src/core/SignalHandler.cxx \
            $$PWD/../src/core/Logger.cxx \
            $$PWD/../src/core/Message.cxx \
            $$PWD/../src/core/FileConfig.cxx \
            $$PWD/../src/web/RequestHandler.cxx \
            $$PWD/../src/web/TemplateHolder.cxx \
            $$PWD/../src/web/WebServer.cxx \
            $$PWD/../src/core/Storage.cxx \
            $$PWD/../src/core/Wallet.cxx \
            $$PWD/../src/core/Transaction.cxx \
            $$PWD/../src/core/Account.cxx \
            $$PWD/../src/core/Hash.cxx

HEADERS += include/Node.hxx \
            include/NodeNetwork.hxx\
            include/Network.hxx\
            include/BoffinApp.hxx \
            $$PWD/../include/core/Value.hxx \
            $$PWD/../include/core/Controller.hxx \
            $$PWD/../include/core/Config.hxx \
            $$PWD/../include/core/Core.hxx \
            $$PWD/../include/core/Defines.hxx \
            $$PWD/../include/core/Logger.hxx \
            $$PWD/../include/core/Message.hxx \
            $$PWD/../include/core/Application.hxx \
            $$PWD/../include/core/FileConfig.hxx \
            $$PWD/../include/core/CallOnce.hxx \
            $$PWD/../include/core/Singleton.hxx \
            $$PWD/../include/core/SignalHandler.hxx \
            $$PWD/../include/web/RequestHandler.hxx \
            $$PWD/../include/web/TemplateHolder.hxx \
            $$PWD/../include/web/WebServer.hxx \
            $$PWD/../include/core/Storage.hxx \
            $$PWD/../include/core/Wallet.hxx \
            $$PWD/../include/core/Transaction.hxx \
            $$PWD/../include/core/Account.hxx \
            $$PWD/../include/core/Hash.hxx


DESTDIR = $$PWD/../bin
OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc
UI_DIR = .ui
