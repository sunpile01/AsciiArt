#include <iostream>
#include "lodepng.h"
#include "ImageLoaders/ImageToAscii.h"
#include "ImageLoaders/BMPLoader.h"
#include "ImageLoaders/PNGLoader.h"
#include "ImageLoaders/JPEGLoader.h"
#include "memory"
#include "Util/Util.h"

int main(int argc, char* argv[]) {

	ImageToAscii* imageLoader = processCommandLine(argc, argv);
	if (!imageLoader) {
		return 1;
	}
	std::cout << imageLoader->getAsciiValues();

	return 0;
}
