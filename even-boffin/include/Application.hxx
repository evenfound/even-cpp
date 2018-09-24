/**
 * @file    Application.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 24, 2018, 7:49 PM
 */

#pragma once

#include <QThread>
#include <QCoreApplication>
#include "SignalHandler.hxx"
#include <iostream>

class Application : public SignalHandler
{
public:
    Application();
    virtual ~Application();

    /** @brief Return status of main thread. */
    bool isRunning();

    /** @brief Terminate main thread. */
    void terminate();

    /** @brief Wait for terminate app thread.
     * @return True if waiting success.
     */
    bool wait();

protected:
    int main(int argc, char *argv[]);

private:
    QThread* _myThread;
};

