/**
 * @file    Wallet.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 1, 2018, 06:09 PM
 */

#pragma once

#include "Account.hxx"
#include "Message.hxx"
#include "Hash.hxx"

#include <initializer_list>
#include <QString>
#include <QVector>

namespace even {

/** @brief Entitity of storage handler */
class Wallet {
    public:
        Wallet() = default;

        /** @brief Initialize accounts path */
        void initialize(const Hash& parent_, const QString& path_);

        /** @brief Create account */
        void createAccount();

        /** @brief Init array accounts */
        void initAccounts();

        /** @brief Save accounts to store */
        void saveAccounts();

        /** @brief Do send value */
        bool send(QString account_, int value_);

        /** @brief Do send message to node address from raited list. */
        bool send(QString hash_, const Message& message_);

        /** @brier Create message with transactions to account. */
        Message createMessage(QString account_, int value_);

        /** @brief Count current balance */


        /** @brief Got errors list */
        inline const QStringList &errors() const { return _errors; }

        /** @brief Got a account random hash */
        QString accountRandomAddress();

    private:
        QString _seed;              ///< Seed for creatin HD wallet accounts
        QVector<Account> _accounts; ///< Array of accounts
        QString _path="";           ///< Path to Wallet accounts
        QStringList _errors;        ///< List of error while processing
        Hash _parent;               ///< Hash parent node

};

};

