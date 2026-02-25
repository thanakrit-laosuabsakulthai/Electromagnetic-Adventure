export module Parity.Chromaticity;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
#endif

export namespace Parity
{

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
	static constexpr int reach = 2; // Each outcome corresponds to 2 die results (e.g., 1-2, 3-4, 5-6)
	static inline const std::vector<std::string> outcomes = {
		"Yellow space effect.",
		"Orange space effect.",
		"Pink space effect."
	};
};
export struct Apply_Pink_Orange_Yellow_Gradient_Result : Rule {
	void execute(Overworld &world) override;
};
export struct Pink_Orange_Yellow_Gradient_Effect : Rule {
	void execute(Overworld &world) override;
};
export struct Media_Of_Red_Purple_Gradient : Rule {
	void execute(Overworld &world) override;
	static constexpr int reach = 3; // Each outcome corresponds to 3 die results (e.g., 1-3, 4-6)
	static inline const std::vector<std::string> outcomes = {
		"Purple space effect.",
		"Red space effect."
	};
};
export struct Apply_Red_Purple_Gradient_Result : Rule {
	void execute(Overworld &world) override;
};
export struct Red_Purple_Gradient_Effect : Rule {
	void execute(Overworld &world) override;
};

} // namespace Parity