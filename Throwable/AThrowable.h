/* 
 * File:   AThrowable.h
 * Author: drsobik
 *
 * Created on January 11, 2011, 2:05 PM
 *
 * Description: AThrowable class is the base class for all objects that can be
 *              thrown from the methods.
 *
 */

#ifndef ATHROWABLE_H
#define	ATHROWABLE_H

#include <iostream>

//#include "Debug.h"
#include "DebugExt.h"

using namespace std;

namespace Common {

    class AThrowable {
    public:
        virtual ~AThrowable();

        /** Output the description of the throwable. */
        virtual void msg(ostream& stream = cout);
    };

}

#endif	/* ATHROWABLE_H */

