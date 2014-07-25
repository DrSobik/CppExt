/* 
 * File:   Assignable.h
 * Author: DrSobik
 *
 * Created on July 15, 2014, 7:59 PM
 * 
 * Description : Class Assignable defines an interface of any object that can be assigned. Defines a pure virtual = method.
 * 
 */

#ifndef ASSIGNABLE_H
#define	ASSIGNABLE_H

namespace Common {

	namespace Interfaces {
		
		/**********************************************************************/
		
		template<class T> class AssignableFrom {
		public:
			
			virtual AssignableFrom& operator=(const T&) = 0;
			
		private:
			
			/** We do not need a copy constructor for the interface. */
			AssignableFrom(const AssignableFrom&){}
			
		protected:
			AssignableFrom(){}
			
			virtual ~AssignableFrom(){}
		};
		
		/**********************************************************************/
		
		/**********************************************************************/
		
		template<class T> class NonAssignableFrom {
		public:

			virtual NonAssignableFrom& operator=(const T&) = delete;
			virtual NonAssignableFrom& operator=(T&) = delete;
			virtual NonAssignableFrom& operator=(T) = delete;
			
		private:
			
			/** We do not need a copy constructor for the interface. */
			NonAssignableFrom(const NonAssignableFrom&) = delete;
			
			//virtual NonAssignableFrom& operator=(const T&) {};
			//virtual NonAssignableFrom& operator=(T&) {};
			//virtual NonAssignableFrom& operator=(T) {};
			
		protected:
			NonAssignableFrom(){}
			
			virtual ~NonAssignableFrom(){}
		};
		
		/**********************************************************************/
		
	//	/**********************************************************************/
	//	
	//	class Assignable : public AssignableFrom<const Object<>&> {
	//	public:
	//
	//		// = is inherited
	//		
	//	private:
	//		
	//		/** We do not need a copy constructor for the interface. */
	//		Assignable(const Assignable&) : AssignableFrom<const Object<>&>(){}
	//		
	//	protected:
	//		Assignable(){}
	//		
	//		virtual ~Assignable(){}
	//	};
	//	
	//	/**********************************************************************/
	//	
	//	/**********************************************************************/
	//	
	//	class NonAssignable : public NonAssignableFrom<Object<>> {
	//	public:
	//		
	//		virtual NonAssignable& operator=(const Object<>&) = delete;
	//		virtual NonAssignable& operator=(Object<>&) = delete;
	//		virtual NonAssignable& operator=(Object<>) = delete;
	//		
	//	private:
	//		
	//		/** We do not need a copy constructor for the interface. */
	//		NonAssignable(const NonAssignable&) = delete;
	//		
	//	protected:
	//		NonAssignable(){}
	//		
	//		virtual ~NonAssignable(){}
	//	};
	//	
	//	/**********************************************************************/
		
	}
}

#endif	/* ASSIGNABLE_H */

