/**
 * @file    TemplateHolder.hxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on October 24, 2018, 06:31 PM
 */

#pragma once

#include "Config.hxx"
#include "httpserver/httprequesthandler.h"
#include "templateengine/templatecache.h"

#include <QSharedPointer>

namespace even {

using namespace stefanfrings;

class TemplateHolder : public TemplateCache {
    public:
        TemplateHolder(QSettings* settings_, QObject* parent_ = nullptr);

        /** @brief Return teplate directory file path */
        const QString& filePath() const;

        /** @brief Return caching enable flag */
        inline bool enable() const { return _enable; }

private:
        bool _enable = false;   ///< Caching enable flag

};

};
