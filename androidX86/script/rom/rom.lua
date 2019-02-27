---- rom.lua ------
LOGFILENAME = "/data/local/tmp/rom.log";
if RomFileLogger == nil then
	RomFileLogger = {};
	RomFileLogger.f = io.open(LOGFILENAME, "a");
	--RomFileLogger.f:setvbuf ("line");
end;
RomFileLogger.log = function(data)
	RomFileLogger.f:write(data .. "\n");
	RomFileLogger.f:flush();
end;

RomFileLogger.reset = function()
    RomFileLogger.f:close();
	RomFileLogger.f = io.open(LOGFILENAME, "w");
    RomFileLogger.f:close();
    RomFileLogger.f = io.open(LOGFILENAME, "a");
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
    --LogDebug("ROM_SkillTarget");
    local skillInfo = ROM_GetMySkillInfoByName(tab.name);
    if skillInfo == nil then 
        LogDebug("ROM_SkillTarget: skill not found for " .. tab.name);
        return false 
    end;
    local skillID = skillInfo.staticData.id;
	if SkillProxy.Instance:SkillCanBeUsedByID(skillID) == false then
		local skillItem = SkillProxy.Instance:GetLearnedSkill(skillID)
		local inCD = SkillProxy.Instance:IsInCD(skillItem);
        --return self:IsInCD(SceneUser2_pb.CD_TYPE_SKILL,id) or self:IsInCD(SceneUser2_pb.CD_TYPE_SKILL,CDProxy.CommunalSkillCDSortID)
        local in1 = CDProxy.Instance:IsInCD(SceneUser2_pb.CD_TYPE_SKILL,skillItem.sortID);
        local in2 = CDProxy.Instance:IsInCD(SceneUser2_pb.CD_TYPE_SKILL,CDProxy.CommunalSkillCDSortID);
		LogDebug("ROM_SkillTarget: " .. tab.name .. " inCD=" .. tostring(inCD) .. ' ' .. tostring(in1) .. ' ' .. tostring(in2));		
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
			if tab.filter ~= nil and tab.filter(npc,tab) == false then
				return false;
			end;
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
	local ignoreLockTarget = tab.ignoreLockTarget or false
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
		if npc == nil or ignoreLockTarget == true then
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
    local filter = tab.filter or function(mon) return true end;
    local npc = ROM_GetMonsterLockTarget();
    if npc == nil then
        npc = ROM_FindBestMonster();
    end;
    if npc ~= nil and filter() then
        --ListField(npc,"",{},"  ");  
        local myPos = Game.Myself:GetPosition();
        local targetPosition = npc:GetPosition();
        local distance = LuaVector3.Distance(myPos, targetPosition);
        --LogDebug("ROM_WalkToRange: dist=" .. distance);
        if distance > range then
            LogDebug("ROM_WalkToRange walk to target");
			Game.AreaTrigger_ExitPoint:SetDisable(true)
            Game.Myself:Client_MoveTo(targetPosition, nil, 
				function(self,param)
					Game.AreaTrigger_ExitPoint:SetDisable(false)
					LogDebug("ROM_WalkToRange done");
				end, 
			nil, nil, range);
            return true;
        end;
    else
        --LogDebug("npc is null");
    end;
    return false;
end;

function ROM_Follow(tab)
	if not TeamProxy.Instance:IHaveTeam() then
		LogDebug("ROM_Follow: no team");
		return false
	end
	if ROM_AmITeamLeader() then
		LogDebug("ROM_Follow: I am leader");
		return false
	end;
	local leaderID = ROM_GetTeamLeaderID();
	LogDebug("ROM_Follow: " .. tostring(leaderID));
	local myTeam = TeamProxy.Instance.myTeam;
	local leader = myTeam:GetMemberByGuid(leaderID);
	local currentMapID = Game.MapManager:GetMapID()
	local leaderMapID = leader.mapid	
	if currentMapID ~= leaderMapID then
		LogDebug("ROM_Follow: leader on different map " .. leaderMapID .. " ~= " .. currentMapID);
		--ServiceNUserProxy.Instance:CallGoMapFollowUserCmd(leaderMapID, leaderID)
		ROM_CommandGOTO(leaderMapID);
		return true;
	else	
		local leaderTeamMember = myTeam:GetMemberByGuid(leaderID);
		local leaderPos = leaderTeamMember.pos	-- default data not accurate
		local leaderCreature = SceneCreatureProxy.FindCreature(leaderID)
		if leaderCreature then
			leaderPos = leaderCreature:GetPosition();
		end
		local dist = ROM_DistanceToPos(leaderPos);
		--local leaderPos = leaderCreature:GetPosition();
		--local dist = ROM_DistanceToCreature(leaderCreature);            
		LogDebug("ROM_Follow: " .. tostring(leaderPos) .. ' dist=' .. dist);
		if dist > 2 then 
			Game.Myself:Client_MoveTo(leaderPos, nil, 
					function(self,param)
						--Game.AreaTrigger_ExitPoint:SetDisable(false)
						LogDebug("ROM_Follow done");
					end, 
			nil, nil, 0.5);
			return true, 0;
		end;
	end;
	return false;
end;

function ROM_BuffTeam(tab)
	if not TeamProxy.Instance:IHaveTeam() then
		LogDebug("ROM_BuffTeam: no team");
		return false
	end
	
	--local ignoreLockTarget = tab.ignoreLockTarget or false
    local skillInfo = ROM_GetMySkillInfoByName(tab.name);
    if skillInfo == nil then 
		LogDebug("ROM_BuffTeam: skill name found " .. tab.name);
		return false 
	end;
    local skillID = skillInfo.staticData.id;
	
	if SkillProxy.Instance:SkillCanBeUsedByID(skillID) == false then
--		LogDebug("ROM_BuffNoTarget: " .. tab.name .. " skill can not be used");
		return false;
	end;
	local myTeam = TeamProxy.Instance.myTeam;
	if(myTeam)then
		local myMembers = myTeam:GetMembersList();
		for i=1,#myMembers do
			local memberData = myMembers[i];
			local id = memberData.id;
			local creature = SceneCreatureProxy.FindCreature(id);
			if creature then
				local dist = ROM_DistanceToCreature(creature);            
				--LogDebug("id=" .. id .. ' dist=' .. dist);
				if not ROM_HasBuffFromSkillID(skillID,creature) and dist < 5 then
					--LogDebug("ROM_BuffTeam: " .. SkillToStringByID(skillID));
					Game.Myself:Client_UseSkill(skillID, creature ,nil,nil,true);
					return true;
				end;
			end;
		end
	end
	
	--
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
			-- check team
			if not TeamProxy.Instance:IHaveTeam() then
				--LogDebug("ROM_Heal: no team");
				return false
			end
			local myTeam = TeamProxy.Instance.myTeam;
			if(myTeam)then
				local myMembers = myTeam:GetMembersList();
				for i=1,#myMembers do
					local memberData = myMembers[i];
					local id = memberData.id;
					local creature = SceneCreatureProxy.FindCreature(id);
					if creature then
						local dist = ROM_DistanceToCreature(creature);     
						local stat = ROM_GetMonStatus(creature);						
						--LogDebug("ROM_Heal id=" .. id .. ' dist=' .. dist .. );
						if stat.frachp < frac and dist < 5 and stat.hp > 0 then
							Game.Myself:Client_UseSkill(skillID, creature ,nil,nil,true);
							return true;
						end;
					end;
				end
			end

			
		end;
        --end;
    else
--        LogDebug("ROM_Heal: Not enough SP");
    end;
    return false;			
end;


function ROM_MonFullHP(npc)
    local monStatus = ROM_GetMonStatus(npc);
    return monStatus.frachp > 0.99 
end;

function ROM_NearestAvoidMonDist(refPos)
	local list = avoidMonList or {};
	local isAvoid = function(mon)
		return TableUtil.HasValue(list,mon.data.staticData.id)
	end;
	local mons = ROM_GetAllMonster(isAvoid);
	local minDist = 100000;
	for i,v in pairs(mons) do
		local pos = v:GetPosition();
		local dist = LuaVector3.Distance(refPos,pos);
		if dist < minDist then
			minDist = dist;
		end;
	end;
	return minDist;
end;


ROM_DoFile("/data/local/tmp/script/romConfig.lua");

function ROM_Test(g)
    LogDebug("----- ROM_Test --------");
    LogDebug(CreatureToString(Game.Myself) .. " mapID=" .. Game.MapManager:GetMapID()  .. ' leader=' .. tostring(ROM_AmITeamLeader()));
	LogDebug("--- Follower ---- " .. tostring(ROM_HasFollowers()));
	local followers = Game.Myself:Client_GetAllFollowers();
	LogDebug(MyTostring(followers));
    
    LogDebug(" --- Skill --- ");
    local skills = ROM_GetLearnSkill();
    tableForEach(skills,function(i,v)
        LogDebug(SkillToString(v));
    end);    
--[[    
    local props = Game.Myself.data.props;
    tableForEach(props.configs,function(i,v)
		if (type(i) == 'number') then
            LogDebug(ROM_PropGetName(props,i) .. " " .. tostring(props:GetValueByID(i)))
			--local p = props:GetPropByName(v.name);
			--if p ~= nil then
				--local value  = p:GetValue() or 0
            --LogDebug("" .. tostring(i) .. " " .. v.name .. ' ' .. value) -- .. " " .. props:GetValueByID(i)); GetValueByName			
				--
			--end;
			--LogDebug(props:GetValueByName(v.name));
		end;
    end);
	local userDatas = Game.Myself.data.userdata;
	--LogDebug(tostring(Game.Myself.data.userdata:GetBytes(UDEnum.NAME)));
	--LogDebug(tostring(Game.Myself.data.name));
    tableForEach(userDatas.datas,function(i,v)
		if (type(i) == 'number') then
			LogDebug("" .. ROM_DataGetName(i) .. " " .. tostring(v));
			--local p = props:GetPropByName(v.name);
			--if p ~= nil then
			--	local value  = p:GetValue() or 0
			--	LogDebug("" .. tostring(i) .. " " .. v.name .. ' ' .. value) -- .. " " .. props:GetValueByID(i)); GetValueByName			
				--
			--end;
			--LogDebug(props:GetValueByName(v.name));
		end;
    end);
	
	--tableForEach(UDEnum,function(i,v)
	--	LogDebug("" .. tostring(GetKey(v)) .. " " .. tostring(v));
	--end);
]]	
    
    --DumpMyself();
    local mons = ROM_GetAllNPC();	
    LogDebug("---- NPC List count=" .. #mons .. " -----");
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
        local myPos = Game.Myself:GetPosition();
        local npc = v;
		local pos = npc:GetPosition();
        local canArrive,path = NavMeshUtils.CanArrived(myPos, pos, WorldTeleport.DESTINATION_VALID_RANGE, true, nil);        
        local cost = NavMeshUtils.GetPathDistance(path);
        LogDebug(CreatureToString(v) .. ' ' .. tostring(canArrive) .. ' cost=' .. tostring(cost));
    end);
	
    local npcList = Game.MapManager:GetNPCPointArray();
	LogDebug("npcList=" .. #npcList);
    tableForEach(npcList, function(i, v)
        if(v and v.ID and v.position)then
            local npcData = Table_Npc[v.ID];
            if npcData then
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
                LogDebug("" .. i .. " to " .. ROM_GetMapName(v.nextSceneID) .. " " .. MyTostring(v));
        --    end;
        --end;
    end);
    
    local exitPoints2 = ROM_GetExitPoints(Game.MapManager:GetMapID());
    if exitPoints2 then
        LogDebug("exitPoints2=" .. #exitPoints2);
        for i,v in pairs(exitPoints2) do
            LogDebug("" .. i ..  " -> " ..  ROM_GetMapName(v));
        end;
    end;
	
	
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
	
	--local nearestNPC, nearestDist = ROM_GetNearestNPC();	
	--LogDebug(MonsterToString(nearestNPC));
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
	LogDebug("--- nearest NPC -----");    
    local nearestNPC, nearestDist = ROM_GetNearestNPC();
	if nearestNPC then
		LogDebug(CreatureToString(nearestNPC) .. " " .. nearestDist);
	end;
	--ROM_TeleportTo(22);	-- pay dun 2 = 22
    --Game.Myself:Client_LockTarget(nearestNPC);
    --ServiceQuestProxy.Instance:CallVisitNpcUserCmd(nearestNPC.data.id);
    --ServiceQuestProxy.Instance:CallRunQuestStep(300010075, nil, nil, 0); 
    LogDebug("--- questList -----");
	local qtab = {1,2,3,4};
	local qtabName = {"ACCEPT","COMPLETE","SUBMIT","CANACEPT"};
	tableForEach(qtab, function(_, index)
		if QuestProxy.Instance.questList[index] then
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
		end;
	end);

	local quest = ROM_GetBestQuest();
	if quest~= nil then
		--ROM_WalkToNPCPos(quest.params.npc);
	end;
    --ROM_WalkToNPCPos(1067);
	LogDebug("-- submitable quest --");
	local wq = ROM_GetSubmitableQuest();
	if wq then
		LogDebug(QuestToString(wq));
	end;
    LogDebug("-- ROM_GetAcceptedQuest ----");
    local wq = ROM_GetAcceptedQuest();
	if wq then
		LogDebug(QuestToString(wq));
	end;
    LogDebug("-- END ----");
    --ROM_DumpBag();
    --ROM_UseItem("Fly Wing");
    --local t = Game.WorldTeleport:CanArriveMap(Game.MapManager:GetMapID(),1)
    --LogDebug(tostring(t));
    for i,v in pairs(MapOutterTeleport[Game.MapManager:GetMapID()]) do
        if v.transitNPCToMap ~= nil then
            LogDebug(ROM_GetMapName(i) .. " " .. MyTostring(v));
        else
            --[5]={[1]={[4]={totalCost=122.6325302124,nextEP=2}}}
            --[1]={[1]={[5]={totalCost=24}}}
            local ep,v1 = next(v, nil);
            local retep,val = next(v1,nil);
            LogDebug(ROM_GetMapName(i) .. " exit=" .. ep .. " returnExit=" .. retep .. " " .. MyTostring(val));
        end;
        
    end;
	LogDebug("--- teleport able ---- ");
	for _, v in pairs(Table_Map) do
		--if v.Range == self.areaID and v.Money then
		if v.Money and v.MoneyType == 1 then	-- we can transport if v.MoneyType == 1 
			local path = ROM_GetPathToMap(Game.MapManager:GetMapID(),v.id);
			LogDebug(MapInfoToString(v) .. ' active=' .. tostring(ROM_IsActiveMap(v.id)) .. ' ' .. MyTostring(path));
		end
	end
    
    ROM_GetMapIDPath(Game.MapManager:GetMapID(),22);
    --[[
02/18/19 14:06:50  1 (table: 0x6a1a2710)
02/18/19 14:06:50   screen=0
02/18/19 14:06:50   callTime=3006.1437988281
02/18/19 14:06:50   shopID=1
02/18/19 14:06:50   goods (table: 0x6a1a2760)
02/18/19 14:06:50    92224 (table: 0x6a1a2800)
02/18/19 14:06:50     discountMax=0
02/18/19 14:06:50     RemoveDate=4294967295
02/18/19 14:06:50     des=
02/18/19 14:06:50     ItemID=5503
02/18/19 14:06:50     goodsID=5580
02/18/19 14:06:50     lockType=0
02/18/19 14:06:50     itemData table: 0x6fd3e2c0 >
02/18/19 14:06:50     LimitType=64
02/18/19 14:06:50     PreCost=0
02/18/19 14:06:50     LevelDes=
02/18/19 14:06:50     LimitNum=1
02/18/19 14:06:50     lock=false
02/18/19 14:06:50     business=0
02/18/19 14:06:50     source=0
02/18/19 14:06:50     MenuID=6010
02/18/19 14:06:50     produceNum=0
02/18/19 14:06:50     ItemCount=15
02/18/19 14:06:50     lockArg=ΘÇÜσà│µü⌐σ╛╖σïÆµû»σíö10σ▒éσÉÄΦºúΘöü
02/18/19 14:06:50     ShopOrder=12
02/18/19 14:06:50     Discount=100
02/18/19 14:06:50     actDiscount=0
02/18/19 14:06:50     id=92224
02/18/19 14:06:50     BaseLv=0
02/18/19 14:06:50     class table: 0x6deb8ac0 >
    ]]
    --ListField(ShopProxy.Instance.info,"",{},"    ");    
    LogDebug("------ shop info -------");
    for sid, v0 in pairs(ShopProxy.Instance.info) do
		local t,v = next(v0, nil);
		if v and v.shopID then			
			local ret = "type=" .. sid .. " shopID=" .. v.shopID;
			for _, g in pairs(v.goods) do
				local itemData = Table_Item[g.ItemID];
				local gitemData = Table_Item[g.goodsID];
				--local num = BagProxy.Instance:GetAllItemNumByStaticID(itemData.id);
				--ret = ret .. "\n" ..  PropToString(itemData," ",{"id","NameZh","Type"},{"MediaPath","Desc","TFValidDate","ValidDate","Icon"}) .. " num=" .. num .. " itemCount=" .. item.itemcount .. " configid=" .. item.configid;
				if gitemData then
					ret = ret .. "\n id=" .. g.id .. " ItemID=" .. itemData.id .. " name=" .. itemData.NameZh .. " Type=" .. itemData.Type ..  " ItemCount=" .. g.ItemCount .. " LimitNum=" .. g.LimitNum .. " goodsID=" .. g.goodsID .. ' lock=' .. tostring(g.lock) .. ' [' .. gitemData.NameZh .. ']'
				else
					ret = ret .. "\n id=" .. g.id .. " ItemID=" .. itemData.id .. " name=" .. itemData.NameZh .. " Type=" .. itemData.Type .. " " .. PropToString(g);
				end;			
			end;
			LogDebug(ret);
		end;
	end
	LogDebug("--- Table_NpcFunction ----");
	for _, v in pairs(Table_NpcFunction) do
		if v.Type == "Common_Shop" then
			LogDebug(PropToString(v) .. ' Parama=' .. MyTostring(v.Parama));
		end;
	end;
    --LogDebug("--- FIND -----")
	--for _, npc in pairs(Table_Npc) do
	--	LogDebug("" .. npc.id .. " " .. npc.NameZh .. " " .. PropToString(npc.NpcFunction[1],"NpcFunction."));
	--end;

	
    UIUtil.FloatMsgByText("Test Done 1");	
	--local followingTeammatesID = UIModelKaplaTransmit.Ins():GetFollowingTeammates()
	--ServiceNUserProxy.Instance:CallGoToGearUserCmd(self.mapInfo.id, SceneUser2_pb.EGoToGearType_Team, followingTeammatesID)
	
	--ServiceNUserProxy.Instance:CallGoToGearUserCmd(18, SceneUser2_pb.EGoToGearType_Single, nil);
		
    if true then
        return;
    end;


    

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

function ROM_HasBuffFromSkillID(skillID,player)
	player = player or Game.Myself;
    local skillInfo = Game.LogicManager_Skill:GetSkillInfo(skillID);
    local buffs = skillInfo:GetSelfBuffs(player);
    return player:HasBuffs(buffs);
end;

function ROM_MyCheat()
    local button = myButton["Cheat"];
    local label = UIUtil.FindGO("Label",button);
    local uiLabel = label:GetComponent(UILabel);
    if Game.Myself.myCheat == nil then
        Game.Myself.myCheat = false;
    end;
    if Game.Myself.myCheat then
        Game.Myself.myCheat = false;
        uiLabel.effectStyle = UILabel.Effect.None;
    else
        Game.Myself.myCheat = true;
        uiLabel.effectColor = ColorUtil.NGUILabelRed;
        uiLabel.effectStyle = UILabel.Effect.Outline;
    end;
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

if farmData == nil then
farmData = {};
end;
function ROM_MyDlg()
		local viewdata = {
		viewname = "DialogView",
		tasks = nil,
		dialoglist = {"เล่นกันดีๆไท้ได้เหรอ]"},
	};
	viewdata.addfunc = {
--[[		{
			event = function (npcinfo,param)
                farmData.mapID = Game.MapManager:GetMapID();
                farmData.pos = Game.Myself:GetPosition():Clone();
				UIUtil.FloatMsgByText(MyTostring(farmData));	
			end,
			--eventParam = {"haha"},
			closeDialog = true,
			NameZh = "RememberPos",
			
		},
		{
			event = function (npcinfo)
				FunctionNpcFunc.JumpPanel(PanelConfig.ChangeZoneView, npcinfo)
			end,
			closeDialog = true,
			NameZh = ZhString.ChangeZone_ChangeLine
		},]]
		{
			event = function (npcinfo)
                --GameFacade.Instance:sendNotification(UIEvent.ShowUI,{viewname = "AgreementPanel"});
                --GameFacade.Instance:sendNotification(UIEvent.ShowUI,{viewname = "SystemUnLockView"});
                --local UniqueConfirmView = class("UniqueConfirmView",BaseView)
                --UniqueConfirmView.ViewType = UIViewType.ConfirmLayer;
                --GameFacade.Instance:sendNotification(UIEvent.ShowUI,{viewname = "SystemUnLockView"});
                --ServiceSessionShopProxy.Instance:CallQueryShopConfigCmd(600, 11);
				-- 600,1  general shop
				-- 600,4  food
				-- 600,11  toy shop
				--[[
				02/19/19 08:29:39 type=904 shopID=1
 id=100000 ItemID=5250 name=Creste's Royal Medal Type=61 ItemCount=2500 LimitNum=0 goodsID=17542 lock=true [Mask of Darkness Blueprint]
 
 02/19/19 08:31:22 type=700 shopID=2
 id=31040 ItemID=100 name=Zeny Type=131 ItemCount=9000 LimitNum=0 goodsID=40330 lock=false [Blade]

 
 02/19/19 08:32:27 type=750 shopID=2
 id=41040 ItemID=100 name=Zeny Type=131 ItemCount=8600 LimitNum=0 goodsID=42027 lock=false [Mantle]
 
 02/19/19 08:34:06 type=922 shopID=1
 id=26080 ItemID=5502 name=Nibelungen Shard Type=61 ItemCount=300 LimitNum=0 goodsID=41234 lock=false [Epic SpiritยทHerist's Bow]
 
 02/19/19 08:35:37 type=908 shopID=1
 id=140000 ItemID=150 name=Fighter Coin Type=141 ItemCount=1000 LimitNum=1 goodsID=48566 lock=false [Marchosias' Arrow]
 id=140010 ItemID=150 name=Fighter Coin Type=141 ItemCount=1500 LimitNum=1 goodsID=48565 lock=false [Marchosias' Gaze]
 id=140020 ItemID=150 name=Fighter Coin Type=141 ItemCount=1500 LimitNum=1 goodsID=48009 lock=false [Marchosias' Tail]
 
02/19/19 08:39:02 type=800 shopID=1000
 id=59040 ItemID=110 name=Eden Coin Type=140 ItemCount=1200 LimitNum=0 goodsID=14306 lock=true [Snake hairpin Blueprint]
 id=59010 ItemID=110 name=Eden Coin Type=140 ItemCount=300 LimitNum=0 goodsID=14302 lock=false [Monkey Circlet Blueprint] 
 
 02/19/19 08:40:07 type=605 shopID=1
 id=8000 ItemID=5525 name=Colorful Shell Type=61 ItemCount=10 LimitNum=0 goodsID=900001 lock=false [Green Apple]
 id=8050 ItemID=5525 name=Colorful Shell Type=61 ItemCount=150 LimitNum=0 goodsID=900004 lock=true [Nutrition Potion]
 id=8020 ItemID=5525 name=Colorful Shell Type=61 ItemCount=40 LimitNum=0 goodsID=900003 lock=false [Tropical Banana]
 
02/19/19 08:44:24 type=950 shopID=7
 id=1006000 ItemID=100 name=Zeny Type=131 ItemCount=50000 LimitNum=0 goodsID=46041 lock=true [The Fighter]
 id=1006050 ItemID=12109 name=Scarlet Dyestuffs Type=70 id=1006050,LimitType=0,business=0,actDiscount=0,lockType=0,produceNum=0,PreCost=710030,ItemCount=1,Discount=100,source=0,MenuID=0,LimitNum=0,Rem
oveDate=4294967295,LevelDes=,lockArg=,ItemID=12109,BaseLv=0,discountMax=0,hairColorID=2,des=,ShopOrder=6,
 id=1006020 ItemID=100 name=Zeny Type=131 ItemCount=15000 LimitNum=0 goodsID=46042 lock=true [The Light Shield]
 id=1006070 ItemID=12116 name=White Dyestuffs Type=70 id=1006070,LimitType=0,business=0,actDiscount=0,lockType=0,produceNum=0,PreCost=710030,ItemCount=1,Discount=100,source=0,MenuID=0,LimitNum=0,Remov 
 
02/19/19 08:46:32 type=912 shopID=1
 id=190000 ItemID=52624 name=Tattered Time Pointer Type=61 ItemCount=1580 LimitNum=0 goodsID=17569 lock=true [Time Observation Blueprint]
 id=190010 ItemID=52624 name=Tattered Time Pointer Type=61 ItemCount=15804 LimitNum=0 goodsID=14251 lock=true [Gold Clock Guardian [1] Blueprint]
 id=190020 ItemID=52624 name=Tattered Time Pointer Type=61 ItemCount=19755 LimitNum=0 goodsID=16026 lock=true [Back in Time Blueprint]

02/19/19 08:50:31 type=3003 shopID=1
 id=180640 ItemID=110 name=Eden Coin Type=140 ItemCount=20 LimitNum=1 goodsID=52203 lock=false [Immortal Heart]
 id=180750 ItemID=110 name=Eden Coin Type=140 ItemCount=60 LimitNum=1 goodsID=52505 lock=false [Skel-Bone]
 id=180740 ItemID=110 name=Eden Coin Type=140 ItemCount=40 LimitNum=1 goodsID=52205 lock=false [Hand of God] 
 
 02/19/19 08:52:49 type=1502 shopID=160
 id=1400000 ItemID=53097 name=Gold Snake Eye Type=62 ItemCount=1 LimitNum=0 goodsID=40037 lock=false [Ouroboros Spear]
 id=1400050 ItemID=53097 name=Gold Snake Eye Type=62 ItemCount=1 LimitNum=0 goodsID=41236 lock=false [Ouroboros Bow]
 id=1400020 ItemID=53097 name=Gold Snake Eye Type=62 ItemCount=1 LimitNum=0 goodsID=40639 lock=false [Ouroboros Staff]
 id=1400070 ItemID=53097 name=Gold Snake Eye Type=62 ItemCount=1 LimitNum=0 goodsID=41847 lock=false [Ouroboros Axe]
 
 02/19/19 11:57:02 type=950 shopID=1
 id=1000000 ItemID=100 name=Zeny Type=131 ItemCount=10000 LimitNum=0 goodsID=46001 lock=true [The Tech]
 id=1000130 ItemID=100 name=Zeny Type=131 ItemCount=20000 LimitNum=0 goodsID=46020 lock=true [The Natural]
 id=1000100 ItemID=100 name=Zeny Type=131 ItemCount=2000 LimitNum=0 goodsID=46014 lock=false [The Monk]
 
02/19/19 11:59:16 type=750 shopID=1
 id=40000 ItemID=100 name=Zeny Type=131 ItemCount=1400 LimitNum=0 goodsID=43001 lock=false [Eden Team Manteau I]
 id=40050 ItemID=100 name=Zeny Type=131 ItemCount=4700 LimitNum=0 goodsID=42503 lock=false [Buckler] 
 
 02/19/19 12:04:03 type=1400 shopID=1
 id=320 ItemID=100 name=Zeny Type=131 id=320,business=0,discountMax=0,MenuID=0,LevelDes=,ItemID=100,LimitNum=0,RemoveDate=4294967295,produceNum=0,lockArg=,LimitType=0,ShopOrder=45,BaseLv=0,SkillID=500
51001,source=0,Discount=100,PreCost=0,ItemCount=1000000,lockType=0,actDiscount=0,des=,
 id=130 ItemID=100 name=Zeny Type=131 id=130,business=0,discountMax=0,MenuID=0,LevelDes=,ItemID=100,LimitNum=0,RemoveDate=4294967295,produceNum=0,lockArg=,LimitType=0,ShopOrder=13,BaseLv=1,SkillID=500
08001,source=0,Discount=100,PreCost=0,ItemCount=30000,lockType=0,actDiscount=0,des=,
 id=260 ItemID=100 name=Zeny Type=131 id=260,business=0,discountMax=0,MenuID=0,LevelDes=,ItemID=100,LimitNum=0,RemoveDate=4294967295,produceNum=0,lockArg=,LimitType=0,ShopOrder=37,BaseLv=1,SkillID=500
29001,source=0,Discount=100,PreCost=0,ItemCount=400000,lockType=0,actDiscount=0,des=,
 id=70 ItemID=100 name=Zeny Type=131 id=70,business=0,discountMax=0,MenuID=0,LevelDes=,ItemID=100,LimitNum=0,RemoveDate=4294967295,produceNum=0,lockArg=,LimitType=0,ShopOrder=7,BaseLv=1,SkillID=500260
01,source=0,Discount=100,PreCost=0,ItemCount=30000,lockType=0,actDiscount=0,des=,

02/19/19 14:07:44 type=3004 shopID=1
 id=1700020 ItemID=52626 name=Edelweiss Type=61 ItemCount=2 LimitNum=20 goodsID=52208 lock=false [Frozen Heart]
 id=1700030 ItemID=52626 name=Edelweiss Type=61 ItemCount=5 LimitNum=5 goodsID=52412 lock=false [Christmas Garland]
 id=1700040 ItemID=52626 name=Edelweiss Type=61 ItemCount=10 LimitNum=5 goodsID=52516 lock=false [Christmas Socks]
02/19/19 14:22:00 type=3007 shopID=1
 id=180000 ItemID=100 name=Zeny Type=131 ItemCount=300 LimitNum=3 goodsID=550520 lock=true [Yoyo Banana]
 id=180050 ItemID=100 name=Zeny Type=131 ItemCount=360 LimitNum=4 goodsID=550503 lock=true [Eggshell Chick]
 id=180020 ItemID=100 name=Zeny Type=131 ItemCount=425 LimitNum=4 goodsID=550522 lock=true [Moai Melon]
 id=180150 ItemID=100 name=Zeny Type=131 ItemCount=500 LimitNum=4 goodsID=550517 lock=true [Gold Pumpkin] 
 				]]
				
				
                --ShopProxy.Instance:CallQueryShopConfig(3004, 2); -- just do more checking
				--ServiceSessionShopProxy.Instance:CallQueryShopConfigCmd(3003, 1);
				--local npcFunc = ;
				FunctionNpcFunc.Me():DoNpcFunc(Table_NpcFunction[300], nil, 1 );
			end,
			closeDialog = true,
			NameZh = "Test Shop"
		},
		{
			event = function (npcinfo)
                --if farmData.pos then
                --    ServicePlayerProxy.Instance:CallMoveTo(farmData.pos[1], farmData.pos[2], farmData.pos[3])	
                --end;
                ServiceGuildCmdProxy.Instance:CallDonateListGuildCmd();
                ServiceGuildCmdProxy.Instance:CallDonateFrameGuildCmd(true);
                LogDebug("Done");
			end,
			--closeDialog = true,
			NameZh="Guild Donate",
			
		},
		{
			event = function (npcinfo)
                RomFileLogger.reset();
			end,
			--closeDialog = true,
			NameZh="Log Reset",
		},
		{
			event = function (npcinfo) FunctionNpcFunc.Me():DoNpcFunc(Table_NpcFunction[3004], nil, 1 ); end, closeDialog = true, NameZh="Greedy Shop",
		},
--[[		{
			event = function (npcinfo) FunctionNpcFunc.Me():DoNpcFunc(Table_NpcFunction[850], nil, 1 ); end, closeDialog = true, NameZh="FriendShip Shop",
		},]]
		{
			event = function (npcinfo) FunctionNpcFunc.Me():DoNpcFunc(Table_NpcFunction[3003], nil, 1 ); end, closeDialog = true, NameZh="Lucky Shop",
		},
		{
			event = function (npcinfo) FunctionNpcFunc.Me():DoNpcFunc(Table_NpcFunction[3001], nil, 1 ); end, closeDialog = true, NameZh="Teleport",
		},
		{
			event = function (npcinfo) FunctionNpcFunc.Me():DoNpcFunc(Table_NpcFunction[5000], nil, 1 ); end, closeDialog = true, NameZh="Exchange",
		},
		{
			event = function (npcinfo) FunctionNpcFunc.Me():DoNpcFunc(Table_NpcFunction[100], nil, 1 ); end, closeDialog = true, NameZh="Storage",
		},
		{
			event = function (npcinfo) FunctionNpcFunc.Me():DoNpcFunc(Table_NpcFunction[302], nil, 1 ); end, closeDialog = true, NameZh="DeCompose",
		},
		
		{
			event = function (npcinfo)
                local status,err = pcall(function()
                    LogDebug("Test Start")
                    local config = {
                        myMonsterList = {10081},
                        myMonsterRules = myMonsterRules,
                        myAIRules = myAIRules,
                        walkBack = false,
                    };
                    --local oldConfig = ROM_SetConfig(config)
                    
                    local cmdArgs = {
                        --monID = 10081,
                        config = config,
                        --targetMapID = 0,
                        --targetPos = 0,
                    }
                    Game.Myself:Client_SetMissionCommand(nil );
                    local cmd = ReusableObject.Create( MissionCommandHunt, true, cmdArgs );
                    --local cmd = MissionCommandFactory.CreateCommand(cmdArgs, MissionCommandHunt);
                    if(cmd)then
                        Game.Myself:Client_SetMissionCommand(cmd );
                    else
                        LogDebug("cmd error");
                    end
                    LogDebug("Test End")
                end);
                if status == false then
                    LogDebug("ERROR: " .. singleLine(tostring(err)));
                    return false
                end;
			end,
			closeDialog = true,
			NameZh="Test",
		},
        
        
	};
	--local dialogInfo ={ DialogUtil.GetDialogData(defaultDialogId) };
	--ListField(dialogInfo,"",{},"      ");
	GameFacade.Instance:sendNotification(UIEvent.ShowUI, viewdata);
end;

function ROM_IsNear(pos1,pos2,range)
	range = range or 2;
	local distance = LuaVector3.Distance(pos1, pos2);
	LogDebug("ROM_IsNear: " .. distance .. " " .. tostring(pos1) .. " " .. tostring(pos2) .. ' ' .. range);
	return distance <= range
end;

function ROM_DistanceToCreature(creature)
    --local myPos = Game.Myself:GetPosition();	
    local toPos = creature:GetPosition();	
    return ROM_DistanceToPos(toPos);
end;

function ROM_DistanceToPos(toPos)
    local myPos = Game.Myself:GetPosition();	
    return LuaVector3.Distance(myPos, toPos);
end;

function ROM_IsMeNear(mapID,pos,range)
	range = range or 4;
	local currentMapID = Game.MapManager:GetMapID();
	if currentMapID == mapID then
		local myPos = Game.Myself:GetPosition();	
		return ROM_IsNear(myPos,pos,range);
	end;
	return false;
end;

function ROM_GetOriginalPoses(ID,mapID)
	local oriMonster = ROM_tabMonsterOrigin[ID] or Table_MonsterOrigin[ ID] or {};
	local oriPos = nil;
	--local tmpPos = {};
	if oriMonster == nil or #oriMonster == 0 then
		return nil;
	end;
    if mapID then
        local tmpPos = {};
        for i=1,#oriMonster do
            if(oriMonster[i].mapID == mapID)then
                --oriPos = oriMonster[i].pos;
               tmpPos[#tmpPos+1] = oriMonster[i];
            end
        end
        LogDebug("ROM_GetOriginalPoses " .. ID .. " " ..  #tmpPos);
        return tmpPos;
    end
	LogDebug("ROM_GetOriginalPoses " .. ID .. " " ..  #oriMonster);
	return oriMonster;
end;

function ROM_GetOriginalPos(ID)
	local oriMonster = ROM_GetOriginalPoses(ID)
	if oriMonster == nil then
		return nil;
	end;
	local oriPos = nil;
	LogDebug("ROM_GetOriginalPos " .. ID .. " " ..  #oriMonster);
	local randIndex = 1;
	--if #oriMonster > 1 then
	--	randIndex = math.random(#oriMonster);
	--end;
	oriPos = oriMonster[randIndex];
	LogDebug("ROM_GetOriginalPos " .. ID .. " randIndex=" .. randIndex .. " oriPos=" .. tostring(oriPos));        
	return oriPos;
end;

function ROM_GetMonsterByGroupID(groupID)
	local ret = {};
	for i,v in pairs(Table_Monster) do
		if v.GroupID == groupID and v.id < 20000 then
			ret[#ret + 1] = v;
			--LogDebug(MyTostring(v));
		end;
	end;
	return ret;
end;

function ROM_CommandVisitMonster(mapID,monID)
		local oriPos = ROM_GetOriginalPos(monID,mapID);
        LogDebug("ROM_CommandVisitMonster oriPos=" .. MyTostring(oriPos));        
		if(oriPos)then
            local currentMapID = Game.MapManager:GetMapID();
            local nearestTownID = ROM_GetNearestTown() or 1;
            --if ROM_MapDist(currentMapID,mapID) > ROM_MapDist(nearestTownID,mapID) then
            --    LogDebug("ROM_CommandVisitMonster teleport =" .. nearestTownID);        
            --    ROM_TeleportTo(mapID);
            --end;
			local cmdArgs = {
				targetMapID = mapID,
				npcID = monID,
				targetPos = TableUtil.Array2Vector3(oriPos.pos),
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
                                if q.params.team_can_finish and q.params.team_can_finish ~= 1 then 
                                    LogDebug("ROM_CommandVisitMonster: wait for team 2");                                    
                                else
                                    -- might need to wait here
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
                            end;
                            if q.params.team_can_finish and q.params.team_can_finish ~= 1 then 
                                LogDebug("ROM_CommandVisitMonster: wait for team");                                                        
                            else
                                LogDebug("ROM_CommandVisitMonster: Quest done");                            
                                ROM_WalkToBoard();
                            end;
                            
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
		else	
			LogDebug("ROM_CommandVisitMonster " .. monID .. " original pos not found");
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

function ROM_WalkToNPCPos(npcID,mapID,finish)
	npcID = npcID or 1067;
	finish = finish or (function() end);
	local oriPoses = ROM_GetOriginalPoses(npcID,mapID);
	if oriPoses == nil then
		LogDebug("ROM_WalkToNPCPos: not found " .. npcID .. " " .. mapID );
		return false;
	end;
	--local oriPos = ROM_GetOriginalPos(npcID);
	local oriPos = oriPoses[1];
	if oriPos then
		LogDebug("ROM_WalkToNPCPos: " .. npcID .. " " .. MyTostring(oriPos));
		-- check current location
		local npcPos = TableUtil.Array2Vector3(oriPos.pos);
		if ROM_IsMeNear(oriPos.mapID,npcPos) then
			finish();
			return true;
		else	
			ROM_CommandGOTO(oriPos.mapID,npcPos,finish);
			return false;
		end;
		
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
        LogDebug("ROM_CommandGOTO: targetPos=" .. tostring(tempVector3));
        tempArgs.callback = function(cmd, event)
            LogDebug("ROM_CommandGOTO: cmd=" .. MyTostring(cmd));
            LogDebug("ROM_CommandGOTO: event=" .. MyTostring(event));
            if MissionCommandMove.CallbackEvent.TeleportFailed == event then
                LogDebug("ROM_CommandGOTO: event=TeleportFailed");
                --Game.Myself:Client_MoveTo( tempVector3 );
            end
            if event == 2 then
				if ROM_IsMeNear(mapID,tempVector3) then
					finish();
				else
					Game.Myself:Client_MoveTo( tempVector3 );
				--	ROM_CommandGOTO(mapID,pos,finish)
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
        {name="Cheat", pos=Vector3(0.05,0.28,0), func= ROM_MyCheat},
	};
	for i=1,#buttons do
		local btn = buttons[i];
		if CreateMyButton(btn.name) then
			local button = myButton[btn.name];
			button.transform.position = uiCamera:ViewportToWorldPoint(btn.pos);
			button:SetActive(true);       
			--LogDebug("pos=" .. MyTostring(button.transform.position));
			g_mainView:AddClickEvent(button, function (g)
                local status,err = pcall(function()
                    btn.func(g);
                end);
                if status == false then
                    LogDebug("ERROR: " .. singleLine(tostring(err)));
                    return false
                end;
			end);        
		end;
	end;
end;
--[[
	self:Listen(9, 89, function (data)
		self:RecvActivityNtfUserCmd(data) 
	end)
]]	

--LogDebug("\n" .. ROM_CreateSendPackets());
LogDebug("ROM Loaded 1.03");

