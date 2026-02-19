#pragma once
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

class Plugins {
    private:
        lua_State* L = luaL_newstate();
    public:
        Plugins();
        ~Plugins();
        void test();
};

