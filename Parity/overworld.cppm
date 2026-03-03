export module Parity.World;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <deque>
	#include <memory>
	#include <print>
	#include <iostream>
	#include "type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.DieRoll;
	import Parity.Biology;
	import Parity.Necrology;
	import Parity.Geography;
	import Parity.Expedition;
	import Parity.Announcement;
	import Parity.Encyclopedia;
	import Parity.Optoelectronic;
	import Parity.Battlefield;
	import Parity.Celestial;
#endif


export namespace Parity {


export struct Rule { 
	virtual ~Rule() = default;
	virtual void execute(class Overworld &world) = 0;
};

export class Overworld
{
	public:
	
	// +++ announcement +++
	Announcement announce;
	// +++ geography +++
	Geography atlas = Atlas;
	
	// +++ expedition-embark +++
	Expedition expedition;
	Landmark getLandmarkOfActivePlayer();
	Dialect encyclopedia = Encyclopedia;
	std::string appearanzonality(Landmark target_landmark);
	std::string appearancity(Landmark target_landmark);
	std::string pathochronality(Pathway target_pathway);
	std::string pathochronality(Direction target_direction);
	DieRoll die_roll_for_entropy = DieRoll::One;
	
	// +++ fortuneboard +++
	DieRoll die_roll_for_fortune_board = DieRoll::One;
	int lucky_board_multiplier = 1;
	int useLuckyBoardMultiplier();
	
	// +++ oracle +++
	Certainty certainty = {};
	DieRoll fatesAndCertainty();
	
	// +++ chromaticity +++
	DieRoll die_roll_for_chromaticity = DieRoll::One;
	ApparentColor getColorUnderActivePlayer();
	
	// +++  biology-physiology +++
	Treasury playerbase;
	Humanity humanity;
	PlayerIdentity active_player;
	PlayerIdentity turn_of_adventurer;
	int player_count = 1;
	int maximum_player_count = 4;
	std::string_view getActivePlayerName();
	void firstAdventurer();
	void nextAdventurer();
	
	// +++ necrology +++
	DemonSeriality active_demon_seriality;
	DemonForm getActiveDemonForm();
	Landmark getLandmarkOfActiveDemon();
	
	// +++ warfare-battlefield +++
	Battlefield battlefield;
	
	// +++ opticular +++
	MarketValuation marketplace = Marketplace;
	Inventory purchasement;
	Inventory consumption;
	Inventory potential_consumption;
	
	// +++ prismarine +++
	ApparentColor chosen_prismarine;
	PolyChromaticity potential_prismarine;
	
	// +++ traverser +++
	int calendar_of_sunrise = 0;
	CelestialClause clause_of_adventure = CelestialClause::VoidOfForgather;
	
	/// +++ rule-event +++
	int amount_of_new_event = 0;
	
	void relocate_new_events_to_front() {
		if (amount_of_new_event > 0) {
			std::rotate(event_queue.begin(), event_queue.end() - amount_of_new_event, event_queue.end());
			amount_of_new_event = 0;
		}
	}
	
	std::deque<std::unique_ptr<Rule>> event_queue;
	void main_loop()
	{
		amount_of_new_event = 0; // Reset the counter at the start of the loop
		
		while (!event_queue.empty())
		{
			// Wait for enter and clear the enter line
			// std::cin.get();
			// std::cout << "\033[1A\033[2K"; // Move cursor up and clear the line
			
			std::unique_ptr<Rule> event = std::move(event_queue.front());
			event_queue.pop_front();
			event->execute(*this);
			
			relocate_new_events_to_front();
		}
	}
	
	template <typename Extent_of_Rule, typename... Argument_of_Rule>
	void event(Argument_of_Rule&&... custom_arguments) {
		event_queue.push_back(std::make_unique<Extent_of_Rule>(std::forward<Argument_of_Rule>(custom_arguments)...));
		amount_of_new_event++;
	}
};
} // namespace Parity

