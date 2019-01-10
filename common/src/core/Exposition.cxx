/**
 * @file    Exposition.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 13, 2018, 03:06 PM
 */

#include "Exposition.hxx"
#include "Logger.hxx"
#include "Singleton.hxx"
#include "WebServer.hxx"

using namespace even;

//------------------------------------------------------------------------------
Exposition::Exposition()
    : Config({{QString(u8"exposition"), u8"object", u8"Type object"}})
{
    addValue(u8"transact-per-sec", 0.0, u8"Number of transactions per second"
             , {0.0, 0.0, 0.0, 4, true});
    addValue(u8"confirm-time-sec", 0.0, u8"Average confirmation time (sec.)"
             , {0.0, 0.0, 0.0, 1, true});
    addValue(u8"operated", 0, u8"Current trans. operated nodes"
             , {0.0, 0.0, 0.0, 0, true});
    WebServer::instance()->appendConfig(this, "process/exposition");
}

//------------------------------------------------------------------------------
Exposition::~Exposition() {
    INFO(10) << "Exposition singleton destroyed..";
}

//------------------------------------------------------------------------------
bool Exposition::serialize(QString path_, QJsonObject& other_) {
    INFO(20) << "Have a path " << path_ << " in Exposition ..";
    if(path_ == "process/exposition") {
        other_.insert(path_, encode());
        return true;
    }
    return false;
}

//-----------------------------------------------------------------------------  -
Exposition* Exposition::instance()
{
    return Singleton<Exposition>::instance(Exposition::createInstance);
}

//------------------------------------------------------------------------------
Exposition* Exposition::createInstance()
{
    return new Exposition();
}

