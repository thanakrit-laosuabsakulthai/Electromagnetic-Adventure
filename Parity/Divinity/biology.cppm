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
	
# Shop (Items cost Gold Coins)

1.  **Radio Waves (2 Gold):** Use this item to call for support. Trigger the Lucky Board once.
2.  **Microwaves (2 Gold):** Use this item *after* winning a combat to cook the demon's meat. Heal 1 Heart upon consumption.
3.  **Infrared Waves (1 Gold):** Use this item to detect a demon's heat signature weakness. Reduce the demon's Power by 1 for that combat.
4.  **Light Waves (3 Gold):** Use this item when landing on a Gradient space to choose the color effect instead of rolling the die for that turn's resolution.
    *   Pink-Orange-Yellow Gradient: Choose Pink, Orange, or Yellow effect.
    *   Red-Purple Gradient: Choose Red or Purple effect.
    *   White-Gray Gradient: Choose *any* non-gradient color effect. The space retains this chosen color effect until changed again by this item.
5.  **Ultraviolet Waves (5 Gold):** Use this item when entering a space with a demon. The demon retreats 1 space, and combat does not occur. This item cannot be used in the Demon Zone.
6.  **X-Rays (5 Gold):** Use this item to scan a demon's internal structure. The player gains ==Advantage== status for that combat. When a player has this status, they roll 2 dice and use the higher result multiplied by their Power for their Attack Value.
7.  **Gamma Rays (10 Gold):** Use this item in combat. The player's Power increases by 10 for that combat, and their attack hits *all* demons in the space.

 */