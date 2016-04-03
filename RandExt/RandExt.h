/* 
 * File:   RandExt.h
 * Author: DrSobik
 *
 * Created on July 26, 2014, 1:18 PM
 */

#ifndef RANDEXT_H
#define RANDEXT_H

#include "Object"
#include "Clonable"
#include "MathExt"

#include "RandExt_MersenneTwister.h"

#include <type_traits>
#include <vector>
#include <algorithm>

#include <iostream>

// For testing
//#include <QThread>

using namespace Common;
using namespace Common::Interfaces;

namespace Common {

	namespace Rand {

		/**********************************************************************/
		class RandGen;
		class IntRandGen;
		class FloatRandGen;
		class GeneralRandGen;
		class RandGenMT;
		class RandGenLCGNL;

		void rndSeed(const Math::uint32& s);
		Math::uint32 rndSeed();
		//Math::uint32 rndMaxInt();
		//Math::uint32 rndInt();
		//Math::int32 rndInt(const Math::int32& start, const Math::int32& finish);
		//double rndDouble();
		//double rndDouble(const double& start, const double& finish);

		template <template<class, class...> class V, class T, class... otherT> void randPermut(V<T, otherT...>& permut);

		template <template<class, class...> class V, class... otherVT> Math::int32 probSelectIdx(const V<double, otherVT...>& prob, const double& probPow = 1.0);
		template <template<class, class...> class V, class T, class... otherVT, class... otherProbT> T& probSelect(const V<T, otherVT...> v, const V<double, otherProbT...>& prob, const double& probPow = 1.0);

		/**********************************************************************/


		/**********************************************************************/

		/** Basic class for all random generators */
		class RandGen : public Object<> {
		private:

			std::vector<Math::uint32> seeds; // Seeds

		protected:

			RandGen() { }

			RandGen(const RandGen& orig) : BasicObject(orig), Object<>(orig), seeds(orig.seeds) { } // No initialization in the copy constructor

			RandGen(const std::vector<Math::uint32>& someSeeds) {
				setSeeds(someSeeds);
			}

			RandGen(const Math::uint32& someSeed) {
				setSeed(someSeed);
			}

			virtual void init() = 0; // Set the generator into the initial state

		public:

			virtual ~RandGen() { }

			/** Set the seeds of the generator and initialize it. */
			void setSeeds(const std::vector<Math::uint32>& seeds) {
				if (seeds.size() == 0) throw ErrMsgException<Message < string >> (string("Common::Rand::RandGen::setSeeds : No seeds provided!!!"), this);
				this->seeds = seeds;

				/*
				std::cout << std::endl << std::endl << "Setting seeds" << std::endl;
				std::cout << "Thread: " << QThread::currentThread() << std::endl;
				std::cout << "Object: " << this << std::endl;
				
				for (Math::uint32 i = 0 ; i < (Math::uint32) this->seeds.size() ;i++ ){
					std::cout << "Seed: " << this->seeds[i] << std::endl;
				}
				getchar();
				 */

				init();
			}

			void setSeed(const Math::uint32& seed) {
				std::vector<Math::uint32> newSeeds;
				newSeeds.push_back(seed);
				setSeeds(newSeeds);
			}

			const std::vector<Math::uint32>& getSeeds() {

				/*
				std::cout << std::endl << std::endl << "Getting seeds" << std::endl;
				std::cout << "Thread: " << QThread::currentThread() << std::endl;
				std::cout << "Object: " << this << std::endl;
				
				for (Math::uint32 i = 0 ; i < (Math::uint32) this->seeds.size() ;i++ ){
					std::cout << "Seed: " << this->seeds[i] << std::endl;
				}
				getchar();
				 */

				return seeds;
			}

		};

		/**********************************************************************/

		/**********************************************************************/

		/** Basic class for all integer random number generators */
		class IntRandGen : public virtual RandGen, public ClonableTo<IntRandGen> {
		private:

		protected:

			const Math::uint32 maxGenInt; // The upper bound of the generated integers 

			IntRandGen() : maxGenInt((Math::uint32) ((((Math::uint64) (2)) << 31) - 1)) { }

			IntRandGen(const IntRandGen& orig) : BasicObject(orig), RandGen(orig), ClonableTo<IntRandGen>(), maxGenInt(orig.maxGenInt) { }

			IntRandGen(std::vector<Math::uint32>& seeds) : RandGen(seeds), maxGenInt((Math::uint32) ((((Math::uint64) (2)) << 31) - 1)) { }

			// Clone the integer RNG
			virtual IntRandGen* clone() = 0;

		public:

			virtual ~IntRandGen() { }

			const Math::uint32& getMaxGenInt() {
				return maxGenInt;
			}

			/** Generate a random integer out of [0, 2^32]-1. */
			virtual Math::uint32 rndInt() = 0;

			/** Generate a random integer out of [a,b]. */
			Math::uint32 rndInt(const Math::uint32& a, const Math::uint32& b) {
				Math::uint32 rndInteger = rndInt();
				// IMPORTANT!!! We generate a random double out of [a - 0.5; b + 0.5] to make equal selection probabilities when rounding! Otherwise the probability of selecting a or b is twice smaller than it should be.
				// IMPORTANT!!! Constant 0.499999999999999 is used instead of 0.5 to avoid incorrect rounding of a-0.5 to a-1 and b+0.5 to b+1;
				return (Math::uint32) Math::round(double(a - 0.499999999999999) + double (rndInteger) / double (maxGenInt) * double (b + 0.499999999999999 - (a - 0.499999999999999)));
			}

		};

		/**********************************************************************/

		/**********************************************************************/

		/** Basic class for all float random number generators */
		class FloatRandGen : public virtual RandGen, public ClonableTo<FloatRandGen> {
		private:

		protected:

			FloatRandGen() { }

			FloatRandGen(const FloatRandGen& orig) : BasicObject(orig), RandGen(orig), ClonableTo<FloatRandGen>() { }

			FloatRandGen(std::vector<Math::uint32>& seeds) : RandGen(seeds) { }

			virtual FloatRandGen* clone() = 0;

		public:

			virtual ~FloatRandGen() { }

			/** Generate a random float out of [0, 1]. */
			virtual double rndFloat() = 0;

			/** Generate a random float out of [a,b]. */
			double rndFloat(const double& a, const double& b) {
				return a + (b - a) * rndFloat();
			}

		};

		/**********************************************************************/

		/**********************************************************************/

		/** Basic class for all random number generators */
		class GeneralRandGen : public IntRandGen, public FloatRandGen, ClonableTo<GeneralRandGen> {
		private:

		protected:

			GeneralRandGen() : RandGen() { }

			GeneralRandGen(const GeneralRandGen& orig) : BasicObject(orig), RandGen(orig), IntRandGen(orig), FloatRandGen(orig), ClonableTo<GeneralRandGen>() { }

			GeneralRandGen(const std::vector<Math::uint32>& seeds) : RandGen(seeds) { }

			virtual void init() = 0;

		public:

			virtual ~GeneralRandGen() { }

			virtual GeneralRandGen* clone() = 0;

			/** Generate a random float out of [0, 1]. */
			virtual double rndFloat() {
				return ((double) rndInt()) / double(IntRandGen::maxGenInt);
			}

			using IntRandGen::rndInt;
			using FloatRandGen::rndFloat;

		};

		/**********************************************************************/

		/**********************************************************************/

		/** Random number generator based on the Mersenne Twister algorithm MT19937. */
		class RandGenMT : public GeneralRandGen, public ClonableTo<RandGenMT> {
			//Q_OBJECT
		private:

			Math::uint32 MT [624];
			Math::uint32 idx; // Initial value = 0

		protected:

			RandGenMT() { }

		public:

			RandGenMT(const RandGenMT& orig) : BasicObject(), RandGen(orig), GeneralRandGen(orig), ClonableTo<RandGenMT>() {
				idx = orig.idx;
				std::copy(orig.MT, orig.MT + 624, MT);
				/*std::cout << "Created RandGenMT copy" << std::endl; getchar();*/
			}

			RandGenMT(const std::vector<Math::uint32>& seeds) : GeneralRandGen(seeds) { /*std::cout << "Created RandGenMT seeds" << std::endl; getchar();*/ }

			RandGenMT(const Math::uint32& seed) {
				//std::cout << "Created RandGenMT seed" << std::endl; getchar();
				setSeed(seed);
			}

			virtual ~RandGenMT() { }

			/** Initialize the MT-Algorithm */
			virtual void init() {

				idx = 0;

				std::vector<Math::uint32> curSeeds = getSeeds();

				MT[0] = curSeeds[0];

				for (Math::uint32 i = 1; i <= 623; i++) { // loop over each other element
					MT[i] = (1812433253 * (MT[i - 1] ^ ((MT[i - 1] >> 30))) + i) & 0xFFFFFFFF; // 0x6c078965
				}

			}

			virtual RandGenMT* clone() {
				return new RandGenMT(*this);
			}

			/** Generate the parameters for MT. */
			void generateNumbers() {
				for (Math::int32 i = 0; i <= 623; i++) {
					Math::uint32 y = (MT[i] & 0x80000000) // bit 31 (32nd bit) of MT[i]
							+ (MT[(i + 1) % 624] & 0x7fffffff); // bits 0-30 (first 31 bits) of MT[...]

					MT[i] = MT[(i + 397) % 624] ^ (y >> 1);

					if ((y % 2) != 0) { // y is odd
						MT[i] = MT[i] ^ (2567483615); // 0x9908b0df
					}
				}
			}

			/** Generate a random integer out of [0, 2^32-1] using the MT19937 algorithm. */
			virtual Math::uint32 rndInt() {
				if (idx == 0) {
					generateNumbers();
				};

				Math::uint32 y = MT[idx];

				y = y ^ (y >> 11);
				y = y ^ ((y << 7) & (2636928640)); // 0x9d2c5680
				y = y ^ ((y << 15) & (4022730752)); // 0xefc60000
				y = y ^ (y >> 18);

				idx = (idx + 1) % 624;

				return y;
			}

			using GeneralRandGen::rndInt; // Reuse from IntRandGen
			using GeneralRandGen::rndFloat; // Reuse from FloatRandGen

		};

		/**********************************************************************/

		/**********************************************************************/

		/** Random number generator based on the LCG algorithm from NewLib. */
		class RandGenLCGNL : public GeneralRandGen, ClonableTo<RandGenLCGNL> {
		private:

			const Math::uint64 a;
			const Math::uint64 c;
			const Math::uint64 m;

			Math::uint64 X;

		protected:

			RandGenLCGNL() : GeneralRandGen(), a((Math::uint64) (6364136223846793005)), c((Math::uint64) (1)), m((Math::uint64) ((Math::uint64) (2) << 63) - 1), X(0) { }

		public:

			RandGenLCGNL(const RandGenLCGNL& orig) : BasicObject(orig), RandGen(orig), GeneralRandGen(orig), ClonableTo<RandGenLCGNL>(), a(orig.a), c(orig.c), m(orig.m), X(orig.X) { }

			RandGenLCGNL(const std::vector<Math::uint32>& seeds) : GeneralRandGen(seeds), a((Math::uint64) (6364136223846793005)), c((Math::uint64) (1)), m((Math::uint64) ((Math::uint64) (2) << 63) - 1), X(0) { }

			RandGenLCGNL(const Math::uint32& seed) : a((Math::uint64) (6364136223846793005)), c((Math::uint64) (1)), m((Math::uint64) ((Math::uint64) (2) << 63) - 1), X(0) {
				setSeed(seed);
			}

			virtual ~RandGenLCGNL() { }

			virtual void init() {
				std::vector<Math::uint32> curSeeds = getSeeds();
				X = curSeeds[0];
			}

			virtual RandGenLCGNL* clone() {
				return new RandGenLCGNL(*this);
			}

			/** Generate a random integer out of [0, 2^32]-1. */
			virtual Math::uint32 rndInt() {
				X = ((a * X + c) & 0xFFFFFFFFFFFFFFFF) >> 32;
				return (Math::uint32)X;
			}

			using GeneralRandGen::rndInt; // Reuse from IntRandGen
			using GeneralRandGen::rndFloat; // Reuse from FloatRandGen

		};


		/**********************************************************************/

		/**********************************************************************/

		//Math::int32 rSeed = 0; // Initial seed 
		//extern thread_local RandGenMT RNG; // Declare it as extern thread_local so that there is only one RNG over all translation units but it is thread-local

		extern thread_local MT19937<Math::uint32> iRNG; // For generation of integers
		extern thread_local MT19937<double> fRNG; // For generation of floats

		/**********************************************************************/

		/**********************************************************************/

		inline void rndSeed(const Math::uint32& s) {
			//qsrand(s); //std::srand(s);

			//rSeed = s; // Preserve the initial random seed

			//RNG.setSeed(s);
			iRNG.setSeed(s);
			fRNG.setSeed(s);
		}

		inline Math::uint32 rndSeed() {
			//return rSeed;
			//if (RNG.getSeeds().size() == 0) throw ErrMsgException<Message < string >> (string("Math::int32 Common::Rand::rndSeed() : No seed set!"));

			//return RNG.getSeeds()[0];
			return iRNG.getSeed();
		}

		template <class T = void> inline T rnd();

		template<> inline Math::uint32 rnd<Math::uint32>() {
			return iRNG.rnd();
		}

		template<> inline double rnd<double>() {
			return fRNG.rnd();
		}

		template <class T = void> inline T rnd(const T&, const T&);

		template<> inline Math::uint32 rnd<Math::uint32>(const Math::uint32& start, const Math::uint32& finish) {
			return iRNG.rnd(start, finish);
		}

		template<> inline double rnd<double>(const double& start, const double& finish) {
			return fRNG.rnd(start, finish);
		}



		/*
		 
		inline Math::uint32 rndMaxInt() {

			return RNG.getMaxGenInt();

		} 
		  
		inline Math::uint32 rndInt() {
			//return qrand(); //std::rand();

			return RNG.rndInt();
		}
		 

		inline Math::int32 rndInt(const Math::int32& start, const Math::int32& finish) {
			//return start + round((double) rndInt() / (double) RAND_MAX * (double) (finish - start));
			return start + (Math::int32) round((double) Rand::rndInt() / (double) rndMaxInt() * (double) (finish - start));
		}

		inline double rndDouble() {
			//return (double) Rand::rndInt() / double(RAND_MAX);
			return (double) Rand::rndInt() / double(rndMaxInt());
		}

		inline double rndDouble(const double& start, const double& finish) {
			return start + (finish - start) * Rand::rndDouble();
		}
		 */

		/**********************************************************************/

		/**********************************************************************/

		template <template<class, class...> class V, class T, class... otherT> inline void randPermut(V<T, otherT...>& permut) {
			Math::int32 n = (Math::int32) permut.size();
			Math::int32 i;
			Math::int32 j;

			for (i = 1; i < n; i++) {
				//j = qrand() % (i + 1);
				//j = Rand::rndInt() % (i + 1);
				j = Rand::rnd<Math::uint32>() % (i + 1);
				Math::swap(permut[i], permut[j]);
			}
		}

		/**********************************************************************/

		/**********************************************************************/

		template <template<class, class...> class V, class... otherVT> Math::int32 probSelectIdx(const V<double, otherVT...>& prob, const double& probPow) {
			Math::int32 n = prob.size();
			double total;
			vector<double> intBegin;
			vector<double> intEnd;

			intBegin.resize(n);
			intEnd.resize(n);

			total = 0.0;

			if (probPow == 1.0) { // Do not call the pow function

				for (Math::int32 i = 0; i < n; i++) {
					intBegin[i] = total;
					intEnd[i] = total + prob[i];
					//Debugger::info << prob[i] << " - " << probPow << "-" << ENDL;
					total = intEnd[i]; //+= pow(prob[i], probPow);
				}

			} else { // Call the pow function

				for (Math::int32 i = 0; i < n; i++) {
					intBegin[i] = total;
					intEnd[i] = total + Math::pow(prob[i], probPow);
					//Debugger::info << prob[i] << " - " << probPow << "-" << ENDL;
					total = intEnd[i]; //+= pow(prob[i], probPow);
				}

			}

			//for (Math::int32 i = 0; i < n; i++) {
			//    Debugger::info << intBegin[i] << " - " << intEnd[i] << ENDL;
			//    getchar();
			//}

			//double point = Rand::rndDouble(0.0, total);
			double point = Rand::rnd<double>(0.0, total);

			Math::int32 i = 0;
			for (i = 0; i < n; i++) {
				if (intBegin[i] < point && point <= intEnd[i]) {
					break;
				}
			}

			if (i == n) {
				throw ErrMsgException<Message < string >> (string("Common::MathExt::probSelectIdx : Failed to find interval with the point selecting randomly!"));
				//return rndInt(0, n - 1);
				return rnd<Math::uint32>(0, n - 1);
			}

			return i;
		}

		template <template<class, class...> class V, class T, class... otherVT, class... otherProbT> T& probSelect(const V<T, otherVT...> v, const V<double, otherProbT...>& prob, const double& probPow) {

			Math::int32 idx = Rand::probSelectIdx(prob, probPow);

			return (T&) v[idx];

		}

		/**********************************************************************/

	}

}




#endif /* RANDEXT_H */

