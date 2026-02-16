export module Parity.Physiology;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include "type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.Biology;
	import Parity.World;
#endif

export namespace Parity
{

export inline std::string_view to_string(PlayerIdentity identity) {
using enum PlayerIdentity;
static const std::map<PlayerIdentity, std::string_view> identityToString = {
	{AmethystApprentice, "AmethystApprentice"},
	{SapphireSummoner, "SapphireSummoner"},
	{EmeraldEnchantress, "EmeraldEnchantress"},
	{OpalinOracle, "OpalinOracle"}
};

return identityToString.at(identity);
}

std::string_view Overworld::getActivePlayerName() {
	return to_string(active_player);
};


} // namespace Parity