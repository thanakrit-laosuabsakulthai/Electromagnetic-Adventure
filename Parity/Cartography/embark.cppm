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
#endif

export namespace Parity {

export struct Media_Of_Embark : Rule {
	void execute(Overworld &world) override {
		Landmark &landmark_of_beginning = world.expedition.landmark_of_beginning;
		
		std::string lexicon_of_beginning = world.appearanzonality(landmark_of_beginning);
		world.announce.subtitle(std::format("Moving from {} to...", lexicon_of_beginning));
	}
};

// Set the landmark of beginning as the current location of the active player
export struct Embark : Rule {
	void execute(Overworld &world) override {
		
		world.expedition.landmark_of_beginning = world.getLandmarkOfActivePlayer();
		world.event<Media_Of_Embark>();
	}
};


export struct Media_Of_Passage : Rule {
	void execute(Overworld &world) override {
		Landmark &landmark_of_beginning = world.expedition.landmark_of_beginning;
		Passageway &passageway_of_beginning = world.atlas[landmark_of_beginning].passageway;
		
		world.announce.beginChoice();
		
		for (const auto& pathway : passageway_of_beginning) {
			
			std::string appranzonality_of_destination = world.appearanzonality(pathway.destination);
			std::string pathochronality_of_destination = world.pathochronality(pathway);
			
			std::string lexicon_of_destination = std::format("{} {}", appranzonality_of_destination, pathochronality_of_destination);
			
			if (is_restricted_path(pathway.pathType)) {
				world.announce.forbid(lexicon_of_destination);
			} else {
				world.announce.choice(lexicon_of_destination);
			}
		}
		
		if(world.expedition.is_journey_optional) {
			world.announce.choice("Ignore further movements.");
		}
	}
};

// Populate the choice_of_direction based on the passageway of the landmark of beginning
export struct Choice_Of_Passage : Rule {
	void execute(Overworld &world) override {
		Landmark &landmark_of_beginning = world.expedition.landmark_of_beginning;
		Passageway &passageway_of_beginning = world.atlas[landmark_of_beginning].passageway;
		world.event<Media_Of_Passage>();
		
		world.expedition.choice_of_direction.clear();
		for (const auto& pathway : passageway_of_beginning) {
			if (is_restricted_path(pathway.pathType)) {
				continue; // Skip restricted paths when adding choices
			}
			
			world.expedition.choice_of_direction.add(pathway.direction);
		}
	}
};

// Handle the player input, write to expedition: chosen_direction and is_journey_declined
export struct Decision_Of_Passage : Rule {
	
	Overworld *terra = nullptr;
	std::string player_choice;
	
	void execute(Overworld &world) override {
		terra = &world;
		
		get_player_choice();
		
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
	
		
	void query() {
		Overworld &world = *terra;
		
		std::string choice_of_dialect = dialect_synthesis(world.expedition.choice_of_direction.vector());
		
		if (world.expedition.is_journey_optional) {
			choice_of_dialect += " " + std::string(world.encyclopedia.decline_journey);
		}
		
		std::string content_of_query = bag_notation_synthesis(choice_of_dialect);
		
		world.announce.ask(std::format("» Choice {} : ", content_of_query));
	}
	
	void invalid() {
		Overworld &world = *terra;
		world.announce.reject(); // Reject the most recent query
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
	
	void get_player_choice() {
		Overworld &world = *terra;
		std::string player_input;
		
		while (true) {
			query();
			player_input = world.announce.listen();
			
			if (!validate_dialect(player_input)) {
				invalid();
				continue;
			}
			
			break; // Exit the loop if a valid choice is made
		}
		
		// At this point, we have a valid dialect input
		player_choice = player_input;
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

export struct Media_Of_Journey : Rule {
	void execute(Overworld &world) override {
		// display the warning only if a path is marked with an arrow.
		Landmark landmark_of_expeditionist = world.getLandmarkOfActivePlayer();
		Passageway &passageway_of_expeditionist = world.atlas[landmark_of_expeditionist].passageway;
		
		std::string content_of_media = "Move 1 space.";
		
		for (const auto& pathway : passageway_of_expeditionist) {
			if (is_arrow_path(pathway.pathType)) {
				content_of_media += " If the path is marked with an arrow, players cannot move against the arrow's direction.";
				break; // No need to check further paths once we find an arrow path
			}
		}
		
		world.announce.action(content_of_media);
	}
};

} // namespace Parity