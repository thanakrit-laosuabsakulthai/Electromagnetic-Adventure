export module Parity.Journey;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include <print>
	#include <iostream>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.Geography;
	import Parity.World;
	import Parity.Expedition;
	import Parity.Embark;
#endif

export namespace Parity {

export struct Move_One_Space : Rule {
	void execute(Overworld &world) override {
		world.expedition.is_journey_optional = false; // This move is not optional
		world.event<Media_Of_Journey>();
		world.event<Embark>();
		world.event<Choice_Of_Passage>();
		world.event<Decision_Of_Passage>();
		world.event<Travel>();
		world.event<Arrival>();
	}
};

// Forward declaration

struct Apply_Optional_Journey;

export struct Move_One_Space_Optional : Rule {
	int amount_of_optional_move;
	Move_One_Space_Optional(int amount = 1) : amount_of_optional_move(amount) {}
	
	void execute(Overworld &world) override {
		
		if (amount_of_optional_move > 0) {
			world.expedition.is_journey_optional = true;
			world.event<Media_Of_Journey>();
			world.event<Embark>();
			world.event<Choice_Of_Passage>();
			world.event<Decision_Of_Passage>();
			world.event<Apply_Optional_Journey>(amount_of_optional_move);
		}
	}
};

export struct Apply_Optional_Journey : Rule {
	int amount_of_optional_move;
	Apply_Optional_Journey(int amount) : amount_of_optional_move(amount) {}
	
	void execute(Overworld &world) override {
		if (world.expedition.is_journey_declined) {
			world.event<Decline_Journey>();
		} else {
			world.event<Travel>();
			world.event<Arrival>();
			// If there are more optional moves left, ask the player if they want to move again
			if (amount_of_optional_move > 1) {
				world.event<Move_One_Space_Optional>(amount_of_optional_move - 1);
			}
		}
	}
};

} // namespace Parity