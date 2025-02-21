#pragma once
#include "ImageToAscii.h"
#include <string>
class PNGLoader : public ImageToAscii {
public: 
	PNGLoader(std::string filename, int levels) : ImageToAscii(filename, levels){}
	std::string getAsciiValues() override;
};