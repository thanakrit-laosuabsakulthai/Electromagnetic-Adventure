export module Parity.UnluckyBoard;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
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
#endif

export namespace Parity
{

export struct Media_Of_Unlucky_Board : Rule {
	void execute(Overworld &world) override {
		world.announce.subtitle("Roll 1 die and apply the result...");
		
		world.announce.beginChoice();
		for (const auto& media : outcomes) {
			world.announce.choice(media);
		}
	}
	
	static inline const std::vector<std::string> outcomes = {
		"Trigger the Demon Board once.",
		"A Magnetic Demon spawns in this space and initiates combat.",
		"An Electric Minion spawns in this space and initiates combat.",
		"Lose 1 Heart.",
		"Lose 1 Gold Coin.",
		"Lose 3 Gold Coins."
	};
};

export struct Apply_Unlucky_Board_Result : Rule
{
	void execute(Overworld &world) override {
		applyUnluckyBoardResult(world, world.die_roll_for_fortune_board);
	}
	void applyUnluckyBoardResult(Overworld &world, DieRoll roll) {
		world.announce.result(Media_Of_Unlucky_Board::outcomes[static_cast<int>(roll) - 1]);
		
		using enum DieRoll;
		switch (roll) {
		case One:
			world.event<Demon_Board>();
			break;
		case Two:
			break;
		case Three:
			break;
		case Four:
			world.event<Vitality_Hurt>(1);
			break;
		case Five:
			world.event<Take_Gold_Coin>(1);
			break;
		case Six:
			world.event<Take_Gold_Coin>(3);
			break;
		}
	}
};

void Unlucky_Board::execute(Overworld &world) {
	world.announce.action(std::format(
		"{} rolls the Unlucky Board once.",
		to_string(world.active_player)
	));
	
	world.event<Media_Of_Unlucky_Board>();
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