#pragma once
//#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Viewer {
    private:
        GLuint imgTxtr = 0;
        
        bool ret;
        bool showMode=false;

        int width, height;

        std::string imagePath;
    public:
        Viewer(std::string imagePath, int width, int height);
        void toogle(bool sm) { showMode=sm; }
        void display();
        void changeImg(std::string path, int w, int h);
};