/**
 * @file    Wallet.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 1, 2018, 06:09 PM
 */

#pragma once

#include "Account.hxx"

#include <initializer_list>
#include <QString>
#include <QVector>

namespace even {

/** @brief Entitity of storage handler */
class Wallet {
    public:
        Wallet() = default;

        /** @brief Initialize accounts path */
        void initialize(const QString& path_);

        /** @brief Create account */
        void createAccount();

        /** @brief Init array accounts */
        void initAccounts();

        /** @brief Save accounts to store */
        void saveAccounts();

    private:
        QString _seed;              ///< Seed for creatin HD wallet accounts
        QVector<Account> _accounts; ///< Array of accounts
        QString _path;              ///< Path to Wallet accounts

};

};

