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

export struct Vitality_Heal : Rule {
	int amount_of_healing;
	
	Vitality_Heal(int healing) : amount_of_healing(healing) {}
	void execute(Overworld &world) override {
		
		PlayerPosession &possession = world.playerbase[world.active_player];
		
		int maximum_healing = possession.vitality_maximum_heart - possession.vitality_heart;
		int actual_healing = std::min(amount_of_healing, maximum_healing); // Ensure we don't exceed maximum hearts
		possession.vitality_heart += actual_healing;
		
		if (actual_healing == 0) {
			world.announce.bygone(std::format(
				"{} was already at maximum hearts. Nothing happened.",
				to_string(world.active_player)
			));
			return;
		}
		
		
		world.announce.bygone(std::format(
			"Injected healing of {} vitality heart{} to {}.",
			actual_healing,
			actual_healing > 1 ? "s" : "",
			to_string(world.active_player)
		));
	}
};

export struct Gain_Gold_Coin : Rule
{
	int amount_of_gold_coin;
	Gain_Gold_Coin(int amount) : amount_of_gold_coin(amount) {}
	void execute(Overworld &world) override {
		world.playerbase[world.active_player].gold_coin += amount_of_gold_coin;
		
		world.announce.bygone(std::format(
			"Gave {} [Gold Coin] to {}.",
			amount_of_gold_coin, to_string(world.active_player)
		));
	}
};

export struct Gain_Permanent_Power_Point : Rule
{
	int amount_of_permanent_power;
	Gain_Permanent_Power_Point(int amount) : amount_of_permanent_power(amount) {}
	void execute(Overworld &world) override {
		world.playerbase[world.active_player].permanent_power_point += amount_of_permanent_power;
		
		world.announce.bygone(std::format(
			"Gave {} [Permanent Power] to {}.",
			amount_of_permanent_power, to_string(world.active_player)
		));
	}
};

export struct Take_Gold_Coin : Rule
{
	int amount_of_gold;
	
	Take_Gold_Coin(int amount) : amount_of_gold(amount) {}
	void execute(Overworld &world) override {
		PlayerPosession &possession = world.playerbase[world.active_player];
		int gold_loss = std::min(amount_of_gold, possession.gold_coin); // Ensure we don't go below zero
		possession.gold_coin -= gold_loss;
		
		world.announce.bygone(std::format(
			"Cleared {} [Gold Coin] from {}.",
			gold_loss,
			world.getActivePlayerName()
		));
	}
};

} // namespace Parity