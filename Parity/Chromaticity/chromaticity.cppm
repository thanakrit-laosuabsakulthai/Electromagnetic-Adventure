export module Parity.Chromaticity;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.Geography;
	import Parity.Notation;
#endif

export namespace Parity
{
//

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
	static inline const std::vector<ApparentColor> outcomes = {
		ApparentColor::Yellow,
		ApparentColor::Orange,
		ApparentColor::Pink
	};
};
export struct Pink_Orange_Yellow_Gradient_Effect : Rule {
	void execute(Overworld &world) override;
};
export struct Media_Of_Red_Purple_Gradient : Rule {
	void execute(Overworld &world) override;
/* 	static constexpr int reach = 3; // Each outcome corresponds to 3 die results (e.g., 1-3, 4-6)
	static inline const std::vector<std::string> outcomes = {
		"Purple space effect.",
		"Red space effect."
	}; */
};
export struct Apply_Red_Purple_Gradient_Result : Rule {
	void execute(Overworld &world) override;
	static constexpr int reach = 3; // Each outcome corresponds to 3 die results (e.g., 1-3, 4-6)
	static inline const std::vector<ApparentColor> outcomes = {
		ApparentColor::Purple,
		ApparentColor::Red
	};
};
export struct Red_Purple_Gradient_Effect : Rule {
	void execute(Overworld &world) override;
};


export inline std::string activation_synthesis(ApparentColor color) {
	return std::format(
		"Activate {}{} effect.",
		to_string(color),
		is_gradient_color(color) ? "" : " color"
	);
}


} // namespace Parity