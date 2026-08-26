export module Parity.Accoutrement;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	
	import Parity.Geography;
	import Parity.Notation;
	
	import Parity.Expedition;
	import Parity.Journey;
	import Parity.ScoutFly;
#endif

export namespace Parity {

// ---+++ overworld methods +++---

Landmark Overworld::getLandmarkOfActivePlayer() {
	return expedition.municipality.getLandmarkOf(active_player);
}

std::string Overworld::appearanzonality(Landmark target_landmark) {
	Overworld &world = *this; // For clarity
	
	LandmarkPosession posession = world.atlas[target_landmark];
	
	std::string apparency_word = appearancy(posession.apparentQuality, posession.apparentColor, posession.apparentGeometry);
	std::string zonoity_word = zonoity(posession.zone, apparency_word);
	std::string appearanzonality_word = archeometrinoity(posession.apparentGeometry, zonoity_word);
	
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

std::string Overworld::pathochronality(Direction direction) {
	Overworld &world = *this; // For clarity
	
	Landmark &landmark_of_beginning = world.expedition.landmark_of_beginning;
	Passageway &passageway_of_beginning = world.atlas[landmark_of_beginning].passageway;
	
	Pathway target_pathway;
	bool found_pathway = false;
	
	for (const auto& pathway : passageway_of_beginning) {
		if (pathway.direction == direction) {
			target_pathway = pathway;
			found_pathway = true;
			break;
		}
	}
	
	if (!found_pathway) {
		return ""; // Return an empty string if no pathway is found in the given direction
	}
	
	return pathochronality(target_pathway);
}

// ---+++ embarkation rule +++---

void Media_Of_Journey::execute(Overworld &world) {
	// display the warning only if a path is marked with an arrow.
	Landmark landmark_of_expeditionist = world.getLandmarkOfActivePlayer();
	Passageway &passageway_of_expeditionist = world.atlas[landmark_of_expeditionist].passageway;
	
	std::string content_of_media = "Move 1 space.";
	
	for (const auto& pathway : passageway_of_expeditionist) {
		if (is_arrow_path(pathway.pathType)) {
			content_of_media += " Players cannot move against the arrow's direction.";
			break; // No need to check further paths once we find an arrow path
		}
	}
	
	world.announce.action(content_of_media);
}


void Query_Of_Passage::execute(Overworld &world) {
	std::string query_dialect = dialect_synthesis(world.expedition.choice_of_direction.vector());
	
	if (world.expedition.is_journey_optional) {
		query_dialect += " " + std::string(world.encyclopedia.decline_journey);
	}
	
	std::string content_of_query = bag_notation_synthesis(query_dialect);
	
	world.announce.ask(content_of_query);
}


void Media_Of_Embark::execute(Overworld &world) {
	Landmark &landmark_of_beginning = world.expedition.landmark_of_beginning;
	
	std::string lexicon_of_beginning = world.appearanzonality(landmark_of_beginning);
	world.announce.subtitle(std::format("Moving from {} to...", lexicon_of_beginning));
}

void Media_Of_Passage::execute(Overworld &world) {
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
		world.announce.abandon("Ignore further movements.");
	}
}

void Restricted_Choice_Of_Passage::execute(Overworld &world) {
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

void Every_Choice_Of_Passage::execute(Overworld &world) {
	Landmark &landmark_of_beginning = world.expedition.landmark_of_beginning;
	Passageway &passageway_of_beginning = world.atlas[landmark_of_beginning].passageway;
	world.expedition.choice_of_direction.clear();
	
	for (const auto& pathway : passageway_of_beginning) {
		world.expedition.choice_of_direction.add(pathway.direction);
	}
}





// ---+++ demonic journey rule +++---

/* 
- **» Action 3:** The Magnetic Mage Demon moves 3 spaces towards a player.
- Moving from ⟨Purple Diamond Space⟩ to…
	1. ｢Red Space｣ ← left, then…
	2. ｢Red Space｣ ← left, then…
	3. ｢Red-Purple Gradient Space｣ ← left
- **« Result 3:** The Magnetic Mage Demon moved to ==｢Red-Purple Gradient Space｣ ← left ← left ← left==
*/

void Media_Of_Conquest::execute(Overworld &world) {
	DemonForm active_demon_form = world.getActiveDemonForm();
	world.announce.action(std::format("The {} moves {} space{} towards a player.",
		to_string(active_demon_form),
		world.expedition.amount_of_conquest,
		(world.expedition.amount_of_conquest > 1) ? "s" : ""
	));
}

void Media_Of_Perpetrate::execute(Overworld &world) {
	// same as Media_Of_Embark
	Landmark &landmark_of_beginning = world.expedition.landmark_of_beginning;
	
	std::string lexicon_of_beginning = world.appearanzonality(landmark_of_beginning);
	world.announce.linger(std::format("Moving from {} to...", lexicon_of_beginning));
	
	world.announce.beginAnalog();
}


void Media_Of_Conquest_Success::execute(Overworld &world) {
	world.announce.result(std::format("The {} moved to {} {}.",
		bold_cyan(std::string(to_string(world.getActiveDemonForm()))),
		bold_cyan(world.appearanzonality(world.expedition.landmark_of_destination)),
		bold_cyan(world.pathochronality(world.expedition.chosen_direction))
	));
}

void Media_Of_Conquest_Failure::execute(Overworld &world) {
	world.announce.result(std::format("The {} stayed on {}.",
		bold_cyan(std::string(to_string(world.getActiveDemonForm()))),
		bold_cyan(world.appearanzonality(world.expedition.landmark_of_beginning))
	));
}

} // namespace Parity


