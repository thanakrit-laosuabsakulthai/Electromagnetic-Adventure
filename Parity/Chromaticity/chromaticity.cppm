export module Parity.Chromaticity;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
#endif

export namespace Parity
{

export struct Activate_Color_Effect : Rule {
	void execute(Overworld &world) override;
};

} // namespace Parity