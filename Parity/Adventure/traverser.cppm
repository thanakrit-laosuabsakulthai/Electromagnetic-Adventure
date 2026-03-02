export module Parity.Adventurer;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.Biology;
	import Parity.Geography;
	import Parity.Expedition;
	
	import Parity.Adventure;
	import Parity.Marketplace;
	import Parity.Warfare;
	import Parity.Physiology;
#endif

export namespace Parity
{
// 

void Rule_Of_Adventure::execute(Overworld &world) {
}

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



} // namespace Parity