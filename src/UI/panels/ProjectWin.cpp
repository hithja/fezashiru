#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

#include "imgui.h"

#include "core/Events.hpp"
#include "core/Logger.hpp"
#include "core/io/Files.hpp"

#include "UI/base_elements/Window.hpp"
#include "UI/panels/Editor.hpp"
#include "UI/panels/ProjectWin.hpp"
namespace fs = std::filesystem;

void drop_callback(GLFWwindow* window, int count, const char** paths) {
     auto* self = static_cast<ProjectWin*>(
        glfwGetWindowUserPointer(window)
    );
    if (!self) return;

    std::error_code ec;

    for (int i = 0;  i < count;  i++) {
        fs::path src(paths[i]);
        fs::path dst = self->path / src.filename();
        fs::copy_file(src, dst, fs::copy_options::overwrite_existing, ec);
        fs::remove(src, ec);
    }
}

ProjectWin::ProjectWin(Window& win, Editor& editor) : editor(editor), win(win) {
    glfwSetWindowUserPointer(win.getWin(), this);
    glfwSetDropCallback(win.getWin(), drop_callback);


    Events::subscribe(EventType::ProjectFileSelected, [this]{
        Files file(this->selectedFilePath);
        this->editor.createTab(file.read(), this->selectedFilePath);
        Logger::log(LogLevel::DEBUG, std::string("File Opened: ") + this->selectedFilePath.string());
    });
}

void ProjectWin::displayTree(fs::path path) {
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            if (ImGui::TreeNode(entry.path().filename().c_str())) {
                displayTree(entry.path());
                ImGui::TreePop();
            }
        }
        else {
            if (ImGui::Selectable(entry.path().filename().c_str())) {
                this->selectedFilePath=entry.path().c_str();
                Events::emit(EventType::ProjectFileSelected);
            }
        }
    }
}

void ProjectWin::display() {
    if (this->showMode) {
        ImGui::Begin("Project");
            std::string label = "/" + this->path.filename().string();
            ImGui::SeparatorText(label.c_str());

            displayTree(this->path);
        ImGui::End();
    }
}