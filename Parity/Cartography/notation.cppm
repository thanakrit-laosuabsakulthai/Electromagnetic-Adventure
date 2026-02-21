export module Parity.Notation;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <string_view>
	#include <format>
	#include <print>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.Geography;
	import Parity.Encyclopedia;
#endif

export namespace Parity
{

export inline std::string_view to_string(Landmark landmark) {
	using enum Landmark;
	static const std::map<Landmark, std::string_view> landmarkToString = {
		{DiamondOfCattail, "Diamond of Cattail"},
		{OrdinaryCattail, "Ordinary Cattail"},
		{GoldenCattail, "Golden Cattail"},
		{OpticalAurum, "Optical Aurum"},
		{OpticalMarketplace, "Optical Marketplace"},
		{OpticalCorruption, "Optical Corruption"},
		{ContestedCorruption, "Contested Corruption"},
		{SparseForestland, "Sparse Forestland"},
		{AutumnForestland, "Autumn Forestland"},
		{FountainOfApricot, "Fountain of Apricot"},
		{PrismaticFieldstone, "Prismatic Fieldstone"},
		{SouthernHorizon, "Southern Horizon"},
		{NorthernHorizon, "Northern Horizon"},
		{TheCataclysm, "The Cataclysm"},
		{DiamondOfParity, "Diamond of Parity"}
	};
	
	return landmarkToString.at(landmark);
}

export inline std::string_view to_string(Region region) {
	using enum Region;
	static const std::map<Region, std::string_view> regionToString = {
		{Capital, "Capital"},
		{Prefecture, "Prefecture"},
		{Wilderness, "Wilderness"},
		{Afterfae, "Afterfae"},
		{Demonic, "Demonic"},
		{Pandemonium, "Pandemonium"}
	};
	
	return regionToString.at(region);
}

export inline std::string_view to_string(Zone zone) {
	using enum Zone;
	static const std::map<Zone, std::string_view> zoneToString = {
		{SafeZone, "Safe Zone"},
		{DemonZone, "Demon Zone"},
		{NeutralZone, "Neutral Zone"}
	};
	
	return zoneToString.at(zone);
}

export inline std::string_view to_string(ApparentColor color) {
	using enum ApparentColor;
	static const std::map<ApparentColor, std::string_view> colorToString = {
		{Pink, "Pink"},
		{Green, "Green"},
		{Orange, "Orange"},
		{Yellow, "Yellow"},
		{Red, "Red"},
		{Purple, "Purple"},
		{PinkOrangeYellowGradient, "Pink-Orange-Yellow Gradient"},
		{RedPurpleGradient, "Red-Purple Gradient"},
		{WhiteGrayGradient, "White-Gray Gradient"}
	};
	
	return colorToString.at(color);
}

export inline std::string_view to_string(ApparentGeometry geometry) {
	using enum ApparentGeometry;
	static const std::map<ApparentGeometry, std::string_view> geometryToString = {
		{Square, "Square"},
		{Diamond, "Diamond"},
		{Rectangle, "Rectangle"},
		{LongRectangle, "Long Rectangle"}
	};
	
	return geometryToString.at(geometry);
}

export inline std::string_view to_string(Direction direction) {
	using enum Direction;
	static const std::map<Direction, std::string_view> directionToString = {
		{Above, "↑ above"},
		{Below, "↓ below"},
		{Left, "← left"},
		{Right, "→ right"},
		{AboveLeft, "↖ above left"},
		{AboveRight, "↗ above right"},
		{BelowLeft, "↙ below left"},
		{BelowRight, "↘ below right"}
	};
	
	return directionToString.at(direction);
}

export inline std::string_view to_string(Path path) {
	using enum Path;
	static const std::map<Path, std::string_view> pathToString = {
		{WalkPath, "—"},
		{WarpPath, "—"},
		{ArrowPath, "→"},
		{ArrowWarpPath, "→"},
		{ArrowRestrictedPath, "←×—"},
		{ArrowRestrictedWarpPath, "←×—"}
	};
	
	return pathToString.at(path);
}

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

export inline std::string_view to_space_notation(ApparentGeometry geometry) {
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

export inline std::string chromaticon(ApparentQuality quality, ApparentColor color) {
	if (quality == ApparentQuality::Color) {
		return std::string(to_string(color));
	} else {
		return "Imitation " + std::string(to_string(color));
	}
}

export inline std::string appearancy(ApparentQuality quality, ApparentColor color, ApparentGeometry geometry) {
	std::string quality_color_word = chromaticon(quality, color);
	std::string_view shape_space_notation = to_space_notation(geometry);
	
	return std::vformat(shape_space_notation, std::make_format_args(quality_color_word));
}

export inline std::string zonoity(Zone zone, std::string content_prepend_zone) {
	std::string_view zone_notation = to_zone_notation(zone);
	return std::vformat(zone_notation, std::make_format_args(content_prepend_zone));
}

export inline std::string chronoity(Path path, std::string content_prepend_warp) {
	using enum Path;
	switch (path) {
		case WarpPath:
		case ArrowWarpPath:
		case ArrowRestrictedWarpPath:
			return content_prepend_warp + " warp";
		default:
			return content_prepend_warp;
	}
}

export inline std::string archeometrinoity(ApparentGeometry geometry, std::string content_inside_braket) {
	std::string_view braket_notation = to_braket_notation(geometry);
	return std::vformat(braket_notation, std::make_format_args(content_inside_braket));
}

// ⟨Pink Diamond Space ¦ Safe Zone⟩

export void print_all_landmark_notations() {
	for (const auto &[landmark, posession] : Atlas) {
		std::string landmark_name = std::string(to_string(landmark));
		
		std::string apparent_word = appearancy(posession.apparentQuality, posession.apparentColor, posession.apparentGeometry);
		std::string apparent_zone_word = zonoity(posession.zone, apparent_word);
		std::string full_notation = archeometrinoity(posession.apparentGeometry, apparent_zone_word);
		std::print("{}: {}\n", landmark_name, full_notation);
	}
	std::print("\n");
}

export inline std::string_view to_dialect(Direction direction) {
	using enum Direction;
	static const std::map<Direction, std::string_view> directionToDialect = {
		{Above, Encyclopedia.above},
		{Below, Encyclopedia.below},
		{Left, Encyclopedia.left},
		{Right, Encyclopedia.right},
		{AboveLeft, Encyclopedia.above_left},
		{AboveRight, Encyclopedia.above_right},
		{BelowLeft, Encyclopedia.below_left},
		{BelowRight, Encyclopedia.below_right}
	};
	
	return directionToDialect.at(direction);
}

export inline Direction from_dialect(const std::string& dialect) {
	using enum Direction;
	static const std::map<std::string_view, Direction> dialectToDirection = {
		{Encyclopedia.above, Above},
		{Encyclopedia.below, Below},
		{Encyclopedia.left, Left},
		{Encyclopedia.right, Right},
		{Encyclopedia.above_left, AboveLeft},
		{Encyclopedia.above_right, AboveRight},
		{Encyclopedia.below_left, BelowLeft},
		{Encyclopedia.below_right, BelowRight}
	};
	
	return dialectToDirection.at(dialect);
}

export inline std::string dialect_synthesis(MultiDirection multidirection) {
	std::string multidirection_word;
	for (const auto& direction : multidirection) {
		multidirection_word += std::string(to_dialect(direction));
		if (&direction != &multidirection.back()) {
			multidirection_word += " ";
		}
	}
	
	return multidirection_word;
}

} // End of namespace Parity
 
/*


1. **Diamond of Cattail (Capital)**
	- ⟨Pink Diamond Space ¦ Safe Zone⟩
	- Player spawn point & Player respawn point 
	- — ｢Ordinary Cattail (Prefecture)｣ ↑ above
	- — ｢Golden Cattail (Prefecture)｣ → right

*/