-- ����ScriptPackage
require "ScriptPackage"
--[[
    һ�����ṹ�Ĺ��죺
    {�ֶ�����,�ֶ�����,�ֶνṹ(��ѡ������ڸ������ͽṹ)}
    ע�⣺
        ���ְ��ṹ�в��ܰ����л��������ֶΣ��������ɵݹ��ջ���
]]


Tel = ScriptPackage:New({
    {"num",STRING},  -- �绰����
    {"flag",STRING},  -- ˭�ĺ���
})
Peio = ScriptPackage:New({
    {"name",STRING},
    {"country",STRING},
})   

Person = ScriptPackage:New({
    {"name",STRING},    -- ��table���ֶ�1��name���ֶ�2������
    {"age",INT},
    {"sex",BYTE},
    {"hight",FLOAT},  -- ��ߣ���float��ʾ��1.72m
    {"money",INT64},  -- ����ĺ�
    {"rate",DOUBLE},  -- ���ܶ�ĸ��ʣ���DOUBLE��ʾ
    {"tellist",ARRAY,Tel}, -- ��ϵ�绰�б�
    -- {"parents",ARRAY,Person} -- �԰�������������޵ݹ�
    {"peio",Peio},
})

print "load ProtoPackage.lua"