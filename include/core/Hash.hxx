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

        /** @brief Hash binary byte length */
        static uint hashByteLength;

        Hash();
        ~Hash() = default;

        /** @brief genegate hash self. */
        void create();

        /** @brief  Convert hash to readable */
        QString serialize();

        /** @brief  Get binary hash */
        inline QByteArray &binary() { return _byteHash; }

        /** @brief Init from binary */
        void fromBinary(const QByteArray& bytes_);

        /** @brief Init from string */
        void fromString(const QString& string_);

    private:
        /** @brief  ByteArray unique hash of this transaction  */
        QByteArray _byteHash;

        /** @brief  String unique hash of this transaction  */
        QString _hash="";
};

};

