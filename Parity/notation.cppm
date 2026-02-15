export module Parity.Notation;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <string_view>
	#include <format>
	#include <print>
	#include "type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.Geography;
#endif

export namespace Parity
{

export inline std::string_view to_braket_notation(ApparentGeometry geometry) {
	using enum ApparentGeometry;
	static const std::map<ApparentGeometry, std::string_view> geometryToBraketNotation = {
		{Square, "⟦{}⟧"},
		{Diamond, "⟨{}⟩"},
		{Rectangle, "｢{}｣"},
		{LongRectangle, "｢{}｣"}
	};
	
	return geometryToBraketNotation.at(geometry);
}

export inline std::string_view to_sapce_notation(ApparentGeometry geometry) {
	using enum ApparentGeometry;
	static const std::map<ApparentGeometry, std::string_view> geometryToSpaceNotation = {
		{Square, "{} Square Space"},
		{Diamond, "{} Diamond Space"},
		{Rectangle, "{} Space"},
		{LongRectangle, "Long {} Space"}
	};
	
	return geometryToSpaceNotation.at(geometry);
}


export inline std::string_view to_zone_notation(Zone zone) {
	using enum Zone;
	static const std::map<Zone, std::string_view> zoneToNotation = {
		{SafeZone, "{} ¦ Safe Zone"},
		{DemonZone, "{} ¦ Demon Zone"},
		{NeutralZone, "{}"}
	};
	
	return zoneToNotation.at(zone);
}

export inline std::string word_synthesis(ApparentQuality quality, ApparentColor color) {
	if (quality == ApparentQuality::Color) {
		return std::string(to_string(color));
	} else {
		return "Imitation " + std::string(to_string(color));
	}
}

export inline std::string word_synthesis(ApparentQuality quality, ApparentColor color, ApparentGeometry geometry) {
	std::string quality_color_word = word_synthesis(quality, color);
	std::string_view shape_space_notation = to_sapce_notation(geometry);
	
	return std::vformat(shape_space_notation, std::make_format_args(quality_color_word));
}

export inline std::string zone_notation_synthesis(Zone zone, std::string content_prepend_zone) {
	std::string_view zone_notation = to_zone_notation(zone);
	return std::vformat(zone_notation, std::make_format_args(content_prepend_zone));
}

export inline std::string braket_notation_synthesis(ApparentGeometry geometry, std::string content_inside_braket) {
	std::string_view braket_pattern = to_braket_notation(geometry);
	return std::vformat(braket_pattern, std::make_format_args(content_inside_braket));
}

//  ⟨Pink Diamond Space ¦ Safe Zone⟩

export void print_all_landmark_notations() {
	for (const auto &[landmark, posession] : Atlas) {
		std::string landmark_name = std::string(to_string(landmark));
		
		std::string apparent_word = word_synthesis(posession.apparentQuality, posession.apparentColor, posession.apparentGeometry);
		std::string apparent_zone_word = zone_notation_synthesis(posession.zone, apparent_word);
		std::string full_notation = braket_notation_synthesis(posession.apparentGeometry, apparent_zone_word);
		std::print("{}: {}\n", landmark_name, full_notation);
	}
	std::print("\n");
}

} // End of namespace Parity
 
/*


1. **Diamond of Cattail (Capital)**
	- ⟨Pink Diamond Space ¦ Safe Zone⟩
	- Player spawn point & Player respawn point 
	- — ｢Ordinary Cattail (Prefecture)｣ ↑ above
	- — ｢Golden Cattail (Prefecture)｣ → right

*/