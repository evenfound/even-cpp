/**
 * @file    Config.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 24, 2018, 7:49 PM
 */

#include "Config.hxx"

using namespace even;

//------------------------------------------------------------------------------
void Config::setValue(const QString &intro_, const QVariant &value_) {
    _config.insert(intro_, Value(value_, intro_));
}

//------------------------------------------------------------------------------
const QVariant &Config::getValue(const QString &intro_) {
    return _config[intro_].value();
}

//------------------------------------------------------------------------------
void Config::setValue(const Value &value_) {
    _config.insert(value_.name(), value_);
}

//------------------------------------------------------------------------------
const QString Config::echo() {
    QStringList line;
    for(const Value v: _config)
        line << "\n\t\t\t{" + v.name() + ", " + v.value().toString() + "}";
    return line.join(",");
}

