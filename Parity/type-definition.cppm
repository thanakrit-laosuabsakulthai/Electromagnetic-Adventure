#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <memory>
#include <map>
#include <string>
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

// +++------>>> physiology.cppm <<<------+++

export inline std::string_view to_string(PlayerIdentity identity);

// +++------>>> overworld.cppm <<<------+++

export struct Rule { 
	virtual ~Rule();
	virtual void execute(class Overworld &world);
};

export class Overworld
{
	public:
	
	// +++ announcement +++
	Announcement announce;
	// +++ geography +++
	Geography atlas;
	// +++ expedition-embark +++
	Expedition expedition;
	std::string appearanzonality(Landmark target_landmark);
	std::string appearancity(Landmark target_landmark);
	std::string pathochronality(Pathway target_pathway);
	
	// +++ fortuneboard +++
	DieRoll die_roll_for_fortune_board;
	int fortune_board_multiplier;
	int useFortuneBoardMultiplier();
	
	// +++  biology-physiology +++
	Humanity playerbase;
	PlayerIdentity active_player;
	std::string_view getActivePlayerName();
	
	// +++ rule-event +++
	int amount_of_new_event;
	void relocate_new_events_to_front();
	
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

export struct Move_Again_One_Space : Rule {
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

// +++------>>> notation.cppm <<<------+++

export inline std::string_view to_string(Landmark landmark);
export inline std::string_view to_string(Region region);
export inline std::string_view to_string(Zone zone);
export inline std::string_view to_string(ApparentColor color);
export inline std::string_view to_string(ApparentGeometry geometry);
export inline std::string_view to_string(Direction direction);
export inline std::string_view to_string(Path path);

export inline std::string_view to_braket_notation(ApparentGeometry geometry);
export inline std::string_view to_sapce_notation(ApparentGeometry geometry);
export inline std::string_view to_zone_notation(Zone zone);
export inline std::string word_synthesis(ApparentQuality quality, ApparentColor color);
export inline std::string appearancy(ApparentQuality quality, ApparentColor color, ApparentGeometry geometry);
export inline std::string zonoity(Zone zone, std::string content_prepend_zone);
export inline std::string chronoity(Path path, std::string content_prepend_warp);
export inline std::string braket_notation_synthesis(ApparentGeometry geometry, std::string content_inside_braket);

export void print_all_landmark_notations();

// +++------>>> announcement.cppm <<<------+++

export enum class MediaClause {
	Media,
	MediaBullet,
	MediaChoicebox,
};

export enum class FormattingNotation {
	Plain,
	Bold,
	Italic,
	Underline,
	Cyan,
};

export inline std::string_view to_notation(FormattingNotation notation);
export inline std::string bold(const std::string content);
export inline std::string italic(const std::string content);
export inline std::string cyan(const std::string content);
export inline std::string italic_cyan(const std::string content);

export class Announcement {
public:
	MediaClause clause;
	int consequential_ordinal = 0;
	
	std::string_view getMediaNotation();
	void media(const std::string& content_append_media);
	void chat(const std::string& content_append_chat);
	
	std::string getActionLexicon();
	std::string getResultLexicon();
	
	void action(const std::string& content_append_action);
	void result(const std::string& content_append_result);
	void bygone(const std::string& content_of_bygone);
	void subtitle(const std::string& content_of_subtitle);
	void choice(const std::string& content_of_choice);
	void ask(const std::string& content_of_ask);
	void redact(); // Delete the most recent announcement
	void reject(); // Reject the most recent user query
};

// +++------>>> expedition.cppm <<<------+++

export struct OmniDirection {
	MultiDirection multidirection;
	void add(Direction direction);
	void clear();
	bool has(Direction direction);
	MultiDirection vector();
};

export struct Expedition
{
	Landmark landmark_of_beginning;
	Landmark landmark_of_destination;
	Direction chosen_direction;
	OmniDirection choice_of_direction;
	PlayerLocation municipality;
};

export inline std::string_view to_dialect(Direction direction);
export inline Direction from_dialect(const std::string& dialect);
export enum class Multiplicity {
	One,
	Many
};
export inline std::string_view to_bracket_notation(Multiplicity multiplicity);
export inline std::string dialect_synthesis(MultiDirection multidirection);
export inline std::string braket_notation_synthesis(MultiDirection multidirection);

export using MultiDirection = std::vector<Direction>;

export using PlayerLocation = std::unordered_map<PlayerIdentity, Landmark>;

// +++------>>> embark.cppm <<<------+++

export struct Embark : Rule {
	void execute(Overworld &world) override;
	void media_of_embark(Overworld &world);
};


export struct Choice_Of_Passage : Rule {
	void execute(Overworld &world) override;
	
	void query();
	void invalid();
	bool validate_choice(Direction chosen_direction);
	bool validate_dialect(const std::string& player_input);
	Direction get_player_choice();
};
export struct Travel : Rule {
	void execute(Overworld &world) override;
};
export struct Arrival : Rule {
	void execute(Overworld &world) override;
};
export struct Move_One_Space : Rule {
	void execute(Overworld &world) override;
};


} // namespace Parity