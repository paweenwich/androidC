function log(str)
	bot:logDebug(str);
end

log("Loading script 1");

function string.starts(String,Start)
   return string.sub(String,1,string.len(Start))==Start
end

function string.ends(String,End)
   return End=='' or string.sub(String,-string.len(End))==End
end

function tablelength(T)
  local count = 0
  for _ in pairs(T) do count = count + 1 end
  return count
end

function Test2()
	DumpRootGameObjects();
end;


function DumpRootGameObjects()
	local scene = SceneManager.GetActiveScene();
	log("scene name=" .. scene.name .. " path=" .. scene.path);
	
	local objs = scene:GetRootGameObjects();
	log("Root count==" .. objs.Length);
	for i=0,objs.Length-1 do
		log(objs[i]:ToString());
		--if objs[i]:ToString():starts("UIManager") then
		--	DumpGameObject(objs[i]);
		--end
	end;
end;

function DumpGameObject(gobj)
	local components = gobj:GetComponents(gobj:GetType());
	for i=0,components.Length-1 do
		log(" " .. components[i]:ToString());
	end;	
end;

function DumpGUI()
	local guiMgr = GUIManager.instance;
	log("_visitingLordID=" .. guiMgr._visitingLordID);
	log("--- GUIManager.windows ----");
	local it = guiMgr.windows:GetEnumerator();
	while it:MoveNext() do
		local entry = it.Current;
		if entry ~= nil then
			log(entry.Key:ToString() .. "=" .. entry.Value:ToString());
		end;
	end
	log("--- GUIManager.uiWindows ----");
	local uiWindows = guiMgr.uiWindows;
	for i=0,uiWindows.Count -1 do
		log(uiWindows[i]:ToString());
	end;
end;


function DumpMyLord()
	local lordUserManager = LordUserManager.instance;
	local myLordData = lordUserManager.myLordData;
	log('id=' .. myLordData.lordID);
	log('lordGauge=' .. myLordData.lordGauge);
	log('lordGaugeServerData=' .. myLordData.lordGaugeServerData);
	log('battlePoint=' .. myLordData.battlePoint);
	log('enablePurchaseBattlePoint=' .. myLordData.enablePurchaseBattlePoint);
	log('supportPoint=' .. myLordData.supportPoint);
	log('lordLevel=' .. myLordData.lordLevel);
	log('exp=' .. myLordData.exp);
	log('illustName=' .. myLordData.illustName);
end;

function DumpMonsterData()
	local monsterDataManager = MonsterDataManager.instance;
	local data = monsterDataManager.data;
	log('data.Length=' .. data.Length);
	for i=0,data.Length-1 do
		--log(data[i]:ToString());
	end;
end;

function Init()
--	bot.strDebug:Clear();


--	AddButtonScript();
	luanet.load_assembly("FantasyWarTactic");
	luanet.load_assembly("Assembly-CSharp");
	luanet.load_assembly("UnityEngine");
	
	FWT = luanet.import_type 'FantasyWarTactic.FWT';
	AIManager = luanet.import_type 'AIManager';
	GameStage = luanet.import_type 'GameStage';
	GUIManager = luanet.import_type 'GUIManager';
	GameApp = luanet.import_type 'GameApp'; 
	GameConfig = luanet.import_type 'GameConfig'; 
	NetworkManager = luanet.import_type 'NetworkManager'; 
	BannerManager = luanet.import_type 'BannerManager'; 
	InventoryItemManager = luanet.import_type 'InventoryItemManager';
	LordUserManager = luanet.import_type 'LordUserManager';
	MonsterDataManager = luanet.import_type 'MonsterDataManager';
	GameRule = luanet.import_type 'GameRule';
	GameMissionManager = luanet.import_type 'GameMissionManager';
	AbusingScoreManager = luanet.import_type 'AbusingScoreManager';
	DungeonManager = luanet.import_type 'DungeonManager';
	LordActiveSkillManager = luanet.import_type 'LordActiveSkillManager';
	ScoreManager = luanet.import_type 'ScoreManager';
	StatChangeTraceLogManager = luanet.import_type 'StatChangeTraceLogManager';
	BattleManager= luanet.import_type 'BattleManager';
	GameObject =  luanet.import_type 'UnityEngine.GameObject';
	Object = luanet.import_type 'UnityEngine.Object';
	Type = luanet.import_type 'System.Type';
	MessageBoxManager = luanet.import_type 'MessageBoxManager';
	AlarmManager = luanet.import_type 'AlarmManager';
	CreatureKindManager = luanet.import_type 'CreatureKindManager';
	CreatureDataManager = luanet.import_type 'CreatureDataManager';
	UtilFunc = luanet.import_type 'UtilFunc';
	SkillDataManager = luanet.import_type 'SkillDataManager';
	MonsterDataManager = luanet.import_type 'MonsterDataManager';
	MissionDataManager = luanet.import_type 'MissionDataManager';
	JsonConvert = luanet.import_type 'Newtonsoft.Json.JsonConvert';
	Formatting = luanet.import_type 'Newtonsoft.Json.Formatting';
	InventoryCreatureManager = luanet.import_type 'InventoryCreatureManager';
	SecureDataManager = luanet.import_type 'SecureDataManager';
	AssetBundle = luanet.import_type 'UnityEngine.AssetBundle';
	DungeonGUIManager = luanet.import_type 'DungeonGUIManager';
	ButtonState = luanet.import_type 'ButtonState';
	GameStageType = luanet.import_type 'GameStageType';
	PVPManager = luanet.import_type 'PVPManager';
	PVPBattleHistoryManager = luanet.import_type 'PVPBattleHistoryManager';
	PVPUserRankManager = luanet.import_type 'PVPUserRankManager';
	DimensionBreakManager = luanet.import_type 'DimensionBreakManager';
	ExpeditionManager = luanet.import_type 'ExpeditionManager';
	ExpeditionStatus = luanet.import_type 'ExpeditionStatus';
	ExpeditionRewardManager = luanet.import_type 'ExpeditionRewardManager';
	GameSceneType = luanet.import_type 'GameSceneType';
	MessageBoxResultType = luanet.import_type 'MessageBoxResultType';
	WindowType = luanet.import_type 'WindowType';
	RepeatPlayManager =  luanet.import_type 'RepeatPlayManager';
	DungeonDataManager = luanet.import_type 'DungeonDataManager';
	log("Init done");	
--	SceneManager =  luanet.import_type 'UnityEngine.SceneManagement.SceneManager';

end;


--[[
	NetworkManager.instance.SendGameResult(LordUserManager.instance.lordUser.dungeonKey, isWin, lordGauge, curDungeonId, (int)ScoreManager.instance.curGrade, ScoreManager.instance.totalScore, 
dungeonClientReward.killedMonstersID.Count, AbusingScoreManager.instance.abusingScore, StatChangeTraceLogManager.instance.CompressedTraceLog());
]]
function Status()
	local abusingScoreManager = AbusingScoreManager.instance;
	log('abusingScore=' .. abusingScoreManager.abusingScore);
	
	local curDungeonId = DungeonManager.instance.curDungeonId;
	local curMonsterCount = DungeonManager.instance.curMonsterCount;
	local curMissionTurn = DungeonManager.instance.curMissionTurn;
	log('curDungeonId=' .. curDungeonId);
	log('curMonsterCount=' .. curMonsterCount);
	log('curMissionTurn=' .. curMissionTurn);
	log('takeLordSkillWithDungeonID=' .. LordActiveSkillManager.instance:GetTakeLordSkillWithDungeonID(curDungeonId));
	log('lordGauge=' .. LordUserManager.instance.lordData.lordGauge);
	log('dungeonKey=' .. LordUserManager.instance.lordUser.dungeonKey);
	log('curGrade=' .. ScoreManager.instance.curGrade:ToString());
	log('totalScore=' .. ScoreManager.instance.totalScore);
	
	--dungeonClientReward.killedMonstersID.Count
	log('abusingScore=' .. AbusingScoreManager.instance.abusingScore);
	log('CompressedTraceLog=' .. StatChangeTraceLogManager.instance:CompressedTraceLog());
	if(StatChangeTraceLogManager.instance.log ~= nil) then
		log('abusingScoreOccurs.Count=' .. StatChangeTraceLogManager.instance.log.abusingScoreOccurs.Count);
	end;
	--[[log('gameMissionManager:');
	local gameMissionManager = GameMissionManager.instance;	
	log(' missionIdx=' .. gameMissionManager.missionIdx);
	log(' missionIdx=' .. gameMissionManager.missionIdx);
	log(' mainMissionTitle=' .. gameMissionManager.mainMissionTitle);
	log(' maxLimitTurn=' .. gameMissionManager. maxLimitTurn);
	log(' resultSubMissonText=' .. gameMissionManager.resultSubMissonText);]]
end;

--log("" .. DungeonManager.instance._monsterList.Count)
--[[
function xxx()

log(StatChangeTraceLogManager._instance._log:ToString());
DungeonManager.instance:FinishGame(true);
log("" .. GameRule.instance._movingTimePerTile)
log("" .. tostring(GameRule.instance._showDevelopeMenu))
log("" .. tostring(BattleManager.instance._targetMemberList.Count))
log("" .. tostring(BattleManager.instance._attackerMemberList.Count))

log(BattleManager.instance._leadCaster:ToString());
log(BattleManager.instance._leadCaster.creatureName);
log("maxHp=" .. BattleManager.instance._leadCaster.stats._maxHp);
log("hp=" .. BattleManager.instance._leadCaster.stats.hp);
--log(BattleManager.instance._mainCastee:ToString());
BattleManager.instance._leadCaster.stats.hp = BattleManager.instance._leadCaster.stats.maxHp

log("defenceRate=" .. BattleManager.instance._leadCaster.data.drf);
opponentCamp
log("" .. GameStage.instance.playerCamp.Count);
log("" .. GameStage.instance.opponentCamp.Count);
BattleManager.instance._leadCaster.data.data._baseDr = 0.2;log(BattleManager.instance._leadCaster.data.data._baseDr);log("defenceRate=" .. BattleManager.instance._leadCaster.data.drf);

BattleManager.instance._leadCaster.data.defenceRate = 0.5
BattleManager.instance._leadCaster.data.drf = 0.0001
log("" .. CreatureKindManager.instance.playerCreatureKindContainer.Count);
log("" .. CreatureDataManager.instance._data.Length);
log(UtilFunc.JsonSerialize(CreatureDataManager.instance._data[0]));

BattleManager.instance._leadCaster.data.movingRange = 6
BattleManager.instance._leadCaster.data.data.skill0 = BattleManager.instance._leadCaster.data.data.skill1
BattleManager.instance._leadCaster.data.data.skill0 = 1048705

bot:GetObjectAddress(MonsterDataManager.instance._data);

logger:logHex(2137702416,64);

logger:logHex(2276819808,64);

UtilFunc.DecryptFile("/sdcard/Android/data/com.nexon.fwar/files/Resources/datatable/creaturedataenglish.unity3d", "/data/local/tmp/creaturedataenglish.unity3d", SecureDataManager.GetCryptKey(), SecureDataManager.GetCryptIV())
assetBundle = AssetBundle.CreateFromFile("/data/local/tmp/creaturedataenglish.unity3d");
end;
]]

function DumpData(file,obj)
	local fout = io.open(file, "w")
	local str = json(obj);
	fout:write(str);
	fout:close()
end;

function DumpCreature()
	DumpData("/data/local/tmp/creatures.txt",CreatureDataManager.instance._data);
end;

function DumpSkill()
	DumpData("/data/local/tmp/skills.txt",SkillDataManager.instance._data);
end;

function DumpMonster()
	DumpData("/data/local/tmp/monsters.txt",MonsterDataManager.instance._data);
end;

function DumpMission()
	DumpData("/data/local/tmp/missions.txt",MissionDataManager.instance._data);
end;

function DumpInventoryCreature()
	DumpData("/data/local/tmp/InventoryCreatures.txt",InventoryCreatureManager.instance._creatureItems);
end;

function Test()
	Status();
end;

function Full()
	BattleManager.instance._leadCaster.stats.hp = BattleManager.instance._leadCaster.stats.maxHp
end;

function Atk(num)
	BattleManager.instance._leadCaster.data.data.baseAttackPoint = num*BattleManager.instance._leadCaster.data.data.baseAttackPoint;
end;

function CharStat()
	log("baseDr=" .. BattleManager.instance._leadCaster.data.data.baseDr);
	log("defenceRate=" .. BattleManager.instance._leadCaster.data.drf);
	log("_baseAttackPoint=" .. BattleManager.instance._leadCaster.data.data._baseAttackPoint);
	log("_apf;=" .. BattleManager.instance._leadCaster.data.data._apf);
end;

function DumpGameStage()
	if GameStage.instance == nil then
		return;
	end;
	local gs = GameStage.instance;
	--log("currentCamp.Count=" .. gs.currentCamp.Count);
	log("playerCamp.Count=" .. gs.playerCamp.Count);
	DumpCamp(gs.playerCamp);
	log("opponentCamp.Count=" .. gs.opponentCamp.Count);
	DumpCamp(gs.opponentCamp);
end;

function DumpCamp(camp)
	for i=0,camp.members.Count -1 do
		local charactor = camp.members[i];
		DumpCharactor(charactor);
	end;
end;

function DumpCharactor(c)
	log(c.creatureName);
	log("baseDr=" .. c.data.data.baseDr .. " drf=" .. c.data.data.drf .. " baseAttackPoint=" .. c.data.data.baseAttackPoint .. " apf=" .. c.data.data.apf);
	log("baseCr=" .. c.data.data.baseCr .. " crf=" .. c.data.data.crf .. " baseDgr=" .. c.data.data.baseDgr .. " dgrf=" .. c.data.data.dgrf);
	log("baseCar=" .. c.data.data.baseCar .. " baseCadr=" .. c.data.data.baseCadr .. " baseHr=" .. c.data.data.baseHr );
	
	--log("movingRange=" .. c.data.data.movingRange);
	
end;


function MessageBox(data)
	AlarmManager.instance:AlarmClientMessage(data);
end;

function json(obj)
	return JsonConvert.SerializeObject(obj,Formatting.Indented);
end;


function GetCreatureDataByName(name)
	local ret = {};
	for i=0,CreatureDataManager.instance._data.Length -1 do
		local data = CreatureDataManager.instance._data[i];
		if data.name == name then
			--log(json(data));
			table.insert(ret,data);
		end;
	end;
	return ret;
end;

function GetCreatureDataByID(id)
	return CreatureDataManager.GetData(id);
	--[[for i=0,CreatureDataManager.instance._data.Length -1 do
		local data = CreatureDataManager.instance._data[i];
		if data._creatureId == id then
			return data;
		end;
	end;
	return nil;]]
end;

tabDownMonster = {};
tabDownMonster["Shadow Arrow"] = 1;
tabDownMonster["Shadow Spear"] = 1;
tabDownMonster["Napalm Ghost"] = 1;
tabDownMonster["Hellhound"] = 1;
tabDownMonster["Shadow Knight"] = 1;
tabDownMonster["Shadow Witch"] = 1;
tabDownMonster["Killer Machine"] = 1;
tabDownMonster["Shadow Hammer"] = 1;
tabDownMonster["Shadow Hammer"] = 1;
tabDownMonster["Shadow Hammer"] = 1;
tabDownMonster["Reaper Guardian"] = 1;
tabDownMonster["Magma Giant"] = 1;
tabDownMonster["Abyss Dragon"] = 1;
tabDownMonster["Fortress Sentinel"] = 1;
tabDownMonster["Fortress Sniper"] = 1;
tabDownMonster["Fortress Destroyer"] = 1;
tabDownMonster["Parsifal"] = 1;
tabDownMonster["Hellmaster"] = 1;
tabDownMonster["Trishula"] = 1;
tabDownMonster["Chronos"] = 1;
tabDownMonster["Juggernaut"] = 1;
tabDownMonster["Bathory"] = 1;
tabDownMonster["Deimos"] = 1;
tabDownMonster["Ancient Keeper"] = 1;
tabDownMonster["Celestial"] = 1;

if flgMonsterDown == nil then
	flgMonsterDown = false;
end;
function DownMonsters()
	local cm = CreatureDataManager.instance;
	if cm == nil then return end;
	if flgMonsterDown then return end;
	for i=0,cm.data.Length -1 do
		local creatureData = cm.data[i];
		if creatureData._creatureId >= 0x200000 then
			if tabDownMonster[creatureData._name] ~= nil then
				log("DownMonster" .. creatureData._name .. ' ' .. creatureData._creatureId );
				creatureData._skill0 = -1;
				creatureData._skill1 = -1;
				creatureData._skill2 = -1;
				creatureData._skill3 = -1;
				creatureData._movePoint = 1;
				creatureData._baseAttackPoint = 50;
				creatureData._baseDr = 0.05;
				creatureData._baseDgr = 0.01;
				creatureData._baseMpRegen = 100;	
				if(creatureData._name == "Napalm Ghost") then
					creatureData._skill3 = 2195490;
				end;	
			end;
		end;
	end;
	flgMonsterDown = true;
end;

function CreateTabUpGrade()
	if tabUpgrade == nil or tablelength(tabUpgrade) < 100 then
		tabUpgrade = {};
		local cm = CreatureDataManager.instance;
		for i=0,cm.data.Length -1 do
			local creatureData = cm.data[i];
			tabUpgrade[creatureData._creatureId] = {
				_baseHp = creatureData._baseHp, 
				_baseAttackPoint= creatureData._baseAttackPoint,
				_baseDr = creatureData._baseDr,
				_baseDgr = creatureData._baseDgr,
				_baseMpRegen = creatureData._baseMpRegen,
				_movePoint = creatureData._movePoint,
			};
		end;
	end;
end;

function NoUpgrade()
	if tabUpgrade ~= nil then
		log("NoUpgrade");
		for key,value in pairs(tabUpgrade) do 
			--print(key,value) 
			DownGrade(key);
		end
	end;
end;

function SaveUpgrade()
	tabSaveUpgrade = {};
	for key,value in pairs(tabUpgradeList) do 
		tabSaveUpgrade[key] = value;
	end
	log("SaveUpgrade " .. tablelength(tabSaveUpgrade));
end;

function RestoreUpgrade()
	if tabSaveUpgrade ~= nil then
		for key,value in pairs(tabSaveUpgrade) do 
			UpGrade(key);
		end
		log("RestoreUpgrade " .. tablelength(tabSaveUpgrade));
	end;
end;

if tabUpgradeList == nil then
	tabUpgradeList = {};
end;

function UpGrade(id)
	--log("upgrade " .. id);
	CreateTabUpGrade();
	local creatureData = GetCreatureDataByID(id);
	if creatureData ~= nil then
		if creatureData._movePoint == 7 then
			--log("Already upgrade " .. creatureData._name);
			return false;
		end;				
		--[[
		tabUpgrade[id] = {
			_baseHp = creatureData._baseHp, 
			_baseAttackPoint= creatureData._baseAttackPoint,
			_baseDr = creatureData._baseDr,
			_baseDgr = creatureData._baseDgr,
			_baseMpRegen = creatureData._baseMpRegen,
			_movePoint = creatureData._movePoint,
		};]]
		creatureData._baseHp = 70000;
		creatureData._baseAttackPoint = 70000;
		creatureData._baseDr = 4.0;
		creatureData._baseDgr = 2.5;
		creatureData._baseMpRegen = 100;
		creatureData._movePoint = 7;	
		log("Upgrade " .. creatureData._name);
		tabUpgradeList[id] = creatureData._name;
		return true;
	else 
		log("Upgrade " .. id .. " notfound");
	end;
	return false;
end;


function DownGrade(id)
	local creatureData = GetCreatureDataByID(id);
	if creatureData ~= nil and tabUpgrade[id] ~= nil then
		if creatureData._movePoint == 7 and creatureData._baseHp ~= tabUpgrade[id]._baseHp then
			creatureData._baseHp = tabUpgrade[id]._baseHp;
			creatureData._baseAttackPoint = tabUpgrade[id]._baseAttackPoint;
			creatureData._baseDr = tabUpgrade[id]._baseDr;
			creatureData._baseDgr = tabUpgrade[id]._baseDgr;
			creatureData._baseMpRegen = tabUpgrade[id]._baseMpRegen;
			creatureData._movePoint = tabUpgrade[id]._movePoint;	
			log("DownGrade " .. creatureData._name .. ' ' .. creatureData._baseHp);
			tabUpgradeList[id] = nil;
			return true;
		end;
	end;
	return false;
end;


function AutoClose()

	if HasMessageBox() then
		log("MessageBox.Desc " ..  MessageBoxManager.instance.messageBox.uiDesc.text);
		log("MessageBox.Title " ..  MessageBoxManager.instance.messageBox.uiMessageBoxTitle.text);
		if "Allocate" == MessageBoxManager.instance.messageBox.uiMessageBoxTitle.text then
			log("Auto close for guild allocate");
			MessageBoxManager.instance.messageBox:OnOKButtonPressed(nil);
		end;
		
		if "Notice" == MessageBoxManager.instance.messageBox.uiMessageBoxTitle.text then
			log("Auto close for guild allocate");
			MessageBoxManager.instance.messageBox:OnOKButtonPressed(nil);
		end;
		
		return;
	end;

	if(bot:IsWindowOpen("DungeonResult")) then
		local d = bot:GetWindow("DungeonResult");	
		if GameStage.instance.stageType == GameStageType.PVP then
			log("AutoClose: GameStageType.PVP");		
			d.uiPVPResult:OnOKButtonPressed(nil);
			lastPVPTime = os.clock() + 10;
		end;
		if GameStage.instance.stageType == GameStageType.DimensionBreak then
			log("AutoClose: GameStageType.DimensionBreak");	
			DownGradeDimensionTeam();
			d.uiDimensionDungeonResult:OnOKButtonPressed(nil);		
			lastDimensionTime = os.clock() + 10;			
		end;
		if GameStage.instance.stageType == GameStageType.Normal and RepeatPlayManager.instance.isRepeating == false then
			log("AutoClose: GameStageType.Normal");	
			d:OnHomeButtonPressed(nil);
			--DownGradeDimensionTeam();
			--d.uiDimensionDungeonResult:OnOKButtonPressed(nil);		
			--lastDimensionTime = os.clock() + 10;			
		end;
		
	end;
	
	if(bot:IsWindowOpen("MessageBoxGUIPauseApp")) then
		log("AutoClose: MessageBoxGUIPauseApp");
		local gui = bot:GetWindow("MessageBoxGUIPauseApp");
		gui:OnOKButtonPressed(nil);
	end;
	
	if(bot:IsWindowOpen("PauseInGameGUI")) then
		log("AutoClose: PauseInGameGUI");
		local gui = bot:GetWindow("PauseInGameGUI");
		gui:OnClosePressed(nil);
	end;
	
	if(bot:IsWindowOpen("RepeatPlayRewardGUI")) then
		log("AutoClose: RepeatPlayRewardGUI");
		local gui = bot:GetWindow("RepeatPlayRewardGUI");
		gui:OnClickOKButton(nil);
	end;
	
	if(bot:IsWindowOpen("RepeatPlayStart")) then
		log("AutoClose: RepeatPlayStart");
		local gui = bot:GetWindow("RepeatPlayStart");
		gui:OnClickStartRepeat(nil);
	end;

	

	if(bot:IsWindowOpen("SpawnSelectItemGUI")) then
		log("AutoClose: SpawnSelectItemGUI");
		local gui = bot:GetWindow("SpawnSelectItemGUI");
		--gui:OnAutoPlacementPlayer(nil);
	end;

	if(bot:IsWindowOpen("InventoryCreatureSmall")) then
		log("AutoClose: InventoryCreatureSmall");
		local gui = bot:GetWindow("InventoryCreatureSmall");
		--gui.StartDungeonButton:OnClick();
		--gui:CallBackButton(gui.StartDungeonButton);
	end;

	if(bot:IsWindowOpen("DefenseRewardGUI")) then
		log("AutoTry: DefenseRewardGUI " .. DungeonManager.instance.curDungeonId);
		local gui = bot:GetWindow("DefenseRewardGUI");
		if DungeonManager.instance.curDungeonId == 4333600 then
			if gui.keepTryButton.state == ButtonState.On then
				gui:OnClickKeepTryButton(nil);
			else
				gui:OnClickOKButto(nil);
			end;
		end;
	end;
	if(bot:IsWindowOpen("DefenseDetailInfoGUI")) then
		log("AutoTry: DefenseDetailInfoGUI");
		local gui = bot:GetWindow("DefenseDetailInfoGUI");
		if gui.uiEnterButton.state == ButtonState.On then
			log("AutoTry: DefenseDetailInfoGUI enter");
			gui:OnEnterButtonPressed(nil);
		end;
	end;
	
	
	
end;

function ToggleGUI(guiName)
	local gui = bot:GetWindow(guiName);
	if(gui ~= nil) then
		if bot:IsWindowOpen(guiName) then
			gui:CloseWindow();
		else
			gui:OpenWindow();
		end;
	end;
end;

function DumpNetworkManager()
--17/09/2016 19:55:37 10940000002475019
--17/09/2016 19:55:37 TOTtBmElXxTvxmvWoS71lQJhQjiRLi2yrypmDaPq5vUNcuSR8m9VEUoFWylLN4k2R0G4cL0
--17/09/2016 19:55:37 09T01VE00M0P

--17/09/2016 20:31:16 10940000002475019
--17/09/2016 20:31:16 TOTtBmElXxTvxmvWoS71lQJhQjiRLi2yrypmDaPq5vUNcuSR8m9VEUoFWylLN4k2R0G4cL0
--17/09/2016 20:31:16 09T01VE00M0P

--19/09/2016 11:17:10 packetNo39
--19/09/2016 11:17:10 10940000002475019
--19/09/2016 11:17:10 TOT02JjSA3krvurMQU9RFVVwnNCdpKfRpQmT9k4T0SM13RFz2uZtJlDh5KXNQJ2cDz
--19/09/2016 11:17:10 09T01VE00M0P

	log("packetNo" .. NetworkManager.instance.packetNo);
    log(NetworkManager.instance.npaUserId);
	log(NetworkManager.instance.npaUserToken);
	log(NetworkManager.instance.npaUserCode);
end;


if lastAutoAttack == nil then
lastAutoAttack = os.clock();
end;
function AutoAttack()
	if lastAutoAttack + 5 > os.clock() then
		return;
	end	
	lastAutoAttack = os.clock();
	local gui = bot:GetWindow("MenuButtonGUI");
	if(gui~=nil) then 
		if gui.uiAutoButton ~= nil and gui.currentComponent ~= nil then
			if gui.uiAutoButton.state ~= ButtonState.On then
				gui:OnAutoButtonPressed(nil);
			end;
		end;
	end;
end;

function BoolValue(v)
	if v then return "True"; end;
	return "False";
end;



function DownGradeTeam(myTeamList)
	for i=0, myTeamList.Count -1 do
		local inventoryCreatureData = InventoryCreatureManager.instance:GetItem(myTeamList[i]); 
		DownGrade(inventoryCreatureData.data._creatureId);
	end;
end;

function DownGradeDimensionTeam()
	local dbm = DimensionBreakManager.instance;
	local myTeam = dbm._myDimensionTeam;
	local myTeamList = myTeam:GetCurrentTeamInstanceIdList();
	DownGradeTeam(myTeamList);
end;
if lastDimensionTime == nil then
	lastDimensionTime = os.clock();
end;

tabNormalDungeon = {};
tabNormalDungeon[1118259] = 3;	-- Moon Island 3
tabNormalDungeon[1114403] = 3;	-- Land of Extinction 2

tabNormalDungeon[1118258] = 2;
tabNormalDungeon[1114402] = 2;

lastNormal = os.clock();

tabDungeon = {
	{id = 1118259},
	{id = 1114403},
--	{id = 1114243},
	{id = 1114179},
--	{id = 1085731},
	


	{id = 1118258},
	{id = 1114402},	
	{id = 1114242},	
	{id = 1114178},
--	{id = 1085730},

	{id = 1118257},
	{id = 1114401},	
	{id = 1114241},
	{id = 1114177},
	{id = 1085729},

	
}

function FindBestDungeon()
	for i=1,table.getn(tabDungeon) do
		if CanPlayDungeon(tabDungeon[i].id) then
			return tabDungeon[i].id;
		end;
	end;
	return nil;
end

function FindBestDungeonData()
	local bestDun = FindBestDungeon();
	if bestDun ~= nil then
		return DungeonDataManager.GetData(bestDun);
	end;
	return nil;
end;

function CanPlayDungeon(id)
	return GameRule.CanPlayDungeon(id,false);
end;

function AutoNormal()
	if lastNormal + 5 > os.clock() then
		--log('AutoNormal skip ' );
		return;
	end;
	
	if bot:IsWindowOpen("DungeonList") then
		local bestDunData = FindBestDungeonData();
		if bestDunData ~= nil then
			local gui = bot:GetWindow("DungeonList");
			local dungeonListGUI = gui.uiNormalDungeonList;
			log("AutoNormal DungeonList " .. dungeonListGUI.dungeonElements.Count);			
			for i=0,dungeonListGUI.dungeonElements.Count -1 do
				local dungeonElement = dungeonListGUI.dungeonElements[i];
					log("#" .. i .. " " .. dungeonElement.dungeonId .. " " .. bestDunData.dgId);
				if math.abs(dungeonElement.dungeonId - bestDunData.dgId) <= 4 then
					log("Found best dun: click");
					dungeonElement:OnGoButtonPressed(nil);
					lastNormal = os.clock();
					return;
				end;
			end;
		end;
	end;
	
	if bot:IsWindowOpen("DungeonWorldMap") then
		log("AutoNormal DungeonWorldMap")
		local gui = bot:GetWindow("DungeonWorldMap");
		
		local bestDunData = FindBestDungeonData();
		if bestDunData ~= nil then
			for i=0,gui.uiRegions.Length-1 do
				local dungeonRegionGUI = gui.uiRegions[i];
				log("#" .. i .. " regionID=" .. dungeonRegionGUI.regionID);
				if dungeonRegionGUI.regionID == bestDunData.regionId then
					log("Found best dun: click");
					dungeonRegionGUI:OnRegionButtonPressed(nil);
					lastNormal = os.clock();
					return;
				end;
			end;
		end;
		
		lastNormal = os.clock();
		return;
	end;
	
	if(bot:IsWindowOpen("DungeonInfoNormal")) then
	
		if RepeatPlayManager.instance.isRepeating then
			lastNormal = os.clock();
			return;
		end;

		local gui = bot:GetWindow("DungeonInfoNormal");
		log("AutoTry: DungeonInfoNormal regionID=" .. gui.curDungeonData.regionId);		
		local  dungeonDetailInfoMissionGUI = gui.uiMissionInfo;
		local gameRule = GameRule.instance;
		
		local bestDunData = FindBestDungeonData();
		if bestDunData ~= nil then
			local bestID = bestDunData.dgId;
			local flgFound = false;
			for i=0,dungeonDetailInfoMissionGUI.uiMissionButtons.Length-1 do
				if dungeonDetailInfoMissionGUI.uiMissionButtons[i].dungeonID == bestID then
					flgFound = true;
				end;
			end;
			if flgFound == false then
				log("No Best dungeion found: go back home");
				local guiDungeonInfo = bot:GetWindow("DungeonInfo");
				if guiDungeonInfo ~= nil then
					guiDungeonInfo:OnHomeButtonPressed();
					lastNormal = os.clock();
					return;
					
				end;
			end;
			log("Found best dungeon " .. bestID);
			if gui.curDungeonData.dgId ~= bestID then
				gui:OnChangeChallengeQuest(bestID);
				return;
			else	
				if gui:CheckEnterPreCondition(false,nil) then
					log("Auto play " .. bestID);
					gui:OnClickStartRepeat(nil);
					lastNormal = os.clock();
					return;
				else	
					log("CheckEnterPreCondition fail");
				end;
			end;
		else
			log("No dungeion found");
			local guiDungeonInfo = bot:GetWindow("DungeonInfo");
			if guiDungeonInfo ~= nil then
				guiDungeonInfo:OnHomeButtonPressed();
				lastNormal = os.clock();
				return;
				
			end;
		end;
		
		
		--uiDungeonTypeEmblems
		--if gui.uiEnterButton.state == ButtonState.On then
			--gui:OnEnterButtonPressed(nil);
		--end;
	end;
	lastNormal = os.clock();
end;

function AutoDimension()
	--if GameStage.instance.stageType ~= GameStageType.DimensionBreak then
	--	return;
	--end;
	--DimensionBreak
	if lastDimensionTime + 10 > os.clock() then
--		log('AutoPVP skip ' .. (lastPVPTime + 10) .. ' > ' .. os.clock() );
		return;
	end;


	
	local dbm = DimensionBreakManager.instance;
	--dbm._isPlaying = false;

	if dbm ~= nil then
		local dimensionStageInfo = dbm._dimensionStageInfo;
	
		log("AutoDimension " .. BoolValue(dbm._isPlaying));		
		local myTeam = dbm._myDimensionTeam;
		local myTeamCP = myTeam:GetTeamCP(); 
		--log("myteam CP=" .. myTeamCP .. " " .. myTeam:GetCurrentTeamInstanceIdList().Count);
		local myTeamList = myTeam:GetCurrentTeamInstanceIdList();
		local currentTeamCount = 0;
		for i=0, myTeamList.Count -1 do
			if myTeamList[i] > 0 then
				local inventoryCreatureData = InventoryCreatureManager.instance:GetItem(myTeamList[i]); 
				--log("MyTeam InsianceID=" .. myTeamList[i] .. ' CreatureID=' .. inventoryCreatureData.data._creatureId);
				log("MyTeam " .. inventoryCreatureData.name .. ' ' .. inventoryCreatureData.dimensionHp .. '/' .. inventoryCreatureData.originalMaxHP);
				if inventoryCreatureData.dimensionHp > 0 or inventoryCreatureData.dimensionHp == -1 then
					--log(inventoryCreatureData.name .. ' ' .. inventoryCreatureData.dimensionHp);
					local hp = inventoryCreatureData.originalMaxHP;
					local mp = inventoryCreatureData.originalMaxMP;
					--inventoryCreatureData:SetDimensionStat(hp,mp);
					if hp > inventoryCreatureData._dimensionHp then
						inventoryCreatureData._dimensionHp = hp;
					end;
					if mp > inventoryCreatureData._dimensionMp then
						inventoryCreatureData._dimensionMp = mp;
					end;
					UpGrade(inventoryCreatureData.data._creatureId);
					currentTeamCount = currentTeamCount + 1;
				end;
			else
				
			end;
		end;
		
		local opTeam = dimensionStageInfo._oppDimensionTeam;
		local opTeamList = opTeam._creatureDatas;
		
		for i=0, opTeamList.Count -1 do
			local inventoryCreatureData = opTeamList[i];
			--log("MyTeam InsianceID=" .. myTeamList[i] .. ' CreatureID=' .. inventoryCreatureData.data._creatureId);
			DownGrade(inventoryCreatureData.data._creatureId);
		end;
		myTeamCP = myTeam:GetTeamCP(); 
		log("myteam CP=" .. myTeamCP .. " " .. currentTeamCount);
		log("stage " .. dimensionStageInfo.stageNo .. ' id=' .. dimensionStageInfo.dungeonId .. ' ' .. BoolValue(dimensionStageInfo.isClear) .. ' ' .. BoolValue(dimensionStageInfo.isFinalStage));
		local op = dimensionStageInfo._oppDimensionTeam;
		log("opteam " .. op.nickName .. ' id=' .. op.userId .. ' lvl=' .. op.lordLevel .. ' cp=' .. op:GetTeamCP() .. ' ' .. BoolValue(op.isClear));
		if currentTeamCount ~= 4 then
			
			MessageBox("Member=" .. currentTeamCount);
			lastDimensionTime = os.clock();
			return;
		end;
		if myTeamCP and currentTeamCount == 4 then		
			log("myteam ");
			
			if bot:IsWindowOpen("DungeonList") then
				local gui = bot:GetWindow("DungeonList");
				--log(gui:ToString());
				local dimensionDungeonElement = gui.uiDimensionDungeonList:GetRecommendedDungeonElement();
				if dimensionDungeonElement.isCurrentDungeon then
					log('start game2');
					dimensionDungeonElement.uiMiniInfoPopup:OnEnterDungeonButtonPressed(nil);
				else
					log('No current Dungeon');
					if dimensionStageInfo.stageNo == 10 then
						local remainTime = dbm.myDimensionStaminaInfo:GetUpdateRemainTime();
						log("Remaining Time = " .. remainTime);
						if remainTime > 0 then
							log("Go home");
							gui:OnHomeButtonPressed();
							return;
						else
							log("Re dun");
							--gui:OnHomeButtonPressed();
							return;
						end;
						lastDimensionTime = os.clock();
						return;
					end;
				end;
				return;
			end;
			if bot:IsWindowOpen("DungeonInfoDimension") then
				local gui = bot:GetWindow("DungeonInfoDimension");
				log('Auto DungeonInfoDimension');
				--gui:OnStartButtonPressed(nil);
				SaveUpgrade();
				NoUpgrade();
				DimensionBreakManager.instance:StartGame();
				RestoreUpgrade();
			end;
			lastDimensionTime = os.clock();
			return;
		end;
		
	
		
	end;
	lastDimensionTime = os.clock();
	--DimensionDungeonListGUI
end;

--if lastPVPTime == nil then
lastPVPTime = os.clock();
--end;

function IsInTeam(id,opTeamList)
	for i=0, opTeamList.Count -1 do
		local inventoryCreatureData = opTeamList[i];
		if inventoryCreatureData.data._creatureId == id then
			return true;
		end;
	end;
	return false;
end;

notEnoughStaminaCount = 0;
function AutoPVP()
	if lastPVPTime + 10 > os.clock() then
--		log('AutoPVP skip ' .. (lastPVPTime + 10) .. ' > ' .. os.clock() );
		return;
	end;
--	log("AutoPVP " .. os.clock());
	--NetworkManager.instance:SendGetPVPWholeRanking(100);
	local pvpGUI = bot:GetWindow("PVP");
	local pvp = PVPManager.instance;
	if pvp ~= nil then 
		if pvp.myPVPStaminaInfo.curValue <= 0 then
			log("PVP not enough stamina " .. pvp.myPVPStaminaInfo.curValue  );
			notEnoughStaminaCount = notEnoughStaminaCount + 1;
			if notEnoughStaminaCount > 1 then
				notEnoughStaminaCount = 0;
				log("ClickHome()");
				pvpGUI:OnHomeButtonPressed();
			end;
			lastPVPTime = os.clock();						
			return;
		end;	
		--local lastUserID = 0;
		local pvpIndex = -1;
		if(pvp._isPlaying) then
			log("pvp._isPlaying");	
			lastPVPTime = os.clock();
			return;
		end;			
		
		local myTeam = pvp._myPVPTeam;
		local myCP = myTeam:GetTeamCombatPower();
		log("MyCP = " .. myCP);
		


		for i=0,pvp.myMatchingPVPTeams.Count -1 do
			local pvpMonsterManager = pvp.myMatchingPVPTeams[i];
			if pvpMonsterManager.isClear == false  then
				local myTeamList = myTeam:GetCurrentTeamInstanceIdList();
				for i=0, myTeamList.Count -1 do
					local inventoryCreatureData = InventoryCreatureManager.instance:GetItem(myTeamList[i]); 
					log("MyTeam InsianceID=" .. myTeamList[i] .. ' CreatureID=' .. inventoryCreatureData.data._creatureId);
					if UpGrade(inventoryCreatureData.data._creatureId) then
					end;
				end;
			
				local opTeamList = pvpMonsterManager._creatureDatas;
				for i=0, opTeamList.Count -1 do
					local inventoryCreatureData = opTeamList[i];
					--log("MyTeam InsianceID=" .. myTeamList[i] .. ' CreatureID=' .. inventoryCreatureData.data._creatureId);
					DownGrade(inventoryCreatureData.data._creatureId);
				end;
				log("current: " .. pvpMonsterManager.nickName .. ' id=' .. pvpMonsterManager.userId .. ' lvl=' .. pvpMonsterManager.lordLevel .. ' cp=' .. pvpMonsterManager:GetTeamCP() .. ' ' .. BoolValue(pvpMonsterManager.isClear));
				log("MyCP = " .. myTeam:GetTeamCombatPower());
				--if myTeam:GetTeamCombatPower() - pvpMonsterManager:GetTeamCP() > 50000 then
				if pvpMonsterManager:GetTeamCP() < 125000 then
					log("StartGame");
					SaveUpgrade();
					NoUpgrade();
					pvp:StartGame(pvpMonsterManager.userId,false);
					lastPVPTime = os.clock();
					RestoreUpgrade();
					return;
				else
					log("Compat power too close");
				end;
			end;
			--log(json(pvpMonsterManager._internalData));
		end;
		-- can not found opponent if we have stamina then reset
		if pvp.myPVPStaminaInfo:IsEnough(1) then
			local pvpMatchingTabPage = pvpGUI.uiTabPages[0];
			local num = pvp.myPVPResetMatchingInfo:GetUpdateRemainTime();
			log(" TabPagetype=" .. pvpMatchingTabPage.tabPageType:ToString() .. ' ' .. num);
			if num <= 0 then
				PVPManager.instance:ResetMyPVPResetMatchingInfo(0);
				NetworkManager.instance:SendReqPVPMatching(true);
				--pvpMatchingTabPage:OnConfirmResetMatchingMessageResult(MessageBoxResultType.OK);
				lastPVPTime = os.clock();
				return;
			else
				if num > 2 then
					-- not enoght stamina return home
					log("ClickHome() and wait for " .. num);
					pvpGUI:OnHomeButtonPressed();
					lastPVPTime = os.clock();
					return;
				end;
			end;
		else
			-- not enoght stamina return home
			log("ClickHome()");
			pvpGUI:OnHomeButtonPressed();
			lastPVPTime = os.clock();
			return;
		end;
		--[[
		if pvpIndex ~= -1 then
			local pvpMonsterManager = pvp.myMatchingPVPTeams[pvpIndex];
			log('Auto start PVP with ' .. pvpMonsterManager.nickName .. ' ' .. pvpMonsterManager:GetTeamCP());
			local opTeamList = pvpMonsterManager._creatureDatas;
			for i=0, opTeamList.Count -1 do
				local inventoryCreatureData = opTeamList[i];
				log('OpTeam CreatureID=' .. inventoryCreatureData.data._creatureId);
				--DownGrade(inventoryCreatureData.data._creatureId);
			end;
			--pvp:StartGame(pvpMonsterManager.userId,false);
		else
			log('AutoPVP no opponent found');
		end;
		]]
		lastPVPTime = os.clock();
		--log(json(pvp.myMatchingPVPTeams));
	end;
--[[	
	local pvpHist = PVPBattleHistoryManager.instance;
	if pvpHist ~= nil then 
		for i=0,pvpHist._battleHistories.Count -1 do
			local pvpBattleHistoryInfo = pvpHist._battleHistories[i];
			log("history: " .. pvpBattleHistoryInfo.oppNickName .. ' id=' .. pvpBattleHistoryInfo.oppUserId );
			--log(json(pvpMonsterManager._internalData));
		end;
		
	end;
	
	local pvpUser = PVPUserRankManager.instance;
	if pvpUser ~= nil then 
		local wholeRank = pvpUser._userRanks[0];
		for i=0,wholeRank.Count -1 do
			local pvpUserRankInfo = wholeRank[i];
			log("whole: " .. pvpUserRankInfo._nickName .. ' id=' .. pvpUserRankInfo._userId .. ' lvl=' .. pvpUserRankInfo._lordLevel );
			--log(json(pvpMonsterManager._internalData));
		end;
		
	end;	
	--pvp:StartGame(473675,false);
]]
end;
log("Loading script 2");
if lastExpeditionTime == nil then
	lastExpeditionTime = os.clock();
end;
function AutoExpedition()
--21/09/2016 09:42:15 Expedetion ExpeditionGUI(Clone) (ExpeditionGUI) True
	if lastExpeditionTime + 10 > os.clock() then
		return;
	end;
	local expeditionGUI = bot:GetWindow("Expedetion");	-- Whole GUI
	if expeditionGUI ~= nil and bot:IsWindowOpen("Expedetion") then
		for i=0,expeditionGUI.uiExpeditionGUI.Length -1 do
			local windowGUI = expeditionGUI.uiExpeditionGUI[i];
			if windowGUI == nil then break end;
			log("#" .. i .. " " .. windowGUI:ToString());
		end;
		local expeditionListGUI = expeditionGUI.uiExpeditionGUI[0];
		local exped = ExpeditionManager.instance;
		--for i=0,exped.expeditionContainer.Count -1 do
--			local expeditionInfo = exped.expeditionContainer[i];
--			log("expeditionID=" .. expeditionInfo.expeditionID .. " status=" .. expeditionInfo.status:ToString() .. " regionID=" .. expeditionInfo.regionID .. " myMercenaryID=" .. expeditionInfo.myMercenaryID);
--			log("leftTime=" .. expeditionInfo.leftTime .. " totalTime=" .. expeditionInfo.totalTime .. " expeditionArtifactType=" .. expeditionInfo.expeditionArtifactType:ToString());
--			if expeditionInfo.leftTime == 0 then
--			end;
--		end;		
		for i=0,expeditionListGUI.listItem.Count -1 do
			local expeditionListItem = expeditionListGUI.listItem[i];
			if expeditionListItem ~= nil then
				local expeditionInfo = expeditionListItem.expeditionInfo;
				if expeditionInfo ~= nil then
					log("expeditionID=" .. expeditionInfo.expeditionID .. " status=" .. expeditionInfo.status:ToString() .. " regionID=" .. expeditionInfo.regionID .. " myMercenaryID=" .. expeditionInfo.myMercenaryID);
					log("leftTime=" .. expeditionInfo.leftTime .. " totalTime=" .. expeditionInfo.totalTime .. " expeditionArtifactType=" .. expeditionInfo.expeditionArtifactType:ToString());
					if expeditionInfo.status == ExpeditionStatus.Finish then
						log('OnClickReward');
						expeditionListItem:OnClickReward(nil);
						--lastExpeditionTime = os.clock() - 5;
						return;
					end;
				end;
			end;
		end;
		-- nothing to do go back home
		log("ClickHome()");
		expeditionGUI:OnClickHome();
		lastExpeditionTime = os.clock();
		return;
	end;
	
	local expeditionRewardGUI = bot:GetWindow("ExpedetionReward");	-- Reward GUI
	if expeditionRewardGUI ~= nil and bot:IsWindowOpen("ExpedetionReward") then
		local creature = expeditionRewardGUI.mercenaryCreature;
		log(creature.name .. " " .. creature.exp .. '/' .. creature.maxExp .. ' ' .. creature.needExp);
		if creature.needExp > 0 then
			expeditionRewardGUI:OneMoreExpeditionButtonClick(nil)
		else
			expeditionRewardGUI:OKButtonClick(nil);
		end;
		lastExpeditionTime = os.clock() -5 ; 
		return;
	end;
	
	local expeditionRewardManager = ExpeditionRewardManager.instance;
	for i=0, expeditionRewardManager.data.Length -1 do 
		--log(json(expeditionRewardManager.data[i]));
	end;
	lastExpeditionTime = os.clock() ;
end;

flgReload = true;
lastAutoUpgrade = os.clock();
function OnGUI()
	if CreatureDataManager == nil or flgReload == true then
		Init();
		AddButtonScript();
		flgReload = false;
	end;
	local stage = "";
	if GameApp.instance ~= nil then
		stage = stage .. " " .. GameApp.instance.gameSceneType:ToString() .. ' [' .. tablelength(tabUpgradeList) .. "]"
	end;
	if GameStage.instance ~= nil then
		stage = stage .. " " .. GameStage.instance.stageType:ToString() .. " " .. GameStage.instance.currentTurnNo;
		if DungeonManager.instance ~= nil then
			stage = stage .. " Id=" .. DungeonManager.instance.curDungeonId;
			--stage = stage .. " Turn=" .. DungeonManager.instance.curMissionTurn;
			--stage = stage .. " MissionNo=" .. DungeonManager.instance.curMissionNo;
		end;
		
		if AbusingScoreManager.instance ~= nil then
			stage = stage .. " abs" .. AbusingScoreManager.instance.abusingScore
		end; 
		
		if tabUpgrade ~= nil then
			--stage = stage .. " up" .. tablelength(tabUpgrade);
		end;
	else
		if GameApp.instance.gameSceneType == GameSceneType.Lobby then
			if tablelength(tabUpgradeList) > 0 then
				NoUpgrade();
			end;
		end;
	end;
	local pvp = PVPManager.instance;
	if pvp ~= nil and pvp.myPVPStaminaInfo ~= nil then	
		stage = stage .. " st=" .. pvp.myPVPStaminaInfo.curValue;
	end;
	
	local lordUser = LordUserManager.instance;
	if lordUser ~= nil then
		stage = stage .. " gu=" .. lordUser.myLordData.lordGauge .. " lvl=" .. lordUser.myLordData.lordLevel .. " en=" .. lordUser.lordUser.stamina;
		local bestDun = FindBestDungeon();
		if bestDun ~= nil then
			--stage = stage .. " dun=" .. bestDun;
		end;
	end;
	--stage = stage .. " " .. (os.clock() - lastAutoUpgrade);
	
	log("OnGUI() " .. stage .. " MD=" .. BoolValue(flgMonsterDown));	

	AutoClose();
	if bot.flgAuto then
		CreateTabUpGrade();
		if GameStage.instance ~= nil then
			AutoAttack();
		else
			if bot:IsWindowOpen("PVP") then
				AutoPVP();
				return;
			end;
			if bot:IsWindowOpen("DungeonList") then
				local gui = bot:GetWindow("DungeonList");
				if gui.uiDimensionDungeonList.gameObject.active then
					AutoDimension();
					return;
				end;
				if gui.uiNormalDungeonList.gameObject.active then
					AutoNormal();
					return;
				end;
			end;
			if bot:IsWindowOpen("DungeonInfoDimension") then
				AutoDimension();
				return;
			end;
			if bot:IsWindowOpen("Expedetion") or bot:IsWindowOpen("ExpedetionReward") then
				AutoExpedition();
				return;
			end		
			
			if bot:IsWindowOpen("DungeonInfoNormal") or bot:IsWindowOpen("DungeonWorldMap") then
				AutoNormal();
				return;
			end;
			
			if bot:IsWindowOpen("MainLobby") then
				local gui = bot:GetWindow("MainLobby");
				local exped = ExpeditionManager.instance;
				if exped ~= nil then
					for i=0,exped.expeditionContainer.Count -1 do
						local expeditionInfo = exped.expeditionContainer[i];
						--log("expeditionID=" .. expeditionInfo.expeditionID .. " status=" .. expeditionInfo.status:ToString() .. " regionID=" .. expeditionInfo.regionID .. " myMercenaryID=" .. expeditionInfo.myMercenaryID);
						--log("leftTime=" .. expeditionInfo.leftTime .. " totalTime=" .. expeditionInfo.totalTime .. " expeditionArtifactType=" .. expeditionInfo.expeditionArtifactType:ToString());
						if expeditionInfo.status == ExpeditionStatus.Finish then
							gui:OnExpeditionButtonPressed(nil);
							return;
						end;
						--if expeditionInfo.leftTime == 0 then
							
						--end;
					end;		
				end;
				
				--local pvp = PVPManager.instance;
				if pvp ~= nil then	
					
					if pvp.myPVPStaminaInfo:IsRequireSyncWithServer() then
						log("SendUpdatePVPStaminaInfo");
						NetworkManager.instance:SendUpdatePVPStaminaInfo();
						return;
					end;		
					local num = pvp.myPVPResetMatchingInfo:GetUpdateRemainTime();
					if pvp.myPVPStaminaInfo.curValue > 0 and  num < 2 then
						log("Has stamina and timewaite < 2 goto PVP");
						gui:CloseWindow();
						GUIManager.instance:OpenWindow(WindowType.PVP);
						return;
					end;
					--stage = stage .. " stamina=" .. pvp.myPVPStaminaInfo.curValue;
				end;
				
				if lordUser.lordUser.stamina >= 27 then
					local bestDun = FindBestDungeon();
					if bestDun ~= nil then
						local dunData = DungeonDataManager.GetData(bestDun);
						log("Bestdun = " .. bestDun .. " " .. dunData.dgName .. " regionID=" .. dunData.regionId);
						gui:OnShowWorldMap(nil);
					end;
				end;

				-- normal dunfeon
				
			end;
		end;
	end;
	
	-- auto upgrade in combat
	if lastAutoUpgrade + 3 < os.clock() then
		if GameStage.instance ~= nil then
			--log(GameStage.instance.stageType:ToString());
			if GameStage.instance.stageType == GameStageType.Normal or GameStage.instance.stageType == GameStageType.GuildRaidDungeon or GameStage.instance.stageType == GameStageType.Defense or GameStage.instance.stageType == GameStageType.DailyDungeon then
				DownMonsters();
				local myCamp = GameStage.instance.playerCamp;
				--log("Count=" .. myCamp.Count);
				for i=0,myCamp.members.Count -1 do
					local character = myCamp.members[i];
					--log(character:ToString());
					--log("" .. character.data.id);
					UpGrade(character.data.id);
				end;
				lastAutoUpgrade = os.clock();
			else
				lastAutoUpgrade = 0;
			end;
		end;
	end;	
end;

function HasMessageBox()
	if MessageBoxManager.instance ~= nil and MessageBoxManager.instance.messageBox ~= nil then
		return MessageBoxManager.instance.messageBox.gameObject.active;
	end;
	return false;
end;

function Test_Click()
-- "TurnTableGUI"  turm
--	local guiName = "DungeonList";
	local guiName = "DungeonInfoNormal";
	
	--ToggleGUI(guiName);
	bot:DumpGUI();
	--AutoPVP();
	--AutoDimension();
	--AutoExpedition();
	--bot:ClosePauseInGameGUIOpen();
	--tabUpgrade = {};
	--log("->" .. MessageBoxManager.instance.messageBox:ToString());
	if HasMessageBox() then
		log("Desc " ..  MessageBoxManager.instance.messageBox.uiDesc.text);
		log("Title " ..  MessageBoxManager.instance.messageBox.uiMessageBoxTitle.text);
		if "Allocate" == MessageBoxManager.instance.messageBox.uiMessageBoxTitle.text then
			MessageBoxManager.instance.messageBox:OnOKButtonPressed(nil);
		end;
	end;
end;

function B1()
	log("B1");
	local guiName = "DefenseRewardGUI";
	ToggleGUI(guiName);
	
end;

function AddButtonScript()
	bot.buttonScripts:Clear();
	bot:addButton("B1","B1()");
	bot:addButton("B2","B2()");
end;

log("Script 1.01 loaded");	
--Test();