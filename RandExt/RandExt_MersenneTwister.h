/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MersenneTwister.h
 * Author: DrSobik
 *
 * Created on April 3, 2016, 9:39 PM
 */

#ifndef MERSENNETWISTER_H
#define MERSENNETWISTER_H

#include "Driver"

#include "RandExt_Interfaces.h"
#include "RandExt.h"


using namespace Common::Interfaces;

namespace Common {

	namespace Rand {


		/**********************************************************************/

		template <class T, class enableT = void> class MT19937;

		template <class T, class enableT> class MT19937 : public Common::Interfaces::RandGen<T>, public ClonableTo<MT19937<T, enableT>>
		{
			private:
			protected:
			public:
		};

		/**********************************************************************/

		/** Random number generator based on the Mersenne Twister algorithm MT19937. Integer version. */
		template<> class MT19937<Math::uint32> : public Common::Interfaces::RandGen<Math::uint32>, public ClonableTo<MT19937<Math::uint32>>
		{
			private:

			Math::uint32 MT [624];
			Math::uint32 idx; // Initial value = 0

			Math::uint32 seed; // The seed

			protected:

			//MT19937() { }

			public:

			using Common::Interfaces::RandGen<Math::uint32>::ValueType;	
				
			MT19937() : seed(1872638163) { init(); }	
				
			MT19937(const MT19937 & orig) : RandGen(), ClonableTo<MT19937>() {
				idx = orig.idx;
				std::copy(orig.MT, orig.MT + 624, MT);

				seed = orig.seed;
				/*std::cout << "Created RandGenMT copy" << std::endl; getchar();*/
			}

			MT19937(const Math::uint32 & seed) {
				//std::cout << "Created RandGenMT seed" << std::endl; getchar();
				setSeed(seed);
			}

			virtual ~MT19937() { }

			void setSeed(const Math::uint32 & seed) {
				this->seed = seed;
				init();
			}

			Math::uint32 getSeed() {
				return this->seed;
			}

			/** Initialize the MT-Algorithm */
			virtual void init() {

				idx = 0;

				MT[0] = this->seed;

				for (Math::uint32 i = 1; i <= 623; i++) { // loop over each other element
					MT[i] = (1812433253 * (MT[i - 1] ^ ((MT[i - 1] >> 30))) + i) & 0xFFFFFFFF; // 0x6c078965
				}

			}

			virtual MT19937 * clone() {
				return new MT19937(*this);
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
			virtual Math::uint32 rnd() override {
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

			using Common::Interfaces::RandGen<Math::uint32>::rnd;

		};

		/**********************************************************************/

		// Floating point RNG MT
		template<class fpT> class MT19937<fpT, typename std::enable_if<std::is_floating_point<fpT>::value, void>::type> : public Common::Interfaces::RandGen<fpT>, DrivenBy<MT19937<Math::uint32>&>, public ClonableTo<MT19937<fpT>>
		{
			private:

			MT19937<Math::uint32> irg; // Internal integer RNG

			protected:

			//MT19937() : irg(1872638163) { }

			public:

			using Common::Interfaces::RandGen<fpT>::ValueType;	
				
			MT19937() : irg(1872638163) { }	
				
			MT19937(const MT19937 & orig) : Common::Interfaces::RandGen<fpT>(), DrivenBy(), ClonableTo<MT19937 < fpT >> (), irg(orig.irg) { }

			MT19937(const Math::uint32 & seed) : irg(seed) {
				//std::cout << "Created RandGenMT seed" << std::endl; getchar();
			}

			virtual ~MT19937() { }

			void setSeed(const Math::uint32 & seed) {
				irg.setSeed(seed);
			}

			Math::uint32 getSeed() {
				return this->irg.getSeed();
			}

			/** Initialize the MT-Algorithm */
			virtual void init() {
				irg.init();
			}

			virtual MT19937<Math::uint32>& driver() override {
				return irg;
			}

			virtual MT19937 * clone() override {
				return new MT19937(*this);
			}

			/** Generate a random double out of [0, 1] using the MT19937 algorithm. */
			virtual fpT rnd() override {
				return fpT(irg.rnd()) / fpT(Math::uint32(~Math::uint32(0)));
			}

			using Common::Interfaces::RandGen<fpT>::rnd;

		};

		/**********************************************************************/

	}

}

#endif /* MERSENNETWISTER_H */

