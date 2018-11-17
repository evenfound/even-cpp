/**
 * @file    Controller.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 29, 2018, 7:49 PM
 */

#pragma once

#include <QObject>
#include <QThread>
#include <QSharedPointer>

#include "Value.hxx"
namespace even {
    
    /** 
     * @brief Base class for incapsulate QObject signals-slot
     * functionality for derived object equipped threaded work
     * environment 
     */
    
    class _Controller : public QObject {
        Q_OBJECT
    public:

        _Controller();
        virtual ~_Controller();

        /** @brief Move derivative class object to thread */
        void hideToThread(QObject &object_);

        /** @brief Terminate thread. */
        void terminate();

        /** @brief Launch the controller thread. */
        void start(void);

    public slots:
        virtual void handleResults(const QString &) = 0;

    signals:
//        virtual void operate(const QString &) = 0;
        virtual void operate(const QString &);

    private:
        QThread _workerThread; ///< @brief Worker thread for objects
    };

    /**
     * @brief Universal reduction class for create threaded work containers
     */
    template<typename T> class Controller : public _Controller {
    public:

        /** @brief Creating constructor with Value
         * value parameters list.
         */

        Controller(std::initializer_list<Value> config_);

        /** @brief Copy constructor */
        explicit Controller(const Controller<T> &orig);
        virtual ~Controller() override;

        void handleResults(const QString &) override;
//        void operate(const QString &) override;

        Controller<T>& operator=(const Controller<T> &orig_);

        /** @brief Return pointer to _t */
        inline T* operator->() { return get(); }

        /** @brief Return pointer to _t */
        inline T* get() { return _t; }

    private:
        T* _t; ///<@brief Pointer to object memory.
    };
};

