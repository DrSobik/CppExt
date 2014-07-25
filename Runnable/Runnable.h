/* 
 * File:   Runnable.h
 * Author: DrSobik
 *
 * Created on July 15, 2014, 7:46 PM
 * 
 * Description : Class Runnable defines an interface of any object that can be run. Defines a pure virtual run method.
 * 
 */

#ifndef RUNNABLE_H
#define	RUNNABLE_H

#include "Object"

namespace Common {

	namespace Interfaces {

		/**********************************************************************/
		
		class Runnable {
		public:

			virtual void run() = 0;

		private:

			Runnable(const Runnable&) {}
			
		protected:

			Runnable() {}

			virtual ~Runnable() {}

		};

		/**********************************************************************/
		
		/**********************************************************************/
		
		template<class envT> class RunnableIn : public Runnable {
		private:	
			
		protected:	
			envT env; // Type of the running environment (thread) in which the runnable should be executed
			
		public:

			// run() is inherited

		private:

			RunnableIn(const RunnableIn& other) : Runnable(other) {}
			
		protected:

			RunnableIn() : Runnable() {}


			virtual ~RunnableIn() {}

		};
		
		/**********************************************************************/
		
	}

}

#endif	/* RUNNABLE_H */

