#include "Util.h"
#include "../ImageLoaders/ImageToAscii.h"
#include "../ImageLoaders/BMPLoader.h"
#include "../ImageLoaders/JPEGLoader.h"
#include "../ImageLoaders/PNGLoader.h"
#include <filesystem>

const std::string IMAGEDIRECTORY = (std::filesystem::current_path()
    .parent_path()
    .parent_path()
    .parent_path() / "pics").string() + "\\";

ImageToAscii* processCommandLine(int argc, char* argv[]) {
    std::string filename;
    std::string filetype;
    bool invert = false;
    bool save = false;
    int levels = 10;

    parseArguments(argc, argv, filename, filetype, invert, save, levels);

    if (filename.empty()) {
        std::cerr << "Usage: " << argv[0] << " -f <filename> -t <filetype> [-invert | -i]\n";
        return nullptr;
    }

    if (filetype.empty()) {
        filetype = deduceFileType(filename);
    }

    ImageToAscii* imageLoader = createImageLoader(filename, filetype, levels);
    if (!imageLoader) {
        return nullptr;
    }

    if (invert) {
        imageLoader->invertGrayScaleMap();
    }
    if (save) {
        imageLoader->setSave();
    }

    return imageLoader;
}

void parseArguments(int argc, char* argv[], std::string& filename, std::string& filetype, bool& invert, bool& save, int& levels) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-f" && i + 1 < argc) {
            filename = argv[++i];
        }
        else if (arg == "-t" && i + 1 < argc) {
            filetype = argv[++i];
        }
        else if (arg == "-invert" || arg == "-i") {
            invert = true;
        }
        else if (arg == "-s" || arg == "-save") {
            save = true;
        }
        else if ((arg == "-levels" || arg =="-l") && i + 1 < argc) {
            levels = std::stoi(argv[++i]);
        }

    }
}

std::string deduceFileType(const std::string& filename) {
    size_t dotPos = filename.find_last_of('.');
    if (dotPos != std::string::npos && dotPos + 1 < filename.size()) {
        return filename.substr(dotPos + 1);
    }
    return "";
}

ImageToAscii* createImageLoader(const std::string& filename, const std::string& filetype, const int& levels) {
    std::string fullPath = IMAGEDIRECTORY + filename;

    if (filetype == "bmp") {
        return new BMPLoader{ fullPath, levels };
    }
    if (filetype == "jpg" || filetype == "jpeg") {
        return new JPEGLoader{ fullPath, levels };
    }
    if (filetype == "png") {
        return new PNGLoader{ fullPath, levels };
    }

    std::cerr << "Error: Unsupported file type '" << filetype << "'\n";
    return nullptr;
}