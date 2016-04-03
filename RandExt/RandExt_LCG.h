/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LCG.h
 * Author: DrSobik
 *
 * Created on April 3, 2016, 10:05 PM
 */

#ifndef LCG_H
#define LCG_H

#include "RandExt.h"

#include "Driver"

using namespace Common;
using namespace Common::Interfaces;

namespace Common {

	namespace Rand {

		/**********************************************************************/

		template <class T, class enableT = void> class LCGNL;

		template <class T, class enableT> class LCGNL : public Common::Interfaces::RandGen<T>, public ClonableTo<LCGNL<T, enableT>>
		{
			private:
			protected:
			public:
		};

		/**********************************************************************/

		/** Random number generator based on the LCG algorithm from NewLib. */
		template<> class LCGNL<Math::uint32> : public Common::Interfaces::RandGen<Math::uint32>, ClonableTo<LCGNL<Math::uint32>>
		{
			private:

			const Math::uint64 a;
			const Math::uint64 c;
			const Math::uint64 m;

			Math::uint64 X;

			Math::uint64 seed;

			protected:

			LCGNL() : RandGen(), ClonableTo<LCGNL>(), a((Math::uint64) (6364136223846793005)), c((Math::uint64) (1)), m((Math::uint64) ((Math::uint64) (2) << 63) - 1), X(0) { }

			public:

			LCGNL(const LCGNL & orig) : RandGen(), ClonableTo<LCGNL>(), a(orig.a), c(orig.c), m(orig.m), X(orig.X), seed(orig.seed) { }

			LCGNL(const Math::uint32 & seed) : a((Math::uint64) (6364136223846793005)), c((Math::uint64) (1)), m((Math::uint64) ((Math::uint64) (2) << 63) - 1), X(0) {
				setSeed(seed);
			}

			virtual ~LCGNL() { }

			void setSeed(const Math::uint32 & seed) {
				this->seed = seed;
				init();
			}

			Math::uint32 getSeed() {
				return this->seed;
			}

			virtual void init() {
				X = Math::uint64(seed);
			}

			virtual LCGNL * clone() {
				return new LCGNL(*this);
			}

			/** Generate a random integer out of [0, 2^32-1]. */
			virtual Math::uint32 rnd() {
				X = ((a * X + c) & 0xFFFFFFFFFFFFFFFF) >> 32;
				return (Math::uint32)X;
			}

			using Common::Interfaces::RandGen<Math::uint32>::RandGen::rnd;
			
		};


		/**********************************************************************/

		// Floating point RNG LCGNL
		template<class fpT> class LCGNL<fpT, typename std::enable_if<std::is_floating_point<fpT>::value, void>::type> : public Common::Interfaces::RandGen<fpT>, DrivenBy<LCGNL<Math::uint32>&>, public ClonableTo<LCGNL<fpT>>
		{
			private:

			LCGNL<Math::uint32> irg; // Internal integer RNG

			protected:

			LCGNL() : irg(0) { }

			public:

			LCGNL(const LCGNL & orig) : Common::Interfaces::RandGen<fpT>(), DrivenBy(), ClonableTo<LCGNL < fpT >> (), irg(orig.irg) { }

			LCGNL(const Math::uint32 & seed) : irg(seed) {
				//std::cout << "Created RandGenMT seed" << std::endl; getchar();
			}

			virtual ~LCGNL() { }

			void setSeed(const Math::uint32 & seed) {
				irg.setSeed(seed);
			}

			Math::uint32 getSeed() {
				return this->irg.getSeed();
			}

			/** Initialize the LCGNL-Algorithm */
			virtual void init() {
				irg.init();
			}

			virtual LCGNL<Math::uint32>& driver() override {
				return irg;
			}
			
			virtual LCGNL * clone() {
				return new MT19937<fpT>(*this);
			}

			/** Generate a random double out of [0, 1] using the LCGNL algorithm. */
			virtual fpT rnd() override {
				return fpT(irg.rnd()) / fpT(Math::uint32(~Math::uint32(0)));
			}

			using Common::Interfaces::RandGen<fpT>::rnd;
			
		};

		/**********************************************************************/

	}

}
#endif /* LCG_H */

