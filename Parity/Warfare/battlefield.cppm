export module Parity.Battlefield;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include "../type-definition.cppm"
#else
	import std;
	import Parity.DieRoll;
	import Parity.Biology;
	import Parity.Necrology;
#endif

export namespace Parity
{
//
export enum class BattleResult {
	PlayerWins,
	PlayerLoses,
	Draw
};

export struct Battlefield {
	DieRoll die_roll_for_combat_strength;
	DieRoll die_roll_for_attacker;
	DieRoll die_roll_for_defender;
	DieRoll advantage_die_roll_for_attacker;
	DieRoll advantage_die_roll_for_defender;
	
	PlayerIdentity combatant_player;
	DemonForm combatant_demon;
	
	bool advantage_of_player;
	bool advantage_of_demon;
	bool collimation_of_player;
	bool weakness_of_demon;
	
	int attack_power_modification_of_attacker;
	int attack_power_modification_of_defender;
	
	int attack_power_of_attacker;
	int attack_power_of_defender;
	int combat_strength_of_attacker;
	int combat_strength_of_defender;
	int attack_value_of_attacker;
	int attack_value_of_defender;
	
	BattleResult battle_result;
	
	DemonMalignity malignity = MalignityOfDemonForm;
};

} // namespace Parity
