export module Parity.DemonBoard;

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

/* 
# Demon Board

Roll 1 die and apply the result:

1.  All non-Boss demons move 1 space towards a player.
2.  Summon Electric Minion on the Red Square space and initiates combat with players on that space.
3.  A Magnetic Mage Demon spawns on the Purple Diamond space and moves 1 space towards a player.
4.  A Magnetic Demon spawns on the Purple Diamond space and moves 2 spaces towards a player.
5.  All players currently in the Demon Zone (Red area) lose 1 Heart.
6.  Roll a die to determine which demon spawns on the Purple Diamond space and moves 3 spaces towards a player:
    *   1-2: Electric Minion
    *   3-4: Magnetic Demon
    *   5-6: Magnetic Mage Demon
*/

export namespace Parity
{
//

export struct Media_Of_Demon_Board : Rule {
	void execute(Overworld &world) override {
		world.announce.subtitle("Roll 1 die and apply the result...");
		
		world.announce.beginChoice();
		for (const auto& media : outcomes) {
			world.announce.choice(media);
		}
	}
	
	static inline const std::vector<std::string> outcomes = {
		"All non-Boss demons move 1 space towards a player.",
		"Summon Electric Minion on the Red Square space and initiates combat.",
		"A Magnetic Mage Demon spawns on the Purple Diamond space and moves 1 space towards a player.",
		"A Magnetic Demon spawns on the Purple Diamond space and moves 2 spaces towards a player.",
		"All players currently in the Demon Zone (Red area) lose 1 Heart.",
		"Roll a die to spawn a demon on the Purple Diamond space and moves 3 spaces towards a player:\n\t\t• 1-2: Electric Minion\n\t\t• 3-4: Magnetic Demon\n\t\t• 5-6: Magnetic Mage Demon"
	};
};

export struct Apply_Demon_Board_Result : Rule
{
	void execute(Overworld &world) override {
		applyDemonBoardResult(world, world.die_roll_for_fortune_board);
	}
	void applyDemonBoardResult(Overworld &world, DieRoll roll) {
		world.announce.result(Media_Of_Demon_Board::outcomes[static_cast<int>(roll) - 1]);
		
		using enum DieRoll;
		switch (roll) {
		case One:
			break;
		case Two:
			break;
		case Three:
			break;
		case Four:
			break;
		case Five:
			break;
		case Six:
			break;
		}
	}
};

void Demon_Board::execute(Overworld &world) {
	world.announce.action(std::format(
		"{} rolls the Demon Board once.",
		to_string(world.active_player)
	));
	
	world.event<Media_Of_Demon_Board>();
	world.event<Roll_For_Random_Board>();
	world.event<Apply_Demon_Board_Result>();
}

} // namespace Parity