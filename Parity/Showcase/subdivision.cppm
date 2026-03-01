export module Parity.Subdivision;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include "../type-definition.cppm"
#else
	import Parity.World;
	
	import Parity.Necromancy;
	import Parity.Physiology;
	import Parity.Marketplace;
	import Parity.Warfare;
	import Parity.Adventure;
	import Parity.Journey;
	import Parity.FortuneBoard;
	import Parity.ScoutFly;
#endif

export namespace Parity
{

export struct Showcase_Movement : Rule {
	void execute(Overworld &world) override {
		world.event<Welcome_Adventurer>(1);
		world.event<First_Adventurer_Turn>();
		world.event<Move_One_Space_Optional>(30);
	}
};

export struct Showcase_Fortuneboard : Rule {
	void execute(Overworld &world) override {
		world.event<Welcome_Adventurer>(1);
		world.event<First_Adventurer_Turn>();
		
		for (int i = 0; i < 5; ++i) {
			world.event<Lucky_Board>();
		}
	}
};

export struct Showcase_Marketplace : Rule {
	void execute(Overworld &world) override {
		world.event<Welcome_Adventurer>(1);
		world.event<First_Adventurer_Turn>();
		world.event<Gain_Gold_Coin>(60);
		world.expedition.landmark_of_destination = Landmark::OpticalMarketplace;
		world.event<Arrival>();
		world.event<Arrival>();
	}
};

export struct Showcase_Adventurer_Turn : Rule {
	void execute(Overworld &world) override {
		world.event<Welcome_Adventurer>(2);
		world.event<First_Adventurer_Turn>();
		world.event<Move_One_Space>();
		
		for (int i = 0; i < 2; ++i) {
			world.event<Next_Adventurer_Turn>();
			world.event<Move_One_Space>();
		}
	};
};


export struct Showcase_Reincarnation : Rule {
	void execute(Overworld &world) override {
		world.event<Welcome_Adventurer>(2);
		world.event<First_Adventurer_Turn>();
		
		world.event<Vitality_Hurt>(3);
		world.event<Vitality_Hurt>(3);
		
		world.event<Next_Adventurer_Turn>();
		
		world.event<Vitality_Hurt_Humanity>(7);
		world.event<Vitality_Hurt>(11);
		
		world.event<Next_Adventurer_Turn>();
		world.event<Vitality_Hurt>(5);
	}
};

export struct Showcase_Warfare : Rule {
	void execute(Overworld &world) override {
		world.event<Welcome_Adventurer>(2);
		world.event<First_Adventurer_Turn>();
		
		world.event<Summon_Demon>(DemonForm::ElectricMinion, Landmark::DiamondOfParity);
		
		world.event<Commencement_Of_Warfare>();
	}
};

export struct Showcase_Demon_Movement : Rule {
	void execute(Overworld &world) override {
		world.event<Welcome_Adventurer>(1);
		world.event<First_Adventurer_Turn>();
		world.event<Summon_Demon>(DemonForm::ElectricMinion, Landmark::DiamondOfParity);
		world.event<Move_Demon_Towards_Player>(16);
	}
};

export struct Showcase_Potential_Of_Warfare : Rule {
	void execute(Overworld &world) override {
		world.event<Welcome_Adventurer>(1);
		world.event<First_Adventurer_Turn>();
		world.event<Summon_Demon>(DemonForm::ElectricMinion, Landmark::DiamondOfParity);
		world.event<Move_One_Space_Optional>(3);
		world.event<Move_Demon_Towards_Player>(16);
		world.event<Potential_Of_Warfare>(Landmark::OpticalMarketplace);
	}
};

} // namespace Parity