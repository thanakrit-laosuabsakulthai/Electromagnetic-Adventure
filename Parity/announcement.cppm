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
	MediaCatalog,
	MediaOverhang,
};

export enum class FormattingNotation {
	Plain,
	Bold,
	Italic,
	Underline,
	Strikethrough,
	Cyan
};


export inline std::string_view to_notation(FormattingNotation notation) {
	using enum FormattingNotation;
	static const std::map<FormattingNotation, std::string_view> formattingLexiconToString = {
		{Plain, "{}"},
		{Bold, "\033[1m{}\033[0m"},
		{Italic, "\033[3m{}\033[0m"},
		{Underline, "\033[4m{}\033[0m"},
		{Strikethrough, "\033[9m{}\033[0m"},
		{Cyan, "\033[36m{}\033[0m"}
	};
	return formattingLexiconToString.at(notation);
}


export inline std::string format_with_notation(FormattingNotation notation, const std::string& content) {
	std::string_view notation_template = to_notation(notation);
	return std::vformat(notation_template, std::make_format_args(content));
}

export inline std::string bold(const std::string content) {
	return format_with_notation(FormattingNotation::Bold, content);
}

export inline std::string italic(const std::string content) {
	return format_with_notation(FormattingNotation::Italic, content);
}

export inline std::string underline(const std::string content) {
	return format_with_notation(FormattingNotation::Underline, content);
}

export inline std::string strikethrough(const std::string content) {
	return format_with_notation(FormattingNotation::Strikethrough, content);
}

export inline std::string cyan(const std::string content) {
	return format_with_notation(FormattingNotation::Cyan, content);
}

export inline std::string italic_cyan(const std::string content) {
	return italic(cyan(content));
}

export inline std::string bold_cyan(const std::string content) {
	return bold(cyan(content));
}

export inline std::string bold_italic_cyan(const std::string content) {
	return bold(italic(cyan(content)));
}

export inline std::string bold_acute(const std::string content) {
	return bold("‹" + content + "›");
}

export class Announcement {
public:
	MediaClause clause = MediaClause::Media;
	int consequential_ordinal = 0;
	int choice_ordinal = 0;
	int analog_ordinal = 0;
	
	std::string_view getMediaNotation() {
		static const std::map<MediaClause, std::string_view> mediaClauseToNotation = {
			{MediaClause::Media, "{}"},
			{MediaClause::MediaBullet, "• {}"},
			{MediaClause::MediaIndent, "\t{}"},
			{MediaClause::MediaCatalog, "\t\t• {}"},
			{MediaClause::MediaOverhang, "\t• {}"}
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
	
	std::string getForbidLexicon() {
		return bold_cyan("[-]");
	}
	
	std::string getRangeLexicon(int reach) {
		if (reach <= 1) {
			return getChoiceLexicon();
		} else {
			return bold_cyan(std::format("[{}-{}]", choice_ordinal - reach + 1, choice_ordinal));
		}
	}
	
	std::string getAnalogLexicon() {
		return bold(std::format("{}.", analog_ordinal));
	}
	
	std::string getAskNotation() {
		return bold("» Choice {}: ");
	}
	
	void beginConsequential() {
		consequential_ordinal = 0;
	}
	
	void action(const std::string& content_append_action) {
		consequential_ordinal++;
		clause = MediaClause::MediaBullet;
		media(std::format("{} {}", getActionLexicon(), content_append_action));
	}
	
	void result(const std::string& content_append_result) {
		clause = MediaClause::MediaBullet;
		media(std::format("{} {}", getResultLexicon(), content_append_result));
	}
	
	void bygone(const std::string& content_of_bygone) {
		media(italic_cyan(content_of_bygone));
	}
	
	void subtitle(const std::string& content_of_subtitle) {
		media(content_of_subtitle);
	}
	
	void caption(const std::string& content_of_caption) {
		clause = MediaClause::Media;
		media(content_of_caption);
	}
	
	void linger(const std::string& content_of_linger) {
		clause = MediaClause::MediaBullet;
		media(content_of_linger);
	}
	
	void linebreak() {
		clause = MediaClause::Media;
		std::print("\n");
	}
	
	void horizon(const std::string& content_of_horizon) {
		clause = MediaClause::Media;
		linebreak();
		media(content_of_horizon);
		linebreak();
	}
	
	void ask(const std::string& content_of_ask) {
		clause = MediaClause::MediaBullet;
		chat(std::vformat(getAskNotation(), std::make_format_args(content_of_ask)));
	}
	
	void choice(const std::string& content_of_choice) {
		clause = MediaClause::MediaIndent;
		choice_ordinal++;
		media(std::format("{} {}", getChoiceLexicon(), content_of_choice));
	}
	
	void forbid(const std::string& content_of_forbid) {
		clause = MediaClause::MediaIndent;
		media(std::format("{} {}", getForbidLexicon(), strikethrough(content_of_forbid)));
	}
	
	void range(const std::string& content_of_range, int reach) {
		clause = MediaClause::MediaIndent;
		choice_ordinal += reach;
		media(std::format("{} {}", getRangeLexicon(reach), content_of_range));
	}
	
	void beginChoice() {
		choice_ordinal = 0;
	}
	
	void catalog(const std::string& content_of_catalog) {
		clause = MediaClause::MediaCatalog;
		media(content_of_catalog);
	}
	
	void overhang(const std::string& content_of_overhang) {
		clause = MediaClause::MediaOverhang;
		media(content_of_overhang);
	}
	
	void beginAnalog() {
		analog_ordinal = 0;
	}
	
	void analog(const std::string& content_of_analog) {
		clause = MediaClause::MediaIndent;
		analog_ordinal++;
		media(std::format("{} {}", getAnalogLexicon(), content_of_analog));
	}
	
	void analogical(const std::string& content_of_analogical) {
		clause = MediaClause::MediaIndent;
		analog_ordinal++;
		media(std::format("{} {}", cyan(getAnalogLexicon()), content_of_analogical));
	}
	
	void redact() { // Delete the most recent announcement
		std::print("\033[1A\033[2K"); // Move cursor up and clear the line
	}
	
	void reject() { // Reject the most recent user query
		std::print("\033[1A\033[2K"); // Move cursor up and clear the line
		//std::print("\033[2K"); 
	}
	
	std::string listen() {
		std::string player_input;
		std::getline(std::cin, player_input);
		return player_input;
	}
};

} // namespace Parity







