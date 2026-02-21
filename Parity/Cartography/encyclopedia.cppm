export module Parity.Encyclopedia;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <map>
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
#endif

export namespace Parity
{

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

export inline constexpr Dialect Encyclopedia{};

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

export inline std::string bag_notation_synthesis(std::string &content_inside_bag) {
	content_inside_bag = " " + content_inside_bag + " ";
	
	std::string_view bag_notation = to_bracket_notation(Multiplicity::One);
	return std::vformat(bag_notation, std::make_format_args(content_inside_bag));
}

} // namespace Parity