-- 引入ScriptPackage
require "ScriptPackage"
--[[
    一个包结构的构造：
    {字段描述,字段类型,字段结构(可选，针对于复合类型结构)}
    注意：
        这种包结构中不能包含有环的数据字段，否则会造成递归堆栈溢出
]]


Tel = ScriptPackage:New({
    {"num",STRING},  -- 电话号码
    {"flag",STRING},  -- 谁的号码
})
Peio = ScriptPackage:New({
    {"name",STRING},
    {"country",STRING},
})   

Person = ScriptPackage:New({
    {"name",STRING},    -- 子table，字段1：name，字段2：类型
    {"age",INT},
    {"sex",BYTE},
    {"hight",FLOAT},  -- 身高，用float表示，1.72m
    {"money",INT64},  -- 存款多的很
    {"rate",DOUBLE},  -- 存款很多的概率，用DOUBLE表示
    {"tellist",ARRAY,Tel}, -- 联系电话列表
    -- {"parents",ARRAY,Person} -- 自包含，会造成无限递归
    {"peio",Peio},
})

print "load ProtoPackage.lua"