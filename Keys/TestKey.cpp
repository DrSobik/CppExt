/* 
 * File:   TestKey.cpp
 * Author: drsobik
 * 
 * Created on December 21, 2010, 3:32 PM
 */

#include "TestKey.h"

TestKey::TestKey() {
}

TestKey::~TestKey() {
}

void TestKey::copy(const AComparable &other){
    TestKey &o= (TestKey &)other;
    _key = o._key;
}

bool TestKey::equals(const AComparable &other)const{
    TestKey &o= (TestKey &)other;
    return _key == o._key;
}

bool TestKey::less(const AComparable &other)const{
    TestKey &o= (TestKey &)other;
    return _key < o._key;
}
