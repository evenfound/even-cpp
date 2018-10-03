/**
 * @file    Node.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 29, 2018, 7:49 PM
 */

#pragma once

#include <initializer_list>
#include <QObject>
#include <QThread>
#include "Config.hxx"

namespace even {

class Node : public QObject, public Config {
        Q_OBJECT
    public:
        /** @brief System node count in system created. */
        static long nodeCount;

        /** @brief Create Node entity with config_ parameters list */
        Node(std::initializer_list<Value> config_);

        ~Node() override;

        /** @brief Assign operator - nocopyable */
        Node& operator=(const Node& node_) = delete;

        /** @brief Copy constructor - nocopyable */
        Node(const Node& orig) = delete;

        /** @brief Default constructor deprecated */
        Node() = delete;

    public slots:
        /** @brief Accept signal about start threading job. */
        void doWork(const QString &message_);

    signals:
        /** @brief Signal acceptors about that threading job is finished. */
        void resultReady(const QString &);

    private:
        /** @brief Links to Nodes, developing triangle with
         * us in Network topology
         */
        Node *_left, *_right;
};
};

