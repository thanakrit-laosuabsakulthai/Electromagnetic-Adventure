export module Parity;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include "overworld.cppm"
	#include "announcement.cppm"

	#include "Fortuneboard/diceroll.cppm"
	#include "Fortuneboard/fortuneboard.cppm"
	#include "Fortuneboard/luckyboard.cppm"
	#include "Fortuneboard/eventboard.cppm"
	#include "Fortuneboard/unluckyboard.cppm"
	#include "Fortuneboard/demonboard.cppm"

	#include "Divinity/physiology.cppm"
	#include "Divinity/necrology.cppm"
	#include "Divinity/biology.cppm"
	#include "Divinity/adventurer.cppm"
	#include "Divinity/forgather.cppm"
	#include "Divinity/necromancy.cppm"

	#include "Cartography/geography.cppm"
	#include "Cartography/notation.cppm"
	#include "Cartography/expedition.cppm"
	#include "Cartography/embark.cppm"
	#include "Cartography/encyclopedia.cppm"
	#include "Cartography/journey.cppm"
	#include "Cartography/accoutrement.cppm"
	#include "Cartography/passagedecision.cppm"
	
	#include "Opticular/optoelectronic.cppm"
	#include "Opticular/opticalnotation.cppm"
	#include "Opticular/marketplace.cppm"
	#include "Opticular/marketmedia.cppm"
	#include "Opticular/purchasement.cppm"
	
	#include "Chromaticity/chromaticity.cppm"
	#include "Chromaticity/coloreffect.cppm"
	
	#include "Showcase/subdivision.cppm"
	#include "Showcase/amusement.cppm"
	
	#include "Warfare/warfare.cppm"
	#include "Warfare/battlefield.cppm"
	#include "Warfare/armament.cppm"
	#include "Warfare/combat.cppm"
	#include "Warfare/simulation.cppm"
	
	
#else
	export import Parity.World;
	export import Parity.Announcement;
	
	export import Parity.DieRoll;
	export import Parity.FortuneBoard;
	export import Parity.LuckyBoard;
	export import Parity.EventBoard;
	export import Parity.UnluckyBoard;
	export import Parity.DemonBoard;
	
	export import Parity.Physiology;
	export import Parity.Necrology;
	export import Parity.Biology;
	export import Parity.Adventurer;
	export import Parity.Forgather;
	export import Parity.Necromancy;
	
	export import Parity.Geography;
	export import Parity.Notation;
	export import Parity.Expedition;
	export import Parity.Embark;
	export import Parity.Encyclopedia;
	export import Parity.Journey;
	export import Parity.Accoutrement;
	export import Parity.PassageDecision;
	
	export import Parity.Optoelectronic;
	export import Parity.OpticalNotation;
	export import Parity.Marketplace;
	export import Parity.MarketMedia;
	export import Parity.Purchasement;
	
	export import Parity.Chromaticity;
	export import Parity.ColorEffect;
	
	export import Parity.Subdivision;
	// export import Parity.Amusement;
	
	export import Parity.Warfare;
	export import Parity.Battlefield;
	// export import Parity.Armament;
	// export import Parity.Combat;
	export import Parity.Simulation;
#endif
