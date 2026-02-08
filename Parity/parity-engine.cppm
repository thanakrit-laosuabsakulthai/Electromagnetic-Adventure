export module Electromagnetic.Engine;

#if defined(__INTELLISENSE__)
	#include <vector>
	#include <variant>
	#include <iostream>
	#include <format>
	#include <print>
	#include "parity-core.cppm"
#else
	import std; // Standard library import
	import Electromagnetic.Core;
#endif

export namespace Electromagnetic
{
	class Parity;
	class RollRule;
	class ApplyResultRule;
	class GainGoldRule;
	
	class Rule {
	public:
		virtual ~Rule() = default;
		virtual void foresight(Parity& engine) {}
		virtual void enact(Parity& engine) = 0;
		virtual void hindsight(Parity& engine) {}
	};
	
	using RulePointer = std::unique_ptr<Rule>;
	
	class Parity {
		std::vector<RulePointer> stack;
		Overworld world;
		Internationalization dialect;
		
		public:
		void push(RulePointer rule) { stack.push_back(std::move(rule)); }
		
		// Templated convenience overload: construct and push a rule of type R
		template<typename R, typename... Args>
		void push(Args&&... args) {
			static_assert(std::is_base_of_v<Rule, R>, "R must derive from Rule");
			push(std::make_unique<R>(std::forward<Args>(args)...));
		}
		
		void step() {
			if (stack.empty()) return;
			auto rule = std::move(stack.back());
			stack.pop_back();

			rule->foresight(*this);
			rule->enact(*this);
			rule->hindsight(*this);
		}
		
		bool is_done() const { return stack.empty(); }
		
		// Helper methods for rules to interact with the engine
		void push_rule(RulePointer rule) { push(std::move(rule)); }
		Overworld& get_world() { return world; }
		Internationalization& get_dialect() { return dialect; }
	};
	
	class RollRule : public Rule {
	public:
		void foresight(Parity& engine) override {
			engine.get_dialect().translate("rule.roll");
			// Mock choices list print
			std::print("\t[ ] ...\n\t[ ] ...\n\t[ ] ...\n\t[ ] Gain 1 Gold Coin.\n\t[ ] ...\n");
		}
		void enact(Parity& engine) override {
			engine.get_world().last_die_roll = 4; // Mocked roll
		}
		void hindsight(Parity&) override {}
	};

	class GainGoldRule : public Rule {
	public:
		void foresight(Parity& engine) override {
			engine.get_dialect().translate("rule.gain_gold");
		}
		void enact(Parity& engine) override {
			engine.get_world().gold += 1;
		}
		void hindsight(Parity& engine) override {
			engine.get_dialect().translate("atomic.give_gold", engine.get_world().player_name);
		}
	};
	
	class ApplyResultRule : public Rule {
	public:
		void foresight(Parity& engine) override {}
		void enact(Parity& engine) override {
			if (engine.get_world().last_die_roll == 4) {
				engine.push_rule(std::make_unique<GainGoldRule>());
			}
		}
		void hindsight(Parity&) override {}
	};
	
	class LuckyBoardRule : public Rule {
	public:
		void foresight(Parity& engine) override {
			engine.get_dialect().translate("action.lucky", engine.get_world().player_name);
		}
		void enact(Parity& engine) override {
			engine.push_rule(std::make_unique<RollRule>());
			engine.push_rule(std::make_unique<ApplyResultRule>());
		}
		void hindsight(Parity& ) override {}
	};

}