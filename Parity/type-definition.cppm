#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <memory>
#include <map>
#include <set>
#include <string>
#include <vector>

export namespace Parity {

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
	Landmark getLandmarkOfActivePlayer();
	Dialect encyclopedia;
	std::string appearanzonality(Landmark target_landmark);
	std::string appearancity(Landmark target_landmark);
	std::string pathochronality(Pathway target_pathway);
	
	// +++ fortuneboard +++
	DieRoll die_roll_for_fortune_board;
	int lucky_board_multiplier;
	int useLuckyBoardMultiplier();
	
	// +++ chromaticity +++
	DieRoll die_roll_for_chromaticity;
	ApparentColor getColorUnderActivePlayer();
	
	// +++  biology-physiology +++
	Treasury playerbase;
	Humanity humanity;
	PlayerIdentity active_player;
	int player_count;
	int maximum_player_count;
	std::string_view getActivePlayerName();
	void firstAdventurer();
	void nextAdventurer();
	
	// +++ opticular +++
	const MarketValuation marketplace;
	Inventory purchasement;
	
	// +++ rule-event +++
	int amount_of_new_event;
	void relocate_new_events_to_front();
	
	std::deque<std::unique_ptr<Rule>> event_queue;
	void main_loop();
	
	template <typename Extent_of_Rule, typename... Argument_of_Rule>
	void event(Argument_of_Rule&&... custom_arguments);
};

// +++------>>> announcement.cppm <<<------+++

export enum class MediaClause {
	Media,
	MediaBullet,
	MediaIndent,
	MediaCatalog,
	MediaOverhang
};

export enum class FormattingNotation {
	Plain,
	Bold,
	Italic,
	Underline,
	Strikethrough,
	Cyan,
};

export inline std::string_view to_notation(FormattingNotation notation);
export inline std::string format_with_notation(FormattingNotation notation, const std::string& content);
export inline std::string bold(const std::string content);
export inline std::string italic(const std::string content);
export inline std::string underline(const std::string content);
export inline std::string strikethrough(const std::string content);
export inline std::string cyan(const std::string content);
export inline std::string italic_cyan(const std::string content);
export inline std::string bold_cyan(const std::string content);
export inline std::string bold_italic_cyan(const std::string content);

export class Announcement {
public:
	MediaClause clause;
	int consequential_ordinal;
	int choice_ordinal;
	int analog_ordinal;
	
	std::string_view getMediaNotation();
	void media(const std::string& content_append_media);
	void chat(const std::string& content_append_chat);
	
	std::string getActionLexicon();
	std::string getResultLexicon();
	std::string getChoiceLexicon();
	std::string getForbidLexicon();
	std::string getAnalogLexicon();
	std::string getRangeLexicon(int reach);
	
	void action(const std::string& content_append_action);
	void result(const std::string& content_append_result);
	void bygone(const std::string& content_of_bygone);
	void subtitle(const std::string& content_of_subtitle);
	void caption(const std::string& content_of_caption);
	void linger(const std::string& content_of_linger);
	
	void linebreak();
	void horizon(const std::string& content_of_horizon);
	
	void choice(const std::string& content_of_choice);
	void forbid(const std::string& content_of_forbid);
	void range(const std::string& content_of_range, int reach);
	void catalog(const std::string& content_of_catalog);
	void overhang(const std::string& content_of_overhang);
	void analog(const std::string& content_of_analog);
	void analogical(const std::string& content_of_analogical);
	void beginChoice();
	void beginAnalog();
	
	
	void ask(const std::string& content_of_ask);
	void redact(); // Delete the most recent announcement
	void reject(); // Reject the most recent user query
	std::string listen(); // Listen for user input
};








// ##××××-------->>> ./Opticular <<<--------××××##
//
//
//
//

// +++------>>> optoelectronic.cppm <<<------+++


export enum class OpticalEffect {
	Advantage,
	Weakness,
	Repulsion,
	Chromatic,
	Collimation
};

export enum class Optics {
	RadioWaves,
	MicroWaves,
	InfraredWaves,
	LightWaves,
	UltravioletWaves,
	XRays,
	GammaRays
};

export using Iridescent = std::set<OpticalEffect>;
export using Inventory = std::multiset<Optics>;
export using MarketValuation = std::map<Optics, int>;
export MarketValuation Marketplace;

// +++------>>> opticalnotation.cppm <<<------+++


export inline std::string_view to_string(Optics optical_item);
export inline std::string_view to_description(Optics optical_item);
enum class ApparentColor; // forward declaration for some reason
export using Chromaticon = std::map<ApparentColor, std::string_view>;
export inline const Chromaticon LightWaveExtensionDescriptions;
export inline std::string_view to_light_wave_description(ApparentColor gradient_color);
export inline std::multiset<int> transcribe_numerical_dialect(std::string &numerical_dialect);

// +++------>>> marketplace.cppm <<<------+++

export struct Open_Shop : Rule {
	void execute(Overworld &world) override;
};
export struct Apply_Purchasement_Of_Optics : Rule {
	void execute(Overworld &world) override;
};
export struct Apply_Purchasement_Result : Rule {
	void execute(Overworld &world) override;
};
export struct Decline_Shop : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> marketmedia.cppm <<<------+++

export struct Media_Of_Marketplace : Rule {
	void execute(Overworld &world) override;
	void display_market();
	void display_player_possesion_hint();
};

export struct Review_Of_Purchase : Rule {
	void execute(Overworld &world) override;
	void display_purchasement();
	void display_inventory();
};

// +++------>>> purchasement.cppm <<<------+++

export struct Purchasement_Of_Optics : Rule {
	void execute(Overworld &world) override;
	void fill_valid_numeral();
	Optics getOpticsFromNumber(int number);
	
	void query();
	
	bool validate_dialect(std::string &player_input);
	void apply_dialect(std::string &player_input);
	
	bool validate_numerical_dialect();
	void apply_numerical_dialect();
	
	bool validate_choice();
	
	void clause_decline_shop();
	void clause_invalid();
	
	void end_concentration();
	void concentrate();
};

// +++------>>> chromaticity.cppm <<<------+++

export struct Activate_Color_Effect : Rule {
	void execute(Overworld &world) override;
	
	ApparentColor getColorUnderActivePlayer(Overworld &world);
};

export struct Pink_Color_Effect : Rule {
	void execute(Overworld &world) override;
};
export struct Green_Color_Effect : Rule {
	void execute(Overworld &world) override;
};
export struct Orange_Color_Effect : Rule {
	void execute(Overworld &world) override;
};
export struct Yellow_Color_Effect : Rule {
	void execute(Overworld &world) override;
};
export struct Red_Color_Effect : Rule {
	void execute(Overworld &world) override;
};
export struct Purple_Color_Effect : Rule {
	void execute(Overworld &world) override;
};
export struct Roll_For_Chromaticity : Rule {
	void execute(Overworld &world) override;
};
export struct Media_Of_Pink_Orange_Yellow_Gradient : Rule {
	void execute(Overworld &world) override;
	static constexpr int reach = 2; // Each outcome corresponds to 2 die results (e.g., 1-2, 3-4, 5-6)
	static inline const std::vector<std::string> outcomes;
};
export struct Apply_Pink_Orange_Yellow_Gradient_Result : Rule {
	void execute(Overworld &world) override;
};
export struct Pink_Orange_Yellow_Gradient_Effect : Rule {
	void execute(Overworld &world) override;
};
export struct Apply_Red_Purple_Gradient_Result : Rule {
	void execute(Overworld &world) override;
};
export struct Red_Purple_Gradient_Effect : Rule {
	void execute(Overworld &world) override;
};

export inline std::string activation_synthesis(ApparentColor color);

// ##××××-------->>> ./Divinity <<<--------××××##
//
//
//
//

// +++------>>> biology.cppm <<<------+++

export enum class PlayerIdentity {
	AmethystApprentice,
	SapphireSummoner,
	EmeraldEnchantress,
	OpalinOracle
};

export struct PlayerPosession {
	int gold_coin;
	int permanent_power_point;
	int vitality_heart;
	int vitality_maximum_heart;
	Iridescent active_optical_effect;
	Inventory inventory;
	int inventory_capacity;
};

export using Treasury = std::map<PlayerIdentity, PlayerPosession>;
export using Humanity = std::set<PlayerIdentity>;

// +++------>>> physiology.cppm <<<------+++

export inline std::string_view to_string(PlayerIdentity identity);
export struct Welcome_Adventurer : Rule {
	int amount_of_adventurer;
	
	Welcome_Adventurer(int amount);
	void execute(Overworld &world) override;
};

export struct Respawn : Rule {
	void execute(Overworld &world) override {
	}
};

export struct Vitality_Death : Rule {
	void execute(Overworld &world) override {
	}
};

export struct Vitality_Hurt : Rule {
	int amount_of_damage;
	
	Vitality_Hurt(int damage) : amount_of_damage(damage) {}
	void execute(Overworld &world) override;
};
export struct Vitality_Heal : Rule {
	int amount_of_healing;
	
	Vitality_Heal(int healing) : amount_of_healing(healing) {}
	void execute(Overworld &world) override {
	}
};
export struct Gain_Gold_Coin : Rule
{
	int amount_of_gold_coin;
	Gain_Gold_Coin(int amount) : amount_of_gold_coin(amount) {}
	void execute(Overworld &world) override;
};
export struct Gain_Permanent_Power_Point : Rule {
	int amount_of_permanent_power;
	Gain_Permanent_Power_Point(int amount);
	void execute(Overworld &world) override;
};
export struct Take_Gold_Coin : Rule
{
	int amount_of_gold;
	
	Take_Gold_Coin(int amount) : amount_of_gold(amount) {}
	void execute(Overworld &world) override;
};

export struct Gain_Optical_Item : Rule
{
	Optics optical_item;
	int quantity;
	
	Gain_Optical_Item(Optics item, int quantity);
	void execute(Overworld &world) override;
};

// +++------>>> adventurer.cppm <<<------+++

export template <typename Element_Of_Set>
	inline Element_Of_Set getNextElement(const std::set<Element_Of_Set>& target_set, Element_Of_Set current_element);

// string repetition for emdash because emdash is a multicharacter string in UTF-8
export inline std::string repetition(const std::string& target_string, int amount_of_repetition);
export inline std::string get_ornament_notation(int amount_of_emdash);

export struct Media_Of_Adventurer : Rule {
	void execute(Overworld &world) override;
};
export struct Media_Of_Adventurer_Separator : Rule {
	void execute(Overworld &world) override;
};
export struct First_Adventurer_Turn : Rule {
	void execute(Overworld &world) override;
};
export struct Next_Adventurer_Turn : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> necrology.cppm <<<------+++


export enum class DemonForm {
	ElectricMinion,
	MagneticDemon,
	MagneticMageDemon,
	ElectromagneticDemonBoss
};

export inline std::string_view to_string(DemonForm demon_form);

export using DemonSeriality = int;
export using DemonPossession = std::map<DemonSeriality, DemonForm>;
export using Demonity = std::set<DemonSeriality>;

// +++------>>> forgather.cppm <<<------+++

export struct Forgather_of_Adventurer : Rule {
	
	Overworld *terra;
	int player_choice;
	
	void execute(Overworld &world) override;
	
	void query();
	bool validate_choice(int choice);
	bool validate_dialect(std::string &player_input);
	void get_player_choice();
};












// ###××××-------->>> ./Cartography <<<--------××××##
//
//
//
//
//

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

export Geography Atlas;

export inline bool is_arrow_path(const Path& path);
export inline bool is_restricted_path(const Path& path);
export inline bool is_gradient_color(const ApparentColor& color);

// +++------>>> notation.cppm <<<------+++

export inline std::string_view to_string(Landmark landmark);
export inline std::string_view to_string(Region region);
export inline std::string_view to_string(Zone zone);
export inline std::string_view to_string(ApparentColor color);
export inline std::string_view to_string(ApparentGeometry geometry);
export inline std::string_view to_string(Direction direction);
export inline std::string_view to_string(Path path);

export inline std::string_view to_braket_notation(ApparentGeometry geometry);
export inline std::string_view to_space_notation(ApparentGeometry geometry);
export inline std::string_view to_zone_notation(Zone zone);
export inline std::string chromaticon(ApparentQuality quality, ApparentColor color);
export inline std::string appearancy(ApparentQuality quality, ApparentColor color, ApparentGeometry geometry);
export inline std::string zonoity(Zone zone, std::string content_prepend_zone);
export inline std::string chronoity(Path path, std::string content_prepend_warp);
export inline std::string archeometrinoity(ApparentGeometry geometry, std::string content_inside_braket);

export void print_all_landmark_notations();

export inline std::string dialect_synthesis(MultiDirection multidirection);








// +++------>>> expedition.cppm <<<------+++

export using PlayerLocation = std::map<PlayerIdentity, Landmark>;
export using PlayerLocator = std::map<Landmark, Humanity>;

export struct Municipality {
	PlayerLocation player_location;
	PlayerLocator player_locator;
	
	void teleport(PlayerIdentity target_player, Landmark landmark_of_destination);
	
	Landmark getLandmarkOf(PlayerIdentity player) const;
	Humanity getHumanityAt(Landmark landmark) const;
	void addPlayer(PlayerIdentity player, Landmark landmark);
};

export struct OmniDirection {
	MultiDirection multidirection;
	void add(Direction direction);
	void clear();
	bool has(Direction direction);
	MultiDirection vector();
};

export using DemonLocation = std::map<DemonSeriality, Landmark>;
export using DemonLocator = std::map<Landmark, Demonity>;

export struct AntiDivinity {
	DemonLocation demon_location;
	DemonLocator demon_locator;
	
	void teleport(DemonSeriality target_demon, Landmark landmark_of_destination);
	
	Landmark getLandmarkOf(DemonSeriality demon) const;
	Demonity getDemonityAt(Landmark landmark) const;
	
	void addDemon(DemonSeriality demon, Landmark landmark);
	void removeDemon(DemonSeriality demon);
};

export struct Expedition
{
	Landmark landmark_of_beginning;
	Landmark landmark_of_destination;
	Direction chosen_direction;
	std::string player_choice_dialect;
	OmniDirection choice_of_direction;
	bool is_journey_optional;
	bool is_journey_declined;
	Municipality municipality;
	AntiDivinity antidivinity;
};




// +++------>>> encyclopedia.cppm <<<------+++

export struct Dialect {
	std::string_view above;
	std::string_view below;
	std::string_view left;
	std::string_view right;
	std::string_view above_left;
	std::string_view above_right;
	std::string_view below_left;
	std::string_view below_right;
	std::string_view decline_journey;
	std::string_view decline_shop;
};

export constexpr Dialect Encyclopedia;

export inline std::string_view to_dialect(Direction direction);
export inline Direction from_dialect(const std::string& dialect);
export enum class Multiplicity {
	One,
	Many
};
export inline std::string_view to_bracket_notation(Multiplicity multiplicity);
export inline std::string bag_notation_synthesis(std::string &content_inside_bag);
export inline std::string archangel_notation_synthesis(std::string &content_inside_archangel);

// +++------>>> accoutrement.cppm <<<------+++

export struct Query_Of_Passage : Rule {
	void execute(Overworld &world) override {
	}
};
export struct Media_Of_Embark : Rule {
	void execute(Overworld &world) override;
};
export struct Media_Of_Passage : Rule {
	void execute(Overworld &world) override;
};
export struct Media_Of_Journey : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> embark.cppm <<<------+++

export struct Embark : Rule {
	void execute(Overworld &world) override;
};


export struct Choice_Of_Passage : Rule {
	void execute(Overworld &world) override;
};

export struct Travel : Rule {
	void execute(Overworld &world) override;
};
export struct Arrival : Rule {
	void execute(Overworld &world) override;
};

export struct Decline_Journey : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> passagedecision.cppm <<<------+++

export struct Listen_Passage_Dialect : Rule {
	void execute(Overworld &world) override {
	}
};

export struct Resolve_Passage_Dialect : Rule {
	void execute(Overworld &world) override {
	}
};

export struct Apply_Passage_Dialect : Rule {
	
	Overworld *terra = nullptr;
	void execute(Overworld &world) override;
	bool validate_choice(Direction chosen_direction);
	bool validate_dialect(const std::string& player_input);
};

export struct Decision_Of_Passage : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> journey.cppm <<<------+++

export struct Move_One_Space : Rule {
	void execute(Overworld &world) override;
};

export struct Move_One_Space_Optional : Rule {
	int amount_of_optional_move;
	Move_One_Space_Optional(int amount);
	void execute(Overworld &world) override;
};

export struct Apply_Optional_Journey : Rule {
	int amount_of_optional_move;
	Apply_Optional_Journey(int amount);
	void execute(Overworld &world) override;
};





// ##××××-------->>> ./Fortuneboard <<<--------××××##
//
//
//
//

// +++------>>> dieroll.cppm <<<------+++

export enum class DieRoll : int
{
	One = 1,
	Two,
	Three,
	Four,
	Five,
	Six
};

// +++------>>> fortuneboard.cppm <<<------+++

export struct Roll_For_Random_Board : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> luckyboard.cppm <<<------+++

export struct Media_Of_Lucky_Board : Rule {
	void execute(Overworld &world) override;
	static inline const std::vector<std::string> outcomes;
};

export struct Move_Again_One_Space : Rule {
	void execute(Overworld &world) override;
};

export struct Apply_Lucky_Board_Result : Rule {
	void execute(Overworld &world) override;
	void applyLuckyBoardResult(Overworld &world, DieRoll roll);
};

export struct Lucky_Board : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> eventboard.cppm <<<------+++

export struct All_Players_Gain_Gold_Coin : Rule {
	int amount_of_gold_coin;
	All_Players_Gain_Gold_Coin(int amount);
	void execute(Overworld &world) override;
};

export struct Media_Of_Event_Board : Rule {
	void execute(Overworld &world) override;
	static inline const std::vector<std::string> outcomes;
};

export struct Apply_Event_Board_Result : Rule {
	void execute(Overworld &world) override;
	void applyEventBoardResult(Overworld &world, DieRoll roll);
};

export struct Event_Board : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> unluckyboard.cppm <<<------+++

export struct Media_Of_Unlucky_Board : Rule {
	void execute(Overworld &world) override;
	static inline const std::vector<std::string> outcomes;
};

export struct Apply_Unlucky_Board_Result : Rule {
	void execute(Overworld &world) override;
	void applyUnluckyBoardResult(Overworld &world, DieRoll roll);
};

export struct Unlucky_Board : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> demonboard.cppm <<<------+++

export struct Media_Of_Demon_Board : Rule {
	void execute(Overworld &world) override;
	static inline const std::vector<std::string> outcomes;
};

export struct Apply_Demon_Board_Result : Rule {
	void execute(Overworld &world) override;
	void applyDemonBoardResult(Overworld &world, DieRoll roll);
};

export struct Demon_Board : Rule
{
	void execute(Overworld &world) override;
};



} // namespace Parity