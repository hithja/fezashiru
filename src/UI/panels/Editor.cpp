#include <fstream>
#include <vector>
#include <filesystem>

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include "core/Events.hpp"
#include "core/Settings.hpp"

#include "UI/base_elements/Tab.hpp"
#include "UI/panels/Editor.hpp"
namespace fs = std::filesystem;

Editor::Editor() {
    ImGuiIO& io = ImGui::GetIO();
    this->codeFont=io.Fonts->AddFontFromFileTTF(Settings::codeFont.c_str(), Settings::codeFontSize);

    Events::subscribe(EventType::FileSaved, [this]{ this->isSaved=false; });
}

void Editor::display() {
    ImGui::Begin("Code");
        if (ImGui::BeginTabBar("TabBar")) {
            if (tabs.size() == 0) {
                ImGui::Text("No files opened! Open it with Sourcer");
            }

            for (int i = 0; i < tabs.size(); ) {
                auto& tab = tabs[i];

                if (!tab.isOpen) {
                    tabs.erase(tabs.begin() + i);
                    continue;
                }

                if (ImGui::BeginTabItem(tab.getName().c_str(), &tab.isOpen, tab.isSaved)) {
                    currTabID = tab.getTabID();

                    
                    ImGui::PushFont(this->codeFont);

                    if (ImGui::InputTextMultiline("##code", &tab.getText(), ImGui::GetContentRegionAvail())) {
                        this->isSaved = true;
                    }
                    ImGui::PopFont();
                    ImGui::EndTabItem();
                    tab.isSaved = this->isSaved;
                }
                i++;
            }
            ImGui::EndTabBar();
        }
    ImGui::End();
}

std::string Editor::getText() {
    for (auto& tab : tabs)
        if (tab.getTabID() == currTabID)
            return tab.getText();
    return "";
}

std::string Editor::getPath() {
    for (auto& tab : tabs)
        if (tab.getTabID() == currTabID)
            return tab.getPath();
    return "";
}