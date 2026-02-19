#pragma once
#include <functional>
#include <unordered_map>
#include <vector>

enum class EventType {
    WindowClose,
    ProjectFileSelected,
    FileSelected,
    DirSelected,
    SelectFile,
    SelectDir,
    OpenRecent,
    FileSaved,
    SettingsShowMode,
};

class Events {
    public:
        Events();
        using Callback = std::function<void()>;
        static void subscribe(EventType type, Callback cb);
        static void emit(EventType type, std::string status = "");
    private:
        static std::unordered_map<EventType, std::vector<Callback>> listeners;
};
