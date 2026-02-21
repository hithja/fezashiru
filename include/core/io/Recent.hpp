#pragma once
#include <string>
#include <fstream>

#include "core/Events.hpp"
#include "core/io/json.hpp"

#include "UI/panels/Editor.hpp"
using json = nlohmann::json;

class Recent {
    private:
        json recentData;
        std::vector<std::string> recent;
    public:
        Recent() {
            std::ifstream recentPath("./recent.json");
            this->recentData = json::parse(recentPath);
            this->recent = this->recentData["recent"];
        }
        void addFilePath(std::string path) {
            this->recent.push_back(path);
        }
        void save() { 
            this->recentData["recent"] = this->recent;

            std::ofstream recentFile("./recent.json");
            recentFile << this->recentData.dump(4);
        } 
        std::vector<std::string> getRecent() { return this->recentData["recent"]; }
};
