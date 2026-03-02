export module Parity.EventBoard;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <print>
	#include <format>
	#include <string>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.DieRoll;
	import Parity.OpticalNotation;
	import Parity.Optoelectronic;
	
	import Parity.FortuneBoard;
	import Parity.Physiology;
	import Parity.Marketplace;
#endif

export namespace Parity
{

export struct All_Players_Gain_Gold_Coin : Rule
{
	int amount_of_gold_coin;
	All_Players_Gain_Gold_Coin(int amount) : amount_of_gold_coin(amount) {}
	void execute(Overworld &world) override {
		for (auto& [player_identity, posession] : world.playerbase) {
			posession.gold_coin += amount_of_gold_coin;
		}
		
		world.announce.bygone(std::format(
			"Gave {} [Gold Coin] to all players.",
			amount_of_gold_coin
		));
	} 
};


export struct Apply_Gift_Of_Optics : Rule {
	void execute(Overworld &world) override {
		DieRoll roll = world.die_roll_for_fortune_board;
		int optic_index = static_cast<int>(roll) - 1; // Convert DieRoll to 0-based index
		
		if (! (optic_index >= 0 && optic_index < static_cast<int>(obtainable_optical_items.size())) ) {
			return; // Invalid die roll, do nothing
		}
		
		Optics aquired_optic = obtainable_optical_items[optic_index];
		world.event<Gain_Optical_Item>(aquired_optic);
		
		world.announce.result(std::format(
			"{} received {} for free.",
			to_string(world.active_player),
			bold_cyan(std::string(to_string(aquired_optic)))
		));
	}

	static inline const std::vector<Optics> obtainable_optical_items = {
		Optics::RadioWaves,
		Optics::MicroWaves,
		Optics::InfraredWaves,
		Optics::LightWaves,
		Optics::UltravioletWaves,
		Optics::XRays
		// Note: Gamma Rays is unobtainable from this result
	};

};

export struct Gift_Of_Optics : Rule {
	Overworld *terra = nullptr;
	
	void execute(Overworld &world) override {
		terra = &world; // for helper functions
		// Check inventory capacity 
		
		PlayerIdentity active_player = world.active_player;
		PlayerPosession& possession = world.playerbase.at(active_player);
		
		int inventory_capacity = possession.inventory_capacity;
		int current_inventory_size = static_cast<int>(possession.inventory.size());
		
		if (current_inventory_size >= inventory_capacity) {
			world.announce.result(std::format(
				"{} already has {} item{} in inventory and cannot receive more from the Shop Board.",
				world.getActivePlayerName(),
				current_inventory_size,
				current_inventory_size == 1 ? "" : "s"
			));
			return;
		}
		
		// Logic to give the player a free random item from the shop
		world.announce.action(std::format(
			"{} rolls a die to receive an item...",
			to_string(world.active_player)
		));
		
		display_gift_of_optics();
		
		world.event<Roll_For_Random_Board>();
		world.event<Apply_Gift_Of_Optics>();
	}
	
		
	void display_gift_of_optics() {
		Overworld &world = *terra;
		std::vector<Optics> obtainable_optical_items = Apply_Gift_Of_Optics::obtainable_optical_items;
		
		world.announce.beginChoice();
		for (const auto& optic : obtainable_optical_items) {
			world.announce.choice(std::string(to_string(optic)));
		}
	}
};


export struct Media_Of_Event_Board : Rule {
	void execute(Overworld &world) override {
		world.announce.subtitle("Roll 1 die and apply the result...");
		world.announce.beginChoice();
		
		for (const auto& media : outcomes) {
			world.announce.choice(media);
		}
	}
	
	static inline const std::vector<std::string> outcomes = {
		"Trigger the Demon Board once.",
		"Trigger the Unlucky Board once.",
		"Trigger the Lucky Board once.",
		"Purchase 1 item from the Shop (pay cost as normal).",
		"All players gain 1 Gold Coin.",
		"Roll a die to receive 1 free random item from the Shop."
	};
};

export struct Apply_Event_Board_Result : Rule
{
	void execute(Overworld &world) override {
		applyEventBoardResult(world, world.die_roll_for_fortune_board);
	}
	void applyEventBoardResult(Overworld &world, DieRoll roll) {
		// world.announce.result(Media_Of_Event_Board::outcomes[static_cast<int>(roll) - 1]);
		std::string result_description = Media_Of_Event_Board::outcomes[static_cast<int>(roll) - 1];
		
		using enum DieRoll;
		switch (roll) {
		case One:
			world.event<Demon_Board>();
			world.announce.result(std::format(
				"Trigger the {} once.",
				bold_cyan("Demon Board")
			));
			break;
		case Two:
			world.event<Unlucky_Board>();
			world.announce.result(std::format(
				"Trigger the {} once.",
				bold_cyan("Unlucky Board")
			));
			break;
		case Three:
			world.event<Lucky_Board>();
			world.announce.result(std::format(
				"Trigger the {} once.",
				bold_cyan("Lucky Board")
			));
			break;
		case Four:
			// Logic to allow the player to purchase an item from the shop
			world.event<Open_Delivery>();
			world.announce.result(result_description);
			break;
		case Five:
			world.event<All_Players_Gain_Gold_Coin>(1);
			world.announce.result(result_description);
			break;
		case Six:
			// Logic to roll a die and give the player a free random item from the shop
			world.event<Gift_Of_Optics>();
			world.announce.result(result_description);
			break;
		}
	}
};

void Event_Board::execute(Overworld &world) {
	world.announce.action(std::format(
		"{} rolls the Event Board once.",
		to_string(world.active_player)
	));
	
	world.event<Media_Of_Event_Board>();
	world.event<Roll_For_Random_Board>();
	world.event<Apply_Event_Board_Result>();
}

} // namespace Parity

/* 
# Event Board

Roll 1 die and apply the result:

1.  Trigger the Demon Board once.
2.  Trigger the Unlucky Board once.
3.  Trigger the Lucky Board once.
4.  Purchase 1 item from the Shop (pay cost as normal).
5.  All players gain 1 Gold Coin.
6.  Roll a die to receive 1 free random item from the Shop (Gamma Rays is unobtainable from this result).
*/