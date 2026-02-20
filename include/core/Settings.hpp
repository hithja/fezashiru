#pragma once
#include <string>

class Settings {
    private:
    public:
        inline static std::string name = "Fezashiru";
        inline static std::string version = "pre-alpha 0226a";
        inline static std::string author = "hithja";

        inline static std::string confPath = "./config";
        inline static std::string appPath = confPath + "/app.json";
        inline static std::string settingsPath = confPath + "/settings.json";
        inline static std::string themesPath = confPath + "/themes.json";

        // Booleans
        static bool autosave;
        static bool showLogs;

        static std::string background;
        static std::string font;
        static std::string codeFont;
        static int fontSize;
        static int codeFontSize;
        
        static int init();
        static void update();
};
