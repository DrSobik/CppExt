/* 
 * File:   Clonable.h
 * Author: DrSobik
 *
 * Created on July 15, 2014, 6:59 PM
 * 
 * Description : Class Clonable is a virtual class which is a base class for all classes that can be cloned. Implements only a pure virtual clone method.
 * 
 */

#ifndef CLONABLE_H
#define	CLONABLE_H

#include "Object"

namespace Common {

	namespace Interfaces {

		/**********************************************************************/
		
		/** Parameter T specifies the type of the returned value. */
		template<class T> class ClonableTo {
		
		public:

			virtual T* clone()  = 0;
			
		private:

			/** We do not need a copy constructor for the interface. */
			ClonableTo(const ClonableTo&){}
			
		protected:

			ClonableTo(){}
			
			virtual ~ClonableTo(){}

		};
		
		/**********************************************************************/
		
		/**********************************************************************/
		
		class Clonable : public ClonableTo<Clonable> {
		
		public:

			// clone() is inherited
			
		private:

			/** We do not need a copy constructor for the interface. */
			Clonable(const Clonable&) : ClonableTo() {}
			
		protected:

			Clonable(){}
			
			virtual ~Clonable(){}

		};
		
		/**********************************************************************/

	}

}
#endif	/* CLONABLE_H */

