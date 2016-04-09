#include "RandExt.h"

using namespace Common::Rand;

namespace Common{
	
	namespace Rand{
		
		//thread_local RandGenMT RNG(1872638163);
		
		thread_local iRNGType iRNG(1872638163); // For generation of integers
		thread_local fRNGType fRNG(1872638163); // For generation of floats
		
	}
}


