#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "core/stb_image.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "misc/cpp/imgui_stdlib.h"

#include "core/Events.hpp"
#include "core/Settings.hpp"
#include "core/Logger.hpp"

#include "UI/base_elements/Window.hpp"

Window::Window(std::string title, int width, int height) : width(width), height(height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->win = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (this->win == nullptr) {
        Logger::log(LogLevel::ERROR, "Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(this->win);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger::log(LogLevel::ERROR, "Failed to initialize GLAD");
    }

    glViewport(0, 0, this->width, this->height);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(this->win, true);
    ImGui_ImplOpenGL3_Init();

    io.Fonts->Clear();
    ImFont* font = io.Fonts->AddFontFromFileTTF(Settings::font.c_str(), Settings::fontSize);
    if (font) {
        io.FontDefault = font;
    }
    static std::string imguiIniPath = Settings::confPath + "/imgui.ini";
    io.IniFilename = imguiIniPath.c_str();

    Events::subscribe(EventType::WindowClose, [this]{ glfwSetWindowShouldClose(this->win, true); });
}

Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    Logger::log(LogLevel::DEBUG, "Quited");
}

void Window::display() {
    glClear(GL_COLOR_BUFFER_BIT); 
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}