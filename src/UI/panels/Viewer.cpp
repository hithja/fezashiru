//#include <glad/glad.h>   
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "misc/cpp/imgui_stdlib.h"

#include "core/Events.hpp"
#include "core/Image.hpp"

#include "UI/panels/Viewer.hpp"

Viewer::Viewer(std::string imagePath, int width, int height) : imagePath(imagePath), width(width), height(height) {
    this->ret = Image::LoadTextureFromFile(imagePath.c_str(), &imgTxtr, &width, &height);
    IM_ASSERT(ret);
}

void Viewer::changeImg(std::string path, int w, int h) {
    this->ret = Image::LoadTextureFromFile(path.c_str(), &imgTxtr, &w, &h);
    this->width=w;
    this->height=h;
    IM_ASSERT(ret);
}

void Viewer::display() {
    if (this->showMode) {
        ImGui::SetNextWindowSize(ImVec2(this->width+6, this->height+20), ImGuiCond_FirstUseEver);
        ImGui::Begin("Viewer");
            std::string label = this->imagePath;
            ImGui::SeparatorText(label.c_str());
            ImGui::SameLine();
            if (ImGui::Button("Close")) {
                toogle(false);
            }
            ImGui::Image((ImTextureID)(intptr_t)imgTxtr, ImVec2(this->width, this->height));
        ImGui::End();
    }
}