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
            $$PWD/../src/core/Hash.cxx \
            $$PWD/../src/core/TransactionTree.cxx \
            $$PWD/../src/web/TemplateController.cxx \
            $$PWD/../src/web/SessionController.cxx \
            $$PWD/../src/core/Exposition.cxx \
    ../src/core/SignalHandler.cxx


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
            $$PWD/../include/core/Hash.hxx \
            $$PWD/../include/core/TransactionTree.hxx \
            $$PWD/../include/core/Random.hxx \
            $$PWD/../include/web/TemplateController.hxx \
            $$PWD/../include/web/SessionController.hxx \
            $$PWD/../include/core/Exposition.hxx
