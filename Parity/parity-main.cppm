#if defined(__INTELLISENSE__)
	#include <memory>
	#include <print>
	#include "type-definition.cppm"
	
	#include <set>
#else
	import Parity;
	import std; // Standard library import
#endif

using namespace Parity;

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	Overworld world;
	
	// Parity::print_all_landmark_notations(); // Testing for now

	world.announce.suspense_level = 1;
	world.event<Rule_Of_Adventure>();
	
	// world.event<Amusement_A>();
	
	world.main_loop();
	std::print("{} now has {} Gold Coins and {} Power points.\n", 
		to_string(world.active_player),
		world.playerbase[world.active_player].gold_coin,
		world.playerbase[world.active_player].permanent_power_point
	);
	
	for (int i = 0; i < 10; ++i) {
		std::print("\n");
	}
	return 0;
}

