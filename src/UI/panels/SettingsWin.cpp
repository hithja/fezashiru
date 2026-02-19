#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "imgui.h"

#include "core/Events.hpp"
#include "core/Settings.hpp"
#include "core/io/Links.hpp"

#include "UI/panels/SettingsWin.hpp"

SettingsWin::SettingsWin() {
    Events::subscribe(EventType::SettingsShowMode, [this]{this->toggle();});
}

void SettingsWin::display() {
    if (this->showMode) {
        ImGui::Begin("Settings");
            ImGui::SeparatorText("Editor");

            ImGui::SeparatorText("Files");
            if (ImGui::Checkbox("Autosave", &Settings::autosave))
                Settings::update();
            if (ImGui::Checkbox("Show Logs", &Settings::showLogs))
                Settings::update();

            ImGui::SeparatorText("Styles");

            ImGui::Text("Font Size");
            ImGui::SameLine();
            if (ImGui::InputInt("###fontSize", &Settings::fontSize, 2))
                Settings::update();
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Restart editor to apply changes");

            ImGui::Text("Editor Font Size");
            ImGui::SameLine();
            if (ImGui::InputInt("###editorFontSize", &Settings::codeFontSize, 2))
                Settings::update();
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Restart editor to apply changes");
            
            ImGui::SeparatorText("About");
            ImGui::Text("Version: %s", Settings::version.c_str());
            ImGui::Text("Developer: %s", Settings::author.c_str());

            if (ImGui::Button("Discord")) {
                Links::open("https://discord.gg/4UmmWeQfWT");
            }
            if (ImGui::Button("Github")) {
                Links::open("https://github.com/hithja/fezashiru");
            }
        ImGui::End();
    }
}