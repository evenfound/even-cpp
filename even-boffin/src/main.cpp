/****************************************************************************
 **
 ** Copyright (C) 2016 The Qt Company Ltd.
 ** Contact: https://www.qt.io/licensing/
 **
 ** This file is part of the Qt Data Visualization module of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:GPL$
 ** Commercial License Usage
 ** Licensees holding valid commercial Qt licenses may use this file in
 ** accordance with the commercial license agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and The Qt Company. For licensing terms
 ** and conditions see https://www.qt.io/terms-conditions. For further
 ** information use the contact form at https://www.qt.io/contact-us.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3 or (at your option) any later version
 ** approved by the KDE Free Qt Foundation. The licenses are as published by
 ** the Free Software Foundation and appearing in the file LICENSE.GPL3
 ** included in the packaging of this file. Please review the following
 ** information to ensure the GNU General Public License requirements will
 ** be met: https://www.gnu.org/licenses/gpl-3.0.html.
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include "datasource.h"

//! [2]
#include <QtDataVisualization/qutils.h>
//! [2]

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

//< TODO: resolve this trouble more detailed after reconstrain project
//< under linux


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
        //return app.main(argc, argv);
    } catch (std::exception& e) {
        CRITICAL(5) << "main: Application closed by error: " << e.what();
    }

}
