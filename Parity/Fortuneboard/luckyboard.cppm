export module Parity.LuckyBoard;

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
	import Parity.Biology;
	
	import Parity.FortuneBoard;
	import Parity.Physiology;
	import Parity.Journey;
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

export struct Media_Of_Lucky_Board : Rule
{
	void execute(Overworld &world) override {
		world.announce.subtitle("Roll 1 die and apply the result...");
		
		world.announce.beginChoice();
		for (const auto& media : outcomes) {
			world.announce.choice(media);
		}
		
	}
	
	static inline const std::vector<std::string> outcomes = {
		"Trigger the Event Board once.",
		"Trigger the Lucky Board again, but the result is doubled.",
		"Move again 1 space (optional).",
		"Gain 1 Gold Coin.",
		"Gain 1 permanent Power point.",
		"Gain 5 Gold Coins."
	};
};

export struct Apply_Lucky_Board_Result : Rule
{
	void execute(Overworld &world) override {
		applyLuckyBoardResult(world, world.die_roll_for_fortune_board);
	}
	void applyLuckyBoardResult(Overworld &world, DieRoll roll) {
		std::string result_description = Media_Of_Lucky_Board::outcomes[static_cast<int>(roll) - 1];
		
		int multiplier = 1;
		if (roll != DieRoll::Two && roll != DieRoll::Three) { // The multiplier only applies to certain outcomes
			multiplier = world.useLuckyBoardMultiplier();
		}
		
		using enum DieRoll;
		switch (roll) {
		case One:
			for (int i = 0; i < multiplier; ++i) {
				world.event<Event_Board>();
			}
			if (multiplier > 1) {
				world.announce.result(std::format(
					"Trigger the {} {} times.",
					bold_cyan("Event Board"),
					multiplier
				));
			} else {
				world.announce.result(std::format(
					"Trigger the {} once.",
					bold_cyan("Event Board")
				));
			}
			break;
		case Two:
			world.event<Double_Lucky_Board_Multiplier>();
			world.event<Lucky_Board>();
			world.announce.result(std::format(
				"Trigger the {} again, but the result is doubled.",
				bold_cyan("Lucky Board")
			));
			break;
		case Three:
			world.event<Move_Again_One_Space>();
			world.announce.result(result_description);
			break;
		case Four:
			world.event<Gain_Gold_Coin>(1 * multiplier);
			world.announce.result(result_description);
			break;
		case Five:
			world.event<Gain_Permanent_Power_Point>(1 * multiplier);
			world.announce.result(result_description);
			break;
		case Six:
			world.event<Gain_Gold_Coin>(5 * multiplier);
			world.announce.result(result_description);
			break;
		}
	}
};

void Lucky_Board::execute(Overworld &world) {
	world.announce.action(std::format(
		"{} rolls the Lucky Board once.",
		to_string(world.active_player)
	));
	
	world.event<Media_Of_Lucky_Board>();
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