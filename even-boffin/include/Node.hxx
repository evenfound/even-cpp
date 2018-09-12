/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.hxx
 * Author: zipper
 *
 * Created on August 24, 2018, 7:53 PM
 */

#ifndef NODE_HXX
#define NODE_HXX

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

        /** @brief Parametric constructor */
        Node(std::initializer_list<Value> config_);

        virtual ~Node();

    public slots:
        /** @brief Accept signal about start threading job. */
        void doWork(const QString &message_);

    signals:
        /** @brief Signal acceptors about that threading job is finished. */
        void resultReady(const QString &);

    private:
        /** @brief Assign operator - nocopyable */
        Node& operator=(const Node& node_) = delete;

        /** @brief Copy constructor - nocopyable */
        Node(const Node& orig) = delete;

        /** @brief Default constructor deprecated */
        Node() = delete;

        /** @brief Links to Nodes, developing triangle with
         * us in Network topology
         */
        Node *_left, *_right;
    };
};

#endif /* NODE_HXX */

