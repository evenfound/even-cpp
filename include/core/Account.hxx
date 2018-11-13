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
        Account();
        ~Account() = default;

    private:
        /** @brief  ByteArray unique hash of this transaction  */
        QByteArray _byteHash;

        /** @brief  String unique hash of this transaction  */
        Hash _hash;
};

};

