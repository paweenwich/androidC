-- romUtil.lua ----
function splitByChunk(text, chunkSize)
    local s = {}
    for i=1, #text, chunkSize do
        s[#s+1] = text:sub(i,i+chunkSize - 1)
    end
    return s
end

function tableForEach(t, f) 
        for i, v in pairs(t) do f(i,v) end 
end 

function tableIsEmpty(t)
    for _,_ in pairs(t) do
        return false
    end
    return true
end



function GameObjectToString(go,tab,visible)
	tab = tab or "";
	if go == nil then return "NULL"; end;
	local ret = tab .. UserDataToString(go);
	local trans = go.transform;
	for i=0, trans.childCount-1 do
		local goChild = trans:GetChild(i).gameObject;
        if visible == nil or goChild.activeSelf == visible then
            ret = ret .. "\n" .. GameObjectToString(goChild,tab .. " ",visible);
        end;
	end
	return ret;
end;


function UserDataToString(value)
	local ret = "[" .. type(value) .. "] " .. tostring(value);
	if string.match(ret, "(UnityEngine.GameObject)") then	
		--ret = "[GameObject] name=" .. tostring(value.name) .. " scene=" .. MyTostring(value.scene) .. " " .. tostring(value.activeSelf);
        if value.name == "Label" then
            local label = value:GetComponent(UILabel);
            if label ~= nil then
                ret = "[GameObject] name=" .. tostring(value.name) ..  " text=" .. label.text .. " " .. tostring(value.activeSelf);        
                return ret;
            end;
        end;
        ret = "[GameObject] name=" .. tostring(value.name) ..  " " .. tostring(value.activeSelf);        
	end;
	if string.match(ret, "(UnityEngine.SceneManagement.Scene)") then	
		--ret = "[Scene] name=" .. value.name .. " path=" .. value.path .. " rootCount=" .. value.rootCount;
		ret = "[Scene] name=" .. value.name .. " #root=" .. value.rootCount;
	end;
	if string.match(ret, "(UISprite)") then	
		ret = "[UISprite] name=" .. value.name .. " spriteName=" .. value.spriteName;
	end;
	if string.match(ret, "(UILabel)") then	
		ret = "[UILabel] name=" .. value.name .. " text=" .. value.text .. " fontSize=" .. value.fontSize;
	end;
	
	return ret;
end;

function ListField(obj,tab,tableHash,targetTab,ignore)
    ignore = ignore or {};
    targetTab = targetTab or "       ";
    tab = tab or "";
	tableHash = tableHash or {};
    if (type(obj) == 'table') then
		-- check if we visit this able before
		if tableHash[tostring(obj)]  ~= nil then
			return tab .. tostring(obj) .. "*";
		end;
		tableHash[tostring(obj)] = true;
		-- check if it a custom lua object
		--if obj["__cname"] ~= nil and obj["super"] ~= nil then
		--	LogDebug(tab .. "[" .. obj.__cname .. "] " .. tostring(obj));
		--end;
        tableForEach(obj, function(i, v)
            
			if (type(i) == 'userdata') then
				LogDebug(tab .. "[" .. tostring(i) ..  "] " .. tostring(v));			
				return;
			end;
--			if (type(i) == 'number') then
--				LogDebug(tab .. "[" .. i ..  "] " .. tostring(v));			
--				return;
--			end;
			if (type(i) == 'string') or (type(i) == 'number') then
                local key = tostring(i);
				if (key == "__cname") or  (key == "__ctype") then
					return;
				end;
                if TableUtil.HasValue(ignore,key) then
                    return;
                end;
				-- skip function
				if(type(v) == 'function') then
					LogDebug(tab .. "func " .. key .. "=" .. tostring(v));
					return;
				end;
				if(type(v) == 'table') then
					if tab == targetTab then
						LogDebug(tab .. key .. " " .. tostring(v) .. " >");			
					else
                        if tableIsEmpty(v) == false then
                            LogDebug(tab .. key .. " (" .. tostring(v) .. ")");							
                            ListField(v,tab .. " ",tableHash,targetTab,ignore);
                        else
                            LogDebug(tab .. key .. " " .. tostring(v) .. " {}");							
                        end;
					end;
				else
					LogDebug(tab .. key .. "=" .. tostring(v));
				end;
				return;
			end;
			LogDebug(tab .. tostring(i) .. "=" .. tostring(v));
        end)
    else
        LogDebug(tostring(obj));
    end;
end;


function MyTostring(value,level)
  local str = ''
  if level == nil then level = 0; end;
  if level > 2 then
	return tostring(value);
  end
  if (type(value) ~= 'table') then
	if type(value) == 'userdata' then
		return UserDataToString(value);
	end;
	if type(value) == 'function' then
		return "[func]";
	end;
	if type(value) == 'boolean' then
		return tostring(value);
	end;
	if (type(value) == 'number') then
	  str = "" .. value;
    else 
		if (type(value) == 'string') then
		  --str = string.format("%q", value)
		  str = string.format("%s", value)
		else
			if(value == nil) then
				str = "(nil)";
			else
				str = "[" .. type(value) .. "] " .. tostring(value);
			end;
		end
	end;
  else
    local auxTable = {}
    --table.foreach(value, function(i, v)
	tableForEach(value, function(i, v)
      if (tonumber(i) ~= i) then
        table.insert(auxTable, i)
      else
        table.insert(auxTable, tostring(i))
      end
    end)
    table.sort(auxTable)

    str = str..'{'
    local separator = ""
    local entry = ""
    --table.foreachi (auxTable, function (i, fieldName)
	tableForEach(auxTable, function (i, fieldName)
      if ((tonumber(fieldName)) and (tonumber(fieldName) > 0)) then
        entry = MyTostring(value[tonumber(fieldName)],level + 1)
      else
        entry = fieldName.." = ".. MyTostring(value[fieldName], level + 1)
      end
      str = str..separator..entry
      separator = ", "
    end)
    str = str..'}'
  end
  return str
end




function DumpMyself()
    LogDebug("SKILL_POINT=" .. (Game.Myself.data.userdata:Get(UDEnum.SKILL_POINT) or 0));
    LogDebug("BATTLEPOINT=" .. (Game.Myself.data.userdata:Get(UDEnum.BATTLEPOINT) or 0));
    LogDebug("ROLEEXP=" .. (Game.Myself.data.userdata:Get(UDEnum.ROLEEXP) or 0));
    LogDebug("JOBEXP=" .. (Game.Myself.data.userdata:Get(UDEnum.JOBEXP) or 0));
    LogDebug("KILLERNAME=" .. (Game.Myself.data.userdata:Get(UDEnum.KILLERNAME) or 0));
    LogDebug("DROPBASEEXP=" .. (Game.Myself.data.userdata:Get(UDEnum.DROPBASEEXP) or 0));
    LogDebug("NORMAL_SKILL=" .. (Game.Myself.data.userdata:Get(UDEnum.NORMAL_SKILL) or 0));
    LogDebug("PET_PARTNER=" .. (Game.Myself.data.userdata:Get(UDEnum.PET_PARTNER) or 0));
    LogDebug("NAME=" .. (Game.Myself.data.userdata:Get(UDEnum.NAME) or 0));
    LogDebug("proxyName=" .. MyselfProxy.Instance.proxyName);
    LogDebug("Level=" .. MyselfProxy.Instance:RoleLevel());
    LogDebug("Zeny=" .. MyselfProxy.Instance:GetROB());
    LogDebug("Gold=" .. MyselfProxy.Instance:GetGold());
    LogDebug("Diamond=" .. MyselfProxy.Instance:GetDiamond());
    LogDebug("Garden=" .. MyselfProxy.Instance:GetGarden());
    LogDebug("Laboratory=" .. MyselfProxy.Instance:GetLaboratory());
    LogDebug("JobLevel=" .. MyselfProxy.Instance:JobLevel());
    LogDebug("ZoneId=" .. MyselfProxy.Instance:GetZoneId());
    LogDebug("ZoneString=" .. MyselfProxy.Instance:GetZoneString());
    LogDebug("GetMyProfession=" .. MyselfProxy.Instance:GetMyProfession());
    LogDebug("GetMyProfessionType=" .. MyselfProxy.Instance:GetMyProfessionType());
    LogDebug("GetMyMapID=" .. MyselfProxy.Instance:GetMyMapID());
    LogDebug("GetMySex=" .. MyselfProxy.Instance:GetMySex());
    LogDebug("GetQuota=" .. MyselfProxy.Instance:GetQuota());
    LogDebug("GetQuotaLock=" .. MyselfProxy.Instance:GetQuotaLock());
    LogDebug("GetHasCharge=" .. MyselfProxy.Instance:GetHasCharge());
    LogDebug("GetFashionHide=" .. MyselfProxy.Instance:GetFashionHide());
    LogDebug("GetPvpCoin=" .. MyselfProxy.Instance:GetPvpCoin());
    LogDebug("GetLottery=" .. MyselfProxy.Instance:GetLottery());
    LogDebug("GetGuildHonor=" .. MyselfProxy.Instance:GetGuildHonor());
    LogDebug("GetServantFavorability=" .. MyselfProxy.Instance:GetServantFavorability());
    LogDebug("GetBoothScore=" .. MyselfProxy.Instance:GetBoothScore());
end;

function DumpQuest()
    local currentMapID = Game.MapManager:GetMapID(); 
    local questlst = QuestProxy.Instance:getQuestListByMapAndSymbol(currentMapID);
    for k, q in pairs(questlst) do
        LogDebug(tostring(k));
        local params = q.staticData and q.staticData.Params;
        local symbolType = QuestSymbolCheck.GetQuestSymbolByQuest(q);
        LogDebug(tostring(params) .. ' ' .. MyTostring(params.ShowSymbol) .. ' ' .. tostring(symbolType));
        local uniqueid, npcid = params.uniqueid, params.npc;
        npcid = type(npcid) == "table" and npcid[1] or npcid;
        local npcPoint,combineId;
        if( uniqueid )then
            npcPoint = Game.MapManager:FindNPCPoint( uniqueid );
        elseif(npcid)then
            --npcPoint = self:GetMapNpcPointByNpcId( npcid );
            uniqueid = npcPoint and npcPoint.uniqueID or 0;
        else
            combineId = q.questDataStepType..q.id;
        end
        LogDebug("uniqueid=" .. tostring(uniqueid) .. ' npcid=' .. MyTostring(npcid) .. ' npcPoint=' .. MyTostring(npcPoint));
    end
end;

function DumpSelf(self)
    LogDebug("g_MainView " .. MyTostring(g_MainView));
    local go = self.gameObject;
    local childCount = go.transform.childCount;
    LogDebug("childCount " .. childCount);
    local trans = go.transform;
    for i=0, trans.childCount-1 do
        local transChild = trans:GetChild(i);
        --LogDebug("#"..i.. " " .. MyTostring(transChild));
        --LogDebug("#"..i.. " " ..  MyTostring(transChild.gameObject));
        LogDebug(GameObjectToString(transChild.gameObject));
        --transChild.gameObject.layer = layer;
        --UIUtil.ChangeLayer(transChild.gameObject, layer);
    end
    LogDebug("mapLabel " .. MyTostring(self.mapLabel));
    local activeScene = SceneManagement.SceneManager.GetActiveScene();
    LogDebug("activeScene " .. MyTostring(activeScene));
end;

function QuestToString(wq)
    local listType = "";
    local wd = wq.wantedData;
    if wq.questListType == SceneQuest_pb.EQUESTLIST_ACCEPT then listType = "EQUESTLIST_ACCEPT" end;
    if wq.questListType == SceneQuest_pb.EQUESTLIST_CANACCEPT then listType = "EQUESTLIST_CANACCEPT" end;
    if wq.questListType == SceneQuest_pb.EQUESTLIST_COMPLETE then listType = "EQUESTLIST_COMPLETE" end;
    if wq.questListType == SceneQuest_pb.EQUESTLIST_SUBMIT then listType = "EQUESTLIST_SUBMIT" end;
    local info = QuestDataUtil.parseWantedQuestTranceInfo(wq,wd);

    return "id=" .. wd.id .. " Target=[" .. wd.Target .. "] MapId=" .. wd.MapId .. " NpcId=" .. wd.NpcId .. " questListType=" .. listType .. " Content=" .. wd.Content .. " info=[" .. info .. "]";
end;


function MonsterToString(m)
	local stat = ROM_GetMonStatus(m);
	--if  m.data.props ~= nil then
	    local props = m.data.props;
		local hp = props.Hp:GetValue();
		return "ID=" .. m.data.id .. " TypeID=" .. m.data.staticData.id .. " name=" ..  m.data.staticData.NameZh .. " Type=" .. m.data.staticData.Type .. ' HP=' .. stat.hp;	
	--else
	--	return "ID=" .. m.data.id .. " TypeID=" .. m.data.staticData.id .. " name=" ..  m.data.staticData.NameZh .. " Type=" .. m.data.staticData.Type;	
	--end;

end;

function SkillToString(s)
    local skillInfo = Game.LogicManager_Skill:GetSkillInfo(s.id);
    --return "ID=" .. skillInfo.staticData.id .. " name=[" .. skillInfo.staticData.NameZh .. "] type=" .. skillInfo.staticData.SkillType;
    return SkillInfoToString(skillInfo);
end;

function SkillToStringByID(id)
    local skillInfo = Game.LogicManager_Skill:GetSkillInfo(id);
    return SkillInfoToString(skillInfo);
end;

function SkillInfoToString(skillInfo)
    return "ID=" .. skillInfo.staticData.id .. " name=[" .. skillInfo.staticData.NameZh .. "] type=" .. skillInfo.staticData.SkillType;
end;




function DumpLearnSkill()
    local lstSkill = SkillProxy.Instance.learnedSkills;
    tableForEach(lstSkill, function(i, v)
        local skills = v;
        --local skillInfo = Game.LogicManager_Skill:GetSkillInfo(skill:GetID());
        --ListField(skill.id);
        tableForEach(skills, function(i, v)
            local skill = v;
            LogDebug(SkillToString(skill));
            --LogDebug(MyTostring(skill.id));
        end);
    end);    
end;

function DumpMonsters()
    local lst = NSceneNpcProxy.Instance.npcMap;
    tableForEach(lst, function(i, v)
        local mons = v;
        tableForEach(mons, function(i, v)
            local mon = v;
            LogDebug(MonsterToString(mon));
        end);
    end);    
end;

if class ~= nil then
    if MyBot == nil then
        MyBot = class("MyBot");
    end;
    MyBot.version = "1.0";
    function MyBot:ctor()
		LogDebug("MyBot:ctor()");
	end
    function MyBot:OnHPChange(evt)
        LogDebug("MyBot.OnHPChange " .. MyTostring(evt));
    end;
    function MyBot:OnSPChange(evt)
        LogDebug("MyBot.OnSPChange " .. MyTostring(evt));
    end;
    function MyBot:OnMyselfPlaceTo(evt)
        LogDebug("MyBot.OnMyselfPlaceTo data=" .. MyTostring(evt.data));
    end;
    function MyBot:OnMyselfLeaveScene(evt)
        LogDebug("MyBot.OnMyselfLeaveScene " .. MyTostring(evt));
    end;
    function MyBot:UsedSkillCheck(evt)
        LogDebug("MyBot.UsedSkillCheck " .. MyTostring(evt));
    end;
    function MyBot:PartnerUpdateCheck(evt)
        LogDebug("MyBot.PartnerUpdateCheck " .. MyTostring(evt));
    end;
    function MyBot:BuffUpdateCheck(evt)
        LogDebug("MyBot.BuffUpdateCheck " .. MyTostring(evt));
    end;
    function MyBot:PropChangeCheck(evt)
        LogDebug("MyBot.PropChangeCheck " .. MyTostring(evt));
    end;
    function MyBot:MeSceneUIClear(evt)
        LogDebug("MyBot.MeSceneUIClear " .. MyTostring(evt));
    end;
    function MyBot:handleMissionCommand(evt)
        LogDebug("MyBot.handleMissionCommand " .. MyTostring(evt));
    end;
    function MyBot:HandlePetHpChange(evt)
        LogDebug("MyBot.HandlePetHpChange " .. MyTostring(evt));
    end;
    function MyBot:OnSelectTargetChange(evt)
        LogDebug("MyBot.OnSelectTargetChange " .. MyTostring(evt));
    end;
    function MyBot:MyDataChange(evt)
        LogDebug("MyBot.MyDataChange " .. MyTostring(evt));
    end;
    function MyBot:LevelUp(evt)
        LogDebug("MyBot.LevelUp " .. MyTostring(evt));
    end;
    function MyBot:JobExpChange(evt)
        LogDebug("MyBot.JobExpChange " .. MyTostring(evt));
    end;
    function MyBot:BaseExpChange(evt)
        LogDebug("MyBot.BaseExpChange " .. MyTostring(evt));
    end;
    function MyBot:ZenyChange(evt)
        LogDebug("MyBot.ZenyChange " .. MyTostring(evt));
    end;
    function MyBot:HitTargets(evt)
        LogDebug("MyBot.HitTargets " .. MyTostring(evt));
    end;
    function MyBot:BeHited(evt)
        LogDebug("MyBot.BeHited " .. MyTostring(evt));
    end;
    function MyBot:BeHited(evt)
        LogDebug("MyBot.BeHited " .. MyTostring(evt));
    end;
    function MyBot:PlaceTo2(evt)
        LogDebug("MyBot.PlaceTo2 " .. MyTostring(evt));
    end;
    
    function MyBot:GetEvents()
        local ret = {
            {event=MyselfEvent.HpChange,"HpChange"},
            {event=MyselfEvent.SpChange,"SpChange"},
            {event=MyselfEvent.PlaceTo,"PlaceTo"},
        };
        return ret;
    end;
    function MyBot:UnHookEvents()
        tableForEach(EventManager.Me().handlers,function(index,tab)
            tableForEach(tab,function(_,o)
                while (TableUtil.Remove(o.owners,self) ~= 0)  do
                end;
            end);
        end);
        LogDebug("MyBot.UnHookEvents");
    end;
    function MyBot:HookEvents()
        if EventManager ~= nil then
            self:UnHookEvents();
            EventManager.Me():AddEventListener(MyselfEvent.HpChange,self.OnHPChange,self);
            EventManager.Me():AddEventListener(MyselfEvent.SpChange,self.OnSPChange,self);
            EventManager.Me():AddEventListener(MyselfEvent.PlaceTo, self.OnMyselfPlaceTo, self);
            EventManager.Me():AddEventListener(MyselfEvent.LeaveScene, self.OnMyselfLeaveScene, self);
            EventManager.Me():AddEventListener(MyselfEvent.SelectTargetChange, self.OnSelectTargetChange, self);
            EventManager.Me():AddEventListener(MyselfEvent.UsedSkill,self.UsedSkillCheck,self);
            EventManager.Me():AddEventListener(MyselfEvent.PartnerChange,self.PartnerUpdateCheck,self);
            EventManager.Me():AddEventListener(MyselfEvent.BuffChange,self.BuffUpdateCheck,self);
            EventManager.Me():AddEventListener(MyselfEvent.MyPropChange,self.PropChangeCheck,self);
            EventManager.Me():AddEventListener(MyselfEvent.MyDataChange,self.MyDataChange,self);
            EventManager.Me():AddEventListener(MyselfEvent.MyAttrChange,self.MyAttrChange,self);
            
            EventManager.Me():AddEventListener(MyselfEvent.LevelUp,self.LevelUp,self);
            EventManager.Me():AddEventListener(MyselfEvent.JobExpChange,self.JobExpChange,self);
            EventManager.Me():AddEventListener(MyselfEvent.BaseExpChange,self.BaseExpChange,self);
            EventManager.Me():AddEventListener(MyselfEvent.ZenyChange,self.ZenyChange,self);
            EventManager.Me():AddEventListener(MyselfEvent.HitTargets,self.HitTargets,self);
            EventManager.Me():AddEventListener(MyselfEvent.BeHited,self.BeHited,self);
            
            EventManager.Me():AddEventListener(MyselfEvent.MyselfSceneUIClear,self.MeSceneUIClear,self);
            EventManager.Me():AddEventListener(MyselfEvent.MissionCommandChanged,self.handleMissionCommand,self);
            EventManager.Me():AddEventListener(MyselfEvent.Pet_HpChange, self.HandlePetHpChange, self);
            LogDebug("MyBot.HookEvent");
        end;
    end;
    if myBot == nil or myBot.version ~= MyBot.version then
        if myBot ~= nil then
            myBot:UnHookEvents();
        end;
        myBot = MyBot.new();
        LogDebug("MyBot.new()");
    end;
    --myBot:HookEvents();
end;

--[[
MyselfEvent= {
	Inited = "MyselfEvent_Inited",
	PlaceTo = "MyselfEvent_PlaceTo",
	LeaveScene = "MyselfEvent_LeaveScene",
	SelectTargetChange = "MyselfEvent_SelectTargetChange",
	SelectTargetClassChange = "MyselfEvent_SelectTargetClassChange",
	--属性值发生变化，攻击力啦，生命值啦
	MyPropChange = "MyselfEvent_MyPropChange",
	--数据发生变化，等级，经验
	MyDataChange = "MyselfEvent_MyDataChange",
	--属性值、数据变化的通知
	MyAttrChange = "MyselfEvent_MyAttrChange",
	MyProfessionChange = "MyselfEvent_MyProfessionChange",
	ScaleChange = "MyselfEvent_ScaleChange",
	AskUseSkill = "MyselfEvent_AskUseSkill",
	CancelAskUseSkill = "MyselfEvent_CancelAskUseSkill",
	LevelUp = "MyselfEvent_LevelUp",
	JobExpChange = "MyselfEvent_JobExpChange",
	BaseExpChange = "MyselfEvent_BaseExpChange",
	ZenyChange = "MyselfEvent_ZenyChange",
	ContributeChange = "MyselfEvent_ContributeChange",
	BattlePointChange = "MyselfEvent_BattlePointChange",
	MusicInfoChange = "MyselfEvent_MusicInfoChange",
	ResetHpShortCut = "MyselfEvent_ResetHpShortCut",
	MyRoleChange = "MyselfEvent_MyRoleChange",
	ChangeDress = "MyselfEvent_ChangeDress",
	--击npc怪物通知
	HitTargets = "MyselfEvent_HitTargets",
	BeHited = "MyselfEvent_BeHited",
	-- 访问目标通知
	AccessTarget = "MyselfEvent_AccessTarget",
	AccessSealNpc = "MyselfEvent_AccessSealNpc",
	-- 玩家手动控制通知
	ManualControlled = "MyselfEvent_ManualControlled",
	SyncBuffs = "MyselfEvent_SyncBuffs",
	AddBuffs = "MyselfEvent_AddBuffs",
	RemoveBuffs = "MyselfEvent_RemoveBuffs",
	DeathBegin = "MyselfEvent_DeathBegin",
	DeathEnd = "MyselfEvent_DeathEnd",
	ReliveStatus = "MyselfEvent_ReliveStatus",
	DeathStatus = "MyselfEvent_DeathStatus",
	LeaveCarrier = "MyselfEvent_LeaveCarrier",
	SkillPointChange = "MyselfEvent_SkillPointChange",
	SpChange = "MyselfEvent_SpChange",
	HpChange = "MyselfEvent_HpChange",
	EnableUseSkillStateChange = "MyselfEvent_EnableUseSkillStateChange",
	UsedSkill = "MyselfEvent_UsedSkill",
	ChangeJobReady = "MyselfEvent_ChangeJobReady",
	ChangeJobBegin = "MyselfEvent_ChangeJobBegin",
	ChangeJobEnd = "MyselfEvent_ChangeJobEnd",
	PartnerChange = "MyselfEvent_PartnerChange",
	MyselfSceneUIClear = "MyselfSceneUIClear",
	TransformChange = "MyselfEvent_TransformChange",
	UpdateAttrEffect = "MyselfEvent_UpdateAttrEffect",
	AddWeakDialog = "MyselfEvent_AddWeakDialog",

	--skill
	SkillGuideBegin = "MyselfEvent_SkillGuideBegin",
	SkillGuideEnd = "MyselfEvent_SkillGuideEnd",

	--new
	TargetPositionChange = "MyselfEvent_TargetPositionChange",

	ZoneIdChange = "MyselfEvent_ZoneIdChange",

	MissionCommandChanged = "MyselfEvent_MissionCommandChanged",
	SceneGoToUserCmdHanded = "MyselfEvent_SceneGoToUserCmd",
	BuffChange = "MyselfEvent_BuffChange",

	CookerLvChange = "MyselfEvent_CookerLvChange",
	TasterLvChange = "MyselfEvent_TasterLvChange",
	Pet_HpChange = "MyselfEvent_Pet_HpChange",
	ServantFavorChange = "MyselfEvent_ServantFavorChange",

	TwinActionStart = "MyselfEvent_TwinActionStart",
}
]]


if class ~= nil then
	AutoAI_Rom = class("AutoAI_Rom")

	function AutoAI_Rom:ctor()
        self.enable = false;
		self.UpdateInterval = 0;
		self.nextUpdateTime = 0
		LogDebug("AutoAI_Rom:ctor()");
	end
    
    function AutoAI_Rom:Enable(value)
        self.enable = value;
    end;
    
    function AutoAI_Rom:IsEnable()
        return self.enable;
    end;
    

	function AutoAI_Rom:Clear(idleElapsed, time, deltaTime, creature)
		LogDebug("AutoAI_Rom:Clear()");
		self.nextUpdateTime = 0
	end

	function AutoAI_Rom:Prepare(idleElapsed, time, deltaTime, creature)
		--LogDebug("AutoAI_Rom:Prepare()");
        if self.enable then
			if time < self.nextUpdateTime then
				return true
			end
			--LogDebug("AutoAI_Rom:Prepare() " .. (time - self.nextUpdateTime) .. " " .. self.UpdateInterval);
			self.nextUpdateTime = time + self.UpdateInterval		
            for i= 1, #myAIRules do
                local rule = myAIRules[i];
                --LogDebug("" .. i .. " " .. MyTostring(rule));
                if rule.func ~= nil and rule.func(rule) then
                    return true;
                end;
            end;        
            LogDebug("AutoAI_Rom:Prepare() nothing to do");
            -- nothing to do
            self.nextUpdateTime = time + 1.0;
        end;
        return false
	end

	function AutoAI_Rom:Start(idleElapsed, time, deltaTime, creature)
	    --LogDebug("AutoAI_Rom:Start()");
	end

	function AutoAI_Rom:End(idleElapsed, time, deltaTime, creature)
        self.target = nil;
	    --LogDebug("AutoAI_Rom:End()");
	end

	function AutoAI_Rom:Update(idleElapsed, time, deltaTime, creature)
		if time < self.nextUpdateTime then
			return true
		end
		--LogDebug("AutoAI_Rom:Update() " .. (time - self.nextUpdateTime));
		self.nextUpdateTime = time + self.UpdateInterval		
		return false
	end
    
end;

function ROM_GetMonStatus(mon)
    local props = mon.data.props;
    local hp = props.Hp:GetValue();
    local maxhp = props.MaxHp:GetValue();
    local frachp = hp/maxhp;
    local sp = props.Sp:GetValue();
    local maxSp = props.MaxSp:GetValue();
    local fracsp = sp/maxSp;
    return {
        hp=hp,
        maxhp=maxhp,
        frachp=frachp,
        sp=sp,
        maxSp=maxSp,
        fracsp=fracsp,
    };
end;

function ROM_GetMyStatus()
	return ROM_GetMonStatus(Game.Myself);
--[[    local props = Game.Myself.data.props;
    local hp = props.Hp:GetValue();
    local maxhp = props.MaxHp:GetValue();
    local frachp = hp/maxhp;
    local sp = props.Sp:GetValue();
    local maxSp = props.MaxSp:GetValue();
    local fracsp = sp/maxSp;
    return {
        hp=hp,
        maxhp=maxhp,
        frachp=frachp,
        sp=sp,
        maxSp=maxSp,
        fracsp=fracsp,
    };]]
end;

function ROM_GetSkillNeeded(skillID)
    local skillInfo = Game.LogicManager_Skill:GetSkillInfo(skillID);
    local spCost = skillInfo:GetSP(Game.Myself);
    local hpCost = skillInfo:GetHP(Game.Myself);
    local delayCD = skillInfo:GetDelayCD(Game.Myself);
    --local CD = skillInfo:GetCD(Game.Myself);
    local CD = skillInfo:GetLogicRealCD(Game.Myself);
    return {
        hp=hpCost or 0,sp=spCost or 0,delayCD=delayCD or 0,CD=CD or 0
    };
end;

function ROM_FindNearestMonsterEx(monlist)
    monlist = monlist or {};
    local filterFunc = function(mon)
        return #monlist == 0 or TableUtil.HasValue(monlist,mon.data.staticData.id)
    end;
    local mons = ROM_GetAllMonster(filterFunc);
    return ROM_GetNearestMonFromList(mons);
end;

function ROM_GetNearestMonFromList(mons)
    local minDist = 100000;
    local retNpc = nil;
    local myPos = Game.Myself:GetPosition();
    --m.data.staticData.id 
    tableForEach(mons,function(i,v)
        local npc = v;
        local distance = LuaVector3.Distance(myPos, npc:GetPosition());
        --LogDebug("ID=" .. v .. " dist=" .. tostring(distance));
        if distance < minDist then
            retNpc = npc;
            minDist = distance;
        end;
    end);
    if retNpc ~= nil then
        LogDebug("ROM_GetNearestMonFromList: found " .. MonsterToString(retNpc) .. " " .. minDist);
    end;
    return retNpc;
end;

function ROM_GetAllNPC(filterFunc)
    filterFunc = filterFunc or function(mon) return true; end
    local ret = {};
    local lst = NSceneNpcProxy.Instance.npcMap;
    tableForEach(lst, function(i, v)
        local mons = v;
        tableForEach(mons, function(i, v)
            local mon = v;
			if ROM_IsMonster(mon) == false then
            --if mon.data.staticData.Type ~= "Monster" then
                if filterFunc(mon) then
                    table.insert(ret, mon);
                end;
            end;
        end);
    end);    
    return ret;
end;

function ROM_GetAllMonster(filterFunc)
    filterFunc = filterFunc or function(mon) return true; end
    local ret = {};
    local lst = NSceneNpcProxy.Instance.npcMap;
    tableForEach(lst, function(i, v)
        local mons = v;
        tableForEach(mons, function(i, v)
            local mon = v;
			local stat = ROM_GetMonStatus(mon);
            if ROM_IsMonster(mon) and stat.hp > 0 then
                if filterFunc(mon) then
                    table.insert(ret, mon);
                end;
            end;
        end);
    end);    
    return ret;
end;
--[[
function ROM_GetAllMonsterFromNSceneNpcProxy()
    filterFunc = filterFunc or function(mon) return true; end
    local ret = {};
    local lst = NSceneNpcProxy.Instance.npcMap;
    tableForEach(lst, function(i, v)
        local mons = v;
        tableForEach(mons, function(i, v)
            local mon = v;
            if filterFunc(mon) then
                table.insert(ret, mon);
            end;
        end);
    end);    
    return ret;
end;]]

function ROM_GetLearnSkill(filter)
    filter = filter or {};
    local ret = {};
    local lstSkill = SkillProxy.Instance.learnedSkills;
    tableForEach(lstSkill, function(i, v)
        local skills = v;
        tableForEach(skills, function(i, v)
            local skill = v;
            local skillInfo = Game.LogicManager_Skill:GetSkillInfo(skill.id);
            if #filter == 0 or TableUtil.HasValue(filter,skillInfo.staticData.SkillType) then
            --if skillInfo.staticData.SkillType == "Attack" then  -- "Heal"
                table.insert(ret, skill);
            end;
            --LogDebug(SkillToString(skill));
        end);
    end);    
    return ret;
end;

function ROM_GetActiveSkill()
    return ROM_GetLearnSkill({"Attack","Heal","Buff","FakeDead"});
end;

function ROM_GetMySkillInfoByName(name)
    local skills = ROM_GetActiveSkill();
    for i=1,#skills do
        local skill = skills[i];
        local skillInfo = Game.LogicManager_Skill:GetSkillInfo(skill.id);
        local skillName = skillInfo.staticData.NameZh;
        --LogDebug(skillName .. " vs " .. name);
        if string.match(skillName, name) then	
            return skillInfo;
        end;
    end;
    return nil;
end;

function ROM_FindStaticMonster(tab)
    local filterFunc = function(mon)
        return (mon.data.staticData.id >= 40000 and mon.data.staticData.id < 50000) or (mon.data.staticData.id >= 100000); 
    end;
    return ROM_FindMonByFilter(filterFunc,"ROM_FindStaticMonster");
end;

function ROM_FindMiniBoss(tab)
    local filterFunc = function(mon)
		--LogDebug("ROM_FindMiniBoss " ..  MonsterToString(mon));
        return mon.data.staticData.Type == "MINI";
    end;
    return ROM_FindMonByFilter(filterFunc,"ROM_FindMiniBoss");
end;

function ROM_FindMonByFilter(filterFunc,str)
    str = str or "ROM_FindMonByFilter";
    local mons = ROM_GetAllMonster(filterFunc);   
    local mon = ROM_GetNearestMonFromList(mons);
    if mon ~= nil then
        LogDebug(str .. ": found " .. MonsterToString(mon));
	else
		--LogDebug(str .. ": not found ");
    end;
    return mon;
end;

function ROM_FindBestMonster()
    for i= 1, #myMonsterRules do
        local rule = myMonsterRules[i];
        --LogDebug(MyTostring(rule));
        if rule.func ~= nil then
            local param = rule.param or rule;
            local npc = rule.func(param);
            if npc ~= nil then
                return npc;
            end;
        end;
    end;     
    return nil;
end;

function ROM_GetMonsterLockTarget()
    local mon = Game.Myself:GetLockTarget();
    if mon~= nil then
		-- possible player here which does not has staticData
		if ROM_IsMonster(mon) then
			return mon;
		end;
		--[[
		if mon.data.staticData ~= nil then
			if mon.data.staticData.Type == "Monster" then
				return mon;
			end;
		end;
		]]
    end;
    return nil;
end;

function ROM_IsMonster(mon)
	if mon.data.staticData ~= nil then
		if mon.data.staticData.Type == "Monster" or mon.data.staticData.Type == "MINI" or mon.data.staticData.Type == "MVP" then
			return true;
		end;
	end;
	return false;
end;

if FunctionMonster ~= nil then
    function FunctionMonster:FilterMonster(ignoreSkill)
        --LogDebug("FunctionMonster:FilterMonster()");
        TableUtility.ArrayClear(self.monsterList)

        local userMap = NSceneNpcProxy.Instance.userMap

        local hasLearnMvp,hasLearnMini = true, true;
        --if(ignoreSkill ~= true)then
        --    hasLearnMvp = SkillProxy.Instance:HasLearnedSkill(GameConfig.Expression_SearchSkill.searchmvpskill)
        --    hasLearnMini = SkillProxy.Instance:HasLearnedSkill(GameConfig.Expression_SearchSkill.searchminiskill)
        --end

        for _,monster in pairs(userMap)do
            if monster.data and monster.data:IsMonster() then
                if(monster.data.staticData.Type == "MVP")then
                    LogDebug("MVP found" .. MonsterToString(monster));
                    if(hasLearnMvp)then
                        table.insert(self.monsterList, monster.data.id)
                    end
                elseif(monster.data.staticData.Type == "MINI")then
                    LogDebug("MINI found" .. MonsterToString(monster));
                    if(hasLearnMini)then
                        table.insert(self.monsterList, monster.data.id)
                    end
                else
                    table.insert(self.monsterList, monster.data.id)
                end
            end
        end

        return self.monsterList
    end
end;

--[[
UIUtil.WarnPopup("Title","Text",
	function(obj) 
		LogDebug("OK" .. tostring(obj));--ListField(obj,"",{}," ");
	end,
	function(obj) 
		LogDebug("Cancel" .. tostring(obj));--ListField(obj,"",{}," ");
	end,
	g_mainView,"OK","Cancel");
]]	

--[[
local msg = {text = "text",title = "title"};
GameFacade.Instance:sendNotification(UIEvent.CloseUI, {viewname = "PopUp10View"});
GameFacade.Instance:sendNotification(UIEvent.ShowUI, {viewname = "PopUp10View"});
GameFacade.Instance:sendNotification(SystemMsgEvent.MenuMsg,msg);
]]

