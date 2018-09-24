/**
 * @file    Node.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 24, 2018, 7:49 PM
 */

#include "Logger.hxx"
#include "Node.hxx"

using namespace even;

///< @brief System node count in system created.
long Node::nodeCount = 0L;

//------------------------------------------------------------------------------
///< @brief Parametric constructor
Node::Node(std::initializer_list<Value> config_) :
    Config(),
    _left(0L),
    _right(0L)
{
    Node::nodeCount++;
    setValue(u8"object",{"Node"});
    setValue(u8"#",{Node::nodeCount});

    //< Position Node in Network topology.
    setValue(u8"xpos", {0.0});
    setValue(u8"ypos", {0.0});

    //< Edges, that constrains new triangle
    //< in developing topology process.
    setValue(u8"d1", {0.0});
    setValue(u8"d2", {0.0});

    for (const Value v : config_)
        setValue(v);

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
void Node::doWork(const QString &message_) {

}

