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
    -- wrong map use morrc (16) as base for now
    
	local tempArgs = {};
	tempArgs.targetMapID = 16;
	tempArgs.showClickGround = true;
	tempArgs.allowExitPoint = true;
    tempArgs.callback = function(cmd, event)
        LogDebug("cmd=" .. MyTostring(cmd));
        LogDebug("event=" .. MyTostring(event));
        if 2 == event then
            LogDebug("ROM_WalkToBoard auto walk to board");
            --ROM_WalkToNPC(Game.MapManager:GetMapID(),boardNPC);
            ROM_WalkToBoard();
        end
    end
	local cmd = MissionCommandFactory.CreateCommand(tempArgs, MissionCommandMove);
	if(cmd)then
        LogDebug("ROM_WalkToBoard: Client_SetMissionCommand");
		Game.Myself:Client_SetMissionCommand( cmd );
    else
        LogDebug("ROM_WalkToBoard: cmd error");
	end
    return false
end;

function ROM_WalkToNPC(mapID,npcID,finish)
    npcID = npcID or 1016;
    mapID = mapID or 16;
    finish = finish or function() LogDebug("ROM_WalkToNPC Finish"); end;
    
    -- check nearest NPC
    --LogDebug("ROM_WalkToNPC2: MapID=" .. Game.MapManager:GetMapID() .. " [" .. Game.MapManager:GetMapName() .. "]");
    LogDebug("ROM_WalkToNPC2: From " .. Game.MapManager:GetMapID() .. " ->" .. mapID .. " npc=" .. npcID);
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
        -- just walk to that map and continue
        tempArgs.callback = function(cmd, event)
            LogDebug("cmd=" .. MyTostring(cmd));
            LogDebug("event=" .. MyTostring(event));
            if 2 == event then
                LogDebug("ROM_WalkToNPC2 continue");
                --ROM_WalkToNPC(Game.MapManager:GetMapID(),boardNPC);
                ROM_WalkToNPC2(mapID,npcID,finish);
            end
        end        
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
    LogDebug("ROM_SubmitQuest: #wantedQuest=" .. #wantedQuest);
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
    LogDebug("ROM_AcceptQuest: #wantedQuest=" .. #wantedQuest);
	local contents = {"move","kill","selfie","remove_item"};
	for j=1,#contents do
		local content = contents[j];
		for i=1,#wantedQuest do
			local wq = wantedQuest[i];
			local wd = wq.wantedData;
			if wq.questListType == SceneQuest_pb.EQUESTLIST_CANACCEPT then
				LogDebug(QuestToString(wq));
				if wd.Content == content then
					LogDebug("ROM_AcceptQuest found " .. content);
					ServiceQuestProxy.Instance:CallQuestAction(SceneQuest_pb.EQUESTACTION_ACCEPT,wq.id);
					return true;
				end;
--[[				if wd.Content == "kill" then
					LogDebug("ROM_AcceptQuest kill found");
					ServiceQuestProxy.Instance:CallQuestAction(SceneQuest_pb.EQUESTACTION_ACCEPT,wq.id);
					return true;
				end;
				if wd.Content == "selfie" then
					LogDebug("ROM_AcceptQuest selfie found");
					ServiceQuestProxy.Instance:CallQuestAction(SceneQuest_pb.EQUESTACTION_ACCEPT,wq.id);
					return true;
				end;
				if wd.Content == "remove_item" then
					LogDebug("ROM_AcceptQuest collect found");
					ServiceQuestProxy.Instance:CallQuestAction(SceneQuest_pb.EQUESTACTION_ACCEPT,wq.id);
					return true;
				end;]]
				
				
				--LogDebug("Submitable quest found to submit");
				--ServiceQuestProxy.Instance:CallQuestAction(SceneQuest_pb.EQUESTACTION_SUBMIT,wq.id);
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

function ROM_ClickNearestNPC()
	local nearestNPC, nearestDist = ROM_GetNearestNPC();	
	--ListField(nearestNPC,"",{},"");
	if nearestNPC ~= nil then
		Game.Myself:Client_LockTarget(nearestNPC);
		FunctionVisitNpc.me:AccessTarget(nearestNPC, nil, nil);
	end;	
end;

function ROM_DoAutoQuest()
	local currentMapID = Game.MapManager:GetMapID();
	local myPos = Game.Myself:GetPosition();
	local nearestNPC, nearestDist = ROM_GetNearestNPC();
	if nearestNPC ~= nil  then
		LogDebug("ROM_DoAutoQuest: NeartesNPC=" .. MonsterToString(nearestNPC) .. ' ' .. nearestDist);
	end;
	-- check if we have quest that can be accept
	local q = ROM_GetAcceptedQuest();
	if q ~= nil then
		local questString = QuestToString(q);
		LogDebug("Has Accepted Wanted Quest " .. questString );
		local traceInfo = q.traceInfo or "";
		LogDebug("traceInfot " .. traceInfo );
		if string.match(traceInfo, "Mission Board") then	
			LogDebug("Mission complete walk to board");
			if ROM_WalkToBoard() then
				-- near board
				LogDebug("Near board");
				Game.Myself:Client_LockTarget(nearestNPC);
				FunctionVisitNpc.openWantedQuestPanel( 101, nearestNPC);
				if ROM_SubmitQuest() == false then
					ROM_AcceptQuest();
					
				end;
			end;
		else
			--ListField(q,"",{},"    ");  
			--LogDebug(MyTostring(q));
			if q.wantedData.Content == "move" then
				ListField(q,"",{},"    ");
				if q.wantedData.MapId ~= nil then
					ROM_WalkToNPC(q.wantedData.MapId,q.params.npc,
						function()
							--local nearestNPC, nearestDist = ROM_GetNearestNPC();
							--Game.Myself:Client_LockTarget(nearestNPC);
							LogDebug("ROM_DoAutoQuest: click");
							ROM_ClickNearestNPC();
							FunctionVisitNpc.me:AccessTarget(nil, nil, nil);		
						end
					);
				else
					LogDebug("Should not be here");
				end;
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
			elseif q.wantedData.Content == "selfie" then
				ListField(q,"",{},"    ");  
				if q.wantedData.MapId ~= nil then
					LogDebug("target pos = " .. MyTostring(q.staticData.Params.tarpos));
					LogDebug("target pos = " .. MyTostring(q.pos));
					ROM_CommandGOTO(q.wantedData.MapId,q.pos);
					--ROM_WalkToNPC(q.wantedData.MapId,q.wantedData.NpcId,
					--    function()
					--        local nearestNPC, nearestDist = ROM_GetNearestNPC();
					--        Game.Myself:Client_LockTarget(nearestNPC);
					--    end
					--);
				else
					LogDebug("Should not be here");
				end                            
			elseif q.wantedData.Content == "remove_item" then
				ListField(q,"",{},"    ");  
				if q.wantedData.MapId ~= nil then
					ROM_WalkToNPC(q.staticData.Map,q.wantedData.NpcId);
					--LogDebug("target pos = " .. MyTostring(q.staticData.Params.tarpos));
					--LogDebug("target pos = " .. MyTostring(q.pos));
					--ROM_CommandGOTO(q.wantedData.MapId,q.pos);
					--ROM_WalkToNPC(q.wantedData.MapId,q.wantedData.NpcId,
					--    function()
					--        local nearestNPC, nearestDist = ROM_GetNearestNPC();
					--        Game.Myself:Client_LockTarget(nearestNPC);
					--    end
					--);
				else
					--LogDebug("Should not be here");
				end                            
			else
				LogDebug("Quest type not suppoted");
			end;
		end;
	else 
		LogDebug("ROM_DoAutoQuest: No quest to already accept walk to board");
		if ROM_WalkToBoard() then
			-- near board
			LogDebug("ROM_DoAutoQuest: at board need");
			-- TODO: find a way to click
			ROM_ClickNearestNPC();
			--Game.Myself:Client_LockTarget(nearestNPC);
			if ROM_SubmitQuest() == false then
				ROM_AcceptQuest();
				--FunctionVisitNpc.me:AccessTarget(nil, nil, nil);
			end;
		end;
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

end;


LogDebug("romAutoQuest.lua 1.0");
