export module Parity.Geography;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <map>
	#include <set>
	#include <vector>
	#include <string>
	#include <string_view>
	#include <format>
	#include <print>
#else
	import std; // Standard library import
#endif

export namespace Parity
{

export enum class Landmark : int {
	DiamondOfCattail = 1,
	OrdinaryCattail,
	GoldenCattail,
	OpticalAurum,
	OpticalMarketplace,
	OpticalCorruption,
	ContestedCorruption,
	SparseForestland,
	AutumnForestland,
	FountainOfApricot,
	PrismaticFieldstone,
	SouthernHorizon,
	NorthernHorizon,
	TheCataclysm,
	DiamondOfParity
};

export enum class Region {
	Capital,
	Prefecture,
	Wilderness,
	Afterfae,
	Demonic,
	Pandemonium
};


export enum class Zone {
	SafeZone,
	DemonZone,
	NeutralZone
};

export enum class ApparentQuality {
	Color,
	ImitationOfColor
};

export enum class ApparentColor {
	Pink,
	Green,
	Orange,
	Yellow,
	Red,
	Purple,
	PinkOrangeYellowGradient,
	RedPurpleGradient,
	WhiteGrayGradient
};

export enum class ApparentGeometry {
	Square,
	Diamond,
	Rectangle,
	LongRectangle
};

export enum class Path {
	WalkPath,
	WarpPath,
	ArrowPath,
	ArrowWarpPath,
	ArrowRestrictedPath,
	ArrowRestrictedWarpPath
};

export enum class Direction {
	Above,
	Below,
	Left,
	Right,
	AboveLeft,
	AboveRight,
	BelowLeft,
	BelowRight
};

export using MultiDirection = std::vector<Direction>;

export struct Pathway {
	Path pathType;
	Landmark destination;
	Direction direction;
};

export using Passageway = std::vector<Pathway>;

export struct LandmarkPosession {
	Zone zone;
	Region region;
	ApparentQuality apparentQuality;
	ApparentColor apparentColor;
	ApparentGeometry apparentGeometry;
	Passageway passageway;
};

export using Geography = std::map<Landmark, LandmarkPosession>;

export Geography Atlas = {
	{ Landmark::DiamondOfCattail, {
		Zone::SafeZone,
		Region::Capital,
		ApparentQuality::Color,
		ApparentColor::Pink,
		ApparentGeometry::Diamond,
		Passageway {
			{Path::WalkPath, Landmark::OrdinaryCattail, Direction::Above},
			{Path::WalkPath, Landmark::GoldenCattail, Direction::Right}
		}
	} },
	{ Landmark::OrdinaryCattail, {
		Zone::SafeZone,
		Region::Prefecture,
		ApparentQuality::Color,
		ApparentColor::Green,
		ApparentGeometry::Rectangle,
		Passageway {
			{Path::WalkPath, Landmark::OpticalAurum, Direction::Above},
			{Path::WalkPath, Landmark::DiamondOfCattail, Direction::Below}
		}
	} },
	{ Landmark::GoldenCattail, {
		Zone::SafeZone,
		Region::Prefecture,
		ApparentQuality::Color,
		ApparentColor::Orange,
		ApparentGeometry::Rectangle,
		Passageway {
			{Path::WalkPath, Landmark::ContestedCorruption, Direction::Right},
			{Path::WalkPath, Landmark::DiamondOfCattail, Direction::Left}
		}
	} },
	{ Landmark::OpticalAurum, {
		Zone::NeutralZone,
		Region::Wilderness,
		ApparentQuality::Color,
		ApparentColor::Orange,
		ApparentGeometry::Rectangle,
		Passageway {
			{Path::WalkPath, Landmark::OpticalMarketplace, Direction::Above},
			{Path::WalkPath, Landmark::OrdinaryCattail, Direction::Below}
		}
	} },
	{ Landmark::OpticalMarketplace, {
		Zone::NeutralZone,
		Region::Wilderness,
		ApparentQuality::Color,
		ApparentColor::Yellow,
		ApparentGeometry::LongRectangle,
		Passageway {
			{Path::WalkPath, Landmark::OpticalCorruption, Direction::Right},
			{Path::WalkPath, Landmark::OpticalAurum, Direction::Below},
			{Path::WarpPath, Landmark::FountainOfApricot, Direction::Left}
		}
	} },
	{ Landmark::OpticalCorruption, {
		Zone::NeutralZone,
		Region::Wilderness,
		ApparentQuality::Color,
		ApparentColor::RedPurpleGradient,
		ApparentGeometry::Rectangle,
		Passageway {
			{Path::WalkPath, Landmark::NorthernHorizon, Direction::Right},
			{Path::WalkPath, Landmark::OpticalMarketplace, Direction::Left},
			{Path::ArrowRestrictedWarpPath, Landmark::ContestedCorruption, Direction::Above}
		}
	} },
	{ Landmark::ContestedCorruption, {
		Zone::NeutralZone,
		Region::Wilderness,
		ApparentQuality::Color,
		ApparentColor::Red,
		ApparentGeometry::Square,
		Passageway {
			{Path::WalkPath, Landmark::SparseForestland, Direction::Right},
			{Path::WalkPath, Landmark::GoldenCattail, Direction::Left},
			{Path::ArrowWarpPath, Landmark::OpticalCorruption, Direction::Below}
		}
	} },
	{ Landmark::SparseForestland, {
		Zone::NeutralZone,
		Region::Afterfae,
		ApparentQuality::Color,
		ApparentColor::Green,
		ApparentGeometry::Rectangle,
		Passageway {
			{Path::WalkPath, Landmark::AutumnForestland, Direction::AboveRight},
			{Path::WalkPath, Landmark::ContestedCorruption, Direction::Left},
			{Path::ArrowPath, Landmark::PrismaticFieldstone, Direction::Above},
			{Path::ArrowPath, Landmark::FountainOfApricot, Direction::Right}
		}
	} },
	{ Landmark::AutumnForestland, {
		Zone::NeutralZone,
		Region::Afterfae,
		ApparentQuality::Color,
		ApparentColor::Orange,
		ApparentGeometry::Rectangle,
		Passageway {
			{Path::WalkPath, Landmark::PrismaticFieldstone, Direction::AboveLeft},
			{Path::WalkPath, Landmark::SparseForestland, Direction::BelowLeft},
			{Path::ArrowRestrictedPath, Landmark::FountainOfApricot, Direction::Below}
		}
	} },
	{ Landmark::FountainOfApricot, {
		Zone::NeutralZone,
		Region::Afterfae,
		ApparentQuality::Color,
		ApparentColor::PinkOrangeYellowGradient,
		ApparentGeometry::Rectangle,
		Passageway {
			{Path::WarpPath, Landmark::OpticalMarketplace, Direction::Right},
			{Path::ArrowPath, Landmark::AutumnForestland, Direction::AboveLeft},
			{Path::ArrowRestrictedPath, Landmark::SparseForestland, Direction::Left}
		}
	} },
	{ Landmark::PrismaticFieldstone, {
		Zone::NeutralZone,
		Region::Afterfae,
		ApparentQuality::Color,
		ApparentColor::WhiteGrayGradient,
		ApparentGeometry::Rectangle,
		Passageway {
			{Path::WalkPath, Landmark::SouthernHorizon, Direction::Above},
			{Path::WalkPath, Landmark::AutumnForestland, Direction::BelowRight},
			{Path::ArrowRestrictedPath, Landmark::SparseForestland, Direction::BelowLeft}
		}
	} },
	{ Landmark::SouthernHorizon, {
		Zone::DemonZone,
		Region::Demonic,
		ApparentQuality::Color,
		ApparentColor::Red,
		ApparentGeometry::Rectangle,
		Passageway {
			{Path::ArrowPath, Landmark::TheCataclysm, Direction::Above},
			{Path::WalkPath, Landmark::PrismaticFieldstone, Direction::Below}
		}
	} },
	{ Landmark::NorthernHorizon, {
		Zone::DemonZone,
		Region::Demonic,
		ApparentQuality::Color,
		ApparentColor::Red,
		ApparentGeometry::Rectangle,
		Passageway {
			{Path::ArrowPath, Landmark::TheCataclysm, Direction::Right},
			{Path::WalkPath, Landmark::OpticalCorruption, Direction::Left}
		}
	} },
	{ Landmark::TheCataclysm, {
		Zone::DemonZone,
		Region::Demonic,
		ApparentQuality::Color,
		ApparentColor::Red,
		ApparentGeometry::Rectangle,
		Passageway {
			{Path::WalkPath, Landmark::DiamondOfParity, Direction::AboveRight},
			{Path::ArrowRestrictedPath, Landmark::SouthernHorizon, Direction::Below},
			{Path::ArrowRestrictedPath, Landmark::NorthernHorizon, Direction::Left}
		}
	} },
	{ Landmark::DiamondOfParity, {
		Zone::DemonZone,
		Region::Pandemonium,
		ApparentQuality::Color,
		ApparentColor::Purple,
		ApparentGeometry::Diamond,
		Passageway {
			{Path::WalkPath, Landmark::TheCataclysm, Direction::BelowLeft}
		}
	} }
};


export inline bool is_arrow_path(const Path& path) {
	using enum Path;
	return path == ArrowPath || path == ArrowWarpPath || path == ArrowRestrictedPath || path == ArrowRestrictedWarpPath;
}

export inline bool is_restricted_path(const Path& path) {
	using enum Path;
	return path == ArrowRestrictedPath || path == ArrowRestrictedWarpPath;
}

export inline bool is_gradient_color(const ApparentColor& color) {
	using enum ApparentColor;
	return color == PinkOrangeYellowGradient || color == RedPurpleGradient || color == WhiteGrayGradient;
}

} // End of namespace Parity

/* 
1. Diamond of Cattail (Capital)
2. Ordinary Cattail (Prefecture)
3. Golden Cattail (Prefecture)
4. Optical Aurum (Wilderness)
5. Optical Marketplace (Wilderness)
6. Optical Corruption (Wilderness)
7. Contested Corruption (Wilderness)
8. Sparse Forestland (Afterfae)
9. Autumn Forestland (Afterfae)
10. Fountain of Apricot (Afterfae)
11. Prismatic Fieldstone (Afterfae)
12. Southern Horizon (Demonic)
13. Northern Horizon (Demonic)
14. The Cataclysm (Demonic)
15. Diamond of Parity (Pandemonium)

---

1. **Diamond of Cattail (Capital)**
	- ⟨Pink Diamond Space ¦ Safe Zone⟩
	- Player spawn point & Player respawn point 
	- — ｢Ordinary Cattail (Prefecture)｣ ↑ above
	- — ｢Golden Cattail (Prefecture)｣ → right
2. **Ordinary Cattail (Prefecture)**
	- ｢Green Space ¦ Safe Zone｣
	- — ｢Optical Aurum (Wilderness)｣ ↑ above
	- — ⟨Diamond of Cattail (Capital)⟩ ↓ below 
3. **Golden Cattail (Prefecture)**
	- ｢Orange Space ¦ Safe Zone｣
	- — ｢Contested Corruption (Wilderness)｣ → left
	- — ⟨Diamond of Cattail (Capital)⟩ ← right 
4. **Optical Aurum (Wilderness)**
	- ｢Orange Space｣
	- — ｢Optical Marketplace (Wilderness)｣ ↑ above
	- — ｢Ordinary Cattail (Prefecture)｣ ↓ below 
5. **Optical Marketplace (Wilderness)**
	- ｢Yellow Long Space｣
	- The only shop space in the map
	- — ｢Optical Corruption (Wilderness)｣ → right 
	- — ｢Optical Aurum (Wilderness)｣ ↓ below
	- — ｢Fountain of Apricot (Afterfae)｣ ← left warp
6. **Optical Corruption (Wilderness)**
	- ｢Red-Purple Gradient Space｣
	- — ｢Northern Horizon (Demonic)｣ → right 
	- — ｢Optical Marketplace (Wilderness)｣ ← left
	- ←×— ⟦Contested Corruption (Wilderness)⟧ ↑ above warp
7. **Contested Corruption (Wilderness)**
	- ⟦Red Square Space⟧
	- — ｢Sparse Forestland (Afterfae)｣ → right
	- — ｢Golden Cattail (Prefecture)｣ ← left
	- → ｢Optical Corruption (Wilderness)｣ ↓ below warp
8. **Sparse Forestland (Afterfae)**
	- ｢Green Space｣
	- — ｢Autumn Forestland (Afterfae)｣ ↗ above right
	- — ⟦Contested Corruption (Wilderness)⟧ ← left 
	- → ｢Prismatic Fieldstone (Afterfae)｣ ↑ above
	- → ｢Fountain of Apricot (Afterfae)｣ → right 
9. **Autumn Forestland (Afterfae)**
	- ｢Orange Space｣
	- — ｢Prismatic Fieldstone (Afterfae)｣ ↖ above left
	- — ｢Sparse Forestland (Afterfae)｣ ↙ below left 
	- ←×— ｢Fountain of Apricot (Afterfae)｣ ↓ below
10. **Fountain of Apricot (Afterfae)**
	- ｢Pink-Orange-Yellow Gradient Space｣
	- — ｢Optical Marketplace (Wilderness)｣ → right warp
	- → ｢Autumn Forestland (Afterfae)｣ ↖ above left
	- ←×— ｢Sparse Forestland (Afterfae)｣ ← left 
11. **Prismatic Fieldstone (Afterfae)**
	- ｢White-Gray Gradient Space｣
	- — ｢Southern Horizon (Demonic)｣ ↑ above
	- — ｢Autumn Forestland (Afterfae)｣ ↘ below right
	- ←×— ｢Sparse Forestland (Afterfae)｣ ↙ below left  
12. **Southern Horizon (Demonic)**
	- ｢Red Space ¦ Demon Zone｣
	- → ｢The Cataclysm (Demonic)｣ ↑ above
	- — ｢Prismatic Fieldstone (Afterfae)｣ ↓ below
13. **Northern Horizon (Demonic)**
	- ｢Red Space ¦ Demon Zone｣
	- → ｢The Cataclysm (Demonic)｣ → right
	- — ｢Optical Corruption (Wilderness)｣ ← left
14. **The Cataclysm (Demonic)**
	- ｢Red Space ¦ Demon Zone｣
	- — ⟨Diamond of Parity (Pandemonium)⟩ ↗ above right
	- ←×— ｢Southern Horizon (Demonic)｣ ↓ below
	- ←×— ｢Northern Horizon (Demonic)｣ ← left
15. **Diamond of Parity (Pandemonium)**
	- ⟨Purple Diamond Space ¦ Demon Zone⟩
	- The ‹Electromagnetic Demon Boss› enthrones here
	- — ｢The Cataclysm｣ ↙ below left  

---

###### Bullet Point Definition: Electromagnetic Namespace

- **Geography**
	- electromagnetic:diamond_of_cattail
	- electromagnetic:ordinary_cattail
	- electromagnetic:golden_cattail
	- electromagnetic:optical_aurum
	- electromagnetic:optical_marketplace
	- electromagnetic:optical_corruption
	- electromagnetic:contested_corruption
	- electromagnetic:sparse_forestland
	- electromagnetic:autumn_forestland
	- electromagnetic:fountain_of_apricot
	- electromagnetic:prismatic_fieldstone
	- electromagnetic:southern_horizon
	- electromagnetic:northern_horizon
	- electromagnetic:the_cataclysm
	- electromagnetic:diamond_of_parity
- **Region** 
	- electromagnetic:capital
	- electromagnetic:prefecture
	- electromagnetic:wilderness
	- electromagnetic:afterfae
	- electromagnetic:demonic
	- electromagnetic:pandemonium
- **Apparent Quality**
	- electromagnetic:color
	- electromagnetic:imitation_of_color
- **Apparent Color**
	- electromagnetic:pink
	- electromagnetic:green
	- electromagnetic:orange
	- electromagnetic:yellow
	- electromagnetic:red
	- electromagnetic:purple
	- electromagnetic:pink_orange_yellow_gradient
	- electromagnetic:red_purple_gradient
	- electromagnetic:white_gray_gradient
- **Apparent Geometry**
	- electromagnetic:square
	- electromagnetic:diamond
	- electromagnetic:rectangle
	- electromagnetic:long_rectangle
- **Zone**
	- electromagnetic:safe_zone
	- electromagnetic:demon_zone
	- electromagnetic:neutral_zone
- **Path**
	- electromagnetic:path
	- electromagnetic:warp_path
	- electromagnetic:arrow_path
	- electromagnetic:arrow_warp_path
	- electromagnetic:arrow_restricted_path
	- electromagnetic:arrow_restricted_warp_path
- **Direction**
	- electromagnetic:above
	- electromagnetic:below
	- electromagnetic:left
	- electromagnetic:right
	- electromagnetic:above_left
	- electromagnetic:above_right
	- electromagnetic:below_left
	- electromagnetic:below_right
*/