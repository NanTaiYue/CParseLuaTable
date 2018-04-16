#include <iostream>
#include <lua.hpp>

#include "MessageHandle.h"

using namespace std;

int main()
{
	lua_State* L = luaL_newstate();
	OpenAllLuaLibs(L);
	CMessageHandle::getInstance()->RegisterFunc(L);
	luaL_dofile(L, "main.lua");
	lua_close(L);
	system("pause");
	return 0;
}