/**
 * @file    Account.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 13, 2018, 03:06 PM
 */

#include "Account.hxx"
#include "Logger.hxx"

#include <QCryptographicHash>
#include <QTextCodec>

using namespace even;

//------------------------------------------------------------------------------
Account::Account(const Hash& parent_)
    : _hash()
    , _parent(parent_)
{
    _hash.create();
    INFO(20) << QString("Create new account %1...").arg(_hash.serialize());
}
