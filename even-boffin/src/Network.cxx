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
    Config(config_)
{
    for (const Value v : config_)
        addValue(v);
    // Attach this to Http handle
    WebServer::instance()->appendConfig(this, "process/status");
    WebServer::instance()->appendConfig(this, "process/start");
    WebServer::instance()->appendConfig(this, "process/stop");
}

//------------------------------------------------------------------------------
//Network::Network(const Network& orig) :
//    QObject(),
//    Config() {
//}

//------------------------------------------------------------------------------
Network::~Network() {
    // Break the timer
    emit stopTimer();
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
            Controller<Node> *node  = new Controller<Node>({
                    {QString(u8"node"), u8"object", u8"Type object"}
                    , {d.key(), u8"hash", u8"Public key(test)"}
                    , {d.value(), u8"path", u8"Path of node IPFS storage"}});
            _network.insert(d.key(), node);
        }
        return true;
    } else {
        clear();
        for (int i = 0; i < getValue("network_size").toInt(); i++) {
            Controller<Node> *node = new Controller<Node>({
                    {QString(u8"node"), u8"object", u8"Type object"}
                    , {getValue(u8"path").toString(), u8"path", u8"Path of node IPFS storage"}});
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
void Network::processOneThing(QTimer* timer_) {
    _timer = timer_;
    INFO(15) << "Receive tick from application..";
    for(auto &n: _network) {
        emit n->operate("Tick modeling fire..");
    }
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

//------------------------------------------------------------------------------
bool Network::serialize(QString path_, QJsonObject& other_) {
    if(path_ == "process/start" && run()) {
        other_.insert("status", "Simulation started sacccess..");
        return true;
    } else if(path_ == "process/stop" && run(false)) {
        other_.insert("status", "Simulation stopped sacccess..");
        return true;
    } else if(path_ == "process/status") {
        if(_timer != nullptr && _timer->isActive())
            other_.insert("status", "running");
        else
            other_.insert("status", "stopped");
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
bool Network::run(bool on_) {
    int tick = getValue(u8"tick").toInt();
    if(!tick)
        return false;
    if(on_) {
        INFO(15) << QString("Emit start timer %1..")
                    .arg(tick);
        emit startTimer(tick);
    } else {
        INFO(15) << "Emit stop timer..";
        emit stopTimer();
    }
    return true;
//    for(auto &o: _network) {
//        o->run(on_);
//    }
}
