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

using namespace even;

//------------------------------------------------------------------------------
Transaction::Transaction()
    : _byteHash(QCryptographicHash::hash(QByteArray(QString("EVEN-0x%1")
                                                    .arg((quintptr)this, QT_POINTER_SIZE * 2, 16, QChar('0')).toUtf8())
                                         , QCryptographicHash::Keccak_256))
    , _hash(QTextCodec::codecForMib(1015)->toUnicode(_byteHash))
{
    INFO(15) << QString("Create new transaction %1...").arg(_hash);
}

