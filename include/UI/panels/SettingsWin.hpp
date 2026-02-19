#pragma once

class SettingsWin {
    private:
        bool showMode = false;
    public:
        SettingsWin();
        void toggle() {this->showMode=!this->showMode;};
        void display();
        bool isOpened() { return this->showMode; }
};
