export module Parity.Demonmancy;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	
	import Parity.Necrology;
	import Parity.Expedition;
	
	import Parity.Necromancy;
#endif

export namespace Parity
{
//

void Summon_Demon::execute(Overworld &world) {
	
	AntiDivinity &antidivinity = world.expedition.antidivinity;
	
	antidivinity.addDemon(demonform, landmark_of_summoning);
	world.active_demon_seriality = antidivinity.next_demon_seriality - 1;
	
	
	if ( !(demonform == DemonForm::ElectromagneticDemonBoss) ) {
		world.announce.bygone(std::format("{} spawned on the {}",
			to_string(demonform),
			world.appearancity(landmark_of_summoning)
		));
	} else {
		world.announce.horizon(std::format("The {} spawned on the {}!",
			bold(std::string(to_string(demonform))),
			world.appearancity(landmark_of_summoning)
		));
	}
	
	
}

void Execute_As_Demon::execute(Overworld &world) {
	world.active_demon_seriality = demon_seriality;
}

} // namespace Parity