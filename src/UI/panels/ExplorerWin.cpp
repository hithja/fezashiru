#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>

#include "imgui.h"

#include "core/Events.hpp"
#include "core/Logger.hpp"
#include "core/io/Explorer.hpp"
#include "core/io/Files.hpp"

#include "UI/panels/Editor.hpp"
#include "UI/panels/Viewer.hpp"
#include "UI/panels/ProjectWin.hpp"
#include "UI/panels/ExplorerWin.hpp"
namespace fs = std::filesystem;

std::vector<std::string> imgExt = {"png", "jpg"};

ExplorerWin::ExplorerWin(std::vector<std::string> types, Editor& editor, ProjectWin& projectWin, Viewer& viewer) : types(types), editor(editor), projectWin(projectWin), viewer(viewer) {
    this->exp.init(types);

    Events::subscribe(EventType::SelectFile, [this]{this->toggleFile();});
    
    Events::subscribe(EventType::SelectDir, [this]{this->toggleDir();}); 
    Events::subscribe(EventType::FileSelected, [this]{
        Files file(this->getSelectedPath());
        this->editor.createTab(file.read(), this->getSelectedPath());
        Logger::log(LogLevel::DEBUG, std::string("File Opened: ") + this->selectedPath.string());
    });
    Events::subscribe(EventType::DirSelected, [this]{
        this->projectWin.setPath(this->selectedPath);
        this->projectWin.toggle();
        Logger::log(LogLevel::DEBUG, std::string("Project Opened: ") + this->selectedPath.string());
    });
}

void ExplorerWin::display() {
    if (this->showMode) {
        ImGui::SetNextWindowSize(ImVec2(436, 400), ImGuiCond_FirstUseEver);
        ImGui::Begin("Open");
            ImGui::SeparatorText(this->exp.getPath().c_str());

            if(ImGui::Selectable("[..]")) {
                this->exp.setPath(this->exp.getPath().parent_path());
                this->exp.init(this->types);
            }

            ImGui::BeginChild("Scrolling", ImVec2(0, 300));
                for (const auto& file : exp.getFiles()) {
                    if (file.type == "dir") {
                        if(ImGui::Selectable(file.path.filename().c_str())) {
                            this->exp.setPath(file.path);
                            this->exp.init(this->types);
                        }
                    }
                    else {
                        if (this->mode == ExplorerMode::FILE) {
                            if(this->types[this->currentTypeID] != "all") {
                                if (file.ext == this->types[this->currentTypeID]) {
                                    if(ImGui::Selectable(file.path.filename().c_str()))
                                        this->tempPath=file.path;
                                }
                            }
                            else {
                                if(ImGui::Selectable(file.path.filename().c_str()))
                                    this->tempPath=file.path;
                            }
                        }
                    }
                }
            ImGui::EndChild();

            ImGui::Separator();

            std::vector<const char*> items;
            for (auto& s : types)
                items.push_back(s.c_str());
            
            if (this->mode == ExplorerMode::FILE) {
                ImGui::Text("Ext:");
                ImGui::SameLine();
                ImGui::Combo("##ext", &currentTypeID, items.data(), items.size());
                
                ImGui::BeginDisabled(this->tempPath.empty());
                    if(ImGui::Button("Select")) {
                        auto it = std::find(imgExt.begin(), imgExt.end(), this->tempPath.string().substr(this->tempPath.string().find_last_of(".") + 1));
                        if (it != imgExt.end()) {
                            this->viewer.changeImg(this->tempPath, 256, 256);
                            this->viewer.toogle(true);
                        }
                        else {
                            this->selectedPath=this->tempPath;
                            this->tempPath="";
                            this->showMode=false;
                        
                            Events::emit(EventType::FileSelected);
                        }
                    }   
                ImGui::EndDisabled();
            }
            else {
                if(ImGui::Button("Select Folder")) {
                    this->selectedPath=this->exp.getPath();
                    this->showMode=false;
                        
                    Events::emit(EventType::DirSelected);
                }
            }

            ImGui::SameLine();

            if(ImGui::Button("Cancel"))
                this->showMode=false;

        ImGui::End();
    }
}