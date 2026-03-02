export module Parity.ScoutFly;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include <print>
	#include <iostream>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	
	import Parity.Geography;
	import Parity.Expedition;
#endif

export namespace Parity {

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













} // namespace Parity