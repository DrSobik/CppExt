/* 
 * File:   AData.h
 * Author: drsobik
 *
 * Created on December 21, 2010, 4:33 PM
 *
 * Description: AData is a virtual class that is used as the base class for any
 *              data types.
 *
 * Mathods to overload:
 *              init - initialization;
 *              copy - copy other data;
 *
 */

#ifndef ADATA_H
#define	ADATA_H

#include <iostream>

#include "DebugExt.h"

using namespace std;

namespace Common {

    class AData {
    public:
        virtual ~AData();

        /** Initialize the key. */
        virtual void init();

        /** Copy the key. */
        virtual void copy(const AData &other);

        /** Read data from the stream. */
        virtual void read(const ostream &stream);

        /** Write data to the  stream. */
        virtual void write(ostream &stream);

    };

}

#endif	/* ADATA_H */

