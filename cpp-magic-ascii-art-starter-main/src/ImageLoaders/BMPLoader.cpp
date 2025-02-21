#include "BMPLoader.h"
#include "EasyBMP.h"
std::string BMPLoader::getAsciiValues() {
	
	BMP image;
	image.ReadFromFile(fileName.c_str());
	int width = image.TellWidth();
	int height = image.TellHeight();

	std::stringstream asciiStream;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			char asciiChar = convertToAscii(image(j, i)->Red, image(j, i)->Green, image(j, i)->Blue);
			asciiStream << asciiChar;
		}
		asciiStream << '\n'; // New line after each row
	}
	if (save)
		saveASCIIToFile(asciiStream.str());
	return asciiStream.str();
}