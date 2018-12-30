function ReadFile(path)
    local f = io.open(path)
    local s = f:read("*a")
    f:close()
    return s
end

function ROM_Reload()
	local s = ReadFile("/data/local/tmp/script/rom.lua");
	local f = loadstring(s);
	f();
end;

if Debug ~= nil then
	Debug.Log("ROM Loaded");
end;

print("ROM Loaded");
