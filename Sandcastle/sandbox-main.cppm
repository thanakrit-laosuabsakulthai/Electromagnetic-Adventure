
#if defined(__INTELLISENSE__)
	#include <iostream>
	#include "sandbox-math.cppm" // Use the shim header for IntelliSense
#else
// Main.cpp
	import Math; // Import the module
	import std;	 // Standard library import
#endif

int main()
{
	std::cout << "Add: " << add(5, 3) << std::endl;
	std::cout << "Multiply: " << multiply(5, 3) << std::endl;

	// helper(5); // This would cause a compiler error
	return 0;
}
