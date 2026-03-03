export module Parity.Optometrist;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <set>
	#include <string>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	
	import Parity.FortuneBoard;
	import Parity.Physiology;
	import Parity.Marketplace;
	import Parity.Warfare;
	import Parity.Necromancy;
	import Parity.ScoutFly;
#endif


export namespace Parity
{

void Consumption_Of_RadioWaves::execute(Overworld &world) {
	world.event<Lucky_Board>();
}
void Consumption_Of_MicroWaves::execute(Overworld &world) {
	world.event<Vitality_Heal>(1);
}
void Consumption_Of_InfraredWaves::execute(Overworld &world) {
	world.event<Gain_Optical_Effect>(OpticalEffect::Ascendancy);
}
void Consumption_Of_LightWaves::execute(Overworld &world) {
	world.event<Gain_Optical_Effect>(OpticalEffect::Chromatic);
}
void Consumption_Of_UltravioletWaves::execute(Overworld &world) {
	world.event<Gain_Optical_Effect>(OpticalEffect::Repulsion);
}
void Consumption_Of_XRays::execute(Overworld &world) {
	world.event<Gain_Optical_Effect>(OpticalEffect::Advantage);
}
void Consumption_Of_GammaRays::execute(Overworld &world) {
	world.event<Gain_Optical_Effect>(OpticalEffect::Collimation);
}

// set potential consumption to every item in the game
void Excellece_Of_Consumption::execute(Overworld &world) {
	world.potential_consumption = {
		Optics::RadioWaves,
		Optics::MicroWaves,
		Optics::InfraredWaves,
		Optics::LightWaves,
		Optics::UltravioletWaves,
		Optics::XRays,
		Optics::GammaRays
	};
	
	world.event<Open_Inventory>();
}

void Potential_Of_Combat_Consumption::execute(Overworld &world) {
	static std::vector<Optics> combat_optics = {
		Optics::InfraredWaves,
		Optics::XRays,
		Optics::GammaRays
	};
	
	// Check active player's inventory for combat optics
	Inventory& player_inventory = world.playerbase.at(world.active_player).inventory;
	world.potential_consumption.clear();
	for (const auto& optic : combat_optics) {
		if (player_inventory.count(optic) > 0) {
			world.potential_consumption.insert(optic);
		}
	}
	
	if (world.potential_consumption.empty()) {
		return; // No combat optics available, skip offering consumption
	} 
	
	world.event<Open_Inventory>();
}

void Potential_Of_Repulsion_Consumption::execute(Overworld &world) {
	static std::vector<Optics> repulsion_optics = {
		Optics::UltravioletWaves,
	};
	
	// Check active player's inventory for repulsion optics
	Inventory& player_inventory = world.playerbase.at(world.active_player).inventory;
	world.potential_consumption.clear();
	for (const auto& optic : repulsion_optics) {
		if (player_inventory.count(optic) > 0) {
			world.potential_consumption.insert(optic);
		}
	}
	
	if (world.potential_consumption.empty()) {
		return; // No repulsion optics available, skip offering consumption
	}
	
	world.event<Open_Inventory>();
}

void Potential_Of_Culinary_Consumption::execute(Overworld &world) {
	PlayerIdentity active_player = world.active_player;
	PlayerPosession& active_player_posession = world.playerbase.at(active_player);
	
	if (active_player_posession.vitality_heart >= active_player_posession.vitality_maximum_heart) {
		return; // Player is already at maximum Hearts, skip offering culinary consumption
	}
	
	static std::vector<Optics> culinary_optics = {
		Optics::MicroWaves,
	};
	
	Inventory& player_inventory = active_player_posession.inventory;
	world.potential_consumption.clear();
	for (const auto& optic : culinary_optics) {
		if (player_inventory.count(optic) > 0) {
			world.potential_consumption.insert(optic);
		}
	}
	
	if (world.potential_consumption.empty()) {
		return; // No culinary optics available, skip offering consumption
	}
	
	world.event<Open_Inventory>();
}

void Potential_Of_Chromatic_Consumption::execute(Overworld &world) {
	static std::vector<Optics> chromatic_optics = {
		Optics::LightWaves,
	};
	
	Inventory& player_inventory = world.playerbase.at(world.active_player).inventory;
	world.potential_consumption.clear();
	for (const auto& optic : chromatic_optics) {
		if (player_inventory.count(optic) > 0) {
			world.potential_consumption.insert(optic);
		}
	}
	
	if (world.potential_consumption.empty()) {
		return; // No chromatic optics available, skip offering consumption
	}
	
	world.event<Open_Inventory>();
}

void Potential_Of_Fortune_Consumption::execute(Overworld &world) {
	static std::vector<Optics> fortune_optics = {
		Optics::RadioWaves,
	};
	
	Inventory& player_inventory = world.playerbase.at(world.active_player).inventory;
	world.potential_consumption.clear();
	// insert as many fortune optics as the player has, since fortune optics can be consumed multiple times in a turn
	for (const auto& optic : fortune_optics) {
		int count = static_cast<int>(player_inventory.count(optic));
		
		for (int i = 0; i < count; ++i) {
			world.potential_consumption.insert(optic);
		}
	}
	
	if (world.potential_consumption.empty()) {
		return; // No fortune optics available, skip offering consumption
	}
	
	world.event<Open_Inventory>();
}

void Power_Of_Repulsion::execute(Overworld &world) {
	// apply repulsion status effect to all demons at the target landmark
	AntiDivinity antidivinity = world.expedition.antidivinity;
	Demonity demons_at_landmark = antidivinity.getDemonityAt(target_landmark);
	
	for (const auto& demon : demons_at_landmark) {
		world.event<Execute_As_Demon>(demon);
		world.event<Repulse_Demon>();
		world.event<Potential_Of_Warfare_At_Active_Demon>();
	}
}







} // namespace Parity