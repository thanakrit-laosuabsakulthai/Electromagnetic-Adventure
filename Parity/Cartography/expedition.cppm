export module Parity.Expedition;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <unordered_map>
	#include <unordered_set>
	#include <set>
	#include <vector>
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	
	import Parity.Geography;
	import Parity.Biology;
	import Parity.Notation;
	import Parity.Necrology;
	
#endif

export namespace Parity {

export using PlayerLocation = std::map<PlayerIdentity, Landmark>;
export using PlayerLocator = std::map<Landmark, Humanity>;

export struct Municipality {
	PlayerLocation player_location;
	PlayerLocator player_locator;
	
	void teleport(PlayerIdentity target_player, Landmark landmark_of_destination) {
		Landmark landmark_of_beginning = player_location[target_player];
		
		// Update player_location
		player_location[target_player] = landmark_of_destination;
		// Update player_locator
		player_locator[landmark_of_beginning].erase(target_player);
		player_locator[landmark_of_destination].insert(target_player);
	}
	
	Landmark getLandmarkOf(PlayerIdentity player) const {
		return player_location.at(player);
	}
	
	Humanity getHumanityAt(Landmark landmark) const {
		if (player_locator.find(landmark) == player_locator.end()) {
			return {}; // Return an empty set if no players are at the landmark
		}
		
		return player_locator.at(landmark);
	}
	
	void addPlayer(PlayerIdentity player, Landmark landmark) {
		player_location[player] = landmark;
		player_locator[landmark].insert(player);
	}
};

export struct OmniDirection {
	MultiDirection multidirection;
	
	void add(Direction direction) {
		multidirection.push_back(direction);
	}
	
	void clear() {
		multidirection.clear();
	}
	
	bool has(Direction direction) const {
		return std::find(multidirection.begin(), multidirection.end(), direction) != multidirection.end();
	}
	
	MultiDirection vector() const {
		return multidirection;
	}
};

export using DemonLocation = std::map<DemonSeriality, Landmark>;
export using DemonLocator = std::map<Landmark, Demonity>;

export struct AntiDivinity {
	DemonLocation demon_location;
	DemonLocator demon_locator;
	DemonManifest demon_manifest;
	int next_demon_seriality = 1; // Start from 1 for better readability
	
	void teleport(DemonSeriality target_demon, Landmark landmark_of_destination) {
		Landmark landmark_of_beginning = demon_location[target_demon];
		
		// Update demon_location
		demon_location[target_demon] = landmark_of_destination;
		// Update demon_locator
		demon_locator[landmark_of_beginning].erase(target_demon);
		demon_locator[landmark_of_destination].insert(target_demon);
	}
	
	Landmark getLandmarkOf(DemonSeriality demon) const {
		return demon_location.at(demon);
	}
	
	Demonity getDemonityAt(Landmark landmark) const {
		if (demon_locator.find(landmark) == demon_locator.end()) {
			return {}; // Return an empty set if no demons are at the landmark
		}
		
		return demon_locator.at(landmark);
	}
	
	void addDemon(DemonForm demon_form, Landmark landmark) {
		DemonSeriality demon_seriality = next_demon_seriality++;
		demon_location[demon_seriality] = landmark;
		demon_locator[landmark].insert(demon_seriality);
		demon_manifest[demon_seriality] = demon_form;
	}
	
	void removeDemon(DemonSeriality demon) {
		Landmark landmark_of_demon = demon_location.at(demon);
		
		// Update demon_location
		demon_location.erase(demon);
		// Update demon_locator
		demon_locator[landmark_of_demon].erase(demon);
		// Update demon_manifest
		demon_manifest.erase(demon);
	}
	
	Demonity getAllLesserDemons() const {
		Demonity all_lesser_demons;
		for (const auto& [demon_seriality, demon_form] : demon_manifest) {
			if (demon_form == DemonForm::ElectricMinion) {
				all_lesser_demons.insert(demon_seriality);
			}
		}
		return all_lesser_demons;
	}
};

export struct Expedition
{
	Landmark landmark_of_beginning = Landmark::DiamondOfCattail;
	Landmark landmark_of_destination = Landmark::DiamondOfCattail;
	std::string player_choice_dialect;
	Direction chosen_direction;
	OmniDirection choice_of_direction;
	bool is_journey_optional = false;
	bool is_journey_declined = false;
	Municipality municipality = {};
	AntiDivinity antidivinity = {};
	
	int amount_of_conquest_remaining = 0;
	int amount_of_conquest = 0;
};

} // namespace Parity







