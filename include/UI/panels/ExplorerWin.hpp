#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include "core/Events.hpp"
#include "core/io/Explorer.hpp"

#include "UI/panels/ProjectWin.hpp"
#include "UI/panels/Viewer.hpp"
#include "UI/panels/Editor.hpp"
namespace fs = std::filesystem;

enum class ExplorerMode {
    FILE,
    DIR
};

class ExplorerWin {
    private:
        Editor& editor;
        ProjectWin& projectWin;
        Viewer& viewer;
        Explorer exp;

        fs::path selectedPath;
        fs::path tempPath;
        
        ExplorerMode mode;

        std::vector<std::string> types;
        int currentTypeID = 0;
        bool showMode = false;
    public:
        ExplorerWin(std::vector<std::string> types, Editor& editor, ProjectWin& projectWin, Viewer& viewer);
        void toggleFile() {this->showMode=!this->showMode; this->mode=ExplorerMode::FILE; };
        void toggleDir() {this->showMode=!this->showMode; this->mode=ExplorerMode::DIR; };
        void display();
        void clearSelected() { this->selectedPath=""; }
        bool isOpened() { return this->showMode; }
        fs::path getSelectedPath() { return this->selectedPath; }
};