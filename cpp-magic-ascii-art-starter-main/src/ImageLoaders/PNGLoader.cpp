#include "PNGLoader.h"
#include "lodepng.h"
#include <iostream>

std::string PNGLoader::getAsciiValues() {
	std::vector<unsigned char> png;
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;
	lodepng::State state; //optionally customize this one

	unsigned error = lodepng::load_file(png, fileName); //load the image file with given filename
	if (!error) error = lodepng::decode(image, width, height, state, png);

	//if there's an error, display i
	if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	std::stringstream asciiStream;
	int pixelIndex = 0;
	// Each pixel consists of an rgba value and iamge contians the raw pixels so for each pixel we have to process 4 values in the image vector
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			char asciiChar = convertToAscii(image[pixelIndex + 1], image[pixelIndex + 2], image[pixelIndex + 3]);
			asciiStream << asciiChar;
			pixelIndex += 4;
		}
		asciiStream << '\n';
	}

	if (save)
		saveASCIIToFile(asciiStream.str());
	return asciiStream.str();
}