export module Parity.Amusement;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include "../type-definition.cppm"
#else
	import Parity.World;
	
	import Parity.Necromancy;
	import Parity.Physiology;
	import Parity.Marketplace;
	import Parity.Warfare;
	import Parity.Adventure;
	import Parity.Journey;
	import Parity.FortuneBoard;
	import Parity.ScoutFly;
#endif

export namespace Parity
{
//

export struct Amusement_A : Rule {
	void execute(Overworld &world) override {
		world.certainty = {
			// for [2] adventurers in game
			4, // gain 1 gold coin
			2, // trigger the unlucky board once
			1, // trigger the demon board once
			2, // an electric minion on the red square space
			// Night [1]
			4, // magnetic demon
			3, // 1: aboveright, 2: below, 3: left (cataclysm)
			// Day [2]
			5, // all players gain 1 gold coin
			6, // player combat strength
			6, // demon combat strength
			4, // player combat strength (redraw)
			5, // demon combat strength (redraw)
			6, // recieve free item from the shop
			5, // ultraviolet waves
			// Night [2]
			1, // all lesser demons move 1 space
			// Day [3]
			3, // move 1 space again (optional)
			6, // player combat strength
			1, // demon combat strength
			4, // lose 1 heart
			5, // lose 1 gold coin
			// Night [3]
			
			
			
			
			
			
			
		};
		world.announce.suspense_level = 1; 
		world.event<Rule_Of_Adventure>();
	}
};


















} // namespace Parity