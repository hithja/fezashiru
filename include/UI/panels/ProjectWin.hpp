#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

#include "core/io/Explorer.hpp"

#include "UI/base_elements/Window.hpp"
#include "UI/panels/Editor.hpp"
namespace fs = std::filesystem;

class ProjectWin {
    private:
        Window& win;
        Editor& editor;

        fs::path selectedFilePath;

        bool showMode = false;
        
    public:
        fs::path path;

        ProjectWin(Window& win, Editor& editor);
        void setPath(fs::path path) { this->path=path; }
        void toggle() { this->showMode=true; }
        void display();
        void displayTree(fs::path path);
};
