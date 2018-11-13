/**
 * @file    Storage.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on October 30, 2018, 12:09 AM
 */

#include "Storage.hxx"

using namespace  std;
using namespace even;

//------------------------------------------------------------------------------
Storage::Storage(initializer_list<QPair<QString, QString>> dirPaths_) {
    foreach(auto dir, dirPaths_) {
        _dirPaths.insert(dir.first, dir.second);
    }
}

//------------------------------------------------------------------------------
void Storage::checkDirectories() {
//    foreach(auto d, _dirPaths) {
//        if((*d).key() == "root" && !QDir(getValue((*d).value()).toString()).exists()) {
//            QDir().mkdir(getValue((*d).value()).toString());
//        }
//        if((*d).key() == "subroot" && !QDir(getValue((*d).value()).toString()).exists())
//            QDir().mkdir(getValue((*d).value()).toString() + "/outbox");
//        }
//    }
}

//------------------------------------------------------------------------------
