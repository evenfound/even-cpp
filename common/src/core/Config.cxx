/**
 * @file    Config.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 24, 2018, 7:49 PM
 */

#include "Config.hxx"
#include "Logger.hxx"
#include "WebServer.hxx"

using namespace even;
using namespace std;
using namespace stefanfrings;

//------------------------------------------------------------------------------
Config::Config(std::initializer_list<Value> config_) {
    for (auto &v : config_)
        addValue(v);
//    WebServer::instance()->appendConfig(this);
}

//------------------------------------------------------------------------------
Config::iterator Config::begin() {
    return _config.begin();
}

//------------------------------------------------------------------------------
Config::iterator Config::end() {
    return _config.end();
}

//------------------------------------------------------------------------------
void Config::addValue(const QString &name_
                      , const QVariant &value_
                      , const QString& intro_
                      , Value::Property property_) {
    _config.insert(name_, Value(value_, name_, intro_, property_));
}

//------------------------------------------------------------------------------
void Config::setValue(const QString &name_, const QVariant &value_) {
    auto value = _config.find(name_);
    if(value != _config.end())
        value->setValue(value_);
    else {
        CRITICAL(1) << QString("Value named %1 not finded and failed init to %2...")
                       .arg(name_)
                       .arg(value_.toString());
    }
}

//------------------------------------------------------------------------------
const QVariant &Config::getValue(const QString &name_) {
    return _config[name_].get();
}

//------------------------------------------------------------------------------
void Config::addValue(const Value &value_) {
    _config.insert(value_.name(), value_);
}

//------------------------------------------------------------------------------
const QString Config::echo() {
    QStringList line;
    for(auto &v: _config)
        line << "\n\t\t\t{" + v.name() + ", " + v.get().toString() + "}";
    return line.join(",");
}

//------------------------------------------------------------------------------
QJsonObject Config::encode() {
    QJsonObject other;
    for(auto v = _config.begin(); v != _config.end(); ++v) {
            other.insert(v.key(), v.value().encode());
    }
    return other;
}


