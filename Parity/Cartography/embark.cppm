export module Parity.Embark;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include <print>
	#include <iostream>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.Geography;
	import Parity.World;
	import Parity.Announcement;
	import Parity.Notation;
	import Parity.Encyclopedia;
	import Parity.Expedition;
	import Parity.Accoutrement;
#endif

export namespace Parity {

// Set the landmark of beginning as the current location of the active player
export struct Embark : Rule {
	void execute(Overworld &world) override {
		
		world.expedition.landmark_of_beginning = world.getLandmarkOfActivePlayer();
		world.event<Media_Of_Embark>(); // In accountrement.cppm
	}
};

// Populate the choice_of_direction based on the passageway of the landmark of beginning
export struct Choice_Of_Passage : Rule {
	void execute(Overworld &world) override {
		world.event<Media_Of_Passage>(); // In accountrement.cppm
		
		Landmark &landmark_of_beginning = world.expedition.landmark_of_beginning;
		Passageway &passageway_of_beginning = world.atlas[landmark_of_beginning].passageway;
		world.expedition.choice_of_direction.clear();
		for (const auto& pathway : passageway_of_beginning) {
			if (is_restricted_path(pathway.pathType)) {
				continue; // Skip restricted paths when adding choices
			}
			
			world.expedition.choice_of_direction.add(pathway.direction);
		}
	}
};

// Write the landmark_of_destination based on the chosen_direction and the passageway of the landmark of beginning
export struct Travel : Rule {
	void execute(Overworld &world) override {
		world.expedition.landmark_of_beginning = world.getLandmarkOfActivePlayer();
		
		Landmark &landmark_of_beginning = world.expedition.landmark_of_beginning;
		Passageway &passageway_of_beginning = world.atlas[landmark_of_beginning].passageway;
		
		for (const auto& pathway : passageway_of_beginning) {
			if (pathway.direction == world.expedition.chosen_direction) {
				world.expedition.landmark_of_destination = pathway.destination;
				return;
			}
		}
		
		// If the chosen direction is not valid, stay in the same place
		world.expedition.landmark_of_destination = world.expedition.landmark_of_beginning;
	}
};

// Using the municipality to teleport the active player to the landmark of destination
export struct Arrival : Rule {
	void execute(Overworld &world) override {
		world.announce.result(std::format(
			"{} chose {}",
			world.getActivePlayerName(),
			bold_cyan(world.appearanzonality(world.expedition.landmark_of_destination))
		));
		
		world.expedition.municipality.teleport(world.active_player, world.expedition.landmark_of_destination);
	}
};

export struct Decline_Journey : Rule {
	void execute(Overworld &world) override {
		world.announce.result(std::format(
			"{} stayed on {}",
			world.getActivePlayerName(),
			bold_cyan(world.appearanzonality(world.expedition.landmark_of_beginning))
		));
	}
};


} // namespace Parity