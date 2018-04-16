#include "MessageHandle.h"

unsigned int CMessageHandle::m_cmd = 0;

map<int,string> CMessageHandle::m_str = map<int,string>();

CMessageHandle::CMessageHandle(void)
{
	m_str[FieldType::BYTE] = "BYTE";
	m_str[FieldType::INT] = "INT";
	m_str[FieldType::FLOAT] = "FLOAT";
	m_str[FieldType::DOUBLE] = "DOUBLE";
	m_str[FieldType::INT64] = "INT64";
	m_str[FieldType::STRING] = "STRING";
	m_str[FieldType::ARRAY] = "ARRAY";
}


CMessageHandle::~CMessageHandle(void)
{
}

void CMessageHandle::RegisterFunc(lua_State* L)
{
	const struct luaL_Reg ll[] = {
		{"ParseCmd",CMessageHandle::L_ParseCmd},
		{"NULL",NULL},
	};
	const struct luaL_Reg *iter = ll;
	for (; iter->func; ++iter)
	{
		lua_register(L, iter->name, iter->func);
	}
}
// 该函数会涉及到递归的调用
void CMessageHandle::ParseTable(lua_State* L, int idx, stringstream & ss)
{
	int top = lua_gettop(L);
	if (lua_type(L, idx) == LUA_TTABLE) // 如果当前索引处的值为table
	{
		int tp = lua_getfield(L, idx, "__DefineData"); // 获取该table中__DefineData处的table
		cout<<"获得的返回值类型为："<<tp<<endl;
		int len = lua_rawlen(L, -1);  // 获取栈顶的table的大小
		cout<<"当前table的长度为： "<<len<<endl;
		for (int i = 1; i <= len; i++) // 遍历这个idx处的table的中的所有数据,这个table中的所有数据又是一个个的table，所以按索引i来取出所有table
		{
			lua_rawgeti(L,-1,i);  // 将栈顶-1处的table[i]索引的值压入当前栈顶,不触发元方法
			if (lua_type(L, -1) != LUA_TTABLE)
			{
				lua_pop(L, 1); // 如果压入的数据不是一个table，则压入失败，弹出该元素
				break;
			}
			// 否则压入的是一个table则依次取出该栈顶table中的数据结构
			int sz = lua_rawlen(L, -1);
			if (sz == 2)
			{
				cout<<"这是一个简单的数据类型结构"<<endl;
				lua_rawgeti(L, -1, 1);  // 获取第一个数据，为类型名
				const char * name = lua_tostring(L, -1);
				cout<<"类型名："<<name;
				lua_rawgeti(L, -2, 2);
				int tt = lua_tonumber(L, -1);
				// 这一步相当于获取了一个tt_func的函数，然后将下一步获取的值，按照该类型进行写入
				cout<<", FieldType = "<<m_str[tt];
				lua_pop(L, 2);
				// 获取以name为key对应的value,注意:这里的table应该是idx索引对应的table
				lua_getfield(L, idx, name);
				const char* val = lua_tostring(L, -1);
				cout<<", value = "<<val<<endl;
				lua_pop(L, 1);
				// 至此，一个简单的数据类型解析完成
			}
			else if (sz == 3)
			{
				cout<<"这是一个复合的数据类型结构"<<endl;
				// 递归的遍历复合的数据类型结构，其最终也会进入到简单的数据类型中进行处理
				ParseTable(L, lua_gettop(L), ss);
			}
			lua_pop(L, 1);
		}
		lua_pop(L, 1);  // 将table从栈顶弹出
	}
	if (top != lua_gettop(L))
	{
		lua_settop(L, top);
	}
}

int CMessageHandle::L_ParseCmd(lua_State* L)
{
	m_cmd = 0;
	stringstream m_ss;
	int top = lua_gettop(L);
	if (top < 2)
	{
		cout<<"top < 2"<< endl;
		return 0;
	}
	m_cmd = lua_tonumber(L, 1);  // 取出传入的第一个协议号
	if (lua_istable(L, 2)) // 如果第二个参数是table，则解析table
	{
		ParseTable(L, 2, m_ss);
	}
	return 0;
}


// 协议类型注册函数
LUAMOD_API int luaopen_prototype(lua_State*L)
{
	lua_newtable(L);  // 创建一个table放在栈顶
	lua_pushstring(L, "BYTE");
	lua_pushnumber(L, FieldType::BYTE);
	lua_rawset(L, -3); // 直接赋值，不触发元方法
	lua_pushstring(L, "INT");
	lua_pushnumber(L, FieldType::INT);
	lua_rawset(L, -3); // 直接赋值，不触发元方法
	lua_pushstring(L, "FLOAT");
	lua_pushnumber(L, FieldType::FLOAT);
	lua_rawset(L, -3); // 直接赋值，不触发元方法
	lua_pushstring(L, "DOUBLE");
	lua_pushnumber(L, FieldType::DOUBLE);
	lua_rawset(L, -3); // 直接赋值，不触发元方法
	lua_pushstring(L, "INT64");
	lua_pushnumber(L, FieldType::INT64);
	lua_rawset(L, -3); // 直接赋值，不触发元方法
	lua_pushstring(L, "STRING");
	lua_pushnumber(L, FieldType::STRING);
	lua_rawset(L, -3); // 直接赋值，不触发元方法
	lua_pushstring(L, "ARRAY");
	lua_pushnumber(L, FieldType::ARRAY);
	lua_rawset(L, -3); // 直接赋值，不触发元方法
	return 1;
}

// 打开所有的自定义lua库
static const luaL_Reg selfLib[] = {
	{"prototype",luaopen_prototype},
	{"NULL",NULL},
};
void OpenAllLuaLibs(lua_State* L)
{
	luaL_openlibs(L);
	const luaL_Reg* libs = selfLib;
	for (;libs->func; ++libs)
	{
		luaL_requiref(L, libs->name, libs->func, 1);
		lua_pop(L, 1);
	}
}