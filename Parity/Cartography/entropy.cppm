export module Parity.Entropy;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	
	import Parity.Geography;
	import Parity.Notation;
	
	import Parity.Expedition;
	import Parity.Journey;
	import Parity.ScoutFly;
#endif

export namespace Parity {
//

void Roll_For_Entropy::execute(Overworld &world) {
	world.die_roll_for_entropy = world.fatesAndCertainty();
}

void Entropy_Of_Adventurer::execute(Overworld &world) {
	/* 
	If there are Left, BelowLeft, or Below directions available,
		always chose in the order of Left, BelowLeft, and Below. 
	Otherwise, pick randomly from the available directions.
	*/
	
	OmniDirection available_directions = world.expedition.choice_of_direction;
	MultiDirection multidirection = available_directions.vector();
	
	OmniDirection preferred_directions;
	preferred_directions.add(Direction::Left);
	preferred_directions.add(Direction::BelowLeft);
	preferred_directions.add(Direction::Below);
	
 	for (Direction preferred_direction : preferred_directions.vector()) {
		if (available_directions.has(preferred_direction)) {
			world.expedition.chosen_direction = preferred_direction;
			return;
		}
	}
	
	// If no preferred direction is available, pick the first one in OmniDirection
	if (!multidirection.empty()) {
		world.expedition.chosen_direction = multidirection[0];
	}
}

void Entropy_Of_Corruption::execute(Overworld &world) {
	 
	// If landmark of beginning is The Cataclysm, pick randomly using die roll for entropy.
	

	if (world.expedition.landmark_of_beginning == Landmark::TheCataclysm) {
		world.event<Roll_For_Entropy>();
		world.event<Apply_Fate_Of_Corruption>();
		return;
	}
	

	/* 
	If there are Left, BelowLeft, or Below directions available,
		always chose in the order of Left, BelowLeft, and Below. 
	Otherwise, pick randomly from the available directions.
	*/

	OmniDirection available_directions = world.expedition.choice_of_direction;
	MultiDirection multidirection = available_directions.vector();
	
	OmniDirection preferred_directions;
	preferred_directions.add(Direction::Left);
	preferred_directions.add(Direction::BelowLeft);
	preferred_directions.add(Direction::Below);
	
 	for (Direction preferred_direction : preferred_directions.vector()) {
		if (available_directions.has(preferred_direction)) {
			world.expedition.chosen_direction = preferred_direction;
			return;
		}
	}
	
	// If no preferred direction is available, pick the first one in OmniDirection
	if (!multidirection.empty()) {
		world.expedition.chosen_direction = multidirection[0];
	}
	
	
	
}

void Apply_Fate_Of_Corruption::execute(Overworld &world) {
	DieRoll roll = world.die_roll_for_entropy;
	int roll_value = static_cast<int>(roll);
	
	MultiDirection available_multidirection = world.expedition.choice_of_direction.vector();
	int available_count = static_cast<int>(available_multidirection.size());
	
	// debug
	
	/* for (Direction dir : available_multidirection) {
		std::print("Available direction: {}\n", to_string(dir));
	}
	 */

	if (available_count == 0) {
		return; // No available directions, do nothing
	}
	
	int chosen_index = (roll_value - 1) % available_count; // Map roll to index
	world.expedition.chosen_direction = available_multidirection[chosen_index];
}

void Entropy_Of_Repulsion::execute(Overworld &world) {
	/* 
	If there are Right, AboveRight, or Above directions available,
		always chose in the order of Right, AboveRight, and Above.
	*/
	OmniDirection available_directions = world.expedition.choice_of_direction;
	MultiDirection multidirection = available_directions.vector();
	
	OmniDirection preferred_directions;
	preferred_directions.add(Direction::Right);
	preferred_directions.add(Direction::AboveRight);
	preferred_directions.add(Direction::Above);
	
 	for (Direction preferred_direction : preferred_directions.vector()) {
		if (available_directions.has(preferred_direction)) {
			world.expedition.chosen_direction = preferred_direction;
			return;
		}
	}
	
	// If no preferred direction is available, pick the first one in OmniDirection
	if (!multidirection.empty()) {
		world.expedition.chosen_direction = multidirection[0];
	}
}


















} // namespace Parity


























