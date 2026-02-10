export module Parity;

#if defined(__INTELLISENSE__)
	#include <deque>
	#include <memory>
	#include <print>
	#include "diceroll.cppm" // Use the shim header for IntelliSense
	export using namespace Parity;
#else
	import std; // Standard library import
	export import Parity.DieRoll;
#endif

export namespace Parity {

export struct Rule { 
	virtual ~Rule() = default;
	virtual void execute(class Overworld &world) = 0;
};

export class Overworld
{
	public:
	
	DieRoll die_roll_for_random_board = DieRoll::One;
	
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
};

} // namespace Parity