/**
 * @file    Controller.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 24, 2018, 7:49 PM
 */

#include <QCoreApplication>
#include "Controller.hxx"
#include "Logger.hxx"

using namespace even;

//------------------------------------------------------------------------------
_Controller::_Controller() :
    QObject()
{
}

//------------------------------------------------------------------------------
void _Controller::hideToThread(QObject &object_) {
    object_.moveToThread(&_workerThread);
    //< Mark object to kill in process destruction.
    //connect(&_workerThread, &QThread::finished, &object_, &QObject::deleteLater);
    //object_.deleteLater();
}

//------------------------------------------------------------------------------
_Controller::~_Controller() {
}

//------------------------------------------------------------------------------
void _Controller::start(void) {
    _workerThread.start();
}

//------------------------------------------------------------------------------
void _Controller::terminate() {
    _workerThread.terminate();
    _workerThread.wait();
}

//------------------------------------------------------------------------------
template<typename T> Controller<T>::Controller(std::initializer_list<Value> config_) :
    _Controller(),
    _t(new T(config_))
{
    //< Move object to his thread context
    hideToThread(*_t);

    //< Connection of event callbacks
    connect(this, &_Controller::operate, _t, &T::doWork);
    connect(_t, &T::resultReady, this, &_Controller::handleResults);

    //< Latency start of object thread
    start();
}

//------------------------------------------------------------------------------
template<typename T> Controller<T>::Controller(const Controller<T>& orig_) {
    _t = orig_._t;
}

//------------------------------------------------------------------------------
template<typename T> Controller<T>& Controller<T>::operator=(const Controller<T>& orig_) {
    _t = orig_._t;
    return *this;
}

//------------------------------------------------------------------------------
template <typename T> void Controller<T>::handleResults(const QString&) {

}

//------------------------------------------------------------------------------
template<typename T> Controller<T>::~Controller() {
    terminate();
    delete _t;
}

//------------------------------------------------------------------------------
//template <typename T> void Controller<T>::operate(const QString&) {
//}


