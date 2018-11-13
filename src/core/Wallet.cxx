/**
 * @file    Wallet.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 31, 2018, 06:10 PM
 */

#include "Wallet.hxx"

#include <QDir>

using namespace even;

//------------------------------------------------------------------------------
void Wallet::initialize(const QString& path_) {
    _path = path_;
}
