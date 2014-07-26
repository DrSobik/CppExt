/* 
 * File:   RandExt.h
 * Author: DrSobik
 *
 * Created on July 26, 2014, 1:18 PM
 */

#ifndef RANDEXT_H
#define	RANDEXT_H

#include "Object"
#include "Clonable"
#include "MathExt"

#include <vector>

using namespace Common;
using namespace Common::Interfaces;

namespace Common {

	namespace Rand {

		/**********************************************************************/

		/** Basic class for all random generators */
		class RandGen : public Object<> {
		private:

			std::vector<unsigned int> seeds; // Seeds

		protected:

			RandGen() {}

			RandGen(const RandGen& orig) : BasicObject(orig), Object<>(orig), seeds(orig.seeds) {} // No initialization in the copy constructor

			RandGen(const std::vector<unsigned int>& someSeeds) {
				setSeeds(someSeeds);
			}

			virtual void init() = 0; // Set the generator into the initial state

		public:

			virtual ~RandGen() {}

			/** Set the seeds of the generator and initialize it. */
			void setSeeds(const std::vector<unsigned int>& seeds) {
				if (seeds.size() == 0) throw ErrMsgException<Message<>>("Common::Rand::RandGen::setSeeds : No seeds provided!!!", this);
				this->seeds = seeds;
				init();
			}

			void setSeed(const unsigned int& seed) {
				std::vector<unsigned int> newSeeds;
				newSeeds.push_back(seed);
				setSeeds(newSeeds);
			}
			
			const std::vector<unsigned int>& getSeeds() {
				return seeds;
			}

		};

		/**********************************************************************/

		/**********************************************************************/

		/** Basic class for all integer random number generators */
		class IntRandGen : public virtual RandGen, public ClonableTo<IntRandGen> {
		private:

		protected:

			const unsigned int maxGenInt; // The upper bound of the generated integers 
			
			IntRandGen() : maxGenInt((unsigned int)((((unsigned long int)(2)) << 31) - 1)) {}

			IntRandGen(const IntRandGen& orig) : BasicObject(orig), RandGen(orig), ClonableTo<IntRandGen>(), maxGenInt(orig.maxGenInt) {}

			IntRandGen(std::vector<unsigned int>& seeds) : RandGen(seeds), maxGenInt((unsigned int)((((unsigned long int)(2)) << 31) - 1)) {}
			
			// Clone the integer RNG
			virtual IntRandGen* clone() = 0; 

		public:

			virtual ~IntRandGen() {}
			
			const unsigned int& getMaxGenInt(){return maxGenInt;}
			
			/** Generate a random integer out of [0, 2^32]-1. */
			virtual unsigned int rndInt() = 0;

			/** Generate a random integer out of [a,b]. */
			unsigned int rndInt(const unsigned int& a, const unsigned int& b) {
				unsigned int rndInteger = rndInt();
				// IMPORTANT!!! We generate a random double out of [a - 0.5; b + 0.5] to make equal selection probabilities when rounding! Otherwise the probability of selecting a or b it twice smaller than it should be.
				return (unsigned int) Math::round ( double(a - 0.5) + double (rndInteger) / double (maxGenInt) * double (b + 0.5 - (a - 0.5)));
			}

		};

		/**********************************************************************/

		/**********************************************************************/

		/** Basic class for all float random number generators */
		class FloatRandGen : public virtual RandGen, public ClonableTo<FloatRandGen> {
		private:

		protected:

			FloatRandGen() {}

			FloatRandGen(const FloatRandGen& orig) : BasicObject(orig), RandGen(orig), ClonableTo<FloatRandGen>() {}

			FloatRandGen(std::vector<unsigned int>& seeds) : RandGen(seeds) {}

			virtual FloatRandGen* clone() = 0;

		public:

			virtual ~FloatRandGen() {}

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

			GeneralRandGen() : RandGen() {}

			GeneralRandGen(const GeneralRandGen& orig) : BasicObject(orig), RandGen(orig), IntRandGen(orig), FloatRandGen(orig), ClonableTo<GeneralRandGen>() {}

			GeneralRandGen(const std::vector<unsigned int>& seeds) : RandGen(seeds) {}
			
			virtual void init() = 0;

		public:

			virtual ~GeneralRandGen() {}
			
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

			unsigned int MT [624];
			unsigned int idx; // Initial value = 0

		protected:

			RandGenMT(){}

		public:

			RandGenMT(const RandGenMT& orig) : BasicObject(), RandGen(orig), GeneralRandGen(orig), ClonableTo<RandGenMT>() {}

			RandGenMT(const std::vector<unsigned int>& seeds) : GeneralRandGen(seeds) {}

			RandGenMT(const unsigned int& seed) {setSeed(seed);}

			virtual ~RandGenMT() {}

			/** Initialize the MT-Algorithm */
			virtual void init() {

				idx = 0;

				std::vector<unsigned int> curSeeds = getSeeds();

				MT[0] = curSeeds[0];

				for (unsigned int i = 1; i <= 623; i++) { // loop over each other element
					MT[i] = (1812433253 * (MT[i - 1] ^ ((MT[i - 1] >> 30))) + i) & 0xFFFFFFFF; // 0x6c078965
				}

			}
			
			virtual RandGenMT* clone() {return new RandGenMT(*this);}

			/** Generate the parameters for MT. */
			void generateNumbers() {
				for (int i = 0; i <= 623; i++) {
					unsigned int y = (MT[i] & 0x80000000) // bit 31 (32nd bit) of MT[i]
							+ (MT[(i + 1) % 624] & 0x7fffffff); // bits 0-30 (first 31 bits) of MT[...]

					MT[i] = MT[(i + 397) % 624] ^ (y >> 1);

					if ((y % 2) != 0) { // y is odd
						MT[i] = MT[i] ^ (2567483615); // 0x9908b0df
					}
				}
			}

			/** Generate a random integer out of [0, 2^32]-1 using the MT19937 algorithm. */
			virtual unsigned int rndInt() {
				if (idx == 0) {
					generateNumbers();
				};
				
				unsigned int y = MT[idx];

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

			const unsigned long int a;
			const unsigned long int c;
			const unsigned long int m;

			unsigned long int X;

		protected:

			RandGenLCGNL() : GeneralRandGen(), a((unsigned long int)(6364136223846793005)), c((unsigned long int)(1)), m((unsigned long int)((unsigned long int)(2) << 63) - 1), X(0) {}

		public:

			RandGenLCGNL(const RandGenLCGNL& orig) : BasicObject(orig), RandGen(orig), GeneralRandGen(orig), ClonableTo<RandGenLCGNL>(), a(orig.a), c(orig.c), m(orig.m), X(orig.X) {}

			RandGenLCGNL(const std::vector<unsigned int>& seeds) : GeneralRandGen(seeds), a((unsigned long int)(6364136223846793005)), c((unsigned long int)(1)), m((unsigned long int)((unsigned long int)(2) << 63) - 1), X(0) {}

			RandGenLCGNL(const unsigned int& seed) : a((unsigned long int)(6364136223846793005)), c((unsigned long int)(1)), m((unsigned long int)((unsigned long int)(2) << 63) - 1), X(0) {
				setSeed(seed);
			}

			virtual ~RandGenLCGNL() {}

			virtual void init() {
				std::vector<unsigned int> curSeeds = getSeeds();
				X = curSeeds[0];
			}
			
			virtual RandGenLCGNL* clone() {
				return new RandGenLCGNL(*this);
			}

			/** Generate a random integer out of [0, 2^32]-1. */
			virtual unsigned int rndInt() {
				X = ((a * X + c) & 0xFFFFFFFFFFFFFFFF) >> 32;
				return X;
			}

			using GeneralRandGen::rndInt; // Reuse from IntRandGen
			using GeneralRandGen::rndFloat; // Reuse from FloatRandGen
			
		};


		/**********************************************************************/

	}

}




#endif	/* RANDEXT_H */

