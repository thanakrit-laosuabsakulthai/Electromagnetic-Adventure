export module Parity.Traverser;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.Biology;
	import Parity.Necrology;
	import Parity.Geography;
	import Parity.Expedition;
	import Parity.Optoelectronic;
	
	import Parity.Adventure;
	import Parity.Marketplace;
	import Parity.Warfare;
	import Parity.Physiology;
	import Parity.Necromancy;
	import Parity.Journey;
	import Parity.FortuneBoard;
#endif

export namespace Parity
{

// check for combat and combat item usage
void Omen_Of_Corruption::execute(Overworld &world) {
	PlayerIdentity active_player = world.active_player;
	Landmark player_landmark = world.getLandmarkOfActivePlayer();
	
	// check for demons in landmark
	AntiDivinity antidivinity = world.expedition.antidivinity;
	Demonity demons_at_landmark = antidivinity.getDemonityAt(player_landmark);
	
	if (demons_at_landmark.empty()) {
		return; // No demons at the landmark, so no combat occurs
	}
	
	// if there are demons, check for ultraviolet waves usability
	Inventory& player_inventory = world.playerbase[active_player].inventory;
	bool has_ultraviolet_waves = player_inventory.count(Optics::UltravioletWaves) > 0;
	bool is_not_demon_zone = !is_demon_zone(world.atlas[player_landmark].zone);
	
	if (has_ultraviolet_waves && is_not_demon_zone) {
		world.event<Potential_Of_Repulsion_Consumption>();
	}
	
	world.event<Apply_Omen_Of_Corruption>();
}

void Apply_Omen_Of_Corruption::execute(Overworld &world) {
	// check for repulsion status effect in active player
	PlayerIdentity active_player = world.active_player;
	PlayerPosession& active_player_posession = world.playerbase[active_player];
	
	bool has_repulsion_status = active_player_posession.active_optical_effect.contains(OpticalEffect::Repulsion);
	
	if (has_repulsion_status) {
		world.event<Power_Of_Repulsion>(world.getLandmarkOfActivePlayer());
		world.event<Take_Optical_Effect>(OpticalEffect::Repulsion);
		return; // combat is repulsed
	}
	
	world.event<Potential_Of_Warfare_At_Active_Player>();
}

void Rule_Of_Adventure::execute(Overworld &world) {
	
	CelestialClause current_clause = world.clause_of_adventure;
	
	switch (current_clause) {
	case CelestialClause::VoidOfForgather:
		world.clause_of_adventure = CelestialClause::Sunrise;
		world.event<Celestial_Clause_Forgather>();
		break;
		
	case CelestialClause::Sunrise:
		world.clause_of_adventure = CelestialClause::RestingPlace;
		world.event<Celestial_Clause_Sunrise>();
		break;
		
	case CelestialClause::Dayspring:
		world.clause_of_adventure = CelestialClause::RestingPlace;
		world.event<Celestial_Clause_Dayspring>();
		break;
		
	case CelestialClause::RestingPlace:
		world.clause_of_adventure = CelestialClause::SleepingPlace;
		world.event<Celestial_Clause_RestingPlace>();
		break;
		
	case CelestialClause::SleepingPlace:
		world.event<Branch_Of_SleepingPlace>();
		world.event<Celestial_Clause_SleepingPlace>();
		break;
		
	case CelestialClause::Sunset:
		world.clause_of_adventure = CelestialClause::Twilight;
		world.event<Celestial_Clause_Sunset>();
		break;
		
	case CelestialClause::Twilight:
		world.clause_of_adventure = CelestialClause::Moonfall;
		world.event<Celestial_Clause_Twilight>();
		break;
		
	case CelestialClause::Moonfall:
		world.clause_of_adventure = CelestialClause::Sunrise;
		world.event<Celestial_Clause_Moonfall>();
		break;
		
	case CelestialClause::Starlight:
		world.event<Celestial_Clause_Starlight>();
		return; // End of adventure, so we return early without triggering the next clause
		
	default:
		return;
	}
	
	world.event<Rule_Of_Adventure>();
}


void Celestial_Clause_Forgather::execute(Overworld &world) {
	world.announce.linebreak();
	world.announce.caption("✤  Welcome to Electromagnetic Adventure! ✤");
	world.announce.linebreak();
	world.event<Forgather_of_Adventurer>();
	world.event<Summon_Demon>(DemonForm::ElectromagneticDemonBoss, Landmark::DiamondOfParity);
	world.event<All_Players_Gain_Gold_Coin>(3);
	
	// begin debug
	

	
	// end debug
}

void Celestial_Clause_Sunrise::execute(Overworld &world) {
	world.calendar_of_sunrise++;
	world.event<Media_Of_Sunrise>();
	world.event<First_Adventurer_Turn>();
	world.event<Move_One_Space>();
	
	// begin debug 
	/*
	world.event<Gain_Permanent_Power_Point>(30);
	world.event<Gain_Optical_Effect>(OpticalEffect::Advantage);
	world.event<Teleport>(Landmark::TheCataclysm);
	world.event<Move_One_Space_Optional>(1);
	// end debug /**/
	
	
	
}

void Media_Of_Sunrise::execute(Overworld &world) {
	if (world.calendar_of_sunrise == 1) {
		world.announce.linebreak();
		world.announce.caption("Adventure Start!");
		int amount_of_emdash = 25 * 2 + 1;
		world.announce.caption(repetition("—", amount_of_emdash));
		world.announce.linebreak();
		return;
	}
	
	int amount_of_emdash = 19;
	std::string day_of_synthesis = std::format("Day {}", world.calendar_of_sunrise);
	std::string ornament_notation = get_ornament_notation(amount_of_emdash);
	std::string content_of_announcement = std::vformat(
		ornament_notation,
		std::make_format_args(day_of_synthesis)
	);
	world.announce.horizon(content_of_announcement);
}

void Celestial_Clause_Dayspring::execute(Overworld &world) {
	world.announce.suspense(1); // quiet if world.announce.suspense_level > 1
	world.event<Next_Adventurer_Turn>();
	world.event<Move_One_Space>();
}





void Celestial_Clause_RestingPlace::execute(Overworld &world) {
	// world.event<Gain_Optical_Item>(Optics::RadioWaves);

	world.event<Potential_Of_Fortune_Consumption>();
}

void Branch_Of_SleepingPlace::execute(Overworld &world) {
	bool is_last_player = (world.active_player == static_cast<PlayerIdentity>(world.player_count - 1));
	
	if (is_last_player) {
		// The night begins after the last player's turn
		world.clause_of_adventure = CelestialClause::Sunset;
	} else {
		// Move to the next player's turn
		world.clause_of_adventure = CelestialClause::Dayspring;
	}
}

void Celestial_Clause_SleepingPlace::execute(Overworld &world) {
	world.announce.action(std::format("{} ends their turn.", world.getActivePlayerName()));
}



void Celestial_Clause_Sunset::execute(Overworld &world) {
	world.announce.suspense(1); // quiet if world.announce.suspense_level > 1
	world.event<Media_Of_Sunset>();
}

void Media_Of_Sunset::execute(Overworld &world) {
	int amount_of_emdash = 17;
	std::string day_of_synthesis = std::format("Night {}", world.calendar_of_sunrise);
	std::string ornament_notation = get_ornament_notation(amount_of_emdash);
	std::string content_of_announcement = std::vformat(
		ornament_notation,
		std::make_format_args(day_of_synthesis)
	);
	world.announce.horizon(content_of_announcement);
	
	static std::string callout_of_synthesis = std::format("The {} extends their reign...",
		bold(std::string(to_string(
			DemonForm::ElectromagneticDemonBoss
		)))
	);
	
	world.announce.caption(callout_of_synthesis);
	world.announce.linebreak();
}

void Celestial_Clause_Twilight::execute(Overworld &world) {
	world.event<Demon_Board>();
}

void Celestial_Clause_Moonfall::execute(Overworld &world) {
	world.announce.action("The sun crests the horizon, though the air still tastes of ozone and malice.");
	world.announce.suspense(1); // quiet if world.announce.suspense_level > 1
}

void Celestial_Clause_Starlight::execute(Overworld &world) {
	int amount_of_emdash = 25 * 2 + 1;
	
	world.announce.action("The parity shimmer with a strange intensity, as if reflecting the turmoil of the world below.");
	world.announce.horizon(repetition("—", amount_of_emdash));
	world.announce.caption(std::format("The {} has been defeated!",
		bold(std::string(to_string(
			DemonForm::ElectromagneticDemonBoss
		)))
	));
	world.announce.caption(std::format("The Adventurers {} against the darkness and restored balance to the world.",
		bold_cyan("✤ Won"))
	);
	
	world.announce.horizon(std::format("{} Thank you for playing Electromagnetic Adventure!",
		bold("Adventure Ends!"
	)));
	world.announce.caption(repetition("—", amount_of_emdash));
	world.announce.linebreak();
}

void End_Of_Parity::execute(Overworld &world) {
	world.event_queue.clear();
	world.amount_of_new_event = 0;
	world.clause_of_adventure = CelestialClause::Starlight;
	world.event<Rule_Of_Adventure>();
}


} // namespace Parity