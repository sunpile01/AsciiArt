#pragma once
#include "ImageToAscii.h"
#include <vector>
class BMPLoader : public ImageToAscii {
public:
	explicit BMPLoader(std::string filename, int levels): ImageToAscii(filename, levels){}
	std::string getAsciiValues() override;
};