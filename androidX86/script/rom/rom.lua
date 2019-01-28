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
ROM_DoFile("/data/local/tmp/script/romAutoQuest.lua");
ROM_DoFile("/data/local/tmp/script/hookSendNotification.lua");
function ROM_Reload()
	return ROM_DoFile("/data/local/tmp/script/rom.lua");
end;
--[[
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
]]
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
			self.timeTick = TimeTickManager.Me():CreateTick(0,10000,self.Tick,self);
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

--[[

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

end;
]]
function ROM_SkillTarget(tab)
    local skillInfo = ROM_GetMySkillInfoByName(tab.name);
    if skillInfo == nil then return false end;
    local skillID = skillInfo.staticData.id;
	if SkillProxy.Instance:SkillCanBeUsedByID(skillID) == false then
		local skillItem = SkillProxy.Instance:GetLearnedSkill(skillID)
		local inCD = SkillProxy.Instance:IsInCD(skillItem);
        --return self:IsInCD(SceneUser2_pb.CD_TYPE_SKILL,id) or self:IsInCD(SceneUser2_pb.CD_TYPE_SKILL,CDProxy.CommunalSkillCDSortID)
        local in1 = CDProxy.Instance:IsInCD(SceneUser2_pb.CD_TYPE_SKILL,skillItem.sortID);
        local in2 = CDProxy.Instance:IsInCD(SceneUser2_pb.CD_TYPE_SKILL,CDProxy.CommunalSkillCDSortID);
		--LogDebug("ROM_SkillTarget: " .. tab.name .. " inCD=" .. tostring(inCD) .. ' ' .. tostring(in1) .. ' ' .. tostring(in2));		
		return false;
	end;
	
    local myStatus= ROM_GetMyStatus();
    local skillNeeded = ROM_GetSkillNeeded(skillID);
    if skillNeeded.sp < myStatus.sp then
		local npc = ROM_GetMonsterLockTarget();
		if npc == nil then
			LogDebug("ROM_SkillTarget: ROM_FindBestMonster");
			npc = ROM_FindBestMonster();
		else
			--LogDebug("ROM_SkillTarget: use locktarget");
		end;
        if npc ~= nil then
            LogDebug("ROM_SkillTarget: " .. skillID .. " " .. MonsterToString(npc));
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
	
	if SkillProxy.Instance:SkillCanBeUsedByID(skillID) == false then
--		LogDebug("ROM_BuffNoTarget: " .. tab.name .. " skill can not be used");
		return false;
	end;

    --local skillID = tab.id;
    local myStatus= ROM_GetMyStatus();
    local skillNeeded = ROM_GetSkillNeeded(skillID);
    if skillNeeded.sp < myStatus.sp then
		if tab.fracsp and myStatus.fracsp > tab.fracsp then
			--LogDebug("ROM_BuffNoTarget: " .. tab.name .. " fracsp > fracsp");
			return false;
		end;
		local npc = ROM_GetMonsterLockTarget();
		if npc == nil then
			if ROM_HasBuffFromSkillID(skillID) == false then
				LogDebug("ROM_BuffNoTarget: " .. SkillToStringByID(skillID));
				Game.Myself:Client_UseSkill(skillID, Game.Myself ,nil,nil,true);
				return true;
			end;
		else	
			--LogDebug("ROM_BuffNoTarget: " .. tab.name .. " has lock target");
		end;
    else
        LogDebug("ROM_BuffNoTarget: " .. tab.name .. " Not enough SP " .. myStatus.sp);
    end;
    return false;
end;

function ROM_Heal(tab)
	local frac = tab.frachp or 0.6;
    local skillInfo = ROM_GetMySkillInfoByName(tab.name);
    if skillInfo == nil then return false end;
    local skillID = skillInfo.staticData.id;
	
	if SkillProxy.Instance:SkillCanBeUsedByID(skillID) == false then
--		LogDebug("ROM_Heal: " .. tab.name .. " skill can not be used");
		return false;
	end;
	
    local myStatus= ROM_GetMyStatus();
    local skillNeeded = ROM_GetSkillNeeded(skillID);
	LogDebug("ROM_Heal: " .. skillNeeded.sp .. " " .. myStatus.frachp);
	if skillNeeded.sp < myStatus.sp then
		if myStatus.frachp < frac then
			--if ROM_HasBuffFromSkillID(skillID) == false then
			LogDebug("ROM_Heal: " .. SkillToStringByID(skillID));
			Game.Myself:Client_UseSkill(skillID, Game.Myself ,nil,nil,true);
			return true;
		else
--			LogDebug("ROM_Heal: hp high enough");
		end;
        --end;
    else
--        LogDebug("ROM_Heal: Not enough SP");
    end;
    return false;			
end;

function ROM_WillMiss(skillAndLevel,targetUser,value)
	value = value or 50;
--    local skillID, skillLevel = CommonFun.UnmergeSkillID(skillAndLevel);
    local srcUser = Game.Myself.data;
	local saveIndex = Game.Myself.data.randomFunc.index;
    local skillParams = Table_Skill[skillAndLevel];
    srcUser:GetRandom();    
    local willMiss = CommonFun.IsMiss(srcUser,targetUser,skillParams);

    logDebug("ROM_WillMiss " .. tostring(willMiss));
--[[    
	local randValue =  srcUser:GetRandom();
	randValue =  srcUser:GetRandom();
	logDebug("ROM_WillMiss " .. randValue .. ' saveIndex=' .. saveIndex);
	local ret = randValue > value]]
	Game.Myself.data.randomFunc.index = saveIndex;
	return willMiss;
end;

function ROM_NeverMiss(tab)
    local skillInfo = ROM_GetMySkillInfoByName(tab.name);
    if skillInfo == nil then return false end;
    local skillID = skillInfo.staticData.id;
    local npc = ROM_FindCurrentMonster();
    if npc == nil then
        return false;
    end;
    if tab.filter then
        if tab.filter(npc) == false then
            return false;
        end;
    end;

	while ROM_WillMiss(skillID,npc.data,49) do
		LogDebug("index=" .. Game.Myself.data.randomFunc.index);
		Game.Myself.data:GetRandom();
	end;
	return ROM_SkillTarget(tab);
end;

function ROM_WillTurnSuccess(skillAndLevel,targetUser)
    local skillID, skillLevel = CommonFun.UnmergeSkillID(skillAndLevel);
    local srcUser = Game.Myself.data;
    local Luk=srcUser:GetProperty("Luk");
    local Int=srcUser:GetProperty("Int");
    local BaseLv = srcUser.BaseLv;
    local Hp=targetUser:GetProperty("Hp");
    local MaxHp=targetUser:GetProperty("MaxHp");
    local rate = ((20*skillLevel+Luk+Int+BaseLv+(1-Hp/MaxHp)*200)/10);
    if rate >=70 then
        rate=70
    end   
    local saveIndex = Game.Myself.data.randomFunc.index;
    -- make some adjusr for index seem to need + 1
    srcUser:GetRandom();
    local randValue =  srcUser:GetRandom();
    local ret = CommonFun.IsInRate(rate, randValue);
    Game.Myself.data.randomFunc.index = saveIndex;
    LogDebug("ROM_WillTurnSuccess rand=" .. randValue .. " rate=" .. rate .. " return=" .. tostring(ret));
    return ret;
end;

function ROM_TurnUndead(tab)
    local skillInfo = ROM_GetMySkillInfoByName(tab.name);
    if skillInfo == nil then return false end;
    local skillID = skillInfo.staticData.id;
	if SkillProxy.Instance:SkillCanBeUsedByID(skillID) == false then
--		LogDebug("ROM_TurnUndead: " .. tab.name .. " skill can not be used");
		return false;
	end;
	
    local myStatus= ROM_GetMyStatus();
    local skillNeeded = ROM_GetSkillNeeded(skillID);
	if skillNeeded.sp < myStatus.sp then
		local npc = ROM_GetMonsterLockTarget();
		if npc == nil then
--			LogDebug("ROM_TurnUndead: ROM_FindBestMonster");
			npc = ROM_FindBestMonster();
		else
			--LogDebug("ROM_SkillTarget: use locktarget");
		end;
        if npc ~= nil then
			if npc.data.staticData.Nature == "Undead" then
				-- check if that monster is undead
				--LogDebug("ROM_TurnUndead: " .. MonsterToString(npc));
				local monStatus = ROM_GetMonStatus(npc);
				if monStatus ~= nil then
					if monStatus.frachp > (tab.frachp or 0.9) then
						local players =  ROM_GetNearPlayers();
						--Game.Myself.data.randomFunc.index = 20;			
						if #players > 0 then
							LogDebug("ROM_TurnUndead: " .. MonsterToString(npc) .. ' players=' .. #players);
							local willHit = ROM_WillTurnSuccess(skillID,npc.data);
							if willHit == false then
								LogDebug("Game.Myself:Client_UseSkill rand index=" .. Game.Myself.data.randomFunc.index .. ' willHit=' .. tostring(willHit));
								Game.Myself.data:GetRandom();   -- roll next dice
							end;
						else
							local willHit = ROM_WillTurnSuccess(skillID,npc.data);
							while willHit == false do
								LogDebug("Game.Myself:Client_UseSkill rand index=" .. Game.Myself.data.randomFunc.index .. ' willHit=' .. tostring(willHit));
								Game.Myself.data:GetRandom();   -- roll next dice
								willHit = ROM_WillTurnSuccess(skillID,npc.data);
							end;
						end;
						LogDebug("ROM_TurnUndead: " .. MonsterToString(npc));
						LogDebug("Game.Myself:Client_UseSkill rand index=" .. Game.Myself.data.randomFunc.index);
						Game.Myself:Client_UseSkill(skillID, npc,nil,nil,true);
						return true;
						
					else	
						--LogDebug("ROM_TurnUndead: Monster frachp > ");
					end;
				else	
					--LogDebug("ROM_TurnUndead: Monster status not found");
				end;
			else	
				--LogDebug("ROM_TurnUndead: Monster is not undead " .. npc.data.staticData.Race);
			end;
        else
            --LogDebug("ROM_TurnUndead: Monster not found");
        end;
    else
        LogDebug("ROM_TurnUndead: Not enough SP");
    end;
    return false;			
end;

function ROM_WalkToRange(tab)
    local range = tab.range or 6;
    
    local npc = ROM_GetMonsterLockTarget();
    if npc == nil then
        npc = ROM_FindBestMonster();
    end;
    if npc ~= nil then
        --ListField(npc,"",{},"  ");  
        local myPos = Game.Myself:GetPosition();
        local targetPosition = npc:GetPosition();
        local distance = LuaVector3.Distance(myPos, targetPosition);
        --LogDebug("ROM_WalkToRange: dist=" .. distance);
        if distance > range then
            LogDebug("ROM_WalkToRange walk to target");
            Game.Myself:Client_MoveTo(targetPosition, nil, nil, nil, nil, range);
            return true;
        end;
    else
        --LogDebug("npc is null");
    end;
    return false;
end;

function ROM_MonFullHP(npc)
    local monStatus = ROM_GetMonStatus(npc);
    return monStatus.frachp > 0.99 
end;

myMonsterList = {

	10004, -- name=Tarou
    10005,    --Thief Bug      
    10006,    --Spore   
    10007,  --Familiar
--    40013,  --Thief Bug Egg
--    110002, --Huge Thief Bug
	10012, -- name=Rocker
	10013, -- name=Willow
	10020, -- name=Pirate Skeleton Type=Monster
--	10017, -- name=Hydra Type=Monster
--  10021, -- name=Poison Spore Type=Monster
--	10019, -- name=Whisper Type=Monster
    10022, -- name=Skeleton Type=Monster
--  40003, -- name=Yellow Plant Type=Monster
--  10024, -- name=Thara Frog Type=Monster
	10025, -- name=Marina Type=Monster
--  10023, -- name=Vadon Type=Monster
	10050, -- name=Soldier Skeleton
    10037, -- name=Flora Type=Monster    
--	10051, -- name=Matyr	
	10052, -- name=Mummy
    10063, -- name=Archer Skeleton
	

};

myMonsterRules = {
--    {func= ROM_FindMiniBoss}, -- priority to miniboss
    {func= ROM_FindStaticMonster},  -- priority to static monster
--    {func= ROM_FindNearestMonsterEx, param=myMonsterList},  -- selected monster
    {func= ROM_FindNearestMonsterEx2, monlist={}},  -- selected monster
};

myAIRules = {
    {name="Play Dead", func=ROM_FakeDead, fracsp=0.2},    --fake dead
--	{name="Bash", func=ROM_SkillTarget},    
	{name="Shield Charge", func=ROM_NeverMiss,filter=function(mon) return ROM_IsEliteMonster(mon) end},    	
	{name="Auto", func=ROM_SkillTarget},    


--    {name="Blessing", func=ROM_BuffNoTarget},  -- bless    
--	{name="Gloria", func=ROM_BuffNoTarget},  -- Gloria    
--	{name="Magnif", func=ROM_BuffNoTarget, fracsp=0.5},  -- Gloria    
--	{name="WalkToRange", func=ROM_WalkToRange,range=5},  		
--	{name="Heal", func=ROM_Heal,frachp=0.6},  -- bless    
--	{name="Turn", func=ROM_TurnUndead, frachp=0.6},  
--    {name="Holy Light Strike", func=ROM_SkillTarget},  	
};

ROM_Config = {};
ROM_Config[4313990901] = {
    myMonsterList = {
    	10052, -- name=Mummy
        10063, -- name=Archer Skeleton
        10061, --  name=Bongun
        10060, --  name=Munak
        10120, --  name=Evil Druid
        10121,--  name=Dark Priest
        10080, --  name=Wraith Type=Monster
    },
    myMonsterRules ={
        {func= ROM_FindStaticMonster},  -- priority to static monster
        {func= ROM_FindNearestMonsterEx2, filter=ROM_MonFullHP, selectFunc=ROM_GetBestScoreMonFromList},  -- selected monster
    },
    myAIRules = {
        {name="Play Dead", func=ROM_FakeDead, fracsp=0.2},    --fake dead
        {name="Blessing", func=ROM_BuffNoTarget},  -- bless    
        {name="Gloria", func=ROM_BuffNoTarget},  -- Gloria    
        {name="Magnif", func=ROM_BuffNoTarget, fracsp=0.5},  -- Gloria    
        {name="WalkToRange", func=ROM_WalkToRange,range=6},  		
        {name="Heal", func=ROM_Heal,frachp=0.6},  -- bless    
        {name="Turn", func=ROM_TurnUndead, frachp=0.6},  
        {name="Holy Light Strike", func=ROM_SkillTarget},  	
    },
}
--4313990901
if Game and Game.Myself and Game.Myself.data then
    if ROM_Config[Game.Myself.data.id] ~= nil then
        LogDebug("Use ROM_Config for " .. Game.Myself.data.id);
        local conf = ROM_Config[Game.Myself.data.id];
        myMonsterList = conf.myMonsterList;
        myMonsterRules = conf.myMonsterRules;
        myAIRules = conf.myAIRules;
    end;
end;

function ROM_Test(g)
    LogDebug("----- ROM_Test --------");
    LogDebug(CreatureToString(Game.Myself));
    local props = Game.Myself.data.props;
    tableForEach(props.configs,function(i,v)
		if (type(i) == 'number') then
			local p = props:GetPropByName(v.name);
			if p ~= nil then
				local value  = p:GetValue() or 0
				LogDebug("" .. tostring(i) .. " " .. v.name .. ' ' .. value) -- .. " " .. props:GetValueByID(i)); GetValueByName			
				--
			end;
			--LogDebug(props:GetValueByName(v.name));
		end;
    end);
	local userDatas = Game.Myself.data.userdata;
	LogDebug(tostring(Game.Myself.data.userdata:GetBytes(UDEnum.NAME)));
	LogDebug(tostring(Game.Myself.data.name));
    tableForEach(userDatas.datas,function(i,v)
		if (type(i) == 'number') then
			LogDebug("" .. i .. " " .. tostring(v));
			--local p = props:GetPropByName(v.name);
			--if p ~= nil then
			--	local value  = p:GetValue() or 0
			--	LogDebug("" .. tostring(i) .. " " .. v.name .. ' ' .. value) -- .. " " .. props:GetValueByID(i)); GetValueByName			
				--
			--end;
			--LogDebug(props:GetValueByName(v.name));
		end;
    end);
	
    
    --DumpMyself();
    local mons = ROM_GetAllNPC();	
    LogDebug("NPC List count=" .. #mons);
    --tableForEach(mons,function(i,v)
	for monIndex = 1,#mons do
		local v = mons[monIndex];
        LogDebug(MonsterToString(v));
		--local conf = NpcMonsterUtility.GetConfig(v.data.staticData.id);
		--LogDebug(MyTostring(conf));
		--ListField(conf,"",{}," ");
		local npcData = v.data.staticData;
		local npcfunc = npcData.NpcFunction;
		--LogDebug(MyTostring(npcfunc));
		for i=1,#npcfunc do
			local single = npcfunc[i];
			if(single.type)then
				local funcCfg = Table_NpcFunction and Table_NpcFunction[single.type];
				if(funcCfg and funcCfg.Type)then
					--LogDebug(" funcCfg.Type " .. MyTostring(funcCfg.Type));
					local configFunc = FunctionVisitNpc.SNpcFuncMap[funcCfg.Type]
					--LogDebug(" configFunc " .. MyTostring(configFunc));
					--if(configFunc and configFunc(npcfunc, target, events))then
					--	return;
					--end
				end
			end
		end
		
		local defaultDialogId = FunctionVisitNpc.GetDefaultDialog(v);
		--LogDebug(" npcData.DefaultDialog " .. MyTostring(npcData.DefaultDialog));
		--LogDebug(" defaultDialogId " .. MyTostring(defaultDialogId));
		local needRequireNpcFunc = npcData.NeedRequireNpcFunction;
		--LogDebug(" needRequireNpcFunc " .. MyTostring(needRequireNpcFunc));
    --end);
	end;
    LogDebug("Monster List count=" .. #mons);
    local mons = ROM_GetAllMonster();
    tableForEach(mons,function(i,v)
        LogDebug(CreatureToString(v));
    end);
	
    local npcList = Game.MapManager:GetNPCPointArray();
	LogDebug("npcList=" .. #npcList);
    tableForEach(npcList, function(i, v)
        if(v and v.ID and v.position)then
            local npcData = Table_Npc[v.ID];
            if npcData  then
                if npcData.id == 1125 then
                    --LogDebug(MyTostring(npcData));
                end;
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
--[[		
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
	]]
    
	--MsgManager.ShowMsgByID(25491);
	--local npcData = Table_Npc[1016];
	--ListField(npcData,"",{}," ");
	
	local nearestNPC, nearestDist = ROM_GetNearestNPC();	
	LogDebug(MonsterToString(nearestNPC));
--[[    
    LogDebug("--Table_Skill--");
    tableForEach(Table_Skill, function(i, v)
        local sk = v;
        if v.Level == 1 then
            local damages = v.Damage;
            if damages and #damages > 0 then
                local damage = damages[1];
                local func = CommonFun.CalcDamageFuncs[damage.type]
                if nil == func then
                    LogDebug("ID=" .. sk.id .. " " .. sk.NameZh .. " FUNC NOT FOUND");
                else
                    LogDebug("ID=" .. sk.id .. " " .. sk.NameZh .. " d-type=" .. damage.type );                
                end;
            end;
        end;
    end);
]]    
    
    --local players = ROM_GetNearPlayers();
    --UIUtil.FloatMsgByText("Players=" .. #players);	
    --ServicePlayerProxy.Instance:CallChangeMap("", 0, 0, 0, 8)
    
    local nearestNPC, nearestDist = ROM_GetNearestNPC();
    --Game.Myself:Client_LockTarget(nearestNPC);
    --ServiceQuestProxy.Instance:CallVisitNpcUserCmd(nearestNPC.data.id);
    --ServiceQuestProxy.Instance:CallRunQuestStep(300010075, nil, nil, 0); 
    LogDebug("--- questList -----");
	local qtab = {1,2,3,4};
	local qtabName = {"ACCEPT","COMPLETE","SUBMIT","CANACEPT"};
	tableForEach(qtab, function(_, index)
		LogDebug("--- questList " .. qtabName[index] .. "-----" .. #QuestProxy.Instance.questList[index]);
		for i, v in pairs(QuestProxy.Instance.questList[index]) do 
			--LogDebug(i);
			--LogDebug(tostring(v) .. " " .. v.id);
			--ListField(v,"",{}," ");
			if v ~= nil then
				-- only trace quest
				if v.whetherTrace == 1 and v.traceInfo and v.traceInfo ~= "" then
					LogDebug(QuestToString(v));
				end;
			end;
		end 
	end);

	local quest = ROM_GetBestQuest();
	if quest~= nil then
		--ROM_WalkToNPCPos(quest.params.npc);
	end;
    --ROM_WalkToNPCPos(1067);
    UIUtil.FloatMsgByText("Test Done 1");	
		
    if true then
        return;
    end;

    LogDebug("Skill");
    local skills = ROM_GetLearnSkill();
    tableForEach(skills,function(i,v)
        LogDebug(SkillToString(v));
    end);
    

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

function ROM_GetBestQuest()
	local currentMapID = Game.MapManager:GetMapID();
	local qtab = {1,2,3,4};
	local qtabName = {"ACCEPT","COMPLETE","SUBMIT","CANACEPT"};
	for i, v in pairs(QuestProxy.Instance.questList[1]) do 
		if v ~= nil then
			-- only trace quest
			if v.whetherTrace == 1 and v.traceInfo and v.traceInfo ~= "" then
				--LogDebug(QuestToString(v));
				if currentMapID == v.map then
					if v.questDataStepType == "visit" then
						LogDebug("ROM_GetBestQuest: found " .. QuestToString(v));
						return v;
					end;
				end;
			end;
		end;
	end 
	return nil;
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
			--GameFacade.Instance.sendNotification = GameFacade.Instance._sendNotification;
            --FunctionVisitNpc.openWantedQuestPanel = FunctionVisitNpc._openWantedQuestPanel
			--FunctionVisitNpc.me.AccessTarget = FunctionVisitNpc.me._AccessTarget;
			--ROM_UnHookFunc(FunctionVisitNpc.me,"AccessTarget");
            ROM_UnHookFunc(NetProtocol,"SendProto");
            ROM_UnHookFunc(NetProtocol,"Send");
			ROM_UnHookFunc(NetProtocol,"DispatchListener");
			LogDebug("UnHook done");
            
        else
            myTick:start();
            uiLabel.effectColor = ColorUtil.NGUILabelRed;
            uiLabel.effectStyle = UILabel.Effect.Outline;
			
			--GameFacade.Instance._sendNotification = GameFacade.Instance.sendNotification;
			--GameFacade.Instance.sendNotification = HOOK_SendNotification;
			--LogDebug("sendNotification org = " .. tostring(GameFacade.Instance._sendNotification));
			--LogDebug("sendNotification new = " .. tostring(GameFacade.Instance.sendNotification));
			--LogDebug(tostring(GameFacade.Instance.sendNotification));
            
            --FunctionVisitNpc._openWantedQuestPanel = FunctionVisitNpc.openWantedQuestPanel;
            --FunctionVisitNpc.openWantedQuestPanel = HOOK_openWantedQuestPanel;
			--GameFacade.Instance:sendNotification(UIEvent.ShowUI, viewdata );	
			--FunctionVisitNpc.me._AccessTarget = FunctionVisitNpc.me.AccessTarget;
			--FunctionVisitNpc.me.AccessTarget = HOOK_AccessTarget;
            --ROM_HookFunc(FunctionVisitNpc.me,"AccessTarget",HOOK_AccessTarget);
            ROM_HookFunc(NetProtocol,"SendProto",HOOK_SendProto);
            ROM_HookFunc(NetProtocol,"Send",HOOK_Send);
			ROM_HookFunc(NetProtocol,"DispatchListener",HOOK_NetProtocol_DispatchListener);
			
			--LogDebug("AccessTarget org = " .. tostring(FunctionVisitNpc.me._AccessTarget));
			--LogDebug("AccessTarget new = " .. tostring(FunctionVisitNpc.me.AccessTarget));
            LogDebug("Hook done");

			
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
        -- remember this position
        Game.Myself.autoPos = Game.Myself:GetPosition():Clone();
		Game.Myself.autoMapID = Game.MapManager:GetMapID();
        LogDebug("autoPos=" .. tostring(Game.Myself.autoPos) .. " autoMapID=" .. Game.Myself.autoMapID);
    end;
    UIUtil.FloatMsgByText("Auto " .. tostring(Game.Myself.ai.autoAI_Rom:IsEnable()));
end;

function ROM_Quest()
    local button = myButton["Quest"];
    local label = UIUtil.FindGO("Label",button);
    local uiLabel = label:GetComponent(UILabel);
    --uiLabel.effectColor = ColorUtil.NGUIWhite; --ColorUtil.Red;
    --LogDebug(MyTostring(uiLabel.effectColor));
	if Game.Myself.ai.autoQuest_Rom == nil then
		Game.Myself.ai.autoQuest_Rom = AutoQuest_Rom.new();
		Game.Myself.ai.idleAIManager:PushAI(Game.Myself.ai.autoQuest_Rom);
		LogDebug("set AutoQuest_Rom");
	else
		local index = TableUtil.FindKeyByValue(Game.Myself.ai.idleAIManager.ais,Game.Myself.ai.autoQuest_Rom);
        local old = Game.Myself.ai.autoQuest_Rom;
		Game.Myself.ai.autoQuest_Rom = AutoQuest_Rom.new();
		Game.Myself.ai.idleAIManager.ais[index] = Game.Myself.ai.autoQuest_Rom;
        Game.Myself.ai.autoQuest_Rom:Enable(old:IsEnable());
	end;
    if Game.Myself.ai.autoQuest_Rom:IsEnable() then
        Game.Myself.ai.autoQuest_Rom:Enable(false);
        uiLabel.effectStyle = UILabel.Effect.None;
    else
        Game.Myself.ai.autoQuest_Rom:Enable(true);
        uiLabel.effectColor = ColorUtil.NGUILabelRed;
        uiLabel.effectStyle = UILabel.Effect.Outline;
    end;
    UIUtil.FloatMsgByText("Auto Quest " .. tostring(Game.Myself.ai.autoQuest_Rom:IsEnable()));
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

function ROM_IsNear(pos1,pos2,range)
	range = range or 2;
	local distance = LuaVector3.Distance(pos1, pos2);
	LogDebug("ROM_IsNear: " .. distance .. " " .. tostring(pos1) .. " " .. tostring(pos2));
	return distance <= range
end;

function ROM_IsMeNear(mapID,pos,range)
	range = range or 2;
	local currentMapID = Game.MapManager:GetMapID();
	if currentMapID == mapID then
		local myPos = Game.Myself:GetPosition();	
		return ROM_IsNear(myPos,pos,range);
	end;
	return false;
end;

function ROM_GetOriginalPos(ID)
	local oriMonster = Table_MonsterOrigin[ ID] or {};
	local oriPos = nil;
	--local tmpPos = {};
	if #oriMonster == 0 then
		return nil;
	end;
	local randIndex = math.random(#oriMonster);
	oriPos = oriMonster[randIndex];
	LogDebug("ROM_GetOriginalPos " .. ID .. " randIndex=" .. randIndex .. " oriPos=" .. tostring(oriPos));        
	return oriPos;
end;

function ROM_CommandVisitMonster(mapID,monID)
		local oriMonster = Table_MonsterOrigin[ monID] or {};
		-- this will have mapID which contain that monsters
		LogDebug(MyTostring(oriMonster));
		local oriPos = nil;
        local tmpPos = {};
		for i=1,#oriMonster do
			if(oriMonster[i].mapID == mapID)then
				--oriPos = oriMonster[i].pos;
                tmpPos[#tmpPos+1] = oriMonster[i].pos;
                --break;
			end
		end
        local randIndex = math.random(#tmpPos);
        oriPos = tmpPos[randIndex];
        LogDebug("randIndex=" .. randIndex .. " oriPos=" .. tostring(oriPos));        
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
							if q.params.item ~= nil then
								local num = BagProxy.Instance:GetAllItemNumByStaticID(q.params.item[1].id);
								if num < q.params.item[1].num then
									LogDebug("" .. tostring(num) .. "/" .. tostring(q.params.item[1].num));
									return 
								end;
							end;
                            if  q.params.npc ~= nil then
                                LogDebug("ROM_CommandVisitMonster walk to npc");
                                ROM_WalkToNPC(q.map,q.params.npc,
                                    function()
										ROM_VisitNearestNPC();
                                        ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, nil, q.step); 
                                        GameFacade.Instance:sendNotification(UIEvent.CloseUI,UIViewType.DialogLayer);
                                        LogDebug(QuestToString(q));
                                        ROM_ClickNearestNPC(true);
                                    end
                                );
                            end;
                            LogDebug("Quest done");
                            --ROM_WalkToNPC(mapID,1016);
                            ROM_WalkToBoard();
                            
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

function ROM_WalkToNPCPos(npcID,finish)
	npcID = npcID or 1067;
	finish = finish or (function() end);
	local oriPos = ROM_GetOriginalPos(npcID);
	if oriPos then
		LogDebug("ROM_WalkToNPCPos: " .. npcID .. " " .. MyTostring(oriPos));
		-- check current location
		local npcPos = TableUtil.Array2Vector3(oriPos.pos);
		if ROM_IsMeNear(oriPos.mapID,npcPos) then
			finish();
		else	
			ROM_CommandGOTO(oriPos.mapID,npcPos,finish);
		end;
		return true;
	else	
		LogDebug("ROM_WalkToNPCPos: " .. npcID .. " original pos not found");
		return false;
	end;
end;

function ROM_CommandGOTO(mapID,pos,finish)
	finish = finish or (function() end);
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
            if event == 2 then
				if ROM_IsMeNear(mapID,tempVector3) then
					finish();
				else
					ROM_CommandGOTO(mapID,pos,finish)
				end
            end;
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

if g_mainView ~= nil then
	local tempVector3 = LuaVector3.zero
	local testButton = g_mainView:FindGO("TestFloat");
	local uiCamera = NGUIUtil:GetCameraByLayername("UI");	
	--LogDebug(GameObjectToString(uiCamera));
	--local obj = g_mainView:FindGO("SkillBord");
	--LogDebug(GameObjectToString(obj));
    local top_right = g_mainView:FindGO("Anchor_TopRight");
    --LogDebug(GameObjectToString(top_right,"",true));
	local buttons = {
		{name="Reload", pos=Vector3(0.05,0.70,0), func= function() if ROM_Reload() then UIUtil.FloatMsgByText("Reload Success"); end; end},
		{name="Test", 	pos=Vector3(0.05,0.63,0), func= ROM_Test},
		{name="Auto", pos=Vector3(0.05,0.56,0), func= ROM_Auto},
		{name="Quest", pos=Vector3(0.05,0.49,0), func= ROM_Quest},
		{name="Tick", pos=Vector3(0.05,0.42,0), func= ROM_MyTick},
		{name="Dlg", pos=Vector3(0.05,0.35,0), func= ROM_MyDlg},
	};
	for i=1,#buttons do
		local btn = buttons[i];
		if CreateMyButton(btn.name) then
			local button = myButton[btn.name];
			button.transform.position = uiCamera:ViewportToWorldPoint(btn.pos);
			button:SetActive(true);       
			--LogDebug("pos=" .. MyTostring(button.transform.position));
			g_mainView:AddClickEvent(button, function (g)
				btn.func(g);
			end);        
		end;
	end;
end;
--[[
	self:Listen(9, 89, function (data)
		self:RecvActivityNtfUserCmd(data) 
	end)
]]	


LogDebug("ROM Loaded 1.03");

