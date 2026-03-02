export module Parity.Psychology;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.Biology;
	import Parity.OpticalNotation;
	import Parity.Optoelectronic;
	import Parity.Geography;
	
	import Parity.Journey;
	import Parity.Physiology;
#endif

export namespace Parity
{

void Execute_As::execute(Overworld &world) {
	world.active_player = executor;
}

void Relinquish_Execution::execute(Overworld &world) {
	world.active_player = world.turn_of_adventurer; // Revert active player to the current adventurer in turn
}

void Respawn::execute(Overworld &world) {
	// Teleport the active player back to the landmark of beginning
	world.expedition.municipality.teleport(world.active_player, Landmark::DiamondOfCattail);
	world.announce.result(std::format(
		"{} respawned at {}",
		world.getActivePlayerName(),
		bold_cyan(world.appearanzonality(Landmark::DiamondOfCattail))
	));
}

void Vitality_Death::execute(Overworld &world) {
	
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

void Vitality_Hurt::execute(Overworld &world) {
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


void Vitality_Hurt_Humanity::execute(Overworld &world) {
	
	for (const PlayerIdentity& player : world.humanity) {
		//world.announce.subtitle(std::format("Targeting {} for damage.", to_string(player)));
		
		world.event<Execute_As>(player);
		world.event<Vitality_Hurt>(amount_of_damage);
	}
	
	world.event<Relinquish_Execution>();
}
void Vitality_Hurt_Humanity_In_Demon_Zone::execute(Overworld &world) {
	// hurt every player in demon zone
	
	for (const PlayerIdentity& player : world.humanity) {
		Landmark player_landmark = world.getLandmarkOfActivePlayer();
		if (!is_demon_zone(world.atlas[player_landmark].zone)) {
			continue; // Skip players not in demon zone
		}
		
		world.event<Execute_As>(player);
		world.event<Vitality_Hurt>(amount_of_damage);
	}
	
	world.event<Relinquish_Execution>();
}

void Vitality_Heal::execute(Overworld &world) {
	
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


void Gain_Gold_Coin::execute(Overworld &world) {
	world.playerbase[world.active_player].gold_coin += amount_of_gold_coin;
	
	world.announce.bygone(std::format(
		"Gave {} [Gold Coin] to {}.",
		amount_of_gold_coin, to_string(world.active_player)
	));
}


void Gain_Permanent_Power_Point::execute(Overworld &world) {
	world.playerbase[world.active_player].permanent_power_point += amount_of_permanent_power;
	
	world.announce.bygone(std::format(
		"Gave {} [Permanent Power] to {}.",
		amount_of_permanent_power, to_string(world.active_player)
	));
}

void Take_Gold_Coin::execute(Overworld &world)  {
	PlayerPosession &possession = world.playerbase[world.active_player];
	int gold_loss = std::min(amount_of_gold, possession.gold_coin); // Ensure we don't go below zero
	possession.gold_coin -= gold_loss;
	
	world.announce.bygone(std::format(
		"Cleared {} [Gold Coin] from {}.",
		gold_loss,
		world.getActivePlayerName()
	));
}


void Gain_Optical_Item::execute(Overworld &world) {
	// doesn't check for inventory capacity
	PlayerPosession &possession = world.playerbase[world.active_player];
	for (int i = 0; i < quantity; ++i) {
		possession.inventory.insert(optical_item);
	}
	
	world.announce.bygone(std::format(
		"Gave {} [{}] to {}.",
		quantity,
		to_string(optical_item),
		world.getActivePlayerName()
	));
}


// helper function to remove a specific quantity of an optical item from inventory
export inline void remove_optical_item_from_inventory(PlayerPosession &possession, Optics item, int quantity) {
	auto it = possession.inventory.find(item);
	int removed_count = 0;
	while (it != possession.inventory.end() && *it == item && removed_count < quantity) {
		it = possession.inventory.erase(it);
		++removed_count;
	}
}

void Take_Optical_Item::execute(Overworld &world) {
	PlayerPosession &possession = world.playerbase[world.active_player];
	
	int current_quantity = static_cast<int>(possession.inventory.count(optical_item));
	int quantity_to_remove = std::min(quantity, current_quantity); // Ensure we don't remove more than the player has
	
	
	
	if (quantity_to_remove == 0) {
		return;
	}
	
	remove_optical_item_from_inventory(possession, optical_item, quantity_to_remove);
	
	world.announce.bygone(std::format(
		"Cleared {} [{}] from {}.",
		quantity_to_remove,
		to_string(optical_item),
		world.getActivePlayerName()
	));
}


void Gain_Optical_Effect::execute(Overworld &world) {
	PlayerPosession &possession = world.playerbase[world.active_player];
	Iridescent &iridescent_of_active_player = possession.active_optical_effect;
	
	iridescent_of_active_player.insert(optical_effect);
	
	world.announce.bygone(std::format(
		"Applied [{}] effect to {}.",
		to_string(optical_effect),
		world.getActivePlayerName()
	));
}

void Take_Optical_Effect::execute(Overworld &world) {
	PlayerPosession &possession = world.playerbase[world.active_player];
	Iridescent &iridescent_of_active_player = possession.active_optical_effect;
	
	iridescent_of_active_player.erase(optical_effect);
	
	world.announce.bygone(std::format(
		"Removed [{}] effect from {}.",
		to_string(optical_effect),
		world.getActivePlayerName()
	));
}

void Take_All_Optical_Effects::execute(Overworld &world) {
	PlayerPosession &possession = world.playerbase[world.active_player];
	Iridescent &iridescent_of_active_player = possession.active_optical_effect;
	
	// call Take_Optical_Effect for each
	for (const OpticalEffect& effect : iridescent_of_active_player) {
		world.event<Take_Optical_Effect>(effect);
	}
}









} // namespace Parity