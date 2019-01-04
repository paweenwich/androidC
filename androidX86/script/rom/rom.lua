function ReadFile(path)
    local f = io.open(path)
    local s = f:read("*a")
    f:close()
    return s
end

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
		--local st = splitByChunk(data,800);
		--tableForEach(st,function(i,v)
		Debug.Log(logData);	
		--end);
		RomFileLogger.log(logData);
	else
		RomFileLogger.log(logData);
		print(logData);
		--local st = splitByChunk(data,5);
		--tableForEach(st,function(i,v)
		--	print(v);	
		--end);
	end;
end;

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

function GameObjectToString(go,tab)
	if tab == nil then tab = ""; end;
	local ret = tab .. UserDataToString(go);
	local trans = go.transform;
	for i=0, trans.childCount-1 do
		local goChild = trans:GetChild(i).gameObject;
		ret = ret .. "\n" .. GameObjectToString(goChild,tab .. " ");
	end
	return ret;
end;


function UserDataToString(value)
	local ret = "[" .. type(value) .. "] " .. tostring(value);
	if string.match(ret, "(UnityEngine.GameObject)") then	
		ret = "" .. tostring(value.name) .. " " .. MyTostring(value.scene) .. " " .. tostring(value.activeSelf);
	end;
	if string.match(ret, "(UnityEngine.SceneManagement.Scene)") then	
		ret = "Scene " .. value.name .. " " .. value.path .. " " .. value.rootCount;
	end;
	return ret;
end;

function ListField(obj,tab)
    tab = tab or "";
    if (type(obj) == 'table') then
        tableForEach(obj, function(i, v)
            -- skip function
            if(type(v) == 'function') then
                
                return;
            end;
            if(type(v) == 'table') then
                if tab == " " then
                    LogDebug(tab .. i .. " " .. tostring(v));
                else
                    LogDebug(tab .. i);                
                    ListField(v,tab .. " ");
                end;
            else
                LogDebug(tab .. i .. "=" .. tostring(v));
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


function ROM_Reload()
	local s = ReadFile("/data/local/tmp/script/rom.lua");
	local f = loadstring(s);
    if f~=nil then
        f();
    else
        if UIUtil ~= nil then
            UIUtil.FloatMsgByText("Fail: ROM_Reload");		
        end;
        LogDebug("Fail: ROM_Reload");
    end;
end;

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


if Game~=nil then
	--LogDebug(Game.Me():GetResolutionNames());
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
    function NCreature:GetClickable()
        LogDebug("NCreature:GetClickable()");
        --LogDebug(MyTostring(self.data));
        --LogDebug(MyTostring(self.assetRole));
        --self:Hide();
        return not self.data:NoAccessable()
    end
    
end;

function onHPChange(param)
    LogDebug("onHPChange");
end;

if EventManager~=nil and MyselfEvent ~= nil then
    EventManager.Me():RemoveEventListener(MyselfEvent.HpChange,onHPChange,nil);
    EventManager.Me():AddEventListener(MyselfEvent.HpChange,onHPChange,nil);
    LogDebug("AddEventListener");
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

if MyTick == nil then
    MyTick = class("MyTick")   
end;
MyTick.version = "1.0";
function MyTick:ctor()
    self.version = MyTick.version;
    LogDebug("MyTick:ctor()");
end

function MyTick:Tick()
    LogDebug("MyTick:Tick() " .. tostring(self) .." " .. self.version .. " *");
end;

function MyTick:start()
    if ROM_IsObjectInit(TimeTickManager) then
        LogDebug("MyTick:start() " .. self.version);
        self.timeTick = TimeTickManager.Me():CreateTick(0,2000,self.Tick,self);
        LogDebug(MyTostring(self.timeTick));
    end;
end;

function MyTick:stop()
    if ROM_IsObjectInit(TimeTickManager) then
        LogDebug("MyTick:stop()");
        TimeTickManager.Me():ClearTick(self);
    end;
end;

if myTick == nil or myTick.version ~= MyTick.version then
    myTick = MyTick.new();
end;
LogDebug("myTick=" .. tostring(myTick) .. " " .. tostring(myTick.version));
--myTick.stop();
--myTick.start();

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
            --myTick:stop();
            --myTick:start();
            if Game.Myself.ai.autoAI_Rom == nil then
                Game.Myself.ai.autoAI_Rom = AutoAI_Rom.new();
                Game.Myself.ai.idleAIManager:PushAI(Game.Myself.ai.autoAI_Rom);
                LogDebug("set AutoAI_Rom");
            else
                local index = TableUtil.FindKeyByValue(Game.Myself.ai.idleAIManager.ais,Game.Myself.ai.autoAI_Rom);
                Game.Myself.ai.autoAI_Rom = AutoAI_Rom.new();
                Game.Myself.ai.idleAIManager.ais[index] = Game.Myself.ai.autoAI_Rom;
                LogDebug("set new AutoAI_Rom");
            end;
            --ListField(Game.Myself.ai);
            ListField(g_MainView.super);
            --DumpSelf(self);
            --DumpMyself();

            
            --LogDebug(MyTostring(questlst));
		end);
	end
end;

a = {
	f1=11,f2=22,{2,2,2}
};
b = {5,6,a};
a.f3 = b;

--LogDebug(MyTostring("1234"));
--LogDebug(MyTostring(a));
--LogDebug(MyTostring(b));

LogDebug("ROM Loaded 1.02");

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


AutoAI_Rom = class("AutoAI_Rom")

function AutoAI_Rom:ctor()
    LogDebug("AutoAI_Rom:ctor()");
end

function AutoAI_Rom:Clear(idleElapsed, time, deltaTime, creature)
    LogDebug("AutoAI_Rom:Clear()");
end

function AutoAI_Rom:Prepare(idleElapsed, time, deltaTime, creature)
--    LogDebug("AutoAI_Rom:Prepare()");
	return true
end

function AutoAI_Rom:Start(idleElapsed, time, deltaTime, creature)
--    LogDebug("AutoAI_Rom:Start()");
end

function AutoAI_Rom:End(idleElapsed, time, deltaTime, creature)
--    LogDebug("AutoAI_Rom:End()");
end

function AutoAI_Rom:Update(idleElapsed, time, deltaTime, creature)
--    LogDebug("AutoAI_Rom:Update()");
	return false
end


