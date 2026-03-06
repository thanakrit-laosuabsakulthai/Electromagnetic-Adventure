export module Parity.Consumption;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <map>
	#include <string>
	#include <format>
	#include <set>
	#include <regex>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.OpticalNotation;
	
	import Parity.Encyclopedia;
	import Parity.Marketplace;
#endif

export namespace Parity
{
//
/* struct Consumption_Of_Optics : Rule {
	Overworld *terra = nullptr;
	
	Inventory consumption;
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
	
	void clause_decline_consumption();
	void clause_invalid();
	
	void end_concentration();
	void concentrate();
}; */


void Consumption_Of_Optics::execute(Overworld &world) {
	terra = &world;
	concentrate();
	
	// After concentration, the local consumption is expected to be valid and can be applied to the world state
	world.consumption = consumption; // Apply the valid consumption to the world state
}

void Consumption_Of_Optics::concentrate() {
	Overworld &world = *terra;
	
	std::string player_input;
	fill_valid_numeral(); 
	
	do {
		query();
		consumption.clear(); // Clear previous consumption for new input
		player_input = world.announce.listen();
		
		if (!validate_dialect(player_input)) {
			clause_invalid();
			continue;
		}
		
		if (player_input == world.encyclopedia.decline_consumption) {
			clause_decline_consumption();
			break;
		}
		
		// now we know player input is a space-separated list of numbers
		apply_dialect(player_input); // input is now live on transcribed_numerical_dialect
		
		if (!validate_numerical_dialect()) {
			clause_invalid();
			continue;
		}
		
		// now we know all numbers in the dialect are valid
		apply_numerical_dialect(); // items are now live in consumption
		
		// If we reach this point, the player's choice is valid and we can proceed with the consumption
		break;
		
	} while (true);
	
	end_concentration();
}


void Consumption_Of_Optics::end_concentration() {
	Overworld &world = *terra;
	world.announce.redact(); // Remove the query about purchasing from the announcement feed
}

void Consumption_Of_Optics::clause_invalid() {
	Overworld &world = *terra;
	world.announce.reject(); // Reject the player input
}

void Consumption_Of_Optics::clause_decline_consumption() {
	consumption.clear();
}

bool Consumption_Of_Optics::validate_dialect(std::string &player_input) {
	Overworld &world = *terra;
	
	if (player_input == world.encyclopedia.decline_consumption) {
		return true; // It is a valid choice to decline consumption
	}
	
	// Use regular expression to validate that the input is a space-separated list of numbers
	std::regex valid_input_pattern(R"(^\d+( \d+)*$)");
	return std::regex_match(player_input, valid_input_pattern);
}

void Consumption_Of_Optics::apply_dialect(std::string &player_input) {
	Overworld &world = *terra;
	
	// Assume the player input is a space-separated list of numbers
	transcribed_numerical_dialect = transcribe_numerical_dialect(player_input);
}

bool Consumption_Of_Optics::validate_numerical_dialect() {
	Overworld &world = *terra;
	// Check if all chosen numbers correspond to valid items
	for (int number : transcribed_numerical_dialect) {
		if (valid_numeral.find(number) == valid_numeral.end()) {
			return false; // Found an invalid number
		}
	}
	
	// Check if there is not any duplicate number in the transcribed numerical dialect
	std::set<int> unique_numbers(transcribed_numerical_dialect.begin(), transcribed_numerical_dialect.end());
	if (unique_numbers.size() != transcribed_numerical_dialect.size()) {
		return false; // Found duplicate numbers
	}
	
	return true; // All numbers are valid
}

void Consumption_Of_Optics::apply_numerical_dialect() {
	Overworld &world = *terra;
	
	// Add the corresponding items to the purchasement based on the transcribed numerical dialect
	for(int number : transcribed_numerical_dialect) {
		Optics item = getOpticsFromNumber(number);
		consumption.insert(item);
	}
}

void Consumption_Of_Optics::query() {
	Overworld &world = *terra;
	
	int amount_of_choice = static_cast<int>(world.potential_consumption.size());
	
	
	std::string query_dialect = "";
	for (int i = 1; i <= amount_of_choice; ++i) {
		query_dialect += std::to_string(i);
		
		if (i < amount_of_choice) {
			query_dialect += " ";
		}
	}
	
	query_dialect += " " + std::string(world.encyclopedia.decline_consumption);
	std::string content_of_query = archangel_notation_synthesis(query_dialect);
	
	world.announce.ask(content_of_query);
}

void Consumption_Of_Optics::fill_valid_numeral() {
		Overworld &world = *terra;
		int choice_size = static_cast<int>(world.potential_consumption.size());
		for (int i = 1; i <= choice_size; ++i) {
			valid_numeral.insert(i);
		}
}

Optics Consumption_Of_Optics::getOpticsFromNumber(int number) {
	Overworld &world = *terra;
	auto it = world.potential_consumption.begin();
	std::advance(it, number - 1); // Move the iterator to the (number-1)-th position
	return *it; // Return the Optics at that position
}

} // namespace Parity