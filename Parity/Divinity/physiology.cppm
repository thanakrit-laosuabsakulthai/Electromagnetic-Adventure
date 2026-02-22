export module Parity.Physiology;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.Biology;
	import Parity.Announcement;
	import Parity.Accoutrement;
	import Parity.Expedition;
	import Parity.Journey;
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

/* - *Inflicted damage of 1 vitality heart to SapphireSummoner*
1.  **Player Characters:** All have Base Power = 1, Maximum Hearts = 5.
Each can hold up to 4 items. If a player dies (reaches 0 Hearts), they return to the Pink Diamond space and lose *all* their Gold and Items.
*/


export struct Respawn : Rule {
	void execute(Overworld &world) override {
		// Teleport the active player back to the landmark of beginning
		world.expedition.municipality.teleport(world.active_player, Landmark::DiamondOfCattail);
		world.announce.result(std::format(
			"{} respawned at {}",
			world.getActivePlayerName(),
			bold_cyan(world.appearanzonality(Landmark::DiamondOfCattail))
		));
	}
};


export struct Vitality_Death : Rule {
	void execute(Overworld &world) override {
		
		world.announce.action(std::format(
			"{} died. They return to the Pink Diamond space and lose all their Gold and Items.",
			world.getActivePlayerName()
		));
		
		PlayerPosession &possession = world.playerbase[world.active_player];
		possession.gold_coin = 0;
		possession.inventory.clear();
		possession.vitality_heart = possession.vitality_maximum_heart; // Restore vitality to maximum upon death
		
		world.announce.bygone(std::format(
			"Cleared all [Gold Coin] from {}",
			world.getActivePlayerName()
		));
		
		world.announce.bygone(std::format(
			"Cleared all items from {}",
			world.getActivePlayerName()
		));
		
		world.announce.bygone(std::format(
			"Restored {} to {} vitality hearts",
			world.getActivePlayerName(),
			possession.vitality_heart
		));
		
		world.event<Respawn>();
	}
};

export struct Vitality_Hurt : Rule {
	int amount_of_damage;
	
	Vitality_Hurt(int damage) : amount_of_damage(damage) {}
	void execute(Overworld &world) override {
		PlayerPosession &possession = world.playerbase[world.active_player];
		
		int vitality_loss = std::min(amount_of_damage, possession.vitality_heart); // Ensure we don't go below zero
		possession.vitality_heart -= vitality_loss;
		
		world.announce.bygone(std::format(
			"Inflicted damage of {} vitality heart{} to {}.",
			vitality_loss,
			vitality_loss > 1 ? "s" : "",
			to_string(world.active_player)
		));
		
		if (possession.vitality_heart == 0) {
			world.event<Vitality_Death>();
		}
	}
};



} // namespace Parity