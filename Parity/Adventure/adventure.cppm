export module Parity.Adventure;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.Biology;
	import Parity.Geography;
	
#endif

export namespace Parity
{
//


// +++------>>> adventurer.cppm <<<------+++

export struct Welcome_Adventurer : Rule {
	int amount_of_adventurer;
	
	Welcome_Adventurer(int amount = 0) : amount_of_adventurer(amount) {}
	void execute(Overworld &world) override;
};

export template <typename Element_Of_Set>
	inline Element_Of_Set getNextElement(const std::set<Element_Of_Set>& target_set, Element_Of_Set current_element);

// string repetition for emdash because emdash is a multicharacter string in UTF-8
export inline std::string repetition(const std::string& target_string, int amount_of_repetition);
export inline std::string get_ornament_notation(int amount_of_emdash);

export struct Media_Of_Adventurer : Rule {
	void execute(Overworld &world) override;
};
export struct Media_Of_Adventurer_Separator : Rule {
	void execute(Overworld &world) override;
};
export struct First_Adventurer_Turn : Rule {
	void execute(Overworld &world) override;
};
export struct Next_Adventurer_Turn : Rule {
	void execute(Overworld &world) override;
};


// +++------>>> forgather.cppm <<<------+++

export struct Forgather_of_Adventurer : Rule {
	
	Overworld *terra;
	int player_choice = 0;
	
	void execute(Overworld &world) override;
	
	void query();
	bool validate_choice(int choice);
	bool validate_dialect(std::string &player_input);
	void get_player_choice();
};

// +--->>> traverser.cppm <<<---+++

export struct Corruption_Of_Landmark : Rule {
	void execute(Overworld &world) override;
};

export struct Forecast_Of_Combat : Rule {
	void execute(Overworld &world) override;
};

export struct Rule_Of_Adventure : Rule {
	void execute(Overworld &world) override;
};


} // namespace Parity