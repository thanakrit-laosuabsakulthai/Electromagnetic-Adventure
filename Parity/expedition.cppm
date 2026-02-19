export module Parity.Expedition;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <unordered_map>
	#include <unordered_set>
	#include <set>
	#include <vector>
	#include <string>
	#include <format>
	#include "type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.Geography;
	import Parity.Biology;
	import Parity.Announcement;
	import Parity.Notation;
#endif

export namespace Parity {

export using PlayerLocation = std::unordered_map<PlayerIdentity, Landmark>;
export using PlayerLocator = std::unordered_map<Landmark, Humanity>;

export struct Municipality {
	PlayerLocation player_location;
	PlayerLocator player_locator;
	
	void teleport(PlayerIdentity target_player, Landmark landmark_of_destination) {
		Landmark landmark_of_beginning = player_location[target_player];
		
		// Update player_location
		player_location[target_player] = landmark_of_destination;
		// Update player_locator
		player_locator[landmark_of_beginning].erase(target_player);
		player_locator[landmark_of_destination].insert(target_player);
	}
	
	Landmark getLandmarkOf(PlayerIdentity player) const {
		return player_location.at(player);
	}
	
	Humanity getHumanityAt(Landmark landmark) const {
		return player_locator.at(landmark);
	}
	
	void addPlayer(PlayerIdentity player, Landmark landmark) {
		player_location[player] = landmark;
		player_locator[landmark].insert(player);
	}
};

export using MultiDirection = std::vector<Direction>;


export struct OmniDirection {
	MultiDirection multidirection;
	
	void add(Direction direction) {
		multidirection.push_back(direction);
	}
	
	void clear() {
		multidirection.clear();
	}
	
	bool has(Direction direction) const {
		return std::find(multidirection.begin(), multidirection.end(), direction) != multidirection.end();
	}
	
	MultiDirection vector() const {
		return multidirection;
	}
};

export struct Expedition
{
	Landmark landmark_of_beginning = Landmark::DiamondOfCattail;
	Landmark landmark_of_destination = Landmark::DiamondOfCattail;
	Direction chosen_direction;
	OmniDirection choice_of_direction;
	bool is_journey_optional = false;
	bool is_journey_declined = false;
	Municipality municipality;
};

export struct Dialect {
	std::string_view above = "w";
	std::string_view below = "s";
	std::string_view left = "a";
	std::string_view right = "d";
	std::string_view above_left = "wa";
	std::string_view above_right = "wd";
	std::string_view below_left = "sa";
	std::string_view below_right = "sd";
	std::string_view decline_journey = "x";
};

export inline constexpr Dialect Encylopedia{};

export inline std::string_view to_dialect(Direction direction) {
	using enum Direction;
	static const std::map<Direction, std::string_view> directionToDialect = {
		{Above, Encylopedia.above},
		{Below, Encylopedia.below},
		{Left, Encylopedia.left},
		{Right, Encylopedia.right},
		{AboveLeft, Encylopedia.above_left},
		{AboveRight, Encylopedia.above_right},
		{BelowLeft, Encylopedia.below_left},
		{BelowRight, Encylopedia.below_right}
	};
	
	return directionToDialect.at(direction);
}

export inline Direction from_dialect(const std::string& dialect) {
	using enum Direction;
	static const std::map<std::string_view, Direction> dialectToDirection = {
		{Encylopedia.above, Above},
		{Encylopedia.below, Below},
		{Encylopedia.left, Left},
		{Encylopedia.right, Right},
		{Encylopedia.above_left, AboveLeft},
		{Encylopedia.above_right, AboveRight},
		{Encylopedia.below_left, BelowLeft},
		{Encylopedia.below_right, BelowRight}
	};
	
	return dialectToDirection.at(dialect);
}

export enum class Multiplicity {
	One,
	Many
};

export inline std::string_view to_bracket_notation(Multiplicity multiplicity) {
	using enum Multiplicity;
	static const std::map<Multiplicity, std::string_view> multiplicityToBracketNotation = {
		{One, "⟅{}⟆"},
		{Many, "⟪{}⟫"}
	};
	
	return multiplicityToBracketNotation.at(multiplicity);
}

export inline std::string dialect_synthesis(MultiDirection multidirection) {
	std::string multidirection_word;
	for (const auto& direction : multidirection) {
		multidirection_word += std::string(to_dialect(direction));
		if (&direction != &multidirection.back()) {
			multidirection_word += " ";
		}
	}
	
	return multidirection_word;
}

export inline std::string braket_notation_synthesis(MultiDirection multidirection) {
	std::string multidirection_word = " " + dialect_synthesis(multidirection) + " ";
	std::string_view bracket_notation = to_bracket_notation(Multiplicity::One);
	return std::vformat(bracket_notation, std::make_format_args(multidirection_word));
}

export inline std::string bag_notation_synthesis(std::string content_inside_bag) {
	content_inside_bag = " " + content_inside_bag + " ";
	
	std::string_view bag_notation = to_bracket_notation(Multiplicity::One);
	return std::vformat(bag_notation, std::make_format_args(content_inside_bag));
}

} // namespace Parity







