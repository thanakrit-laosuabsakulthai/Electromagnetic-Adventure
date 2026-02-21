export module Parity.Physiology;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.Biology;
	import Parity.Announcement;
	import Parity.Expedition;
	import Parity.World;
#endif

export namespace Parity
{

export inline std::string_view to_string(PlayerIdentity identity) {
	using enum PlayerIdentity;
	static const std::map<PlayerIdentity, std::string_view> identityToString = {
		{AmethystApprentice, "AmethystApprentice"},
		{SapphireSummoner, "SapphireSummoner"},
		{EmeraldEnchantress, "EmeraldEnchantress"},
		{OpalinOracle, "OpalinOracle"}
	};

	return identityToString.at(identity);
}

export struct Welcome_Adventurer : Rule {
	int amount_of_adventurer;
	
	Welcome_Adventurer(int amount = 1) : amount_of_adventurer(amount) {}
	void execute(Overworld &world) override {
		if (amount_of_adventurer < 1) {
			return;
		} else if (amount_of_adventurer > 4) {
			amount_of_adventurer = 4; // Cap the number of adventurers to 4
		}
		
		for (int i = 0; i < amount_of_adventurer; ++i) {
			PlayerIdentity new_player = static_cast<PlayerIdentity>(i);
			world.playerbase[new_player] = PlayerPosession();
			world.humanity.insert(new_player);
			world.expedition.municipality.addPlayer(new_player, Landmark::DiamondOfCattail);
			
			std::string player_name = std::string(to_string(new_player));
			std::string content_of_announcement = std::format("{} {}", bold_italic_cyan(player_name), italic_cyan("joined the game."));
			world.announce.subtitle(content_of_announcement);
		}
		
		world.active_player = PlayerIdentity::AmethystApprentice; // Set the first player as the active player
	}
};

/* **Player 1 of 2:** AmethystApprentice begins their turn. */

export struct Media_Of_Adventurer : Rule {
	void execute(Overworld &world) override {
		int player_ordinal = static_cast<int>(world.active_player) + 1; // Convert enum to 1-based index
		int total_amount_of_players = static_cast<int>(world.humanity.size());
		std::string_view player_name = world.getActivePlayerName();
		
		std::string lexicon_of_ordinal = bold(std::format("Player {} of {}:", player_ordinal, total_amount_of_players));
		std::string content_of_announcement = std::format("{} {} begins their turn.", lexicon_of_ordinal, player_name);
		world.announce.caption(content_of_announcement);
	}
};

/* 
—————————————››› <u>[Player Turn]</u> ‹‹‹——————————————

**Player 2 of 2:** SapphireSummoner begins their turn.

*/

// string repetition for emdash because emdash is a multicharacter string in UTF-8
export inline std::string repetition(const std::string& target_string, int amount_of_repetition) {
	std::string result;
	for (int i = 0; i < amount_of_repetition; ++i) {
		result += target_string;
	}
	return result;
}

export inline std::string get_ornament_notation(int amount_of_emdash) {
	std::string ornament_emdash = repetition("—", amount_of_emdash);
	std::string center_placeholder = std::format("››› [{}] ‹‹‹", underline("{}"));
	return ornament_emdash + center_placeholder + ornament_emdash;
}

export struct Media_Of_Adventurer_Separator : Rule {
	void execute(Overworld &world) override {
		std::string ornament_notation = get_ornament_notation(15);
		std::string content_of_announcement = std::vformat(ornament_notation, std::make_format_args("Player Turn"));
		world.announce.horizon(content_of_announcement);
	}
};

export struct First_Adventurer_Turn : Rule {
	void execute(Overworld &world) override {
		world.firstAdventurer();
		world.event<Media_Of_Adventurer>();
	}
};

export struct Next_Adventurer_Turn : Rule {
	void execute(Overworld &world) override {
		world.nextAdventurer();
		world.event<Media_Of_Adventurer_Separator>();
		world.event<Media_Of_Adventurer>();
	}
};

// ---+++ overworld methods +++---

std::string_view Overworld::getActivePlayerName() {
	return to_string(active_player);
};

// helper function to get next player in turn order
export template <typename Element_Of_Set>
inline Element_Of_Set getNextElement(const std::set<Element_Of_Set>& target_set, Element_Of_Set current_element) {
	auto iterator = target_set.find(current_element);
	if (iterator == target_set.end()) {
		throw std::runtime_error("Current element not found in the set.");
	}
	++iterator; // Move to the next element
	if (iterator == target_set.end()) {
		iterator = target_set.begin(); // Wrap around to the beginning if we reach the end
	}
	return *iterator;
}

void Overworld::firstAdventurer() {
	if (humanity.empty()) {
		throw std::runtime_error("No adventurers in the game.");
	}
	active_player = *humanity.begin();
}

void Overworld::nextAdventurer() {
	if (humanity.empty()) {
		throw std::runtime_error("No adventurers in the game.");
	}
	active_player = getNextElement(humanity, active_player);
}

} // namespace Parity