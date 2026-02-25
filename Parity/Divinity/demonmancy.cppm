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
	
	world.announce.bygone(std::format("{} spawns on the {}",
		std::string(to_string(demonform)),
		world.appearancity(landmark_of_summoning)
	));
	
	
}

} // namespace Parity