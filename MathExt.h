/* 
 * File:   Math.h
 * Author: DrSobik
 *
 * Created on February 23, 2010, 11:52 AM
 * Description: A class with basic mathematics in it (for convenience)
 */

#ifndef _SMATH_H
#define	_SMATH_H

#include "DebugExt.h"

#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <complex>
#include <limits>
#include <limits.h>

#include <vector>

#include <QtCore>
//#include <QtAlgorithms>

using namespace std;
using namespace Common;

namespace Common {

	class Math {
	private:
		static int rSeed; // Initial seed for randomization

	public:
		static const double E;
		static const double Pi;
		static const double Pi_2;
		static const double MAX_DOUBLE;
		static const double MIN_DOUBLE;
		static const int MAX_INT;
		static const int MIN_INT;
		static const double EPSILON;

		/** Power. */
		static double pow(const double& x, const double& p);
		static double pow(const double& x, const int& p);

		/** Square/Square root. */
		static double sqr(const double& x);
		static double sqrt(const double& x);

		/** Summing the elements of some vector. */
		template <template<class> class V, class T> static T& sum(V<T>& v);

		/** Direct and inverse trigonometric functions. */
		static double sin(const double& x);
		static double cos(const double& x);
		static double tan(const double& x);
		static double cot(const double& x);
		static double arcsin(const double& x);
		static double arccos(const double& x);
		static double arctan(const double& x);
		static double arccot(const double& x);

		/** Exponent */
		static double exp(const double& x);

		/** Logarihms. */
		static double lg(const double& x);
		static double ln(const double& x);
		static double log(const double& base, const double& x);

		/** Float abs. */
		static double fabs(const double& x);
		/** Integer abs. */
		static int iabs(int& x);
		static double abs(const double& x);
		static int abs(const int& x);

		/** Compare two numbers. */
		static int cmp(const double& x1, const double& x2, const double& eps);

		/** Min routines. */
		static double min(const double& x1, const double& x2);
		static int min(const int& x1, const int& x2);
		template <template<class> class V, class T> static T& min(V<T>& v);
		template <template<class> class V, class T> static int minIdx(V<T>& v);

		/** Max routines. */
		static double max(const double& x1, const double& x2);
		static int max(const int& x1, const int& x2);
		template <template<class> class V, class T> static T& max(V<T>& v);
		template <template<class> class V, class T> static int maxIdx(V<T>& v);

		/** Sorting */
		template <template<class> class V, class T> static void sort(V<T>& v, const bool& asc);
		template <template<class> class V, class T> static void stableSort(V<T>& v, const bool& asc);

		/** Random numbers routines. */
		static void rndSeed(const int& s);
		static int rndSeed();
		static int rndInt();
		static int rndInt(const int& start, const int& finish);
		static double rndDouble();
		static double rndDouble(const double& start, const double& finish);

		/** Select an element index from the array based on the given probabilities. */
		template <template<class> class V, class T> static int probSelect(V<T>& probabilities, const T& probPow);

		/** Rounding and Co. */
		static double round(const double& x);
		static double ceil(const double& x);
		static double floor(const double& x);

		/** Permutations. */

		/** Random permutation of the vector. */
		template <template<class> class V, class T> static void randPermut(V<T>& permut);

		template <class T> static void randPermut(vector<T>& permut);

		/** Next lexicographical permutation. Returns "false" if it is not possible. */
		template <template<class> class V, class T> static bool nextLexPermutation(V<T>& array);

		/** Combinatorics. */

		/** Factorial. */
		static unsigned long long int factorial(const int& n);
	};

	/*-----------------------  Inlined implementation  ---------------------------*/

	inline double Math::pow(const double& x, const double& p) {
		return std::pow(x, p);
	}

	inline double Math::pow(const double& x, const int& p) {
		return std::pow(x, p);
	}

	inline double Math::sqr(const double& x) {
		return std::pow(x, 2);
	}

	inline double Math::sqrt(const double& x) {
#ifdef DEBUG
		if (x < 0.0) Debugger::eDebug("Math::sqrt(const double x) negative argument!");
#endif
		return std::sqrt(x);
	}

	inline double Math::exp(const double& x) {
		return std::exp(x);
	}

	inline double Math::lg(const double& x) {
#ifdef DEBUG
		if (Math::cmp(x, 0.0, Math::EPSILON) <= 0) Debugger::eDebug("Math::lg(const double x) small/negative argument!");
#endif
		return std::log10(x);
	}

	inline double Math::ln(const double& x) {
#ifdef DEBUG
		if (Math::cmp(x, 0.0, Math::EPSILON) <= 0) Debugger::eDebug("Math::ln(const double x) small/negative argument!");
#endif
		return std::log(x);
	}

	inline double Math::log(const double& base, const double& x) {
#ifdef DEBUG
		if (Math::cmp(x, 0.0, Math::EPSILON) <= 0) Debugger::eDebug("Math::lg(const double x) small/negative argument!");
		if (Math::cmp(base, 0.0, Math::EPSILON) <= 0) Debugger::eDebug("Math::lg(const double x) small/negative base!");
#endif
		return ln(x) / ln(base);
	}

	template <template<class> class V, class T> T& Math::sum(V<T>& v) {
		int n = v.size();

		if (n == 0) {
			Debugger::wDebug("Math::sum(V<T> &v) summing an empty vector!");
			return T();
		}

		T res = v[0];

		for (int i = 1; i < n; i++) {
			res = res + v[i];
		}

		return res;
	}

	inline double Math::sin(const double& x) {
		return std::sin(x);
	}

	inline double Math::cos(const double& x) {
		return std::cos(x);
	}

	inline double Math::tan(const double& x) {
#ifdef DEBUG
		if ((Math::cmp(round(x / Math::Pi_2), x / Math::Pi_2, Math::EPSILON) == 0) && (Math::cmp(round(x / Math::Pi), x / Math::Pi, Math::EPSILON) != 0)) Debugger::wDebug("Math::tan(const double x) argument is multiplicity of Pi/2 !");
#endif
		return std::tan(x);
	}

	inline double Math::cot(const double& x) {
#ifdef DEBUG
		if (Math::cmp(round(x / Math::Pi), x / Math::Pi, Math::EPSILON) == 0) Debugger::wDebug("Math::cot(const double x) argument is multiplicity of Pi !");
		if (Math::cmp(round(x / Math::Pi_2), x / Math::Pi_2, Math::EPSILON) == 0) Debugger::wDebug("Math::cot(const double x) argument is multiplicity of Pi/2 !");
#endif
		return 1.0 / Math::tan(x);
	}

	inline double Math::arcsin(const double& x) {
		return std::asin(x);
	}

	inline double Math::arccos(const double& x) {
		return std::acos(x);
	}

	inline double Math::arctan(const double& x) {
		return std::atan(x);
	}

	inline double Math::arccot(const double& x) {
		return Math::Pi_2 - Math::arctan(x);
	}

	inline double Math::fabs(const double& x) {
		return std::fabs(x);
	}

	/** Integer abs */
	inline int Math::iabs(int& x) {
		return abs(x);
	}

	inline double Math::abs(const double& x) {
		return Math::fabs(x);
	}

	inline int Math::abs(const int& x) {
		return (x < 0) ? -x : x;
	}

	inline int Math::cmp(const double& x1, const double& x2, const double& eps = Math::EPSILON) {
		if (Math::abs(x1 - x2) < eps) {
			return 0;
		} else {
			if (x1 < x2) {
				return -1;
			} else {
				return 1;
			}
		}

		Debugger::eDebug("Math::cmp(const double x1, const double x2, const double eps) failed to compare values!");
	}

	inline double Math::min(const double& x1, const double& x2) {
		return std::min(x1, x2);
	}

	inline int Math::min(const int& x1, const int& x2) {
		return std::min(x1, x2);
	}

	template <template<class> class V, class T> T& Math::min(V<T>& v) {
		int n = v.size();

		if (n == 0) {
			Debugger::wDebug("Math::min(V<T> &v) the input vector is empty!");
			return T();
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

	template <template<class> class V, class T> int Math::minIdx(V<T>& v) {
		int n = v.size();

		if (n == 0) {
			Debugger::wDebug("Math::min(V<T> &v) the input vector is empty!");
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

	inline double Math::max(const double& x1, const double& x2) {
		return std::max(x1, x2);
	}

	inline int Math::max(const int& x1, const int& x2) {
		return std::max(x1, x2);
	}

	template <template<class> class V, class T> T& Math::max(V<T>& v) {
		int n = v.size();

		if (n == 0) {
			Debugger::wDebug("Math::max(V<T> &v) the input vector is empty!");
			return T();
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

	template <template<class> class V, class T> int Math::maxIdx(V<T>& v) {
		int n = v.size();

		if (n == 0) {
			Debugger::wDebug("Math::max(V<T> &v) the input vector is empty!");
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

	template <template<class> class V, class T> void Math::sort(V<T>& v, const bool& asc = true) {
		// Sort all elements in v ascending
		qSort(v);

		if (!asc) { // Swap the elements
			for (int i = 0; i < v.size() / 2; i++) {
				qSwap(v[i], v[v.size() - 1 - i]);
			}
		}
	}

	template <template<class> class V, class T> void Math::stableSort(V<T>& v, const bool& asc = true) {
		// Sort all elements in v ascending
		qStableSort(v);

		if (!asc) { // Swap the elements
			for (int i = 0; i < v.size() / 2; i++) {
				qSwap(v[i], v[v.size() - 1 - i]);
			}
		}
	}

	inline void Math::rndSeed(const int& s) {
		qsrand(s); //std::srand(s);

		rSeed = s; // Preserve the initial random seed
	}

	inline int Math::rndSeed() {
		return rSeed;
	}

	inline int Math::rndInt() {
		return qrand(); //std::rand();
	}

	inline int Math::rndInt(const int& start, const int& finish) {
		return start + round((double) Math::rndInt() / (double) RAND_MAX * (double) (finish - start));
	}

	inline double Math::rndDouble() {
		return (double) qrand() / double(RAND_MAX);
	}

	inline double Math::rndDouble(const double& start, const double& finish) {
		return start + (finish - start) * Math::rndDouble();
	}

	inline double Math::round(const double& x) {
		return std::floor(x + 0.5);
	}

	inline double Math::ceil(const double& x) {
		return std::ceil(x);
	}

	inline double Math::floor(const double& x) {
		return std::floor(x);
	}

	template <template<class> class V, class T> int Math::probSelect(V<T>& prob, const T& probPow = 1.0) {
		int n = prob.size();
		T total;
		vector<T> intBegin;
		vector<T> intEnd;

		intBegin.resize(n);
		intEnd.resize(n);

		total = 0.0;

		for (int i = 0; i < n; i++) {
			intBegin[i] = total;
			intEnd[i] = total + Math::pow(prob[i], probPow);
			//Debugger::info << prob[i] << " - " << probPow << "-" << ENDL;
			total = intEnd[i]; //+= Math::pow(prob[i], probPow);
		}

		//for (int i = 0; i < n; i++) {
		//    Debugger::info << intBegin[i] << " - " << intEnd[i] << ENDL;
		//    getchar();
		//}

		T point = Math::rndDouble(0.0, total);

		int i = 0;
		for (i = 0; i < n; i++) {
			if (intBegin[i] < point && point <= intEnd[i]) {
				break;
			}
		}

		if (i == n) {
			Debugger::warn << "Math::probSelect : Failed to find interval with the point selecting randomly!" << ENDL;
			return Math::rndInt(0, n - 1);
		}

		return i;
	}

	template <template<class> class V, class T> void Math::randPermut(V<T>& permut) {
		int n = permut.size();
		int i;
		int j;

		for (i = 1; i < n; i++) {
			j = qrand() % (i + 1);
			swap(permut[i], permut[j]);
		}
	}

	template <class T> void Math::randPermut(vector<T>& permut) {
		int n = permut.size();
		int i;
		int j;

		for (i = 1; i < n; i++) {
			j = qrand() % (i + 1);
			swap(permut[i], permut[j]);
		}
	}

	template <template<class> class V, class T> bool Math::nextLexPermutation(V<T>& array) {
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

	inline unsigned long long int Math::factorial(const int& n) {
		unsigned long long int res = 1;

		for (int i = 2; i <= n; i++) {
			res *= i;
		}

		return res;
	}

};

#endif	/* _SMATH_H */

