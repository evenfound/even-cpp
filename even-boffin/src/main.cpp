/**
 * @file    main.cpp
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 24, 2018, 7:49 PM
 */

#include "BoffinApp.hxx"
#include "Logger.hxx"
#include "WebServer.hxx"
#include "Network.hxx"

#include <QtGui/QGuiApplication>
#include <QtCore/QDir>
#include <QException>
#include <QDebug>

#include <QLoggingCategory>

using namespace even;

/** @brief Main function of application */
int main(int argc, char *argv[]) {

    INFO(20) << "Start boffin application ...";

    try {

        //QGuiApplication app(argc, argv);
        BoffinApp app(argc, argv);

        // Сreate Network object

        Network network;

        // Connect simulation timer to threaded Network object, that runnig processe self
        network.connect(&network, SIGNAL(startTimer(int)), &app, SLOT(timerOn(int)));
        network.connect(&network, SIGNAL(stopTimer()), &app, SLOT(timerOff()));
        network.connect(&app, SIGNAL(shot(QTimer*)), &network, SLOT(processOneThing(QTimer*)));

        network.create();

        return app.exec();
    } catch (std::exception& e) {
        CRITICAL(5) << "main: Application closed by error: " << e.what();
    }
    return 0;
}
