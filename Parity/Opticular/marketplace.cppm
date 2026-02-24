export module Parity.Marketplace;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <map>
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.Optoelectronic;
	import Parity.OpticalNotation;
	import Parity.World;
	import Parity.Announcement;
	import Parity.Physiology;
	import Parity.Purchasement;
	import Parity.MarketMedia;
#endif

export namespace Parity
{

export struct Decline_Shop : Rule {
	void execute(Overworld &world) override {
		world.announce.result(std::format(
			"{} chose to not purchase any items from the Shop.",
			world.getActivePlayerName()
		));
	}
};

export struct Apply_Purchasement_Result : Rule {
	void execute(Overworld &world) override {
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
};

export struct Apply_Purchasement_Of_Optics : Rule {
	void execute(Overworld &world) override {
		Inventory purchasement = world.purchasement;
		
		if (purchasement.empty()) {
			world.event<Decline_Shop>();
		} else {
			world.event<Review_Of_Purchase>();
			world.event<Apply_Purchasement_Result>();
		}

	}
};


export struct Open_Shop : Rule {
	void execute(Overworld &world) override {
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
};


} // namespace Parity

/* 
- **» Action 3:** AmethystApprentice may purchase items from the Shop Board.
	- [x] **Radio Waves (2 Gold):** Use this item to call for support. Trigger the Lucky Board once.
	- [x] **Microwaves (2 Gold):** Use this item *after* winning a combat to cook the demon's meat. Heal 1 Heart upon consumption.
	- [x] **Infrared Waves (1 Gold):** Use this item to detect a demon's heat signature weakness. Reduce the demon's Power by 1 for that combat.
	- [ ] **Light Waves (3 Gold):** Use this item when landing on a Gradient space to choose the color effect instead of rolling the die for that turn's resolution.
		- Pink-Orange-Yellow Gradient: Choose Pink, Orange, or Yellow effect.
		- Red-Purple Gradient: Choose Red or Purple effect.
		- White-Gray Gradient: Choose *any* non-gradient color effect. The space retains this chosen color effect until changed again by this item.
	- [ ] **Ultraviolet Waves (5 Gold):** Use this item when entering a space with a demon. The demon retreats 1 space, and combat does not occur. This item cannot be used in the Demon Zone.
	- [ ] **X-Rays (5 Gold):** Use this item to scan a demon's internal structure. The player gains ==Advantage== status for that combat. When a player has this status, they roll 2 dice and use the higher result multiplied by their Power for their Attack Value.
	- [ ] **Gamma Rays (10 Gold):** Use this item in combat. The player's Power increases by 10 for that combat, and their attack hits *all* demons in the space.
- AmethystApprentice has ==6 Gold Coins==. They have no items in inventory; they may purchase upto 4 items from the Shop.
• » Choice ⟪ 1 2 3 4 5 6 7 x ⟫ : 3 3 1 2
- **» Result 3:** AmethystApprentice chose to purchase…
	1. ==Infrared Waves (1 Gold) × 2:== Use this item to detect a demon's heat signature weakness. Reduce the demon's Power by 1 for that combat.
	2. ==Radio Waves (2 Gold):== Use this item to call for support. Trigger the Lucky Board once.
	3. ==Microwaves (2 Gold):== Use this item after winning a combat to cook the demon's meat. Heal 1 Heart upon consumption.
	- With the total cost of ==6 Gold==.
	- Inventory of AmethystApprentice now includes:
	1. ==Infrared Waves==
	2. ==Infrared Waves==
	3. ==Microwaves==
	4. ==Radio Waves==
	- AmethystApprentice now has ==0 Gold Coins==.
- *Gave 2 [Infrared Waves] to AmethystApprentice*
- *Gave 1 [Microwaves] to AmethystApprentice*
- *Gave 1 [Radio Waves] to AmethystApprentice*
- *Clear 6 [Gold Coin] from AmethystApprentice*
- **» Action 4:** AmethystApprentice ends their turn.
*/