
require "ProtoPackage"

-- ����C++ע��lua�ĺ�����������Person�ṹ���������л�Ϊ����������,֮���ٽ��з����л�
-- �������������һ����������ַ���
local cmd = 0x1000
local pp = Person:New()
pp.name = "zhouhengbo"
pp.age = 26
pp.sex = 1
pp.hight = 1.72
pp.money = 88888888
pp.rate = 98.99999
pp.tellist = {}
local t1 = Tel:New()
t1.num = "17716137804"
t1.flag = "����"
table.insert(pp.tellist,t1)
local t2 = Tel:New()
t2.num = "18308314630"
t2.flag = "����"
table.insert(pp.tellist,t2)
local po = Peio:New()
po.name="123"
po.country = "CH"
pp.peio = po
local resultstr = ParseCmd(cmd,pp)