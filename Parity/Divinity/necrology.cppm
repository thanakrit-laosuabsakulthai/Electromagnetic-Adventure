export module Parity.Necrology;

#if defined(__INTELLISENSE__)
	#include <unordered_set>
	#include <map>
	#include <set>
	#include <vector>
	#include <string>
#else
	import std; // Standard library import
#endif

/*
- **Demon**
	- electromagnetic:electric_minion
	- electromagnetic:magnetic_demon
	- electromagnetic:magnetic_mage_demon
	- electromagnetic:electromagnetic_demon_boss
*/

export namespace Parity
{

export enum class DemonForm {
	ElectricMinion,
	MagneticDemon,
	MagneticMageDemon,
	ElectromagneticDemonBoss
};

export inline std::string_view to_string(DemonForm demon_form) {
	using enum DemonForm;
	static const std::map<DemonForm, std::string_view> demonformToString = {
		{ElectricMinion, "Electric Minion"},
		{MagneticDemon, "Magnetic Demon"},
		{MagneticMageDemon, "Magnetic Mage Demon"},
		{ElectromagneticDemonBoss, "‹Electromagnetic Demon Boss›"}
	};
	
	return demonformToString.at(demon_form);
}

export using DemonSeriality = int;
export using DemonPossession = std::map<DemonSeriality, DemonForm>;
export using Demonity = std::set<DemonSeriality>;
} // namespace Parity
