export module Parity.OpticalNotation;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string_view>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.Optoelectronic;
	import Parity.Geography;
#endif

export namespace Parity
{


export inline std::string_view to_string(Optics optical_item) {
	using enum Optics;
	static const std::map<Optics, std::string_view> opticNames = {
		{ RadioWaves, "Radio Waves" },
		{ MicroWaves, "Microwaves" },
		{ InfraredWaves, "Infrared Waves" },
		{ LightWaves, "Light Waves" },
		{ UltravioletWaves, "Ultraviolet Waves" },
		{ XRays, "X-Rays" },
		{ GammaRays, "Gamma Rays" }
	};
	
	return opticNames.at(optical_item);
}

export inline std::string_view to_description(Optics optical_item) {
	using enum Optics;
	static const std::map<Optics, std::string_view> opticDescriptions = {
		{ RadioWaves, "Use this item to call for support. Trigger the Lucky Board once." },
		{ MicroWaves, "Use this item after winning a combat to cook the demon's meat. Heal 1 Heart upon consumption." },
		{ InfraredWaves, "Use this item to detect a demon's heat signature weakness. Reduce the demon's Power by 1 for that combat." },
		{ LightWaves, "Use this item when landing on a Gradient space to choose the color effect instead of rolling the die for that turn's resolution." },
		{ UltravioletWaves, "Use this item when entering a space with a demon. The demon retreats 1 space, and combat does not occur. This item cannot be used in the Demon Zone." },
		{ XRays, "Use this item to scan a demon's internal structure. The player gains Advantage status for that combat. When a player has this status, they roll 2 dice and use the higher result multiplied by their Power for their Attack Value." },
		{ GammaRays, "Use this item in combat. The player's Power increases by 10 for that combat, and their attack hits all demons in the space." }
	};
	
	return opticDescriptions.at(optical_item);
}

export using Chromaticon = std::map<ApparentColor, std::string_view>;

export inline const Chromaticon LightWaveExtensionDescriptions = {
	{ ApparentColor::PinkOrangeYellowGradient, "Choose Pink, Orange, or Yellow effect." },
	{ ApparentColor::RedPurpleGradient, "Choose Red or Purple effect." },
	{ ApparentColor::WhiteGrayGradient, "Choose any non-gradient color effect. The space retains this chosen color effect until changed again by this item." }
};

// extended descriptions for Light Waves
export inline std::string_view to_light_wave_description(ApparentColor gradient_color) {
	return LightWaveExtensionDescriptions.at(gradient_color);
}



/* 

1.  **Radio Waves (2 Gold):** Use this item to call for support. Trigger the Lucky Board once.
2.  **Microwaves (2 Gold):** Use this item *after* winning a combat to cook the demon's meat. Heal 1 Heart upon consumption.
3.  **Infrared Waves (1 Gold):** Use this item to detect a demon's heat signature weakness. Reduce the demon's Power by 1 for that combat.
4.  **Light Waves (3 Gold):** Use this item when landing on a Gradient space to choose the color effect instead of rolling the die for that turn's resolution.
	*   Pink-Orange-Yellow Gradient: Choose Pink, Orange, or Yellow effect.
	*   Red-Purple Gradient: Choose Red or Purple effect.
	*   White-Gray Gradient: Choose *any* non-gradient color effect. The space retains this chosen color effect until changed again by this item.
5.  **Ultraviolet Waves (5 Gold):** Use this item when entering a space with a demon. The demon retreats 1 space, and combat does not occur. This item cannot be used in the Demon Zone.
6.  **X-Rays (5 Gold):** Use this item to scan a demon's internal structure. The player gains ==Advantage== status for that combat. When a player has this status, they roll 2 dice and use the higher result multiplied by their Power for their Attack Value.
7.  **Gamma Rays (10 Gold):** Use this item in combat. The player's Power increases by 10 for that combat, and their attack hits *all* demons in the space.

*/
} // namespace Parity