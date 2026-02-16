export module Parity.Expedition;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <unordered_map>
	#include "type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.Geography;
	import Parity.Announcement;
	import Parity.Notation;
#endif

export namespace Parity {


export struct Expedition
{
	Landmark landmark_of_beginning = Landmark::DiamondOfCattail;
};

export using PlayerLocation = std::unordered_map<PlayerIdentity, Landmark>;



} // namespace Parity







