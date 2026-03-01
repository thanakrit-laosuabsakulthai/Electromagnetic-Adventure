export module Parity.Physiology;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	
	import Parity.Biology;
	import Parity.Optoelectronic;
#endif

export namespace Parity
{


/* - *Inflicted damage of 1 vitality heart to SapphireSummoner*
1.  **Player Characters:** All have Base Power = 1, Maximum Hearts = 5.
Each can hold up to 4 items. If a player dies (reaches 0 Hearts), they return to the Pink Diamond space and lose *all* their Gold and Items.
*/

// +++------>>> physiology.cppm <<<------+++

export struct Execute_As : Rule {
	PlayerIdentity executor;
	Execute_As(PlayerIdentity executor_identity) : executor(executor_identity) {}
	void execute(Overworld &world) override;
};

export struct Relinquish_Execution : Rule {
	void execute(Overworld &world) override;
};

export struct Respawn : Rule {
	void execute(Overworld &world) override;
};

export struct Vitality_Death : Rule {
	void execute(Overworld &world) override;
};

export struct Vitality_Hurt : Rule {
	int amount_of_damage;
	
	Vitality_Hurt(int damage) : amount_of_damage(damage) {}
	void execute(Overworld &world) override;
};
export struct Vitality_Hurt_Humanity : Rule {
	int amount_of_damage;
	
	Vitality_Hurt_Humanity(int damage) : amount_of_damage(damage) {}
	void execute(Overworld &world) override;
};
export struct Vitality_Heal : Rule {
	int amount_of_healing;
	
	Vitality_Heal(int healing) : amount_of_healing(healing) {}
	void execute(Overworld &world) override;
};
export struct Gain_Gold_Coin : Rule
{
	int amount_of_gold_coin;
	Gain_Gold_Coin(int amount) : amount_of_gold_coin(amount) {}
	void execute(Overworld &world) override;
};
export struct Gain_Permanent_Power_Point : Rule {
	int amount_of_permanent_power;
	Gain_Permanent_Power_Point(int amount) : amount_of_permanent_power(amount) {}
	void execute(Overworld &world) override;
};
export struct Take_Gold_Coin : Rule
{
	int amount_of_gold;
	
	Take_Gold_Coin(int amount) : amount_of_gold(amount) {}
	void execute(Overworld &world) override;
};

export struct Gain_Optical_Item : Rule
{
	Optics optical_item;
	int quantity;
	
	Gain_Optical_Item(Optics item, int quantity) : optical_item(item), quantity(quantity) {}
	void execute(Overworld &world) override;
};

export struct Take_Optical_Item : Rule
{
	Optics optical_item;
	int quantity;
	
	Take_Optical_Item(Optics item, int quantity) : optical_item(item), quantity(quantity) {}
	void execute(Overworld &world) override;
};

export struct Gain_Optical_Effect : Rule
{
	OpticalEffect optical_effect;
	Gain_Optical_Effect(OpticalEffect effect) : optical_effect(effect) {}
	void execute(Overworld &world) override;
};

export struct Take_Optical_Effect : Rule
{
	OpticalEffect optical_effect;
	Take_Optical_Effect(OpticalEffect effect) : optical_effect(effect) {}
	void execute(Overworld &world) override;
};

export struct Take_All_Optical_Effects : Rule
{
	void execute(Overworld &world) override;
};

} // namespace Parity