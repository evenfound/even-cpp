/**
 * @file    Network.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 29, 2018, 7:49 PM
 */

#pragma once

#include "Config.hxx"
#include "Node.hxx"
#include "Controller.hxx"
#include "TransactionTree.hxx"

#include <initializer_list>
#include <QObject>
#include <QHash>
#include <QString>

namespace even {

class Network : public QObject, private Config {
        Q_OBJECT
    public:

        /** @brief Go random address for simulate */
        static QString randomAddress();

        //< TODO: make network singletons
        static Network* networkPtr;

        /**
         * @brief Create object Network
         * @param config_ - list of network parameters
         */
        Network(std::initializer_list<Value> config_);
        ~Network() final;
        
        /** @brief Initialize data and create Network */
        bool create();

        /** @brief Destroy all objects from Network. */
        void clear();
        
        /** @brief Return value set in json array with children object packed */
        QJsonObject encode() override;

        /** @brief Return values in json array packed by path_ set */
        bool serialize(QString path_, QJsonObject& other_) override;

        /** @brief Stop/Run simulation */
        bool run(bool on_ = true);

        /** @brief Shared spce observer */
        TransactionTree* lookupShared();

        /** @brief Got a node random hash */
        QString networkRandomAddress();

    public slots:
        /** @brief Handle Timer shots. */
        void processOneThing(QTimer* _timer);

    signals:
        /** @brief Emit timer launcher. */
        void startTimer(int tick_);

        /** @brief Emit timer breaker. */
        void stopTimer();

private:

        /**
         * @brief Network Nodes hash array
         * @param key - Node Public Key
         * @param Value - Node object
         */
        QHash<QString, Controller<Node>* > _network;

        /** @brief ATTENTION: pointer to QTimer, launched in another
         * thread */
        QTimer* _timer=nullptr;

        /** @brief Tree of shared transactions */
        TransactionTree _shared;
};
};


