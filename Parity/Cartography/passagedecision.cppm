export module Parity.PassageDecision;

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
	
	import Parity.Expedition;
	import Parity.Notation;
	import Parity.Encyclopedia;
	
	import Parity.Journey;
#endif

export namespace Parity {

void Listen_Passage_Dialect::execute(Overworld &world) {
	world.expedition.player_choice_dialect = world.announce.listen();
}


void Resolve_Passage_Dialect::execute(Overworld &world) {
	std::string player_choice = world.expedition.player_choice_dialect;
	
	if (world.expedition.is_journey_optional &&
		player_choice == world.encyclopedia.decline_journey
	) {
		world.expedition.is_journey_declined = true;
	} else {
		world.expedition.chosen_direction = from_dialect(player_choice);
		world.expedition.is_journey_declined = false;
	}
	
	world.announce.redact(); // Remove the query after a valid choice is made
}


void Apply_Passage_Dialect::execute(Overworld &world) {
	terra = &world;
	
	if (!validate_dialect(world.expedition.player_choice_dialect)) {
		world.announce.reject(); // Reject the query if the input is invalid
		world.event<Decision_Of_Passage>(); // Re-query the player for a valid input
		return;
	}
	// If the input is valid, resolve the decision
	world.event<Resolve_Passage_Dialect>();
}

bool Apply_Passage_Dialect::validate_choice(Direction chosen_direction) {
	Overworld &world = *terra;
	return world.expedition.choice_of_direction.has(chosen_direction);
}

bool Apply_Passage_Dialect::validate_dialect(const std::string& player_input) {
	Overworld &world = *terra;
	
	if (world.expedition.is_journey_optional &&
		player_input == world.encyclopedia.decline_journey
	) {
		return true; // It is a valid choice to decline the journey
	}
	
	try {
		Direction direction = from_dialect(player_input);
		return validate_choice(direction);
	} catch (const std::out_of_range&) {
		return false; // Invalid dialect
	}
}


void Decision_Of_Passage::execute(Overworld &world) {
	world.event<Query_Of_Passage>(); // In accountrement.cppm
	world.event<Listen_Passage_Dialect>();
	world.event<Apply_Passage_Dialect>();
}


};