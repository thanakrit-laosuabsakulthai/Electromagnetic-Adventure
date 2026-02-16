export module Parity.Embark;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include <print>
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
		std::string lexicon_of_beginning = world.lexicon_synthesis_A();
		world.announce.subtitle(std::vformat("Moving from {} to...", std::make_format_args(lexicon_of_beginning)));
	}
};

std::string Overworld::lexicon_synthesis_A() {
	Overworld &world = *this; // For clarity
	
	LandmarkPosession posession = world.atlas[world.expedition.landmark_of_beginning];
	
	std::string apparent_word = word_synthesis(posession.apparentQuality, posession.apparentColor, posession.apparentGeometry);
	std::string apparent_zone_word = zone_notation_synthesis(posession.zone, apparent_word);
	std::string lexicon_order_A = braket_notation_synthesis(posession.apparentGeometry, apparent_zone_word);
	
	return lexicon_order_A;
}

}