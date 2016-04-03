/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RandExtInterfaces.h
 * Author: DrSobik
 *
 * Created on April 3, 2016, 11:56 PM
 */

#ifndef RANDEXTINTERFACES_H
#define RANDEXTINTERFACES_H

namespace Common {

	namespace Interfaces {

		/**********************************************************************/

		template<class T, class enableT = void> class RandGen;

		/**********************************************************************/
		// Default template for all data types

		template<class T, class enableT> class RandGen {
		private:

			/** We do not need a copy constructor for the interface. */
			RandGen(const RandGen&) { }

		protected:

			RandGen() { }

			virtual ~RandGen() { }

		public:

			typedef T type;

			virtual T rnd() = 0;

		};

		/**********************************************************************/

		/**********************************************************************/
		// Specialization for integer numbers

		template<class T> class RandGen<T, typename std::enable_if<std::is_unsigned<T>::value, void>::type> {
		private:

			/** We do not need a copy constructor for the interface. */
			RandGen(const RandGen&) { }

		protected:

			RandGen() { }

			virtual ~RandGen() { }

		public:

			virtual T rnd() = 0;

			virtual T rnd(const T& a, const T& b) {
				T rndInteger = rnd();
				// IMPORTANT!!! We generate a random double out of [a - 0.5; b + 0.5] to make equal selection probabilities when rounding! Otherwise the probability of selecting a or b is twice smaller than it should be.
				// IMPORTANT!!! Constant 0.499999999999999 is used instead of 0.5 to avoid incorrect rounding of a-0.5 to a-1 and b+0.5 to b+1;
				return (T) Math::round(double(a - 0.499999999999999) + double (rndInteger) / double (T(~T(0))) * double (b + 0.499999999999999 - (a - 0.499999999999999)));
			};


		};

		/**********************************************************************/

		/**********************************************************************/
		// Specialization for floating-point numbers

		template<class T> class RandGen<T, typename std::enable_if<std::is_floating_point<T>::value, void>::type> {
		private:

			/** We do not need a copy constructor for the interface. */
			RandGen(const RandGen&) { }

		protected:

			RandGen() { }

			virtual ~RandGen() { }

		public:

			virtual T rnd() = 0;

			virtual T rnd(const T& a, const T& b) {
				return a + (b - a) * rnd();
			};

		};

		/**********************************************************************/

	}

}

#endif /* RANDEXTINTERFACES_H */

