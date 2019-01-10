/**
 * @file    Hash.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 13, 2018, 04:32 PM
 */

#include "Hash.hxx"
#include "Logger.hxx"
#include "Random.hxx"

#include <QCryptographicHash>
#include <QTextCodec>
#include <QTime>

using namespace even;

uint Hash::hashByteLength = 32;

//------------------------------------------------------------------------------
Hash::Hash()
{
}

//------------------------------------------------------------------------------
void Hash::create()
{
    QString seed = QString("EVEN%1%2")
            .arg(QTime::currentTime().msec())
            .arg(Random::get(0, (int)1e12));
    INFO(20) << seed;
    _byteHash = QCryptographicHash::hash(QByteArray(seed.toLatin1())
                                         , QCryptographicHash::Keccak_256);
    INFO(20) << QString("Create new hash %1...").arg(serialize());
}

//------------------------------------------------------------------------------
QString Hash::serialize() {
    if(!_hash.isEmpty())
        return _hash;
    _hash = QString(_byteHash.toHex()).toUpper();
    return _hash;
}

//------------------------------------------------------------------------------
void Hash::fromBinary(const QByteArray& bytes_) {
    _byteHash = bytes_;
    _hash = "";
    serialize();
}

//------------------------------------------------------------------------------
void Hash::fromString(const QString& string_) {
    _byteHash = QByteArray::fromHex(string_.toLower().toLatin1());
    _hash = string_;
}



