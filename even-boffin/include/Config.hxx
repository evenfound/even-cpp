/**
 * @file    Config.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 27, 2018, 7:49 PM
 */

#pragma once

#include <QHash>
#include "Value.hxx"

namespace even {

    /** @brief Private Network config class */
    class Config {
    public:
        /**
         * @brief Set config value by name. 
         * @param intro_ - value name
         * @param value_ - value object
         * @return none
         */
        void setValue(const QString &intro_, const QVariant &value_);

        /**
         * @brief Set config value. 
         * @param value_ - value object
         * @return none
         */
        void setValue(const Value &value_);
        
        /**
         * Got value by name.
         * @param intro_ - value name.
         * @return - QVariant object of value
         */
        const QVariant &getValue(const QString &intro_);
        
        /**
         * @brief Return string introduction of config array
         * @return - String? contained line with all values formatted as pairs
         */
        const QString echo();

    private:
        /** @brief Array of Value parameters array. */
        QHash<const QString, Value> _config;

    };
};

