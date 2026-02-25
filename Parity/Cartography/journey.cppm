export module Parity.Journey;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include <print>
	#include <iostream>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	
	import Parity.Geography;
	import Parity.Expedition;
#endif

export namespace Parity {
//
// +++------>>> accoutrement.cppm <<<------+++

export struct Query_Of_Passage : Rule {
	void execute(Overworld &world) override;
};
export struct Media_Of_Embark : Rule {
	void execute(Overworld &world) override;
};
export struct Media_Of_Passage : Rule {
	void execute(Overworld &world) override;
};
export struct Media_Of_Journey : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> embark.cppm <<<------+++

export struct Embark : Rule {
	void execute(Overworld &world) override;
};


export struct Choice_Of_Passage : Rule {
	void execute(Overworld &world) override;
};

export struct Travel : Rule {
	void execute(Overworld &world) override;
};
export struct Arrival : Rule {
	void execute(Overworld &world) override;
};

export struct Decline_Journey : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> passagedecision.cppm <<<------+++

export struct Listen_Passage_Dialect : Rule {
	void execute(Overworld &world) override;
};

export struct Resolve_Passage_Dialect : Rule {
	void execute(Overworld &world) override;
};

export struct Apply_Passage_Dialect : Rule {
	
	Overworld *terra = nullptr;
	void execute(Overworld &world) override;
	bool validate_choice(Direction chosen_direction);
	bool validate_dialect(const std::string& player_input);
};

export struct Decision_Of_Passage : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> journey.cppm <<<------+++

export struct Move_One_Space : Rule {
	void execute(Overworld &world) override;
};

export struct Move_One_Space_Optional : Rule {
	int amount_of_optional_move;
	Move_One_Space_Optional(int amount = 1) : amount_of_optional_move(amount) {}
	void execute(Overworld &world) override;
};

export struct Apply_Optional_Journey : Rule {
	int amount_of_optional_move;
	Apply_Optional_Journey(int amount) : amount_of_optional_move(amount) {}
	void execute(Overworld &world) override;
};


} // namespace Parity