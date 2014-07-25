/* 
 * File:   Math.cpp
 * Author: DrSobik
 * 
 * Created on February 23, 2010, 11:52 AM
 */

#include <complex>
#include <cmath>
#include <algorithm>

#include "MathExt.h"

namespace Common {

int Math::rSeed = 0; // Initial seed 
	
const double Math::E = 2.71828182845904523536028747135266249775724709369995;//M_E;
const double Math::Pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;//M_PI;
const double Math::Pi_2 = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679 / 2.0;//M_PI_2;
const double Math::MAX_DOUBLE = 1e300;
const double Math::MIN_DOUBLE = -1e300;
const int Math::MAX_INT = INT_MAX;
const int Math::MIN_INT = INT_MIN;
const double Math::EPSILON = 1e-15;


}
