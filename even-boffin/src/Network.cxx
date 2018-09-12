/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Network.cxx
 * Author: zipper
 *
 * Created on August 27, 2018, 4:59 PM
 */
#include <QUuid>
#include <QException>
#include <QCoreApplication>
#include "Network.hxx"
#include "Logger.hxx"

#include "Controller.cxx"

using namespace std;

namespace even {

template class Controller<Node>;

Network::Network(initializer_list<Value> config_) :
    QObject(),
    Config() {
    setValue(u8"object",{"Network"});
    for (const Value v : config_)
        setValue(v);
}

Network::Network(const Network& orig) :
    QObject(),
    Config() {
}

Network::~Network() {
    clear();
    INFO(15) << "Destroy Network object success..";
}

//------------------------------------------------------------------------------

void Network::clear() {
    try {
        if (!_network.isEmpty()) {

            INFO(20) << "Start destroy nodes...";

            /*
            while(!_network.isEmpty()) {
                delete _network.takeLast();
            }*/

            qDeleteAll(_network);

            _network.clear();

            DEBUG(10) << "Destroyed all nodes from Network";
        }
    } catch(QException& e) {
        CRITICAL(5) << QString("Error while deleteing Nodes: %1").arg(e.what());
    }
}

//------------------------------------------------------------------------------
/** @brief Initialize data and create Network */

bool Network::create() {

    if (!getValue("network_size").toInt()) {
        WARNING(5) << "Network size is 0, exit creation..";
        return false;
    }

    clear();

    for (int i = 0; i < getValue("network_size").toInt(); i++) {
        QString id_rsa = QUuid::createUuid().toString();
        //<! Public Key - is a GUID
        _network.insert(id_rsa, new Controller< Node >({
                                                       {id_rsa, u8"id_rsa"},
                                                   }));
    }
    return true;
}

}

