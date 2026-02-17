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

export struct Embark : Rule {
	void execute(Overworld &world) override {
		
		world.expedition.landmark_of_beginning = world.expedition.municipality[world.active_player];
		media_of_embark(world);
	}
	
	void media_of_embark(Overworld &world) {
		Landmark &landmark_of_beginning = world.expedition.landmark_of_beginning;
		Passageway &passageway_of_beginning = world.atlas[landmark_of_beginning].passageway;
		
		std::string lexicon_of_beginning = world.appearanzonality(landmark_of_beginning);
		world.announce.subtitle(std::format("Moving from {} to...", lexicon_of_beginning));
		
		for (const auto& pathway : passageway_of_beginning) {
			
			std::string appranzonality_of_destination = world.appearanzonality(pathway.destination);
			std::string pathochronality_of_destination = world.pathochronality(pathway);
			
			std::string lexicon_of_destination = std::format("{} {}", appranzonality_of_destination, pathochronality_of_destination);
			world.announce.choice(lexicon_of_destination);
		}
	}
};

/* 
- **» Action 1:** Move 1 space. If the path is marked with an arrow, players cannot move against the arrow's direction.
*/

export struct Choice_Of_Passage : Rule {
	
	Overworld *terra = nullptr;
	void execute(Overworld &world) override {
		terra = &world; // For member function access
		
		Landmark &landmark_of_beginning = world.expedition.landmark_of_beginning;
		Passageway &passageway_of_beginning = world.atlas[landmark_of_beginning].passageway;
		
		world.expedition.choice_of_direction.clear();
		for (const auto& pathway : passageway_of_beginning) {
			world.expedition.choice_of_direction.add(pathway.direction);
		}
		
		Direction chosen_direction = get_player_choice();
		world.expedition.chosen_direction = chosen_direction;
	}
	
	void query() {
		Overworld &world = *terra;
		
		std::string choice_of_direction_word = braket_notation_synthesis(world.expedition.choice_of_direction.vector());
		world.announce.ask(std::format("» Choice {} : ", choice_of_direction_word));
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
		try {
			Direction direction = from_dialect(player_input);
			return validate_choice(direction);
		} catch (const std::out_of_range&) {
			return false; // Invalid dialect
		}
	}
	
	Direction get_player_choice() {
		std::string player_input;
		Direction chosen_direction;
		
		while (true) {
			query();
			std::getline(std::cin, player_input);
			
			if (!validate_dialect(player_input)) {
				invalid();
				continue;
			} else {
				chosen_direction = from_dialect(player_input);
				break;
			}
		}
		
		return chosen_direction;
	}
};

export struct Travel : Rule {
	void execute(Overworld &world) override {
		
		world.expedition.landmark_of_beginning = world.expedition.municipality[world.active_player];
		
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
			"{} arrives at {}",
			world.getActivePlayerName(),
			world.appearanzonality(world.expedition.landmark_of_destination)
		));
		world.expedition.municipality[world.active_player] = world.expedition.landmark_of_destination;
	}
};

export struct Move_One_Space : Rule {
	void execute(Overworld &world) override {
		world.announce.action("Move 1 space. If the path is marked with an arrow, players cannot move against the arrow's direction.");
		world.event<Embark>();
		world.event<Choice_Of_Passage>();
		world.event<Travel>();
		world.event<Arrival>();
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
	Overworld &world = *this;
	
	std::string direction_word = std::string(to_string(target_pathway.direction));
	std::string pathochronality_word = chronoity(target_pathway.pathType, direction_word);
	
	return pathochronality_word;
}

} // namespace Parity