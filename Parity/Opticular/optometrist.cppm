export module Parity.Optometrist;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <set>
	#include <string>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.FortuneBoard;
	import Parity.Physiology;
	import Parity.Marketplace;
#endif


export namespace Parity
{

void Consumption_Of_RadioWaves::execute(Overworld &world) {
	world.event<Lucky_Board>();
}
void Consumption_Of_MicroWaves::execute(Overworld &world) {
	world.event<Vitality_Heal>(1);
}
void Consumption_Of_InfraredWaves::execute(Overworld &world) {
	world.event<Gain_Optical_Effect>(OpticalEffect::Ascendancy);
}
void Consumption_Of_LightWaves::execute(Overworld &world) {
	world.event<Gain_Optical_Effect>(OpticalEffect::Chromatic);
}
void Consumption_Of_UltravioletWaves::execute(Overworld &world) {
	world.event<Gain_Optical_Effect>(OpticalEffect::Repulsion);
}
void Consumption_Of_XRays::execute(Overworld &world) {
	world.event<Gain_Optical_Effect>(OpticalEffect::Advantage);
}
void Consumption_Of_GammaRays::execute(Overworld &world) {
	world.event<Gain_Optical_Effect>(OpticalEffect::Collimation);
}

// set potential consumption to every item in the game
void Excellece_Of_Consumption::execute(Overworld &world) {
	world.potential_consumption = {
		Optics::RadioWaves,
		Optics::MicroWaves,
		Optics::InfraredWaves,
		Optics::LightWaves,
		Optics::UltravioletWaves,
		Optics::XRays,
		Optics::GammaRays
	};
	
	world.event<Open_Inventory>();
}

} // namespace Parity