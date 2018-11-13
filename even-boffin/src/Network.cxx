/**
 * @file    Network.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 24, 2018, 7:49 PM
 */

#include "Network.hxx"
#include "Logger.hxx"
#include "FileConfig.hxx"
#include "WebServer.hxx"
#include "../../src/core/Controller.cxx"

#include <QUuid>
#include <QException>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QDirIterator>
#include <QCryptographicHash>
#include <QTextCodec>

using namespace std;
using namespace even;

template class Controller<Node>;

//------------------------------------------------------------------------------
Network::Network(initializer_list<Value> config_) :
    QObject(),
    Config(config_) {
    addValue(u8"object",{"Network"}, u8"Type object");
    for (const Value v : config_)
        addValue(v);
    // Attach this to Http handle
    WebServer::instance()->appendObject("Network", this);
}

//------------------------------------------------------------------------------
//Network::Network(const Network& orig) :
//    QObject(),
//    Config() {
//}

//------------------------------------------------------------------------------
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
bool Network::create() {

    // Check file system for early created nodes
    // Find ini file and ipfs root path
    QString configFile = FileConfig::instance()->searchConfigFile(QCoreApplication::applicationName());
    QSettings* network = new QSettings(configFile, QSettings::IniFormat, QCoreApplication::instance());
    network->beginGroup("network");
    addValue(u8"network_size"
             , network->value("network_size", 25)
             , u8"Node count");
    addValue(u8"proof_nodes"
             , network->value("proof_nodes", 10)
             , u8"Percent of master nodes");
    addValue(u8"tick"
             , network->value("tick", 1)
             , u8"Modeling timer tick (usec.)");


    QSettings* nodes = new QSettings(configFile, QSettings::IniFormat, QCoreApplication::instance());
    nodes->beginGroup("nodes");
    addValue(u8"path"
             , nodes->value(u8"path", "./ipfs")
             , u8"Full path to IPFS node storages");

    INFO(15) << QString("IPFS path is %1...").arg(getValue(u8"path").toString());

    // If root path is not created - mkdir's him
    if(!QDir(getValue(u8"path").toString()).exists()) {
        QDir().mkdir(getValue(u8"path").toString());
    }

    QDirIterator dirIt(getValue(u8"path").toString()
                       , QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot
                       , QDirIterator::NoIteratorFlags);
    QMap<QString, QString> dirNames;
    auto countDirs = 0;
    while(dirIt.hasNext()){
        ++countDirs;
        dirIt.next();
        dirNames.insert(dirIt.fileName(), dirIt.path());
        INFO(15) << QString("%1...")
                    .arg(dirIt.fileName());
    }

    // If some dirs in choosen path is present
    if(countDirs) {
        clear();
        setValue(u8"network_size", countDirs);
        for(auto d = dirNames.begin(); d != dirNames.end(); ++d) {
            // Public Key - is a Keccak_256
            _network.insert(d.key(), new Controller<Node>({
                      {d.key(), u8"hash", u8"Public key(test)"}
                    , {d.value(), u8"path", u8"Path of node IPFS storage"}}));
        }
        return true;
    } else {
        clear();
        for (int i = 0; i < getValue("network_size").toInt(); i++) {
            Controller<Node> *node = new Controller<Node>({{getValue(u8"path").toString()
                                                            , u8"path", u8"Path of node IPFS storage"}});
            _network.insert((*node)->hash().serialize(), node);
        }
        return true;
    }

    if (!getValue("network_size").toInt()) {
        WARNING(5) << "Network size is 0, exit creation..";
    }

    return false;
}

//------------------------------------------------------------------------------
QJsonObject Network::encode() {
    QJsonObject root = Config::encode();
    QJsonArray children;
    for(auto &o: _network) {
        children.push_back((*o)->encode());
    }
    root.insert(u8"objects", children);
    return root;
}
