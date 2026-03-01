export module Parity.Simulation;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include "../type-definition.cppm"
#else
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.Biology;
	import Parity.Necrology;
	import Parity.Battlefield;
	import Parity.Optoelectronic;
	import Parity.Expedition;
	
	import Parity.Warfare;
	import Parity.Physiology;
	import Parity.Necromancy;
	import Parity.Marketplace;
#endif

export namespace Parity
{

void Potential_Of_Warfare::execute(Overworld &world) {
	Municipality &municipality = world.expedition.municipality;
	AntiDivinity &antidivinity = world.expedition.antidivinity;
	
	// Check for players and demons in the target landmark
	Humanity humanity_at_landmark = municipality.getHumanityAt(target_landmark);
	Demonity demonity_at_landmark = antidivinity.getDemonityAt(target_landmark);
	
	bool player_present = humanity_at_landmark.size() > 0;
	bool demon_present = demonity_at_landmark.size() > 0;
	
	if (! (player_present && demon_present) ) {
		return; // No combat potential if either player or demon is absent
	}
	
	// Otherwise, combat will occur
	// Select the first player as active player
	world.event<Execute_As>(*humanity_at_landmark.begin());
	world.event<Potential_Of_Combat_Consumption>();
	world.event<Execute_As_Demon>(*demonity_at_landmark.begin());
	world.event<Commencement_Of_Warfare>();
	world.event<Relinquish_Execution>();
}


} // namespace Parity






/* 
- **« Result 1:** SapphireSummoner chose ==⟦Red Square Space⟧ → right==
- **» Action 2:** If the space a player moves to contains a demon, that player must fight the demon. If they lose, they are pushed back to their previous space.
- Activating combat effects…
	- SapphireSummoner: ==Advantage==, ==Collimation==
	- Electric Minion: ==Advantage==, ==Weakness==
- Preparing Batte…
	- SapphireSummoner ♢ ==×1== Attack Power
	- Electric Minion ♢ ==×1== Attack Power
- The Player and the Demon each roll 1 die…
	- SapphireSummoner ⚅ ==×6== Combat Strength 
	- Electric Minion ⚅ ==×6== Combat Strength
- Multiply the die roll result by each party's Power to get their Attack Value…
	- SapphireSummoner ※ ==×6== Attack Value 
	- Electric Minion ※ ==×6== Attack Value 
- The battle resulted in a ==Draw==. Rolling for combat again…
- The Player and the Demon each roll 1 die…
	- SapphireSummoner ⚃ ==×4== Combat Strength 
	- Electric Minion  ⚄ ==×5== Combat Strength
- Multiply the die roll result by each party's Power to get their Attack Value…
	- SapphireSummoner † ==×4== Attack Value 
	- Electric Minion ✤ ==×5== Attack Value 
- **« Result 2:** SapphireSummoner ==Lost== the combat. They lose 1 Heart and are pushed back to their previous space.
- *Inflicted damage of 1 vitality heart to SapphireSummoner*
- SapphireSummoner is pushed back to ==｢Orange Space｣ ← left==
- **» Action 3:** When a player is pushed back onto a space, the effect of that space activates according to its color. 
- **« Result 3:** Trigger the ==Event Board== once
*/