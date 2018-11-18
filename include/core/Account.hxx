/**
 * @file    Account.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 13, 2018, 02:34 PM
 */

#pragma once

#include "Hash.hxx"

#include <QString>

namespace even {

/** @brief Entitity of account handler */
class Account {
    public:
        Account() = default;
        ~Account() = default;

        Account(const Hash& parent_);

        /** @brief Got a hash refrence */
        Hash &hash() { return _hash; }

    private:
        /** @brief  String unique hash of this account  */
        Hash _hash;
        /** @brief Parent wallte hash */
        Hash _parent;
};

};

