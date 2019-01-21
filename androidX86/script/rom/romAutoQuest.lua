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
--[[    tempArgs.callback = function(cmd, event)
        LogDebug("cmd=" .. MyTostring(cmd));
        LogDebug("event=" .. MyTostring(event));
        if 2 == event then
            LogDebug("ROM_WalkToBoard auto walk to board");
            --ROM_WalkToNPC(Game.MapManager:GetMapID(),boardNPC);
            ROM_WalkToBoard();
        end
    end]]
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
		LogDebug("Has Accepted Wanted Quest " .. questString );
		local traceInfo = q.traceInfo or "";
		LogDebug("traceInfot " .. traceInfo );
		if string.match(traceInfo, "Mission Board") then	
			LogDebug("Mission complete walk to board");
			if ROM_WalkToBoard() then
				-- near board
				--LogDebug("Near board submit");
				--ROM_SubmitQuest();
				--LogDebug("Near board refresh");
				--ServiceQuestProxy.Instance:CallQuestList(SceneQuest_pb.EQUESTLIST_CANACCEPT,101);
                ROM_ClickNearestNPC(true);
			end;
		else
			--ListField(q,"",{},"    ");  
			--LogDebug(MyTostring(q));
			if q.wantedData.Content == "move" then
				ListField(q,"",{},"    ");
				if q.wantedData.MapId ~= nil then
					ROM_WalkToNPC(q.wantedData.MapId,q.params.npc,
						function()
							local nearestNPC, nearestDist = ROM_GetNearestNPC();
							--Game.Myself:Client_LockTarget(nearestNPC);
							LogDebug("ROM_DoAutoQuest: move click");
							ServiceQuestProxy.Instance:CallVisitNpcUserCmd(nearestNPC.data.id);
							ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, nil, q.step); 
							GameFacade.Instance:sendNotification(UIEvent.CloseUI,UIViewType.DialogLayer);
							LogDebug(QuestToString(q));
							ROM_ClickNearestNPC(true);
							--FunctionVisitNpc.me:AccessTarget(nil, nil, nil);		
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
				else
					LogDebug("Should not be here");
				end                            
			elseif q.wantedData.Content == "remove_item" then
				ListField(q,"",{},"    ");  
				if q.params.monster ~= nil then
					--ROM_CommandVisitMonster(q.wantedData.MapId,q.params.monster);
					LogDebug("----");
					ListField(q.params,"",{},"    ");  
					local num = BagProxy.Instance:GetAllItemNumByStaticID(q.params.item[1].id);
					LogDebug("num=" .. num);
					if num <  q.params.item[1].num then
						ROM_CommandVisitMonster(q.wantedData.MapId,q.params.monster);
					end;
				else
					if q.wantedData.MapId ~= nil then
						ROM_WalkToNPC(q.staticData.Map,q.wantedData.NpcId,
							function()
								local nearestNPC, nearestDist = ROM_GetNearestNPC();
								--Game.Myself:Client_LockTarget(nearestNPC);
								LogDebug("ROM_DoAutoQuest: remove_item click");
								ServiceQuestProxy.Instance:CallVisitNpcUserCmd(nearestNPC.data.id);
								ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, nil, q.step); 
								GameFacade.Instance:sendNotification(UIEvent.CloseUI,UIViewType.DialogLayer);
								LogDebug(QuestToString(q));
								ROM_ClickNearestNPC(true);
							end
						);
					else
						--LogDebug("Should not be here");
					end                            
				end;
			elseif q.wantedData.Content == "gather" then
				ListField(q,"",{},"    ");  
				if q.params.monster ~= nil then
					-- goto that monster
					ROM_CommandVisitMonster(q.wantedData.MapId,q.params.monster);
				else
					-- goto board to submit quest 
					ROM_WalkToNPC(mapid,q.params.npc);
				end;
			elseif q.wantedData.Content == "visit" then
				ListField(q,"",{},"    ");  
				ROM_WalkToNPC(q.map,q.params.npc,
					function()
						local nearestNPC, nearestDist = ROM_GetNearestNPC();
						--Game.Myself:Client_LockTarget(nearestNPC);
						LogDebug("ROM_DoAutoQuest: visit click");
						ServiceQuestProxy.Instance:CallVisitNpcUserCmd(nearestNPC.data.id);
						ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, nil, q.step); 
						GameFacade.Instance:sendNotification(UIEvent.CloseUI,UIViewType.DialogLayer);
						LogDebug(QuestToString(q));
						--ROM_ClickNearestNPC(true);
						--FunctionVisitNpc.me:AccessTarget(nil, nil, nil);		
					end
				);
			else
				LogDebug("Quest type not suppoted");
			end;
		end;
	else 
		ROM_DumpWantedQuest();
		LogDebug("ROM_DoAutoQuest: No quest to already accept walk to board");
		if ROM_WalkToBoard() then
			-- refresh wanted quest list
			LogDebug("ROM_DoAutoQuest: try refresh())");
			ServiceQuestProxy.Instance:CallQuestList(SceneQuest_pb.EQUESTLIST_CANACCEPT,101);

			-- near board
			
			-- TODO: find a way to click
			--ROM_ClickNearestNPC();
			--Game.Myself:Client_LockTarget(nearestNPC);
			if ROM_SubmitQuest() == false then
                --ROM_ClickNearestNPC();
				LogDebug("Before ROM_AcceptQuest");		
				local nearestNPC, nearestDist = ROM_GetNearestNPC();
				ServiceQuestProxy.Instance:CallVisitNpcUserCmd(nearestNPC.data.id);
				ROM_AcceptQuest();
				--FunctionVisitNpc.me:AccessTarget(nil, nil, nil);
            else
                
			end;
		end;
	end;
	LogDebug("done");

end;


LogDebug("romAutoQuest.lua 1.0");
	