export module Parity.LuckyBoard;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <print>
	#include <format>
	#include <string>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.DieRoll;
	import Parity.FortuneBoard;
	import Parity.Biology;
	import Parity.Physiology;
	import Parity.World;
	import Parity.Journey;
	import Parity.Announcement;
#endif

export namespace Parity
{

export struct Double_Lucky_Board_Multiplier : Rule
{
	void execute(Overworld &world) override {
		world.lucky_board_multiplier *= 2;
		
		world.announce.bygone(std::format(
			"Doubled Fortune Board multiplier to {}.",
			world.lucky_board_multiplier
		));
	}
};

export struct Move_Again_One_Space : Rule
{
	void execute(Overworld &world) override {
		int amount_of_move = 1 * world.useLuckyBoardMultiplier();
		world.announce.bygone(std::format(
			"Move again {} space{} (optional).",
			amount_of_move, amount_of_move > 1 ? "s" : ""
		));
		
		world.event<Move_One_Space_Optional>(amount_of_move);
	}
};

export struct Apply_Lucky_Board_Result : Rule
{
	void execute(Overworld &world) override {
		applyLuckyBoardResult(world, world.die_roll_for_fortune_board);
	}
	void applyLuckyBoardResult(Overworld &world, DieRoll roll) {
		// Logic to apply the result of the lucky board based on the die roll
		using enum DieRoll;
		switch (roll) {
		case One:
			world.announce.result("Trigger the Event Board once.");
			for (int i = 0; i < world.useLuckyBoardMultiplier(); ++i) {
				world.event<Event_Board>();
			}
			break;
		case Two:
			world.announce.result("Trigger the Lucky Board again, but the result is doubled.");
			world.event<Double_Lucky_Board_Multiplier>();
			world.event<Lucky_Board>();
			break;
		case Three:
			world.announce.result("Move again 1 space (optional).");
			world.event<Move_Again_One_Space>();
			break;
		case Four:
			world.announce.result("Gain 1 Gold Coin.");
			world.event<Gain_Gold_Coin>(1 * world.useLuckyBoardMultiplier());
			break;
		case Five:
			world.announce.result("Gain 1 permanent Power point.");
			world.event<Gain_Permanent_Power_Point>(1 * world.useLuckyBoardMultiplier());
			break;
		case Six:
			world.announce.result("Gain 5 Gold Coins.");
			world.event<Gain_Gold_Coin>(5 * world.useLuckyBoardMultiplier());
			break;
		}
	}
};

void Lucky_Board::execute(Overworld &world) {
	world.announce.action(std::format(
		"{} rolls the Lucky Board once.",
		to_string(world.active_player)
	));
	
	world.event<Roll_For_Random_Board>();
	world.event<Apply_Lucky_Board_Result>();
} // Logic to roll on the board


int Overworld::useLuckyBoardMultiplier() {
		int current_multiplier = lucky_board_multiplier;
		lucky_board_multiplier = 1; // Reset after use
		return current_multiplier;
	}

} // namespace Parity

/* 
- **» Action 3:** AmethystApprentice rolls the Lucky Board once.
- Roll 1 die and apply the result…
	- [ ] Trigger the Event Board once.
	- [ ] Trigger the Lucky Board again, but the result is doubled.
	- [ ] Move again 1 space (optional).
	- [x] Gain 1 Gold Coin.
	- [ ] Gain 1 permanent Power point.
	- [ ] Gain 5 Gold Coins.
- **« Result 3:** Gain 1 ==Gold Coin==
*/