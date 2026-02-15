#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <memory>
#include <map>
#include <vector>

export namespace Parity {

export enum class DieRoll : int
{
	One = 1,
	Two,
	Three,
	Four,
	Five,
	Six
};

// +++------>>> biology.cppm <<<------+++

export enum class PlayerIdentity {
	AmethystApprentice,
	SapphireSummoner,
	EmeraldEnchantress,
	OpalinOracle
};

export enum class OpticalEffect {
	Advantage,
	Weakness,
	Repulsion,
	Chromatic,
	Collimation
};

export struct PlayerPosession {
	int gold_coin;
	int permanent_power_point;
	int vitality_heart;
	int vitality_maximum_heart;
	std::unordered_set<OpticalEffect> active_optical_effect;
};

export using Humanity = std::unordered_map<PlayerIdentity, PlayerPosession>;

export inline std::string_view to_string(PlayerIdentity identity);

// +++------>>> overworld.cppm <<<------+++

export struct Rule { 
	virtual ~Rule();
	virtual void execute(class Overworld &world);
};

export class Overworld
{
	public:
	
	Announcement announce;
	
	DieRoll die_roll_for_fortune_board;
	int fortune_board_multiplier;
	int useFortuneBoardMultiplier();
	Humanity playerbase;
	PlayerIdentity active_player;
	
	int amount_of_new_event;
	std::deque<std::unique_ptr<Rule>> event_queue;
	void main_loop();
	
	template <typename Extent_of_Rule, typename... Argument_of_Rule>
	void event(Argument_of_Rule&&... custom_arguments);
};

// +++------>>> fortuneboard.cppm <<<------+++

export struct Gain_Gold_Coin : Rule {
	int amount_of_gold_coin;
	Gain_Gold_Coin(int amount);
	void execute(Overworld &world) override;
};

export struct Gain_Permanent_Power_Point : Rule {
	int amount_of_permanent_power;
	Gain_Permanent_Power_Point(int amount);
	void execute(Overworld &world) override;
};

export struct Apply_Lucky_Board_Result : Rule {
	void execute(Overworld &world) override;
	void applyLuckyBoardResult(Overworld &world, DieRoll roll);
};

export struct Roll_For_Random_Board : Rule {
	void execute(Overworld &world) override;
};

export struct Lucky_Board : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> geography.cppm <<<------+++

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

export Geography Atlas;

export inline std::string_view to_string(Landmark landmark);
export inline std::string_view to_string(Region region);
export inline std::string_view to_string(Zone zone);
export inline std::string_view to_string(ApparentColor color);
export inline std::string_view to_string(ApparentGeometry geometry);
export inline std::string_view to_string(Direction direction);
export inline std::string_view to_string(Path path);


// +++------>>> notation.cppm <<<------+++

export inline std::string_view to_braket_notation(ApparentGeometry geometry);
export inline std::string_view to_sapce_notation(ApparentGeometry geometry);
export inline std::string_view to_zone_notation(Zone zone);
export inline std::string word_synthesis(ApparentQuality quality, ApparentColor color);
export inline std::string word_synthesis(ApparentQuality quality, ApparentColor color, ApparentGeometry geometry);
export inline std::string zone_notation_synthesis(Zone zone, std::string content_prepend_zone);
export inline std::string braket_notation_synthesis(ApparentGeometry geometry, std::string content_inside_braket);

export void print_all_landmark_notations();

// +++------>>> announcement.cppm <<<------+++

enum class AnnouncementClause {
	Subtitle,
	ConsequentialAction,
	ConsequentialResult,
	ConsequenctalBullet,
	ConsequentialIndentation,
	ConsequentialItalic,
};

enum class FormattingNotation {
	Plain,
	Bold,
	Italic,
	Underline,
	Cyan,
};

inline std::string_view to_notation(FormattingNotation notation);
inline std::string bold(const std::string content);
inline std::string italic(const std::string content);
inline std::string cyan(const std::string content);
inline std::string italic_cyan(const std::string content);

class Announcement {
public:
	AnnouncementClause clause;
	int consequential_ordinal = 0;
	void action(const std::string& content_append_action);
	void result(const std::string& content_append_result);
	void bygone(const std::string& content_of_bygone);
};

} // namespace Parity