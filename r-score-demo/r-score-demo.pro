QT += network widgets

TEMPLATE = app

TARGET = r-score-demo

INCLUDEPATH += $$PWD/include \
    $$PWD/../include/core \
    $$PWD/../include/widgets \
    $$PWD/../include/algorithms \
    $$PWD/../prerequisites/QtWebApp/QtWebApp \
    $$PWD/../prerequisites\QtWebApp\QtWebApp\qtwebsockets\src\websockets

HEADERS += \
    include/Controls.h \
    include/ChartRscore.h \
    ../include/widgets/ChartEasy.hxx \
    ../include/widgets/ValueSlider.hxx \
    ../include/core/Value.hxx \
    ../include/core/Config.hxx \
    ../include/core/Logger.hxx \
    ../include/algorithms/Rscore.hxx \
    ../include/widgets/Scene.hxx


SOURCES += \
    src/main.cpp \
    src/Controls.cpp \
    src/ChartRscore.cpp \
    ../src/widgets/ChartEasy.cxx \
    ../src/widgets/ValueSlider.cxx \
    ../src/core/Value.cxx \
    ../src/core/Config.cxx \
    ../src/core/Logger.cxx \
    ../src/algorithms/Rscore.cxx \
    ../src/widgets/Scene.cxx




