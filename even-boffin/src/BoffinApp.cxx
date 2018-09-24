/**
 * @file    BoffinApp.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 24, 2018, 7:49 PM
 */

#include "Logger.hxx"
#include "BoffinApp.hxx"

//------------------------------------------------------------------------------
BoffinApp::BoffinApp(int argc, char *argv[]) :
    QGuiApplication(argc, argv),
    Application()
{
    Application::main(argc, argv);
}

//------------------------------------------------------------------------------
int BoffinApp::exec() {
    int retval = QGuiApplication::exec();
    if (isRunning())
        terminate();
    return retval;
}

//------------------------------------------------------------------------------
bool BoffinApp::handleSignal(int signal) {
    //std::cout << "Handling signal " << signal << std::endl;
    INFO(10) << QString("Handling signal %1").arg(signal);
    if (isRunning())
    {
        INFO(20) << "Start terminate main thread...";
        //QCoreApplication::exit(0);
        terminate();

        wait();
        INFO(20) << "Waiting success...";

        QCoreApplication::exit(0);

        // The thread is going to stop soon, so don't propagate this signal further
        return true;
    }
    INFO(20) << "Main thread not running...";
    // Let the signal propagate as though we had not been there
    return false;
}

