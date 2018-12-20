/**
 * @file    BoffinApp.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 24, 2018, 7:49 PM
 */

#include "Logger.hxx"
#include "BoffinApp.hxx"

using namespace even;

//------------------------------------------------------------------------------
BoffinApp::BoffinApp(int argc, char *argv[]) :
    QGuiApplication(argc, argv),
    Application(),
    _timer(new QTimer(this))
{
    Application::_main(argc, argv);

    connect(_timer, SIGNAL(timeout()), this, SLOT(processOneThing()));
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

//------------------------------------------------------------------------------
void BoffinApp::timerOn(int tick_) {
    _timer->start(tick_);
    INFO(15) << QString("Start timer %1").arg(tick_);
}

//------------------------------------------------------------------------------
void BoffinApp::timerOff() {
    _timer->stop();
    INFO(15) << "Stop timer..";
}

//------------------------------------------------------------------------------
void BoffinApp::processOneThing() {
    INFO(20) << "Fire tick..";
    emit shot(_timer);
}


