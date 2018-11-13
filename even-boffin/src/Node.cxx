/**
 * @file    Node.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 24, 2018, 7:49 PM
 */

#include "Logger.hxx"
#include "Node.hxx"
#include "WebServer.hxx"

#include <QDir>

using namespace even;

///< @brief System node count in system created.
long Node::nodeCount = 0L;

//------------------------------------------------------------------------------
///< @brief Parametric constructor
Node::Node(std::initializer_list<Value> config_) :
    Config(config_),
    _left(0L),
    _right(0L)
{
    Node::nodeCount++;
    addValue(u8"object",{"Node"}, u8"Object type");
    addValue(u8"#",{Node::nodeCount}, u8"Node index");

    // Position Node in Network topology.
    addValue(u8"xpos", {0.0}, u8"x position in topology");
    addValue(u8"ypos", {0.0}, u8"y position in topology") ;

    // Edges, that constrains new triangle
    // in developing topology process.
    addValue(u8"d1", {0.0}, u8"--");
    addValue(u8"d2", {0.0}, u8"--");

    for (auto &v : config_)
        addValue(v);

    if(!QDir(getValue(u8"path").toString()).exists()) {
        QDir().mkdir(getValue(u8"path").toString());
        QDir().mkdir(getValue(u8"path").toString() + "/inbox");
        QDir().mkdir(getValue(u8"path").toString() + "/outbox");
    }

    // Attach this to Http handle
    WebServer::instance()->appendObject("Node", this);

    DEBUG(15) << QString("Node # %1 created.").arg(Node::nodeCount);
}

//------------------------------------------------------------------------------
Node::~Node() {
    Node::nodeCount--;
    DEBUG(15) << QString("Destroy Node # %1 (left %2)")
                 .arg(getValue(u8"#").toLongLong())
                 .arg(Node::nodeCount);
}

//------------------------------------------------------------------------------
void Node::doWork(const QString&) {

}

