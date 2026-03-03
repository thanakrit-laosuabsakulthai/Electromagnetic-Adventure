export module Parity.Celestial;

#if defined(__INTELLISENSE__)
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.Announcement;
#endif

export namespace Parity
{
//
export enum class CelestialClause {
	VoidOfForgather,
	Sunrise,
	Dayspring,
	RestingPlace,
	SleepingPlace,
	Sunset,
	Twilight,
	Moonfall,
	Starlight
};

// string repetition for emdash because emdash is a multicharacter string in UTF-8
export inline std::string repetition(const std::string& target_string, int amount_of_repetition) {
	std::string result;
	for (int i = 0; i < amount_of_repetition; ++i) {
		result += target_string;
	}
	return result;
}

export inline std::string get_ornament_notation(int amount_of_emdash) {
	std::string ornament_emdash = repetition("—", amount_of_emdash);
	std::string center_placeholder = std::format("››› [{}] ‹‹‹", underline("{}"));
	return ornament_emdash + center_placeholder + ornament_emdash;
}


















} // namespace Parity