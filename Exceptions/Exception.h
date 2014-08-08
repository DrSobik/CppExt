/* 
 * File:   Exception.h
 * Author: DrSobik
 *
 * Created on July 19, 2014, 12:24 AM
 */

#ifndef EXCEPTION_H
#define	EXCEPTION_H

#include "Object"

using namespace Common;

namespace Common {

	namespace Exceptions {

		/**********************************************************************/
		
		template<class senderT = BasicObject, class baseExceptionT = std::exception, class... Ts> class Exception : public baseExceptionT, public Ts... {
		private:
			
			senderT* sender; // A pointer to the object which raised the exception
			
		public:

			Exception(senderT* sender = NULL) : Ts()..., sender(NULL) {this->sender = sender;}
			
			Exception(const Exception& orig) : Ts(orig)..., sender(NULL) {}

			virtual ~Exception() {}
			
			virtual senderT* getSender(){
				return sender;
			}
			
		private:

		};

		/**********************************************************************/

		/**********************************************************************/
		
		class InfoException : public Exception<> {
		public:

			virtual ~InfoException() {}
			
		private:

		};

		/**********************************************************************/
		
		/**********************************************************************/
		
		class WarnException : public Exception<> {
		public:

			virtual ~WarnException() {}
			
		private:

		};

		/**********************************************************************/
		
		/**********************************************************************/
		
		class ErrException : public Exception<> {
		public:

			virtual ~ErrException() {}
			
		private:

		};

		/**********************************************************************/
		
	}

}

#endif	/* EXCEPTION_H */

