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
		class RandGen;
		class IntRandGen;
		class FloatRandGen;
		class GeneralRandGen;
		class RandGenMT;
		class RandGenLCGNL;

		void rndSeed(const unsigned int& s);
		unsigned int rndSeed();
		unsigned int rndInt();
		int rndInt(const int& start, const int& finish);
		double rndDouble();
		double rndDouble(const double& start, const double& finish);

		template <template<class, class...> class V, class T, class... otherT> void randPermut(V<T, otherT...>& permut);

		template <template<class, class...> class V, class... otherVT> int probSelectIdx(const V<double, otherVT...>& prob, const double& probPow = 1.0);
		template <template<class, class...> class V, class T, class... otherVT, class... otherProbT> int probSelect(const V<T, otherVT...> v, const V<double, otherProbT...>& prob, const double& probPow = 1.0);

		/**********************************************************************/


		/**********************************************************************/

		/** Basic class for all random generators */
		class RandGen : public Object<> {
		private:

			std::vector<unsigned int> seeds; // Seeds

		protected:

			RandGen() { }

			RandGen(const RandGen& orig) : BasicObject(orig), Object<>(orig), seeds(orig.seeds) { } // No initialization in the copy constructor

			RandGen(const std::vector<unsigned int>& someSeeds) {
				setSeeds(someSeeds);
			}

			RandGen(const unsigned int& someSeed) {
				setSeed(someSeed);
			}

			virtual void init() = 0; // Set the generator into the initial state

		public:

			virtual ~RandGen() { }

			/** Set the seeds of the generator and initialize it. */
			void setSeeds(const std::vector<unsigned int>& seeds) {
				if (seeds.size() == 0) throw ErrMsgException<Message<string>>(string("Common::Rand::RandGen::setSeeds : No seeds provided!!!"), this);
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

			IntRandGen() : maxGenInt((unsigned int) ((((unsigned long int) (2)) << 31) - 1)) { }

			IntRandGen(const IntRandGen& orig) : BasicObject(orig), RandGen(orig), ClonableTo<IntRandGen>(), maxGenInt(orig.maxGenInt) { }

			IntRandGen(std::vector<unsigned int>& seeds) : RandGen(seeds), maxGenInt((unsigned int) ((((unsigned long int) (2)) << 31) - 1)) { }

			// Clone the integer RNG
			virtual IntRandGen* clone() = 0;

		public:

			virtual ~IntRandGen() { }

			const unsigned int& getMaxGenInt() {
				return maxGenInt;
			}

			/** Generate a random integer out of [0, 2^32]-1. */
			virtual unsigned int rndInt() = 0;

			/** Generate a random integer out of [a,b]. */
			unsigned int rndInt(const unsigned int& a, const unsigned int& b) {
				unsigned int rndInteger = rndInt();
				// IMPORTANT!!! We generate a random double out of [a - 0.5; b + 0.5] to make equal selection probabilities when rounding! Otherwise the probability of selecting a or b is twice smaller than it should be.
				// IMPORTANT!!! Constant 0.499999999999999 is used instead of 0.5 to avoid incorrect rounding of a-0.5 to a-1 and b+0.5 to b+1;
				return (unsigned int) Math::round(double(a - 0.499999999999999) + double (rndInteger) / double (maxGenInt) * double (b + 0.499999999999999 - (a - 0.499999999999999)));
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

			FloatRandGen(std::vector<unsigned int>& seeds) : RandGen(seeds) { }

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

			GeneralRandGen(const std::vector<unsigned int>& seeds) : RandGen(seeds) { }

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

			unsigned int MT [624];
			unsigned int idx; // Initial value = 0

		protected:

			RandGenMT() { }

		public:

			RandGenMT(const RandGenMT& orig) : BasicObject(), RandGen(orig), GeneralRandGen(orig), ClonableTo<RandGenMT>() { }

			RandGenMT(const std::vector<unsigned int>& seeds) : GeneralRandGen(seeds) { }

			RandGenMT(const unsigned int& seed) {
				setSeed(seed);
			}

			virtual ~RandGenMT() { }

			/** Initialize the MT-Algorithm */
			virtual void init() {

				idx = 0;

				std::vector<unsigned int> curSeeds = getSeeds();

				MT[0] = curSeeds[0];

				for (unsigned int i = 1; i <= 623; i++) { // loop over each other element
					MT[i] = (1812433253 * (MT[i - 1] ^ ((MT[i - 1] >> 30))) + i) & 0xFFFFFFFF; // 0x6c078965
				}

			}

			virtual RandGenMT* clone() {
				return new RandGenMT(*this);
			}

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

			RandGenLCGNL() : GeneralRandGen(), a((unsigned long int) (6364136223846793005)), c((unsigned long int) (1)), m((unsigned long int) ((unsigned long int) (2) << 63) - 1), X(0) { }

		public:

			RandGenLCGNL(const RandGenLCGNL& orig) : BasicObject(orig), RandGen(orig), GeneralRandGen(orig), ClonableTo<RandGenLCGNL>(), a(orig.a), c(orig.c), m(orig.m), X(orig.X) { }

			RandGenLCGNL(const std::vector<unsigned int>& seeds) : GeneralRandGen(seeds), a((unsigned long int) (6364136223846793005)), c((unsigned long int) (1)), m((unsigned long int) ((unsigned long int) (2) << 63) - 1), X(0) { }

			RandGenLCGNL(const unsigned int& seed) : a((unsigned long int) (6364136223846793005)), c((unsigned long int) (1)), m((unsigned long int) ((unsigned long int) (2) << 63) - 1), X(0) {
				setSeed(seed);
			}

			virtual ~RandGenLCGNL() { }

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

		/**********************************************************************/

		//int rSeed = 0; // Initial seed 
		static thread_local RandGenMT RNG(1872638163); 

		/**********************************************************************/

		/**********************************************************************/

		inline void rndSeed(const unsigned int& s) {
			//qsrand(s); //std::srand(s);

			//rSeed = s; // Preserve the initial random seed

			RNG.setSeed(s);
		}

		inline unsigned int rndSeed() {
			//return rSeed;
			if (RNG.getSeeds().size() == 0) throw ErrMsgException<Message<string>>(string("int Common::Rand::rndSeed() : No seed set!"));

			return RNG.getSeeds()[0];
		}

		inline unsigned int rndInt() {
			//return qrand(); //std::rand();

			return RNG.rndInt();
		}

		inline int rndInt(const int& start, const int& finish) {
			//return start + round((double) rndInt() / (double) RAND_MAX * (double) (finish - start));
			return start + round((double) Rand::rndInt() / (double) RNG.getMaxGenInt() * (double) (finish - start));
		}

		inline double rndDouble() {
			//return (double) Rand::rndInt() / double(RAND_MAX);
			return (double) Rand::rndInt() / double(RNG.getMaxGenInt());
		}

		inline double rndDouble(const double& start, const double& finish) {
			return start + (finish - start) * Rand::rndDouble();
		}

		/**********************************************************************/

		/**********************************************************************/

		template <template<class, class...> class V, class T, class... otherT> inline void randPermut(V<T, otherT...>& permut) {
			int n = permut.size();
			int i;
			int j;

			for (i = 1; i < n; i++) {
				//j = qrand() % (i + 1);
				j = Rand::rndInt() % (i + 1);
				Math::swap(permut[i], permut[j]);
			}
		}

		/**********************************************************************/

		/**********************************************************************/

		template <template<class, class...> class V, class... otherVT> int probSelectIdx(const V<double, otherVT...>& prob, const double& probPow) {
			int n = prob.size();
			double total;
			vector<double> intBegin;
			vector<double> intEnd;

			intBegin.resize(n);
			intEnd.resize(n);

			total = 0.0;

			for (int i = 0; i < n; i++) {
				intBegin[i] = total;
				intEnd[i] = total + pow(prob[i], probPow);
				//Debugger::info << prob[i] << " - " << probPow << "-" << ENDL;
				total = intEnd[i]; //+= pow(prob[i], probPow);
			}

			//for (int i = 0; i < n; i++) {
			//    Debugger::info << intBegin[i] << " - " << intEnd[i] << ENDL;
			//    getchar();
			//}

			double point = Rand::rndDouble(0.0, total);

			int i = 0;
			for (i = 0; i < n; i++) {
				if (intBegin[i] < point && point <= intEnd[i]) {
					break;
				}
			}

			if (i == n) {
				throw ErrMsgException<Message<string>>(string("Common::MathExt::probSelect : Failed to find interval with the point selecting randomly!"));
				return rndInt(0, n - 1);
			}

			return i;
		}

		template <template<class, class...> class V, class T, class... otherVT, class... otherProbT> int probSelect(const V<T, otherVT...> v, const V<double, otherProbT...>& prob, const double& probPow) {

			int idx = Rand::probSelectIdx(prob, probPow);

			return v[idx];

		}

		/**********************************************************************/

	}

}




#endif	/* RANDEXT_H */

