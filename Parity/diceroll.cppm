export module Parity.DieRoll;

#if defined(__INTELLISENSE__)
	export using namespace Parity;
#else
#endif

export namespace Parity {

export enum class DieRoll : int
{
	One = 1,
	Two,
	Three,
	Four,
	Five,
	Six
};


} // namespace Parity