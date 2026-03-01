export module Parity.Embark;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include <print>
	#include <iostream>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.Geography;
	import Parity.Notation;
	import Parity.Encyclopedia;
	import Parity.Expedition;
	
	import Parity.Chromaticity;
	import Parity.Journey;
#endif

export namespace Parity {

// Set the landmark of beginning as the current location of the active player
void Embark::execute(Overworld &world) {
	
	world.expedition.landmark_of_beginning = world.getLandmarkOfActivePlayer();
	world.event<Media_Of_Embark>(); // In accountrement.cppm
}

// Populate the choice_of_direction based on the passageway of the landmark of beginning
void Choice_Of_Passage::execute(Overworld &world) {
	world.event<Media_Of_Passage>(); // In accountrement.cppm
	
	world.event<Restricted_Choice_Of_Passage>(); // Populate the choice_of_direction with non-restricted paths
}

// Write the landmark_of_destination based on the chosen_direction and the passageway of the landmark of beginning
void Travel::execute(Overworld &world) {
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
	// debug
	
}


// Using the municipality to teleport the active player to the landmark of destination
void Arrival::execute(Overworld &world) {
	world.announce.result(std::format(
		"{} chose {}",
		world.getActivePlayerName(),
		bold_cyan(world.appearanzonality(world.expedition.landmark_of_destination))
	));
	
	world.expedition.municipality.teleport(world.active_player, world.expedition.landmark_of_destination);
}


void Decline_Journey::execute(Overworld &world) {
	world.announce.result(std::format(
		"{} stayed on {}",
		world.getActivePlayerName(),
		bold_cyan(world.appearanzonality(world.expedition.landmark_of_beginning))
	));
}



void Move_One_Space::execute(Overworld &world) {
	world.expedition.is_journey_optional = false; // This move is not optional
	world.event<Media_Of_Journey>();
	world.event<Embark>();
	world.event<Choice_Of_Passage>();
	world.event<Decision_Of_Passage>();
	world.event<Travel>();
	world.event<Arrival>();
	world.event<Activate_Color_Effect>(); // In chromaticity.cppm
}



void Move_One_Space_Optional::execute(Overworld &world) {
	
	if (amount_of_optional_move > 0) {
		world.expedition.is_journey_optional = true;
		world.event<Media_Of_Journey>();
		world.event<Embark>();
		world.event<Choice_Of_Passage>();
		world.event<Decision_Of_Passage>();
		world.event<Apply_Optional_Journey>(amount_of_optional_move);
	}
}

void Apply_Optional_Journey::execute(Overworld &world) {
	if (world.expedition.is_journey_declined) {
		world.event<Decline_Journey>();
	} else {
		world.event<Travel>();
		world.event<Arrival>();
		world.event<Activate_Color_Effect>(); // In chromaticity.cppm
		// If there are more optional moves left, ask the player if they want to move again
		if (amount_of_optional_move > 1) {
			world.event<Move_One_Space_Optional>(amount_of_optional_move - 1);
		}
	}
}
















} // namespace Parity