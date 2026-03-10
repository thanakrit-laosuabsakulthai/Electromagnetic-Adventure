export module Parity.DemonBoard;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <format>
	#include <string>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.DieRoll;
	import Parity.Biology;
	import Parity.Necrology;
	import Parity.Expedition;
	import Parity.Geography;
	
	import Parity.FortuneBoard;
	import Parity.Physiology;
	import Parity.Necromancy;
	import Parity.Warfare;
	import Parity.ScoutFly;
#endif

/* 
# Demon Board

Roll 1 die and apply the result:

1.  All non-Boss demons move 1 space towards a player.
2.  Summon Electric Minion on the Red Square space and initiates combat with players on that space.
3.  A Magnetic Mage Demon spawns on the Purple Diamond space and moves 1 space towards a player.
4.  A Magnetic Demon spawns on the Purple Diamond space and moves 2 spaces towards a player.
5.  All players currently in the Demon Zone (Red area) lose 1 Heart.
6.  Roll a die to determine which demon spawns on the Purple Diamond space and moves 3 spaces towards a player:
    *   1-2: Electric Minion
    *   3-4: Magnetic Demon
    *   5-6: Magnetic Mage Demon
*/

export namespace Parity
{
//
/* 
- **» Action 2:** The screech of the Demon Zone could be heard across the Horizon.
- **« Result 2:** Nothing happened.
*/


export struct All_Players_In_Demon_Zone_Lose_One_Heart : Rule {
	void execute(Overworld &world) override {
		world.announce.action("The screech of the Demon Zone could be heard across the Horizon.");
		
		Humanity players_in_demon_zone;
		
		for (const PlayerIdentity& player : world.humanity) {
			Landmark player_landmark = world.expedition.municipality.getLandmarkOf(player);
			if (!is_demon_zone(world.atlas[player_landmark].zone)) {
				continue; // Skip players not in demon zone
			}
			players_in_demon_zone.insert(player);
		}
		
		if (players_in_demon_zone.empty()) {
			world.announce.result("Nothing happened.");
			return;
		}
		
		// amount of vitality consumed
		world.announce.result(std::format(
			"The Diamond of Parity immolated {} Vitality Heart{} tonight.",
			players_in_demon_zone.size(),
			players_in_demon_zone.size() > 1 ? "s" : ""
		));
		
		world.event<Vitality_Hurt_Humanity_In_Demon_Zone>(1);
	}
};

export struct All_Lesser_Demons_Move_One_Space_Towards_Player : Rule {
	void execute(Overworld &world) override {
		Demonity lesser_demonity = world.expedition.antidivinity.getAllLesserDemons();
		
		for (const DemonSeriality& demon : lesser_demonity) {
			
			/* DemonForm demon_form = world.expedition.antidivinity.demon_manifest[demon];
			world.announce.linger(std::format(
				"{} moves 1 space towards a player.",
				bold_cyan(std::string(to_string(demon_form)))
			)); */
			world.event<Execute_As_Demon>(demon);
			world.event<Move_Demon_Towards_Player>(1);
		}
	}
};


export struct Apply_Mediumship_Of_Corruption : Rule {
	void execute(Overworld &world) override {
		DieRoll roll = world.die_roll_for_fortune_board;
		int outcome_index = (static_cast<int>(roll) - 1) / reach;
		
		DemonForm demon_form = outcomes[outcome_index];
		world.announce.result(std::format(
			"A {} spawns on the Purple Diamond space and moves 3 spaces towards a player.",
			bold_cyan(std::string(to_string(demon_form)))
		));
		
		world.event<Summon_Demon>(demon_form, Landmark::DiamondOfParity);
		world.event<Move_Demon_Towards_Player>(3);
	}
	
	static constexpr int reach = 2; // Each outcome corresponds to 2 die results (e.g., 1-2, 3-4, 5-6)
	static inline const std::vector<DemonForm> outcomes = {
		DemonForm::ElectricMinion,
		DemonForm::MagneticDemon,
		DemonForm::MagneticMageDemon
	};
};

export struct Media_Of_Mediumship : Rule {
	void execute(Overworld &world) override {
		world.announce.action("Roll 1 die to determine which demon spawns on the Purple Diamond space...");
		
		std::vector<DemonForm> demon_outcomes = Apply_Mediumship_Of_Corruption::outcomes;
		int reach = Apply_Mediumship_Of_Corruption::reach;
		world.announce.beginChoice();
		
		for (const auto& demon_form : demon_outcomes) {
			world.announce.range(std::string(to_string(demon_form)), reach);
		}
	}
};

export struct Mediumship_Of_Corruption : Rule {
	void execute(Overworld &world) override {
		world.event<Media_Of_Mediumship>();
		world.event<Roll_For_Random_Board>();
		world.event<Apply_Mediumship_Of_Corruption>();
	}
};


export struct Media_Of_Demon_Board : Rule {
	void execute(Overworld &world) override {
		world.announce.subtitle("Roll 1 die and apply the result...");
		
		world.announce.beginChoice();
		for (const auto& media : outcomes) {
			world.announce.choice(media);
		}
	}
	
	static inline const std::vector<std::string> outcomes = {
		"All non-Boss demons move 1 space towards a player.",
		"Summon Electric Minion on the Red Square space and initiates combat.",
		"A Magnetic Mage Demon spawns on the Purple Diamond space and moves 1 space towards a player.",
		"A Magnetic Demon spawns on the Purple Diamond space and moves 2 spaces towards a player.",
		"All players currently in the Demon Zone (Red area) lose 1 Heart.",
		"Roll a die to spawn a demon on the Purple Diamond space and moves 3 spaces towards a player:\n\t\t• 1-2: Electric Minion\n\t\t• 3-4: Magnetic Demon\n\t\t• 5-6: Magnetic Mage Demon"
	};
};

export struct Apply_Demon_Board_Result : Rule
{
	void execute(Overworld &world) override {
		applyDemonBoardResult(world, world.die_roll_for_fortune_board);
	}
	void applyDemonBoardResult(Overworld &world, DieRoll roll) {
		//world.announce.result(Media_Of_Demon_Board::outcomes[static_cast<int>(roll) - 1]);
		
		std::string result_description = Media_Of_Demon_Board::outcomes[static_cast<int>(roll) - 1];
		
		using enum DieRoll;
		switch (roll) {
		case One:
			world.event<All_Lesser_Demons_Move_One_Space_Towards_Player>();
			world.announce.result(result_description);
			break;
		case Two:
			world.announce.result(std::format(
				"An {} spawns on the Red Square space and initiates combat.",
				bold_cyan("Electric Minion")
			));
			world.event<Summon_Demon>(DemonForm::ElectricMinion, Landmark::ContestedCorruption);
			world.event<Potential_Of_Warfare_At_Active_Demon>();
			break;
		case Three:
			world.announce.result(std::format(
				"A {} spawns on the Purple Diamond space and moves 1 space towards a player.",
				bold_cyan("Magnetic Mage Demon")
			));
			world.event<Summon_Demon>(DemonForm::MagneticMageDemon, Landmark::DiamondOfParity);
			world.event<Move_Demon_Towards_Player>(1);
			break;
		case Four:
			world.announce.result(std::format(
				"A {} spawns on the Purple Diamond space and moves 2 spaces towards a player.",
				bold_cyan("Magnetic Demon")
			));
			world.event<Summon_Demon>(DemonForm::MagneticDemon, Landmark::DiamondOfParity);
			world.event<Move_Demon_Towards_Player>(2);
			break;
		case Five:
			world.event<All_Players_In_Demon_Zone_Lose_One_Heart>();
			world.announce.result(result_description);
			break;
		case Six:
			world.announce.result("Roll a die to spawn a demon on the Purple Diamond space and moves 3 spaces towards a player");
			world.event<Mediumship_Of_Corruption>();
			break;
		}
	}
};

void Demon_Board::execute(Overworld &world) {
	if( world.clause_of_adventure != CelestialClause::Moonfall ) {
		world.announce.action(std::format(
			"{} rolls the Demon Board once.",
			to_string(world.active_player)
		));
	} else {
		world.announce.action(std::format(
			"The {} rolls the Demon Board once.",
			std::string(to_string(
				DemonForm::ElectromagneticDemonBoss
			))
		));
	}
	
	world.event<Media_Of_Demon_Board>();
	world.event<Roll_For_Random_Board>();
	world.event<Apply_Demon_Board_Result>();
}

} // namespace Parity