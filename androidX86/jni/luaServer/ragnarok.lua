scriptFile = "/data/local/tmp/ragnarok.lua";

function log(str)
    -- ServerLog(str  .. '\n');
    serverLogger:logStr(str);
end

function reload()
    dofile(scriptFile);
end

log("ragnarok 1.0");
