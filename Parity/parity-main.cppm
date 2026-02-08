
#if defined(__INTELLISENSE__)
	#include <iostream>
	#include <format>
	#include <print>
	#include "parity-engine.cppm"
#else
	import std; // Standard library import
	import Electromagnetic.Engine;
#endif

int main() {
	Electromagnetic::Parity engine;

	// Rulestack 1: Initialize with Lucky Board
	engine.push<Electromagnetic::LuckyBoardRule>();

	std::print("--- Press Enter to start ---\n");
	
	while (!engine.is_done()) {
		std::cin.get(); // Wait for user "Enter"
		std::print("----------------------------\n");
		engine.step();
	}

	std::print("--- Adventure Awaits ---\n");
	return 0;
}