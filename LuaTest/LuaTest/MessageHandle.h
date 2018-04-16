#pragma once

#include <iostream>
#include <sstream>
#include <lua.hpp>
#include <map>
#include <cstring>

using namespace std;
/*
消息处理函数
*/

// 字段类型定义
enum FieldType
{
	UNKOWN = 0,
	BYTE, // 一个字节表示，可以表示bool值
	INT,
	FLOAT,
	DOUBLE,
	INT64, // long long类型
	STRING, 
	ARRAY, // 数组类型
};

class CMessageHandle
{
private:
	static unsigned int m_cmd; //协议号
	static map<int,string> m_str;  // 类型对应名称
public:
	CMessageHandle(void);
	virtual ~CMessageHandle(void);
	static CMessageHandle* getInstance()
	{
		static CMessageHandle m_ins;
		return &m_ins;
	}
	void RegisterFunc(lua_State* L);

public:
	/* */
	static int L_ParseCmd(lua_State* L);
private:
	static void ParseTable(lua_State* L, int idx, stringstream &ss);
};

// 协议类型注册函数
LUAMOD_API int luaopen_prototype(lua_State*L);

// 开启所有的lua库
void OpenAllLuaLibs(lua_State* L);