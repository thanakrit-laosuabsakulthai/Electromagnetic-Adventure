export module Parity.Marketplace;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <map>
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.Geography;
	import Parity.Notation;
	import Parity.Optoelectronic;
	import Parity.OpticalNotation;
	import Parity.World;
	import Parity.Announcement;
#endif

export namespace Parity
{
export struct Media_Of_Marketplace : Rule {
	Overworld *terra = nullptr;
	
	void execute(Overworld &world) override {
		terra = &world; // for helper functions
		
		world.announce.action(std::format(
			"{} may purchase items from the Shop Board.",
			world.getActivePlayerName()
		));
		
		display_market();
		display_player_possesion_hint();
	}
	
	void display_market() {
		Overworld &world = *terra;
		
		world.announce.beginChoice();
		
		for (const auto& [optic, price] : Marketplace) {
			std::string optical_item_title = std::format("{} ({} Gold)", to_string(optic), price);
			
			world.announce.choice(optical_item_title);
		}
	}
	
	void display_player_possesion_hint() {
		Overworld &world = *terra;
		PlayerIdentity active_player = world.active_player;
		const PlayerPosession& player_possession = world.playerbase.at(active_player);
		
		std::string gold_coin_hint = bold(
			std::format("{} Gold Coin{}",
				player_possession.gold_coin,
				player_possession.gold_coin == 1 ? "" : "s"
			)
		);
		
		int amount_of_item_in_inventory = static_cast<int>(player_possession.inventory.size());
		std::string item_in_inventory_hint = std::format("{} item{}",
			amount_of_item_in_inventory > 0 ? std::to_string(amount_of_item_in_inventory) : "no",
			amount_of_item_in_inventory == 1 ? "" : "s"
		);
		
		int remaining_inventory_capacity = player_possession.inventory_capacity - amount_of_item_in_inventory;
		std::string remaining_inventory_capacity_hint = std::format("{} item{}",
			remaining_inventory_capacity,
			remaining_inventory_capacity == 1 ? "" : "s"
		);
		
		world.announce.linger(std::format("{} has {}. They have {} in inventory.",
			world.getActivePlayerName(),
			gold_coin_hint,
			item_in_inventory_hint
		));
		
		if (remaining_inventory_capacity == 0) {
			world.announce.linger("Their inventory is full. They cannot purchase any more items from the Shop.");
		} else {
			world.announce.linger(std::format("{} may purchase upto {} from the Shop.",
				world.getActivePlayerName(),
				remaining_inventory_capacity_hint
			));
		}
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