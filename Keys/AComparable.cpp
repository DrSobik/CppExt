/* 
 * File:   AComparable.cpp
 * Author: drsobik
 * 
 * Created on December 21, 2010, 3:14 PM
 */

#include "AComparable.h"

namespace Common {

    AComparable::~AComparable() {
        Debugger::wDebug("AComparable::~AComparable() not implemented!");
    }

    void AComparable::init() {
        Debugger::eDebug("AComparable::init() not implemented!");
    }

    void AComparable::copy(const AComparable &other) {
        Debugger::eDebug("AComparable::copy(const AKey &other) not implemented!");
    }

    AComparable & AComparable::operator=(const AComparable &other) {
        copy(other);
        return *this;
    }

    bool AComparable::equals(const AComparable &other)const {
        Debugger::eDebug("AComparable::equals(const AComparable &other) not implemented!");
    }
    
    bool AComparable::less(const AComparable &other)const {
        Debugger::eDebug("AComparable::less(const AComparable &other) not implemented!");
    }

    bool operator<(const AComparable &obj1, const AComparable &obj2) {
        return obj1.less(obj2);
    }

    bool operator>(const AComparable &obj1, const AComparable &obj2) {
        return (!(obj1 < obj2)) && (obj1 != obj2);
    }

    bool operator==(const AComparable &obj1, const AComparable &obj2) {
        return obj1.equals(obj2);
    }

    bool operator!=(const AComparable &obj1, const AComparable &obj2) {
        return !(obj1 == obj2);
    }

    bool operator<=(const AComparable &obj1, const AComparable &obj2) {
        return (obj1 < obj2) || (obj1 == obj2);
    }

    bool operator>=(const AComparable &obj1, const AComparable &obj2) {
        return (!(obj1 < obj2));
    }

    int AComparable::compare(const AComparable &other) const {
        if (*this < other) {
            return -1;
        } else {
            if (*this == other) {
                return 0;
            } else {
                return 1;
            }
        }
    }

}