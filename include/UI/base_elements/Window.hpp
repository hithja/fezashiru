#pragma once
#include <GLFW/glfw3.h>
#include <vector>

class Window {
    private:
        GLFWwindow* win;
        int width, height;
    public:
        Window(std::string title, int width, int height);
        ~Window();
        void display();
        std::vector<int> getSize() { return {this->width, this->height}; }
        GLFWwindow* getWin() { return this->win; }
};
