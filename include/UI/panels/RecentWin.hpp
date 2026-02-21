#pragma once

#include "core/io/Recent.hpp"

class RecentWin {
    private:
        bool showMode = false;
        Recent recent;
    public:
        RecentWin();
        void toggle() { this->showMode=!this->showMode; }
        void display();
};
