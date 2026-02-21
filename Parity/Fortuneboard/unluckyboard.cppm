export module Parity.UnluckyBoard;

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

export struct Apply_Unlucky_Board_Result : Rule
{
	void execute(Overworld &world) override {
		applyUnluckyBoardResult(world, world.die_roll_for_fortune_board);
	}
	void applyUnluckyBoardResult(Overworld &world, DieRoll roll) {
		// Logic to apply the result of the lucky board based on the die roll
		using enum DieRoll;
		switch (roll) {
		case One:
			world.announce.result("Trigger the Demon Board once.");
			break;
		case Two:
			world.announce.result("A Magnetic Demon spawns in this space and initiates combat.");
			break;
		case Three:
			world.announce.result("An Electric Minion spawns in this space and initiates combat.");
			break;
		case Four:
			world.announce.result("Lose 1 Heart.");
			break;
		case Five:
			world.announce.result("Lose 1 Gold Coin.");
			break;
		case Six:
			world.announce.result("Lose 3 Gold Coins.");
			break;
		}
	}
};

void Unlucky_Board::execute(Overworld &world) {
	world.announce.action(std::format(
		"{} rolls the Unlucky Board once.",
		to_string(world.active_player)
	));
	
	world.event<Roll_For_Random_Board>();
	world.event<Apply_Unlucky_Board_Result>();
}

} // namespace Parity

/* 
# Unlucky Board

Roll 1 die and apply the result:

1.  Trigger the Demon Board once.
2.  A Magnetic Demon spawns in this space and initiates combat.
3.  An Electric Minion spawns in this space and initiates combat.
4.  Lose 1 Heart.
5.  Lose 1 Gold Coin.
6.  Lose 3 Gold Coins.
*/