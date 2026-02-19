#include <string>
#include <fstream>

#include "core/Logger.hpp"
#include "core/io/json.hpp"
#include "core/Settings.hpp"
using json = nlohmann::json;

bool Settings::autosave;
bool Settings::showLogs;

std::string Settings::background;
std::string Settings::font;
std::string Settings::codeFont;
int Settings::fontSize;
int Settings::codeFontSize;

int Settings::init() {
    std::ifstream app(Settings::appPath);
    std::ifstream settings(Settings::settingsPath);
    std::ifstream themes(Settings::themesPath);
    json appData = json::parse(app);
    json settingsData = json::parse(settings);
    json themesData = json::parse(themes); 

    if (name != appData.at("name")) {
        Logger::log(LogLevel::WARN, "Field \"name\" in app.json have been modified and doesn't match real name");
    }
    if (version != appData.at("version")) {
        Logger::log(LogLevel::WARN, "Field \"vesion\" in app.json have been modified and doesn't match real version");
    }
    if (author != appData.at("author")) {
        Logger::log(LogLevel::WARN, "Field \"author\" in app.json have been modified and doesn't match real author");
    }

    autosave = settingsData.at("autosave");
    showLogs = settingsData.at("showLogs");

    background = themesData.at("background");
    font = themesData.at("font");
    codeFont = themesData.at("codeFont");
    fontSize = themesData.at("fontSize");
    codeFontSize = themesData.at("codeFontSize");

    return 0;
}

void Settings::update() {
    std::ifstream settings(Settings::settingsPath);
    std::ifstream themes(Settings::themesPath);
    json settingsData = json::parse(settings);
    json themesData = json::parse(themes); 

    settingsData["autosave"] = Settings::autosave;
    settingsData["showLogs"] = Settings::showLogs;

    themesData["background"] = Settings::background;
    themesData["font"] = Settings::font;
    themesData["codeFont"] = Settings::codeFont;
    themesData["fontSize"] = Settings::fontSize;
    themesData["codeFontSize"] = Settings::codeFontSize;

    std::ofstream settingsFile(Settings::settingsPath);
    settingsFile << settingsData.dump(4);
    std::ofstream themesFile(Settings::themesPath);
    themesFile << themesData.dump(4);
}