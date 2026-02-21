export module Parity;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include "overworld.cppm"
	#include "announcement.cppm"

	#include "Fortuneboard/diceroll.cppm"
	#include "Fortuneboard/fortuneboard.cppm"
	#include "Fortuneboard/luckyboard.cppm"
	#include "Fortuneboard/eventboard.cppm"
	#include "Fortuneboard/unluckyboard.cppm"

	#include "Divinity/physiology.cppm"
	#include "Divinity/necrology.cppm"
	#include "Divinity/biology.cppm"
	#include "Divinity/adventurer.cppm"

	#include "Cartography/geography.cppm"
	#include "Cartography/notation.cppm"
	#include "Cartography/expedition.cppm"
	#include "Cartography/embark.cppm"
	#include "Cartography/encyclopedia.cppm"
#else
	export import Parity.World;
	export import Parity.Announcement;
	
	export import Parity.DieRoll;
	export import Parity.FortuneBoard;
	export import Parity.LuckyBoard;
	export import Parity.EventBoard;
	export import Parity.UnluckyBoard;
	
	export import Parity.Physiology;
	export import Parity.Necrology;
	export import Parity.Biology;
	export import Parity.Adventurer;
	
	export import Parity.Geography;
	export import Parity.Notation;
	export import Parity.Expedition;
	export import Parity.Embark;
	export import Parity.Encyclopedia;
#endif
