---- rom.lua ------
if RomFileLogger == nil then
	RomFileLogger = {};
	RomFileLogger.f = io.open("/data/local/tmp/rom.log", "a");
	--RomFileLogger.f:setvbuf ("line");
end;
RomFileLogger.log = function(data)
	RomFileLogger.f:write(data .. "\n");
	RomFileLogger.f:flush();
end;

function LogDebug(data)
    local logData = os.date("%x %X") .. ' ' .. data;
	if Debug ~= nil then
		Debug.Log(logData);	
		RomFileLogger.log(logData);
	else
		RomFileLogger.log(logData);
		print(logData);
	end;
end;

logDebug = LogDebug

function ReadFile(path)
    local f = io.open(path)
    local s = f:read("*a")
    f:close()
    return s
end

function ROM_DoFile(fileName)
	LogDebug("ROM_DoFile " .. fileName);
	local s = ReadFile(fileName);
	local f = loadstring(s);
    if f~=nil then
        local status, err =  pcall(f);
        if status == false then
            LogDebug(err);
            return false;
        else    
            --f();
            LogDebug("ROM_DoFile success " .. fileName);
            return true;
        end;
    else
        if UIUtil ~= nil then
            UIUtil.FloatMsgByText("ROM_DoFile Fail (loadstring)");		
        end;
        LogDebug("ROM_DoFile Fail (loadstring)");
		return false;
    end;
end;

ROM_DoFile("/data/local/tmp/script/romUtil.lua");
ROM_DoFile("/data/local/tmp/script/hookSendNotification.lua");
function ROM_Reload()
	return ROM_DoFile("/data/local/tmp/script/rom.lua");
end;

if AI_Myself~=nil then
	function AI_Myself:_Idle(time, deltaTime, creature)
		--LogDebug("AI_Myself:_Idle " .. time .. ' ' .. deltaTime);
		self:_NotifyAngleY(time, deltaTime, creature)
		return AI_Myself.super._Idle(self, time, deltaTime, creature)
	end
	function AI_Myself:SearchAutoBattleLockTarget(creature, skillInfo)
		LogDebug("AI_Myself:SearchAutoBattleLockTarget " .. skillInfo:GetSpeakName(creature));
		--LogDebug(MyTostring(creature));
		--LogDebug(MyTostring(skillInfo));
		local lockID = self.autoAI_Battle.lockID
		if 0 == lockID then
			return nil
		end
		LogDebug("AI_Myself:SearchAutoBattleLockTarget " .. lockID);
	--return self.autoAI_Battle:SearchLockTarget(creature, skillInfo), lockID
	return self.autoAI_Battle:SearchLockTarget(creature, skillInfo), 10003
	end
end;
if MainViewHeadPage~=nil then
	function MainViewHeadPage:clickMyHead()
		LogDebug("Click");
		self:sendNotification(UIEvent.JumpPanel,{view = PanelConfig.Charactor});
	end
	--LogDebug(MyTostring(MainViewHeadPage));
else	
	LogDebug("MainViewHeadPage==nil");
end;

if NCreature ~= nil then
    LogDebug("Mod NCreature");
    function NCreature:Server_SetDirCmd(mode,dir,noSmooth)
        --helplog(string.format("Server SetDirCmd Player:%s Dir:%s", self.data.name, dir));
        self.ai:PushCommand(FactoryAICMD.GetSetAngleYCmd(mode,dir,noSmooth), self)
    end
    --function NCreature:GetClickable()
    --    LogDebug("NCreature:GetClickable()");
        --LogDebug(MyTostring(self.data));
        --LogDebug(MyTostring(self.assetRole));
        --self:Hide();
    --    return not self.data:NoAccessable()
    --end
    
end;

if EventManager~=nil and MyselfEvent ~= nil then
--    EventManager.Me():RemoveEventListener(MyselfEvent.HpChange,onHPChange,nil);
--    EventManager.Me():AddEventListener(MyselfEvent.HpChange,onHPChange,nil);
--    LogDebug("AddEventListener");
end;    

if Game~=nil and Game.LogicManager_Myself_Props ~= nil and Game.me~=nil then
    LogDebug(tostring(Game.me.functionSystemManager.logicManager));
    LogDebug(tostring(Game.LogicManager));
    LogDebug(tostring(Game.LogicManager_Myself_Props));
    LogDebug(tostring(Game.LogicManager_Myself_Props.UpdateHp));
    LogDebug("Before");
    --LogDebug(tostring(Game.LogicManager_Player_Props));
    --LogDebug(tostring(Game.me.functionSystemManager.logicManager.logicCreature.playerPropsManager));
    --function Game.LogicManager_Myself_Props:UpdateHp(ncreature,propName,oldValue,p)
    --    LogDebug("onHPChange " .. oldValue .. ' ' .. p:GetValue());
    --    LogicManager_Myself_Props.super.UpdateHp(self,ncreature,propName,oldValue,p)
    --    EventManager.me:PassEvent(MyselfEvent.HpChange,p:GetValue())
    --end
    function Game.LogicManager_Creature:Update(time, deltaTime)
        self:UpdateNpc(time,deltaTime)
        self:UpdatePets(time,deltaTime)
        self:UpdatePlayer(time,deltaTime)
        self:UpdateMyself(time,deltaTime)

        self.roleDressManager:Update(time, deltaTime)
        self.hatredManager:Update(time, deltaTime)
    end
    --LogDebug(tostring(Game.me.functionSystemManager.logicManager));    
    LogDebug("After");
    LogDebug(tostring(Game.LogicManager_Myself_Props.UpdateHp));
    LogDebug("LogicManager_Myself_Props");
end;

if FunctionChangeScene~= nil then
    LogDebug("Mod FunctionChangeScene");
	function FunctionChangeScene:EnterScene()
		LogDebug("GameAfterLoadSceneState:EnterScene()");
		SceneProxy.Instance:EnterScene()
		SceneProxy.Instance.sceneLoader:SetAllowSceneActivation()
	end
end;

function ROM_IsObjectInit(obj)
    return obj~=nil and obj.me ~= nil 
end;

if MyTick == nil and class ~= nil then
    MyTick = class("MyTick");   
end;
if MyTick ~= nil then
	MyTick.version = "1.01";
	function MyTick:ctor()
		self.version = MyTick.version;
		LogDebug("MyTick:ctor()");
	end

	function MyTick:Tick()
		local isInWantedQuestActivity = QuestProxy.Instance:isInWantedQuestInActivity()
		LogDebug("MyTick:Tick() " .. tostring(self) .." " .. self.version .. ' ' .. tostring(isInWantedQuestActivity));
	end;

	function MyTick:start()
		if ROM_IsObjectInit(TimeTickManager) then
			LogDebug("MyTick:start() " .. self.version);
			self.timeTick = TimeTickManager.Me():CreateTick(0,2000,self.Tick,self);
            --EventManager.Me():AddEventListener(MyselfEvent.HpChange,self.onHPChange,self);
			--LogDebug(MyTostring(self.timeTick));
		end;
	end;

	function MyTick:stop()
		if ROM_IsObjectInit(TimeTickManager) then
			LogDebug("MyTick:stop()");
			TimeTickManager.Me():ClearTick(self);
            self.timeTick = nil;
            --EventManager.Me():RemoveEventListener(MyselfEvent.HpChange,self.onHPChange,self);            
		end;
	end;
    
    function MyTick:isStart()
        return self.timeTick  ~= nil;
    end;
    
	if myTick == nil or myTick.version ~= MyTick.version then
        LogDebug("Create MyTick");
		myTick = MyTick.new();
	end;
end;


--LogDebug("myTick=" .. tostring(myTick) .. " " .. tostring(myTick.version));
--myTick.stop();
--myTick.start();
--[[
if MiniMapWindow~= nil then
    LogDebug("Mod MiniMapWindow");
	function MiniMapWindow:Show()
		--KKK
		--Debug.Log("Reload Start");
		--ROM_Reload();
		--Debug.Log("Reload End");
	
		self.active = true;
		self.gameObject:SetActive(true);

		self:OpenCheckMyPos();

		self:PlayQuestSymbolShow();
		
		--LogDebug(MyTostring(Game.Myself));
		--Game.Myself:Client_MoveTo(p)
		local uiCamera = NGUIUtil:GetCameraByLayername("UI");
		local tempV2, tempV3, tempRot = LuaVector2(), LuaVector3(), LuaQuaternion();
		LogDebug(MyTostring(uiCamera));
		self:AddClickEvent(self.mapTexture.gameObject, function (go)
			--UIUtil.FloatShowyMsg("Click");	-- simple center message
			--UIUtil.FloatMsgByText("Click");		-- center stack mesage
			LogDebug("MiniMap click");
			if(self.lock)then
				LogDebug("MiniMap Lock");	
				return;
			end
			local inputWorldPos = uiCamera:ScreenToWorldPoint(Input.mousePosition);
			LogDebug("inputWorldPos " .. MyTostring(inputWorldPos));
			LogDebug("mousePosition " .. MyTostring(Input.mousePosition));
			tempV3[1], tempV3[2], tempV3[3] = LuaGameObject.InverseTransformPointByVector3(self.mapTexture.transform, inputWorldPos);
			local p = self:MapPosToScene(tempV3);
			LogDebug("MapPos " .. MyTostring(tempV3));
			LogDebug("ScenePos " .. MyTostring(p));
            local currentMapID = Game.MapManager:GetMapID();            
			if(p)then

				LogDebug("currentMapID " .. MyTostring(currentMapID));
				LogDebug("Table_Map[currentMapID] " .. MyTostring(Table_Map[currentMapID]));
				local disableInnerTeleport = Table_Map[currentMapID].MapNavigation
				if nil ~= disableInnerTeleport and 0 ~= disableInnerTeleport then
					LogDebug("disableInnerTeleport");
					self:ResetMoveCMD(nil)
					Game.Myself:Client_MoveTo(p)
				else
					LogDebug("disableInnerTeleport==nil");
					self:ResetMoveCMD(nil)
					Game.Myself:Client_MoveTo(p,true);	-- ignore mesg seem to work
					--Game.Myself:Client_PlaceTo(p,true);	--client side only
				end;
			end;
			OnMiniMapClick(self);
		end);
	end
end;
toggle = 1;
]]

myButton = myButton or {};
function EnsureMyButtom(name)
	if myButton[name] == nil then	
		local obj = g_mainView:FindGO(name);
		if obj ~= nil then
			LogDebug(GameObjectToString(obj));
			myButton[name] = GameObject.Instantiate(obj);
		else	
			LogDebug("EnsureMyButtom Fail " .. name .. " not found");
		end;
	end;
	return myButton[name] ~= nil;
end;

function CreateMyButton(text,pos,onclick)
    if g_mainView == nil then 
        LogDebug("CreateMyButton: g_mainView not found");
        return nil 
    end;
    local templateButton = g_mainView:FindGO("RewardButton");
    if templateButton == nil then 
        LogDebug("CreateMyButton: RewardButton not found");
        return nil 
    end;
    local uiCamera = NGUIUtil:GetCameraByLayername("UI");	
    if uiCamera == nil then 
        LogDebug("CreateMyButton: uiCamera not found");
        return nil 
    end;
    local ret = myButton[text];
    if ret == nil then
        ret = GameObject.Instantiate(templateButton);
        myButton[text] = ret;
        ret:SetActive(false);
        UIUtil.FindGO("Sprite",ret):SetActive(false);
        local label = UIUtil.FindGO("Label",ret);
        --LogDebug(MyTostring(label.transform.localPosition));
        label.transform.localPosition = Vector3(0,0,0);
        label:GetComponent(UILabel).text = text;
        label:GetComponent(UILabel).effectColor = ColorUtil.NGUILabelBlueBlack;
        label:GetComponent(UILabel).effectStyle = UILabel.Effect.None;
        --ret.transform:SetParent(templateButton.transform.parent);
        if pos~= nil then
            ret.transform.position = uiCamera:ViewportToWorldPoint(pos);
        end;
    end;
    return ret;
end;

if g_mainView ~= nil then
	local tempVector3 = LuaVector3.zero
	local testButton = g_mainView:FindGO("TestFloat");
	local uiCamera = NGUIUtil:GetCameraByLayername("UI");	
	--LogDebug(GameObjectToString(uiCamera));
    
	--local obj = g_mainView:FindGO("SkillBord");
	--LogDebug(GameObjectToString(obj));
    local top_right = g_mainView:FindGO("Anchor_TopRight");
    --LogDebug(GameObjectToString(top_right,"",true));
--[[    
    if EnsureMyButtom("RewardButton") then
		myButton["RewardButton"]:SetActive(false);
        UIUtil.FindGO("Sprite",myButton["RewardButton"]):SetActive(false);
        local label = UIUtil.FindGO("Label",myButton["RewardButton"]);
        LogDebug(MyTostring(label.transform.localPosition));
        label.transform.localPosition = Vector3(0,0,0);
        myButton["RewardButton"].transform.position = uiCamera:ViewportToWorldPoint(Vector3(0.05,0.4,0));
	end;]]
    
    if CreateMyButton("Reload") then
        local button = myButton["Reload"];
        button.transform.position = uiCamera:ViewportToWorldPoint(Vector3(0.05,0.70,0));
        button:SetActive(true);        
        g_mainView:AddClickEvent(button, function (g)
            if ROM_Reload() then
                UIUtil.FloatMsgByText("Reload Success");
            end;
        end);        
    end;
    if CreateMyButton("Test") then
        LogDebug("Test");
        local button = myButton["Test"];
        button.transform.position = uiCamera:ViewportToWorldPoint(Vector3(0.05,0.63,0));
        button:SetActive(true);        
        g_mainView:AddClickEvent(button, function (g)
            ROM_Test(g);
        end);        
    end;
    if CreateMyButton("Auto") then
        LogDebug("Auto");
        local button = myButton["Auto"];
        button.transform.position = uiCamera:ViewportToWorldPoint(Vector3(0.05,0.56,0));
        button:SetActive(true);        
        
        local label = UIUtil.FindGO("Label",button);
        local uiLabel = label:GetComponent(UILabel);
        --uiLabel.effectColor = ColorUtil.NGUIWhite; --ColorUtil.Red;
        --uiLabel.effectStyle = UILabel.Effect.None;
        --LogDebug(MyTostring(uiLabel.effectStyle));
        g_mainView:AddClickEvent(button, function (g)
            ROM_Auto(g);
        end);        
    end;	
    if CreateMyButton("Tick") then
        LogDebug("Tick");
        local button = myButton["Tick"];
        button.transform.position = uiCamera:ViewportToWorldPoint(Vector3(0.05,0.49,0));
        button:SetActive(true);        
        g_mainView:AddClickEvent(button, function (g)
            ROM_MyTick(g);
        end);        
    end;	
    if CreateMyButton("Dlg") then
        LogDebug("Dlg");
        local button = myButton["Dlg"];
        button.transform.position = uiCamera:ViewportToWorldPoint(Vector3(0.05,0.42,0));
        button:SetActive(true);        
        g_mainView:AddClickEvent(button, function (g)
            ROM_MyDlg(g);
        end);        
    end;	
end;

function OnMiniMapClick(self)
	--myTick:stop();
	--myTick:start();

	--ListField(Game.Myself.ai);
	--ListField(g_MainView);	--class
	--ListField(g_mainView);	--instance
	--DumpSelf(self);
	--DumpMyself();
	local testButton = g_mainView:FindGO("TestFloat");
	LogDebug(MyTostring(testButton));
	local activeScene = SceneManagement.SceneManager.GetActiveScene();
	LogDebug(MyTostring(activeScene));
	--SceneManagement.SceneManager.LoadScene(testButton.name);
	--g_mainView.topFuncs:SetActive(true);	-- OK top left menu
	--g_mainView.moreBord:SetActive(true);	-- OK more board 
	--g_mainView.Anchor_DownLeft:SetActive(toggle%2 == 1);	-- OK lower left (chat and EXP bar)
	--g_mainView.raidMsgRoot:SetActive(toggle%2 == 1);	-- UNKNOWN
	--g_mainView.mainBord:SetActive(toggle%2 == 1);	-- everything beside background
	--g_mainView:FindGO("SkillBord"):SetActive(toggle%2 == 1); -- skill button
	--LogDebug(MyTostring(questlst));
	if toggle%2 == 1 then
		--UIUtil.FloatMsgByText("Show");
	end;
	--testButton:SetActive(toggle%2 == 1);
	toggle = toggle + 1;
	
	LogDebug("" .. toggle .. " " .. (toggle%2));
end;

function ROM_SkillTarget(tab)
    local skillInfo = ROM_GetMySkillInfoByName(tab.name);
    if skillInfo == nil then return false end;
    local skillID = skillInfo.staticData.id;
    local myStatus= ROM_GetMyStatus();
    local skillNeeded = ROM_GetSkillNeeded(skillID);
    if skillNeeded.sp < myStatus.sp then
		local npc = ROM_GetMonsterLockTarget();
		if npc == nil then
			LogDebug("ROM_SkillTarget: ROM_FindBestMonster");
			--npc = ROM_FindNearestMonsterEx(myMonsterList);
			npc = ROM_FindBestMonster();
		else
			--LogDebug("ROM_SkillTarget: use locktarget");
		end;
        if npc ~= nil then
            LogDebug("ROM_SkillTarget: " .. MonsterToString(npc));
            Game.Myself:Client_UseSkill(skillID, npc,nil,nil,true);
            return true;
        else
            LogDebug("ROM_SkillTarget: Monster not found");
        end;
    else
        LogDebug("ROM_SkillTarget: Not enough SP");
    end;
    return false;
end;
function ROM_FakeDead(tab)
    local skillInfo = ROM_GetMySkillInfoByName(tab.name);
    if skillInfo == nil then return false end;
    local skillID = skillInfo.staticData.id;

	local frachp = tab.frachp or 0.2;
	local fracsp = tab.fracsp or 0.2;
    --local skillID = tab.id;
    local myStatus= ROM_GetMyStatus();
	if ROM_GetMonsterLockTarget() == nil then
		if myStatus.fracsp < fracsp or myStatus.frachp < frachp then
			LogDebug("ROM_FakeDead: " .. MyTostring(myStatus));
			--Game.Myself:Client_UseSkill(skillID, nil, nil,nil,true);
			if(SkillProxy.Instance:SkillCanBeUsedByID(skillID)) then
				FunctionSkill.Me():TryUseSkill(skillID);
				return true;
			else
				LogDebug("ROM_FakeDead: can not use");
			end;
		end;
	else		
		--LogDebug("ROM_FakeDead: has lock target");
	end;
    return false;
end;
function ROM_BuffNoTarget(tab)
    local skillInfo = ROM_GetMySkillInfoByName(tab.name);
    if skillInfo == nil then return false end;
    local skillID = skillInfo.staticData.id;

    --local skillID = tab.id;
    local myStatus= ROM_GetMyStatus();
    local skillNeeded = ROM_GetSkillNeeded(skillID);
    if skillNeeded.sp < myStatus.sp then
        if ROM_HasBuffFromSkillID(skillID) == false then
            LogDebug("ROM_BuffNoTarget: " .. SkillToStringByID(skillID));
            Game.Myself:Client_UseSkill(skillID, Game.Myself ,nil,nil,true);
            return true;
        end;
    else
        LogDebug("ROM_BuffNoTarget: Not enough SP");
    end;
    return false;
end;


myMonsterList = {
--[[
    10005,    --Thief Bug      
    10006,    --Spore   
]]    
--    10007,  --Familiar
--    40013,  --Thief Bug Egg
--    110002, --Huge Thief Bug
	10020, -- name=Pirate Skeleton Type=Monster
--	10017, -- name=Hydra Type=Monster
--  10021, -- name=Poison Spore Type=Monster
--	10019, -- name=Whisper Type=Monster
    10022, -- name=Skeleton Type=Monster
--  40003, -- name=Yellow Plant Type=Monster
--  10024, -- name=Thara Frog Type=Monster
	10025, -- name=Marina Type=Monster
--  10023, -- name=Vadon Type=Monster
};

myMonsterRules = {
    {func= ROM_FindMiniBoss}, -- priority to miniboss
    {func= ROM_FindStaticMonster},  -- priority to static monster
    {func= ROM_FindNearestMonsterEx, param=myMonsterList},  -- selected monster
--    {func= ROM_FindNearestMonsterEx, param=nil},            -- all monster
};

myAIRules = {
    {name="Play Dead", func=ROM_FakeDead, fracsp=0.2},    --fake dead
    {name="Blessing", func=ROM_BuffNoTarget},  -- bless    
    {name="Holy Light Strike", func=ROM_SkillTarget},  -- holy
};


function ROM_Test(g)
    LogDebug("NPC");
    local mons = ROM_GetAllNPC();
    --tableForEach(mons,function(i,v)
	for monIndex = 1,#mons do
		local v = mons[monIndex];
        LogDebug(MonsterToString(v));
		--local conf = NpcMonsterUtility.GetConfig(v.data.staticData.id);
		--LogDebug(MyTostring(conf));
		--ListField(conf,"",{}," ");
		local npcData = v.data.staticData;
		local npcfunc = npcData.NpcFunction;
		LogDebug(MyTostring(npcfunc));
		for i=1,#npcfunc do
			local single = npcfunc[i];
			if(single.type)then
				local funcCfg = Table_NpcFunction and Table_NpcFunction[single.type];
				if(funcCfg and funcCfg.Type)then
					LogDebug(" funcCfg.Type " .. MyTostring(funcCfg.Type));
					local configFunc = FunctionVisitNpc.SNpcFuncMap[funcCfg.Type]
					LogDebug(" configFunc " .. MyTostring(configFunc));
					--if(configFunc and configFunc(npcfunc, target, events))then
					--	return;
					--end
				end
			end
		end
		
		local defaultDialogId = FunctionVisitNpc.GetDefaultDialog(v);
		LogDebug(" npcData.DefaultDialog " .. MyTostring(npcData.DefaultDialog));
		LogDebug(" defaultDialogId " .. MyTostring(defaultDialogId));
		local needRequireNpcFunc = npcData.NeedRequireNpcFunction;
		LogDebug(" needRequireNpcFunc " .. MyTostring(needRequireNpcFunc));
    --end);
	end;
    LogDebug("Monster");
    local mons = ROM_GetAllMonster();
    tableForEach(mons,function(i,v)
        LogDebug(MonsterToString(v));
    end);
    
    local npcList = Game.MapManager:GetNPCPointArray();
	LogDebug("npcList=" .. #npcList);
    tableForEach(npcList, function(i, v)
        if(v and v.ID and v.position)then
            local npcData = Table_Npc[v.ID];
            if npcData  then
                LogDebug(MyTostring(npcData));
            end;
        end;
    end);
	
	--local exitPoints =  Game.MapManager:GetExitPointMap();
	local exitPoints =  Game.MapManager:GetExitPointArray();	
	
	LogDebug("exitPoints=" .. #npcList);
    tableForEach(exitPoints, function(i, v)
        --if(v and v.ID and v.position)then
        --    local npcData = Table_Npc[v.ID];
        --    if npcData  then
                LogDebug("" .. i .. " " .. MyTostring(v));
        --    end;
        --end;
    end);
	
	
    local mainViewMiniMap = g_mainView.viewMap["MainViewMiniMap"];
    --ListField(mainViewMiniMap,"",{},"  ");
    --ListField(FunctionCDCommand.me,"-",{},"      ");
    --ListField(FunctionCDCommand.me.cmdMap,"-",{},"      ");
    --ListField(EventManager.Me().handlers,"",{},"  ");
    --ListField(GameFacade.Instance,"",{},"    ");
		--mainViewMiniMap.container.AddPageListenEvt(myBot,MyselfEvent.PlaceTo,myBot.PlaceTo2);
		--ListField(mainViewMiniMap.container.ListenerEvtMap,"",{},"    ");
		--ListField(mainViewMiniMap.container,"",{}," ");
		--LogDebug(tostring(g_mainView));
		--LogDebug(tostring(mainViewMiniMap.container));
		
		-- stop AI include battle
		--Game.Myself:Client_PauseIdleAI();
		--Game.Myself:Client_ResumeIdleAI();

		-- rotate camera
		--g_mainView:CameraRotateToMe(true);
		--g_mainView:CameraReset();	
	LogDebug('----------- questList -------------');
	--EQUESTLIST_ACCEPT = 1
	--EQUESTLIST_CANACCEPT = 4
	--EQUESTLIST_COMPLETE = 3
	--EQUESTLIST_SUBMIT = 2
	LogDebug('----------- EQUESTLIST_ACCEPT -------------');
	ListField(QuestProxy.Instance.questList[SceneQuest_pb.EQUESTLIST_ACCEPT],"",{},"");
	LogDebug('----------- EQUESTLIST_SUBMIT -------------');
	ListField(QuestProxy.Instance.questList[SceneQuest_pb.EQUESTLIST_SUBMIT],"",{}," ");
	LogDebug('----------- detailList -------------');
	ListField(QuestProxy.Instance.detailList,"",{}," ");
	LogDebug('----------- DailyQuestData -------------');
	ListField(QuestProxy.Instance.DailyQuestData,"",{},"    ");
	LogDebug('----------- menuDatas	 -------------');
	--ListField(QuestProxy.Instance.menuDatas	,"",{},"  ");
    local state = QuestProxy.Instance:hasGoingWantedQuest();
    LogDebug('----------- state	 -------------');
    ListField(state	,"",{},"  ");
    --local questData = QuestProxy.Instance:getWantedQuestDataByIdAndType(self.data.id,SceneQuest_pb.EQUESTLIST_ACCEPT)
	--	questData = questData and QuestData or QuestProxy.Instance:getWantedQuestDataByIdAndType(self.data.id,SceneQuest_pb.EQUESTLIST_COMPLETE)
    --LogDebug('----------- questData	 -------------');
    --ListField(questData	,"",{},"  ");
    ROM_DumpWantedQuest();
    
    --local status, err =  pcall(function() kkk[2]=1; end);
    --if status == false then
    --    LogDebug(err);
    --end;
	--LogDebug('----------- Table_GM_CMD -------------');
	--for k,v in pairs(Table_GM_CMD) do		
	
	local npcData = Table_Npc[1016];
	--ListField(npcData,"",{}," ");
	
	
	
    UIUtil.FloatMsgByText("Test Done");	
    if true then
        return;
    end;

    LogDebug("Skill");
    local skills = ROM_GetLearnSkill();
    tableForEach(skills,function(i,v)
        LogDebug(SkillToString(v));
    end);
    

    --local npc = ROM_FindNearestMonsterEx(myMonsterList);
    local npc = ROM_FindBestMonster();
    --LogDebug(MyTostring(npc));
    --ListField(npc);
    if npc ~= nil then
        Game.Myself:Client_LockTarget(npc);
        --Game.Myself:Client_MoveTo(npc:GetPosition(),true);	-- ignore mesg seem to work   
        --01/08/19 16:20:05 ID=146005 name=[Blessing] type=Buff
        --01/08/19 16:20:05 ID=144003 name=[Heal] type=Heal        
--[[        
        local skillID = 146005;
        if ROM_HasBuffFromSkillID(skillID) == true then
            UIUtil.FloatMsgByText("Has buff");   
        else
            Game.Myself:Client_UseSkill(skillID, nil,nil,nil,true);
        end
        LogDebug(MyTostring(ROM_GetSkillNeeded(skillID)));]]
        
    else
        LogDebug("Target not found");
    end;
    
    --ListField(MyTostring(SkillProxy.Instance.equipedSkillsArrays[SkillProxy.AutoSkillsIndex]));
    --ListField(SkillProxy.Instance.equipedSkillsArrays[SkillProxy.AutoSkillsIndex],"",{}," ");
    --ListField(SkillProxy.Instance.learnedSkills,"",{},"  ");
    --local lstAttkSkill = SkillProxy.Instance.learnedSkills[10];
    --tableForEach(lstAttkSkill, function(i, v)
            --local skill = v;
            --LogDebug(MyTostring(skill.id) .. " " );
            --local skillInfo = Game.LogicManager_Skill:GetSkillInfo(skill:GetID());
            --LogDebug("id=" .. skillInfo.staticData.id .. " name=[" .. skillInfo.staticData.NameZh .. "] type=" .. skillInfo.staticData.SkillType);
            --ListField(skillInfo);
    --end);
    --Game.Myself:Client_UseSkill(10001, npc,nil,nil,true);
    --DumpLearnSkill();
    --DumpMonsters();
    --local skills = ROM_GetActiveSkill();
    
    --ListField(Game.Myself.ai.idleAIManager.ais,"",{},"  ");
    --ListField(Game.Myself.data.props,"",{}," ");
    LogDebug(MyTostring(ROM_GetMyStatus()));
    UIUtil.FloatMsgByText("Test");    
end;

function ROM_HasBuffFromSkillID(skillID)
    local skillInfo = Game.LogicManager_Skill:GetSkillInfo(skillID);
    local buffs = skillInfo:GetSelfBuffs(Game.Myself);
    return Game.Myself:HasBuffs(buffs);
end;

function ROM_MyTick()
    local button = myButton["Tick"];
    local label = UIUtil.FindGO("Label",button);
    local uiLabel = label:GetComponent(UILabel);
    if myTick ~= nil then   
        if myTick:isStart() then
            myTick:stop();
            uiLabel.effectStyle = UILabel.Effect.None;
			GameFacade.Instance.sendNotification = GameFacade.Instance._sendNotification;
			LogDebug("restore = " .. tostring(GameFacade.Instance.sendNotification));
        else
            myTick:start();
            uiLabel.effectColor = ColorUtil.NGUILabelRed;
            uiLabel.effectStyle = UILabel.Effect.Outline;
			
			GameFacade.Instance._sendNotification = GameFacade.Instance.sendNotification;
			GameFacade.Instance.sendNotification = HOOK_SendNotification;
			LogDebug("org = " .. tostring(GameFacade.Instance._sendNotification));
			LogDebug("new = " .. tostring(GameFacade.Instance._sendNotification));
			LogDebug(tostring(GameFacade.Instance.sendNotification));
			--GameFacade.Instance:sendNotification(UIEvent.ShowUI, viewdata );	
        end
    end;
end;

function ROM_Auto()
    local button = myButton["Auto"];
    local label = UIUtil.FindGO("Label",button);
    local uiLabel = label:GetComponent(UILabel);
    --uiLabel.effectColor = ColorUtil.NGUIWhite; --ColorUtil.Red;
    --LogDebug(MyTostring(uiLabel.effectColor));
	if Game.Myself.ai.autoAI_Rom == nil then
		Game.Myself.ai.autoAI_Rom = AutoAI_Rom.new();
		Game.Myself.ai.idleAIManager:PushAI(Game.Myself.ai.autoAI_Rom);
		LogDebug("set AutoAI_Rom");
	else
		local index = TableUtil.FindKeyByValue(Game.Myself.ai.idleAIManager.ais,Game.Myself.ai.autoAI_Rom);
        local old = Game.Myself.ai.autoAI_Rom;
		Game.Myself.ai.autoAI_Rom = AutoAI_Rom.new();
		Game.Myself.ai.idleAIManager.ais[index] = Game.Myself.ai.autoAI_Rom;
        Game.Myself.ai.autoAI_Rom:Enable(old:IsEnable());
--		LogDebug("set new AutoAI_Rom");
	end;
    if Game.Myself.ai.autoAI_Rom:IsEnable() then
        Game.Myself.ai.autoAI_Rom:Enable(false);
        uiLabel.effectStyle = UILabel.Effect.None;
        --uiLabel.effectColor = ColorUtil.NGUILabelBlueBlack;
    else
        Game.Myself.ai.autoAI_Rom:Enable(true);
        uiLabel.effectColor = ColorUtil.NGUILabelRed;
        uiLabel.effectStyle = UILabel.Effect.Outline;
    end;
    UIUtil.FloatMsgByText("Auto " .. tostring(Game.Myself.ai.autoAI_Rom:IsEnable()));
end;

function ROM_MyDlg()
		local viewdata = {
		viewname = "DialogView",
		tasks = nil,
		dialoglist = {"เล่นกันดีๆไท้ได้เหรอ]"},
	};
	viewdata.addfunc = {
		{
			event = function (npcinfo,param)
				UIUtil.FloatMsgByText("[" .. tostring(param) .. "]");	
			end,
			eventParam = {"haha"},
			closeDialog = true,
			NameZh = "Funct1",
			
		},
		{
			event = function (npcinfo)
				FunctionNpcFunc.JumpPanel(PanelConfig.ChangeZoneView, npcinfo)
			end,
			closeDialog = true,
			NameZh = ZhString.ChangeZone_ChangeLine
		},
		{
			event = function (npcinfo)
				if GuildProxy.Instance:IHaveGuild() then
					local zoneid = GuildProxy.Instance.myGuildData.zoneid
					ServiceNUserProxy.Instance:CallJumpZoneUserCmd( npcinfo.data.id , zoneid)
				end
			end,
			closeDialog = true,
			NameZh = ZhString.ChangeZone_BackGuildLine
		},
		{
			event = function (npcinfo)
				LogDebug("npcinfo=" .. tostring(npcinfo));
                LogDebug("currentMapID=" .. Game.MapManager:GetMapID());
				--FunctionDialogEvent.SetDialogEventEnter( DialogEventType.EquipUpgrade, npcinfo )
				--GameFacade.Instance:sendNotification(UIEvent.JumpPanel, {view=PanelConfig.AnnounceQuestPanel, viewdata ={wanted = wantedid, npcTarget = target, isNpcFuncView = true}});
				--FunctionNpcFunc.JumpPanel(PanelConfig.AnnounceQuestPanel, npcinfo)
				local mapid = SceneProxy.Instance.currentScene.mapID;				
				local nearestExit = ROM_GetNearestExitPoint();
                local myPos = Game.Myself:GetPosition();
				LogDebug("nearestExit=" .. MyTostring(nearestExit) .. " mapid=" .. tostring(mapid) .. " pos=" .. tostring(myPos));
				
				local tempVector3 = LuaVector3.zero;
                local nearestNPC, nearestDist = ROM_GetNearestNPC();
                if nearestNPC ~= nil  then
                    LogDebug(MonsterToString(nearestNPC) .. ' ' .. nearestDist);
                end;
                --LuaVector3(15.533345, 7.136991, -23.064865)
				tempVector3:Set(nearestExit.position[1],nearestExit.position[2],nearestExit.position[3]);
				--Game.Myself:Client_MoveTo(tempVector3);
				--ROM_CommandGOTO(mapid,tempVector3);
				--ROM_CommandVisitMonster(2,10001);
                
                local q = ROM_GetAcceptedQuest();
                if q ~= nil then
                    LogDebug("Has Accepted Wanted Quest " .. QuestToString(q) );
                    --ListField(q,"",{},"    ");  
                    --LogDebug(MyTostring(q));
                    if q.wantedData.Content == "move" then
                        ROM_WalkToNPC(q.wantedData.MapId,q.params.npc);
                    elseif q.wantedData.Content == "kill" then
                        ListField(q,"",{},"    ");  
                        if q.params.monster ~= nil then
                            -- goto that monster
                            ROM_CommandVisitMonster(q.wantedData.MapId,q.params.monster);
                        else
                            -- goto board to submit quest 
                            -- it might possibile that this map does not have board will see
                            ROM_WalkToNPC(mapid,q.params.npc);
                        end;
                    else
                        LogDebug("Quest type not suppoted");
                    end;
                else 
                    if ROM_WalkToNPC(mapid,1016) then
                        -- near board
                        LogDebug("Near board");
                        if ROM_SubmitQuest() == false then
                            ROM_AcceptQuest();
                        end;
                    end;
                    --local nearestNPC, nearestDist = ROM_GetNearestNPC();
--[[                    local found = false;
                    if nearestNPC ~= nil then
                        LogDebug(MonsterToString(nearestNPC) .. ' ' .. nearestDist);
                        if nearestNPC.data.staticData.id == 1016 then
                           if nearestDist < 5 then
                            found = true;
                           end;
                        end;
                    end;
                    if found == false then
                        local tempVector3 = LuaVector3.zero;
                        tempVector3:Set(15.533345,7.136991,-23.064865);
                        ROM_CommandGOTO(7,tempVector3);
                    else
                        -- near board
                        LogDebug("Near board");
                        if ROM_SubmitQuest() == false then
                            ROM_AcceptQuest();
                        end;
                    end;]]
                end;
                
                --ROM_CommandVisitNPC(7,1016,nil);
                
                --if ROM_SubmitQuest() == false then
                --    ROM_AcceptQuest();
                --end;
				--LogDebug("Game.Myself:GetPosition()=" .. MyTostring(Game.Myself:GetPosition()));
				--LogDebug("nearestExit=" .. MyTostring(tempVector3));
				--Game.Myself:Client_EnterExitRangeHandler(nearestExit);
				--tempVector3:Set(nearestExit.position[1]*1000,nearestExit.position[2]*1000,nearestExit.position[3]*1000);
				--LogDebug("fake myposition=" .. MyTostring(tempVector3));
				--ServiceNUserProxy.Instance:CallExitPosUserCmd(tempVector3,nearestExit.ID,mapid); 
				LogDebug("done");
			end,
			closeDialog = true,
			--NameZh = ZhString.FunctionDialogEvent_Upgrade,
			NameZh="UNK",
			
		},
	};
	--local dialogInfo ={ DialogUtil.GetDialogData(defaultDialogId) };
	--ListField(dialogInfo,"",{},"      ");
	GameFacade.Instance:sendNotification(UIEvent.ShowUI, viewdata);
end;

function ROM_GetNearestExitPoint()
	local minDist = 100000;
    local ret = nil;
    local myPos = Game.Myself:GetPosition();
	local exitPoints =  Game.MapManager:GetExitPointArray();	
	tableForEach(exitPoints, function(i, v)
		local distance = LuaVector3.Distance(myPos, v.position);
        if distance < minDist then
            ret = v;
            minDist = distance;
        end;
	end);
    return ret;	
end;

function ROM_GetNPCPointByID(npcID)
    local npcList = Game.MapManager:GetNPCPointArray();
    --LogDebug("" .. #npcList);
    for i=1,#npcList do
        local v = npcList[i];
        if v and v.ID and v.position and v.uniqueID ~= 0 and v.ID == npcID then
            local npcData = Table_Npc[v.ID];
            if npcData  then
                --LogDebug("" .. v.ID .. " " .. npcID);
                --ListField(v,"",{}," ");
                --ListField(npcData,"",{},"");
                return v
            end;
            --return v;
        end;
    end;
    return nil;
end;    

function ROM_GetNearestNPC()
	local minDist = 100000;
    local ret = nil;
    local mons = ROM_GetAllNPC();
    local myPos = Game.Myself:GetPosition();
	--local exitPoints =  Game.MapManager:GetExitPointArray();	
	tableForEach(mons, function(i, v)
		local distance = LuaVector3.Distance(myPos, v:GetPosition());
        if distance < minDist then
            ret = v;
            minDist = distance;
        end;
	end);
    return ret,minDist;	
end;


function ROM_CommandVisitMonster(mapID,monID)
		local oriMonster = Table_MonsterOrigin[ monID] or {};
		-- this will have mapID which contain that monsters
		--LogDebug(MyTostring(oriMonster));
		local oriPos = nil;
		for i=1,#oriMonster do
			if(oriMonster[i].mapID == mapID)then
				oriPos = oriMonster[i].pos;
			end
		end
		if(oriPos)then
			local cmdArgs = {
				targetMapID = mapID,
				npcID = monID,
				targetPos = TableUtil.Array2Vector3(oriPos),
                callback = function(cmd, event)
                    --LogDebug("ROM_CommandVisitMonster callback cmd=" .. MyTostring(cmd));
                    --LogDebug("ROM_CommandVisitMonster callback event=" .. MyTostring(event));
                    local q = ROM_GetAcceptedQuest();
                    if q ~= nil then
                        LogDebug(QuestToString(q));
                        if q.params.num == nil then
                            LogDebug("Quest done");
                            ROM_WalkToNPC(mapID,1016);
                            
                        else 
                            LogDebug("" .. tostring(q.process) .. "/" .. tostring(q.params.num));
                        end;
                    end;
                end                
			}
			local cmd = MissionCommandFactory.CreateCommand(cmdArgs, MissionCommandSkill)	
			if(cmd)then
				Game.Myself:Client_SetMissionCommand( cmd );
				--self:PassEvent(WorldMapMenuEvent.StartTrace);
			end
		end
end;

function ROM_CommandVisitNPC(mapID,npcID,npcUID)
	local cmdArgs = {
		targetMapID = mapID,
		npcID = npcID,
		npcUID = npcUID,
	}
	cmd = MissionCommandFactory.CreateCommand(cmdArgs, MissionCommandVisitNpc)	
	if(cmd)then
		Game.Myself:Client_SetMissionCommand( cmd );
	end
end;
function ROM_CommandGOTO(mapID,pos)
	local tempArgs = {};
	tempArgs.targetMapID = mapID;
	tempArgs.showClickGround = true;
	tempArgs.allowExitPoint = true;
    if pos ~= nil then
        local x,y,z = pos[1],pos[2],pos[3];
        local tempVector3 = LuaVector3.zero;
        tempVector3:Set(x,y,z);
        tempArgs.targetPos = tempVector3;      
        LogDebug("targetPos=" .. tostring(targetPos));
        tempArgs.callback = function(cmd, event)
            LogDebug("cmd=" .. MyTostring(cmd));
            LogDebug("event=" .. MyTostring(event));
            if MissionCommandMove.CallbackEvent.TeleportFailed == event then
                LogDebug("event=TeleportFailed");
                Game.Myself:Client_MoveTo( tempVector3 );
            end
        end
    end;
	local cmd = MissionCommandFactory.CreateCommand(tempArgs, MissionCommandMove);
	if(cmd)then
        LogDebug("ROM_CommandGOTO: Client_SetMissionCommand");
		Game.Myself:Client_SetMissionCommand( cmd );
    else
        LogDebug("ROM_CommandGOTO: cmd error");
	end
end;

function ROM_DumpWantedQuest()
    local wantedQuest = QuestProxy.Instance:getWantedQuest();
    LogDebug('----------- wantedQuest	 -------------');
    --
    for i=1,#wantedQuest do
        local wq = wantedQuest[i];
--[[        local wd = wq.wantedData;
        --EQUESTLIST_ACCEPT = 1
        --EQUESTLIST_CANACCEPT = 4
        --EQUESTLIST_COMPLETE = 3
        --EQUESTLIST_SUBMIT = 2
        local listType = "";
        if wq.questListType == SceneQuest_pb.EQUESTLIST_ACCEPT then listType = "EQUESTLIST_ACCEPT" end;
        if wq.questListType == SceneQuest_pb.EQUESTLIST_CANACCEPT then listType = "EQUESTLIST_CANACCEPT" end;
        if wq.questListType == SceneQuest_pb.EQUESTLIST_COMPLETE then listType = "EQUESTLIST_COMPLETE" end;
        if wq.questListType == SceneQuest_pb.EQUESTLIST_SUBMIT then listType = "EQUESTLIST_SUBMIT" end;
        LogDebug("id=" .. wd.id .. " Target=" .. wd.Target .. " MapId=" .. wd.MapId .. " NpcId=" .. wd.NpcId .. " questListType=" .. listType .. " Content=" .. wd.Content);
        --local info = QuestDataUtil.parseWantedQuestTranceInfo(wq,wd);
        --LogDebug(MyTostring(info));]]
        LogDebug(QuestToString(wq));
        --ListField(wd.Params,"",{}," ");        
        --ListField(wq,"",{}," ",{"Describe","Name"});        
    end;
end;

function ROM_SubmitQuest()
    local wantedQuest = QuestProxy.Instance:getWantedQuest();
    for i=1,#wantedQuest do
        local wq = wantedQuest[i];
        local wd = wq.wantedData;
        if wq.questListType == SceneQuest_pb.EQUESTLIST_COMPLETE then
            -- find mission board 1016 location mapID 7
            -- goto that location
            -- submit it
            LogDebug("Submitable quest found to submit");
            ServiceQuestProxy.Instance:CallQuestAction(SceneQuest_pb.EQUESTACTION_SUBMIT,wq.id);
            return true;
        end;
    end;
    LogDebug("Submitable quest not found to submit");
    return false;
end;

function ROM_AcceptQuest()
    local wantedQuest = QuestProxy.Instance:getWantedQuest();
    for i=1,#wantedQuest do
        local wq = wantedQuest[i];
        local wd = wq.wantedData;
        if wq.questListType == SceneQuest_pb.EQUESTLIST_CANACCEPT then
            LogDebug(QuestToString(wq));
            if wd.Content == "move" then
                LogDebug("ROM_AcceptQuest move found");
                ServiceQuestProxy.Instance:CallQuestAction(SceneQuest_pb.EQUESTACTION_ACCEPT,wq.id);
                return true;
            end;
            if wd.Content == "kill" then
                LogDebug("ROM_AcceptQuest kill found");
                ServiceQuestProxy.Instance:CallQuestAction(SceneQuest_pb.EQUESTACTION_ACCEPT,wq.id);
                return true;
            end;
            --LogDebug("Submitable quest found to submit");
            --ServiceQuestProxy.Instance:CallQuestAction(SceneQuest_pb.EQUESTACTION_SUBMIT,wq.id);
        end;
    end;
    LogDebug("Accept quest quest not found to submit");
    return false;
    
end;
function ROM_GetAcceptedQuest()
    local wantedQuest = QuestProxy.Instance:getWantedQuest();
    for i=1,#wantedQuest do
        local wq = wantedQuest[i];
        local wd = wq.wantedData;
        if wq.questListType == SceneQuest_pb.EQUESTLIST_ACCEPT then
            return wq;
        end;
    end;
    return nil;
end;

function ROM_WalkToNPC(mapID,npcID)
    local mapid = Game.MapManager:GetMapID();
    -- check mapID
    if mapid ~= mapID then
        LogDebug("ROM_WalkToNPC: wrong map current=" .. mapid .. " target=" .. mapID);
        ROM_CommandGOTO(q.wantedData.MapId);
        return false;
    end;    
    -- check nearest NPC
    LogDebug("ROM_WalkToNPC: MapID=" .. Game.MapManager:GetMapID() .. " [" .. Game.MapManager:GetMapName() .. "]");
    local nearestNPC, nearestDist = ROM_GetNearestNPC();
    if nearestNPC ~= nil then
        if nearestNPC.data.staticData.id == npcID and  nearestDist < 5 then
            LogDebug("ROM_WalkToNPC: End (target reach)");
            return true;
        end;
    end;
    -- walk to that NPC
    local npc = ROM_GetNPCPointByID(npcID);
    if npc ~= nil then
        --LogDebug("Found npc);
        --ListField(npcs,"",{}," "); 
        LogDebug("ROM_WalkToNPC: same map " .. MyTostring(npc.position));
        ROM_CommandGOTO(mapID,npc.position);
        return false;
    else
        if npcID == 1016 then
            LogDebug("ROM_WalkToNPC: mission board hardcode to morroc");
            ROM_CommandGOTO(16);
            return false;
        end;
        LogDebug("ROM_WalkToNPC: End (npc not found)");
        return true;
    end;
end;
LogDebug("ROM Loaded 1.03");

