/* 
 * File:   MathExt.h
 * Author: DrSobik
 *
 * Created on July 25, 2014, 9:14 PM
 */

#ifndef MATHEXT_H
#define MATHEXT_H

#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdint>
#include <limits>

#include "Exceptions"

using namespace Common::Exceptions;

using namespace std;

namespace Common {

	namespace Math {

		/**********************************************************************/

		typedef int8_t int8; // 8 bit
		typedef int16_t int16; // 16 bit
		typedef int32_t int32; // 32 bit
		typedef int64_t int64; // 64 bit

		typedef uint8_t uint8; // 8 bit
		typedef uint16_t uint16; // 16 bit
		typedef uint32_t uint32; // 32 bit
		typedef uint64_t uint64; // 64 bit

#ifdef MATHEXT_INTUNI_8
		typedef Math::int8 intUNI;
		typedef Math::uint8 uintUNI;
#elif MATHEXT_INTUNI_16
		typedef Math::int16 intUNI;
		typedef Math::uint16 uintUNI;
#elif MATHEXT_INTUNI_32
		typedef Math::int32 intUNI;
		typedef Math::uint32 uintUNI;
#elif MATHEXT_INTUNI_64
		typedef Math::int64 intUNI;
		typedef Math::uint64 uintUNI;
#else 
		typedef Math::int64 intUNI;
		typedef Math::uint64 uintUNI;
#endif


		/**********************************************************************/

		/**********************************************************************/

		template<class T> static const T numLowerLimit = std::numeric_limits<T>::lowest();
		template<class T> static const T numUpperLimit = std::numeric_limits<T>::max();
		template<class T> static const T numInfinity = std::numeric_limits<T>::infinity();
		template<class T> static const T numEpsilon = std::numeric_limits<T>::epsilon();
		
		const double E = 2.71828182845904523536028747135266249775724709369995; //M_E;
		const double Pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679; //M_PI;
		const double Pi_2 = Pi / 2.0; //M_PI_2;
		const double MAX_DOUBLE = 1e300;
		const double MIN_DOUBLE = -1e300;
		const double EPSILON = 1e-15;

		const int8 MAX_INT8 = int8((uint8(1) << 7) - 1); // 127
		const int8 MIN_INT8 = ~MAX_INT8; // -128
		const int16 MAX_INT16 = int16((uint16(1) << 15) - 1); // 32767
		const int16 MIN_INT16 = ~MAX_INT16; // -32768
		//		const int32 MAX_INT = int32((uint32(1) << 31) - 1); // 2147483647
		//		const int32 MIN_INT = ~MAX_INT; // -2147483648
		const int32 MAX_INT32 = int32((uint32(1) << 31) - 1); // 2147483647
		const int32 MIN_INT32 = ~MAX_INT32; // -2147483648
		const int64 MAX_INT64 = int64((uint64(1) << 63) - 1); // 9223372036854775807
		const int64 MIN_INT64 = ~MAX_INT64; // -9223372036854775808

		const uint16 MAX_UINT8 = uint8((uint16(1) << 8) - 1); // 255
		const uint16 MIN_UINT8 = 0;
		const uint16 MAX_UINT16 = uint16((uint32(1) << 16) - 1); // 65535
		const uint16 MIN_UINT16 = 0;
		//		const uint32 MAX_UINT = uint32((uint64(1) << 32) - 1); // 4294967295
		//		const uint32 MIN_UINT = 0;
		const uint32 MAX_UINT32 = uint32((uint64(1) << 32) - 1); // 4294967295
		const uint32 MIN_UINT32 = 0;
		const uint64 MAX_UINT64 = uint64(((uint64(1) << 63) - 1) << 1) + 1; // 18446744073709551615
		const uint64 MIN_UINT64 = 0;

#ifdef MATHEXT_INTUNI_8
		const intUNI MAX_INTUNI = MAX_INT8;
		const intUNI MIN_INTUNI = MIN_INT8;
		const uintUNI MAX_UINTUNI = MAX_UINT8;
		const uintUNI MIN_UINTUNI = MIN_UINT8;
#elif MATHEXT_INTUNI_16
		const intUNI MAX_INTUNI = MAX_INT16;
		const intUNI MIN_INTUNI = MIN_INT16;
		const uintUNI MAX_UINTUNI = MAX_UINT16;
		const uintUNI MIN_UINTUNI = MIN_UINT16;
#elif MATHEXT_INTUNI_32
		const intUNI MAX_INTUNI = MAX_INT32;
		const intUNI MIN_INTUNI = MIN_INT32;
		const uintUNI MAX_UINTUNI = MAX_UINT32;
		const uintUNI MIN_UINTUNI = MIN_UINT32;
#elif MATHEXT_INTUNI_64
		const intUNI MAX_INTUNI = MAX_INT64;
		const intUNI MIN_INTUNI = MIN_INT64;
		const uintUNI MAX_UINTUNI = MAX_UINT64;
		const uintUNI MIN_UINTUNI = MIN_UINT64;
#else
		const intUNI MAX_INTUNI = MAX_INT64;
		const intUNI MIN_INTUNI = MIN_INT64;
		const uintUNI MAX_UINTUNI = MAX_UINT64;
		const uintUNI MIN_UINTUNI = MIN_UINT64;
#endif  
		
		/**********************************************************************/

		/**********************************************************************/
		template<class T> void swap(T& x, T& y);

		double pow(const double& x, const double& p);
		double pow(const double& x, const Math::intUNI& p);
		double sqr(const double& x);
		double sqrt(const double& x);
		double exp(const double& x);

		double lg(const double& x);
		double ln(const double& x);
		double log(const double& base, const double& x);

		double sin(const double& x);
		double cos(const double& x);
		double tan(const double& x);
		double cot(const double& x);

		double arcsin(const double& x);
		double arccos(const double& x);
		double arctan(const double& x);
		double arccot(const double& x);

		Math::intUNI iabs(const Math::intUNI& x);
		double fabs(const double& x);
		Math::intUNI abs(const Math::intUNI& x);
		double abs(const double& x);

		Math::intUNI cmp(const double& x1, const double& x2, const double& eps = Common::Math::EPSILON);

		template<class T> const T& min(const T& x1, const T& x2);
		template <template<class, class...> class V, class T, class... otherT> const T& min(const V<T, otherT...>& v);
		template <template<class, class...> class V, class T, class... otherT> Math::intUNI minIdx(const V<T, otherT...>& v);

		template<class T> const T& max(const T& x1, const T& x2);
		template <template<class, class...> class V, class T, class... otherT> const T& max(const V<T, otherT...>& v);
		template <template<class, class...> class V, class T, class... otherT> Math::intUNI maxIdx(const V<T, otherT...>& v);

		template <template<class, class...> class V, class T, class... otherT> T& sum(V<T, otherT...>& v);

		template <template<class, class...> class V, class T, class... otherT> void sort(V<T, otherT...>& v, const bool& asc = true);
		template <template<class, class...> class V, class T, class... otherT> void stableSort(V<T, otherT...>& v, const bool& asc = true);

		template <template<class, class...> class V, class T, class... otherT> void reverseVec(V<T, otherT...>& v);

		template <template<class, class...> class V, class T, class... otherT> void removeDuplicates(V<T, otherT...>& v);

		double round(const double& x);
		double ceil(const double& x);
		double floor(const double& x);

		template <template<class, class...> class V, class T, class... otherT> bool nextLexPermutation(V<T, otherT...>& array);

		Math::uint64 factorial(const Math::uintUNI& n);
		/**********************************************************************/

		/**********************************************************************/

		/**********************************************************************/

		template<class T> void swap(T& x, T& y) {
			T z = x;

			x = y;

			y = z;
		}

		/**********************************************************************/

		/**********************************************************************/

		inline double pow(const double& x, const double& p) {
			return std::pow(x, p);
		}

		inline double pow(const double& x, const Math::intUNI& p) {
			return std::pow(x, p);
		}

		inline double sqr(const double& x) {
			return std::pow(x, 2);
		}

		inline double sqrt(const double& x) {
#ifndef MATHEXT_NO_CHECKS
			if (x < 0.0) throw ErrMsgException<Message < string >> (string("Common::MathExt::sqrt(const double x) negative argument!"));
#endif
			return std::sqrt(x);
		}

		inline double exp(const double& x) {
			return std::exp(x);
		}

		/**********************************************************************/

		/**********************************************************************/

		inline double lg(const double& x) {
#ifndef MATHEXT_NO_CHECKS
			if (cmp(x, 0.0, EPSILON) <= 0) throw ErrMsgException<Message < string >> (string("Common::MathExt::lg(const double x) small/negative argument!"));
#endif
			return std::log10(x);
		}

		inline double ln(const double& x) {
#ifndef MATHEXT_NO_CHECKS
			if (cmp(x, 0.0, EPSILON) <= 0) throw ErrMsgException<Message < string >> (string("Common::MathExt::ln(const double x) small/negative argument!"));
#endif
			return std::log(x);
		}

		inline double log(const double& base, const double& x) {
#ifndef MATHEXT_NO_CHECKS
			if (cmp(x, 0.0, EPSILON) <= 0) throw ErrMsgException<Message < string >> (string("Common::MathExt::lg(const double x) small/negative argument!"));
			if (cmp(base, 0.0, EPSILON) <= 0) throw ErrMsgException<Message < string >> (string("Common::MathExt::lg(const double x) small/negative base!"));
#endif
			return ln(x) / ln(base);
		}

		/**********************************************************************/

		/**********************************************************************/

		inline double sin(const double& x) {
			return std::sin(x);
		}

		inline double cos(const double& x) {
			return std::cos(x);
		}

		inline double tan(const double& x) {
#ifndef MATHEXT_NO_CHECKS
			if ((cmp(round(x / Pi_2), x / Pi_2, EPSILON) == 0) && (cmp(round(x / Pi), x / Pi, EPSILON) != 0)) throw ErrMsgException<Message < string >> (string("Common::MathExt::tan(const double x) argument is multiplicity of Pi/2 !"));
#endif
			return std::tan(x);
		}

		inline double cot(const double& x) {
#ifndef MATHEXT_NO_CHECKS
			if (cmp(round(x / Pi), x / Pi, EPSILON) == 0) throw ErrMsgException<Message < string >> (string("Common::MathExt::cot(const double x) argument is multiplicity of Pi !"));
			if (cmp(round(x / Pi_2), x / Pi_2, EPSILON) == 0) throw ErrMsgException<Message < string >> (string("Common::MathExt::cot(const double x) argument is multiplicity of Pi/2 !"));
#endif
			return 1.0 / tan(x);
		}

		inline double arcsin(const double& x) {
			return std::asin(x);
		}

		inline double arccos(const double& x) {
			return std::acos(x);
		}

		inline double arctan(const double& x) {
			return std::atan(x);
		}

		inline double arccot(const double& x) {
			return Pi_2 - arctan(x);
		}

		/**********************************************************************/

		/**********************************************************************/

		/** Integer abs */
		inline Math::intUNI iabs(const Math::intUNI& x) {
			return Common::Math::abs(x);
		}

		/** FP abs */
		inline double fabs(const double& x) {
			return (x < 0.0) ? -x : x; //std::fabs(x);
		}

		/** Integer abs */
		inline Math::intUNI abs(const Math::intUNI& x) {
			return (x < 0) ? -x : x;
		}

		inline double abs(const double& x) {
			return Common::Math::fabs(x);
		}

		/**********************************************************************/

		/**********************************************************************/

		inline Math::intUNI cmp(const double& x1, const double& x2, const double& eps) {
			if (Common::Math::abs(x1 - x2) < eps) {
				return 0;
			} else {
				if (x1 < x2) {
					return -1;
				} else {
					return 1;
				}
			}

			throw ErrMsgException<Message < string >> (string("Common::MathExt::cmp(const double x1, const double x2, const double eps) failed to compare values!"));
		}

		template<class T> inline const T& min(const T& x1, const T& x2) {
			return (x1 < x2) ? x1 : x2; //return std::min(x1, x2);
		}

		template <template<class, class...> class V, class T, class... otherT> inline const T& min(const V<T, otherT...>& v) {
			/*
						Math::intUNI n = v.size();
			
			#ifndef MATHEXT_NO_CHECKS
			
						if (n == 0) {
							throw ErrMsgException<Message<>>("Common::MathExt::min(const V<T> &v) the input vector is empty!");
						}

			#endif			

						if (n == 1) {
							return v[0];
						}

						Math::intUNI pos = 0;

						for (Math::intUNI i = 1; i < n; i++) {
							if (v[pos] > v[i]) {
								pos = i;
							}
						}

						return v[pos];
			 */

			Math::intUNI idx = minIdx(v);

			return v[idx];
		}

		template <template<class, class...> class V, class T, class... otherT> inline Math::intUNI minIdx(const V<T, otherT...>& v) {
			Math::intUNI n = (Math::intUNI) v.size();

#ifndef MATHEXT_NO_CHECKS

			if (n == 0) {
				throw ErrMsgException<Message < string >> (string("Common::MathExt::minIdx(const V<T> &v) the input vector is empty!"));
				return -1;
			}
#endif

			if (n == 1) {
				return 0;
			}

			Math::intUNI pos = 0;

			for (Math::intUNI i = 1; i < n; i++) {
				if (v[pos] > v[i]) {
					pos = i;
				}
			}

			return pos;
		}

		template<class T> inline const T& max(const T& x1, const T& x2) {
			return (x1 > x2) ? x1 : x2; //return std::max(x1, x2);
		}

		template <template<class, class...> class V, class T, class... otherT> const T& max(const V<T, otherT...>& v) {
			/*
			
				Math::intUNI n = v.size();

	#ifndef MATHEXT_NO_CHECKS			

				if (n == 0) {
					throw ErrMsgException<Message<>>("Common::MathExt::max(const V<T> &v) the input vector is empty!");
				}

	#endif			

				if (n == 1) {
					return v[0];
				}

				Math::intUNI pos = 0;

				for (Math::intUNI i = 1; i < n; i++) {
					if (v[pos] < v[i]) {
						pos = i;
					}
				}

				return v[pos];
			 */

			Math::intUNI idx = maxIdx(v);

			return v[idx];
		}

		template <template<class, class...> class V, class T, class... otherT> Math::intUNI maxIdx(const V<T, otherT...>& v) {
			Math::intUNI n = (Math::intUNI) v.size();
#ifndef MATHEXT_NO_CHECKS
			if (n == 0) {
				throw ErrMsgException<Message < string >> (string("Common::MathExt::max(const V<T> &v) the input vector is empty!"));
				return -1;
			}
#endif   

			if (n == 1) {
				return 0;
			}

			Math::intUNI pos = 0;

			for (Math::intUNI i = 1; i < n; i++) {
				if (v[pos] < v[i]) {
					pos = i;
				}
			}

			return pos;
		}

		/**********************************************************************/

		/**********************************************************************/

		template <template<class, class...> class V, class T, class... otherT> T& sum(V<T, otherT...>& v) {
			Math::intUNI n = (Math::intUNI) v.size();

#ifndef MATHEXT_NO_CHECKS   

			if (n == 0) {
				throw ErrMsgException<Message < string >> (string("Common::MathExt::sum(V<T>& v) : Summing an empty vector!!!"));
				return T();
			}

#endif   

			T res = v[0];

			for (Math::intUNI i = 1; i < n; i++) {
				res = res + v[i];
			}

			return res;
		}

		/**********************************************************************/

		/**********************************************************************/

		template <template<class, class...> class V, class T, class... otherT> void sort(V<T, otherT...>& v, const bool& asc) {
			// Sort all elements in v ascending
			//qSort(v);
			std::sort(v.begin(), v.end());

			if (!asc) { // Swap the elements
				reverseVec(v);
			}
		}

		template <template<class, class...> class V, class T, class... otherT> void stableSort(V<T, otherT...>& v, const bool& asc) {
			// Sort all elements in v ascending
			//qStableSort(v);
			std::stable_sort(v.begin(), v.end());

			if (!asc) { // Swap the elements
				reverseVec(v);
			}
		}

		/**********************************************************************/

		/**********************************************************************/

		template <template<class, class...> class V, class T, class... otherT> void reverseVec(V<T, otherT...>& v) {
			Math::intUNI n = (Math::intUNI) v.size();

			for (Math::intUNI i = 0; i < n / 2; i++) {
				Math::swap(v[i], v[n - 1 - i]);
			}

		}

		/**********************************************************************/

		/**********************************************************************/

		template <template<class, class...> class V, class T, class... otherT> void removeDuplicates(V<T, otherT...>& v) {
			Math::intUNI n = (Math::intUNI) v.size();
			V<T, otherT...> newV;
			std::set<Math::intUNI> posDel; // Positions to delete
			Math::intUNI lastPos;

			for (Math::intUNI i = 0; i < n - 1; i++) {
				for (Math::intUNI j = i + 1; j < n; j++) {
					if (v[i] == v[j]) {
						posDel.insert(j);
					}
				}
			}

			lastPos = 0;
			newV.resize(n - Math::intUNI(posDel.size()));
			for (Math::intUNI i = 0; i < n; i++) {
				if (posDel.find(i) == posDel.end()) { // Should not be removed
					newV[lastPos] = v[i];
					lastPos++;
				}
			}

			// Remove the last elements
			v = newV;

		}

		/**********************************************************************/

		/**********************************************************************/

		inline double round(const double& x) {
			return std::round(x); //std::floor(x + 0.5);
		}

		inline double ceil(const double& x) {
			return std::ceil(x);
		}

		inline double floor(const double& x) {
			return std::floor(x);
		}

		/**********************************************************************/

		/**********************************************************************/

		/*
		template <template<class,class> class V, class VA, class T> inline void randPermut(V<T,VA>& permut) {
			Math::intUNI n = permut.size();
			Math::intUNI i;
			Math::intUNI j;

			for (i = 1; i < n; i++) {
				j = qrand() % (i + 1);
				swap(permut[i], permut[j]);
			}
		}
		 */

		//template <class T> void randPermut(vector<T>& permut) {
		//	Math::intUNI n = permut.size();
		//	Math::intUNI i;
		//	Math::intUNI j;

		//	for (i = 1; i < n; i++) {
		//		j = qrand() % (i + 1);
		//		swap(permut[i], permut[j]);
		//	}
		//}

		template <template<class, class...> class V, class T, class... otherT> inline bool nextLexPermutation(V<T, otherT...>& array) {
			// Find the non-increasing suffix
			Math::intUNI length = array.size();
			Math::intUNI i = length - 1;

			while (i > 0 && array[i - 1] >= array[i]) {
				i--;
			}

			if (i <= 0) {
				return false;
			}

			// Find the successor to the pivot
			Math::intUNI j = length - 1;

			while (array[j] <= array[i - 1]) {
				j--;
			}

			// Swap the considered elements
			T tmp = array[i - 1];
			array[i - 1] = array[j];
			array[j] = tmp;

			// Reverse the suffix
			j = length - 1;
			while (i < j) {
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
				i++;
				j--;
			}

			return true;
		}

		/**********************************************************************/

		/**********************************************************************/

		inline Math::uint64 factorial(const Math::uintUNI& n) {
			Math::uint64 res = 1;

			for (Math::uintUNI i = 2; i <= n; i++) {
				res *= i;
			}

			return res;
		}

		/**********************************************************************/

	}

}

#endif /* MATHEXT_H */

