#include "JPEGLoader.h"
#include "jpeg_decoder.h"
#include <fstream>

std::string JPEGLoader::getAsciiValues() {
    std::ifstream file(fileName, std::ios::binary);
    if (!file) {
        std::cerr << "Error: could not open file " << fileName
            << " (" << std::strerror(errno) << ")" << std::endl;
        return "";
    }

    // Read file contents into a buffer
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});
    file.close();

    // Decode the image from the buffer
    Jpeg::Decoder decoder(buffer.data(), buffer.size());
    if (decoder.GetResult() != Jpeg::Decoder::OK) {
        std::cerr << "Error: Failed to decode JPEG image" << std::endl;
        return "";
    }

    int width = decoder.GetWidth();
    int height = decoder.GetHeight();
    unsigned char* imagePixels = decoder.GetImage();
    
    if (!imagePixels) {
        std::cerr << "Error image data is null" << std::endl;
        return "";
    }

    std::stringstream asciiStream;
    int pixelIndex = 0;

    // Each pixel consists of an rgba value and iamge contians the raw pixels so for each pixel we have to process 4 values in the image vector
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            char asciiChar = convertToAscii(imagePixels[pixelIndex], imagePixels[pixelIndex + 1], imagePixels[pixelIndex + 2]);
            asciiStream << asciiChar;
            pixelIndex += 3;
        }
        asciiStream << '\n';
    }

    if (save)
        saveASCIIToFile(asciiStream.str());
    return asciiStream.str();
}