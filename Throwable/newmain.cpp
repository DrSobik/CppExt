/* 
 * File:   newmain.cpp
 * Author: drsobik
 *
 * Created on January 11, 2011, 2:18 PM
 */

#include <cstdlib>
#include <iostream>

using namespace std;

#include "AThrowable.h"

using namespace Common;

class TestError : public AThrowable {
public:

    TestError() {

    }

    virtual void msg(ostream& stream = cout) {
        stream << "Simple arror test" << endl;
    }
};

void testfunction() {
    cout << "Throwing the Error ... "<<endl;

    throw TestError();
}

void testfunction1() {
    testfunction();
}

int main(int argc, char** argv) {

    try {

        testfunction1();

    } catch (TestError & err) {
        cout<< "An error has occured: "<<endl;
        err.msg();
    }

    return 0;
}

