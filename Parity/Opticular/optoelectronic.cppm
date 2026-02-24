export module Parity.Optoelectronic;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <set>
	#include <string>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
#endif

export namespace Parity
{

export enum class OpticalEffect {
	Advantage,
	Weakness,
	Repulsion,
	Chromatic,
	Collimation
};

export enum class Optics {
	RadioWaves,
	MicroWaves,
	InfraredWaves,
	LightWaves,
	UltravioletWaves,
	XRays,
	GammaRays
};

export using Iridescent = std::set<OpticalEffect>;
export using Inventory = std::multiset<Optics>;
export using MarketValuation = std::map<Optics, int>;

export MarketValuation Marketplace = {
	{ Optics::RadioWaves, 2 },
	{ Optics::MicroWaves, 2 },
	{ Optics::InfraredWaves, 1 },
	{ Optics::LightWaves, 3 },
	{ Optics::UltravioletWaves, 5 },
	{ Optics::XRays, 5 },
	{ Optics::GammaRays, 10 }
};

} // namespace Parity