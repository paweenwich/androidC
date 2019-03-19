--  romAutoQuest.lua 
if class ~= nil then
	AutoQuest_Rom = class("AutoQuest_Rom")

	function AutoQuest_Rom:ctor()
        self.enable = false;
		self.UpdateInterval = 5.0;
		self.nextUpdateTime = 0
		LogDebug("AutoQuest_Rom:ctor()");
	end
    
    function AutoQuest_Rom:Enable(value)
        self.enable = value;
    end;
    
    function AutoQuest_Rom:IsEnable()
        return self.enable;
    end;
    

	function AutoQuest_Rom:Clear(idleElapsed, time, deltaTime, creature)
		LogDebug("AutoQuest_Rom:Clear()");
		self.nextUpdateTime = 0
	end

	function AutoQuest_Rom:Start(idleElapsed, time, deltaTime, creature)
		if self.enable == false then return false; end;
	    --LogDebug("AutoQuest_Rom:Start()");
		--LogDebug("AutoQuest_Rom:Start() " .. (time - self.nextUpdateTime) .. " " .. idleElapsed);
	end

	function AutoQuest_Rom:End(idleElapsed, time, deltaTime, creature)
		if self.enable == false then return false; end;
        --self.target = nil;
	    LogDebug("AutoQuest_Rom:End() " .. (time - self.nextUpdateTime) .. " " .. idleElapsed);
	end
	
	function AutoQuest_Rom:Prepare(idleElapsed, time, deltaTime, creature)
		if self.enable == false then return false; end;
		if time < self.nextUpdateTime then
			return false;
		end
		LogDebug("AutoQuest_Rom:Prepare() " .. (time - self.nextUpdateTime) .. " " .. idleElapsed);
		self.nextUpdateTime = time + self.UpdateInterval					
		ROM_DoAutoQuest();
		
		return true; -- return false will keept in this stage
	end
	

	function AutoQuest_Rom:Update(idleElapsed, time, deltaTime, creature)
		if self.enable == false then return false; end;	
		LogDebug("AutoQuest_Rom:Update() " .. (time - self.nextUpdateTime) .. " " .. idleElapsed);
		--self.nextUpdateTime = time + self.UpdateInterval		
		
		return false;	-- true or false does not matter
	end
    
end;


function ROM_WalkToBoard()
    local boardNPC = 1016;
    LogDebug("ROM_WalkToBoard");
    -- check if we have 1016 on this map
    local npc = ROM_GetNPCPointByID(boardNPC);
    if npc ~= nil then
        -- found then just walk to it
        return ROM_WalkToNPC(Game.MapManager:GetMapID(),boardNPC);
    end;
    local nearestTownID = ROM_GetNearestTown() or 1;
    local mapReach,reason = ROM_TeleportTo(nearestTownID);
	if mapReach or (reason ~= nil) then
		local tempArgs = {};
		tempArgs.targetMapID = nearestTownID;
		tempArgs.showClickGround = true;
		tempArgs.allowExitPoint = true;
		local cmd = MissionCommandFactory.CreateCommand(tempArgs, MissionCommandMove);
		if(cmd)then
			LogDebug("ROM_WalkToBoard: Client_SetMissionCommand");
			Game.Myself:Client_SetMissionCommand( cmd );
		else
			LogDebug("ROM_WalkToBoard: cmd error");
		end
	end;	
    return false
end;

function ROM_WalkToNPC(mapID,npcID,finish)
    npcID = npcID or 1016;
    mapID = mapID or Game.MapManager:GetMapID();
    finish = finish or function() LogDebug("ROM_WalkToNPC Finish"); end;
    
    -- check nearest NPC
    LogDebug("ROM_WalkToNPC: From " .. Game.MapManager:GetMapID() .. " ->" .. mapID .. " npc=" .. npcID);
    local nearestNPC, nearestDist = ROM_GetNearestNPC();
    if nearestNPC ~= nil then
        if nearestNPC.data.staticData.id == npcID and  nearestDist < 5 then
            LogDebug("ROM_WalkToNPC: End (target reach)");
            finish();
            return true;
        end;
    end;
    
	local tempArgs = {};
	tempArgs.targetMapID = mapID;
	tempArgs.showClickGround = true;
	tempArgs.allowExitPoint = true;
    
    local npc = ROM_GetNPCPointByID(npcID);    
    if npc ~= nil then
        LogDebug("ROM_WalkToNPC: NPC found on map");
        -- found then just walk to it
        tempArgs.targetMapID = Game.MapManager:GetMapID();  -- change target to current map
        local tempVector3 = LuaVector3.zero;
        tempVector3:Set(npc.position[1],npc.position[2],npc.position[3]);
        tempArgs.targetPos = tempVector3;     
        tempArgs.callback = function(cmd, event)
            LogDebug("cmd=" .. MyTostring(cmd));
            LogDebug("event=" .. MyTostring(event));
            if 2 == event then
                finish();
            end
        end        
    else
        LogDebug("ROM_WalkToNPC: NPC not found on map");
        --if ROM_IsTeleportable(mapID) then
        --    LogDebug("ROM_WalkToNPC: try teleport");
        --    ROM_TeleportTo(mapID);
        --    return false;
        --else
            -- find nearest town map
            --local nMapID = ROM_tabTeleport[mapID]
            --if nMapID then
                --LogDebug("ROM_WalkToNPC: try teleport " .. nMapID);
                --ROM_TeleportTo(nMapID);
            --else
                -- just walk to that map and continue
                tempArgs.callback = function(cmd, event)
                    LogDebug("cmd=" .. MyTostring(cmd));
                    LogDebug("event=" .. MyTostring(event));
                    if 2 == event then
                    end
                end 
            --end;
        --end;
    end;
	local cmd = MissionCommandFactory.CreateCommand(tempArgs, MissionCommandMove);
	if(cmd)then
        LogDebug("ROM_WalkToNPC2: Client_SetMissionCommand");
		Game.Myself:Client_SetMissionCommand( cmd );
    else
        LogDebug("ROM_WalkToNPC2: cmd error");
	end
    return false
end;


function ROM_DumpWantedQuest()
    local wantedQuest = QuestProxy.Instance:getWantedQuest();
    LogDebug('----------- wantedQuest ' .. #wantedQuest .. '-------------');
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
    LogDebug("ROM_SubmitQuest: #wantedQuest=" .. #wantedQuest);
    for i=1,#wantedQuest do
        local wq = wantedQuest[i];
        local wd = wq.wantedData;
        if wq.questListType == SceneQuest_pb.EQUESTLIST_COMPLETE then
            LogDebug("Submitable quest found to submit " .. wd.id);
			ROM_VisitNearestNPC();
            ServiceQuestProxy.Instance:CallQuestAction(SceneQuest_pb.EQUESTACTION_SUBMIT,wd.id);
            return true;
        end;
		--[[
		local traceInfo = wq.traceInfo or "";
		--LogDebug("traceInfot " .. traceInfo );
		if string.match(traceInfo, "Mission Board") then	
            LogDebug("Submitable quest found (traceinfo) to submit " .. wd.id);
            ServiceQuestProxy.Instance:CallQuestAction(SceneQuest_pb.EQUESTACTION_SUBMIT,wd.id);
            return true;
		end;]]
    end;
    LogDebug("Submitable quest not found to submit");
    return false;
end;

function ROM_VisitNearestNPC(npcID)
	local nearestNPC, nearestDist = ROM_GetNearestNPC(npcID);
	if nearestNPC ~= nil then
		ServiceQuestProxy.Instance:CallVisitNpcUserCmd(nearestNPC.data.id);
	end;
end;



function ROM_AcceptQuest()
    local wantedQuest = QuestProxy.Instance:getWantedQuest();
    local maxWanted = QuestProxy.Instance:getMaxWanted();
    local submitCount = MyselfProxy.Instance:getVarValueByType(Var_pb.EVARTYPE_QUEST_WANTED) or 0;
    LogDebug("ROM_AcceptQuest: #wantedQuest=" .. #wantedQuest .. " maxWanted=" .. maxWanted .. " submitCount=" .. submitCount);
	local contents = {"move","kill","gather","selfie","remove_item","visit"};
	for j=1,#contents do
		local content = contents[j];
		for i=1,#wantedQuest do
			local wq = wantedQuest[i];
			local wd = wq.wantedData;
			--LogDebug("ROM_AcceptQuest: " .. QuestToString(wq));
			if wq.questListType == SceneQuest_pb.EQUESTLIST_CANACCEPT then
				LogDebug("ROM_AcceptQuest: Check canaccept " .. QuestToString(wq));
				
				if wd.Content == content then
					LogDebug("ROM_AcceptQuest: Found " .. QuestToString(wq) .. ' ' .. wd.id);
					ROM_VisitNearestNPC();
					ServiceQuestProxy.Instance:CallQuestAction(SceneQuest_pb.EQUESTACTION_ACCEPT,wd.id);
					return true;
				end;
			end;
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


function ROM_ClickNearestNPC(autoClose)
    autoClose = autoClose or false;
    LogDebug("ROM_ClickNearestNPC: " .. tostring(autoClose));
	local nearestNPC, nearestDist = ROM_GetNearestNPC();	
	--ListField(nearestNPC,"",{},"");
	if nearestNPC ~= nil then
        LogDebug("ROM_ClickNearestNPC: " .. MonsterToString(nearestNPC) .. ' ' .. nearestDist);
		Game.Myself:Client_LockTarget(nearestNPC);
		--FunctionVisitNpc.me:AccessTarget(nearestNPC, nil, nil);
		Game.Myself:Client_AccessTarget(nearestNPC);
        if autoClose then
            ROM_DelayCall(5000,
                function(param) 
                    LogDebug("ROM_ClickNearestNPC auto close Called");
                    if nearestNPC.data.staticData.id == 1016 then   -- mission board
                        GameFacade.Instance:sendNotification(UIEvent.CloseUI,UIViewType.NormalLayer)
                    else
                        GameFacade.Instance:sendNotification(UIEvent.CloseUI,UIViewType.DialogLayer);
                    end;
					ServiceQuestProxy.Instance:CallQuestList(SceneQuest_pb.EQUESTLIST_CANACCEPT,101);
                    --FunctionVisitNpc.me:AccessTarget(nil, nil, nil);            
                end,
            nil);
        end;
    else
        LogDebug("ROM_ClickNearestNPC: not found");
	end;	
end;

function ROM_GetSubmitableQuest()
	local wantedQuest = QuestProxy.Instance:getWantedQuest();
    for i=1,#wantedQuest do
        local wq = wantedQuest[i];
        --local wd = wq.wantedData;
		local traceInfo = wq.traceInfo or "";
		if string.match(traceInfo, "Mission Board") then	
			--LogDebug(QuestToString(wq));
			return wq;
		end;
    end;
	return nil;
end;

function ROM_GetDailyBox()
	for i, v in pairs(QuestProxy.Instance.questList[1]) do 
        if v ~= nil then
            if v.type == "daily_box" and v.complete == false and v.id == 601500001 then
                return v;
            end;
        end;
    end 
end;
function ROM_GetDailyQuest()
    local igNoreID = {1000070001}
    local qBox = ROM_GetDailyBox();
    if qBox then
        for i, v in pairs(QuestProxy.Instance.questList[1]) do 
            if v ~= nil  then
                if v.type == "daily_maprand" and v.complete == false and v.step ~= 0 and not TableUtil.HasValue(igNoreID,v.id) then
                    return v;
                end;
            end;
        end 
        if qBox.step == 2 then
            for i, v in pairs(QuestProxy.Instance.questList[1]) do 
                if v ~= nil  then
                    if v.type == "daily_maprand" and v.complete == false and v.step == 0 and v.map == 48 and not TableUtil.HasValue(igNoreID,v.id) then
                        return v;
                    end;
                end;
            end 
        end;
        return qBox;
    end;
--[[	for i, v in pairs(QuestProxy.Instance.questList[3]) do 
        if v ~= nil and v.map == Game.MapManager:GetMapID() then
            if v.type == "daily_maprand" then
                return v;
            end;
        end;
    end     

	for i, v in pairs(QuestProxy.Instance.questList[2]) do 
        if v ~= nil and v.map == Game.MapManager:GetMapID() then
            if v.type == "daily_maprand" then
                return v;
            end;
        end;
    end     ]]
    -- acceptable 
    -- main daily_box
    --daily_box
    return nil;
end;

function ROM_DoDailyQuest()
    local q = ROM_GetDailyQuest();
    if q then
        local questString = QuestToString(q);
        ListField(q,"",{},"    ");          
        LogDebug("ROM_DoDailyQuest: Acceptable Quest " .. questString );
        if ROM_TeleportTo(q.map) == false then
            return;
        end;
        if q.questDataStepType == "kill" then
            LogDebug("KILL");
            if ROM_WalkToNPCPos(q.params.monster,q.map) then
                -- wait for friend
                if ROM_IsTeamReady() then
                    ROM_CommandHuntMonsterFromQuest(q);
                    --ROM_CommandVisitMonster(q.wantedData.MapId,q.params.monster);
                else
                    LogDebug("ROM_DoDailyQuest: kill (ROM_WalkToNPCPos) wait for team");
                end;
            end;
           --params.monster=54030,params.num=1
        end;
        if q.questDataStepType == "dialog" then
           LogDebug("DIALOG"); 
           ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil,2, q.step); 
        end;
        
        if q.questDataStepType == "visit" then
            if q.pos then
                if ROM_IsMeNear(q.map,q.pos) then
                    local nearestNPC, nearestDist = ROM_GetNearestNPC();	
                    ServicePlayerProxy.Instance:CallMapObjectData(nearestNPC.data.id);
                    ROM_VisitNearestNPC();                
                    ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, q.step+1, q.step);  
                else
                    ROM_CommandGOTO(q.map,q.pos);
                end;
                return;
            end;
            if ROM_WalkToNPCPos(q.params.npc,q.map) then
                LogDebug("ROM_DoDailyQuest: reach");
                local nearestNPC, nearestDist = ROM_GetNearestNPC();	
                ServicePlayerProxy.Instance:CallMapObjectData(nearestNPC.data.id);
                ROM_VisitNearestNPC();
                if q.type == "daily_box" then
                    if q.step == 1 then
                        ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, 3, q.step);
                    end;
                end
                --ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, nil, q.step); 		
                if  q.step == 0 then
                    ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, 2, q.step); 				
                else
                    local key = "" .. q.id  .. "_" .. q.step;
                    if tabAnswer[key] then
                    --if q.id == 1000080001 and q.step==1 then
                        ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, tabAnswer[key], q.step);
                        ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, nil, q.step); 	
                    else
                        --ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, q.steps[q.step].staticData.SubGroup, q.step);   
                        ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, 0, q.step); 				
                    end;
                end;
            else
                LogDebug("ROM_DoDailyQuest: not reach ");
            end;
        end;
        if q.questDataStepType == "selfie" then
            LogDebug("target pos = " .. MyTostring(q.pos));
            --if ROM_TeleportTo(q.wantedData.MapId) then
                if ROM_IsMeNear(q.map,q.pos) then
                    if ROM_IsTeamReady() then
                        LogDebug("ROM_DoDailyQuest: selfie take photo");
                        ServiceNUserProxy.Instance:CallStateChange(ProtoCommon_pb.ECREATURESTATUS_SELF_PHOTO);
                        ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, 0, q.step); 
                        ServiceNUserProxy.Instance:CallStateChange(0);                            
                    else
                        LogDebug("ROM_DoDailyQuest: selfie wait for team");
                    end;
                else
                    ROM_CommandGOTO(q.map,q.pos);
                end;
            --end;
        end;
        if q.questDataStepType == "use" then
            LogDebug("target pos = " .. MyTostring(q.pos));
            --if ROM_TeleportTo(q.wantedData.MapId) then
                if ROM_IsMeNear(q.map,q.pos) then
                    if ROM_IsTeamReady() then
                        LogDebug("ROM_DoDailyQuest: use");
                        --[[
                        03/18/19 15:24:15 MyTick:Tick() table: 0x70588c80 1.01 nil
03/18/19 15:24:18 SEND: SceneQuest_pb.RunQuestStep step: 4 subgroup: 0 questid: 1000050001
03/18/19 15:24:18 RECV: RecvQuestStepUpdate data { config { FinishJump: 0 Content: dialog Map: 48 params { params { items { items { value: 52916 key: 1 } } key: dialog } } Auto: 1 Class: 0 QuestName:
Ill-tempered Worker SubGroup: 2 Type: daily_maprand FailJump: 0 TraceInfo: WhetherTrace: 1 allrewardid: 880005 FirstClass: 0 Level: 0 RewardGroup: 0 Name: Ill-tempered Worker } } step: 5 id: 100005000
1
03/18/19 15:24:19 RECV< ROM_RecvMemberDataUpdate id=4300736919 [NoDaMe] sp=100
03/18/19 15:24:20 SEND: SceneQuest_pb.RunQuestStep questid: 1000050001 step: 5
03/18/19 15:24:20 RECV: RecvQuestStepUpdate data { config { FinishJump: 0 Content: use Map: 48 params { params { value: Check key: button } params { key: distance value: 3 } params { value: 72 key: it
emIcon } params { value: Rope key: name } params { items { items { value: -6.1 key: 1 } items { value: 3.25 key: 2 } items { value: 53.33 key: 3 } } key: pos } } Auto: 0 Class: 0 QuestName: Ill-temper
ed Worker SubGroup: 2 Type: daily_maprand FailJump: 0 TraceInfo: Continue to find Long-term worker Carville's rope WhetherTrace: 1 allrewardid: 880005 FirstClass: 0 Level: 0 RewardGroup: 0 Name: Ill-t
empered Worker } } step: 6 id: 1000050001

                        ]]
                        --ServiceNUserProxy.Instance:CallStateChange(ProtoCommon_pb.ECREATURESTATUS_SELF_PHOTO);
                        --ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, 0, q.step); 
                        --ServiceNUserProxy.Instance:CallStateChange(0);   
                        ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, q.steps[q.step].staticData.SubGroup, q.step);                         
                    else
                        LogDebug("ROM_DoDailyQuest: use wait for team");
                    end;
                else
                    ROM_CommandGOTO(q.map,q.pos);
                end;
            --end;
        end;        
        --questDataStepType=use
        --questDataStepType=selfie
    end;
end;

function ROM_DoAutoQuest()
	local currentMapID = Game.MapManager:GetMapID();
	local myPos = Game.Myself:GetPosition();
	local nearestNPC, nearestDist = ROM_GetNearestNPC();
    local maxQuestWanted = QuestProxy.Instance:getMaxWanted();
	local wantedQuest = QuestProxy.Instance:getWantedQuest();
    local submitCount = MyselfProxy.Instance:getVarValueByType(Var_pb.EVARTYPE_QUEST_WANTED) or 0;	
	if nearestNPC ~= nil  then
		LogDebug("ROM_DoAutoQuest: NeartesNPC=" .. MonsterToString(nearestNPC) .. ' ' .. nearestDist);
	end;
    LogDebug("ROM_DoAutoQuest: maxQuestWanted=" .. maxQuestWanted .. " #wantedQuest=" .. #wantedQuest .. " submitCount=" .. submitCount);
	if submitCount >= maxQuestWanted then
		LogDebug("ROM_DoAutoQuest no quest left");
		UIUtil.FloatMsgByText("AutoQuest Done");			
	end;
	-- check if we have quest that can be accept
	local q = ROM_GetAcceptedQuest();
	if q ~= nil then
		local questString = QuestToString(q);
		LogDebug("ROM_DoAutoQuest: Has Accepted Wanted Quest " .. questString );
        ListField(q,"",{},"    ");  
		local traceInfo = q.traceInfo or "";
		LogDebug("ROM_DoAutoQuest: traceInfo=" .. traceInfo );
        LogDebug("ROM_DoAutoQuest: Content=" .. q.wantedData.Content );
		if string.match(traceInfo, "Mission Board") then	
            if q.params.team_can_finish and q.params.team_can_finish ~= 1 then
                LogDebug("ROM_DoAutoQuest: Mission Board wait for team to finish");
                return;
            end;
			LogDebug("ROM_DoAutoQuest: Mission complete walk to board");
			if ROM_WalkToBoard() then
				-- near board
                if ROM_IsTeamReady() then
                    LogDebug("ROM_DoAutoQuest: Near board submit");
                    --ROM_SubmitQuest();
                    --LogDebug("Near board refresh");
                    ROM_VisitNearestNPC();
                    ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, nil, q.step); 				
                    ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, 0, q.step); 				
                    ServiceQuestProxy.Instance:CallQuestList(SceneQuest_pb.EQUESTLIST_CANACCEPT,101);
                    --ROM_ClickNearestNPC(true);
                else
                    LogDebug("ROM_DoAutoQuest: Mission Board wait for team");
                end;
			end;
		else
			--ListField(q,"",{},"    ");  
			--LogDebug(MyTostring(q));
			if q.wantedData.Content == "move" then
                LogDebug("ROM_DoAutoQuest: move");
				ListField(q,"",{},"    ");
				if q.wantedData.MapId ~= nil then
					if ROM_TeleportTo(q.wantedData.MapId) then
						if ROM_WalkToNPC(q.wantedData.MapId,q.params.npc) then
							if ROM_IsTeamReady() then
								ROM_VisitNearestNPC();
								ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, nil, q.step); 
								GameFacade.Instance:sendNotification(UIEvent.CloseUI,UIViewType.DialogLayer);
								LogDebug(QuestToString(q));
								ROM_ClickNearestNPC(true);
							else
								LogDebug("ROM_DoAutoQuest: visit wait for team");
							end;
						end;
					end;
				else
					LogDebug("Should not be here");
				end;
			elseif q.wantedData.Content == "kill" then
                LogDebug("ROM_DoAutoQuest: kill");
				ListField(q,"",{},"    ");  
				if q.params.monster ~= nil or q.params.groupId then
					-- goto that monster
					if ROM_TeleportTo(q.wantedData.MapId) then
						if ROM_WalkToNPCPos(q.params.monster,q.wantedData.MapId) then
							-- wait for friend
							if ROM_IsTeamReady() then
                                ROM_CommandHuntMonsterFromQuest(q);
								--ROM_CommandVisitMonster(q.wantedData.MapId,q.params.monster);
							else
								LogDebug("ROM_DoAutoQuest: kill (ROM_WalkToNPCPos) wait for team");
							end;
						end;
					end;
					--if q.params.monster ~= nil then
						--ROM_CommandVisitMonster(q.wantedData.MapId,q.params.monster);
					--else
						--ROM_CommandVisitMonster(q.wantedData.MapId,q.params.groupId);
					--end;
				else
					-- goto board to submit quest 
					-- it might possibile that this map does not have board will see
                    if ROM_WalkToBoard() then
                        if ROM_IsTeamReady() then
                            ROM_ClickNearestNPC(true);
                        else
                            LogDebug("ROM_DoAutoQuest: kill (ROM_WalkToBoard) wait for team");
                        end;
                    end;
				end;
			elseif q.wantedData.Content == "selfie" or q.questDataStepType == "selfie" then
                LogDebug("ROM_DoAutoQuest: selfie");
				ListField(q,"",{},"    ");  
				if q.wantedData.MapId ~= nil then
					LogDebug("target pos = " .. MyTostring(q.staticData.Params.tarpos));
					LogDebug("target pos = " .. MyTostring(q.pos));
					if ROM_TeleportTo(q.wantedData.MapId) then
						if ROM_IsMeNear(q.wantedData.MapId,q.pos) then
							if ROM_IsTeamReady() then
								LogDebug("ROM_DoAutoQuest: selfie take photo");
								ServiceNUserProxy.Instance:CallStateChange(ProtoCommon_pb.ECREATURESTATUS_SELF_PHOTO);
								ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, 0, q.step); 
								ServiceNUserProxy.Instance:CallStateChange(0);                            
							else
								LogDebug("ROM_DoAutoQuest: selfie wait for team");
							end;
						else
							ROM_CommandGOTO(q.wantedData.MapId,q.pos);
						end;
					end;
				else
					LogDebug("Should not be here");
				end                            
			elseif q.wantedData.Content == "remove_item" then
                LogDebug("ROM_DoAutoQuest: remove_item");
				ListField(q,"",{},"    ");  
				if q.params.monster ~= nil then
					LogDebug("----");
					ListField(q.params,"",{},"    ");  
					local num = BagProxy.Instance:GetAllItemNumByStaticID(q.params.item[1].id);
					LogDebug("num=" .. num);
					if num <  q.params.item[1].num then
						if ROM_TeleportTo(q.wantedData.MapId) then
							ROM_CommandVisitMonster(q.wantedData.MapId,q.params.monster);
						end;
					end;
				else
					if q.wantedData.MapId ~= nil then
						--ROM_WalkToNPC(q.staticData.Map,q.wantedData.NpcId,
						if ROM_TeleportTo(q.staticData.Map) then
							ROM_WalkToNPC(q.staticData.Map,q.params.npc,
								function()
									ROM_VisitNearestNPC();
									ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, nil, q.step); 
									GameFacade.Instance:sendNotification(UIEvent.CloseUI,UIViewType.DialogLayer);
									LogDebug(QuestToString(q));
									ROM_ClickNearestNPC(true);
								end
							);
						end;
					else
						--LogDebug("Should not be here");
					end                            
				end;
			elseif q.wantedData.Content == "gather" then
                LogDebug("ROM_DoAutoQuest: gather");
				ListField(q,"",{},"    ");  
				if q.params.monster ~= nil or q.params.groupId then				
					if q.params.monster ~= nil then
						LogDebug("ROM_DoAutoQuest: gather monster " .. q.params.monster);										
						if ROM_TeleportTo(q.wantedData.MapId) then
							if ROM_WalkToNPCPos(q.params.monster,q.wantedData.MapId) then
								-- wait for friend
								if ROM_IsTeamReady() then
                                    ROM_CommandHuntMonsterFromQuest(q);
									--ROM_CommandVisitMonster(q.wantedData.MapId,q.params.monster);
								else
									LogDebug("ROM_DoAutoQuest: gather (ROM_WalkToNPCPos) wait for team");
								end;
							end;
						end;
						--ROM_CommandVisitMonster(q.wantedData.MapId,q.params.monster);
					else
						LogDebug("ROM_DoAutoQuest: gather groupId " .. q.params.groupId);
						local mons = ROM_GetMonsterByGroupID(q.params.groupId);
						LogDebug("ROM_DoAutoQuest: gather select " .. mons[1].id);
						if ROM_TeleportTo(q.wantedData.MapId) then
							if ROM_WalkToNPCPos(mons[1].id,q.wantedData.MapId) then
								-- wait for friend
								if ROM_IsTeamReady() then
                                    ROM_CommandHuntMonsterFromQuest(q);
									--ROM_CommandVisitMonster(q.wantedData.MapId,mons[1].id);
								else
									LogDebug("ROM_DoAutoQuest: gather (ROM_WalkToNPCPos) wait for team");
								end;
							end;
						end;
						--ROM_CommandVisitMonster(q.wantedData.MapId,mons[1].id);
					end;
				else
					-- goto board to submit quest 
					--ROM_WalkToNPC(mapid,q.params.npc);
				end;
			elseif q.wantedData.Content == "visit" then
                LogDebug("ROM_DoAutoQuest: visit");
				ListField(q,"",{},"    ");  
				if ROM_TeleportTo(q.map) then
					if ROM_WalkToNPC(q.map,q.params.npc) then
						if ROM_IsTeamReady() then
							ROM_VisitNearestNPC();
							ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, nil, q.step); 
							GameFacade.Instance:sendNotification(UIEvent.CloseUI,UIViewType.DialogLayer);
							LogDebug(QuestToString(q));
						else
							LogDebug("ROM_DoAutoQuest: visit wait for team");
						end;
					end;
				end;
				--[[ROM_WalkToNPC(q.map,q.params.npc,
					function()
						ROM_VisitNearestNPC();
						ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, nil, q.step); 
						GameFacade.Instance:sendNotification(UIEvent.CloseUI,UIViewType.DialogLayer);
						LogDebug(QuestToString(q));
						--ROM_ClickNearestNPC(true);
						--FunctionVisitNpc.me:AccessTarget(nil, nil, nil);		
					end
				);]]
			else
				LogDebug("Quest type not suppoted");
			end;
		end;
	else 
		ROM_DumpWantedQuest();
		LogDebug("ROM_DoAutoQuest: No quest already accept walk to board");
		if ROM_WalkToBoard() then
			-- refresh wanted quest list
			LogDebug("ROM_DoAutoQuest: try refresh())");
			ServiceQuestProxy.Instance:CallQuestList(SceneQuest_pb.EQUESTLIST_CANACCEPT,101);
			if ROM_SubmitQuest() == false then
				LogDebug("Before ROM_AcceptQuest");		
				ROM_AcceptQuest();
            else
                ROM_DelayCall(3000,
                    function(param) 
                        LogDebug("ROM_DoAutoQuest auto close UI");
                        ROM_CloseAllModal();
                    end,
                nil);   
			end;
		end;
	end;
	LogDebug("done");

end;

function ROM_DoSelfie()
    -- SENDPROTO [9] [42] status: 7
    ServiceNUserProxy.Instance:CallStateChange(ProtoCommon_pb.ECREATURESTATUS_SELF_PHOTO);
--[[
SENDPROTO [5] [27] random: 0 skillID: 20004001 data { pos { z: 120400 y: 5179 x: 16700 } hitedTargets { type: 1 charid: 4313990901 damage: 1 } dir: 351549 number: 1 } charid: 4313990901
01/22/19 10:15:57 SENDPROTO [8] [4] subgroup: 0 step: 1 questid: 53360001
]]
    -- GameConfig.NewRole.flashskill
--[[    
    
	local phaseData = SkillPhaseData.Create(GameConfig.NewRole.flashskill)
	for i=1,#nearMonster do
		-- helplog("nearMonster checkFocus_N:",nearMonster[i].data.id)
		phaseData:AddTarget(nearMonster[i].data.id, 1, 1)
	end
	for i=1,#nearPlayers do
		-- helplog("nearPlayers checkFocus_N:",nearPlayers[i].data.id)
		phaseData:AddTarget(nearPlayers[i].data.id, 1, 1)
	end
	phaseData:SetSkillPhase(SkillPhase.Attack)
	Game.Myself:Client_UseSkillHandler(0, phaseData)]]
end;

function ROM_GetMapNPCs()
    local npcList = Game.MapManager:GetNPCPointArray();
	local ret = {};
    if npcList then
        tableForEach(npcList, function(i, v)
            if(v and v.ID and v.position and v.Icon)then
                local npcData = Table_Npc[v.ID];
                if npcData  then
                    --LogDebug(MyTostring(npcData) .. " " .. v.ID .. " " .. tostring(v.position));
                    --LogDebug(MyTostring(v));
                    ret[#ret + 1] = v;
                end;
            end;
        end);
    end;
	return ret;
end;

function ROM_GetMapNPCsEx()
    local npcList = Game.MapManager:GetNPCPointArray();
	local ret = {};
    if npcList then
        tableForEach(npcList, function(i, v)
            --if(v and v.id and v.Position and v.Icon)then
                --local npcData = Table_Npc[v.ID];
                --if npcData  then
                    --LogDebug(MyTostring(npcData) .. " " .. v.ID .. " " .. tostring(v.position));
                    --LogDebug(MyTostring(v));
                    ret[#ret + 1] = v;
                --end;
            --end;
        end);
    end;
	return ret;
end;


LogDebug("romAutoQuest.lua 1.0");
	