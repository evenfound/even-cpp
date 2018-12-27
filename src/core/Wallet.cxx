/**
 * @file    Wallet.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 31, 2018, 06:10 PM
 */

#include "Wallet.hxx"
#include "Transaction.hxx"
#include "Logger.hxx"
#include "Random.hxx"

#include <QDir>

using namespace even;

//------------------------------------------------------------------------------
void Wallet::initialize(const Hash &parent_, const QString& path_) {
    _parent = parent_;
    _path = path_ +  "/" + _parent.serialize();
    _accounts.clear();
    _accounts.append(Account(_parent));
}

//------------------------------------------------------------------------------
bool Wallet::send(QString hash_, int value_) {
    _errors.clear();
    if(_path.isEmpty()) {
        _errors << "The path of wallet is not initialized..";
        return false;
    }
    Transaction newTransaction;
    newTransaction.addAddress(hash_);
    newTransaction.setValue(value_);
    if(!newTransaction.ipfsFlush(_path + u8"/outbox")) {
        _errors << newTransaction.errors();
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------
QString Wallet::accountRandomAddress() {
    if(_accounts.count()) {
        uint choice = Random::get(0, _accounts.count() - 1);
        return _accounts[choice].hash().serialize();
    }
    return  {};
}
