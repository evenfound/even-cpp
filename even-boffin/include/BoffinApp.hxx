/**
 * @file    BoffinApp.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 24, 2018, 7:49 PM
 */

#pragma once

#include "Application.hxx"

#include <QThread>
#include <QGuiApplication>
#include <iostream>
#include <QTimer>

namespace even {

class BoffinApp :
        public QGuiApplication,
        private Application
{
        Q_OBJECT
    public:
        BoffinApp(int argc, char *argv[]);

        /** @brief QGuiApplication exec routines.*/
        int exec();

    public slots:
        /** @brief Receive tick number of timer shots
     * and run timer. */
        void timerOn(int tick_);

        /** @brief Stop timer. */
        void timerOff();

        /** @brief Handle Timer shots. */
        void processOneThing();

    signals:
        /** @brief Emit timer shots. */
        void shot(QTimer* _timer);

    protected:
        virtual bool handleSignal(int signal);

    private:
        /** @brief Simulation timer - sent all nodes
     * start tick signal for step iterate
     */
        QTimer* _timer = nullptr;

}; // class BoffinApp : public QGuiApplication,private Application

} // namespace even {
