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
// �ú������漰���ݹ�ĵ���
void CMessageHandle::ParseTable(lua_State* L, int idx, stringstream & ss)
{
	int top = lua_gettop(L);
	if (lua_type(L, idx) == LUA_TTABLE) // �����ǰ��������ֵΪtable
	{
		int tp = lua_getfield(L, idx, "__DefineData"); // ��ȡ��table��__DefineData����table
		cout<<"��õķ���ֵ����Ϊ��"<<tp<<endl;
		int len = lua_rawlen(L, -1);  // ��ȡջ����table�Ĵ�С
		cout<<"��ǰtable�ĳ���Ϊ�� "<<len<<endl;
		for (int i = 1; i <= len; i++) // �������idx����table���е���������,���table�е�������������һ������table�����԰�����i��ȡ������table
		{
			lua_rawgeti(L,-1,i);  // ��ջ��-1����table[i]������ֵѹ�뵱ǰջ��,������Ԫ����
			if (lua_type(L, -1) != LUA_TTABLE)
			{
				lua_pop(L, 1); // ���ѹ������ݲ���һ��table����ѹ��ʧ�ܣ�������Ԫ��
				break;
			}
			// ����ѹ�����һ��table������ȡ����ջ��table�е����ݽṹ
			int sz = lua_rawlen(L, -1);
			if (sz == 2)
			{
				cout<<"����һ���򵥵��������ͽṹ"<<endl;
				lua_rawgeti(L, -1, 1);  // ��ȡ��һ�����ݣ�Ϊ������
				const char * name = lua_tostring(L, -1);
				cout<<"��������"<<name;
				lua_rawgeti(L, -2, 2);
				int tt = lua_tonumber(L, -1);
				// ��һ���൱�ڻ�ȡ��һ��tt_func�ĺ�����Ȼ����һ����ȡ��ֵ�����ո����ͽ���д��
				cout<<", FieldType = "<<m_str[tt];
				lua_pop(L, 2);
				// ��ȡ��nameΪkey��Ӧ��value,ע��:�����tableӦ����idx������Ӧ��table
				lua_getfield(L, idx, name);
				const char* val = lua_tostring(L, -1);
				cout<<", value = "<<val<<endl;
				lua_pop(L, 1);
				// ���ˣ�һ���򵥵��������ͽ������
			}
			else if (sz == 3)
			{
				cout<<"����һ�����ϵ��������ͽṹ"<<endl;
				// �ݹ�ı������ϵ��������ͽṹ��������Ҳ����뵽�򵥵����������н��д���
				ParseTable(L, lua_gettop(L), ss);
			}
			lua_pop(L, 1);
		}
		lua_pop(L, 1);  // ��table��ջ������
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
	m_cmd = lua_tonumber(L, 1);  // ȡ������ĵ�һ��Э���
	if (lua_istable(L, 2)) // ����ڶ���������table�������table
	{
		ParseTable(L, 2, m_ss);
	}
	return 0;
}


// Э������ע�ắ��
LUAMOD_API int luaopen_prototype(lua_State*L)
{
	lua_newtable(L);  // ����һ��table����ջ��
	lua_pushstring(L, "BYTE");
	lua_pushnumber(L, FieldType::BYTE);
	lua_rawset(L, -3); // ֱ�Ӹ�ֵ��������Ԫ����
	lua_pushstring(L, "INT");
	lua_pushnumber(L, FieldType::INT);
	lua_rawset(L, -3); // ֱ�Ӹ�ֵ��������Ԫ����
	lua_pushstring(L, "FLOAT");
	lua_pushnumber(L, FieldType::FLOAT);
	lua_rawset(L, -3); // ֱ�Ӹ�ֵ��������Ԫ����
	lua_pushstring(L, "DOUBLE");
	lua_pushnumber(L, FieldType::DOUBLE);
	lua_rawset(L, -3); // ֱ�Ӹ�ֵ��������Ԫ����
	lua_pushstring(L, "INT64");
	lua_pushnumber(L, FieldType::INT64);
	lua_rawset(L, -3); // ֱ�Ӹ�ֵ��������Ԫ����
	lua_pushstring(L, "STRING");
	lua_pushnumber(L, FieldType::STRING);
	lua_rawset(L, -3); // ֱ�Ӹ�ֵ��������Ԫ����
	lua_pushstring(L, "ARRAY");
	lua_pushnumber(L, FieldType::ARRAY);
	lua_rawset(L, -3); // ֱ�Ӹ�ֵ��������Ԫ����
	return 1;
}

// �����е��Զ���lua��
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