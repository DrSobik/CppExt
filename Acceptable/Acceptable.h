/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Settings.h
 * Author: DrSobik
 *
 * Created on 29 квітня 2016, 22:11
 */

#ifndef ACCEPTABLE_H
#define ACCEPTABLE_H

#include "Changeable"
#include "Functor"
#include "Assignable"

namespace Common {

    namespace Interfaces {
	
	/**********************************************************************/

	// Base interface for all Acceptables
	template <class T> class Acceptable {
	private:
	    /** We do not need a copy constructor for the interface. */
	    Acceptable(const Acceptable&) {
	    }

	protected:
	    Acceptable() {
	    }

	public:
	    virtual ~Acceptable() {
	    }

	    virtual void accept() = 0;

	};

	/**********************************************************************/

    }

}

#endif /* ACCEPTABLE_H */

