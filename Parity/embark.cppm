export module Parity.Embark;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include <print>
	#include <iostream>
	#include "type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.Geography;
	import Parity.World;
	import Parity.Announcement;
	import Parity.Notation;
#endif

export namespace Parity {

export struct Media_Of_Embark : Rule {
	void execute(Overworld &world) override {
		Landmark &landmark_of_beginning = world.expedition.landmark_of_beginning;
		
		std::string lexicon_of_beginning = world.appearanzonality(landmark_of_beginning);
		world.announce.subtitle(std::format("Moving from {} to...", lexicon_of_beginning));
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

export struct Embark : Rule {
	void execute(Overworld &world) override {
		
		world.expedition.landmark_of_beginning = world.getLandmarkOfActivePlayer();
		world.event<Media_Of_Embark>();
	}
};

/* 
- **» Action 1:** Move 1 space. If the path is marked with an arrow, players cannot move against the arrow's direction.
*/

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

export struct Decision_Of_Passage : Rule {
	
	Overworld *terra = nullptr;
	std::string player_choice;
	
	void execute(Overworld &world) override {
		terra = &world;
		
		get_player_choice();
		
		if (world.expedition.is_journey_optional &&
			player_choice == world.encylopedia.decline_journey
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
			choice_of_dialect += " " + std::string(world.encylopedia.decline_journey);
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
			player_input == world.encylopedia.decline_journey
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

export struct Move_One_Space : Rule {
	void execute(Overworld &world) override {
		world.expedition.is_journey_optional = false; // This move is not optional
		world.event<Media_Of_Journey>();
		world.event<Embark>();
		world.event<Choice_Of_Passage>();
		world.event<Decision_Of_Passage>();
		world.event<Travel>();
		world.event<Arrival>();
	}
};

// Forward declaration

struct Decide_Optional_Journey;
struct Apply_Optional_Journey;

export struct Move_One_Space_Optional : Rule {
	int amount_of_optional_move;
	Move_One_Space_Optional(int amount = 1) : amount_of_optional_move(amount) {}
	
	void execute(Overworld &world) override {
		
		if (amount_of_optional_move > 0) {
			world.expedition.is_journey_optional = true;
			world.event<Media_Of_Journey>();
			world.event<Embark>();
			world.event<Choice_Of_Passage>();
			world.event<Decision_Of_Passage>();
			world.event<Apply_Optional_Journey>(amount_of_optional_move);
		}
	}
};

export struct Apply_Optional_Journey : Rule {
	int amount_of_optional_move;
	Apply_Optional_Journey(int amount) : amount_of_optional_move(amount) {}
	
	void execute(Overworld &world) override {
		if (world.expedition.is_journey_declined) {
			world.event<Decline_Journey>();
		} else {
			world.event<Travel>();
			world.event<Arrival>();
			// If there are more optional moves left, ask the player if they want to move again
			if (amount_of_optional_move > 1) {
				world.event<Move_One_Space_Optional>(amount_of_optional_move - 1);
			}
		}
	}
};

// ---+++ overworld methods +++---

std::string Overworld::appearanzonality(Landmark target_landmark) {
	Overworld &world = *this; // For clarity
	
	LandmarkPosession posession = world.atlas[target_landmark];
	
	std::string apparency_word = appearancy(posession.apparentQuality, posession.apparentColor, posession.apparentGeometry);
	std::string zonoity_word = zonoity(posession.zone, apparency_word);
	std::string appearanzonality_word = braket_notation_synthesis(posession.apparentGeometry, zonoity_word);
	
	return appearanzonality_word;
}

std::string Overworld::appearancity(Landmark target_landmark) {
	Overworld &world = *this; // For clarity
	
	LandmarkPosession posession = world.atlas[target_landmark];
	
	std::string apparency_word = appearancy(posession.apparentQuality, posession.apparentColor, posession.apparentGeometry);
	
	return apparency_word;
}

std::string Overworld::pathochronality(Pathway target_pathway) {

	std::string direction_word = std::string(to_string(target_pathway.direction));
	std::string pathochronality_word = chronoity(target_pathway.pathType, direction_word);
	
	return pathochronality_word;
}

Landmark Overworld::getLandmarkOfActivePlayer() {
	return expedition.municipality.getLandmarkOf(active_player);
}

} // namespace Parity