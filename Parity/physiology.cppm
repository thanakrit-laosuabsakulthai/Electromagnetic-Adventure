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

std::string_view Overworld::getActivePlayerName() {
	return to_string(active_player);
};

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



} // namespace Parity