#if defined(__INTELLISENSE__)
	#include <memory>
	#include <print>
	#include "type-definition.cppm"
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

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	Overworld world;
	
	Parity::print_all_landmark_notations(); // Testing for now
	
	world.event<Welcome_Adventurer>(2); // Start the game with 2 adventurers
	world.event<First_Adventurer_Turn>(); // Start the first adventurer's turn
	world.event<Move_One_Space_Optional>(3); // Trigger the optional move event with 3 optional moves
	
	world.event<Next_Adventurer_Turn>(); // Move to the next adventurer's turn
	world.event<Move_One_Space_Optional>(2); // Trigger the optional move event with 2 optional moves
	
	world.event<Next_Adventurer_Turn>(); // Move to the next adventurer's turn
	world.event<Move_One_Space_Optional>(1); // Trigger the optional move event with 1 optional move
	world.event<Lucky_Board>(); // Trigger the lucky board event
	world.event<Event_Board>(); // Trigger the event board event
	
	/* do {
		world.event<Lucky_Board>();
	} while (world.event_queue.size() < 10); // Ensure at least 5 events are queued
	*/
	
	world.main_loop();
	std::print("{} now has {} Gold Coins and {} Power points.\n", 
		to_string(world.active_player),
		world.playerbase[world.active_player].gold_coin,
		world.playerbase[world.active_player].permanent_power_point
	);
	
	// print 10 empty lines
	for (int i = 0; i < 10; ++i) {
		std::print("\n");
	}
	return 0;
}

