/*
 * File:   main.cpp
 * Author: drsobik
 *
 * Created on December 21, 2010, 3:06 PM
 */

#include <cstdlib>

#include "TestKey.h"

using namespace std;

using namespace Common;



int main(int argc, char** argv) {

    TestKey k1;
    TestKey k2;

    k1._key = 1;

    k2._key = 2;

    if (k1 < k2) cout<<"k1 < k2"<<endl;
    if (k1 <= k2) cout<<"k1 <= k2"<<endl;
    if (k1 > k2) cout<<"k1 > k2"<<endl;
    if (k1 == k2) cout<<"k1 == k2"<<endl;
    if (k1 != k2) cout<<"k1 != k2"<<endl;

    cout<<"Equall keys"<<endl;
    k1 = k2;
    if (k1 == k2) cout<<"k1 == k2"<<endl;
    if (k1 != k2) cout<<"k1 != k2"<<endl;

    return 0;
}

