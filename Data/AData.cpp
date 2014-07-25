/* 
 * File:   AData.cpp
 * Author: drsobik
 * 
 * Created on December 21, 2010, 4:33 PM
 */

#include "AData.h"

namespace Common {

    AData::~AData() {
        Debugger::wDebug("AData::~AData() not implemented!");
    }

    void AData::init() {
        Debugger::eDebug("AData::init() not implemented!");
    }

    void AData::copy(const AData &other) {
        Debugger::eDebug("AData::copy(const AKey &other) not implemented!");
    }

    void AData::read(const ostream &stream){
        Debugger::eDebug("AData::read(const ostream &stream) not implemented!");
    }

    void AData::write(ostream &stream){
        Debugger::eDebug("AData::write(ostream &stream) not implemented!");
    }

}