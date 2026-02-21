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

} // namespace Parity