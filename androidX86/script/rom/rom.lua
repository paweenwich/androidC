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
        f();
		LogDebug("ROM_DoFile success " .. fileName);
		return true;
    else
        if UIUtil ~= nil then
            UIUtil.FloatMsgByText("ROM_DoFile Fail (loadstring)");		
        end;
        LogDebug("ROM_DoFile Fail (loadstring)");
		return false;
    end;
end;

ROM_DoFile("/data/local/tmp/script/romUtil.lua");

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

if MyTick == nil and class ~= nil then
    MyTick = class("MyTick");   
end;
if MyTick ~= nil then
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
end;
--LogDebug("myTick=" .. tostring(myTick) .. " " .. tostring(myTick.version));
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
			OnMiniMapClick(self);
		end);
	end
end;
toggle = 1;

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

if g_mainView ~= nil then
	local tempVector3 = LuaVector3.zero
	local testButton = g_mainView:FindGO("TestFloat");
	--LogDebug(GameObjectToString(testButton));
	if cpytestButton == nil then
		-- create another test button
		cpytestButton = GameObject.Instantiate(testButton);
	else
	end

	local uiCamera = NGUIUtil:GetCameraByLayername("UI");	
	LogDebug(GameObjectToString(uiCamera));
	--tempVector3:Set(0.1,0.5,uiCamera.nearClipPlane);
	tempVector3:Set(0.05,0.5,0);
	local p = uiCamera:ViewportToWorldPoint(tempVector3);
	LogDebug(MyTostring(p));
	--LogDebug(MyTostring(GUI.Button()));
	--LogDebug(MyTostring(cpytestButton.transform.rect));
	cpytestButton.transform.position = p;
	cpytestButton:SetActive(true);
	
	--tempVector3:Set(10,10,0);
	--cpytestButton.transform.localPosition = tempVector3
	--tempVector3:Set(0.5,0.5,0.5);
	--cpytestButton.transform.localScale = tempVector3	
	g_mainView:AddClickEvent(cpytestButton, function (g)
		if ROM_Reload() then
			UIUtil.FloatMsgByText("Reload Success");
		end;
	end);
	--LogDebug(GameObjectToString(cpytestButton.transform.parent.gameObject));	--UIRoot
	--LogDebug(GameObjectToString(cpytestButton));
	--local label = UIUtil.FindGO("Label",cpytestButton);
	--LogDebug(GameObjectToString(label));
	
	if cpySwitch == nil then
		local obj = g_mainView:FindGO("SkillShortCutSwitch");
		LogDebug(GameObjectToString(obj));
		cpySwitch = GameObject.Instantiate(obj);
	end;
	cpySwitch:SetActive(false);

	if cpySwitchIcon == nil then	
		local obj = g_mainView:FindGO("SwitchIcon");
		LogDebug(GameObjectToString(obj));
		cpySwitchIcon = GameObject.Instantiate(obj);
	end;
	cpySwitchIcon:SetActive(false);
	
	local obj = g_mainView:FindGO("SkillBord");
	LogDebug(GameObjectToString(obj));
	
	if cpyCancelTransformBtn == nil then	
		local obj = g_mainView:FindGO("cancelTransformBtn");
		LogDebug(GameObjectToString(obj));
		cpyCancelTransformBtn = GameObject.Instantiate(obj);
--		cpytestButton:SetActive(true);
	end;
	tempVector3:Set(0.05,0.40,0);
	local p = uiCamera:ViewportToWorldPoint(tempVector3);
	cpyCancelTransformBtn.transform.localScale = Vector3(1,0.5,1);
	cpyCancelTransformBtn.transform.position = p;
	UIUtil.FindGO("Icon", cpyCancelTransformBtn):SetActive(false);
	UIUtil.FindGO("Bg", cpyCancelTransformBtn):SetActive(true);
	cpyCancelTransformBtn:SetActive(true);

	if EnsureMyButtom("ShortCutSkill_") then
		myButton["ShortCutSkill_"]:SetActive(false);
		local sprite = GameObjectUtil.Instance:DeepFindChild(myButton["ShortCutSkill_"], "Icon"):GetComponent(UISprite)
		LogDebug(GameObjectToString(sprite));
		LogDebug(MyTostring(sprite.material));
		LogDebug(MyTostring(sprite.material.mainTexture));
		local tabs = GameObjectUtil.Instance:GetAllComponentsInChildren(myButton["ShortCutSkill_"], UILabel, false) or {};
		LogDebug(MyTostring(tabs));
		LogDebug(MyTostring(tabs[1].trueTypeFont));
		
		
	end;
	local tabs = GameObjectUtil.Instance:GetAllComponentsInChildren(cpytestButton, MonoBehaviour, false) or {};
	LogDebug(MyTostring(tabs));
	local label = UIUtil.FindAllComponents(cpytestButton, UILabel, false) -- cpytestButton:GetComponent(UILabel);
	label[1].text = "Reload";
	label[1].fontSize = 30;
	
	LogDebug(MyTostring(label[1]));
	LogDebug(MyTostring(label[1].trueTypeFont));
	
--	LogDebug(MyTostring(cpytestButton));
	--local objs = cpytestButton:GetRootGameObjects();
	--local skillBord = g_mainView:FindGO("SkillBord");
	--LogDebug(MyTostring(objs));
	--LogDebug(MyTostring(skillBord.transform.parent.gameObject));	--Anchor_DownRight
	
end;

function OnMiniMapClick(self)
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

LogDebug("ROM Loaded 1.03");

