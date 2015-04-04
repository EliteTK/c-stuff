/*
 * Copyright (C) 2015  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */
#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int main(int argc, char **argv)
{
	char buffer[256];

	lua_State *state = luaL_newstate();
	luaL_openlibs(state);

	while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		if (luaL_loadbuffer(state, buffer, strlen(buffer), "line") || lua_pcall(state, 0, 0, 0)) {
			fprintf(stderr, "%s", lua_tostring(state, -1));
			lua_pop(state, 1);
		}
	}

	lua_close(state);
	return 0;
}
