/**
 * @file    Config.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 27, 2018, 7:49 PM
 */

#pragma once

#include "Value.hxx"
#include "httpserver/httplistener.h"
#include "RequestHandler.hxx"

#include <QHash>
#include <QSharedPointer>
#include <QJsonObject>

namespace even {

using namespace stefanfrings;

class RequestHandler;

/** @brief Private Network config class */
class Config {
    public:

        /** @brief Iterator for serialize config value  from other access */
        typedef QHash<const QString, Value>::iterator iterator;

        /** @brief Create values constructor */
        Config(std::initializer_list<Value> config_);

        /** @brief  Return first element */
        iterator begin();

        /** @brief  Return end iterator of array */
        iterator end();

        /**
         * @brief Set config value by name.
         * @param name_  - value name
         * @param value_ - value object
         * @param intro_ - introduction of value
         * @return none
         * @param range_    - set range interval and step of change
         */
        void addValue(const QString &name_
                      , const QVariant &value_
                      , const QString& intro_ = "unknown usage"
                , Value::Property property_ = {0.0, 1000.0, 100.0, 2, true});

        /**
         * @brief Update config value by name.
         * @param name_  - value name
         * @param value_ - value object
         * @param intro_ - introduction of value
         * @return none
         */
        void setValue(const QString &name_, const QVariant &value_);

        /**
         * @brief Set config value.
         * @param value_ - value object
         * @return none
         */
        void addValue(const Value &value_);
        
        /**
         * Got value by name.
         * @param name_ - value name.
         * @return - QVariant object of value
         */
        const QVariant &getValue(const QString &name_);
        
        /**
         * @brief Return string introduction of config array
         * @return - String? contained line with all values formatted as pairs
         */
        const QString echo();

        /** @brief Return value set in json array packed */
        virtual QJsonObject encode();

        /** @brief Return values in json array packed by path_ set */
        virtual bool serialize(QString path_, QJsonObject& other_) = 0;

    private:
        QHash<const QString, Value> _config;    ///< @brief Array of Value parameters array.
};

};

