#include "FileManager.h"

#include <vector>


void FileManager::loadFiles() {
    std::ifstream file("File.txt");
    buffer.clearLines();

    std::string line;
    std::vector<std::string> copyVector;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            copyVector.push_back(line);
        }
        file.close();
    }

    buffer.addFileVector(copyVector);
}


void FileManager::saveFiles() {
    std::ofstream file("File.txt");

    std::vector<std::string> saveFile = buffer.getText();

    if (file.is_open()) {
        for (std::string& s : saveFile) {
            file << s << "\n";
        }
        file.close();
    }
}