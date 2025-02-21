#pragma once
#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
class ImageToAscii {
private:
	// Loaded from loadGrayScaleMap see "Util/grayscalelevel.txt"
	std::vector<char> grayscaleMap;

	char grayScaleToAscii(int grayScaleValue) {
		int index = (grayScaleValue * (grayscaleMap.size() - 1)) / 255;
		return grayscaleMap[index];
	}

	std::filesystem::path getFolderPath(const std::string& folderName) {
		std::filesystem::path exePath = std::filesystem::current_path();
		std::filesystem::path rootPath = exePath.parent_path().parent_path().parent_path(); // Move up 3 levels
		std::filesystem::path folderPath = rootPath / folderName;

		std::cout << "\nFolder path is: " << folderPath << std::endl;

		return folderPath;
	}


	void loadGrayscaleMap(int levels) {
		std::cout << "Going into loadGrayScale now" << std::endl;
		std::filesystem::path utilFolder = getFolderPath("Src");
		std::filesystem::path grayscalemapfile = utilFolder / "Util" / "grayscaleLevels.txt";
		std::ifstream file(grayscalemapfile.string());
		if (!file) {
			std::cerr << "Error: Could not open grayscaleLevels.txt!" << std::endl;
			return;
		}

		std::string line;
		int currentLine = 1;
		while (std::getline(file, line)) {
			if (currentLine == levels) {
				grayscaleMap.assign(line.begin(), line.end());
				break;
			}
			currentLine++;
		}

		if (grayscaleMap.empty()) {
			std::cerr << "Warning: Invalid levels, using default grayscale map of size 10." << std::endl;
			grayscaleMap = { '@', '#', '8', '&', 'o', ':', '*', '.', '-', ' ' };
		}
	}

protected: 
	std::string fileName;
	bool save;
	char convertToAscii(int r, int g, int b) {
		int grayscale = static_cast<int>(0.3 * r + 0.59 * g + 0.11 * b);
		return grayScaleToAscii(grayscale);
	}
	void saveASCIIToFile(std::string asciiValues) {
		std::filesystem::path imageFolder = getFolderPath("Images");
		std::filesystem::path outputFile = imageFolder / fileName; // Correct file path handling

		std::ofstream outfile(outputFile);
		if (outfile) {
			outfile << asciiValues;
			outfile.close();
		}
		else {
			std::cerr << "Error saving to file: " << outputFile << std::endl;
		}
	}
public:
	
	ImageToAscii(std::string& fileName, const int& levels) : fileName{ fileName }, save{false} {
		loadGrayscaleMap(levels);
	}
	virtual std::string getAsciiValues() = 0;

	void invertGrayScaleMap() {
		std::reverse(grayscaleMap.begin(), grayscaleMap.end());
	}
	void setGrayscaleMap(const std::vector<char>& newMap) {
		grayscaleMap = newMap;
	}

	void setSave() { save = !save; }
	
	virtual ~ImageToAscii() = default;
};