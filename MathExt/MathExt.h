/* 
 * File:   MathExt.h
 * Author: DrSobik
 *
 * Created on July 25, 2014, 9:14 PM
 */

#ifndef MATHEXT_H
#define	MATHEXT_H

#include <cmath>
#include <vector>

#include "Exceptions"

using namespace Common::Exceptions;

using namespace std;

namespace Common {

	namespace Math {

		/**********************************************************************/

		typedef short int int16; // 16 bit
		typedef int int32; // 32 bit
		typedef long long int int64; // 64 bit

		typedef unsigned short uint16; // 16 bit
		typedef unsigned int uint32; // 32 bit
		typedef unsigned long long int uint64; // 64 bit

		/**********************************************************************/

		/**********************************************************************/

		const double E = 2.71828182845904523536028747135266249775724709369995; //M_E;
		const double Pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679; //M_PI;
		const double Pi_2 = Pi / 2.0; //M_PI_2;
		const double MAX_DOUBLE = 1e300;
		const double MIN_DOUBLE = -1e300;
		const double EPSILON = 1e-15;

		const int16 MAX_INT16 = int16((uint16(1) << 15) - 1); // 32767
		const int16 MIN_INT16 = ~MAX_INT16; // -32768
		const int32 MAX_INT = int32((uint32(1) << 31) - 1); // 2147483647
		const int32 MIN_INT = ~MAX_INT; // -2147483648
		const int64 MAX_INT64 = int64((uint64(1) << 63) - 1); // 9223372036854775807
		const int64 MIN_INT64 = ~MAX_INT64; // -9223372036854775808

		const uint16 MAX_UINT16 = uint16((uint32(1) << 16) - 1); // 65535
		const uint16 MIN_UINT16 = 0;
		const uint32 MAX_UINT = uint32((uint64(1) << 32) - 1); // 4294967295
		const uint32 MIN_UINT = 0;
		const uint64 MAX_UINT64 = uint64(((uint64(1) << 63) - 1) << 1) + 1; // 18446744073709551615
		const uint64 MIN_UINT64 = 0;

		/**********************************************************************/

		/**********************************************************************/
		template<class T> void swap(T& x, T& y);
		
		double pow(const double& x, const double& p);
		double pow(const double& x, const int& p);
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
		
		int iabs(const int& x);
		double fabs(const double& x);
		int abs(const int& x);
		double abs(const double& x);
		
		int cmp(const double& x1, const double& x2, const double& eps = Common::Math::EPSILON);
		
		template<class T> const T& min(const T& x1, const T& x2);
		template <template<class, class...> class V, class T, class... otherT> const T& min(const V<T, otherT...>& v);
		template <template<class, class...> class V, class T, class... otherT> int minIdx(const V<T, otherT...>& v);
		
		template<class T> const T& max(const T& x1, const T& x2);
		template <template<class, class...> class V, class T, class... otherT> const T& max(const V<T, otherT...>& v);
		template <template<class, class...> class V, class T, class... otherT> int maxIdx(const V<T, otherT...>& v);
		
		template <template<class, class...> class V, class T, class... otherT> T& sum(V<T, otherT...>& v);
		
		template <template<class, class...> class V, class T, class... otherT> void sort(V<T,otherT...>& v, const bool& asc = true);
		template <template<class, class...> class V, class T, class... otherT> void stableSort(V<T,otherT...>& v, const bool& asc = true);
		
		template <template<class, class...> class V, class T, class... otherT> void reverseVec(V<T,otherT...>& v);
		
		double round(const double& x);
		double ceil(const double& x);
		double floor(const double& x);
		
		template <template<class, class...> class V, class T, class... otherT> bool nextLexPermutation(V<T, otherT...>& array);
		
		unsigned long long int factorial(const int& n);
		/**********************************************************************/

		/**********************************************************************/

		/**********************************************************************/ 
		
		template<class T> void swap(T& x, T& y){
			T z = x;
			
			x = y;
			
			y = z;
		}
		
		/**********************************************************************/
		
		/**********************************************************************/
		
		inline double pow(const double& x, const double& p) {
			return std::pow(x, p);
		}

		inline double pow(const double& x, const int& p) {
			return std::pow(x, p);
		}

		inline double sqr(const double& x) {
			return std::pow(x, 2);
		}

		inline double sqrt(const double& x) {
#ifndef MATHEXT_NO_CHECKS
			if (x < 0.0) throw ErrMsgException<Message<>>("Common::MathExt::sqrt(const double x) negative argument!");
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
			if (cmp(x, 0.0, EPSILON) <= 0) throw ErrMsgException<Message<>>("Common::MathExt::lg(const double x) small/negative argument!");
#endif
			return std::log10(x);
		}

		inline double ln(const double& x) {
#ifndef MATHEXT_NO_CHECKS
			if (cmp(x, 0.0, EPSILON) <= 0) throw ErrMsgException<Message<>>("Common::MathExt::ln(const double x) small/negative argument!");
#endif
			return std::log(x);
		}

		inline double log(const double& base, const double& x) {
#ifndef MATHEXT_NO_CHECKS
			if (cmp(x, 0.0, EPSILON) <= 0) throw ErrMsgException<Message<>>("Common::MathExt::lg(const double x) small/negative argument!");
			if (cmp(base, 0.0, EPSILON) <= 0) throw ErrMsgException<Message<>>("Common::MathExt::lg(const double x) small/negative base!");
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
			if ((cmp(round(x / Pi_2), x / Pi_2, EPSILON) == 0) && (cmp(round(x / Pi), x / Pi, EPSILON) != 0)) throw ErrMsgException<Message<>>("Common::MathExt::tan(const double x) argument is multiplicity of Pi/2 !");
#endif
			return std::tan(x);
		}

		inline double cot(const double& x) {
#ifndef MATHEXT_NO_CHECKS
			if (cmp(round(x / Pi), x / Pi, EPSILON) == 0) throw ErrMsgException<Message<>>("Common::MathExt::cot(const double x) argument is multiplicity of Pi !");
			if (cmp(round(x / Pi_2), x / Pi_2, EPSILON) == 0) throw ErrMsgException<Message<>>("Common::MathExt::cot(const double x) argument is multiplicity of Pi/2 !");
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
		inline int iabs(const int& x) {
			return Common::Math::abs(x);
		}
		
		/** FP abs */
		inline double fabs(const double& x) {
			return (x < 0.0) ? -x : x; //std::fabs(x);
		}

		/** Integer abs */
		inline int abs(const int& x) {
			return (x < 0) ? -x : x;
		}

		inline double abs(const double& x) {
			return Common::Math::fabs(x);
		}

		/**********************************************************************/

		/**********************************************************************/

		inline int cmp(const double& x1, const double& x2, const double& eps) {
			if (Common::Math::abs(x1 - x2) < eps) {
				return 0;
			} else {
				if (x1 < x2) {
					return -1;
				} else {
					return 1;
				}
			}

			throw ErrMsgException<Message<>>("Common::MathExt::cmp(const double x1, const double x2, const double eps) failed to compare values!");
		}

		
		template<class T> inline const T& min(const T& x1, const T& x2) {
			return (x1 < x2) ? x1 : x2; //return std::min(x1, x2);
		}

		template <template<class, class...> class V, class T, class... otherT> inline const T& min(const V<T, otherT...>& v) {
			int n = v.size();
			
#ifndef MATHEXT_NO_CHECKS
			
			if (n == 0) {
				throw ErrMsgException<Message<>>("Common::MathExt::min(const V<T> &v) the input vector is empty!");
			}

#endif			

			if (n == 1) {
				return v[0];
			}

			int pos = 0;

			for (int i = 1; i < n; i++) {
				if (v[pos] > v[i]) {
					pos = i;
				}
			}

			return v[pos];
		}

		template <template<class, class...> class V, class T, class... otherT> inline int minIdx(const V<T, otherT...>& v) {
			int n = v.size();

			if (n == 0) {
				throw ErrMsgException<Message<>>("Common::MathExt::min(const V<T> &v) the input vector is empty!");
				return -1;
			}

			if (n == 1) {
				return 0;
			}

			int pos = 0;

			for (int i = 1; i < n; i++) {
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
			int n = v.size();

#ifndef MATHEXT_NO_CHECKS			
			
			if (n == 0) {
				throw ErrMsgException<Message<>>("Common::MathExt::max(const V<T> &v) the input vector is empty!");
			}

#endif			
			
			if (n == 1) {
				return v[0];
			}

			int pos = 0;

			for (int i = 1; i < n; i++) {
				if (v[pos] < v[i]) {
					pos = i;
				}
			}

			return v[pos];
		}

		template <template<class, class...> class V, class T, class... otherT> int maxIdx(const V<T, otherT...>& v) {
			int n = v.size();

			if (n == 0) {
				throw ErrMsgException<Message<>>("Common::MathExt::max(const V<T> &v) the input vector is empty!");
				return -1;
			}

			if (n == 1) {
				return 0;
			}

			int pos = 0;

			for (int i = 1; i < n; i++) {
				if (v[pos] < v[i]) {
					pos = i;
				}
			}

			return pos;
		}

		/**********************************************************************/

		/**********************************************************************/

		template <template<class, class...> class V, class T, class... otherT> T& sum(V<T, otherT...>& v) {
			int n = v.size();

#ifndef MATHEXT_NO_CHECKS			
			
			if (n == 0) {
				throw ErrMsgException<Message<>>("Common::MathExt::sum(V<T>& v) : Summing an empty vector!!!");
				return T();
			}
			
#endif			
			
			T res = v[0];

			for (int i = 1; i < n; i++) {
				res = res + v[i];
			}

			return res;
		}

		/**********************************************************************/
		
		/**********************************************************************/

		template <template<class, class...> class V, class T, class... otherT> void sort(V<T,otherT...>& v, const bool& asc) {
			// Sort all elements in v ascending
			qSort(v);

			if (!asc) { // Swap the elements
				reverseVec(v);
			}
		}

		template <template<class, class...> class V, class T, class... otherT> void stableSort(V<T,otherT...>& v, const bool& asc) {
			// Sort all elements in v ascending
			qStableSort(v);

			if (!asc) { // Swap the elements
				reverseVec(v);
			}
		}

		/**********************************************************************/
		
		/**********************************************************************/
		
		template <template<class, class...> class V, class T, class... otherT> void reverseVec(V<T,otherT...>& v){
			int n = v.size();
			
			for (int i = 0; i < n / 2; i++) {
					Math::swap(v[i], v[n - 1 - i]);
			}
			
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
			int n = permut.size();
			int i;
			int j;

			for (i = 1; i < n; i++) {
				j = qrand() % (i + 1);
				swap(permut[i], permut[j]);
			}
		}
		 */

		//template <class T> void randPermut(vector<T>& permut) {
		//	int n = permut.size();
		//	int i;
		//	int j;

		//	for (i = 1; i < n; i++) {
		//		j = qrand() % (i + 1);
		//		swap(permut[i], permut[j]);
		//	}
		//}

		template <template<class, class...> class V, class T, class... otherT> inline bool nextLexPermutation(V<T, otherT...>& array) {
			// Find the non-increasing suffix
			int length = array.size();
			int i = length - 1;

			while (i > 0 && array[i - 1] >= array[i]) {
				i--;
			}

			if (i <= 0) {
				return false;
			}

			// Find the successor to the pivot
			int j = length - 1;

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

		inline unsigned long long int factorial(const int& n) {
			unsigned long long int res = 1;

			for (int i = 2; i <= n; i++) {
				res *= i;
			}

			return res;
		}

		/**********************************************************************/

	}

}

#endif	/* MATHEXT_H */

