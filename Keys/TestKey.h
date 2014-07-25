/* 
 * File:   TestKey.h
 * Author: drsobik
 *
 * Created on December 21, 2010, 3:32 PM
 */

#ifndef TESTKEY_H
#define	TESTKEY_H

#include "AKey.h"

using namespace Common;

class TestKey: public AKey {
public:
    int _key;

    TestKey();
    virtual ~TestKey();

    virtual void copy(const AComparable &other);

    virtual bool equals(const AComparable &other) const;
    virtual bool less(const AComparable &other) const;

private:

};

#endif	/* TESTKEY_H */

