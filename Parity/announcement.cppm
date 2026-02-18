export module Parity.Announcement;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include <print>
	#include <map>
	#include <iostream>
	#include "type-definition.cppm"
#else
	import std; // Standard library import
#endif

export namespace Parity
{

export enum class MediaClause {
	Media,
	MediaBullet,
	MediaIndent,
};

export enum class FormattingNotation {
	Plain,
	Bold,
	Italic,
	Underline,
	Cyan
};


export inline std::string_view to_notation(FormattingNotation notation) {
	using enum FormattingNotation;
	static const std::map<FormattingNotation, std::string_view> formattingLexiconToString = {
		{Plain, "{}"},
		{Bold, "\033[1m{}\033[0m"},
		{Italic, "\033[3m{}\033[0m"},
		{Underline, "\033[4m{}\033[0m"},
		{Cyan, "\033[36m{}\033[0m"}
	};
	return formattingLexiconToString.at(notation);
}

export inline std::string bold(const std::string content) {
	std::string_view bold_notation = to_notation(FormattingNotation::Bold);
	
	return std::vformat(bold_notation, std::make_format_args(content));
}

export inline std::string italic(const std::string content) {
	std::string_view italic_notation = to_notation(FormattingNotation::Italic);
	
	return std::vformat(italic_notation, std::make_format_args(content));
}

export inline std::string cyan(const std::string content) {
	std::string_view cyan_notation = to_notation(FormattingNotation::Cyan);
	
	return std::vformat(cyan_notation, std::make_format_args(content));
}

export inline std::string italic_cyan(const std::string content) {
	return italic(cyan(content));
}

export inline std::string bold_cyan(const std::string content) {
	return bold(cyan(content));
}

export class Announcement {
public:
	MediaClause clause = MediaClause::Media;
	int consequential_ordinal = 0;
	int choice_ordinal = 0;
	
	std::string_view getMediaNotation() {
		static const std::map<MediaClause, std::string_view> mediaClauseToNotation = {
			{MediaClause::Media, "{}"},
			{MediaClause::MediaBullet, "• {}"},
			{MediaClause::MediaIndent, "\t{}"}
		};
		
		return mediaClauseToNotation.at(clause);
	}
	
	void media(const std::string& content_append_media) {
		std::string_view media_notation = getMediaNotation();
		std::string formatted_media = std::vformat(media_notation, std::make_format_args(content_append_media));
		std::print("{}\n", formatted_media);
	}
	
	void chat(const std::string& content_append_chat) {
		std::string_view media_notation = getMediaNotation();
		std::string formatted_media = std::vformat(media_notation, std::make_format_args(content_append_chat));
		std::print("{}", formatted_media);
	}
	
	std::string getActionLexicon() {
		return bold(std::format("» Action {}:", consequential_ordinal));
	}
	
	std::string getResultLexicon() {
		return bold(std::format("« Result {}:", consequential_ordinal));
	}
	
	std::string getChoiceLexicon() {
		return bold_cyan(std::format("[{}]", choice_ordinal));
	}
	
	void action(const std::string& content_append_action) {
		consequential_ordinal++;
		clause = MediaClause::MediaBullet;
		media(std::format("{} {}", getActionLexicon(), content_append_action));
	}
	
	void result(const std::string& content_append_result) {
		media(std::format("{} {}", getResultLexicon(), content_append_result));
	}
	
	void bygone(const std::string& content_of_bygone) {
		media(italic_cyan(content_of_bygone));
	}
	
	void subtitle(const std::string& content_of_subtitle) {
		media(content_of_subtitle);
	}
	
	void ask(const std::string& content_of_ask) {
		clause = MediaClause::MediaBullet;
		chat(bold(content_of_ask));
	}
	
	void choice(const std::string& content_of_choice) {
		clause = MediaClause::MediaIndent;
		choice_ordinal++;
		media(std::format("{} {}", getChoiceLexicon(), content_of_choice));
	}
	
	void beginChoice() {
		choice_ordinal = 0;
	}
	
	void redact() { // Delete the most recent announcement
		std::print("\033[1A\033[2K"); // Move cursor up and clear the line
	}
	
	void reject() { // Reject the most recent user query
		std::print("\033[1A\033[2K"); // Move cursor up and clear the line
		std::print("\033[2K"); 
	}
	
	std::string listen() {
		std::string player_input;
		std::getline(std::cin, player_input);
		return player_input;
	}
};

} // namespace Parity







