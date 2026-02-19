#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

struct File {
    std::string type;
    std::string ext;
    fs::path path;
};

class Explorer {
    private:
        std::vector<File> files;
        fs::path rootPath = "/home/hithja";
        fs::path currPath = rootPath;
    public:
        void init(std::vector<std::string> fileTypes);
        void setPath(fs::path path) { this->currPath=path; };
        fs::path getPath() { return this->currPath; };
        std::vector<File> getFiles() { return this->files; };
};