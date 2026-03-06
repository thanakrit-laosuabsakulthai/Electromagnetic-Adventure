export module Parity.Peril;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include <print>
	#include <iostream>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.Geography;
	import Parity.Notation;
	import Parity.Expedition;
	
	import Parity.Journey;
	import Parity.Warfare;
	import Parity.ScoutFly;
#endif

export namespace Parity {
//

void Knockback::execute(Overworld &world) {
	// same as Arrival, but without the color effect
	world.announce.linger(std::format("{} is pushed back to {}", 
		world.getActivePlayerName(),
		bold_cyan(world.appearanzonality(world.expedition.landmark_of_destination))
	));
	
	world.expedition.municipality.teleport(world.active_player, world.expedition.landmark_of_destination);
}

void Knockback_Adventurer::execute(Overworld &world) {
	/* 
	If there are Left, BelowLeft, or Below directions available,
		always chose in the order of Left, BelowLeft, and Below. 
	Otherwise, pick the first one in OmniDirection.
	*/
	world.expedition.landmark_of_beginning = world.getLandmarkOfActivePlayer();
	world.event<Every_Choice_Of_Passage>(); // Populate the choice_of_direction with all paths
	world.event<Entropy_Of_Adventurer>(); // Pick a direction based on the entropy of the adventurer
	world.event<Travel>(); // Set the landmark_of_destination
	world.event<Knockback>(); // Teleport the adventurer to the landmark_of_destination
	world.event<Potential_Of_Warfare_At_Active_Player>(); // Check for combat after knockback
	// This will not activate the color effect because the adventurer is knocked back, not moving by choice.
}

void Perpetrate::execute(Overworld &world) {
	// set landmark of beginning as the current location of active demon
	world.expedition.landmark_of_beginning = world.getLandmarkOfActiveDemon();
	
	// print media only on the first action of the conquest
	if (world.expedition.amount_of_conquest == world.expedition.amount_of_conquest_remaining) {
		world.event<Media_Of_Perpetrate>(); // In accountrement.cppm
	}
	
}

void Repulse::execute(Overworld &world) {
	// same as Knockback, but with different announcement
	world.announce.linger(std::format("The {} retreated to {}", 
		std::string(to_string(world.getActiveDemonForm())),
		bold_cyan(world.appearanzonality(world.expedition.landmark_of_destination
	))));
	world.expedition.antidivinity.teleport(world.active_demon_seriality, world.expedition.landmark_of_destination);
}

void Repulse_Demon::execute(Overworld &world) {
	// set landmark of beginning as the current location of active demon
	world.expedition.landmark_of_beginning = world.getLandmarkOfActiveDemon();
	
	world.event<Every_Choice_Of_Passage>(); // Populate the choice_of_direction with all paths
	world.event<Entropy_Of_Repulsion>(); // Pick a direction based on the entropy of the repulsion
	world.event<Travel>(); // Set the landmark_of_destination
	world.event<Repulse>(); // Teleport the demon to the landmark_of_destination and announce the retreat
}

/* 
- **» Action 3:** The Magnetic Mage Demon moves 3 spaces towards a player.
- Moving from ⟨Purple Diamond Space⟩ to…
	1. ｢Red Space｣ ← left, then…
	2. ｢Red Space｣ ← left, then…
	3. ｢Red-Purple Gradient Space｣ ← left
- **« Result 3:** The Magnetic Mage Demon moved to ==｢Red-Purple Gradient Space｣ ← left ← left ← left==
*/

void Step_Of_Conquest::execute(Overworld &world) {
	AntiDivinity &antidivinity = world.expedition.antidivinity;
	
	antidivinity.teleport(world.active_demon_seriality, world.expedition.landmark_of_destination);
	world.expedition.amount_of_conquest_remaining -= 1;
	
	std::string then_of_synthesis = "";
	if (world.expedition.amount_of_conquest_remaining >= 1) {
		then_of_synthesis = ", then…";
	}
	
	world.announce.analog(std::format("{} {}{}",
		world.appearanzonality(world.getLandmarkOfActiveDemon()),
		world.pathochronality(world.expedition.chosen_direction),
		then_of_synthesis
	));
}

void Forfence_Of_Cattail::execute(Overworld &world) {
	
	Landmark landmark_of_destination = world.expedition.landmark_of_destination;
	
	world.announce.analog(strikethrough(std::format("{} {}",
		world.appearanzonality(landmark_of_destination),
		world.pathochronality(world.expedition.chosen_direction)
	)));
	
	world.announce.linger(std::format("The {} forfended the Safe Zone from all demons and their corruptions...",
		to_string(Landmark::DiamondOfCattail)
	));
	
}

void Apply_Conquest_Of_Demon_Result::execute(Overworld &world) {
	Landmark landmark_of_destination = world.expedition.landmark_of_destination;
	Municipality &municipality = world.expedition.municipality;
	
	// Check if the destination is within the Safe Zone
	if (is_safe_zone(world.atlas[landmark_of_destination].zone)) {
		world.event<Forfence_Of_Cattail>();
		
		// If the demon has moved at least 1 space before being stopped,
		// announce the success of conquest
		if (world.expedition.amount_of_conquest_remaining < world.expedition.amount_of_conquest) {
			world.event<Media_Of_Conquest_Success>();
		} else {
			world.event<Media_Of_Conquest_Failure>();
		}
		
		world.expedition.amount_of_conquest_remaining = 0; // Stop the conquest immediately
		return; // Do not move the demon
	}
	
	// Check if the demon will move to a space with a player on it
	Humanity humantity_at_destination = municipality.getHumanityAt(landmark_of_destination);
	if (!humantity_at_destination.empty()) {
		world.expedition.amount_of_conquest_remaining = 1; // Stop the conquest immediately after moving to that space
		world.event<Step_Of_Conquest>(); // Move the demon to that space
		world.event<Media_Of_Conquest_Success>(); // Announce the success of conquest
		world.event<Potential_Of_Warfare_At_Active_Demon>(); // Check for combat
		return; // Do not move the demon further
	}
	
	// The destination is clear, move the demon there
	world.event<Step_Of_Conquest>();
	if (world.expedition.amount_of_conquest_remaining >= 2) {
		world.event<Conquest_Of_Demon>(); // Continue the conquest if there are more spaces to move
	} else { // If the remaining conquest is 1, the demon will move to the destination and then stop, so announce the success of conquest
		world.event<Media_Of_Conquest_Success>();
	}
	
}


/* 
- **» Action 2:** The Electric Minion moves 1 spaces towards a player. Demons can moves against arrow paths. Demons cannot enter spaces within the Safe Zone.
- Moving from ⟦Red Square Space⟧ to…
	1. ~~｢Orange Space ¦ Safe Zone｣ ←×— left~~
- The Diamond of Cattail forfended the Safe Zone from all demons and their corruptions…
- **« Result 3:** The Electric Minion stayed on the ==⟦Red Square Space⟧==
*/

void Move_Demon_Towards_Player::execute(Overworld &world) {
	world.expedition.amount_of_conquest = amount_of_conquest;
	world.expedition.amount_of_conquest_remaining = amount_of_conquest;
	
	world.event<Media_Of_Conquest>(); // Announce the action of conquest
	world.event<Conquest_Of_Demon>();
}

void Conquest_Of_Demon::execute(Overworld &world) {
	
	world.event<Perpetrate>(); // Set the landmark of beginning and announce the action
	world.event<Every_Choice_Of_Passage>(); // Populate the choice_of_direction with all paths
	//world.event<Entropy_Of_Corruption>(); // Pick a direction based on the entropy of the corruption
	world.event<Maximum_Entropy_Of_Corruption>(); // random walk for demon movement
	
	world.event<Travel>(); // Set the landmark of destination
	world.event<Apply_Conquest_Of_Demon_Result>(); // Move the demon and announce the result based on the landmark of destination
}



} // namespace Parity
