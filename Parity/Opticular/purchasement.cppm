export module Parity.Purchasement;

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
	
	import Parity.Optoelectronic;
	import Parity.OpticalNotation;
	
	import Parity.Marketplace;
#endif

export namespace Parity
{
//

void Purchasement_Of_Optics::execute(Overworld &world) {
	terra = &world;
	concentrate();
	// After concentration, the local purchasement is expected to be valid and can be applied to the world state
	world.purchasement = purchasement; // Apply the valid purchasement to the world state
}

void Purchasement_Of_Optics::concentrate() {
	Overworld &world = *terra;
	
	std::string player_input;
	fill_valid_numeral(); // valid ordinal for marketplace items
	
	do {
		query();
		purchasement.clear(); // Clear previous purchasement for new input
		player_input = world.announce.listen();
		
		if (!validate_dialect(player_input)) {
			clause_invalid();
			continue;
		}
		
		if (player_input == world.encyclopedia.decline_shop) {
			clause_decline_shop();
			break;
		}
		
		// now we know player input is a space-separated list of numbers
		apply_dialect(player_input); // input is now live on transcribed_numerical_dialect
		
		if (!validate_numerical_dialect()) {
			clause_invalid();
			continue;
		}
		
		// now we know all numbers in the dialect are valid
		apply_numerical_dialect(); // items are now live in purchasement
		// debug
		/* world.announce.subtitle(std::format("Player input: '{}'", player_input));
		world.announce.subtitle(""); */
		
		
		if (!validate_choice()) {
			clause_invalid();
			continue;
		}
		
		/* world.announce.subtitle("Player's choice validated");
		world.announce.subtitle(""); */
		
		// If we reach this point, the player's choice is valid and we can proceed with the purchase
		break;
	}
	while (true);
	
	end_concentration();
}

void Purchasement_Of_Optics::end_concentration() {
	Overworld &world = *terra;
	world.announce.redact(); // Remove the query about purchasing from the announcement feed
}

void Purchasement_Of_Optics::clause_invalid() {
	Overworld &world = *terra;
	world.announce.reject(); // Reject the player input
}


void Purchasement_Of_Optics::clause_decline_shop() {
	purchasement.clear();
}

void Purchasement_Of_Optics::apply_dialect(std::string &player_input) {
	Overworld &world = *terra;
	
	// Assume the player input is a space-separated list of numbers
	transcribed_numerical_dialect = transcribe_numerical_dialect(player_input);
}

void Purchasement_Of_Optics::apply_numerical_dialect() {
	Overworld &world = *terra;
	
	// Add the corresponding items to the purchasement based on the transcribed numerical dialect
	for(int number : transcribed_numerical_dialect) {
		Optics item = getOpticsFromNumber(number);
		purchasement.insert(item);
	}
}

bool Purchasement_Of_Optics::validate_dialect(std::string &player_input) {
	Overworld &world = *terra;
	
	if (player_input == world.encyclopedia.decline_shop) {
		return true; // It is a valid choice to decline the shop
	}
	
	// Use regular expression to validate that the input is a space-separated list of numbers
	std::regex valid_input_pattern(R"(^\d+( \d+)*$)");
	return std::regex_match(player_input, valid_input_pattern);
}

bool Purchasement_Of_Optics::validate_numerical_dialect() {
	Overworld &world = *terra;
	// Check if all chosen numbers correspond to valid items
	for (int number : transcribed_numerical_dialect) {
		if (valid_numeral.find(number) == valid_numeral.end()) {
			return false; // Found an invalid number
		}
	}
	
	return true; // All numbers are valid
}

bool Purchasement_Of_Optics::validate_choice() {
	// Check inventory capacity and gold coin affordability here
	
	Overworld &world = *terra;
	
	PlayerIdentity active_player = world.active_player;
	PlayerPosession &possession = world.playerbase[active_player];
	
	int inventory_capacity = possession.inventory_capacity;
	int current_inventory_size = static_cast<int>(possession.inventory.size());
	int purchasement_size = static_cast<int>(purchasement.size());
	
	if (current_inventory_size + purchasement_size > inventory_capacity) {
		return false; // Not enough inventory capacity
	}
	
	int total_cost = 0;
	for (const auto& item : purchasement) {
		total_cost += world.marketplace.at(item);
	}
	
	if (possession.gold_coin < total_cost) {
		return false; // Not enough gold coins
	}
	
	return true; // All checks passed, the choice is valid
}


void Purchasement_Of_Optics::query() {
	Overworld &world = *terra;
	
	std::string query_dialect = "";
	for (int i = 0; i < world.marketplace.size(); ++i) {
		query_dialect += std::to_string(i + 1);
		if (i < world.marketplace.size() - 1) {
			query_dialect += " ";
		}
	}
	
	query_dialect += " " + std::string(world.encyclopedia.decline_shop);
	std::string content_of_query = archangel_notation_synthesis(query_dialect);
	
	world.announce.ask(content_of_query);
}

void Purchasement_Of_Optics::fill_valid_numeral() {
		Overworld &world = *terra;
		int marketplace_size = static_cast<int>(world.marketplace.size());
		for (int i = 1; i <= marketplace_size; ++i) {
			valid_numeral.insert(i);
		}
}

Optics Purchasement_Of_Optics::getOpticsFromNumber(int number) {
	Overworld &world = *terra;
	auto it = world.marketplace.begin();
	std::advance(it, number - 1); // Advance the iterator to the (number - 1)-th position
	
	return it->first; // Return the Optics corresponding to the chosen number
}

} // namespace Parity