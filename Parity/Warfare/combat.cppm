export module Parity.Combat;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.Biology;
	import Parity.Necrology;
	import Parity.Battlefield;
	import Parity.Optoelectronic;
	import Parity.OpticalNotation;
	
	import Parity.Warfare;
	import Parity.Physiology;
	import Parity.ScoutFly;
	import Parity.Marketplace;
	import Parity.Adventure;
#endif

export namespace Parity
{
//

void Discord_Of_Beligerence::execute(Overworld &world) {	
	Battlefield &battlefield = world.battlefield;
	battlefield.combatant_player = world.active_player;
	battlefield.combatant_demon = world.getActiveDemonForm();
	
	world.announce.action(std::format("{} engages in combat with the {}",
		world.getActivePlayerName(),
		std::string(to_string(battlefield.combatant_demon))
	));
	world.announce.suspense(1); // quiet if world.announce.suspense_level > 1
}

void Warfare_Iridescence::execute(Overworld &world) {
	PlayerIdentity active_player = world.active_player;
	PlayerPosession &active_player_posession = world.playerbase[active_player];
	Iridescent active_player_iridescence = active_player_posession.active_optical_effect;
	
	Landmark landmark_of_active_demon = world.getLandmarkOfActiveDemon();
	
	Battlefield &battlefield = world.battlefield;
	
	battlefield.advantage_of_player = active_player_iridescence.contains(OpticalEffect::Advantage);
	battlefield.collimation_of_player = active_player_iridescence.contains(OpticalEffect::Collimation);
	// if the player has Ascendancy, the demon will have weakness
	battlefield.weakness_of_demon = active_player_iridescence.contains(OpticalEffect::Ascendancy);
	// if the demon in a demon zone, the demon will have advantage
	battlefield.advantage_of_demon = is_demon_zone(world.atlas[landmark_of_active_demon].zone);
}

void Media_Of_Warfare_Iridescence::execute(Overworld &world) {
	Battlefield &battlefield = world.battlefield;
	
	bool player_has_combat_effect = battlefield.advantage_of_player || battlefield.collimation_of_player;
	bool demon_has_combat_effect = battlefield.advantage_of_demon || battlefield.weakness_of_demon;
	
	if (!player_has_combat_effect && !demon_has_combat_effect) {
		return; // No combat effects to announce
	}
	
	world.announce.linger("Activating combat effects...");
	
	if (player_has_combat_effect) {
		world.announce.overhang(std::format("{} has {} {}",
			world.getActivePlayerName(),
			battlefield.advantage_of_player ? bold("Advantage") : "",
			battlefield.collimation_of_player ? bold("Collimation") : ""
		));
	}
	
	if (demon_has_combat_effect) {
		world.announce.overhang(std::format("{} has {} {}",
			std::string(to_string(battlefield.combatant_demon)),
			battlefield.advantage_of_demon ? bold("Advantage") : "",
			battlefield.weakness_of_demon ? bold("Weakness") : ""
		));
	}
}

/* 
if the player has Ascendancy, the electric minion will have weakness
- Activating combat effects…
	- SapphireSummoner: ==Advantage==, ==Collimation==
	- Electric Minion: ==Advantage==, ==Weakness==
*/

// calculate attack power including modifications from effects
void Read_Attack_Power::execute(Overworld &world) {
	Battlefield &battlefield = world.battlefield;
	
	PlayerPosession &attacker_posession = world.playerbase[battlefield.combatant_player];
	DemonMalignity malignity_of_demon = battlefield.malignity;
	
	int normal_attack_power_of_attacker = attacker_posession.permanent_power_point;
	int normal_attack_power_of_defender = battlefield.malignity.at(battlefield.combatant_demon);
	
	int attack_power_modification_of_attacker = 0;
	int attack_power_modification_of_defender = 0;
	
	// Apply combat effects of player
	if (battlefield.collimation_of_player) {
		attack_power_modification_of_attacker += 10; // Collimation grants +10 attack power
	}
	// Apply combat effects of demon
	if (battlefield.weakness_of_demon) {
		attack_power_modification_of_defender -= 1; // Weakness reduces demon's attack power by 1
	}
	
	int attack_power_of_attacker = normal_attack_power_of_attacker + attack_power_modification_of_attacker;
	int attack_power_of_defender = normal_attack_power_of_defender + attack_power_modification_of_defender;
	
	// Store the calculated attack power
	battlefield.attack_power_modification_of_attacker = attack_power_modification_of_attacker;
	battlefield.attack_power_modification_of_defender = attack_power_modification_of_defender;
	battlefield.attack_power_of_attacker = attack_power_of_attacker;
	battlefield.attack_power_of_defender = attack_power_of_defender;
}


/* - Preparing Batte…
	- SapphireSummoner ♢ ==×1== Attack Power
	- Electric Minion ♢ ==×1== Attack Power */

void Media_Of_Attack_Power::execute(Overworld &world) {
	Battlefield &battlefield = world.battlefield;
	
	int attack_power_modification_of_attacker = battlefield.attack_power_modification_of_attacker;
	int attack_power_modification_of_defender = battlefield.attack_power_modification_of_defender;
	
	int attack_power_of_attacker = battlefield.attack_power_of_attacker;
	int attack_power_of_defender = battlefield.attack_power_of_defender;

	
	world.announce.linger("Preparing Battle...");
	
	std::string power_synthesis_of_attacker = power_of_synthesis(attack_power_of_attacker, attack_power_modification_of_attacker);
	std::string power_synthesis_of_defender = power_of_synthesis(attack_power_of_defender, attack_power_modification_of_defender);
	
	world.announce.overhang(std::format("{} {}",
		world.getActivePlayerName(),
		power_synthesis_of_attacker
	));
	
	world.announce.overhang(std::format("{} {}",
		std::string(to_string(battlefield.combatant_demon)),
		power_synthesis_of_defender
	));
	
	world.announce.suspense(1); // quiet if world.announce.suspense_level > 1
}

std::string Media_Of_Attack_Power::power_of_synthesis(int attack_power, int attack_power_modification) {
	std::string modification_hint = modification_synthesis(attack_power_modification);
	
	std::string power_of_synthesis_hint = std::format("♢ {} Attack Power{}",
		bold("×" + std::to_string(attack_power)),
		modification_hint.empty() ? "" : " " + modification_hint
	);
	
	return power_of_synthesis_hint;
	
}

std::string Media_Of_Attack_Power::modification_synthesis(int attack_power_modification) {
	if (attack_power_modification == 0) {
		return "";
	}
	
	return std::format("({}{})",
		attack_power_modification > 0 ? "+" : "",
		attack_power_modification
	);
}

void Roll_For_Combat_Strength::execute(Overworld &world) {
	world.battlefield.die_roll_for_combat_strength = world.fatesAndCertainty(); // Simulate a die roll (1-6)
}

void Read_Combat_Strength::execute(Overworld &world) {
	Battlefield &battlefield = world.battlefield;
	
	if (clause == "die_roll_for_attacker") {
		battlefield.die_roll_for_attacker = battlefield.die_roll_for_combat_strength;
	} else if (clause == "die_roll_for_defender") {
		battlefield.die_roll_for_defender = battlefield.die_roll_for_combat_strength;
	} else if (clause == "advantage_die_roll_for_attacker") {
		battlefield.advantage_die_roll_for_attacker = battlefield.die_roll_for_combat_strength;
	} else if (clause == "advantage_die_roll_for_defender") {
		battlefield.advantage_die_roll_for_defender = battlefield.die_roll_for_combat_strength;
	}
}

void Apply_Combat_Strength_Result::execute(Overworld &world) {
	Battlefield &battlefield = world.battlefield;
	
	if (battlefield.advantage_of_player) {
		battlefield.combat_strength_of_attacker = std::max(
			static_cast<int>(battlefield.die_roll_for_attacker),
			static_cast<int>(battlefield.advantage_die_roll_for_attacker
		));
	} else {
		battlefield.combat_strength_of_attacker = static_cast<int>(battlefield.die_roll_for_attacker);
	}
	
	if (battlefield.advantage_of_demon) {
		battlefield.combat_strength_of_defender = std::max(
			static_cast<int>(battlefield.die_roll_for_defender),
			 static_cast<int>(battlefield.advantage_die_roll_for_defender)
		);
	} else {
		battlefield.combat_strength_of_defender = static_cast<int>(battlefield.die_roll_for_defender);
	}
}

void Fate_Of_Combat_Strength::execute(Overworld &world) {
	Battlefield &battlefield = world.battlefield;
	
	world.event<Roll_For_Combat_Strength>();
	world.event<Read_Combat_Strength>("die_roll_for_attacker");
	world.event<Roll_For_Combat_Strength>();
	world.event<Read_Combat_Strength>("die_roll_for_defender");
	
	if (battlefield.advantage_of_player) {
		world.event<Roll_For_Combat_Strength>();
		world.event<Read_Combat_Strength>("advantage_die_roll_for_attacker");
	}
	
	if (battlefield.advantage_of_demon) {
		world.event<Roll_For_Combat_Strength>();
		world.event<Read_Combat_Strength>("advantage_die_roll_for_defender");
	}
	
	world.event<Apply_Combat_Strength_Result>();
}

void Media_Of_Combat_Strength::execute(Overworld &world) {
	Battlefield &battlefield = world.battlefield;
	
	world.announce.linger("The Player and the Demon each roll 1 die...");
	
	int combat_strength_of_attacker = battlefield.combat_strength_of_attacker;
	int combat_strength_of_defender = battlefield.combat_strength_of_defender;
	
	std::string advantage_die_roll_hint_of_attacker = "";
	std::string advantage_die_roll_hint_of_defender = "";
	
	if (battlefield.advantage_of_player) {
		advantage_die_roll_hint_of_attacker = discard_of_synthesis(
			battlefield.die_roll_for_attacker,
			battlefield.advantage_die_roll_for_attacker
		);
	}
	
	if (battlefield.advantage_of_demon) {
		advantage_die_roll_hint_of_defender = discard_of_synthesis(
			battlefield.die_roll_for_defender,
			battlefield.advantage_die_roll_for_defender
		);
	}
	
	world.announce.overhang(std::format("{} {}{} Combat Strength",
		world.getActivePlayerName(),
		strength_of_synthesis(combat_strength_of_attacker),
		advantage_die_roll_hint_of_attacker.empty() ? "" : " " + advantage_die_roll_hint_of_attacker
	));
	
	world.announce.overhang(std::format("{} {}{} Combat Strength",
		std::string(to_string(battlefield.combatant_demon)),
		strength_of_synthesis(combat_strength_of_defender),
		advantage_die_roll_hint_of_defender.empty() ? "" : " " + advantage_die_roll_hint_of_defender
	));
	
	world.announce.suspense(1); // quiet if world.announce.suspense_level > 1
}

std::string Media_Of_Combat_Strength::strength_of_synthesis(int combat_strength) {
	std::string strength_of_synthesis_hint = std::format("{} {}",
		dice_synthesis(combat_strength),
		bold("×" + std::to_string(combat_strength))
	);
	
	return strength_of_synthesis_hint;
}

std::string Media_Of_Combat_Strength::discard_of_synthesis(DieRoll normal_die_roll, DieRoll advantage_die_roll) {
	std::string strength_discarded_hint = "";
	
	int combat_strength_one = static_cast<int>(normal_die_roll);
	int combat_strength_two = static_cast<int>(advantage_die_roll);
	
	int discarded_combat_strength = std::min(combat_strength_one, combat_strength_two);
	
	strength_discarded_hint = italic(strikethrough(std::format("{} ×{}",
		dice_synthesis(discarded_combat_strength),
		discarded_combat_strength
	)));
	
	return strength_discarded_hint;
}

std::string Media_Of_Combat_Strength::dice_synthesis(int roll_number) {
	DieRoll die_roll = static_cast<DieRoll>(roll_number);
	
	switch (die_roll) {
		case DieRoll::One:
			return "⚀";
		case DieRoll::Two:
			return "⚁";
		case DieRoll::Three:
			return "⚂";
		case DieRoll::Four:
			return "⚃";
		case DieRoll::Five:
			return "⚄";
		case DieRoll::Six:
			return "⚅";
		default:
			return "";
	}
	
}

/* - The Player and the Demon each roll 1 die…
	- SapphireSummoner ⚅ ==×6== Combat Strength 
	- Electric Minion ⚅ ==×6== Combat Strength ~~⚄ ×5~~ */


/* - Multiply the die roll result by each party's Power to get their Attack Value…
	- SapphireSummoner ※ ==×6== Attack Value 
	- Electric Minion ※ ==×6== Attack Value 
	
	- Multiply the die roll result by each party's Power to get their Attack Value…
	- SapphireSummoner † ==×4== Attack Value 
	- Electric Minion ✤ ==×5== Attack Value 
*/

void Compute_Attack_Value::execute(Overworld &world) {
	Battlefield &battlefield = world.battlefield;
	
	battlefield.attack_value_of_attacker = battlefield.attack_power_of_attacker * battlefield.combat_strength_of_attacker;
	battlefield.attack_value_of_defender = battlefield.attack_power_of_defender * battlefield.combat_strength_of_defender;
}

void Media_Of_Attack_Value::execute(Overworld &world) {
	Battlefield &battlefield = world.battlefield;
	
	int attack_value_of_attacker = battlefield.attack_value_of_attacker;
	int attack_value_of_defender = battlefield.attack_value_of_defender;
	
	world.announce.linger("Multiply the die roll result by each party's Power to get their Attack Value...");
	
	world.announce.overhang(std::format("{} {} Attack Value",
		world.getActivePlayerName(),
		attack_value_synthesis(attack_value_of_attacker, attack_value_of_defender)
	));
	
	world.announce.overhang(std::format("{} {} Attack Value",
		std::string(to_string(battlefield.combatant_demon)),
		attack_value_synthesis(attack_value_of_defender, attack_value_of_attacker)
	));
	
}

std::string Media_Of_Attack_Value::attack_value_synthesis(int attack_value, int opponent_attack_value) {
	std::string symbol_of_value = "";
	if (attack_value == opponent_attack_value) {
		symbol_of_value = "※"; // Equal attack value
	} else if (attack_value > opponent_attack_value) {
		symbol_of_value = "✤"; // Higher attack value
	} else {
		symbol_of_value = "†"; // Lower attack value
	}
	
	std::string attack_value_synthesis_hint = std::format("{} {} Attack Value",
		symbol_of_value,
		bold("×" + std::to_string(attack_value))
	);
	
	return attack_value_synthesis_hint;
}

/* 
- Multiply the die roll result by each party's Power to get their Attack Value…
	- SapphireSummoner ※ ==×6== Attack Value 
	- Electric Minion ※ ==×6== Attack Value 
- The battle resulted in a ==Draw==. Rolling for combat again…
- The Player and the Demon each roll 1 die…
	- SapphireSummoner ⚃ ==×4== Combat Strength 
	- Electric Minion  ⚄ ==×5== Combat Strength
- Multiply the die roll result by each party's Power to get their Attack Value…
	- SapphireSummoner † ==×4== Attack Value 
	- Electric Minion ✤ ==×5== Attack Value 
- **« Result 2:** SapphireSummoner ==Lost== the combat. They lose 1 Heart and are pushed back to their previous space.

6.  If the Player wins, that player receives Gold Coins equal to the demon's *base* Power (before modifications) from the info sheet, and the demon is removed from the space. That player gains 1 permanent Power point.
7.  If the Player loses, they lose 1 Heart and are pushed back to their previous space.
*/

void Combat_Of_Fates::execute(Overworld &world) {
	world.event<Fate_Of_Combat_Strength>();
	world.event<Media_Of_Combat_Strength>();
	world.event<Compute_Attack_Value>();
	world.event<Media_Of_Attack_Value>();
}









void Combat_Clause_Draw::execute(Overworld &world) {
	world.announce.linger(std::format("The battle resulted in a {}. Rolling for combat again...",
		bold("Draw")
	));
	
	world.announce.suspense(1); // quiet if world.announce.suspense_level > 1
	
	world.event<Combat_Of_Fates>();
	world.event<Resolution_Of_Combat>();
	world.event<Apply_Combat_Result>();
}

void Combat_Clause_Player_Wins::execute(Overworld &world) {
	Battlefield &battlefield = world.battlefield;
	
	if (battlefield.combatant_demon == DemonForm::ElectromagneticDemonBoss) {
		world.event<End_Of_Parity>();
		return; // End of parity, 
	}
	
	
	world.announce.result(std::format("{} {} the combat. They receive {} Gold Coins and gain 1 permanent Power point.",
		world.getActivePlayerName(),
		bold("Won"),
		battlefield.malignity.at(battlefield.combatant_demon)
	));
	
	world.announce.suspense(1); // quiet if world.announce.suspense_level > 1
	
	world.expedition.antidivinity.removeDemon(world.active_demon_seriality);
	world.event<Gain_Gold_Coin>(battlefield.malignity.at(battlefield.combatant_demon));
	world.event<Gain_Permanent_Power_Point>(1);
	// world.event<Take_All_Optical_Effects>();
	
	Iridescent combatant_player_iridescence = world.playerbase[world.battlefield.combatant_player].active_optical_effect;
	
	if (combatant_player_iridescence.contains(OpticalEffect::Ascendancy)) {
		world.event<Take_Optical_Effect>(OpticalEffect::Ascendancy);
	}
	if (combatant_player_iridescence.contains(OpticalEffect::Advantage)) {
		world.event<Take_Optical_Effect>(OpticalEffect::Advantage);
	}
	
	Landmark landmark_of_combatant_player = world.getLandmarkOfActivePlayer();
	bool landmark_still_has_demon = world.expedition.antidivinity.getDemonityAt(landmark_of_combatant_player).size() > 0;
	if (combatant_player_iridescence.contains(OpticalEffect::Collimation)
		&& !landmark_still_has_demon
	) {
		world.event<Take_Optical_Effect>(OpticalEffect::Collimation);
		// Take collimation only if there will be no further combat at the player's current space
	}
	
	
	
	
	
	world.event<Potential_Of_Culinary_Consumption>();
	world.event<Potential_Of_Warfare_At_Active_Player>();
}

void Combat_Clause_Player_Loses::execute(Overworld &world) {
	Battlefield &battlefield = world.battlefield;
	
	world.announce.result(std::format("{} {} the combat. They lose 1 Heart and are pushed back one space.",
		world.getActivePlayerName(),
		bold("Lost")
	));
	
	world.announce.suspense(1); // quiet if world.announce.suspense_level > 1
	
	world.event<Take_All_Optical_Effects>();
	world.event<Vitality_Hurt>(1);
	
	if (world.playerbase[world.active_player].vitality_heart > 1) {
		// push back if adventurer will not be knocked out
		world.event<Execute_As>(world.active_player);
		world.event<Knockback_Adventurer>();
		world.event<Relinquish_Execution>();
	}

	world.event<Potential_Of_Warfare>(world.getLandmarkOfActiveDemon());
}

















void Resolution_Of_Combat::execute(Overworld &world) {
	Battlefield &battlefield = world.battlefield;
	
	if (battlefield.attack_value_of_attacker > battlefield.attack_value_of_defender) {
		battlefield.battle_result = BattleResult::PlayerWins;
	} else if (battlefield.attack_value_of_attacker < battlefield.attack_value_of_defender) {
		battlefield.battle_result = BattleResult::PlayerLoses;
	} else {
		battlefield.battle_result = BattleResult::Draw;
	}
}

void Apply_Combat_Result::execute(Overworld &world) {
	Battlefield &battlefield = world.battlefield;
	
	switch (battlefield.battle_result) {
		case BattleResult::PlayerWins:
			world.event<Combat_Clause_Player_Wins>();
			break;
		case BattleResult::PlayerLoses:
			world.event<Combat_Clause_Player_Loses>();
			break;
		case BattleResult::Draw:
			world.event<Combat_Clause_Draw>();
			break;
	}
};

void Preparation_Of_Combat::execute(Overworld &world) {
	world.event<Discord_Of_Beligerence>();
	world.event<Warfare_Iridescence>();
	world.event<Media_Of_Warfare_Iridescence>();
	world.event<Read_Attack_Power>();
	world.event<Media_Of_Attack_Power>();
}

void Commencement_Of_Warfare::execute(Overworld &world) {
	world.event<Preparation_Of_Combat>();
	world.event<Combat_Of_Fates>();
	world.event<Resolution_Of_Combat>();
	world.event<Apply_Combat_Result>();
}

} // namespace Parity