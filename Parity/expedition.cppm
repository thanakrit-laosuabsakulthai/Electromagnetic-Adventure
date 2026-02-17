export module Parity.Expedition;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <unordered_map>
	#include <unordered_set>
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
	PlayerLocation municipality = {{PlayerIdentity::AmethystApprentice, Landmark::DiamondOfCattail}};
};

export inline std::string_view to_dialect(Direction direction) {
	using enum Direction;
	static const std::map<Direction, std::string_view> directionToDialect = {
		{Above, "w"},
		{Below, "s"},
		{Left, "a"},
		{Right, "d"},
		{AboveLeft, "wa"},
		{AboveRight, "wd"},
		{BelowLeft, "sa"},
		{BelowRight, "sd"}
	};
	
	return directionToDialect.at(direction);
}

export inline Direction from_dialect(const std::string& dialect) {
	using enum Direction;
	static const std::map<std::string, Direction> dialectToDirection = {
		{"w", Above},
		{"s", Below},
		{"a", Left},
		{"d", Right},
		{"wa", AboveLeft},
		{"wd", AboveRight},
		{"sa", BelowLeft},
		{"sd", BelowRight}
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

} // namespace Parity







