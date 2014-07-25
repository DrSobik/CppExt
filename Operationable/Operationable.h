/* 
 * File:   Operationable.h
 * Author: DrSobik
 *
 * Created on July 19, 2014, 4:31 PM
 */

#ifndef OPERATIONABLE_H
#define	OPERATIONABLE_H

namespace Common {

	namespace Interfaces {

		/**********************************************************************/
		
		// Base interface for all operationable interfaces
		class Operationable {

		private:

			/** We do not need a copy constructor for the interface. */
			Operationable(const Operationable&) {}

		protected:

			Operationable() {}

			virtual ~Operationable() {}
			
		};
		
		/**********************************************************************/
		
		/**********************************************************************/

		template<class T> class Addible : public Operationable {
		public:	
			
			virtual T& operator+=(const T&) = 0;
			
			friend T operator+(const T& left, const T& right){
				
				T res(left);
				
				return res+= right;
				
			}
			
		protected:
			
			Addible(){}
			
			virtual ~Addible(){}
			
		private:

			Addible(const Addible& orig){}
			
		};
		
		/**********************************************************************/

		/**********************************************************************/

		template<class T> class Subtractable : public Operationable {
		public:	
			
			virtual T& operator-=(const T&) = 0;
			
			friend T operator-(const T& left, const T& right){
				
				T res(left);
				
				return res-= right;
				
			}
			
		protected:
			
			Subtractable(){}
			
			virtual ~Subtractable(){}
			
		private:

			Subtractable(const Subtractable& orig){}
			
		};
		
		/**********************************************************************/
		
		/**********************************************************************/

		template<class T> class Multipliable : public Operationable {
		public:	
			
			virtual T& operator*=(const T&) = 0;
			
			friend T operator*(const T& left, const T& right){
				
				T res(left);
				
				return res*= right;
				
			}
			
		protected:
			
			Multipliable(){}
			
			virtual ~Multipliable(){}
			
		private:

			Multipliable(const Multipliable& orig){}
			
		};
		
		/**********************************************************************/
		
		/**********************************************************************/

		template<class T> class Divisible : public Operationable {
		public:	
			
			virtual T& operator/=(const T&) = 0;
			
			friend T operator/(const T& left, const T& right){
				
				T res(left);
				
				return res/= right;
				
			}
			
		protected:
			
			Divisible(){}
			
			virtual ~Divisible(){}
			
		private:

			Divisible(const Divisible& orig){}
			
		};
		
		/**********************************************************************/
		
		/**********************************************************************/

		template<class T> class Modable : public Operationable {
		public:	
			
			virtual T& operator%=(const T&) = 0;
			
			friend T operator%(const T& left, const T& right){
				
				T res(left);
				
				return res%= right;
				
			}
			
		protected:
			
			Modable(){}
			
			virtual ~Modable(){}
			
		private:

			Modable(const Modable& orig){}
			
		};
		
		/**********************************************************************/
		
		/**********************************************************************/

		template<class T> class ANDable : public Operationable {
		public:	
			
			virtual T& operator&=(const T&) = 0;
			
			friend T operator&(const T& left, const T& right){
				
				T res(left);
				
				return res&= right;
				
			}
			
		protected:
			
			ANDable(){}
			
			virtual ~ANDable(){}
			
		private:

			ANDable(const ANDable& orig){}
			
		};
		
		/**********************************************************************/
		
		/**********************************************************************/

		template<class T> class ORable : public Operationable {
		public:	
			
			virtual T& operator|=(const T&) = 0;
			
			friend T operator|(const T& left, const T& right){
				
				T res(left);
				
				return res|= right;
				
			}
			
		protected:
			
			ORable(){}
			
			virtual ~ORable(){}
			
		private:

			ORable(const ORable& orig){}
			
		};
		
		/**********************************************************************/
		
		/**********************************************************************/

		template<class T> class XORable : public Operationable {
		public:	
			
			virtual T& operator^=(const T&) = 0;
			
			friend T operator^(const T& left, const T& right){
				
				T res(left);
				
				return res^= right;
				
			}
			
		protected:
			
			XORable(){}
			
			virtual ~XORable(){}
			
		private:

			XORable(const XORable& orig){}
			
		};
		
		/**********************************************************************/		
		
		/**********************************************************************/

		template<class T> class Inversible : public Operationable {
		public:	
			
			virtual T inv() = 0; // Override to inverse an element
			
		protected:
			
			Inversible(){}
			
			virtual ~Inversible(){}
			
		private:

			Inversible(const Inversible& orig){}
			
		};
		
		/**********************************************************************/
		
		/**********************************************************************/
	
		template<class T> class Dereferenciable : public Operationable {
		public:

			virtual T& operator*() = 0; // Dereferences a pointer

		private:

			/** We do not need a copy constructor for the interface. */
			Dereferenciable(const Dereferenciable&) {}

		protected:

			Dereferenciable() {}

			virtual ~Dereferenciable() {}

		};
		
		/**********************************************************************/
		
		/**********************************************************************/
	
		template<class T> class PtrDereferenciable : public Operationable {
		public:

			virtual T* operator->() = 0; // Return a raw pointer

		private:

			/** We do not need a copy constructor for the interface. */
			PtrDereferenciable(const PtrDereferenciable&) {}

		protected:

			PtrDereferenciable() {}

			virtual ~PtrDereferenciable() {}

		};
		
		/**********************************************************************/
		
		/**********************************************************************/
	
		template<class T> class Plusable : public Operationable {
		public:

			virtual T operator+() = 0;

		private:

			/** We do not need a copy constructor for the interface. */
			Plusable(const Plusable&) {}

		protected:

			Plusable() {}

			virtual ~Plusable() {}

		};
		
		/**********************************************************************/
		
		/**********************************************************************/
	
		template<class T> class Negatible : public Operationable {
		public:

			virtual T operator-() = 0;

		private:

			/** We do not need a copy constructor for the interface. */
			Negatible(const Negatible&) {}

		protected:

			Negatible() {}

			virtual ~Negatible() {}

		};
		
		/**********************************************************************/
		
		/**********************************************************************/
	
		template<class T> class LogicalNegatible : public Operationable {
		public:

			virtual T operator!() = 0;

		private:

			/** We do not need a copy constructor for the interface. */
			LogicalNegatible(const LogicalNegatible&) {}

		protected:

			LogicalNegatible() {}

			virtual ~LogicalNegatible() {}

		};
		
		/**********************************************************************/
		
		/**********************************************************************/
	
		template<class T> class Complementable : public Operationable {
		public:

			virtual T operator~() = 0;

		private:

			/** We do not need a copy constructor for the interface. */
			Complementable(const Complementable&) {}

		protected:

			Complementable() {}

			virtual ~Complementable() {}

		};
		
		/**********************************************************************/
		
		/**********************************************************************/
	
		template<class T> class Addressable : public Operationable {
		public:

			virtual T operator&() = 0;

		private:

			/** We do not need a copy constructor for the interface. */
			Addressable(const Addressable&) {}

		protected:

			Addressable() {}

			virtual ~Addressable() {}

		};
		
		/**********************************************************************/
		
		/**********************************************************************/
	
		template<class T> class PreIncrementable : public Operationable {
		public:

			virtual T& operator++() = 0;

		private:

			/** We do not need a copy constructor for the interface. */
			PreIncrementable(const PreIncrementable&) {}

		protected:

			PreIncrementable() {}

			virtual ~PreIncrementable() {}

		};
		
		/**********************************************************************/
		
		/**********************************************************************/
	
		// WARNING! Return by type or void and NOT by T&, unless you know what you are doing
		template<class T=void> class PostIncrementable : public Operationable {
		public:

			virtual T operator++(const PostIncrementable&) = 0;

		private:

			/** We do not need a copy constructor for the interface. */
			PostIncrementable(const PostIncrementable&) {}

		protected:

			PostIncrementable() {}

			virtual ~PostIncrementable() {}

		};
		
		/**********************************************************************/
		
		/**********************************************************************/
	
		template<class T> class PreDecrementable : public Operationable {
		public:

			virtual T& operator--() = 0;

		private:

			/** We do not need a copy constructor for the interface. */
			PreDecrementable(const PreDecrementable&) {}

		protected:

			PreDecrementable() {}

			virtual ~PreDecrementable() {}

		};
		
		/**********************************************************************/
		
		/**********************************************************************/
	
		// WARNING! Return by type or void and NOT by T&, unless you know what you are doing
		template<class T=void> class PostDecrementable : public Operationable {
		public:

			virtual T operator--(const PostDecrementable&) = 0;

		private:

			/** We do not need a copy constructor for the interface. */
			PostDecrementable(const PostDecrementable&) {}

		protected:

			PostDecrementable() {}

			virtual ~PostDecrementable() {}

		};
		
		/**********************************************************************/
		
	}
	
}

#endif	/* OPERATIONABLE_H */

