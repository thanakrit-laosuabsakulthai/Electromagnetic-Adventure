export module Parity.EventBoard;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <print>
	#include <format>
	#include <string>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.DieRoll;
	import Parity.FortuneBoard;
	import Parity.Physiology;
	import Parity.World;
	import Parity.Announcement;
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

export struct Apply_Event_Board_Result : Rule
{
	void execute(Overworld &world) override {
		applyEventBoardResult(world, world.die_roll_for_fortune_board);
	}
	void applyEventBoardResult(Overworld &world, DieRoll roll) {
		// Logic to apply the result of the lucky board based on the die roll
		using enum DieRoll;
		switch (roll) {
		case One:
			world.announce.result("Trigger the Demon Board once.");
			break;
		case Two:
			world.announce.result("Trigger the Unlucky Board once.");
			world.event<Unlucky_Board>();
			break;
		case Three:
			world.announce.result("Trigger the Lucky Board once.");
			world.event<Lucky_Board>();
			break;
		case Four:
			world.announce.result("Purchase 1 item from the Shop (pay cost as normal).");
			// Logic to allow the player to purchase an item from the shop
			break;
		case Five:
			world.announce.result("All players gain 1 Gold Coin.");
			world.event<All_Players_Gain_Gold_Coin>(1);
			break;
		case Six:
			world.announce.result("Roll a die to receive 1 free random item from the Shop (Gamma Rays is unobtainable from this result).");
			// Logic to roll a die and give the player a free random item from the shop
			break;
		}
	}
};

void Event_Board::execute(Overworld &world) {
	world.announce.action(std::format(
		"{} rolls the Event Board once.",
		to_string(world.active_player)
	));
	
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