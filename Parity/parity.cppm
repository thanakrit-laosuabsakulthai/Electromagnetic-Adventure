export module Parity;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include "diceroll.cppm"
	#include "biology.cppm"
	#include "overworld.cppm"
	#include "fortuneboard.cppm"
	#include "geography.cppm"
	#include "notation.cppm"
	#include "announcement.cppm"
	#include "expedition.cppm"
	#include "embark.cppm"
	#include "physiology.cppm"
#else
	export import Parity.World;
	export import Parity.FortuneBoard;
	export import Parity.Biology;
	export import Parity.Physiology;
	export import Parity.DieRoll;
	export import Parity.Geography;
	export import Parity.Notation;
	export import Parity.Announcement;
	export import Parity.Expedition;
	export import Parity.Embark;
#endif
