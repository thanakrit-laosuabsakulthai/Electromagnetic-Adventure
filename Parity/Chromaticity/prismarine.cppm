export module Parity.Prismarine;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include "../type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.World;
	import Parity.Announcement;
	
	import Parity.Optoelectronic;
	import Parity.Geography;
	import Parity.Notation;
	
	import Parity.Chromaticity;
	import Parity.Physiology;
	import Parity.Marketplace;
#endif

export namespace Parity
{
//
void Apply_Prismatism::execute(Overworld &world) {
	// check if player is on a gradient color
	ApparentColor current_color = world.getColorUnderActivePlayer();
	ApparentColor chosen_color = world.chosen_prismarine;
	Landmark current_landmark = world.getLandmarkOfActivePlayer();
	ApparentQuality current_quality = world.atlas[current_landmark].apparentQuality;
	
	if (!( is_gradient_color(current_color)
		|| current_quality == ApparentQuality::ImitationOfColor
	)) {
		return; // Do not apply Prismarine if not on a gradient color
		// still apply Prismarine if on an imitation of color
	}
	if (is_gradient_color(chosen_color)) {
		return; // Do not apply Prismarine if the chosen color is a gradient color
	}
	
	world.announce.result(std::format(
		"{} chose {} color effect.",
		world.getActivePlayerName(),
		bold_cyan(std::string(to_string(chosen_color)))
	));
	
	// if it is  an imitation of color, or the white-gray gradient
	
	if (current_quality == ApparentQuality::ImitationOfColor ||
		current_color == ApparentColor::WhiteGrayGradient
	) {
		world.event<Coalescence_Of_Prismatism>();
	} else {
		world.announce.action(activation_synthesis(chosen_color));
	}
	
	// regardless, push the color effect of the chosen color
	
	
	
	
	using enum ApparentColor;
	// only non-gradient colors can be chosen
	switch (chosen_color) {
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
		default:
			break; // Do not apply any color effect if the chosen color is a gradient color
	}
}

void Coalescence_Of_Prismatism::execute(Overworld &world) {
	// if the player is on an imitation of color, or the white-gray gradient
	ApparentColor current_color = world.getColorUnderActivePlayer();
	ApparentColor chosen_color = world.chosen_prismarine;
	
	Landmark current_landmark = world.getLandmarkOfActivePlayer();
	ApparentQuality current_quality = world.atlas[current_landmark].apparentQuality;
	
	
	
	if (! (current_color == ApparentColor::WhiteGrayGradient ||
		current_quality == ApparentQuality::ImitationOfColor
	)) {
		return; // Do not apply Coalescence of Prismatism
	}
	
	world.announce.linger(std::format(
		"The colorful gleam of {} coalesces into a vibrant {} color!",
		to_string(current_landmark),
		to_string(chosen_color)
	));
	world.announce.action(activation_synthesis(chosen_color));
	// change the appearance of the atlas
	
	world.atlas[current_landmark].apparentQuality = ApparentQuality::ImitationOfColor;
	world.atlas[current_landmark].apparentColor = chosen_color;
}

void Media_Of_Prismatism::execute(Overworld &world) {
	world.announce.action(std::format(
		"{} chooses a color effect...",
		world.getActivePlayerName()
	));
	
	world.announce.beginChoice();
	for (const auto& color : world.potential_prismarine) {
		world.announce.choice(std::string(to_string(color)));
	}
}

void Open_Prismarine::execute(Overworld &world) {
	// player chooses a color effect to activate
	Landmark current_landmark = world.getLandmarkOfActivePlayer();
	ApparentColor current_color = world.getColorUnderActivePlayer();
	ApparentQuality current_quality = world.atlas[current_landmark].apparentQuality;
	
	if ( !(
		is_gradient_color(current_color) ||
		current_quality == ApparentQuality::ImitationOfColor
	)) {
		return; // Do not open Prismarine
	}
	
	world.potential_prismarine.clear();
	
	switch (current_color) {
	case ApparentColor::PinkOrangeYellowGradient:
		world.potential_prismarine = {
			ApparentColor::Pink,
			ApparentColor::Orange,
			ApparentColor::Yellow
		};
		break;
	case ApparentColor::RedPurpleGradient:
		world.potential_prismarine = {
			ApparentColor::Red,
			ApparentColor::Purple
		};
		break;
	default:
		world.potential_prismarine = {
			// any non-gradient color except the current color
			// remove the current color later
			ApparentColor::Pink,
			ApparentColor::Green,
			ApparentColor::Orange,
			ApparentColor::Yellow,
			ApparentColor::Red,
			ApparentColor::Purple
		};
		// remove the current color from potential prismarine
		world.potential_prismarine.erase(current_color);
		break;
	}
	
	world.event<Media_Of_Prismatism>();
	world.event<Glazier_Of_Chromaticity>();
	world.event<Apply_Prismatism>();
}

void Omen_Of_Chromaticity::execute(Overworld &world) {
	
	Landmark current_landmark = world.getLandmarkOfActivePlayer();
	ApparentColor current_color = world.getColorUnderActivePlayer();
	ApparentQuality current_quality = world.atlas[current_landmark].apparentQuality;
	
	if ( !(
		is_gradient_color(current_color) ||
		current_quality == ApparentQuality::ImitationOfColor
	)) {
		world.event<Activate_Color_Effect>(); //
		return;
		// if player is on pure color landmark,
		// the light waves item cannot be applied
	}
	
	// check if the player has the light waves item
	PlayerIdentity active_player = world.active_player;
	PlayerPosession &active_player_posession = world.playerbase[active_player];
	Inventory &active_inventory = active_player_posession.inventory;
	
	if (active_inventory.count(Optics::LightWaves) == 0) {
		world.event<Activate_Color_Effect>(); //
		return;
	}
	
	world.event<Potential_Of_Chromatic_Consumption>();
	world.event<Apply_Omen_Of_Chromaticity>();
}

void Apply_Omen_Of_Chromaticity::execute(Overworld &world) {
	// check for chromatic status effect in active player
	PlayerIdentity active_player = world.active_player;
	PlayerPosession &active_player_posession = world.playerbase[active_player];
	
	bool has_chromatic_status = active_player_posession.active_optical_effect.contains(OpticalEffect::Chromatic);
	
	if (has_chromatic_status) {
		world.event<Open_Prismarine>();
		world.event<Take_Optical_Effect>(OpticalEffect::Chromatic);
		return; // will not further activate the space's color effect
	}
	
	world.event<Activate_Color_Effect>();
	
}














} // namespace Parity