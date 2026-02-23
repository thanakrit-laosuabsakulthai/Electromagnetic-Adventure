export module Parity.FortuneBoard;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <print>
	#include <format>
	#include <string>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.DieRoll;
	import Parity.World;
	import Parity.Announcement;
#endif

export namespace Parity
{

export struct Roll_For_Random_Board : Rule
{
	void execute(Overworld &world) override {
		world.die_roll_for_fortune_board = static_cast<DieRoll>((std::rand() % 6) + 1);
		
		world.announce.bygone(std::format(
			"Rolled [{}] on the die.",
			static_cast<int>(world.die_roll_for_fortune_board)
		));
	}
};

export struct Lucky_Board : Rule
{
	void execute(Overworld &world) override;
};

export struct Event_Board : Rule
{
	void execute(Overworld &world) override;
};

export struct Unlucky_Board : Rule
{
	void execute(Overworld &world) override;
};

export struct Demon_Board : Rule
{
	void execute(Overworld &world) override;
};

} // namespace Parity