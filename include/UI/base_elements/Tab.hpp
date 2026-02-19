#pragma once 
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

class Tab {
    private:
        int id;
        std::string path;
        std::string name;
        std::string text;
    public:
        Tab(int id, std::string path, std::string text);
        std::string getName() { return this->name; };
        std::string getPath() { return this->path; };
        std::string& getText() { return this->text; };
        int getTabID() { return this->id; };
        void setText(std::string& txt) { text = txt; };
        void setPath(std::string& p) { path = p; };

        bool isSaved = false;
        bool isOpen=true;
};