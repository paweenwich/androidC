scriptFile = "/data/local/tmp/ragnarok.lua";

function log(str)
    -- ServerLog(str  .. '\n');
    serverLogger:logStr(str);
end

function string.starts(String,Start)
   return string.sub(String,1,string.len(Start))==Start
end

function string.ends(String,End)
   return End=='' or string.sub(String,-string.len(End))==End
end

function GetStaticField(klassName,fieldName)
	local mClass = monoEval:GetClassFromName("",klassName);
	return monoEval:GetFieldAsString(mClass,nil,fieldName);
end;

function reload()
    dofile(scriptFile);
end


function loadMono()
    monoHandle = MonoLoad();

end;

log("ragnarok 1.0");
