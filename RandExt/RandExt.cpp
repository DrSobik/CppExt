#include "RandExt.h"

using namespace Common::Rand;

namespace Common{
	
	namespace Rand{
		
		//thread_local RandGenMT RNG(1872638163);
		
		thread_local MT19937<Math::uint32> iRNG((1872638163)); // For generation of integers
		thread_local MT19937<double> fRNG(1872638163); // For generation of floats
		
	}
}


