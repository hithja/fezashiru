#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include "imgui.h"

#include "core/Events.hpp"
#include "core/Settings.hpp"
#include "core/Logger.hpp"
#include "core/io/Files.hpp"
#include "core/io/Recent.hpp"

#include "UI/panels/RecentWin.hpp"

RecentWin::RecentWin() {
    Events::subscribe(EventType::OpenRecent, [this]{this->toggle();});
}

void RecentWin::display() {
    if (this->showMode) {
        ImGui::Begin("Recent Folders");
            std::vector<std::string> recentFiles = recent.getRecent();
            // Prototype
            for (int i = 0; i < recentFiles.size(); i++) {
                ImGui::Selectable(recentFiles[i].c_str());
            }
        ImGui::End();
    }
}