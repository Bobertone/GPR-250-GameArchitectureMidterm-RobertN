#include "DataManager.h"
#include <iostream>
#include <fstream>
#include <string>
DataManager::DataManager(std::string filepath)
{
	mFilepath = filepath;
}

float DataManager::getFloat(const std::string& key)
{
    std::ifstream inputFile(mFilepath);
    
    float targetFloat = 1;
    
    if (!inputFile) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    bool foundKeyString = false;

    while (std::getline(inputFile, line)) {
        if (line.find(key) != std::string::npos) {
            foundKeyString = true;
            break;
        }
    }

    if (!foundKeyString) {
        std::cerr << "Key string not found in the file." << std::endl;
        return 1;
    }

    std::getline(inputFile, line);
    targetFloat = std::stof(line);
    

    inputFile.close();
    return targetFloat;
}

std::string DataManager::getString(const std::string& key)
{
    std::ifstream inputFile(mFilepath);

    std::string targetString;

    if (!inputFile) {
        std::cerr << "Failed to open the file." << std::endl;
        return "";
    }

    std::string line;
    bool foundKeyString = false;

    while (std::getline(inputFile, line)) {
        if (line.find(key) != std::string::npos) {
            foundKeyString = true;
            break;
        }
    }

    if (!foundKeyString) {
        std::cerr << "Key string not found in the file." << std::endl;
        return "";
    }

    while (std::getline(inputFile, line)) {
        targetString = line;
    }

    inputFile.close();
    return targetString;
}
