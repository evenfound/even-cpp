/**
 * @file    Hash.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 13, 2018, 02:34 PM
 */

#pragma once

#include <QString>

namespace even {

/** @brief Entitity of hash handler */
class Hash {
    public:
        Hash();
        ~Hash() = default;

        /** @brief  Convert hash to readable */
        QString serialize();

    private:
        /** @brief  ByteArray unique hash of this transaction  */
        QByteArray _byteHash;

        /** @brief  String unique hash of this transaction  */
        QString _hash = "";
};

};

