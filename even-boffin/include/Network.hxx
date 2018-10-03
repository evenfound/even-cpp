/**
 * @file    Network.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 29, 2018, 7:49 PM
 */

#pragma once

#include <initializer_list>
#include <QObject>
#include <QHash>
#include <QString>

#include "Config.hxx"
#include "Node.hxx"
#include "Controller.hxx"

namespace even {

class Network : public QObject, private Config {
        Q_OBJECT
    public:
        /**
         * @brief Create object Network
         * @param config_ - list of network parameters
         */
        Network(std::initializer_list<Value> config_);
        Network(const Network& orig);
        ~Network() final;
        
        /** @brief Initialize data and create Network */
        bool create();

        /** @brief Destroy all objects from Network. */
        void clear();
        
    private:

        /** @brief Network Nodes hash array.
         *  @param key - Node Public Key
         *  @param Value - Node object
         */

        // QMap<QString, Controller<Node>* > _network;
        QHash<QString, Controller<Node>* > _network;

};
};


