/* 
 * File:   SmartPointer.h
 * Author: DrSobik
 *
 * Created on July 21, 2014, 11:03 PM
 */

#ifndef SMARTPOINTER_H
#define	SMARTPOINTER_H

#include "Operationable"
#include "Exceptions"

#include <set>

using namespace Common::Interfaces;
using namespace Common::Exceptions;

namespace Common {

	namespace SmartPointers {

		/**********************************************************************/
		
		class BasicSmartPointer : public Object<> {
		private:
			
		public:	
			
		protected:
			
			BasicSmartPointer() : BasicObject(), Object(){}
			BasicSmartPointer(const BasicSmartPointer& other) : BasicObject(other), Object(other){};
			virtual ~BasicSmartPointer(){}
			
		};
		
		/**********************************************************************/
		
		/**********************************************************************/
		
		template<class T> class SmartPointer : public BasicSmartPointer, public PtrDereferenciable<T>, public ComparableEqTo<BasicSmartPointer> {
		private:

			T* ptr; // A pointer to the object

			virtual SmartPointer<T>& operator=(const SmartPointer<T>&){return *this;} // Hide the assignment operator
			
			// Can be problematic in view of thread safety
			//static std::set<T*> registeredAddresses; // Existing pointers

			//static void registerPointer(T* somePtr){
			//	registeredAddresses.insert(somePtr);
			//}
			
			//static void deregisterPointer(T* somePtr){
			//	registeredAddresses.erase(somePtr);
			//}
			
		public:

			SmartPointer() : BasicSmartPointer(), PtrDereferenciable<T>(), ComparableEqTo<BasicSmartPointer>(), ptr(NULL) {
			}

			SmartPointer(const SmartPointer& orig) : BasicSmartPointer(orig), PtrDereferenciable<T>(), ComparableEqTo<BasicSmartPointer>(), ptr(NULL) {
				setPointer(orig.ptr);
			}

			SmartPointer(const T& obj) : BasicSmartPointer(), PtrDereferenciable<T>(), ComparableEqTo<BasicSmartPointer>(), ptr(NULL){
				setPointer(&obj);
			}
			
			SmartPointer(const T* objPtr) : BasicSmartPointer(), PtrDereferenciable<T>(), ComparableEqTo<BasicSmartPointer>(), ptr(NULL){
				setPointer((T*)objPtr);
			}
			
			virtual ~SmartPointer() {
				
				if (ptr != NULL) {
					//deregisterPointer(ptr);
					delete ptr;
					ptr = NULL;
				}
				
			}
			
			//virtual T& operator*() {
				
			//	if (ptr == NULL) throw ErrMsgException<Message<>>("SmartPointer::operator*() : Trying to dereference a NULL pointer!!!", this);
				
			//	return *ptr;
			//}
			
			virtual T* operator->(){
				
				if (ptr == NULL) throw ErrMsgException<Message<string>>(string("SmartPointer::operator->() : Trying to dereference a NULL pointer!!!"), this);
				
				return ptr;
			}
			
			virtual bool operator==(const BasicSmartPointer& other) {
				return ptr == ((SmartPointer&)other).ptr;
			}

			
			virtual void setPointer(const T* somePtr, const bool& deleteCurrent = false) {
				
				//if (somePtr != NULL && SmartPointer::registeredAddresses.count((T*)somePtr) > 0){
				//	throw ErrMsgException<>("SmartPointer::setPointer : There is already a SmartPointer assigned to the given address!!!", this);
				//}
				
				//if (somePtr != NULL && SmartPointer::registeredAddresses.count((T*)somePtr) == 0){
				//	registerPointer((T*)ptr);
				//}
				
				if (deleteCurrent && ptr != somePtr && ptr != NULL){
					delete ptr;
					ptr = NULL;
				}
				
				ptr = (T*)somePtr;
			}

			virtual T* getPointer() {
				return ptr;
			}

		private:

		};
		
		//template<class T> std::set<T*> SmartPointer<T>::registeredAddresses;
		
		/**********************************************************************/

	}

}
#endif	/* SMARTPOINTER_H */

