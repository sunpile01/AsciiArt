#pragma once
#include <string>

class ImageToAscii; // Forward declaration

ImageToAscii* processCommandLine(int argc, char* argv[]);
void parseArguments(int argc, char* argv[], std::string& filename, std::string& filetype, bool& invert, bool& save, int& levels);
std::string deduceFileType(const std::string& filename);
ImageToAscii* createImageLoader(const std::string& filename, const std::string& filetype, const int& levels);
