/**
 * @file    TransactionTree.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 17, 2018, 11:17 PM
 */

#pragma once
#include "Transaction.hxx"
#include "Config.hxx"

#include <QString>
#include <QHash>

namespace even {

class TransactionTree;

/** @brief Entitity of transaction tree */
class TransactionTree : public Config {
    public:
        TransactionTree();
        ~TransactionTree();

        /** @brief Update all transactions tree from shared network space */
        void update(QString path_);

        /** @brief Return values in json array packed by path_ set */
        bool serialize(QString path_, QJsonObject& other_) override;

    private:
        /** @brief Tree clean */
        void _clean();

        /** @brief All shared transactions tree. The key String -
         * is the unique transaction hash, the value: key - unique
         * node (account) hash, value - transaction body */
        QHash<QString, QHash<QString, Transaction*>> _tree;

        /** @brief Path to ipfs shared root directory */
        QString _path;
};

};

