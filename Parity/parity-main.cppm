#if defined(__INTELLISENSE__)
	#include "overworld.cppm" // Use the shim header for IntelliSense
	#include <memory>
	#include <print>
#else
	import Parity;
	import std; // Standard library import
#endif

/*
apply the result:

1.  Trigger the Event Board once.
2.  Trigger the Lucky Board again, but the result is doubled.
3.  Move again 1 space (optional).
4.  Gain 1 Gold Coin.
5.  Gain 1 permanent Power point.
6.  Gain 5 Gold Coins.

just print the action for now
*/
using namespace Parity;

struct Apply_Lucky_Board_Result_Rule : Rule
{
	void execute(Overworld &world) override {
		applyLuckyBoardResult(world, world.die_roll_for_random_board);
	}
	void applyLuckyBoardResult(Overworld &world, DieRoll roll) {
		// Logic to apply the result of the lucky board based on the die roll
		using enum DieRoll;
		switch (roll) {
		case One:
			std::print("Apply Lucky Board Result: Trigger the Event Board once.\n");
			break;
		case Two:
			std::print("Apply Lucky Board Result: Trigger the Lucky Board again, but the result is doubled.\n");
			break;
		case Three:
			std::print("Apply Lucky Board Result: Move again 1 space (optional).\n");
			break;
		case Four:
			std::print("Apply Lucky Board Result: Gain 1 Gold Coin.\n");
			break;
		case Five:
			std::print("Apply Lucky Board Result: Gain 1 permanent Power point.\n");
			break;
		case Six:
			std::print("Apply Lucky Board Result: Gain 5 Gold Coins.\n");
			break;
		}
	}
};


struct Roll_For_Random_Board_Rule : Rule
{
	void execute(Overworld &world) override {
		world.die_roll_for_random_board = static_cast<DieRoll>((std::rand() % 6) + 1);
	}
};

struct Lucky_Board_Rule : Rule
{
	void execute(Overworld &world) override {
		world.event_queue.push_back(std::make_unique<Roll_For_Random_Board_Rule>());
		world.event_queue.push_back(std::make_unique<Apply_Lucky_Board_Result_Rule>());
	} // Logic to roll on the board
};

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	Overworld world;
	world.event_queue.push_back(std::make_unique<Lucky_Board_Rule>());
	world.main_loop();
	return 0;
}

// Parity::DieRoll roll = Parity::DieRoll::One;