#pragma once
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

class Files {
    public:
        Files(fs::path path, std::string data = "");

        void write(std::string data = "");
        void setPath(std::string newPath) { this->path=newPath; };

        std::string read();
        std::string getPath() { return this->path; };
    private:
        fs::path path;
        std::string data;
};