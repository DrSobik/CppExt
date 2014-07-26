/* 
 * File:   MathExt.h
 * Author: DrSobik
 *
 * Created on July 25, 2014, 9:14 PM
 */

#ifndef MATHEXT_H
#define	MATHEXT_H

#include <cmath>
#include <limits.h>
#include <vector>

#include "Exceptions"

using namespace Common::Exceptions;

using namespace std;

namespace Common {

	namespace Math {

		/**********************************************************************/

		int rSeed = 0; // Initial seed 

		const double E = 2.71828182845904523536028747135266249775724709369995; //M_E;
		const double Pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679; //M_PI;
		const double Pi_2 = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679 / 2.0; //M_PI_2;
		const double MAX_DOUBLE = 1e300;
		const double MIN_DOUBLE = -1e300;
		const int MAX_INT = INT_MAX;
		const int MIN_INT = INT_MIN;
		const double EPSILON = 1e-15;

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
#ifdef DEBUG
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
#ifdef DEBUG
			if (cmp(x, 0.0, EPSILON) <= 0) throw ErrMsgException<Message<>>("Common::MathExt::lg(const double x) small/negative argument!");
#endif
			return std::log10(x);
		}

		inline double ln(const double& x) {
#ifdef DEBUG
			if (cmp(x, 0.0, EPSILON) <= 0) throw ErrMsgException<Message<>>("Common::MathExt::ln(const double x) small/negative argument!");
#endif
			return std::log(x);
		}

		inline double log(const double& base, const double& x) {
#ifdef DEBUG
			if (cmp(x, 0.0, EPSILON) <= 0) throw ErrMsgException<Message<>>("Common::MathExt::lg(const double x) small/negative argument!");
			if (cmp(base, 0.0, EPSILON) <= 0) throw ErrMsgException<Message<>>("Common::MathExt::lg(const double x) small/negative base!");
#endif
			return ln(x) / ln(base);
		}

		/**********************************************************************/

		/**********************************************************************/

		template <template<class> class V, class T> T& sum(V<T>& v) {
			int n = v.size();

			if (n == 0) {
				throw ErrMsgException<Message<>>("Common::MathExt::sum(V<T>& v) : Summing an empty vector!!!");
				return T();
			}

			T res = v[0];

			for (int i = 1; i < n; i++) {
				res = res + v[i];
			}

			return res;
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
#ifdef DEBUG
			if ((cmp(round(x / Pi_2), x / Pi_2, EPSILON) == 0) && (cmp(round(x / Pi), x / Pi, EPSILON) != 0)) throw ErrMsgException<Message<>>("Common::MathExt::tan(const double x) argument is multiplicity of Pi/2 !");
#endif
			return std::tan(x);
		}

		inline double cot(const double& x) {
#ifdef DEBUG
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

		/** FP abs */
		inline double fabs(const double& x) {
			return (x < 0.0) ? -x : x;//std::fabs(x);
		}

		/** Integer abs */
		inline int abs(const int& x) {
			return (x < 0) ? -x : x;
		}
		
		/** Integer abs */
		inline int iabs(const int& x) {
			return Common::Math::abs(x);
		}

		inline double abs(const double& x) {
			return Common::Math::fabs(x);
		}

		/**********************************************************************/

		/**********************************************************************/

		inline int cmp(const double& x1, const double& x2, const double& eps = Common::Math::EPSILON) {
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
			return (x1 < x2) ? x1 : x2;	//return std::min(x1, x2);
		}

		template <template<class> class V, class T> inline const T& min(const V<T>& v) {
			int n = v.size();

			if (n == 0) {
				throw ErrMsgException<Message<>>("Common::MathExt::min(const V<T> &v) the input vector is empty!");
			}

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

		template <template<class> class V, class T> inline int minIdx(const V<T>& v) {
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

		template <template<class> class V, class T> const T& max(const V<T>& v) {
			int n = v.size();

			if (n == 0) {
				throw ErrMsgException<Message<>>("Common::MathExt::max(const V<T> &v) the input vector is empty!");
			}

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

		template <template<class> class V, class T> int maxIdx(const V<T>& v) {
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

		template <template<class> class V, class T> void sort(V<T>& v, const bool& asc = true) {
			// Sort all elements in v ascending
			qSort(v);

			if (!asc) { // Swap the elements
				for (int i = 0; i < v.size() / 2; i++) {
					qSwap(v[i], v[v.size() - 1 - i]);
				}
			}
		}

		template <template<class> class V, class T> void stableSort(V<T>& v, const bool& asc = true) {
			// Sort all elements in v ascending
			qStableSort(v);

			if (!asc) { // Swap the elements
				for (int i = 0; i < v.size() / 2; i++) {
					qSwap(v[i], v[v.size() - 1 - i]);
				}
			}
		}

		/**********************************************************************/

		/**********************************************************************/

		inline void rndSeed(const int& s) {
			qsrand(s); //std::srand(s);

			rSeed = s; // Preserve the initial random seed
		}

		inline int rndSeed() {
			return rSeed;
		}

		inline int rndInt() {
			return qrand(); //std::rand();
		}

		inline int rndInt(const int& start, const int& finish) {
			return start + round((double) rndInt() / (double) RAND_MAX * (double) (finish - start));
		}

		inline double rndDouble() {
			return (double) qrand() / double(RAND_MAX);
		}

		inline double rndDouble(const double& start, const double& finish) {
			return start + (finish - start) * rndDouble();
		}

		/**********************************************************************/

		/**********************************************************************/

		inline double round(const double& x) {
			return std::floor(x + 0.5);
		}

		inline double ceil(const double& x) {
			return std::ceil(x);
		}

		inline double floor(const double& x) {
			return std::floor(x);
		}

		/**********************************************************************/

		/**********************************************************************/

		template <template<class> class V, class T> inline int probSelect(const V<T>& prob, const T& probPow = 1.0) {
			int n = prob.size();
			T total;
			vector<T> intBegin;
			vector<T> intEnd;

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

			T point = rndDouble(0.0, total);

			int i = 0;
			for (i = 0; i < n; i++) {
				if (intBegin[i] < point && point <= intEnd[i]) {
					break;
				}
			}

			if (i == n) {
				throw ErrMsgException<Message<>>("Common::MathExt::probSelect : Failed to find interval with the point selecting randomly!");
				return rndInt(0, n - 1);
			}

			return i;
		}
		
		/**********************************************************************/

		/**********************************************************************/

		template <template<class> class V, class T> inline void randPermut(V<T>& permut) {
			int n = permut.size();
			int i;
			int j;

			for (i = 1; i < n; i++) {
				j = qrand() % (i + 1);
				swap(permut[i], permut[j]);
			}
		}

		//template <class T> void randPermut(vector<T>& permut) {
		//	int n = permut.size();
		//	int i;
		//	int j;

		//	for (i = 1; i < n; i++) {
		//		j = qrand() % (i + 1);
		//		swap(permut[i], permut[j]);
		//	}
		//}

		template <template<class> class V, class T> inline bool nextLexPermutation(V<T>& array) {
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

