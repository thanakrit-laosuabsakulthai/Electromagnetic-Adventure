export module Parity.Biology;

#if defined(__INTELLISENSE__)
	#include <map>
	#include <set>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.Optoelectronic;
#endif

export namespace Parity
{

export enum class PlayerIdentity {
	AmethystApprentice,
	SapphireSummoner,
	EmeraldEnchantress,
	OpalinOracle
};

export struct PlayerPosession {
	int gold_coin = 0;
	int permanent_power_point = 1;
	int vitality_heart = 5;
	int vitality_maximum_heart = 5;
	Iridescent active_optical_effect;
	Inventory inventory;
	int inventory_capacity = 4;
};

export using Treasury = std::map<PlayerIdentity, PlayerPosession>;
export using Humanity = std::set<PlayerIdentity>;

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


} // namespace Parity


/* 

*» **AmethystApprentice** joined the game.*
*» **SapphireSummoner** joined the game.*
~~*» **EmeraldEnchantress** joined the game.*~~
~~*» **OpalinOracle** joined the game.*~~

- **Status Effect**
	- electromagnetic:advantage
	- electromagnetic:weakness
	- electromagnetic:repulsion
	- electromagnetic:chromatic
	- electromagnetic:collimation

	- **Material**
	- electromagnetic:vitality_heart
	- electromagnetic:vitality_maximum_heart
	- electromagnetic:gold_coin
	- electromagnetic:permanent_power

 */