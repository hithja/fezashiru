#pragma once
#include <string>
#include <vector>
#include "imgui.h"

#include "UI/base_elements/Tab.hpp"

class Editor {
    private:
        int isSaved;
        int currTabID;
        std::vector<Tab> tabs;
        
        ImFont* codeFont;
    public:
        Editor();
        ~Editor();

        void display();
        void createTab(std::string text, std::string path) { tabs.push_back(Tab(currTabID+1, path, text)); };
        bool isEdited() { return !isSaved; }
        std::string getText();
        std::string getPath();
};