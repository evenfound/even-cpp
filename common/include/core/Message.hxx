/**
 * @file    Message.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on October 25, 2018, 6:41 PM
 */

#pragma once

#include "Transaction.hxx"

#include <QVector>

namespace even {

/** @brief Entitity of message container */
class Message {
    public:
        Message() = default;

    private:
        /** @brief Transaction bundle */
        QVector<Transaction> _transactions;

};

};

