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
	import Parity.Accoutrement;
	import Parity.Expedition;
	import Parity.Notation;
	import Parity.Encyclopedia;
#endif

export namespace Parity {

export struct Listen_Passage_Dialect : Rule {
	void execute(Overworld &world) override {
		world.expedition.player_choice_dialect = world.announce.listen();
	}
};

export struct Resolve_Passage_Dialect : Rule {
	void execute(Overworld &world) override {
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
};

struct Decision_Of_Passage; // Forward declaration

export struct Apply_Passage_Dialect : Rule {
	
	Overworld *terra = nullptr;
	void execute(Overworld &world) override {
		terra = &world;
		
		if (!validate_dialect(world.expedition.player_choice_dialect)) {
			world.announce.reject(); // Reject the query if the input is invalid
			world.event<Decision_Of_Passage>(); // Re-query the player for a valid input
			return;
		}
		// If the input is valid, resolve the decision
		world.event<Resolve_Passage_Dialect>();
	}
	
	bool validate_choice(Direction chosen_direction) {
		Overworld &world = *terra;
		return world.expedition.choice_of_direction.has(chosen_direction);
	}
	
	bool validate_dialect(const std::string& player_input) {
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
};

export struct Decision_Of_Passage : Rule {
	void execute(Overworld &world) override {
		world.event<Query_Of_Passage>(); // In accountrement.cppm
		world.event<Listen_Passage_Dialect>();
		world.event<Apply_Passage_Dialect>();
	}
};


};