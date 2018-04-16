
require "ProtoPackage"

-- 调用C++注入lua的函数来解析该Person结构并将其序列化为二进制数据,之后再进行反序列化
-- 解析命令，并返回一个解析后的字符串
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
t1.flag = "老婆"
table.insert(pp.tellist,t1)
local t2 = Tel:New()
t2.num = "18308314630"
t2.flag = "老婆"
table.insert(pp.tellist,t2)
local po = Peio:New()
po.name="123"
po.country = "CH"
pp.peio = po
local resultstr = ParseCmd(cmd,pp)