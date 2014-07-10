#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int main(int argc, char **argv)
{
    char buffer[256];
    int error;
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        error = luaL_loadbuffer(L, buffer, strlen(buffer), "line")
            || lua_pcall(L, 0, 0, 0);
        if (error) {
            fprintf(stderr, "%s", lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    }

    lua_close(L);
    return 0;
}
