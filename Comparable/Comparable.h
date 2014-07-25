/* 
 * File:   Comparable.h
 * Author: DrSobik
 *
 * Created on July 15, 2014, 9:07 PM
 */

#ifndef COMPARABLE_H
#define	COMPARABLE_H

#include "Exceptions"

using namespace Common;
using namespace Common::Exceptions;

namespace Common {

	namespace Interfaces {
		
		/**********************************************************************/
		
		/** Parameter T specifies the type of objects for comparison. */
		template<class T> class ComparableTo {
		public:

			virtual bool operator==(const T&) = 0 ; // Must be overridden for == and != operations
			virtual bool operator<(const T&) = 0 ; // Must be overridden for < and > operations

			virtual bool operator!=(const T& other) final {
				return !(*this == other);
			}

			virtual bool operator<=(const T& other) final {
				return (*this < other) || (*this == other);
			}

			virtual bool operator>(const T& other) final {
				return !(*this <= other);
			}

			virtual bool operator>=(const T& other) final {
				return !(*this < other);
			}

		private:

			/** We do not need a copy constructor for the interface. */
			ComparableTo(const ComparableTo&) {}
			
		protected:

			ComparableTo() {}

			virtual ~ComparableTo() {}
		};

		/**********************************************************************/
		
		/**********************************************************************/
		
		/** Parameter T specifies the type of objects for comparison. */
		template<class T> class ComparableEqTo : private ComparableTo<T> {
		public:

			using ComparableTo<T>::operator==; // Must be overridden for == and != operations
			using ComparableTo<T>::operator!=; // Inherited from the base class but made public from private
			
		private:

			// Hide the < operator in this class
			virtual bool operator<(const T&) final {throw ErrMsgException<Message<> >("Forbidden usage of ComparableEqTo::operator<"); return false;};
			
			/** We do not need a copy constructor for the interface. */
			ComparableEqTo(const ComparableEqTo&) : ComparableTo<T>() {}
			
		protected:

			ComparableEqTo() {}

			virtual ~ComparableEqTo() {}
		};

		/**********************************************************************/
		
		/**********************************************************************/
		
		class Comparable : public ComparableTo<Comparable> {
		public:

			// Comparison operators are inherited

		private:

			/** We do not need a copy constructor for the interface. */
			Comparable(const Comparable&) : ComparableTo() {}
			
		protected:

			Comparable() {}

			virtual ~Comparable() {}
		};
		
		/**********************************************************************/
		
		/**********************************************************************/
		
		class ComparableEq : public ComparableEqTo<ComparableEq> {
		public:

			// Comparison operators are inherited

		private:

			/** We do not need a copy constructor for the interface. */
			ComparableEq(const ComparableEq&) : ComparableEqTo() {}
			
		protected:

			ComparableEq() {}

			virtual ~ComparableEq() {}
		};
		
		/**********************************************************************/
		
	}

}

#endif	/* COMPARABLE_H */

