#if defined(__INTELLISENSE__)
	#include <memory>
	#include <print>
	#include "type-definition.cppm"
	
	#include <set>
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
	
	// Parity::print_all_landmark_notations(); // Testing for now
	
	// world.event<Showcase_Adventurer_Turn>();
	// world.event<Showcase_Reincarnation>();
	// world.event<Showcase_Movement>();
	
	
	world.event<Welcome_Adventurer>(1);
	world.event<First_Adventurer_Turn>();
	world.event<Mediumship_Of_Corruption>();
	/*
	world.event<All_Players_In_Demon_Zone_Lose_One_Heart>();
	world.event<Move_One_Space_Optional>(10);
	world.event<All_Players_In_Demon_Zone_Lose_One_Heart>();
	
	
	// world.event<Gift_Of_Optics>();
	/*
	world.event<Gain_Gold_Coin>(10);
	world.event<Open_Delivery>();
	
	world.event<Gain_Optical_Item>(Optics::GammaRays);
	world.event<Gain_Optical_Item>(Optics::UltravioletWaves);
	world.event<Gain_Optical_Item>(Optics::MicroWaves);
	world.event<Summon_Demon>(DemonForm::ElectricMinion, Landmark::DiamondOfParity);
	world.event<Move_Demon_Towards_Player>(4);
	/*
	//world.event<Excellece_Of_Consumption>();
	world.event<Knockback_Adventurer>();
	world.event<Knockback_Adventurer>(); */
	
	world.main_loop();
	std::print("{} now has {} Gold Coins and {} Power points.\n", 
		to_string(world.active_player),
		world.playerbase[world.active_player].gold_coin,
		world.playerbase[world.active_player].permanent_power_point
	);
	
	/**/
	// print 10 empty lines
	for (int i = 0; i < 10; ++i) {
		std::print("\n");
	}
	return 0;
}

