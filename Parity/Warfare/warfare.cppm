export module Parity.Warfare;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	import Parity.Biology;
	import Parity.Necrology;
	import Parity.DieRoll;
	import Parity.Geography;
#endif

export namespace Parity
{

//
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
	Read_Combat_Strength(const std::string& clause) : clause(clause) {}
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





}