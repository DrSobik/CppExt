#include "test.h"

Test::Test(){
	Rand::rndSeed(123);
	
	Signal<void, int> testSignal;
	
}

Test::~Test(){
	
}
