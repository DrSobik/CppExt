/* 
 * File:   AComparable.h
 * Author: drsobik
 *
 * Created on December 21, 2010, 3:14 PM
 *
 * Description : AComparable represents an abstract class which is used as a basis
 *               class for any classes that can be compared.
 *
 * Methods that must be overloaded:
 *              - equals - are the objects equal?
 *              - less - is this object "smaller" than the other one?
 */

#ifndef ACOMPARABLE_H
#define	ACOMPARABLE_H

#include "Debug.h"

namespace Common {

    class AComparable {
    public:
        virtual ~AComparable();

        /** Initialize the key. */
        virtual void init();
        /** Copy the key. */
        virtual void copy(const AComparable &other);

        /** Assign other key to this. */
        virtual AComparable & operator=(const AComparable &other);

        /** Check this and the other for equality. */
        virtual bool equals(const AComparable &other) const;
        
        /** Check if this is strictly less than the other.  */
        virtual bool less(const AComparable &other) const;

        /** Check wheather this key is smaller than other. */
        friend bool operator<(const AComparable &obj1, const AComparable &obj2);

        /** Check wheather this key is greater than other. */
        friend bool operator>(const AComparable &obj1, const AComparable &obj2);

        /** Check wheather this key is equall to the other. */
        friend bool operator==(const AComparable &obj1, const AComparable &obj2);

        /** Check wheather this key is not equall to the other. */
        friend bool operator!=(const AComparable &obj1, const AComparable &obj2);

        /** Check wheather this key is smaller or equall to other. */
        friend bool operator<=(const AComparable &obj1, const AComparable &obj2);

        /** Check wheather this key is greater or equall to other. */
        friend bool operator>=(const AComparable &obj1, const AComparable &obj2);

        /** Compare this key to the other one. -1 if smaller, 0 - if equall, 1 - if
         * greater. */
        virtual int compare(const AComparable &other) const;

    };


    typedef AComparable AKey; // Keys must be comparable (at least equals or not?)
}

#endif	/* ACOMPARABLE_H */

