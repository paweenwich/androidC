function log(str)
    ServerLog(str  .. '\n');
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

function Test()
	local mClass = monoEval:GetClassFromName("","UIManagerScript");
	log(monoEval:GetFieldAsString(mClass,nil,"static_string"));
	log("instance=" .. monoEval:GetFieldAsInt(mClass,nil,"instance"));
	log("_instance=" .. monoEval:GetPropertyAsInt(mClass,nil,"_instance"));
	local instance = monoEval:GetFieldAsInt(mClass,nil,"instance");
	local mobj = monoEval:IntToMonoObject(instance);
	--log(monoEval:GetFieldAsString(mClass,mobj,"name"));
	log("strDebug=" .. monoEval:GetFieldAsInt(mClass,mobj,"strDebug"));
	log("log=" .. monoEval:GetFieldAsInt(mClass,mobj,"log"));
	log("instance_int=" .. monoEval:GetFieldAsInt(mClass,mobj,"instance_int"));
	monoEval:SetFieldInt(mClass,mobj,"instance_int",5555);
	log("instance_int=" .. monoEval:GetFieldAsInt(mClass,mobj,"instance_int"));
	log("instance_string=" .. monoEval:GetFieldAsString(mClass,mobj,"instance_string"));
	log("static_int=" .. monoEval:GetFieldAsInt(mClass,nil,"static_int"));
	monoEval:SetFieldInt(mClass,nil,"static_int",5555);
	monoEval:SetFieldString(mClass,nil,"static_string","New String");
	monoEval:SetFieldString(mClass,mobj,"instance_string","New String");
	log("static_int=" .. monoEval:GetFieldAsInt(mClass,nil,"static_int"));
	monoEval:SetProperty(mClass,nil,"_instance",0);
	log("_instance=" .. monoEval:GetPropertyAsInt(mClass,nil,"_instance"));
	
	local pClass = monoEval:GetClassFromName("UnityEngine","MonoBehaviour");
	log("name=" .. monoEval:GetFieldAsString(pClass,mobj,"name"));
	log("name=" .. monoEval:GetPropertyAsString(mClass,mobj,"name"));
	
end;

function Check()
	local mClass = monoEval:GetClassFromName("CodeStage.AntiCheat.Detectors","InjectionDetector");
	log("instancesInScene=" .. monoEval:GetFieldAsInt(mClass,nil,"instancesInScene"));
	log("Instance=" .. monoEval:GetPropertyAsInt(mClass,nil,"Instance"));
	log("hexTable=" .. monoEval:GetFieldAsInt(mClass,nil,"hexTable"));
	log("isRunning=" .. monoEval:GetFieldAsInt(mClass,nil,"isRunning"));
	log("autoStart=" .. monoEval:GetFieldAsInt(mClass,nil,"autoStart"));
	log("keepAlive=" .. monoEval:GetFieldAsInt(mClass,nil,"keepAlive"));
	log("autoDispose=" .. monoEval:GetFieldAsInt(mClass,nil,"autoDispose"));
	log("detectionEventHasListener=" .. monoEval:GetFieldAsInt(mClass,nil,"detectionEventHasListener"));
	log("started=" .. monoEval:GetFieldAsInt(mClass,nil,"started"));	
	local mClass2 = monoEval:GetClassFromName("CodeStage.AntiCheat.Detectors","ActDetectorBase");
	log("CONTAINER_NAME=" .. monoEval:GetFieldAsString(mClass2,nil,"CONTAINER_NAME"));	
	log("detectorsContainer=" .. monoEval:GetFieldAsInt(mClass2,nil,"detectorsContainer"));	
	
end;

function Load()
	while flgLoadAssemblySuccess==false do
		ThreadLoadManageLibrary();
		sleep(5);
	end;
	log("Load success");
end;

function Invoke(flgQueue)
	--monoEval:InvokeStatic("FantasyWarTactic","Main", "Start",flgQueue);
	monoEval:InvokeStatic("FantasyWarTactic","Main", "Reload",nil,flgQueue);
end;

function ServerStart()
	monoEval:InvokeStatic("FantasyWarTactic","Main", "Start",nil,false);
end;

function Start()
	Load();
	ServerStart();
end;

function InvokeLocal()
	monoEval:InvokeStatic("","UIManagerScript", "TestNoparam",nil,false);
end;

function TestParam()
	monoEval:InvokeStatic("","UIManagerScript", "TestParam","Puapnoi",false);
end;

function TestNoparam()
	monoEval:InvokeStatic("","UIManagerScript", "TestNoparam",nil,false);
end;

function LoadKKK()
--	MonoLoadAssembly("/data/local/tmp/SimpleClass.dll");
	MonoLoadAndInvokeAssembly("/data/local/tmp/SimpleClass.dll", "SimpleClass","Main", "Start");
end;

function Check2()
	local AbusingScoreManager_class = monoEval:GetClassFromName("","AbusingScoreManager");
	local AbusingScoreManager_instance = monoEval:GetPropertyAsInt(AbusingScoreManager_class,nil,"instance");
	
	local GameMissionManager_class = monoEval:GetClassFromName("","GameMissionManager");
	local GameMissionManager_instance = monoEval:GetPropertyAsInt(GameMissionManager_class,nil,"instance");
	log("AbusingScoreManager_instance = " .. AbusingScoreManager_instance );
	log("GameMissionManager_instance = " .. GameMissionManager_instance );
end;

log('cscript 1.0 loaded');