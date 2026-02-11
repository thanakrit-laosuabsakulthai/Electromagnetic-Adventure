export module Parity;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include "diceroll.cppm"
	#include "biology.cppm"
	#include "overworld.cppm"
	#include "fortuneboard.cppm"
#else
	export import Parity.World;
	export import Parity.FortuneBoard;
	export import Parity.Biology;
	export import Parity.DieRoll;
#endif
