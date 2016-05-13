/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Changeable.h
 * Author: DrSobik
 *
 * Created on 29 квітня 2016, 22:01
 */

#ifndef CHANGEABLE_H
#define CHANGEABLE_H

namespace Common {

	namespace Interfaces {

		/**********************************************************************/

		// Base interface for all Changeables

		template <class T = void> class Changeable {
		private:

			/** We do not need a copy constructor for the interface. */
			Changeable(const Changeable&) { }

		protected:

			Changeable() { }

		public:

                        virtual ~Changeable() { }
                    
			//virtual bool changed() = 0;
			virtual bool changed() const = 0;

		};

		/**********************************************************************/

	}

}

#endif /* CHANGEABLE_H */

