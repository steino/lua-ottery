#include <lua.h>
#include <lauxlib.h>
#include <ottery.h>
#include <string.h>

#define LUAOTTERY_VERSION   			"lua-ottery 0.1"
#define LUAOTTERY_COPYRIGHT 			"Copyright (C) 2014, lua-ottery authors"
#define LUAOTTERY_DESCRIPTION  		"Binding for libottery."

// luaL_setfuncs() from lua 5.2
static void setfuncs (lua_State *L, const luaL_reg*l, int nup)
{
	luaL_checkstack(L, nup, "Too many upvalues.");
	for(; l && l->name; l++) {
		int i;
		for (i = 0; i < nup; i++)
			lua_pushvalue(L, -nup);
		lua_pushcclosure(L, l->func, nup);
		lua_setfield(L, -(nup + 2), l->name);
	}
	lua_pop(L, nup);
}

static int lottery_number(lua_State * L)
{
	unsigned out;
	if(lua_isnumber(L, 1) == 0) {
		out = ottery_rand_uint64();
	} else {
		int num = lua_tointeger(L, 1);
		out = ottery_rand_range64(num);
	}

	lua_pushnumber(L, out);

	return 1;
}

static int lottery_bytes(lua_State * L)
{
	int num = luaL_checkint(L, 1);
	if(num > 0) {
		char buf[num];
		ottery_rand_bytes(buf, sizeof(buf));
		lua_pushstring(L, buf);

		return 1;
	} else {
		luaL_error(L, "Needs more then zero bytes");

		return 0;
	}
}

static const struct luaL_reg E[] =
{
	{ NULL, NULL }
};

static const struct luaL_reg R[] =
{
	{ "number", lottery_number },
	{ "bytes", lottery_bytes },

	{ NULL, NULL }
};

LUALIB_API int luaopen_ottery(lua_State * L)
{
	luaL_register(L, "ottery", E);

	lua_pushliteral(L, LUAOTTERY_VERSION);
	lua_setfield(L, -2, "_VERSION");

	lua_pushliteral(L, LUAOTTERY_COPYRIGHT);
	lua_setfield(L, -2, "_COPYRIGHT");

	lua_pushliteral(L, LUAOTTERY_DESCRIPTION);
	lua_setfield(L, -2, "_DESCRIPTION");

	lua_pushvalue(L, -1);
	setfuncs(L, R, 1);

	return 1;
}
