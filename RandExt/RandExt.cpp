#include "RandExt.h"

using namespace Common::Rand;

namespace Common{
	
	namespace Rand{
		
		thread_local RandGenMT RNG(1872638163);
		
	}
}


