export module Parity.Biology;

#if defined(__INTELLISENSE__)
	#include <unordered_set>
	#include <unordered_map>
	#include <string>
	export using namespace Parity;
#else
	import std; // Standard library import
#endif

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

export namespace Parity
{

export enum class PlayerIdentity {
	AmethystApprentice,
	SapphireSummoner,
	EmeraldEnchantress,
	OpalinOracle
};

export enum class OpticalEffect {
	Advantage,
	Weakness,
	Repulsion,
	Chromatic,
	Collimation
};

export struct PlayerPosession {
	int gold_coin = 0;
	int permanent_power_point = 1;
	int vitality_heart = 5;
	int vitality_maximum_heart = 5;
	std::unordered_set<OpticalEffect> active_optical_effect;
};

export using Humanity = std::unordered_map<PlayerIdentity, PlayerPosession>;

export constexpr std::string_view to_string(PlayerIdentity identity) {
	using enum PlayerIdentity;
	switch (identity) {
	case AmethystApprentice:
		return "Amethyst Apprentice";
	case SapphireSummoner:
		return "Sapphire Summoner";
	case EmeraldEnchantress:
		return "Emerald Enchantress";
	case OpalinOracle:
		return "Opalin Oracle";
	}
	return "Unknown PlayerIdentity";
}

} // namespace Parity
