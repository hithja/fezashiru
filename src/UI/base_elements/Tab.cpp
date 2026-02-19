#include <vector>
#include <string>
#include <filesystem>

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include "UI/base_elements/Tab.hpp"
namespace fs = std::filesystem;

Tab::Tab(int id, std::string path, std::string text) {
    this->id=id;
    this->path=path;
    this->text=text;
    this->name=fs::path(path).filename().c_str();
}