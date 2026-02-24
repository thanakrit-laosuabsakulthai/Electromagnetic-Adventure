export module Parity.MarketMedia;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
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
	import Parity.Encyclopedia;
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
		
		for (const auto& [optic, price] : world.marketplace) {
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
		

		world.announce.linger(std::format("{} may purchase upto {} from the Shop.",
			world.getActivePlayerName(),
			remaining_inventory_capacity_hint
		));
		}
};

export struct Review_Of_Purchase : Rule {
	Overworld *terra = nullptr;
	void execute(Overworld &world) override {
		terra = &world; // for helper functions
		
		display_purchasement();
		display_inventory();
	}
	void display_purchasement();
	void display_inventory();
};

void Review_Of_Purchase::display_purchasement() {
	
	Overworld &world = *terra;
	
	world.announce.result(std::format("{} chose to purchase...", world.getActivePlayerName()));
	
	// iterate over world.purchasement (multiset) and display each item
	std::map<Optics, int> item_count; // to count occurrences of each item
	for (const auto& item : world.purchasement) {
		item_count[item]++;
	}
	
	world.announce.beginAnalog();
	
	for (const auto& [optic, count] : item_count) {
		int price = world.marketplace.at(optic);
		
		std::string item_caption = std::format("{} ({} Gold)", to_string(optic), price);
		// std::string item_description = std::string(to_description(optic));
		
		if (count > 1) {
			item_caption += std::format(" × {}", count);
		}
		
		/* world.announce.analog(std::format("{} {}",
			bold_cyan(item_caption + ":"),
			item_description
		)); */
		
		world.announce.analogical(std::format("{}",
			bold_cyan(item_caption)
		));
	}
	
	int total_cost = 0;
	for (const auto& item : world.purchasement) {
		total_cost += world.marketplace.at(item);
	}
	
	world.announce.overhang(std::format("With the total cost of {}.",
		bold(std::to_string(total_cost) + " Gold")
	));
}


void Review_Of_Purchase::display_inventory() {
	Overworld &world = *terra;
	PlayerIdentity active_player = world.active_player;
	PlayerPosession& player_possession = world.playerbase[active_player];
	
	// Don't add purchased items to inventory yet
	
	world.announce.overhang(std::format("Inventory of {} now includes:",
		world.getActivePlayerName()
	));
	
	Inventory inventory_preview = player_possession.inventory; // start with current inventory
	for (const Optics& item : world.purchasement) {
		inventory_preview.insert(item); // add purchased items to preview
	}
	
	// Display each item in inventory_preview
	world.announce.beginAnalog();
	for (const auto& item : inventory_preview) {
		std::string item_name = std::string(to_string(item));
		world.announce.analog(std::format("{}",
			bold(item_name)
		));
	}
	
	// Display remaining gold coins
	int total_cost = 0;
	for (const auto& item : world.purchasement) {
		total_cost += world.marketplace.at(item);
	}
	
	int remaining_gold = player_possession.gold_coin - total_cost;
	
	world.announce.linger(std::format("{} now has {} Gold Coins.",
		world.getActivePlayerName(),
		bold(std::to_string(remaining_gold))
	));
}

/* 
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
*/

/* 
export struct Query_Of_Passage : Rule {
	void execute(Overworld &world) override {
		std::string query_dialect = dialect_synthesis(world.expedition.choice_of_direction.vector());
		
		if (world.expedition.is_journey_optional) {
			query_dialect += " " + std::string(world.encyclopedia.decline_journey);
		}
		
		std::string content_of_query = bag_notation_synthesis(query_dialect);
		
		world.announce.ask(content_of_query);
	}
};
*/

} // namespace Parity