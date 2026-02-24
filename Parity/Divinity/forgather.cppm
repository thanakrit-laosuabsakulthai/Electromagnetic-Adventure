export module Parity.Forgather;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	import Parity.Adventurer;
	import Parity.Encyclopedia;
#endif

// decision of how many adventurers are in the game

export namespace Parity
{

export struct Forgather_of_Adventurer : Rule {
	
	Overworld *terra = nullptr;
	int player_choice = 0;
	
	void execute(Overworld &world) override {
		terra = &world;
		
		world.announce.caption("Choose the number of adventurers in the game.");
		get_player_choice();
		
		world.announce.redact(); // Remove the caption after getting the player's choice
		world.player_count = player_choice;
		world.event<Welcome_Adventurer>();
	}
	
	void query();
	bool validate_choice(int choice);
	bool validate_dialect(std::string &player_input);
	void get_player_choice();
};

void Forgather_of_Adventurer::query() {
	Overworld &world = *terra;
	
	std::string query_dialect = "";
	for (int i = 1; i <= world.maximum_player_count; ++i) {
		query_dialect += std::to_string(i);
		
		if (i < world.maximum_player_count) {
			query_dialect += " ";
		}
	}
	
	std::string content_of_query = bag_notation_synthesis(query_dialect);
	world.announce.ask(content_of_query);
}

bool Forgather_of_Adventurer::validate_dialect(std::string &player_input) {
	Overworld &world = *terra;
	
	try {
		int choice = std::stoi(player_input);
		return validate_choice(choice);
	} catch (const std::exception&) {
		return false; // Input is not a valid integer
	}
}

bool Forgather_of_Adventurer::validate_choice(int choice) {
	Overworld &world = *terra;
	return choice >= 1 && choice <= world.maximum_player_count;
}

void Forgather_of_Adventurer::get_player_choice() {
	Overworld &world = *terra;
	
	std::string player_input;
	do {
		query();
		player_input = world.announce.listen();
		
		if (validate_dialect(player_input)) {
			world.announce.redact(); // Remove the query after a valid choice is made
			break; // Valid choice, exit the loop
		} else {
			world.announce.reject(); // Reject the query if the input is invalid
		}
		
	} while (true);
	
	player_choice = std::stoi(player_input);
}


} // namespace Parity