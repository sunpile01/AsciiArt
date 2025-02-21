#pragma once
#include "ImageToAscii.h"
class JPEGLoader : public ImageToAscii {

public:
	JPEGLoader(std::string filename, int levels) : ImageToAscii(filename, levels) {}
	std::string getAsciiValues() override;
};