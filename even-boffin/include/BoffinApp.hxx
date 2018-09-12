#pragma once

#include <QThread>
#include <QGuiApplication>
#include <iostream>
#include "Application.hxx"

class BoffinApp :
        public QGuiApplication,
        private Application
{
public:
    BoffinApp(int argc, char *argv[]);

    /** @brief QGuiApplication exec routines.*/
    int exec();

protected:
    virtual bool handleSignal(int signal);

};

