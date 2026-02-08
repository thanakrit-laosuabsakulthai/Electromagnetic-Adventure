// Math.cppm
export module Math; // Defines the module name

#if defined(__INTELLISENSE__)
	#include <iostream> // Use the shim header for IntelliSense
#else
	import std; // Use the actual module for the compiler
#endif

// Everything here is private to the module by default.

// Exported function (publicly available)
export int add(int a, int b)
{
	return a + b;
}

// Another exported function
export int multiply(int a, int b)
{
	return a * b;
}

// A private function (cannot be used outside this file)
int helper(int a)
{
	return a * 2;
}
