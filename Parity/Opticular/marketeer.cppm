export module Parity.Marketeer;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <map>
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.Optoelectronic;
	import Parity.OpticalNotation;
	import Parity.Biology;
	
	import Parity.Physiology;
	import Parity.Marketplace;
#endif

export namespace Parity
{

void Decline_Shop::execute(Overworld &world) {
	world.announce.result(std::format(
		"{} chose to not purchase any items from the Shop.",
		world.getActivePlayerName()
	));
}


void Apply_Purchasement_Result::execute(Overworld &world) {
	Inventory purchasement = world.purchasement;
	MarketValuation marketplace = world.marketplace;
	
	std::map<Optics, int> item_count;
	for (const auto& item : purchasement) {
		item_count[item]++;
	}
	
	// don't check for any constraint
	for (const auto& [optic, count] : item_count) {
		world.event<Gain_Optical_Item>(optic, count);
	}
	
	int total_cost = 0;
	for (const auto& item : purchasement) {
		total_cost += marketplace.at(item);
	}
	
	world.event<Take_Gold_Coin>(total_cost);
}


void Apply_Purchasement_Of_Optics::execute(Overworld &world) {
	Inventory purchasement = world.purchasement;
	
	if (purchasement.empty()) {
		world.event<Decline_Shop>();
	} else {
		world.event<Review_Of_Purchase>();
		world.event<Apply_Purchasement_Result>();
	}

}

void Open_Shop::execute(Overworld &world) {
	PlayerIdentity active_player = world.active_player;
	PlayerPosession &possession = world.playerbase[active_player];
	
	if (possession.gold_coin == 0) {
		world.announce.result(std::format(
			"{} has no Gold Coins and cannot purchase items from the Shop Board.",
			world.getActivePlayerName()
		));
		return;
	}
	
	int inventory_capacity = possession.inventory_capacity;
	int current_inventory_size = static_cast<int>(possession.inventory.size());
	
	if (current_inventory_size >= inventory_capacity) {
		world.announce.result(std::format(
			"{} already has {} item{} in inventory and cannot purchase more from the Shop Board.",
			world.getActivePlayerName(),
			current_inventory_size,
			current_inventory_size == 1 ? "" : "s"
		));
		return;
	}
	
	world.event<Media_Of_Marketplace>();
	world.event<Purchasement_Of_Optics>();
	world.event<Apply_Purchasement_Of_Optics>();
}

void Decline_Consumption::execute(Overworld &world) {
	world.announce.result(std::format(
		"{} chose to not use any items from their inventory.",
		world.getActivePlayerName()
	));
}

void Apply_Consumption_Of_Optics::execute(Overworld &world) {
	Inventory consumption = world.consumption;
	
	if (consumption.empty()) {
		world.event<Decline_Consumption>();
	} else {
		world.event<Review_Of_Consumption>();
		world.event<Apply_Consumption_Result>();
	}
}

void Apply_Consumption_Result::execute(Overworld &world) {
	terra = &world; // for helper functions
	
	Inventory consumption = world.consumption;
	
	// for removing items only
	std::map<Optics, int> item_count;
	
	for (const auto& item : consumption) {
		item_count[item]++;
	}
	
	for (const auto& [optic, count] : item_count) {
		world.event<Take_Optical_Item>(optic, count);
	}
	
	
	for (const auto& item : consumption) {
		apply_optical_item(item);
	}
	
}

void Apply_Consumption_Result::apply_optical_item(Optics item) {
	Overworld &world = *terra;
	
	switch (item) {
	case Optics::RadioWaves:
		world.event<Consumption_Of_RadioWaves>();  // In optometrist.cppm
		break;
	case Optics::MicroWaves:
		world.event<Consumption_Of_MicroWaves>();
		break;
	case Optics::InfraredWaves:	
		world.event<Consumption_Of_InfraredWaves>();
		break;
	case Optics::LightWaves:
		world.event<Consumption_Of_LightWaves>();
		break;
	case Optics::UltravioletWaves:
		world.event<Consumption_Of_UltravioletWaves>();
		break;
	case Optics::XRays:
		world.event<Consumption_Of_XRays>();
		break;
	case Optics::GammaRays:
		world.event<Consumption_Of_GammaRays>();
		break;
	}
}

void Open_Inventory::execute(Overworld &world) {
	Inventory potential_consumption = world.potential_consumption;
	
	if (potential_consumption.empty()) {
		world.announce.result(std::format(
			"{} has no items in their inventory that can be used.",
			world.getActivePlayerName()
		));
		return;
	}
	
	world.event<Media_Of_Consumption>();
	world.event<Consumption_Of_Optics>();
	world.event<Apply_Consumption_Of_Optics>();
}


} // namespace Parity