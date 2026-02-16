export module Parity.Announcement;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <string>
	#include <format>
	#include <print>
	#include <map>
	#include "type-definition.cppm"
#else
	import std; // Standard library import
#endif

export namespace Parity
{

export enum class AnnouncementClause {
	Subtitle,
	ConsequentialAction,
	ConsequentialResult,
	ConsequenctalBullet,
	ConsequentialIndentation,
	ConsequentialItalic,
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

export class Announcement {
public:
	AnnouncementClause clause;
	int consequential_ordinal = 0;
	
	std::string getActionLexicon() {
		return bold(std::vformat("» Action {}:", std::make_format_args(consequential_ordinal)));
	}
	
	std::string getResultLexicon() {
		return bold(std::vformat("« Result {}:", std::make_format_args(consequential_ordinal)));
	}
	
	static void printClauseSubtitle(const std::string& subtitle) {
		std::print("{}\n", subtitle);
	}
	
	void printClauseConsequentialAction(const std::string& content_append_action) {
		std::print("{} {}\n", getActionLexicon(), content_append_action);
	}
	
	void printClauseConsequentialResult(const std::string& content_append_result) {
		std::print("{} {}\n", getResultLexicon(), content_append_result);
	}
	
	void printClauseConsequentialItalic(const std::string& content_of_italic) {
		std::print("{}\n", italic_cyan(content_of_italic));
	}
	
	void action(const std::string& content_append_action) {
		consequential_ordinal++;
		printClauseConsequentialAction(content_append_action);
	}
	
	void result(const std::string& content_append_result) {
		printClauseConsequentialResult(content_append_result);
	}
	
	void bygone(const std::string& content_of_bygone) {
		printClauseConsequentialItalic(content_of_bygone);
	}
	
	void subtitle(const std::string& content_of_subtitle) {
		printClauseSubtitle(content_of_subtitle);
	}
};

} // namespace Parity







