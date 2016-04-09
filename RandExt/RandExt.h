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
		/**********************************************************************/

		// Default trap
		template <class T, class enableT = void> class RND;

		void rndSeed(const Math::uint32& s);
		Math::uint32 rndSeed();

		template <template<class, class...> class V, class T, class... otherT> void randPermut(V<T, otherT...>& permut);

		template <template<class, class...> class V, class... otherVT> Math::int32 probSelectIdx(const V<double, otherVT...>& prob, const double& probPow = 1.0);
		template <template<class, class...> class V, class T, class... otherVT, class... otherProbT> T& probSelect(const V<T, otherVT...> v, const V<double, otherProbT...>& prob, const double& probPow = 1.0);

		/**********************************************************************/
		/**********************************************************************/

#ifndef RANDEXT_IRNG_TYPE
#define RANDEXT_IRNG_TYPE MT19937<Math::uint32>
#endif  

#ifndef RANDEXT_FRNG_TYPE
#define RANDEXT_FRNG_TYPE MT19937<double> 
#endif    

		typedef RANDEXT_IRNG_TYPE iRNGType;
		typedef RANDEXT_FRNG_TYPE fRNGType;

		extern thread_local iRNGType iRNG; // For generation of integers. Declare it as extern thread_local so that there is only one RNG over all translation units but it is thread-local
		extern thread_local fRNGType fRNG; // For generation of floats. Declare it as extern thread_local so that there is only one RNG over all translation units but it is thread-local

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

		/**********************************************************************/
		/**********************************************************************/

		// Integer implementation for uint32

		template<> class RND<Math::uint32> {
		public:

			inline Math::uint32 operator()() {
				return iRNG.rnd();
			}

			inline Math::uint32 operator()(const Math::uint32& start, const Math::uint32& finish) {
				return iRNG.rnd(start, finish);
			}

		};

		// Float implementation

		template<class fpT> class RND <fpT, typename std::enable_if<std::is_floating_point<fpT>::value>::type> {
		public:

			inline fpT operator()() {
				return (fpT) fRNG.rnd();
			}

			inline fpT operator()(const fpT& start, const fpT& finish) {
				return (fpT) fRNG.rnd(start, finish);
			}

		};

		// Static rnd structure which can be used for generation of random numbers
		template <class T> static RND<T> rnd = RND<T>();

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
		/**********************************************************************/

	}

}




#endif /* RANDEXT_H */

