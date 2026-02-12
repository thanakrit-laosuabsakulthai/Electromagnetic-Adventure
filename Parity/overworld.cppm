export module Parity.World;

#if defined(__INTELLISENSE__) // Use the shim header for IntelliSense
	#include <deque>
	#include <memory>
	#include <print>
	#include "type-definition.cppm"
#else
	import std; // Standard library import
	import Parity.DieRoll;
	import Parity.Biology;
#endif


export namespace Parity {

export struct Rule { 
	virtual ~Rule() = default;
	virtual void execute(class Overworld &world) = 0;
};

export class Overworld
{
	public:
	
	DieRoll die_roll_for_fortune_board = DieRoll::One;
	int fortune_board_multiplier = 1;
	int useFortuneBoardMultiplier() {
		int current_multiplier = fortune_board_multiplier;
		fortune_board_multiplier = 1; // Reset after use
		return current_multiplier;
	}
	
	Humanity playerbase;
	PlayerIdentity active_player = PlayerIdentity::AmethystApprentice;
	
	std::deque<std::unique_ptr<Rule>> event_queue;
	void main_loop()
	{
		while (!event_queue.empty())
		{
			std::unique_ptr<Rule> event = std::move(event_queue.front());
			event_queue.pop_front();
			event->execute(*this);
		}
	}
	
	template <typename Extent_of_Rule, typename... Argument_of_Rule>
	void event(Argument_of_Rule&&... custom_arguments) {
		event_queue.push_back(std::make_unique<Extent_of_Rule>(std::forward<Argument_of_Rule>(custom_arguments)...));
	}
};
} // namespace Parity

