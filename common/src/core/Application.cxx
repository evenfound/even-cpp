/**
 * @file    Application.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 24, 2018, 7:49 PM
 */

#include "Application.hxx"
#include "Logger.hxx"

//#include <QLoggingCategory>

using namespace even;

//------------------------------------------------------------------------------
Application::Application() :
    SignalHandler(SignalHandler::SIG_INT)
{
//    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
}

//------------------------------------------------------------------------------
bool Application::isRunning() {
    return (_myThread && _myThread->isRunning());
}

//------------------------------------------------------------------------------
void Application::terminate() {
    if(_myThread)
        _myThread->terminate();
}

//------------------------------------------------------------------------------
bool Application::wait() {
    return _myThread->wait();
}

//------------------------------------------------------------------------------
int Application::_main(int, char*[])
{
   // Main program instructions here (e.g. start a thread)
    _myThread = new QThread();
    _myThread->start();
    return 0;
}

//------------------------------------------------------------------------------
Application::~Application() {
    _myThread->wait();
    delete _myThread;
    INFO(10) << "Destroy Application object";
}
