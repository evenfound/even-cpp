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
#include <QBuffer>
#include <QIODevice>

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
    if(!file.open(QIODevice::OpenModeFlag::ReadOnly)) {
        _errors << "Error opening file transaction " << fileName_;
        return false;
    }
    _body = file.readAll();
    _unpackBody();
    return true;
}

//------------------------------------------------------------------------------
void Transaction::addAddress(QString address_) {
    _address.fromString(address_);
}

//------------------------------------------------------------------------------
void Transaction::_unpackHash(QDataStream& stream_, Hash& value_) {
    QVector<char> buffer(Hash::hashByteLength);
    stream_.readRawData(buffer.data(), Hash::hashByteLength);
    value_.fromBinary(QByteArray(buffer.data(), Hash::hashByteLength));
//    char* buffer = new char[Hash::hashByteLength];
//    stream_.readRawData(buffer, Hash::hashByteLength);
//    value_.fromBinary(QByteArray(buffer, Hash::hashByteLength));
//    delete[] buffer;
}

//------------------------------------------------------------------------------
void Transaction::_unpackString(QDataStream &stream_, QString &value_, uint size_) {
    char* buffer = new char[size_];
    stream_.readRawData(buffer, size_);
    value_ = QString(QByteArray(buffer, size_));
    delete[] buffer;
}

//------------------------------------------------------------------------------
void Transaction::_unpackUInt(QDataStream &stream_, uint &value_) {
    stream_.readRawData((char*)&value_, sizeof(value_));
}

//------------------------------------------------------------------------------
void Transaction::_unpackInt(QDataStream &stream_, int &value_) {
    stream_.readRawData((char*)&value_, sizeof(value_));
}

//------------------------------------------------------------------------------
void Transaction::_unpackBody() {
    QDataStream stream(&_body, QIODevice::ReadOnly);
    _unpackHash(stream, _hash);
    _unpackString(stream, _signatureMessageFragment, 1024);
    _unpackHash(stream, _address);
    _unpackString(stream, _tag, 24);
    _unpackInt(stream, _value);
    _unpackUInt(stream, _timestamp);
    _unpackInt(stream, _currentIndex);
    _unpackInt(stream, _lastIndex);
    _unpackHash(stream, _messageHash);
    _unpackHash(stream, _trunkHash);
    _unpackHash(stream, _branchHash);
    _unpackString(stream, _nonce, 24);
}

//------------------------------------------------------------------------------
void Transaction::_packBody() {
    _body.fill('0');
    QDataStream stream(&_body, QIODevice::WriteOnly);
    stream.writeRawData(_hash.binary().data()
                        , Hash::hashByteLength);
    _signatureMessageFragment.resize(1024);
    char letters[] = {'a', 'b', 'c', 'd', 'e'};
    int number = 0;
    for(int i = 0; i < 1024; ++i) {
        _signatureMessageFragment[i] = letters[number];
        number = (number == 4)? 0: number + 1;
    }
    stream.writeRawData(_signatureMessageFragment.toLatin1().data(), 1024);
    stream.writeRawData(_address.binary().data()
                        , Hash::hashByteLength);
    number = 0;
    for(int i = 0; i < 24; ++i) {
        _tag[i] = letters[number];
        number = (number == 4)? 0: number + 1;
    }
    stream.writeRawData(_tag.toLatin1().data(), 24);
    stream.writeRawData((char*)&_value, sizeof(_value));
    stream.writeRawData((char*)&_timestamp, sizeof(_timestamp));
    stream.writeRawData((char*)&_currentIndex, sizeof(_currentIndex));
    stream.writeRawData((char*)&_lastIndex, sizeof(_lastIndex));
    stream.writeRawData(_messageHash.binary().data()
                        , Hash::hashByteLength);
    stream.writeRawData(_trunkHash.binary().data()
                        , Hash::hashByteLength);
    stream.writeRawData(_branchHash.binary().data()
                        , Hash::hashByteLength);
    stream.writeRawData(_nonce.toLower().toLatin1().data(), 24);
}

//------------------------------------------------------------------------------
bool Transaction::ipfsFlush(QString filePath_) {
    QFile file(filePath_ + "/" + _hash.serialize());
    if(!file.open(QIODevice::OpenModeFlag::WriteOnly)) {
        _errors << "Error create file transaction " << filePath_ + "/" + _hash.serialize();
        return false;
    }
    _packBody();
    QDataStream stream(&file);
    stream.writeRawData(_body.data(), _body.size());
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
