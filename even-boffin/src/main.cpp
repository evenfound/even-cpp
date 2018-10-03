/**
 * @file    main.cpp
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 24, 2018, 7:49 PM
 */

#include "datasource.h"
#include <QtDataVisualization/qutils.h>
#include <QtGui/QGuiApplication>
#include <QtCore/QDir>
//#include <QtQml/QQmlContext>
//#include <QtQuick/QQuickView>
//#include <QtQml/QQmlEngine>
#include <QException>

#include "BoffinApp.hxx"
#include "Logger.hxx"
#include "Network.hxx"

using namespace even;

///< TODO: resolve this trouble more detailed after reconstrain project
///< under linux

/** @brief Main function of application */
int main(int argc, char *argv[]) {

    INFO(20) << "Start boffin application ...";

    try {

        //QGuiApplication app(argc, argv);
        BoffinApp app(argc, argv);

        // Сreate Network object

        Network network({
                            {50, "network_size"},  // Node network count, integer digit 0...1024
                            {10, "proof_nodes"},    // Count of proofed nodes, percent
                            {1, "tick"},            // Modeling timer tick, msec
                        });

        network.create();

/**
        QQuickView viewer;

        // Enable antialiasing in direct rende ring mode
        //! [1]
        viewer.setFormat(QtDataVisualization::qDefaultSurfaceFormat());
        //! [1]

        // The following are needed to make examples run without having to install the module
        // in desktop environments.
#ifdef Q_OS_WIN
        QString extraImportPath(QStringLiteral("%1/../../../%2"));
#else
        QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif
        viewer.engine()->addImportPath(extraImportPath.arg(QGuiApplication::applicationDirPath(),
                                                           QString::fromLatin1("qml")));

        QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

        viewer.setTitle(QStringLiteral("Oscilloscope example"));

        //! [0]
        DataSource dataSource;
        viewer.rootContext()->setContextProperty("dataSource", &dataSource);
        //! [0]

        viewer.setSource(QUrl("qrc:/qml/boffin/main.qml"));
        viewer.setResizeMode(QQuickView::SizeRootObjectToView);
        viewer.show();
*/
        return app.exec();
    } catch (std::exception& e) {
        CRITICAL(5) << "main: Application closed by error: " << e.what();
    }
}
