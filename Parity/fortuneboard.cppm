export module Parity.FortuneBoard;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <print>
	#include "type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.DieRoll;
	import Parity.Biology;
	import Parity.World;
#endif
export namespace Parity
{

export struct Gain_Gold_Coin : Rule
{
	int amount_of_gold_coin;
	Gain_Gold_Coin(int amount) : amount_of_gold_coin(amount) {}
	void execute(Overworld &world) override {
		amount_of_gold_coin *= world.useFortuneBoardMultiplier();
		
		world.playerbase[world.active_player].gold_coin += amount_of_gold_coin;
		std::print("Gave {} [Gold Coin] to {}.\n", amount_of_gold_coin, to_string(world.active_player));
	}
};

export struct Gain_Permanent_Power_Point : Rule
{
	int amount_of_permanent_power;
	Gain_Permanent_Power_Point(int amount) : amount_of_permanent_power(amount) {}
	void execute(Overworld &world) override {
		amount_of_permanent_power *= world.useFortuneBoardMultiplier();
		
		world.playerbase[world.active_player].permanent_power_point += amount_of_permanent_power;
		std::print("Gave {} [Permanent Power] to {}.\n", amount_of_permanent_power, to_string(world.active_player));
	}
};

export struct Double_Fortune_Board_Multiplier : Rule
{
	void execute(Overworld &world) override {
		world.fortune_board_multiplier *= 2;
		std::print("Doubled Fortune Board Multiplier to {}.\n", world.fortune_board_multiplier);
	}
}; 

struct Lucky_Board; // Forward declaration

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
			std::print("Apply Lucky Board Result: Trigger the Event Board once.\n");
			break;
		case Two:
			std::print("Apply Lucky Board Result: Trigger the Lucky Board again, but the result is doubled.\n");
			world.event<Double_Fortune_Board_Multiplier>();
			world.event<Lucky_Board>();
			break;
		case Three:
			std::print("Apply Lucky Board Result: Move again 1 space (optional).\n");
			break;
		case Four:
			std::print("Apply Lucky Board Result: Gain 1 Gold Coin.\n");
			world.event<Gain_Gold_Coin>(1);
			break;
		case Five:
			std::print("Apply Lucky Board Result: Gain 1 permanent Power point.\n");
			world.event<Gain_Permanent_Power_Point>(1);
			break;
		case Six:
			std::print("Apply Lucky Board Result: Gain 5 Gold Coins.\n");
			world.event<Gain_Gold_Coin>(5);
			break;
		}
	}
};

export struct Roll_For_Random_Board : Rule
{
	void execute(Overworld &world) override {
		world.die_roll_for_fortune_board = static_cast<DieRoll>((std::rand() % 6) + 1);
	}
};

export struct Lucky_Board : Rule
{
	void execute(Overworld &world) override {
		world.event<Roll_For_Random_Board>();
		world.event<Apply_Lucky_Board_Result>();
	} // Logic to roll on the board
};

} // namespace Parity