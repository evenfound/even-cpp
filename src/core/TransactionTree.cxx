/**
 * @file    TransactionTree.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on November 18, 2018, 00:09 AM
 */

#include "TransactionTree.hxx"
#include "Logger.hxx"

#include <QCryptographicHash>
#include <QTextCodec>
#include <QDirIterator>
#include <QDir>

using namespace even;

//------------------------------------------------------------------------------
TransactionTree::TransactionTree()
    : Config({})
{
}

//------------------------------------------------------------------------------
void TransactionTree::update(QString path_) {
    bool needClean = false;
    if(_path != path_) {
        needClean = true;
        _path = path_;
    }
    if(needClean)
        _clean();
    QDirIterator dirIt(_path
                       , QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot
                       , QDirIterator::NoIteratorFlags);
    QMap<QString, QString> dirNames;
    while(dirIt.hasNext()){
        dirIt.next();
        QString hash = dirIt.fileName(); // Node ipfs hash - as virtual dir name
        QDirIterator dirOutput(_path + "/" + hash + "/outbox"
                               , QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot
                               , QDirIterator::NoIteratorFlags);
        INFO(20) << "Look to " << _path + "/" + hash + "/outbox";
        while(dirOutput.hasNext()) {
            dirOutput.next();
            Transaction* newTransaction = new Transaction();
            if(newTransaction->ipfsLoad(dirOutput.path() + "/" + dirOutput.fileName())
                    && newTransaction->checkHash_wFileName(dirOutput.fileName())) {
                QHash<QString, QHash<QString, Transaction*>>::iterator iit = _tree.find(dirOutput.fileName());
                if(iit == _tree.end()) {
                    QHash<QString, Transaction*> newNode;
                    newNode.insert(hash, newTransaction);
                    _tree.insert(dirOutput.fileName(), newNode);
                } else {
                    iit.value().insert(hash, newTransaction);
                }
            } else {
                delete newTransaction;
            }
        }
    }
}

//------------------------------------------------------------------------------
void TransactionTree::_clean() {
    for(auto &t: _tree)
        qDeleteAll(t);
    _tree.clear();
    INFO(20) << QString("Clean transaction tree...");
}

//------------------------------------------------------------------------------
TransactionTree::~TransactionTree() {
    _clean();
}

//------------------------------------------------------------------------------
bool TransactionTree::serialize(QString, QJsonObject& other_) {
    QJsonObject branch;
//    for(auto a = _tree.begin(); a != _tree.end(); ++a) {
//        QJsonObject leaf;
//        for(auto n = a.value().begin(); n != a.value().end(); ++n) {
//            n.value()->serialize(n.key(), leaf);
//        }
//        branch.insert(a.key(), leaf);
//    }
    other_.insert(u8"shared", branch);
    return true;
}


