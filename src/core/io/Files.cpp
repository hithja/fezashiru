#include <fstream>
#include <string>
#include <iostream>

#include "core/Events.hpp"
#include "core/Logger.hpp"
#include "core/io/Files.hpp"

namespace fs = std::filesystem;

Files::Files(fs::path path, std::string data) {
    this->path=path;
    this->data=data;
}

void Files::write(std::string data) {
    std::ofstream y(this->path);

    if (!data.empty()) {
        if(y.is_open()) {
            y << data;
        }
    }
    else {
        if(y.is_open()) {
            y << this->data;
        }
    }

    y.close();
}

std::string Files::read() {
    std::string text;
    std::string output;
    std::ifstream MyFile(this->path);
    while (std::getline(MyFile, text)) {
        output += text + "\n";
    }
    MyFile.close();
    return output;
}