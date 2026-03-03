export module Parity.Glazier;


#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include <set>
	#include <regex>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.Geography;
	import Parity.Notation;
	
	import Parity.Chromaticity;
#endif

export namespace Parity
{
//

void Glazier_Of_Chromaticity::execute(Overworld &world) {
	terra = &world;
	concentrate();
	
	world.chosen_prismarine = chosen_color; // Apply the valid chosen color to the world state
}

void Glazier_Of_Chromaticity::concentrate() {
	Overworld &world = *terra;
	
	std::string player_input;
	fill_valid_numeral(); // valid ordinal for marketplace items
	
	do {
		query();
		player_input = world.announce.listen();
		
		if (!validate_dialect(player_input)) {
			clause_invalid();
			continue;
		}
		
		// now we know player input is a number
		apply_dialect(player_input); // input is now live on transcribed_numerical_dialect
		
		if (!validate_numerical_dialect()) {
			clause_invalid();
			continue;
		}
		
		// now we know all numbers in the dialect are valid
		apply_numerical_dialect(); // items are now live in chosen_color
		
		// If we reach this point, the player's choice is valid and we can proceed 
		break;
	}
	while (true);
	
	end_concentration();
}

void Glazier_Of_Chromaticity::end_concentration() {
	Overworld &world = *terra;
	world.announce.redact(); // Remove the query about purchasing from the announcement feed
}

void Glazier_Of_Chromaticity::clause_invalid() {
	Overworld &world = *terra;
	world.announce.reject(); // Reject the player input
}

void Glazier_Of_Chromaticity::apply_dialect(std::string &player_input) {
	Overworld &world = *terra;
	
	// Assume the player input is a single number
	transcribed_numerical_dialect = std::stoi(player_input); // Convert the input string to an integer
}

void Glazier_Of_Chromaticity::apply_numerical_dialect() {
	Overworld &world = *terra;

	chosen_color = getColorFromNumber(transcribed_numerical_dialect);
}

bool Glazier_Of_Chromaticity::validate_dialect(std::string &player_input) {
	Overworld &world = *terra;
	
	// Use regular expression to validate that the input is just a single number
	std::regex valid_input_pattern(R"(^\d+$)");
	return std::regex_match(player_input, valid_input_pattern);
}

bool Glazier_Of_Chromaticity::validate_numerical_dialect() {
	Overworld &world = *terra;

	if (valid_numeral.find(transcribed_numerical_dialect) == valid_numeral.end()) {
		return false; // Found an invalid number
	}
	
	return true; // The number is valid
}


void Glazier_Of_Chromaticity::query() {
	Overworld &world = *terra;
	
	int size_of_potential = static_cast<int>(world.potential_prismarine.size());
	
	std::string query_dialect = "";
	for (int i = 0; i < size_of_potential; ++i) {
		query_dialect += std::to_string(i + 1);
		if (i < size_of_potential - 1) {
			query_dialect += " ";
		}
	}

	std::string content_of_query = bag_notation_synthesis(query_dialect);
	
	world.announce.ask(content_of_query);
}

void Glazier_Of_Chromaticity::fill_valid_numeral() {
		Overworld &world = *terra;
		int size_of_potential = static_cast<int>(world.potential_prismarine.size());
		for (int i = 1; i <= size_of_potential; ++i) {
			valid_numeral.insert(i);
		}
}

ApparentColor Glazier_Of_Chromaticity::getColorFromNumber(int number) {
	Overworld &world = *terra;
	auto it = world.potential_prismarine.begin();
	std::advance(it, number - 1); // Advance the iterator to the (number - 1)-th position
	
	return *it; // Return the ApparentColor at that position
}







} // namespace Parity












