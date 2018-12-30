function ReadFile(path)
    local f = io.open(path)
    local s = f:read("*a")
    f:close()
    return s
end

if Debug ~= nil then
	Debug.Log("ROM");
end;

local s= ReadFile("/data/local/tmp/script/rom.lua");
print("rom.lua");
print(s);

dofile("/data/local/tmp/script/rom1.lua");
