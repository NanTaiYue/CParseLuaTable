BYTE = prototype.BYTE
INT = prototype.INT
FLOAT = prototype.FLOAT
DOUBLE = prototype.DOUBLE
INT64 = prototype.INT64
STRING = prototype.STRING
ARRAY = prototype.ARRAY

-- 定义一个table来产生各种数据表
if ScriptPackage == nil then
    ScriptPackage = {}
end
function ScriptPackage:New(obj)
    local o = {}
    setmetatable(o,{__index=self})
    if obj ~= nil then
        o.__DefineData = obj
    end
    return o
end

print "load ScriptPackage.lua"