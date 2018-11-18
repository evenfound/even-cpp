/**
 * @file    Transaction.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on October 31, 2018, 06:49 PM
 */

#include "Transaction.hxx"
#include "Logger.hxx"

#include <QCryptographicHash>
#include <QTextCodec>
#include <QFile>
#include <QDataStream>
#include <QJsonObject>

using namespace even;

//------------------------------------------------------------------------------
Transaction::Transaction()
    : Config({})
    , _body(1248, '\x0')
{
    _hash.create();
    INFO(20) << QString("Create new transaction %1...").arg(_hash.serialize());
}

//------------------------------------------------------------------------------
Transaction::~Transaction() {
    INFO(20) << QString("Success destroy transaction %1..")
                .arg(_hash.serialize());

}

//------------------------------------------------------------------------------
bool Transaction::ipfsLoad(QString fileName_) {
    QFile file(fileName_);
    if(!file.open(QIODevice::ReadOnly)) {
        _errors << "Error opening file transaction " << fileName_;
        return false;
    }
    _body = file.readAll();
    _bodyReadHash();
    _unpackBody();
    return true;
}

//------------------------------------------------------------------------------
void Transaction::addAddress(QString address_) {
    _address.fromString(address_);
}

//------------------------------------------------------------------------------
void Transaction::_bodyReadHash() {
    QDataStream stream(&_body, QIODevice::ReadOnly);
    QByteArray buffer(Hash::hashByteLength, Qt::Uninitialized);
    stream.readRawData(buffer.data(), Hash::hashByteLength);
    _hash.fromBinary(buffer);
}

//------------------------------------------------------------------------------
void Transaction::_unpackBody() {
    QDataStream stream(&_body, QIODevice::ReadOnly);
    QByteArray buffer;
    stream.skipRawData(32);
    buffer.resize(1024);
    stream.readRawData(buffer.data(), 1024);
    _signatureMessageFragment = QString(buffer);
    _address.binary().resize(32);
    stream.readRawData(_address.binary().data(), 32);
    buffer.resize(24);
    stream.writeRawData(buffer.data(), 24);
    _tag = QString(buffer);
    stream.readRawData((char*)&_value, sizeof(_value));
    stream.readRawData((char*)&_timestamp, sizeof(_timestamp));
    stream.readRawData((char*)&_currentIndex, sizeof(_currentIndex));
    stream.readRawData((char*)&_lastIndex, sizeof(_lastIndex));
    _messageHash.binary().resize(32);
    stream.readRawData(_messageHash.binary().data(), 32);
    _trunkHash.binary().resize(32);
    stream.readRawData(_trunkHash.binary().data(), 32);
    _branchHash.binary().resize(32);
    stream.readRawData(_branchHash.binary().data(), 32);
    buffer.resize(24);
    stream.writeRawData(buffer.data(), 24);
    _nonce = QString(buffer);
}

//------------------------------------------------------------------------------
void Transaction::_packBody() {
    _body.fill('0');
    QDataStream stream(&_body, QIODevice::WriteOnly);
    stream.writeRawData(_hash.binary().data(), 32);
    _signatureMessageFragment.resize(1024);
    _signatureMessageFragment.fill('0');
    stream.writeRawData(_signatureMessageFragment.toLatin1().data(), 1024);
    stream.writeRawData(_address.binary().data(), 32);
    stream.writeRawData(_tag.toLower().toLatin1().data(), 24);
    stream.writeRawData((char*)&_value, sizeof(_value));
    stream.writeRawData((char*)&_timestamp, sizeof(_timestamp));
    stream.writeRawData((char*)&_currentIndex, sizeof(_currentIndex));
    stream.writeRawData((char*)&_lastIndex, sizeof(_lastIndex));
    stream.writeRawData(_messageHash.binary().data(), 32);
    stream.writeRawData(_trunkHash.binary().data(), 32);
    stream.writeRawData(_branchHash.binary().data(), 32);
    stream.writeRawData(_nonce.toLower().toLatin1().data(), 24);
//    INFO(15) << "Pack Body: " << QString(_body.toHex()).toUpper() << ", address " << _address.serialize();
}

//------------------------------------------------------------------------------
bool Transaction::ipfsFlush(QString filePath_) {
    QFile file(filePath_ + "/" + _hash.serialize());
    if(!file.open(QIODevice::WriteOnly|QIODevice::NewOnly)) {
        _errors << "Error create file transaction " << filePath_ + "/" + _hash.serialize();
        return false;
    }
    _packBody();
    QDataStream stream(&file);
    stream.writeRawData(_body.data(), 1248);
    return true;
}

//------------------------------------------------------------------------------
bool Transaction::checkHash_wFileName(QString fileName_) {
    bool result = (fileName_ == _hash.serialize());
    if(!result)
        _errors << "Error comapare hash and file name transaction in to " << fileName_;
    return result;
}

//------------------------------------------------------------------------------
bool Transaction::serialize(QString path_, QJsonObject& other_) {
    QJsonObject leaf;
    leaf.insert(u8"hash", _hash.serialize());
    leaf.insert(u8"signatureMessageFragment", _signatureMessageFragment);
    leaf.insert(u8"address", _address.serialize());
    leaf.insert(u8"tag", _tag);
    leaf.insert(u8"value", QString::number(_value));
    leaf.insert(u8"timestamp", QString::number(_timestamp));
    leaf.insert(u8"currentIndex", QString::number(_currentIndex));
    leaf.insert(u8"lastIndex", QString::number(_lastIndex));
    leaf.insert(u8"message", _messageHash.serialize());
    leaf.insert(u8"trunkTransaction", _trunkHash.serialize());
    leaf.insert(u8"branchTransaction", _branchHash.serialize());
    leaf.insert(u8"nonce", _nonce);
    leaf.insert(u8"persistence", _persistence);
    leaf.insert(u8"body", QString(_body.toHex()).toUpper());
    other_.insert(path_, leaf);
    return true;
}
