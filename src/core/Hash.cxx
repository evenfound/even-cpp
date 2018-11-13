/**
 * @file    Hash.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 13, 2018, 04:32 PM
 */

#include "Hash.hxx"
#include "Logger.hxx"

#include <QCryptographicHash>
#include <QTextCodec>

using namespace even;

//------------------------------------------------------------------------------
Hash::Hash()
    : _byteHash(QCryptographicHash::hash(QByteArray(QString("EVEN-0x%1")
                                                    .arg((quintptr)this, QT_POINTER_SIZE * 2, 16, QChar('0')).toLatin1())
                                         , QCryptographicHash::Keccak_256))
{
}

//------------------------------------------------------------------------------
QString Hash::serialize() {
    if(!_hash.isEmpty())
        return _hash;
    _hash = QString(_byteHash.toHex()).toUpper();
    INFO(15) << QString("Create new hash %1...").arg(_hash);
    return _hash;
}
