export module Parity.Marketplace;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <set>
	#include <map>
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.Optoelectronic;
#endif

export namespace Parity
{
//

// +++------>>> marketplace.cppm <<<------+++

export struct Open_Shop : Rule {
	void execute(Overworld &world) override;
};
export struct Apply_Purchasement_Of_Optics : Rule {
	void execute(Overworld &world) override;
};
export struct Apply_Purchasement_Result : Rule {
	void execute(Overworld &world) override;
};
export struct Decline_Shop : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> marketmedia.cppm <<<------+++

export struct Media_Of_Marketplace : Rule {
	Overworld *terra = nullptr;
	void execute(Overworld &world) override;
	void display_market();
	void display_player_possesion_hint();
};

export struct Review_Of_Purchase : Rule {
	Overworld *terra = nullptr;
	void execute(Overworld &world) override;
	void display_purchasement();
	void display_inventory();
};

// +++------>>> purchasement.cppm <<<------+++

export struct Purchasement_Of_Optics : Rule {
	Overworld *terra = nullptr;
	
	Inventory purchasement;
	std::multiset<int> transcribed_numerical_dialect; 
	std::set<int> valid_numeral;
	void execute(Overworld &world) override;
	void fill_valid_numeral();
	Optics getOpticsFromNumber(int number);
	
	void query();
	
	bool validate_dialect(std::string &player_input);
	void apply_dialect(std::string &player_input);
	
	bool validate_numerical_dialect();
	void apply_numerical_dialect();
	
	bool validate_choice();
	
	void clause_decline_shop();
	void clause_invalid();
	
	void end_concentration();
	void concentrate();
};

} // namespace Parity

/* 
- **» Action 3:** AmethystApprentice may purchase items from the Shop Board.
	- [x] **Radio Waves (2 Gold):** Use this item to call for support. Trigger the Lucky Board once.
	- [x] **Microwaves (2 Gold):** Use this item *after* winning a combat to cook the demon's meat. Heal 1 Heart upon consumption.
	- [x] **Infrared Waves (1 Gold):** Use this item to detect a demon's heat signature weakness. Reduce the demon's Power by 1 for that combat.
	- [ ] **Light Waves (3 Gold):** Use this item when landing on a Gradient space to choose the color effect instead of rolling the die for that turn's resolution.
		- Pink-Orange-Yellow Gradient: Choose Pink, Orange, or Yellow effect.
		- Red-Purple Gradient: Choose Red or Purple effect.
		- White-Gray Gradient: Choose *any* non-gradient color effect. The space retains this chosen color effect until changed again by this item.
	- [ ] **Ultraviolet Waves (5 Gold):** Use this item when entering a space with a demon. The demon retreats 1 space, and combat does not occur. This item cannot be used in the Demon Zone.
	- [ ] **X-Rays (5 Gold):** Use this item to scan a demon's internal structure. The player gains ==Advantage== status for that combat. When a player has this status, they roll 2 dice and use the higher result multiplied by their Power for their Attack Value.
	- [ ] **Gamma Rays (10 Gold):** Use this item in combat. The player's Power increases by 10 for that combat, and their attack hits *all* demons in the space.
- AmethystApprentice has ==6 Gold Coins==. They have no items in inventory; they may purchase upto 4 items from the Shop.
• » Choice ⟪ 1 2 3 4 5 6 7 x ⟫ : 3 3 1 2
- **» Result 3:** AmethystApprentice chose to purchase…
	1. ==Infrared Waves (1 Gold) × 2:== Use this item to detect a demon's heat signature weakness. Reduce the demon's Power by 1 for that combat.
	2. ==Radio Waves (2 Gold):== Use this item to call for support. Trigger the Lucky Board once.
	3. ==Microwaves (2 Gold):== Use this item after winning a combat to cook the demon's meat. Heal 1 Heart upon consumption.
	- With the total cost of ==6 Gold==.
	- Inventory of AmethystApprentice now includes:
	1. ==Infrared Waves==
	2. ==Infrared Waves==
	3. ==Microwaves==
	4. ==Radio Waves==
	- AmethystApprentice now has ==0 Gold Coins==.
- *Gave 2 [Infrared Waves] to AmethystApprentice*
- *Gave 1 [Microwaves] to AmethystApprentice*
- *Gave 1 [Radio Waves] to AmethystApprentice*
- *Clear 6 [Gold Coin] from AmethystApprentice*
- **» Action 4:** AmethystApprentice ends their turn.
*/