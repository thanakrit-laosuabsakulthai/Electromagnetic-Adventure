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
	import Parity.Marketplace;
	
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
void Pink_Color_Effect::execute(Overworld &world) {
	world.event<Vitality_Heal>(1);
	world.announce.result("Heal 1 Heart (unless already at maximum Hearts)");
}

void Green_Color_Effect::execute(Overworld &world) {
	world.event<Lucky_Board>();
	world.announce.result(std::format(
		"Trigger the {} once",
		bold_cyan("Lucky Board")
	));
}

void Orange_Color_Effect::execute(Overworld &world) {
	world.event<Event_Board>();
	world.announce.result(std::format(
		"Trigger the {} once",
		bold_cyan("Event Board")
	));
}

void Yellow_Color_Effect::execute(Overworld &world) {
	world.event<Gain_Gold_Coin>(1);
	world.event<Open_Shop>();
	
	/* world.announce.result("Gain 1 Gold Coin, and you may purchase items from the Shop Board."); */
	world.announce.result(std::format(
		"Gain {}, and you may purchase items from the {}.",
		bold_cyan("1 Gold Coin"),
		bold_cyan("Shop Board")
	));
}

void Red_Color_Effect::execute(Overworld &world) {
	world.event<Unlucky_Board>();
	world.announce.result(std::format(
		"Trigger the {} once",
		bold_cyan("Unlucky Board")
	));
}

void Purple_Color_Effect::execute(Overworld &world) {
	world.event<Demon_Board>();
	world.announce.result(std::format(
		"Trigger the {} once",
		bold_cyan("Demon Board")
	));
}

void Roll_For_Chromaticity::execute(Overworld &world) {
	world.die_roll_for_chromaticity = world.fatesAndCertainty();
	world.announce.bygone(std::format(
		"Rolled [{}] for Chromaticity.",
		static_cast<int>(world.die_roll_for_chromaticity)
	));
}

void Media_Of_Pink_Orange_Yellow_Gradient::execute(Overworld &world) {
	world.announce.linger("Roll 1 die and apply the result...");	
	world.announce.beginChoice();
	
	std::vector<ApparentColor> outcomes = Apply_Pink_Orange_Yellow_Gradient_Result::outcomes;
	
	for (int i = 0; i < outcomes.size(); ++i) {
		world.announce.range(std::format("{} color effect.",
			to_string(outcomes[i])
			),
			Apply_Pink_Orange_Yellow_Gradient_Result::reach
		);
	}
}

void Apply_Pink_Orange_Yellow_Gradient_Result::execute(Overworld &world) {
	using enum DieRoll;
	
	int outcome_index = (static_cast<int>(world.die_roll_for_chromaticity) - 1) / reach;
	
	world.announce.linger(std::format(
		"Activate {} color effect.",
		to_string(outcomes[outcome_index])
	));
	
	switch (outcomes[outcome_index]) {
	case ApparentColor::Yellow:
		world.event<Yellow_Color_Effect>();
		break;
	case ApparentColor::Orange:
		world.event<Orange_Color_Effect>();
		break;
	case ApparentColor::Pink:
		world.event<Pink_Color_Effect>();
		break;
	}
	
}

void Pink_Orange_Yellow_Gradient_Effect::execute(Overworld &world) {
	world.event<Media_Of_Pink_Orange_Yellow_Gradient>();
	world.event<Roll_For_Chromaticity>();
	world.event<Apply_Pink_Orange_Yellow_Gradient_Result>();
}

void Media_Of_Red_Purple_Gradient::execute(Overworld &world) {
	world.announce.linger("Roll 1 die and apply the result...");	
	world.announce.beginChoice();
	
	std::vector<ApparentColor> outcomes = Apply_Red_Purple_Gradient_Result::outcomes;
	
	for (int i = 0; i < outcomes.size(); ++i) {
		world.announce.range(std::format("{} color effect.",
			to_string(outcomes[i])
			),
			Apply_Red_Purple_Gradient_Result::reach
		);
	}
}

void Apply_Red_Purple_Gradient_Result::execute(Overworld &world) {
	using enum DieRoll;
	
	int outcome_index = (static_cast<int>(world.die_roll_for_chromaticity) - 1) / reach;
	
	world.announce.linger(std::format(
		"Activate {} color effect.",
		to_string(outcomes[outcome_index])
	));
	
	switch (outcomes[outcome_index]) {
	case ApparentColor::Purple:
		world.event<Purple_Color_Effect>();
		break;
	case ApparentColor::Red:
		world.event<Red_Color_Effect>();
		break;
	}
}

void Red_Purple_Gradient_Effect::execute(Overworld &world) {
	world.event<Media_Of_Red_Purple_Gradient>();
	world.event<Roll_For_Chromaticity>();
	world.event<Apply_Red_Purple_Gradient_Result>();
}


void Activate_Color_Effect::execute(Overworld &world) {
	PlayerIdentity active_player = world.active_player;
	PlayerPosession &active_player_posession = world.playerbase[active_player];
	Landmark current_landmark = world.getLandmarkOfActivePlayer();
	
	if (current_landmark == Landmark::DiamondOfCattail
		&& active_player_posession.vitality_heart >= active_player_posession.vitality_maximum_heart
	) {
		return; // Do not activate color effect if on Diamond of Cattail and already at maximum Hearts
	}
	
	ApparentColor color_under_active_player = world.getColorUnderActivePlayer();
	
	world.announce.action(activation_synthesis(color_under_active_player));
	//

	
	
	using enum ApparentColor;
	switch (color_under_active_player) {
		case Pink:
			world.event<Pink_Color_Effect>();
			break;
		case Green:
			world.announce.suspense(1); // quiet if world.announce.suspense_level > 1
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
			world.announce.result("Nothing happened.");
			break;
	}
}


}