export module Parity.Necromancy;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	
	import Parity.Necrology;
	import Parity.Expedition;
#endif

export namespace Parity
{
//

DemonForm Overworld::getActiveDemonForm() {
	DemonSeriality active_demon = active_demon_seriality;
	DemonManifest &demon_manifest = expedition.antidivinity.demon_manifest;
	DemonForm active_demon_form = demon_manifest.at(active_demon);
	return active_demon_form;
}

Landmark Overworld::getLandmarkOfActiveDemon() {
	DemonSeriality active_demon = active_demon_seriality;
	Landmark landmark_of_active_demon = expedition.antidivinity.getLandmarkOf(active_demon);
	return landmark_of_active_demon;
}


export struct Summon_Demon : Rule {
	DemonForm demonform;
	Landmark landmark_of_summoning;
	
	Summon_Demon(DemonForm demonform, Landmark landmark_of_summoning) : demonform(demonform), landmark_of_summoning(landmark_of_summoning) {}
	void execute(Overworld &world) override;
};

/* 
appearancy()
- *Electric Minion spawns on the Red Square space.*
*/


























} // namespace Parity
















