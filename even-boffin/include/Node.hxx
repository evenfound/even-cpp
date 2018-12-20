/**
 * @file    Node.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 29, 2018, 7:49 PM
 */

#pragma once

#include "Config.hxx"
#include "Wallet.hxx"

#include <initializer_list>
#include <QObject>
#include <QThread>

namespace even {

class Node : public QObject, public Config {
        Q_OBJECT
    public:
        /** @brief System node count in system created. */
        static int nodeCount;

        /** @brief Create Node entity with config_ parameters list */
        Node(std::initializer_list<Value> config_);

        ~Node() override;

        /** @brief Assign operator - nocopyable */
        Node& operator=(const Node& node_) = delete;

        /** @brief Copy constructor - nocopyable */
        Node(const Node& orig) = delete;

        /** @brief Default constructor deprecated */
        Node() = delete;

        /** @brief Return Hash reference */
        inline Hash &hash() { return _hash; }

        /** @brief Return values in json array packed by path_ set */
        bool serialize(QString path_, QJsonObject& other_) override;

        /** @brief Got a node wallet reference */
        Wallet &wallet() { return _wallet; }

    public slots:
        /** @brief Accept signal about start threading job. */
        void doWork(const QString &message_);

    signals:
        /** @brief Signal acceptors about that threading job is finished. */
        void resultReady(const QString &);

    private:
        Node *_left, *_right;   ///< @brief Links to Nodes, developing triangle with
                                ///< us in Network topology
        Wallet _wallet;         ///< Node Wallet object
        Hash _hash;             ///< Node hash
};
};

