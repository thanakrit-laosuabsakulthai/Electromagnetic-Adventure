export module Electromagnetic.Core;
#if defined(__INTELLISENSE__)
	#include <iostream>
	#include <string>
	#include <map>
	#include <variant>
	#include <format>
	#include <print>
#else
	import std; // Standard library import
#endif

export namespace Electromagnetic
{
	// Global Context
	struct Overworld
	{
		int gold = 3;
		int last_die_roll = 0;
		std::string player_name = "AmethystApprentice";
	};

	// Internationalization Registry
	struct Internationalization
	{
		std::map<std::string, std::string> strings = {
			{"action.lucky", "» Action 3: {} rolls the Lucky Board once."},
			{"rule.roll", "Roll 1 die and apply the result…"},
			{"rule.gain_gold", "« Result 3: Gain 1 ==Gold Coin=="},
			{"atomic.give_gold", "* Gave 1 [Gold] to {}."},
			{"choice.4", "[x] Gain 1 Gold Coin."}};

		void translate(std::string_view key, auto... args)
		{
			if (strings.contains(key.data()))
			{
				auto fmt = strings.at(key.data()); // std::string
				auto out = std::vformat(std::string_view(fmt), std::make_format_args(args...));
				std::print("{}\n", out);
			}
		}
	};

	// Forward declarations of Rule types
	class LuckyBoardRule;
	class RollRule;
	class ApplyResultRule;
	class GainGoldRule;

	// The Rule Variant
	export using RuleVariant = std::variant<
		LuckyBoardRule,
		RollRule,
		ApplyResultRule,
		GainGoldRule
	>;
}