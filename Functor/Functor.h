/* 
 * File:   Functor.h
 * Author: DrSobik
 *
 * Created on July 15, 2014, 8:31 PM
 */

#ifndef FUNCTOR_H
#define	FUNCTOR_H

namespace Common {

	namespace Interfaces {

		/**********************************************************************/
		
		template<class resT, class... argT> class Functor {
		public:
			
			virtual resT operator()(const argT&...) = 0;
			
		private:

			/** We do not need a copy constructor for the interface. */
			Functor(const Functor&){}
			
		protected:
			
			Functor(){}
			
			virtual ~Functor(){}
			
		};

		/**********************************************************************/
		
		/**********************************************************************/
		
		template<class resT, class argT> class Subscriptable {
		public:
			
			virtual resT& operator[](const argT&) = 0; // For modifying
			
			virtual const resT& operator[](const argT&) const = 0; // Only for accessing
			
		private:

			/** We do not need a copy constructor for the interface. */
			Subscriptable(const Subscriptable&){}
			
		protected:
			
			Subscriptable(){}
			
			virtual ~Subscriptable(){}
			
		};

		/**********************************************************************/
		
	}

}

#endif	/* FUNCTOR_H */

