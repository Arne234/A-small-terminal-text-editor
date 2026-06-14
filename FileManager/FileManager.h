#pragma once
#include "../Buffer/Buffer.h"

#include <fstream>
#include <vector>


class FileManager {
    private:
        Buffer& buffer;

    public:
        FileManager(Buffer& b) : buffer(b) {}

        void loadFiles();
        void saveFiles();
};