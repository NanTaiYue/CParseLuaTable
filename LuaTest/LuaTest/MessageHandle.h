#pragma once

#include <iostream>
#include <sstream>
#include <lua.hpp>
#include <map>
#include <cstring>

using namespace std;
/*
��Ϣ������
*/

// �ֶ����Ͷ���
enum FieldType
{
	UNKOWN = 0,
	BYTE, // һ���ֽڱ�ʾ�����Ա�ʾboolֵ
	INT,
	FLOAT,
	DOUBLE,
	INT64, // long long����
	STRING, 
	ARRAY, // ��������
};

class CMessageHandle
{
private:
	static unsigned int m_cmd; //Э���
	static map<int,string> m_str;  // ���Ͷ�Ӧ����
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

// Э������ע�ắ��
LUAMOD_API int luaopen_prototype(lua_State*L);

// �������е�lua��
void OpenAllLuaLibs(lua_State* L);