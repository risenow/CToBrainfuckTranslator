#pragma once
#include <string>

//in the future it can be used as base class for such classed as CVar, CFunc, etc.
class CElement {
public:
	std::string getSignature() {
		return signature;
	}
protected:
	std::string signature;
};