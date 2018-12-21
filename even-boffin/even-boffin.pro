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
    win32:      LIBS += -L$$PWD/../bin/ -lQtWebAppd1
    mac:        LIBS += -L$$PWD/../bin/ -lQtWebAppd_debug
    unix:!mac:  LIBS += -L$$PWD/../bin/ -lQtWebAppd
}

win32 {
   DEFINES += QTWEBAPPLIB_IMPORT
}

SOURCES += ./src/main.cpp \
            ./src/Node.cxx \
            ./src/NodeNetwork.cxx\
            ./src/Network.cxx\
            ./src\BoffinApp.cxx \
            ../src/core/Value.cxx\
            ../src/core/Controller.cxx \
            ../src/core/Config.cxx \
            ../src/core/Application.cxx \
            ../src/core/SignalHandler.cxx \
            ../src/core/Logger.cxx \
            ../src/core/Message.cxx \
            ../src/core/FileConfig.cxx \
            ../src/web/RequestHandler.cxx \
            ../src/web/TemplateHolder.cxx \
            ../src/web/WebServer.cxx \
            ../src/core/Storage.cxx \
            ../src/core/Wallet.cxx \
            ../src/core/Transaction.cxx \
            ../src/core/Account.cxx \
            ../src/core/Hash.cxx \
            ../src/core/TransactionTree.cxx \
            ../src/web/TemplateController.cxx \
            ../src/web/SessionController.cxx \
            ../src/core/Exposition.cxx


HEADERS += ./include/Node.hxx \
            ./include/NodeNetwork.hxx\
            ./include/Network.hxx\
            ./include/BoffinApp.hxx \
            ../include/core/Value.hxx \
            ../include/core/Controller.hxx \
            ../include/core/Config.hxx \
            ../include/core/Core.hxx \
            ../include/core/Defines.hxx \
            ../include/core/Logger.hxx \
            ../include/core/Message.hxx \
            ../include/core/Application.hxx \
            ../include/core/FileConfig.hxx \
            ../include/core/CallOnce.hxx \
            ../include/core/Singleton.hxx \
            ../include/core/SignalHandler.hxx \
            ../include/web/RequestHandler.hxx \
            ../include/web/TemplateHolder.hxx \
            ../include/web/WebServer.hxx \
            ../include/core/Storage.hxx \
            ../include/core/Wallet.hxx \
            ../include/core/Transaction.hxx \
            ../include/core/Account.hxx \
            ../include/core/Hash.hxx \
            ../include/core/TransactionTree.hxx \
            ../include/core/Random.hxx \
            ../include/web/TemplateController.hxx \
            ../include/web/SessionController.hxx \
            ../include/core/Exposition.hxx
