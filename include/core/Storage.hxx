/**
 * @file    Storage.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on October 30, 2018, 12:05 AM
 */

#pragma once

#include "Config.hxx"

#include <QHash>
#include <QPair>


namespace even {

/** @brief Entitity of storage handler */
class Storage {
    public:
        Storage(std::initializer_list<QPair<QString, QString>> dirPaths_);

        /** @brief Check creation and create service directories */
        void checkDirectories();

    private:
        QHash<QString, QString> _dirPaths; ///< @brief Hash list of the directory paths
};

};

