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
	std::string pathochronality(Direction target_direction);
	DieRoll die_roll_for_entropy;
	
	// +++ fortuneboard +++
	DieRoll die_roll_for_fortune_board;
	int lucky_board_multiplier;
	int useLuckyBoardMultiplier();
	
		// +++ oracle +++
	Certainty certainty = {};
	DieRoll fatesAndCertainty();
	
	// +++ chromaticity +++
	DieRoll die_roll_for_chromaticity;
	ApparentColor getColorUnderActivePlayer();
	
	// +++  biology-physiology +++
	Treasury playerbase;
	Humanity humanity;
	PlayerIdentity active_player;
	PlayerIdentity turn_of_adventurer;
	int player_count;
	int maximum_player_count;
	std::string_view getActivePlayerName();
	void firstAdventurer();
	void nextAdventurer();
	
	// +++ necrology +++
	DemonSeriality active_demon_seriality;
	DemonForm getActiveDemonForm();
	Landmark getLandmarkOfActiveDemon();
	
	// +++ warfare-battlefield +++
	Battlefield battlefield;
	
	// +++ opticular +++
	const MarketValuation marketplace;
	Inventory purchasement;
	Inventory consumption;
	Inventory potential_consumption;
	
	// +++ prismarine +++
	ApparentColor chosen_prismarine;
	PolyChromaticity potential_prismarine;
	
	// +++ traverser +++
	int calendar_of_sunrise;
	CelestialClause clause_of_adventure;
	
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

export inline std::string bold_acute(const std::string content);

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
	int suspense_level;
	
	std::string_view getMediaNotation();
	void media(const std::string& content_append_media);
	void chat(const std::string& content_append_chat);
	
	std::string getActionLexicon();
	std::string getResultLexicon();
	std::string getChoiceLexicon();
	std::string getForbidLexicon();
	std::string getAnalogLexicon();
	std::string getRangeLexicon(int reach);
	
	void beginConsequential();
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
	void suspense(); // Wait for user to press enter
	void suspense(int quiet_at_level); // only if world.annouce.suspense_level < quiet_above_level
};








// ##××××-------->>> ./Opticular <<<--------××××##
//
//
//
//

// +++------>>> optoelectronic.cppm <<<------+++


export enum class OpticalEffect {
	Advantage,
	Ascendancy,
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
export inline std::string_view to_string(OpticalEffect optical_effect);
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

export struct Open_Delivery : Rule {
	void execute(Overworld &world) override;
};

export struct Open_Inventory : Rule {
	void execute(Overworld &world) override;
};

export struct Apply_Consumption_Of_Optics : Rule {
	void execute(Overworld &world) override;
};

export struct Apply_Consumption_Result : Rule {
	Overworld *terra = nullptr;
	
	void execute(Overworld &world) override;
	void apply_optical_item(Optics item);
};

export struct Decline_Consumption : Rule {
	void execute(Overworld &world) override;
};

	// +++------>>> marketmedia.cppm <<<------+++

export struct Media_Of_Marketplace : Rule {
	Overworld *terra = nullptr;
	void execute(Overworld &world) override;
	void display_market();
	void display_player_possesion_hint();
};

export struct Review_Of_Purchase : Rule {
	Overworld *terra = nullptr;
	void execute(Overworld &world) override;
	void display_purchasement();
	void display_inventory();
};

export struct Media_Of_Consumption : Rule {
	Overworld *terra = nullptr;
	void execute(Overworld &world) override;
	void display_consumption();
};

export struct Review_Of_Consumption : Rule {
	Overworld *terra = nullptr;
	void execute(Overworld &world) override;
	void display_item_consumption(Optics item);
	void display_fortune_consumption();
	void display_combat_consumption();
	void display_repulsion_consumption();
	void display_culinary_consumption();
	void display_chromatic_consumption();
};

export struct Media_Of_Delivery : Rule {
	Overworld *terra = nullptr;
	void execute(Overworld &world) override;
	void display_market();
	void display_player_possesion_hint();
};

// +++------>>> purchasement.cppm <<<------+++

export struct Purchasement_Of_Optics : Rule {
	Overworld *terra = nullptr;
	
	Inventory purchasement;
	std::multiset<int> transcribed_numerical_dialect; 
	std::set<int> valid_numeral;
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


// +++------>>> order.cppm <<<------+++


export struct Order_Of_Optics : Rule {
	Overworld *terra = nullptr;
	
	Inventory purchasement;
	int transcribed_numerical_dialect; 
	std::set<int> valid_numeral;
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

// +++------>>> consumption.cppm <<<------+++

export struct Consumption_Of_Optics : Rule {
	Overworld *terra = nullptr;
	
	Inventory consumption;
	std::multiset<int> transcribed_numerical_dialect; 
	std::set<int> valid_numeral;
	void execute(Overworld &world) override;
	void fill_valid_numeral();
	Optics getOpticsFromNumber(int number);
	
	void query();
	
	bool validate_dialect(std::string &player_input);
	void apply_dialect(std::string &player_input);
	
	bool validate_numerical_dialect();
	void apply_numerical_dialect();
	
	void clause_decline_consumption();
	void clause_invalid();
	
	void end_concentration();
	void concentrate();
};

// +++------>>> optometrist.cppm <<<------+++

export struct Excellece_Of_Consumption : Rule {
	void execute(Overworld &world) override;
};

export struct Potential_Of_Combat_Consumption : Rule {
	void execute(Overworld &world) override;
};

export struct Potential_Of_Repulsion_Consumption : Rule {
	void execute(Overworld &world) override;
};

export struct Potential_Of_Culinary_Consumption : Rule {
	void execute(Overworld &world) override;
};

export struct Potential_Of_Chromatic_Consumption : Rule {
	void execute(Overworld &world) override;
};

export struct Potential_Of_Fortune_Consumption : Rule {
	void execute(Overworld &world) override;
};

export struct Consumption_Of_RadioWaves : Rule {
	void execute(Overworld &world) override;
};

export struct Consumption_Of_MicroWaves : Rule {
	void execute(Overworld &world) override;
};

export struct Consumption_Of_InfraredWaves : Rule {
	void execute(Overworld &world) override;
};

export struct Consumption_Of_LightWaves : Rule {
	void execute(Overworld &world) override;
};

export struct Consumption_Of_UltravioletWaves : Rule {
	void execute(Overworld &world) override;
};

export struct Consumption_Of_XRays : Rule {
	void execute(Overworld &world) override;
};

export struct Consumption_Of_GammaRays : Rule {
	void execute(Overworld &world) override;
};

export struct Power_Of_Repulsion : Rule {
	Landmark target_landmark;
	Power_Of_Repulsion(Landmark target_landmark) : target_landmark(target_landmark) {}
	void execute(Overworld &world) override;
};




// +++------>>> chromaticity.cppm <<<------+++

export struct Omen_Of_Chromaticity : Rule {
	void execute(Overworld &world) override;
};

export struct Apply_Omen_Of_Chromaticity : Rule {
	void execute(Overworld &world) override;
};

// +++----->>> prismarine.cppm <<<------+++

export struct Open_Prismarine : Rule {
	void execute(Overworld &world) override;
};

export struct Media_Of_Prismatism : Rule {
	void execute(Overworld &world) override;
};

export struct Apply_Prismatism : Rule {
	void execute(Overworld &world) override;
};

export struct Coalescence_Of_Prismatism : Rule {
	void execute(Overworld &world) override;
};

// +++----->>> glazier.cppm <<<------+++


export struct Glazier_Of_Chromaticity : Rule {
	Overworld *terra = nullptr;
	
	ApparentColor chosen_color;
	int transcribed_numerical_dialect; 
	std::set<int> valid_numeral;
	void execute(Overworld &world) override;
	void fill_valid_numeral();
	ApparentColor getColorFromNumber(int number);
	
	void query();
	
	bool validate_dialect(std::string &player_input);
	void apply_dialect(std::string &player_input);
	
	bool validate_numerical_dialect();
	void apply_numerical_dialect();
	
	bool validate_choice();
	
	void clause_invalid();
	
	void end_concentration();
	void concentrate();
};

// +++----->>> coloreffect.cppm <<<------+++

export struct Activate_Color_Effect : Rule {
	void execute(Overworld &world) override;
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
};
export struct Apply_Pink_Orange_Yellow_Gradient_Result : Rule {
	void execute(Overworld &world) override;
	static constexpr int reach = 2; // Each outcome corresponds to 2 die results (e.g., 1-2, 3-4, 5-6)
	static inline const std::vector<ApparentColor> outcomes;
};
export struct Pink_Orange_Yellow_Gradient_Effect : Rule {
	void execute(Overworld &world) override;
};
export struct Media_Of_Red_Purple_Gradient : Rule {
	void execute(Overworld &world) override;
};
export struct Apply_Red_Purple_Gradient_Result : Rule {
	void execute(Overworld &world) override;
	static constexpr int reach = 3; // Each outcome corresponds to 2 die results (e.g., 1-2, 3-4, 5-6)
	static inline const std::vector<ApparentColor> outcomes;
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
export inline std::string_view to_string(PlayerIdentity identity);

// +++------>>> physiology.cppm <<<------+++

export struct Execute_As : Rule {
	PlayerIdentity executor;
	Execute_As(PlayerIdentity executor_identity) : executor(executor_identity) {}
	void execute(Overworld &world) override;
};

export struct Relinquish_Execution : Rule {
	void execute(Overworld &world) override;
};

export struct Respawn : Rule {
	void execute(Overworld &world) override;
};

export struct Vitality_Death : Rule {
	void execute(Overworld &world) override;
};

export struct Vitality_Hurt : Rule {
	int amount_of_damage;
	
	Vitality_Hurt(int damage) : amount_of_damage(damage) {}
	void execute(Overworld &world) override;
};
export struct Vitality_Hurt_Humanity : Rule {
	int amount_of_damage;
	
	Vitality_Hurt_Humanity(int damage) : amount_of_damage(damage) {}
	void execute(Overworld &world) override;
};
export struct Vitality_Hurt_Humanity_In_Demon_Zone : Rule {
	int amount_of_damage;
	
	Vitality_Hurt_Humanity_In_Demon_Zone(int damage) : amount_of_damage(damage) {}
	void execute(Overworld &world) override;
};
export struct Vitality_Heal : Rule {
	int amount_of_healing;
	
	Vitality_Heal(int healing) : amount_of_healing(healing) {}
	void execute(Overworld &world) override;
};
export struct Gain_Gold_Coin : Rule
{
	int amount_of_gold_coin;
	Gain_Gold_Coin(int amount) : amount_of_gold_coin(amount) {}
	void execute(Overworld &world) override;
};

export struct All_Players_Gain_Gold_Coin : Rule {
	int amount_of_gold_coin;
	All_Players_Gain_Gold_Coin(int amount) : amount_of_gold_coin(amount) {}
	void execute(Overworld &world) override;
};

export struct Gain_Permanent_Power_Point : Rule {
	int amount_of_permanent_power;
	Gain_Permanent_Power_Point(int amount) : amount_of_permanent_power(amount) {}
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
	
	Gain_Optical_Item(Optics item, int quantity) : optical_item(item), quantity(quantity) {}
	void execute(Overworld &world) override;
};

export struct Take_Optical_Item : Rule
{
	Optics optical_item;
	int quantity;
	
	Take_Optical_Item(Optics item, int quantity) : optical_item(item), quantity(quantity) {}
	void execute(Overworld &world) override;
};


export struct Take_All_Optical_Effects : Rule
{
	void execute(Overworld &world) override;
};


// helper function to remove a specific quantity of an optical item from inventory
export inline void remove_optical_item_from_inventory(PlayerPosession &possession, Optics item, int quantity);

export struct Gain_Optical_Effect : Rule
{
	OpticalEffect optical_effect;
	Gain_Optical_Effect(OpticalEffect effect) : optical_effect(effect) {}
	void execute(Overworld &world) override;
};

export struct Take_Optical_Effect : Rule
{
	OpticalEffect optical_effect;
	Take_Optical_Effect(OpticalEffect effect) : optical_effect(effect) {}
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
export using DemonManifest = std::map<DemonSeriality, DemonForm>;
export using Demonity = std::set<DemonSeriality>;

export using DemonMalignity = std::map<DemonForm, int>; // Attack Power

export DemonMalignity MalignityOfDemonForm;

// +++------>>> necromancy.cppm <<<------+++


export struct Summon_Demon : Rule {
	DemonForm demonform;
	Landmark landmark_of_summoning;
	
	Summon_Demon(DemonForm demonform, Landmark landmark_of_summoning);
	void execute(Overworld &world) override;
};

export struct Execute_As_Demon : Rule {
	DemonSeriality demon_seriality;
	Execute_As_Demon(DemonSeriality demon_seriality) : demon_seriality(demon_seriality) {}
	void execute(Overworld &world) override;
};






// ##××××-------->>> ./Adventure <<<--------××××##
//
//
//
//
//

// +++------>>> celestial.cppm <<<------+++

export enum class CelestialClause {
	VoidOfForgather,
	Sunrise,
	Dayspring,
	RestingPlace,
	SleepingPlace,
	Sunset,
	Twilight,
	Moonfall,
	Starlight
};


// string repetition for emdash because emdash is a multicharacter string in UTF-8
export inline std::string repetition(const std::string& target_string, int amount_of_repetition);
export inline std::string get_ornament_notation(int amount_of_emdash);
// +++------>>> adventurer.cppm <<<------+++

export struct Welcome_Adventurer : Rule {
	int amount_of_adventurer;
	
	Welcome_Adventurer(int amount = 0) : amount_of_adventurer(amount) {}
	void execute(Overworld &world) override;
};

export template <typename Element_Of_Set>
	inline Element_Of_Set getNextElement(const std::set<Element_Of_Set>& target_set, Element_Of_Set current_element);


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

// +--->>> traverser.cppm <<<---+++

export struct Omen_Of_Corruption : Rule {
	void execute(Overworld &world) override;
};

export struct Apply_Omen_Of_Corruption : Rule {
	void execute(Overworld &world) override;
};

export struct Rule_Of_Adventure : Rule {
	void execute(Overworld &world) override;
};

export struct Celestial_Clause_Forgather : Rule {
	void execute(Overworld &world) override;
};

export struct Celestial_Clause_Sunrise : Rule {
	void execute(Overworld &world) override;
};

export struct Celestial_Clause_Dayspring : Rule {
	void execute(Overworld &world) override;
};

export struct Celestial_Clause_RestingPlace : Rule {
	void execute(Overworld &world) override;
};

export struct Celestial_Clause_SleepingPlace : Rule {
	void execute(Overworld &world) override;
};

export struct Celestial_Clause_Sunset : Rule {
	void execute(Overworld &world) override;
};

export struct Celestial_Clause_Twilight : Rule {
	void execute(Overworld &world) override;
};

export struct Celestial_Clause_Moonfall : Rule {
	void execute(Overworld &world) override;
};

export struct Celestial_Clause_Starlight : Rule {
	void execute(Overworld &world) override;
};

// media of celestial clauses

export struct Media_Of_Sunrise : Rule {
	void execute(Overworld &world) override;
};

export struct Media_Of_Sunset : Rule {
	void execute(Overworld &world) override;
};

export struct Branch_Of_SleepingPlace : Rule {
	void execute(Overworld &world) override;
};

export struct End_Of_Parity : Rule {
	void execute(Overworld &world) override;
};





// ##××××-------->>> ./Warfare <<<--------××××##
//
//
//
//

// +++------>>> battlefield.cppm <<<------+++

export enum class BattleResult {
	PlayerWins,
	PlayerLoses,
	Draw
};

export struct Battlefield {
	DieRoll die_roll_for_combat_strength;
	DieRoll die_roll_for_attacker;
	DieRoll die_roll_for_defender;
	DieRoll advantage_die_roll_for_attacker;
	DieRoll advantage_die_roll_for_defender;
	
	PlayerIdentity combatant_player;
	DemonForm combatant_demon;
	
	bool advantage_of_player;
	bool advantage_of_demon;
	bool collimation_of_player;
	bool weakness_of_demon;
	
	int attack_power_modification_of_attacker;
	int attack_power_modification_of_defender;
	
	
	int attack_power_of_attacker;
	int attack_power_of_defender;
	int combat_strength_of_attacker;
	int combat_strength_of_defender;
	int attack_value_of_attacker;
	int attack_value_of_defender;
	
	BattleResult battle_result;
	
	DemonMalignity malignity = MalignityOfDemonForm;
};

// +++------>>> armament.cppm <<<------+++
// +++------>>> combat.cppm <<<------+++
// +++------>>> simulation.cppm <<<------+++
// +++------>>> warfare.cppm <<<------+++

export struct Discord_Of_Beligerence : Rule {
	void execute(Overworld &world) override;
};
export struct Warfare_Iridescence : Rule {
	void execute(Overworld &world) override;
};
export struct Media_Of_Warfare_Iridescence : Rule {
	void execute(Overworld &world) override;
};
export struct Read_Attack_Power : Rule {
	void execute(Overworld &world) override;
};
export struct Media_Of_Attack_Power : Rule {
	void execute(Overworld &world) override;
	std::string power_of_synthesis(int attack_power, int attack_power_modification);
	std::string modification_synthesis(int attack_power_modification);
};

export struct Roll_For_Combat_Strength : Rule {
	void execute(Overworld &world) override;
};
export struct Read_Combat_Strength : Rule {
	std::string clause;
	Read_Combat_Strength(const std::string& clause);
	void execute(Overworld &world) override;
};
export struct Apply_Combat_Strength_Result : Rule {
	void execute(Overworld &world) override;
};
export struct Fate_Of_Combat_Strength : Rule {
	void execute(Overworld &world) override;
};
export struct Media_Of_Combat_Strength : Rule {
	void execute(Overworld &world) override;
	std::string discard_of_synthesis(DieRoll normal_die_roll, DieRoll advantage_die_roll);
	std::string strength_of_synthesis(int combat_strength);
	std::string dice_synthesis(int roll_number);
};

export struct Compute_Attack_Value : Rule {
	void execute(Overworld &world) override;
};
export struct Media_Of_Attack_Value : Rule {
	void execute(Overworld &world) override;
	std::string attack_value_synthesis(int attack_value, int opponent_attack_value);
};


export struct Preparation_Of_Combat : Rule {
	void execute(Overworld &world) override;
};

export struct Combat_Of_Fates : Rule {
	void execute(Overworld &world) override;
};
export struct Combat_Clause_Draw : Rule {
	void execute(Overworld &world) override;
};
export struct Combat_Clause_Player_Wins : Rule {
	void execute(Overworld &world) override;
};
export struct Combat_Clause_Player_Loses : Rule {
	void execute(Overworld &world) override;
};
export struct Resolution_Of_Combat : Rule {
	void execute(Overworld &world) override;
};
export struct Apply_Combat_Result : Rule {
	void execute(Overworld &world) override;
};

export struct Commencement_Of_Warfare : Rule {
	void execute(Overworld &world) override;
};

export struct Potential_Of_Warfare : Rule {
	Landmark target_landmark;
	Potential_Of_Warfare(Landmark target_landmark) : target_landmark(target_landmark) {}
	void execute(Overworld &world) override;
};

export struct Potential_Of_Warfare_At_Active_Player : Rule {
	void execute(Overworld &world) override;
};

export struct Potential_Of_Warfare_At_Active_Demon : Rule {
	void execute(Overworld &world) override;
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
export using PolyChromaticity = std::set<ApparentColor>;

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
export inline bool is_demon_zone(const Zone& zone);
export inline bool is_safe_zone(const Zone& zone);

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
	DemonManifest demon_manifest;
	int next_demon_seriality;
	
	void teleport(DemonSeriality target_demon, Landmark landmark_of_destination);
	
	Landmark getLandmarkOf(DemonSeriality demon);
	Demonity getDemonityAt(Landmark landmark);
	
	void addDemon(DemonForm demon_form, Landmark landmark);
	void removeDemon(DemonSeriality demon);
	Demonity getAllLesserDemons() const;
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
	int amount_of_conquest_remaining = 0;
	int amount_of_conquest = 0;
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
	std::string_view decline_consumption;
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

//
// +++------>>> accoutrement.cppm <<<------+++

export struct Query_Of_Passage : Rule {
	void execute(Overworld &world) override;
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

export struct Restricted_Choice_Of_Passage : Rule {
	void execute(Overworld &world) override;
};

export struct Every_Choice_Of_Passage : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> entropy.cppm <<<------+++

export struct Roll_For_Entropy : Rule {
	void execute(Overworld &world) override;
};

export struct Entropy_Of_Adventurer : Rule {
	void execute(Overworld &world) override;
};

export struct Entropy_Of_Corruption : Rule {
	void execute(Overworld &world) override;
};

export struct Apply_Fate_Of_Corruption : Rule {
	void execute(Overworld &world) override;
};

export struct Entropy_Of_Repulsion : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> accoutrement.cppm <<<------+++

export struct Media_Of_Conquest : Rule {
	void execute(Overworld &world) override;
};

export struct Media_Of_Perpetrate : Rule {
	void execute(Overworld &world) override;
};

export struct Media_Of_Conquest_Success : Rule {
	void execute(Overworld &world) override;
};

export struct Media_Of_Conquest_Failure : Rule {
	void execute(Overworld &world) override;
};

// +++------>>> peril.cppm <<<------+++

export struct Knockback : Rule {
	void execute(Overworld &world) override;
};

export struct Knockback_Adventurer : Rule {
	void execute(Overworld &world) override;
};

export struct Repulse : Rule {
	void execute(Overworld &world) override;
};

export struct Repulse_Demon : Rule {
	void execute(Overworld &world) override;
};

export struct Perpetrate : Rule {
	void execute(Overworld &world) override;
};

export struct Step_Of_Conquest : Rule {
	void execute(Overworld &world) override;
};

export struct Forfence_Of_Cattail : Rule {
	void execute(Overworld &world) override;
};

export struct Move_Demon_Towards_Player : Rule {
	int amount_of_conquest = 0;
	Move_Demon_Towards_Player(int amount) : amount_of_conquest(amount) {}
	void execute(Overworld &world) override;
};

export struct Conquest_Of_Demon : Rule {
	void execute(Overworld &world) override;
};

export struct Apply_Conquest_Of_Demon_Result : Rule {
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
	void execute(Overworld &world) override;
};

export struct Resolve_Passage_Dialect : Rule {
	void execute(Overworld &world) override;
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
	Move_One_Space_Optional(int amount = 1) : amount_of_optional_move(amount) {}
	void execute(Overworld &world) override;
};

export struct Apply_Optional_Journey : Rule {
	int amount_of_optional_move;
	Apply_Optional_Journey(int amount) : amount_of_optional_move(amount) {}
	void execute(Overworld &world) override;
};

export struct Teleport : Rule {
	Landmark landmark_of_destination;
	Teleport(Landmark landmark_of_destination) : landmark_of_destination(landmark_of_destination) {}
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

export using Certainty = std::deque<int>;

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

export struct Gift_Of_Optics : Rule {
	Overworld *terra = nullptr;
	void execute(Overworld &world) override;
	void display_gift_of_optics();
};


export struct Apply_Gift_Of_Optics : Rule {
	void execute(Overworld &world) override;
	static inline const std::vector<Optics> obtainable_optical_items;
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


export struct All_Players_In_Demon_Zone_Lose_One_Heart : Rule {
	void execute(Overworld &world) override;
};

export struct Apply_Mediumship_Of_Corruption : Rule {
	void execute(Overworld &world) override;
		static constexpr int reach = 2; // Each outcome corresponds to 2 die results (e.g., 1-2, 3-4, 5-6)
	static inline const std::vector<DemonForm> outcomes;
};

export struct Media_Of_Mediumship : Rule {
	void execute(Overworld &world) override;
};

export struct Mediumship_Of_Corruption : Rule {
	void execute(Overworld &world) override;
};

export struct Apply_Demon_Board_Result : Rule {
	void execute(Overworld &world) override;
	void applyDemonBoardResult(Overworld &world, DieRoll roll);
};

export struct Demon_Board : Rule
{
	void execute(Overworld &world) override;
};



// ##××××-------->>> ./Showcase <<<--------××××##
//
//
//
//

// +++------>>> subdivision.cppm <<<------+++

export struct Showcase_Movement : Rule {
	void execute(Overworld &world) override {
	}
};
export struct Showcase_Fortuneboard : Rule {
	void execute(Overworld &world) override {
	}
};
export struct Showcase_Marketplace : Rule {
	void execute(Overworld &world) override {
	}
};
export struct Showcase_Adventurer_Turn : Rule {
	void execute(Overworld &world) override {
	}
};
export struct Showcase_Reincarnation : Rule {
	void execute(Overworld &world) override {
	}
};
export struct Showcase_Warfare : Rule {
	void execute(Overworld &world) override {
	}
};

// +++------>>> amusement.cppm <<<------+++

export struct Amusement_A : Rule {
	void execute(Overworld &world) override;
};









} // namespace Parity