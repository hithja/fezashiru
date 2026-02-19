#pragma once
#include <string>
#include <fstream>

#include "core/Events.hpp"
#include "core/io/json.hpp"

#include "UI/panels/Editor.hpp"
using json = nlohmann::json;

class Recent {
    private:
        Editor& editor;

        json recent;
    public:
        Recent(Editor& editor) : editor(editor) {
            std::ifstream app("./recent.json");
        }
        ~Recent() {

        }
        void save() {}
        json getRecent() {}
};
