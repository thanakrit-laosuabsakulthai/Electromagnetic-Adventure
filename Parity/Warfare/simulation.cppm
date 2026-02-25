export module Parity.Simulation;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include "../type-definition.cppm"
#else
	import std;
	import Parity.DieRoll;
	import Parity.Biology;
	import Parity.Necrology;
#endif















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