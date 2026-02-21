#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "misc/cpp/imgui_stdlib.h"

#include "core/Events.hpp"
#include "core/Settings.hpp"
#include "core/Logger.hpp"
// #include "core/plugins/Plugins.hpp"
#include "core/io/Files.hpp"

#include "UI/base_elements/Window.hpp"
#include "UI/panels/SettingsWin.hpp"
#include "UI/panels/ProjectWin.hpp"
#include "UI/panels/ExplorerWin.hpp"
#include "UI/panels/Editor.hpp"
#include "UI/panels/Viewer.hpp"
#include "UI/panels/RecentWin.hpp"
#include "UI/panels/Sourcer.hpp"
namespace fs = std::filesystem;

int main() {
    Settings::init();

    Window win(Settings::name, 1920, 1080);

    SettingsWin settingsWin;
    Sourcer sourcer;
    Editor editor;
    Viewer viewer("", 256, 256);
    ProjectWin projectWin(win, editor);
    RecentWin recent;
    ExplorerWin explorer({"all"}, editor, projectWin, viewer);

    while(!glfwWindowShouldClose(win.getWin())) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        sourcer.display(editor);
        settingsWin.display();
        explorer.display();
        editor.display();
        recent.display();
        projectWin.display();
        viewer.display();
        
        explorer.clearSelected();

        win.display();
        glfwSwapBuffers(win.getWin());
    }

    return 0;
}