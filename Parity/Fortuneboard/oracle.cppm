export module Parity.Oracle;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	
	import Parity.DieRoll;
#endif

export namespace Parity
{
//
DieRoll Overworld::fatesAndCertainty() {
	// if certainty is empty, use rand for the return value
	if (certainty.empty()) {
		return static_cast<DieRoll>((std::rand() % 6) + 1);
	} else {
		// otherwise, pop the front value from certainty and return it as a DieRoll
		int certainty_value = certainty.front();
		certainty.pop_front();
		
		// Ensure the popped value is within the valid range of 1 to 6
		if (certainty_value < 1) {
			certainty_value = 1;
		} else if (certainty_value > 6) {
			certainty_value = 6;
		}
		
		return static_cast<DieRoll>(certainty_value);
	}
}
} // namespace Parity






























