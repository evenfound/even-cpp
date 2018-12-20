/**
 * @file    Exposition.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 27, 2018, 04:27 PM
 */

#pragma once

#include "Config.hxx"

#include <QString>

namespace even {

/** @brief Entitity of exposition data handler */
class Exposition : public Config {
    public:
        explicit Exposition();
        virtual ~Exposition();

        /** @brief Take a singleton object pointer */
        static Exposition* instance();

        /** @brief Return values in json array packed by path_ set */
        bool serialize(QString path_, QJsonObject& other_) final;

    private:

        /** @brief Create singleton once object */
        static Exposition* createInstance();
};

};

