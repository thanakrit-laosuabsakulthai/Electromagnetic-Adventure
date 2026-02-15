export module Parity.FortuneBoard;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <print>
	#include <format>
	#include <string>
	#include "type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.DieRoll;
	import Parity.Biology;
	import Parity.World;
	import Parity.Announcement;
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
		
		std::string_view active_player_name = to_string(world.active_player);
		std::string bygone_text = std::vformat("Gave {} [Gold Coin] to {}.", std::make_format_args(amount_of_gold_coin, active_player_name));
		world.announce.bygone(bygone_text);
	}
};

export struct Gain_Permanent_Power_Point : Rule
{
	int amount_of_permanent_power;
	Gain_Permanent_Power_Point(int amount) : amount_of_permanent_power(amount) {}
	void execute(Overworld &world) override {
		amount_of_permanent_power *= world.useFortuneBoardMultiplier();
		
		std::string_view active_player_name = to_string(world.active_player);
		std::string bygone_text = std::vformat("Gave {} [permanent Power Point] to {}.", std::make_format_args(amount_of_permanent_power, active_player_name));
		world.announce.bygone(bygone_text);
	}
};

export struct Double_Fortune_Board_Multiplier : Rule
{
	void execute(Overworld &world) override {
		world.fortune_board_multiplier *= 2;
		
		std::string_view active_player_name = to_string(world.active_player);
		std::string bygone_text = std::vformat("Doubled the Fortune Board multiplier for {}.", std::make_format_args(active_player_name));
		world.announce.bygone(bygone_text);
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
			world.announce.result("Trigger the Event Board once.");
			break;
		case Two:
			world.announce.result("Trigger the Lucky Board again, but the result is doubled.");
			world.event<Double_Fortune_Board_Multiplier>();
			world.event<Lucky_Board>();
			break;
		case Three:
			world.announce.result("Move again 1 space (optional).");
			break;
		case Four:
			world.announce.result("Gain 1 Gold Coin.");
			world.event<Gain_Gold_Coin>(1);
			break;
		case Five:
			world.announce.result("Gain 1 permanent Power point.");
			world.event<Gain_Permanent_Power_Point>(1);
			break;
		case Six:
			world.announce.result("Gain 5 Gold Coins.");
			world.event<Gain_Gold_Coin>(5);
			break;
		}
	}
};

export struct Roll_For_Random_Board : Rule
{
	void execute(Overworld &world) override {
		world.die_roll_for_fortune_board = static_cast<DieRoll>((std::rand() % 6) + 1);
		
		// std::string die_number = std::to_string(static_cast<int>(world.die_roll_for_fortune_board));
		// world.announce.bygone(std::vformat("Rolled [{}] on the die.", std::make_format_args(die_number)));
	}
};

export struct Lucky_Board : Rule
{
	void execute(Overworld &world) override {
		std::string_view active_player_name = to_string(world.active_player);
		std::string action_text = std::vformat("{} rolls the Lucky Board once.", std::make_format_args(active_player_name));
		world.announce.action(action_text);
		
		world.event<Roll_For_Random_Board>();
		world.event<Apply_Lucky_Board_Result>();
	} // Logic to roll on the board
};

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