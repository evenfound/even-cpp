/**
 * @file    TemplateHolder.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on October 24, 2018, 06:33 PM
 */

//#include <logging/filelogger.h>
#include "Logger.hxx"
#include "TemplateHolder.hxx"

using namespace even;

//------------------------------------------------------------------------------
TemplateHolder::TemplateHolder(QSettings* settings_
                               , QObject* parent_)
    :TemplateCache(settings_, parent_)
    , _enable(settings_->value(u8"enable").toBool())
{}

//------------------------------------------------------------------------------
const QString& TemplateHolder::filePath() const {
    return templatePath;
}

