/* 
 * File:   SmartPointer.h
 * Author: DrSobik
 *
 * Created on July 21, 2014, 11:03 PM
 */

#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Operationable"
#include "Comparable"
#include "Exceptions"
#include "MathExt"

#include <atomic>
#include <mutex>
#include <map>

//#include <set>

using namespace Common;
using namespace Common::Interfaces;
using namespace Common::Exceptions;

namespace Common {

    namespace SmartPointers {

	/**********************************************************************/

	class BasicSmartPointer : public Object<> {
	private:

	public:

	protected:

	    BasicSmartPointer() : BasicObject(), Object() {
	    }

	    BasicSmartPointer(const BasicSmartPointer& other) : BasicObject(other), Object(other) {
	    };

	    virtual ~BasicSmartPointer() {
	    }

	};

	/**********************************************************************/

	/**********************************************************************/

	template<class T> class SmartPointer : public BasicSmartPointer, public PtrDereferenciable<T>, public ComparableEqTo<BasicSmartPointer> {
	private:

	    std::atomic<T*> ptr; // A pointer to the object
	    static std::map<T*, Math::uintUNI> ptrCtrMap;

	    std::mutex ptrLocker;

	    virtual SmartPointer<T>& operator=(const SmartPointer<T>&) {
		return *this;
	    } // Hide the assignment operator

	    // Can be problematic in view of thread safety
	    //static std::set<T*> registeredAddresses; // Existing pointers

	    //static void registerPointer(T* somePtr){
	    //	registeredAddresses.insert(somePtr);
	    //}

	    //static void deregisterPointer(T* somePtr){
	    //	registeredAddresses.erase(somePtr);
	    //}

	protected:

	    void deletePtr(T* ptr) {

		if (ptr != nullptr) {

		    --ptrCtrMap[ptr];

		    if (ptrCtrMap[ptr] == 0) {

			ptrCtrMap.erase(ptr); // Clean-up
			//deregisterPointer(ptr);
			delete ptr;

		    }

		    ptr = nullptr; // If other SPs are referencing it then they'll manage the pointer

		}

	    }

	public:

	    SmartPointer() : BasicSmartPointer(), PtrDereferenciable<T>(), ComparableEqTo<BasicSmartPointer>(), ptr(nullptr) {
	    }

	    SmartPointer(const SmartPointer & orig) : BasicObject(), BasicSmartPointer(orig), PtrDereferenciable<T>(), ComparableEqTo<BasicSmartPointer>(), ptr(nullptr) {
		setPointer(orig.ptr);
	    }

	    SmartPointer(const T & obj) : BasicObject(), BasicSmartPointer(), PtrDereferenciable<T>(), ComparableEqTo<BasicSmartPointer>(), ptr(nullptr) {
		setPointer(&obj);
	    }

	    SmartPointer(const T * objPtr) : BasicObject(), BasicSmartPointer(), PtrDereferenciable<T>(), ComparableEqTo<BasicSmartPointer>(), ptr(nullptr) {
		setPointer((T*) objPtr);
	    }

	    virtual ~SmartPointer() {

		std::lock_guard<std::mutex> ptrGuard(ptrLocker);

		deletePtr(ptr);

	    }

	    //virtual T& operator*() {

	    //	if (ptr == NULL) throw ErrMsgException<Message<>>("SmartPointer::operator*() : Trying to dereference a NULL pointer!!!", this);

	    //	return *ptr;
	    //}

	    virtual T* operator->() {

		if (ptr == (T*) nullptr) throw ErrMsgException<Message < string >> (string("SmartPointer::operator->() : Trying to dereference a NULL pointer!!!"), this);

		return ptr;
	    }

	    virtual const T* operator->() const {

		if (ptr == (T*) nullptr) throw ErrMsgException<Message < string >> (string("SmartPointer::operator->() : Trying to dereference a NULL pointer!!!"), (BasicSmartPointer*) this);

		return ptr;
	    }

	    virtual bool operator==(const BasicSmartPointer & other) {
		return (T*) ptr == (T*) ((SmartPointer&) other).ptr;
	    }

	    virtual void setPointer(const T* somePtr, const bool& deleteCurrent = false) {

		//if (somePtr != NULL && SmartPointer::registeredAddresses.count((T*)somePtr) > 0){
		//	throw ErrMsgException<>("SmartPointer::setPointer : There is already a SmartPointer assigned to the given address!!!", this);
		//}

		//if (somePtr != NULL && SmartPointer::registeredAddresses.count((T*)somePtr) == 0){
		//	registerPointer((T*)ptr);
		//}

		std::lock_guard<std::mutex> ptrGuard(ptrLocker);

		if (ptr != somePtr) { // Otherwise, do nothing

		    // Delete the current pointer is not null
		    if (deleteCurrent && ptr != (T*) nullptr) {

			deletePtr(ptr);

			ptr = (T*) nullptr;

		    }

		    // Set the new pointer
		    ptr = (T*) somePtr;
		    if (ptrCtrMap.count(ptr) == 0) {
			ptrCtrMap[ptr] = 1;
		    } else {
			++ptrCtrMap[ptr];
		    }



		} // Not the same pointer

	    }

	    virtual T * getPointer() const {
		return ptr;
	    }

	    virtual bool valid() const {
		return ptr != (T*) nullptr;
	    }

	private:

	};

	//template<class T> std::set<T*> SmartPointer<T>::registeredAddresses;
	template<class T> std::map<T*, Math::uintUNI> SmartPointer<T>::ptrCtrMap;

	/**********************************************************************/

    }

}
#endif /* SMARTPOINTER_H */

