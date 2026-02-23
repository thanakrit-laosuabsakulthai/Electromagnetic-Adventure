export module Parity.ColorEffect;

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
	import Parity.Physiology;
	import Parity.FortuneBoard;
	import Parity.Chromaticity;
	
#endif


/* 
# Space Effects

1.  **Pink:** Heal 1 Heart (unless already at maximum Hearts).
2.  **Green:** Trigger the Lucky Board once.
3.  **Orange:** Trigger the Event Board once.
4.  **Yellow:** Gain 1 Gold Coin, and the player *may* purchase items from the Shop Board.
5.  **Red:** Trigger the Unlucky Board once.
6.  **Purple:** Trigger the Demon Board once.
7.  **Pink-Orange-Yellow Gradient:** Roll 1 die:
    *   1-2: Yellow space effect.
    *   3-4: Orange space effect.
    *   5-6: Pink space effect.
8.  **Red-Purple Gradient:** Roll 1 die:
    *   1-3: Purple space effect.
    *   4-6: Red space effect.
9.  **White-Gray Gradient:** Nothing happens.
*/

export namespace Parity
{
ApparentColor Overworld::getColorUnderActivePlayer() {
		Landmark current_landmark = getLandmarkOfActivePlayer();
		return atlas[current_landmark].apparentColor;
	
};

export inline std::string activation_synthesis(ApparentColor color) {
	return std::format(
		"Activate {}{} effect.",
		to_string(color),
		is_gradient_color(color) ? "" : " color"
	);
}

export struct Pink_Color_Effect : Rule {
	void execute(Overworld &world) override {
		world.event<Vitality_Heal>(1);
		world.announce.result("Heal 1 Heart (unless already at maximum Hearts)");
	}
};

export struct Green_Color_Effect : Rule {
	void execute(Overworld &world) override {
		world.event<Lucky_Board>();
		world.announce.result("Trigger the Lucky Board once");
	}
};

export struct Orange_Color_Effect : Rule {
	void execute(Overworld &world) override {
		world.event<Event_Board>();
		world.announce.result("Trigger the Event Board once");
	}
};

export struct Yellow_Color_Effect : Rule {
	void execute(Overworld &world) override {
		world.event<Gain_Gold_Coin>(1);
		world.announce.result("Gain 1 Gold Coin, and you may purchase items from the Shop Board");
	}
};

export struct Red_Color_Effect : Rule {
	void execute(Overworld &world) override {
		world.event<Unlucky_Board>();
		world.announce.result("Trigger the Unlucky Board once");
	}
};

export struct Purple_Color_Effect : Rule {
	void execute(Overworld &world) override {
		world.event<Demon_Board>();
		world.announce.result("Trigger the Demon Board once");
	}
};

export struct Roll_For_Chromaticity : Rule {
	void execute(Overworld &world) override {
		world.die_roll_for_chromaticity = static_cast<DieRoll>((std::rand() % 6) + 1);
		world.announce.bygone(std::format(
			"Rolled [{}] for Chromaticity.",
			static_cast<int>(world.die_roll_for_chromaticity)
		));
	}
};

export struct Media_Of_Pink_Orange_Yellow_Gradient : Rule {
	void execute(Overworld &world) override {
		world.announce.linger("Roll 1 die and apply the result...");	
		world.announce.beginChoice();
		
		for (int i = 0; i < outcomes.size(); ++i) {
			world.announce.range(outcomes[i], reach);
		}
	}
	
	static constexpr int reach = 2; // Each outcome corresponds to 2 die results (e.g., 1-2, 3-4, 5-6)
	
	static inline const std::vector<std::string> outcomes = {
		"Yellow space effect.",
		"Orange space effect.",
		"Pink space effect."
	};
};

export struct Apply_Pink_Orange_Yellow_Gradient_Result : Rule {
	void execute(Overworld &world) override {
		using enum DieRoll;
		
		int outcome_index = (static_cast<int>(world.die_roll_for_chromaticity) - 1) / Media_Of_Pink_Orange_Yellow_Gradient::reach;
		world.announce.linger(std::format(
			"Activate {}",
			Media_Of_Pink_Orange_Yellow_Gradient::outcomes[outcome_index]
		));
		
		switch (world.die_roll_for_chromaticity) {
		case One:
		case Two:
			world.event<Yellow_Color_Effect>();
			break;
		case Three:
		case Four:
			world.event<Orange_Color_Effect>();
			break;
		case Five:
		case Six:
			world.event<Pink_Color_Effect>();
			break;
		}
	}
};

export struct Pink_Orange_Yellow_Gradient_Effect : Rule {
	void execute(Overworld &world) override {
		world.event<Media_Of_Pink_Orange_Yellow_Gradient>();
		world.event<Roll_For_Chromaticity>();
		world.event<Apply_Pink_Orange_Yellow_Gradient_Result>();
	}
};

export struct Media_Of_Red_Purple_Gradient : Rule {
	void execute(Overworld &world) override {
		world.announce.linger("Roll 1 die and apply the result...");	
		world.announce.beginChoice();
		
		for (int i = 0; i < outcomes.size(); ++i) {
			world.announce.range(outcomes[i], reach);
		}
	}
	
	static constexpr int reach = 3; // Each outcome corresponds to 3 die results (e.g., 1-3, 4-6)
	
	static inline const std::vector<std::string> outcomes = {
		"Purple space effect.",
		"Red space effect."
	};
};

export struct Apply_Red_Purple_Gradient_Result : Rule {
	void execute(Overworld &world) override {
		using enum DieRoll;
		
		int outcome_index = (static_cast<int>(world.die_roll_for_chromaticity) - 1) / Media_Of_Red_Purple_Gradient::reach;
		world.announce.linger(std::format(
			"Activate {}",
			Media_Of_Red_Purple_Gradient::outcomes[outcome_index]
		));
		
		switch (world.die_roll_for_chromaticity) {
		case One:
		case Two:
		case Three:
			world.event<Purple_Color_Effect>();
			break;
		case Four:
		case Five:
		case Six:
			world.event<Red_Color_Effect>();
			break;
		}
	}
};

export struct Red_Purple_Gradient_Effect : Rule {
	void execute(Overworld &world) override {
		world.event<Media_Of_Red_Purple_Gradient>();
		world.event<Roll_For_Chromaticity>();
		world.event<Apply_Red_Purple_Gradient_Result>();
	}
};


void Activate_Color_Effect::execute(Overworld &world) {
	ApparentColor color_under_active_player = world.getColorUnderActivePlayer();
	
	world.announce.action(activation_synthesis(color_under_active_player));
	
	using enum ApparentColor;
	switch (color_under_active_player) {
		case Pink:
			world.event<Pink_Color_Effect>();
			break;
		case Green:
			world.event<Green_Color_Effect>();
			break;
		case Orange:
			world.event<Orange_Color_Effect>();
			break;
		case Yellow:
			world.event<Yellow_Color_Effect>();
			break;
		case Red:
			world.event<Red_Color_Effect>();
			break;
		case Purple:
			world.event<Purple_Color_Effect>();
			break;
		case PinkOrangeYellowGradient:
			world.event<Pink_Orange_Yellow_Gradient_Effect>();
			break;
		case RedPurpleGradient:
			world.event<Red_Purple_Gradient_Effect>();
			break;
		default:
			world.announce.result("Nothing happens.");
			break;
	}
}


}