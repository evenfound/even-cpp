/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Network.hxx
 * Author: zipper
 *
 * Created on August 27, 2018, 4:59 PM
 */

#ifndef NETWORK_HXX
#define NETWORK_HXX

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
         * @brief Create object Network with size_ nodes 
         * @param size_
         */
        Network(std::initializer_list<Value> config_);
        Network(const Network& orig);
        virtual ~Network();
        
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
#endif /* NETWORK_HXX */

