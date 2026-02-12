#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <memory>

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

export constexpr std::string_view to_string(PlayerIdentity identity);

export struct Rule { 
	virtual ~Rule();
	virtual void execute(class Overworld &world);
};

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

export class Overworld
{
	public:
	
	DieRoll die_roll_for_fortune_board;
	int fortune_board_multiplier;
	int useFortuneBoardMultiplier();
	Humanity playerbase;
	PlayerIdentity active_player;
	
	std::deque<std::unique_ptr<Rule>> event_queue;
	void main_loop();
	
	template <typename Extent_of_Rule, typename... Argument_of_Rule>
	void event(Argument_of_Rule&&... custom_arguments);
};

export void print_all_landmark_notations();

} // namespace Parity