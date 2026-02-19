#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include "imgui.h"

#include "core/Events.hpp"
#include "core/Settings.hpp"
#include "core/Logger.hpp"
#include "core/io/Files.hpp"

#include "UI/panels/Editor.hpp"
#include "UI/panels/Sourcer.hpp"
namespace fs = std::filesystem;

void Sourcer::display(Editor &editor) {
    ImGui::Begin("Sourcer");
        ImGui::Text("%s %s", Settings::name.c_str(), Settings::version.c_str());
        ImGui::SeparatorText("Files");
        if (ImGui::Button("Open File"))
            Events::emit(EventType::SelectFile);
        if (ImGui::Button("Open Folder"))
            Events::emit(EventType::SelectDir);
        if (ImGui::Button("Open Recent"))
            Events::emit(EventType::OpenRecent);
        
        if (ImGui::Button("Save") || (ImGui::IsKeyPressed(ImGuiKey_LeftCtrl) && ImGui::IsKeyPressed(ImGuiKey_S)) || (Settings::autosave)) {
            if (!editor.getPath().empty()) {
                Files file(fs::path(editor.getPath()));
                file.write(editor.getText());
                Events::emit(EventType::FileSaved);
            }
        }

        if (ImGui::Button("Save As")) {}
        
        ImGui::SeparatorText("Other");
        if (ImGui::Button("Settings"))
            Events::emit(EventType::SettingsShowMode);
        
        if (ImGui::Button("Close"))
            Events::emit(EventType::WindowClose);
                
    ImGui::End();
}