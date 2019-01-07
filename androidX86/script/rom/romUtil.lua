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

function ListField(obj,tab,tableHash,targetTab)
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
				-- skip function
				if(type(v) == 'function') then
					return;
				end;
				if(type(v) == 'table') then
					if tab == targetTab then
						LogDebug(tab .. key .. " " .. tostring(v) .. " >");			
					else
						LogDebug(tab .. key .. " " .. tostring(v));							
						ListField(v,tab .. " ",tableHash,targetTab);
					end;
				else
					LogDebug(tab .. key .. "=" .. tostring(v));
				end;
			end;
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



function MonsterToString(m)
    return "ID=" .. m.data.id .. " TypeID=" .. m.data.staticData.id .. " name=" ..  m.data.staticData.NameZh .. " Type=" .. m.data.staticData.Type;
end;

function SkillToString(s)
    local skillInfo = Game.LogicManager_Skill:GetSkillInfo(s.id);
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
	AutoAI_Rom = class("AutoAI_Rom")

	function AutoAI_Rom:ctor()
        self.enable = false;
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
	end

	function AutoAI_Rom:Prepare(idleElapsed, time, deltaTime, creature)
        if self.enable then
            local npc = ROM_FindNearestMonsterEx(myMonsterList);
            if npc ~= nil then
--              LogDebug("AutoAI_Rom:Prepare() true");   
                self.target = npc;
                Game.Myself:Client_LockTarget(npc);
                --Game.Myself:Client_MoveTo(npc:GetPosition(),true);	-- ignore mesg seem to work                
                return true
            end;
        end;
        --LogDebug("AutoAI_Rom:Prepare() false");        
        return false
	end

	function AutoAI_Rom:Start(idleElapsed, time, deltaTime, creature)
	    LogDebug("AutoAI_Rom:Start()");
        if self.target ~= nil then
            local npc = self.target;
            --local npc = NSceneNpcProxy.Instance:FindNearestNpc(Game.Myself:GetPosition(), 10001);
            --Game.Myself:Client_LockTarget(npc);
    --[[        local lstAttkSkill = SkillProxy.Instance.learnedSkills[10];
            tableForEach(lstAttkSkill, function(i, v)
                    local skill = v;
                    --LogDebug(MyTostring(skill.id) .. " " .. );
                    local skillInfo = Game.LogicManager_Skill:GetSkillInfo(skill:GetID());
                    LogDebug("id=" .. skillInfo.staticData.id .. " name=[" .. skillInfo.staticData.NameZh .. "] type=" .. skillInfo.staticData.SkillType);
                    --ListField(skillInfo);
            end);]]
            Game.Myself:Client_UseSkill(145001, npc,nil,nil,true);
            Game.Myself:Client_UseSkill(143001, npc,nil,nil,true);
        end;
	end

	function AutoAI_Rom:End(idleElapsed, time, deltaTime, creature)
        self.target = nil;
	    LogDebug("AutoAI_Rom:End()");
	end

	function AutoAI_Rom:Update(idleElapsed, time, deltaTime, creature)
	    LogDebug("AutoAI_Rom:Update()");
		return false
	end

end;


function ROM_FindNearestMonster(monlist)
    local minDist = 100000;
    local retNpc = nil;
    local myPos = Game.Myself:GetPosition();
    tableForEach(monlist,function(i,v)
        local npc = NSceneNpcProxy.Instance:FindNearestNpc(myPos, v);
        if npc ~= nil then
            local distance = LuaVector3.Distance(myPos, npc:GetPosition());
            LogDebug("ID=" .. v .. " dist=" .. tostring(distance));
            if distance < minDist then
                retNpc = npc;
                minDist = distance;
            end;
        else
            LogDebug("ID=" .. v .. " not found");
        end;
    end);
    return retNpc;
end;

function ROM_FindNearestMonsterEx(monlist)
    local mons = ROM_GetAllMonster();
    local minDist = 100000;
    local retNpc = nil;
    local myPos = Game.Myself:GetPosition();
    tableForEach(mons,function(i,v)
        local npc = v;
        local distance = LuaVector3.Distance(myPos, npc:GetPosition());
        --LogDebug("ID=" .. v .. " dist=" .. tostring(distance));
        if distance < minDist then
            retNpc = npc;
            minDist = distance;
        end;
    end);
    return retNpc;
end;



