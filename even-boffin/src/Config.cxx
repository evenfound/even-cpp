/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Config.hxx"

namespace even {

    /**
     * @brief Set config value by name. 
     * @param intro_ - value name
     * @param value_ - value object
     * @return none
     */
    void Config::setValue(const QString &intro_, const QVariant &value_) {
        _config.insert(intro_, Value(value_, intro_));
    }

    /**
     * Got value by name.
     * @param intro_ - value name.
     * @return - QVariant object of value
     */
    const QVariant &Config::getValue(const QString &intro_) {
        return _config[intro_].value();
    }

    /**
     * @brief Set config value. 
     * @param value_ - value object
     * @return none
     */
    void Config::setValue(const Value &value_) {
        _config.insert(value_.name(), value_);
    }

    /**
     * @brief Return string introduction of config array
     * @return - String? contained line with all values formatted as pairs
     */
    const QString Config::echo() {
        QStringList line;
        for(const Value v: _config)
            line << "\n\t\t\t{" + v.name() + ", " + v.value().toString() + "}";
        return line.join(",");
    }

};