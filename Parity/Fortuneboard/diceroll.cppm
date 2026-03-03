export module Parity.DieRoll;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <deque>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
#endif




export namespace Parity {

export enum class DieRoll : int
{
	One = 1,
	Two,
	Three,
	Four,
	Five,
	Six
};

export using Certainty = std::deque<int>;

} // namespace Parity