#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

#include "UI/panels/ExplorerWin.hpp"
#include "core/io/Explorer.hpp"
namespace fs = std::filesystem;

void Explorer::init(std::vector<std::string> fileTypes) {
    this->files.clear();
    for (const auto& entry : fs::directory_iterator(this->currPath)) {
        if(fs::is_directory(entry.path()))
            this->files.push_back({"dir", "none", entry.path()});
        else
            this->files.push_back({"file", entry.path().string().substr(entry.path().string().find_last_of(".") + 1), entry.path()}); // Can be some bugs
    }
}