#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"
#include "core/Settings.hpp"
#include "core/Events.hpp"
#include "core/plugins/Plugins.hpp"
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

Plugins::Plugins() {
    luaL_openlibs(this->L);
}

Plugins::~Plugins() {
    lua_close(this->L);
}

void Plugins::test() {

}