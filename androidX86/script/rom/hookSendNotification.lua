-- hookSendNofication.lua --- 

function HOOK_SendNotification(self,p1,p2)
	if p1 ~= nil then
		if p1 == UIEvent.ShowUI then
			LogDebug("HOOK_SendNotification: " .. tostring(p1));	
			--ListField(p2,"",{}," ");
			if p2 and p2.viewname == "DeathPopView" then
				LogDebug(p2.viewname);
				LogDebug("I am dead");
				ROM_DelayCall(5000,function(param)
					LogDebug("Auto revive start");
					ServiceSceneProxy.Instance:CallReliveUserCmd(1)
					LogDebug("Auto revive end");
				end);
			end;
			--LogDebug(MonsterToString(p2.npcinfo));
		end;
		
		if p1 == UIEvent.CloseUI then
			--LogDebug("HOOK_SendNotification: " .. tostring(p1));	
			--ListField(p2,"",{}," ");
			--LogDebug(MonsterToString(p2.npcinfo));
		end;
		if p1 == UIEvent.JumpPanel then
			--LogDebug("HOOK_SendNotification: " .. tostring(p1));	
			--ListField(p2,"",{}," ");
			--if p2 and p2.viewdata ~= nil then
			--	LogDebug(p2.viewdata);
				--LogDebug("npcTarget=" .. MonsterToString(p2.viewdata.npcTarget));
			--end;
		end;
	end;
	GameFacade.Instance:_sendNotification(p1,p2);
end;

function _HOOK_SendNotification(self,p1,p2)
    if p1 ~= nil then
        if string.match(p1, "ServiceEvent_") then	
        --if p1 == "ServiceEvent_NUserUserNineSyncCmd" then
        else
            LogDebug("HOOK_SendNotification: " .. tostring(p1));
            if p1 == MyselfEvent.BaseExpChange then
                local userData = Game.Myself.data.userdata
                local roleExp = userData:Get(UDEnum.ROLEEXP);
                local nowRoleLevel = userData:Get(UDEnum.ROLELEVEL);
                local referenceValue = Table_BaseLevel[nowRoleLevel+1];
                if(referenceValue == nil)then
                    referenceValue = 1;
                else
                    referenceValue = referenceValue.NeedExp;
                end
                local str = string.format("BaseLv%s Exp=%s/%s",tostring(nowRoleLevel),tostring(roleExp),tostring(referenceValue));  		
                LogDebug(str);
            end;
            
            if p1 == MyselfEvent.JobExpChange then
                local nowJob = Game.Myself.data:GetCurOcc();  --self.myself.userData:Get(UDEnum.JOBLEVEL);
                if nowJob ~= nil then
                    local professionid = MyselfProxy.Instance:GetMyProfession()
                    local nowJobLevel = nowJob:GetLevelText()
                    local userData = Game.Myself.data.userdata
                    local cur_max = userData:Get(UDEnum.CUR_MAXJOB) or 0
                    local previousId = ProfessionProxy.Instance:GetThisIdPreviousId(professionid)
                    if previousId then
                        local previousData = Table_Class[previousId]
                        if previousData.MaxPeak~=nil then
                            cur_max =  cur_max - previousData.MaxPeak
                        elseif 	previousData.MaxJobLevel~=nil then
                            cur_max =  cur_max - previousData.MaxJobLevel
                        end
                    end
                    if cur_max<= 0 then
                        cur_max = 1;
                    end
                    local curlv = ProfessionProxy.Instance:GetThisJobLevelForClient(professionid,MyselfProxy.Instance:JobLevel())
                    local referenceValue = Table_JobLevel[nowJob.level+1];
                    if(referenceValue == nil)then
                        referenceValue = 1;
                    else
                        referenceValue = referenceValue.JobExp;
                    end
                    local str = string.format("JobLv%s Exp=%s/%s",tostring(curlv),tostring(nowJob.exp),tostring(referenceValue));  		
                    LogDebug(str);
                end;
            end;
            
            if p1 == MyselfEvent.MyDataChange then
                -- Game.Myself.data.userdata changed need to refresh display
            end;
            
            if p1 == UIEvent.ShowUI then
                ListField(p2,"",{}," ");
                LogDebug(MonsterToString(p2.npcinfo));
            end;
            
            if p1 == UIEvent.CloseUI then
                ListField(p2,"",{}," ");
                LogDebug(MonsterToString(p2.npcinfo));
            end;
            
            
            if p1 == UIEvent.JumpPanel then
                ListField(p2,"",{},"  ");
                if p2.viewdata ~= nil then
                    LogDebug("npcTarget=" .. MonsterToString(p2.viewdata.npcTarget));
                end;
            end;
            --if(TableUtil.HasValue(MyselfEvent,p1)) then
                
                --LogDebug(MyTostring(p2));
            --	ListField(p2,"",{}," ");
            --end;
            --if(TableUtil.HasValue(ChatRoomEvent,p1)) then
            --	ListField(p2,"",{}," ");
            --end;
        end;
    else
        LogDebug("HOOK_SendNotification: " .. tostring(p1));    
    end;
	GameFacade.Instance:_sendNotification(p1,p2);
end;

if GameFacade and GameFacade.Instance and GameFacade.Instance.sendNotification then
	if GameFacade.Instance._sendNotification == nil then
		-- keep original
		GameFacade.Instance._sendNotification = GameFacade.Instance.sendNotification;
	end;
	if GameFacade.Instance._sendNotification  then
		--GameFacade.Instance.sendNotification = HOOK_SendNotification;
	end;
end;


function HOOK_openWantedQuestPanel( wantedid, target)
    LogDebug("HOOK_openWantedQuestPanel " .. MyTostring(wantedid));
    ListField(target,"",{}," ");
    FunctionVisitNpc.Me()._openWantedQuestPanel(wantedid,target);
end;

function HOOK_AccessTarget(self, target, custom, customType)
    LogDebug("HOOK_AccessTarget ");
	LogDebug("-- target --")
	ListField(target,"",{},"");
	LogDebug("-- custom --")
    ListField(custom,"",{},"");
	LogDebug("-- customType --")
	ListField(customType,"",{},"");
	FunctionVisitNpc.me:_AccessTarget(target, custom, customType);
end;

function ROM_RecvSKIP()
	return true;
	--return false;
end;
function ROM_RecvAddMapItem(data)
	--LogDebug("items=" .. MyTostring(data.items));
	return false;
end;

function ROM_RecvGUIDSkip(data)
	return false;
	--return data.guid ~= Game.Myself.data.id;
end;

function ROM_RecvCHARIDSkip(data)
	return false;
	--return data.charid ~= Game.Myself.data.id;
end;


function ROM_RecvUSERIDSkip(data)
	return false;
--	return data.userid ~= Game.Myself.data.id;
end;

function ROM_RecvPLAYERGUIDSkip(data)
	return false;
--	return data.playerguid ~= Game.Myself.data.id;
end;

function ROM_MapOtherUserOut(data)
	--SceneObjectProxy.RemoveObjs(data.list,data.delay_del,data.fadeout)
	local status,err = pcall(function()
		local ret = "";
		if(data.list ~= nil and #data.list >0) then
			for i = 1, #data.list do
				local id = data.list[i];
				ret = ret .. " " .. ROM_GetCreatureNameFromID(id);
			end
		end
		if data.delay_del ~= nil then
			ret = ret .. " delay_del=" .. tostring(data.delay_del);
		end;
		if data.fadeout ~= nil then
			ret = ret .. " fadeout=" .. tostring(data.fadeout);
		end;
		
		LogDebug("RECV< MapOtherUserOut" .. ret);
		--LogDebug(singleLine(tostring(data)));
	end);
    if status == false then
        LogDebug("ERROR: " .. singleLine(tostring(err)));
        return false
    end;
    return true;
end;

function ROM_UserAttrSyncCmd(data,funcName)
	funcName = funcName or "UserAttrSyncCmd";
    local status,err = pcall(function()
        local ret = "";
        local props = Game.Myself.data.props;
        local creature = Game.Myself;
        if data.guid ~= nil then
            creature = SceneCreatureProxy.FindCreature(data.guid);
			if creature ~= nil then
				props = creature.data.props;
			end;
            --LogDebug(CreatureToString(creature));
        end;
        if creature~= nil then
            ret = ROM_GetCreatureName(creature) .. " ";
		else	
			LogDebug(singleLine(data));
			ret = "CREATURE[" .. (data.guid or "") .. "] ";
        end;
        if data.attrs ~= nil then
            for i = 1, #data.attrs do
                sdata = data.attrs[i];
                if creature~= nil then
                    --ret = ret .. tostring(sdata.type) .. "=" .. tostring(sdata.value) .. " ";
                    ret = ret .. ROM_PropGetName(props,sdata.type) .. "=" .. tostring(sdata.value) .. " ";
                end;
            end
        end;
		if data.pointattrs ~= nil then
            for i = 1, #data.pointattrs do
                sdata = data.pointattrs[i];
                if creature~= nil then
                    --ret = ret .. tostring(sdata.type) .. "=" .. tostring(sdata.value) .. " ";
                    ret = ret .. ROM_PropGetName(props,sdata.type) .. "=" .. tostring(sdata.value) .. " ";
                end;
            end
		end;
        if data.datas ~= nil then
            for i = 1, #data.datas do
                sdata = data.datas[i];
                ret = ret .. ROM_DataGetName(sdata.type) .. "=" .. tostring(sdata.value) .. " ";
            end
        end;
        LogDebug("RECV< " .. funcName .. " " .. ret);
    end);
    if status == false then
        LogDebug("ERROR: " .. singleLine(tostring(err)));
        return false
    end;
    return true;
end;
function ROM_RecvNpcDataSync(data)
	return ROM_UserAttrSyncCmd(data,"NpcDataSync");
end;
function ROM_RecvUserNineSyncCmd(data)
	return ROM_UserAttrSyncCmd(data,"UserNineSyncCmd");
end;

function ROM_RecvDamageNpcUserEvent(data)
    local status,err = pcall(function()
		local id = data.npcguid
		local userid = data.userid
		LogDebug("RECV< RecvDamageNpcUserEvent " .. ROM_GetCreatureNameFromID(userid) .. " HIT " .. ROM_GetCreatureNameFromID(id));
	end);
    if status == false then
        LogDebug("ERROR: " .. singleLine(tostring(err)));
        return false
    end;
    return true;
end;

function ROM_RecvMemberDataUpdate(data)
    local status,err = pcall(function()
        local ret = "";
        local id = data.id;
        local members = data.members;
        local teamMemberData = TeamProxy.Instance.myTeam:GetMemberByGuid(id);
        ret = "id=" .. teamMemberData.id .. " [" .. teamMemberData.name .. ']'
        for i=1,#members do
            local data = members[i];
            local key = TeamMemberData.KeyType[data.type];
            ret = ret .. " " .. key .. "=" .. tostring(data.value) .. " " .. tostring(data.data);
        end
		LogDebug("RECV< ROM_RecvMemberDataUpdate " .. ret);
        --LogDebug(singleLine(tostring(data)));
        
        --LogDebug(singleLine(tostring(teamMemberData)));
	end);
    if status == false then
        LogDebug("ERROR: " .. singleLine(tostring(err)));
        return false
    end;
    return true;
end;
--RecvCDTimeUserCmd list { type: 0 time: 1548925769486 id: 14010 }   
function ROM_RecvCDTimeUserCmd(data)
    local status,err = pcall(function()
        local ret = "";
        for i=1,#data.list do
            local cdData = data.list[i]
            if(cdData.type == SceneUser2_pb.CD_TYPE_SKILL) then
                local sortID = math.floor(cdData.id / 1000)
                local skill = SkillProxy.Instance:GetLearnedSkillBySortID(sortID)
                local skillStaticData = skill and skill.staticData or nil
                --LogDebug(SkillInfoToString(skill));
                ret = ret .. SkillInfoToString(skill) .. " time=" .. cdData.time ;
                if(skillStaticData and skillStaticData.SkillType == SkillType.FakeDead) then
                    --needSendEvent = true
                    --CDProxy.Instance:AddSkillCD(cdData.id,cdData.time,skillStaticData.CD,skillStaticData.CD)
                else
                    --CDProxy.Instance:AddSkillCD(cdData.id,cdData.time)
                    if(skillStaticData and skillStaticData.Logic_Param and skillStaticData.Logic_Param.real_cd) then
                        --needSendEvent = true
                    end
                end
            else
                ret = ret .. cdData.id .. " " .. cdData.time .. " " .. cdData.type;
                --CDProxy.Instance:AddCD(cdData.type,cdData.id,cdData.time)
            end
        end;
        LogDebug("RECV< ROM_RecvCDTimeUserCmd " .. ret);
	end);
    if status == false then
        LogDebug("ERROR: " .. singleLine(tostring(err)));
        return false
    end;
    return true;

end;

function ROM_RecvDonateListGuildCmd(data)
    local status,err = pcall(function()
        local ret = "";
        for i=1,#data.items do
            local item = data.items[i]
            local itemData = Table_Item[item.itemid];
            local num = BagProxy.Instance:GetAllItemNumByStaticID(itemData.id);
            ret = ret .. "\n" ..  PropToString(itemData," ",{"id","NameZh","Type"},{"MediaPath","Desc","TFValidDate","ValidDate","Icon"}) .. " num=" .. num .. " itemCount=" .. item.itemcount .. " configid=" .. item.configid;
            if num > 300 and item.itemcount < 60 then
                LogDebug("Should contribute");
                ServiceGuildCmdProxy.Instance:CallApplyRewardConGuildCmd(item.configid);
                ServiceGuildCmdProxy.Instance:CallDonateGuildCmd(item.configid,item.time);
            end;
        end;
        LogDebug(singleLine(tostring(data)));
        LogDebug("RECV< ROM_RecvDonateListGuildCmd " .. ret);
	end);
    if status == false then
        LogDebug("ERROR: " .. singleLine(tostring(err)));
        return false
    end;
    return true;
end;
function ROM_RecvUpdateWantedQuestTeamCmd(data)
    local status,err = pcall(function()
        local ret = "";
--[[		02/05/19 01:19:25 RECV: RecvUpdateWantedQuestTeamCmd quest { questid: 54670001 charid: 4300736919 questdata { config { Auto: 0 Class: 0 QuestName: Book of Evil Druid SubGroup: 0 Type: wanted FailJump:
 0 TraceInfo: WhetherTrace: 1 FirstClass: 0 Level: 0 RewardGroup: 0 Name: Book of Evil Druid FinishJump: 0 Content: GM Map: 0 params { params { value: 2 key: etype } params { value: effect key: type }
 } } } action: 1 }
 
 02/05/19 01:44:38 quest { questid: 54660001 charid: 4300736919 questdata { config { Auto: 0 Class: 0 QuestName: An Experiment SubGroup: 0 Type: wanted FailJump: 0 TraceInfo: Go to the Mission Board of
 a nearby city to submit quests WhetherTrace: 0 FirstClass: 0 Level: 0 RewardGroup: 0 Name: An Experiment FinishJump: 0 Content: visit Map: 0 params { params { value: 1 key: ifAccessFc } params { valu
e: 1 key: mark_team_wanted } params { value: 1016 key: npc } } } } step: 5 action: 1 }

 02/05/19 01:33:56 RECV: RecvUpdateWantedQuestTeamCmd quest { questid: 54670001 charid: 4300736919 questdata { config { Auto: 0 Class: 0 QuestName: Book of Evil Druid SubGroup: 0 Type: wanted FailJump:
 0 TraceInfo: WhetherTrace: 1 FirstClass: 0 Level: 0 RewardGroup: 0 Name: Book of Evil Druid FinishJump: 0 Content: GM Map: 0 params { params { value: 2 key: etype } params { value: effect key: type }
 } } } action: 2 }
 
 02/05/19 02:21:00 quest { questid: 54550001 charid: 4299674004 questdata { config { Auto: 0 Class: 0 QuestName: Mutated Cramp SubGroup: 0 Type: wanted FailJump: 0 TraceInfo: WhetherTrace: 1 FirstClass
: 0 Level: 0 RewardGroup: 0 Name: Mutated Cramp FinishJump: 0 Content: GM Map: 0 params { params { value: 2 key: etype } params { value: effect key: type } } } } action: 2 }

02/06/19 09:27:38 RECV< ROM_RecvUpdateWantedQuestTeamCmd ACCEPTED step=7 questid=55070001 MY TEAM[4300736919] τÑ₧τºÿτÜäµëïµÄî
02/06/19 09:27:38 quest { step: 7 action: 1 questid: 55070001 charid: 4300736919 questdata { config { Level: 0 RewardGroup: 0 Name: Mystical Palms FinishJump: 0 Content: visit Map: 0 params { params {
 value: 1 key: ifAccessFc } params { value: 1 key: mark_team_wanted } params { value: 1016 key: npc } } Auto: 0 Class: 0 QuestName: Mystical Palms SubGroup: 4 Type: wanted FailJump: 0 TraceInfo: Go to
 the Mission Board of a nearby city to submit quests WhetherTrace: 0 FirstClass: 0 } } }
02/06/19 09:27:39 RECV: RecvMemberPosUpdate id: 4313990901 pos { y: 119 z: 7770 x: -7129 }
02/06/19 09:27:40 RECV< ROM_RecvMemberDataUpdate id=4313990901 [α╕₧α╕▓α╕ùα╣ëα╕¡α╣üα╕ùα╣ë] mapid=47  raid=0  guildraidindex=0

2/06/19 10:25:23 Found quest id=54620001,type=wanted,map=37,step=1,acceptlv=88,traceTitle=ΦíÇµƒôτÜäµòÖσáé,traceInfo=Go to Glast Heim Churchyard to take a picture of the Ruins┬╖Sage's End,process=0,fi
ishcount=4,questDataStepType=selfie,scope=cityScope,orderId=54620001,instanceID=162630,questListType=1,whetherTrace=1,time=1549404000,params.distance=5,params.cameraId=9,params.button=µïìτàº,params.i
emIcon=74,
2/06/19 10:25:23 RECV< ROM_RecvUpdateWantedQuestTeamCmd ACCEPTED step=3 questid=54620001 MY TEAM[4300736919] ΦíÇµƒôτÜäµòÖσáé

02/08/19 09:11:24 quest { questdata { config { RewardGroup: 0 Name: Blue Gem FinishJump: 0 Content: visit Map: 0 params { params { value: 1 key: ifAccessFc } params { value: 1 key: mark_team_wanted }
params { value: 1016 key: npc } } Auto: 0 Class: 0 QuestName: Blue Gem SubGroup: 4 Type: wanted FailJump: 0 TraceInfo: Go to the Mission Board of a nearby city to submit quests WhetherTrace: 0 FirstCl
ass: 0 Level: 0 } } step: 7 action: 1 questid: 55030001 charid: 4300736919 }
02/08/19 09:11:25 RECV: RecvQuestStepUpdate data { config { RewardGroup: 0 Name: Blue Gem FinishJump: 0 Content: visit Map: 43 params { params { items { items { key: 1 value: 88894 } } key: dialog } p
arams { key: npc value: 6507 } params { key: uniqueid value: 6507 } } Auto: 1 Class: 0 QuestName: Blue Gem SubGroup: 4 Type: wanted FailJump: 0 TraceInfo: Give 8 Cyfars to Thelma WhetherTrace: 1 First
Class: 0 Level: 0 } } step: 6 id: 55030001

2/08/19 09:25:31 RECV< ROM_RecvMemberDataUpdate id=4313990901 [α╕₧α╕▓α╕ùα╣ëα╕¡α╣üα╕ùα╣ë] mapid=26  raid=0  guildraidindex=0
2/08/19 09:25:31 Found quest id=55030001,type=wanted,map=43,step=6,finishcount=2,questListType=1,acceptlv=89,traceInfo=Give 8 Cyfars to Thelma,traceTitle=Φô¥Φë▓σ«¥τƒ│,questDataStepType=visit,time=154
576800,whetherTrace=1,process=0,scope=cityScope,instanceID=35250,orderId=55030001,params.npc=6507,params.uniqueid=6507,
2/08/19 09:25:31 SEND: SceneQuest_pb.VisitNpcUserCmd npctempid: 2147485661
2/08/19 09:25:31 SEND: SceneQuest_pb.RunQuestStep questid: 55030001 step: 6
 
 ]]
		if data.quest.action == 1 then 
			local shouldAccept = false
			if data.quest.step then
				ret = ret .. "ACCEPTED step=" .. data.quest.step;
				if data.quest.step == 0 then
					shouldAccept = true;
                else
                    -- check if we can update step also
                    local q = ROM_GetAcceptedQuest();
                    if q and q.id == data.quest.questid then
                        LogDebug("Found quest " .. QuestToString(q));
                        if q.questDataStepType == "visit" then
                            ROM_VisitNearestNPC(q.params.npc);
                            ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, nil, q.step); 
                            ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, nil, 6); 
                             ROM_DelayCall(3000,
                                function(param) 
                                    LogDebug("ROM_RecvUpdateWantedQuestTeamCmd auto close UI");
                                    GameFacade.Instance:sendNotification(UIEvent.CloseUI,UIViewType.DialogLayer);                                    
                                end,
                            nil);
                        end;
                        if q.questDataStepType == "selfie" then
                            ServiceNUserProxy.Instance:CallStateChange(ProtoCommon_pb.ECREATURESTATUS_SELF_PHOTO);
                            ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, 0, q.step); 
                            ServiceNUserProxy.Instance:CallStateChange(0);
                        end;
                    end;
				end;
			else
				ret = ret .. "ACCEPT";
				shouldAccept = true;
			end;
			if shouldAccept then
				ROM_VisitNearestNPC(1016);
				ServiceQuestProxy.Instance:CallQuestAction(SceneQuest_pb.EQUESTACTION_ACCEPT,data.quest.questid);
                ROM_DelayCall(3000,
                    function(param) 
                        LogDebug("ROM_RecvUpdateWantedQuestTeamCmd auto close UI");
                        ROM_CloseAllModal();
                        --[[tableForEach(UIManagerProxy.Instance.modalLayer, function(_, layerType)
                            logDebug(tostring(layerType));
                            GameFacade.Instance:sendNotification(UIEvent.CloseUI,layerType);    
                        end);]]
                    end,
                nil);                
			end;
			
		elseif 	data.quest.action == 2 then 
			ret = ret .. "SUBMIT";
			local q = ROM_GetSubmitableQuest();
			if q then
				LogDebug(QuestToString(q))
				if q.id == data.quest.questid then
					ROM_VisitNearestNPC(1016);
					ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, nil, q.step); 				
					ServiceQuestProxy.Instance:CallRunQuestStep(q.id, nil, 0, q.step); 				
					--ServiceQuestProxy.Instance:CallQuestList(SceneQuest_pb.EQUESTLIST_CANACCEPT,101);
					ServiceQuestProxy.Instance:CallQuestAction(SceneQuest_pb.EQUESTACTION_SUBMIT,q.id);
                    ROM_DelayCall(3000,
                        function(param) 
                            LogDebug("ROM_RecvUpdateWantedQuestTeamCmd auto close UI");
                            tableForEach(UIManagerProxy.Instance.modalLayer, function(_, layerType)
                                logDebug(tostring(layerType));
                                GameFacade.Instance:sendNotification(UIEvent.CloseUI,layerType);    
                            end);
                        end,
                    nil);                
				end;
			end;
			--ROM_DoAutoQuest();
			-- check if we can auto submit
		else
			ret = ret .. "ACTION" .. data.quest.action;
		end;
		
		ret = ret .. " questid=" .. data.quest.questid .. " " .. ROM_GetCreatureNameFromID(data.quest.charid) .. " " .. data.quest.questdata.config.QuestName;
        LogDebug("RECV< ROM_RecvUpdateWantedQuestTeamCmd " .. ret);
		LogDebug(singleLine(tostring(data)));
	end);
    if status == false then
        LogDebug("ERROR: " .. singleLine(tostring(err)));
        return false
    end;
    return true;
end;

function ROM_RecvQueryShopConfigCmd(data)
    local status,err = pcall(function()
        LogDebug("RECV< ROM_RecvQueryShopConfigCmd " .. singleLine(tostring(data)));
        ROM_Alert("ROM_RecvQueryShopConfigCmd");
	end);
    if status == false then
        LogDebug("ERROR: " .. singleLine(tostring(err)));
        return false
    end;
    return true;
end;

ROM_DoFile("/data/local/tmp/script/romPackets.lua");

function ROM_GetPacket(tab,id1,id2)
    for i=1,#tab do
        local pkt = tab[i];
        if id1 == pkt[1] and id2 == pkt[2] then
            return pkt;
        end;
    end;
    return nil;
end;

function HOOK_SendProto(data)
	local id1 = data.cmd;
	local id2 = data.param;
    --LogDebug("SEND: " .. tostring(data));
    local pkt = ROM_GetPacket(ROM_SendPackets,id1,id2);
    if pkt then
        LogDebug("SEND: " .. pkt[3] .. " " .. singleLine(data));
    else
        LogDebug("SEND: [" .. id1 .. '] [' .. id2 .. '] ' .. singleLine(data));
    end;
    NetProtocol._SendProto(data);
end;

function HOOK_Send(id1, id2, data)
    local pkt = ROM_GetPacket(ROM_SendPackets,id1,id2);
    if pkt then
        LogDebug("SEND: " .. pkt[3] .. " " .. singleLine(data));
    else
        LogDebug("SEND: [" .. id1 .. '] [' .. id2 .. '] ' .. singleLine(data));
    end;
    NetProtocol._Send(data);
end;


function ROM_HandleRecv(id1, id2, data)
	for i=1,#ROM_Packets do
		local pkt = ROM_Packets[i];
		if id1 == pkt[1] and id2 == pkt[2] then
			if pkt[4] ~= nil and pkt[4](data) then
				-- do nothing
			else
				LogDebug("RECV: " .. pkt[3] .. " " .. singleLine(data));
			end;
			return;
		end;
	end;
	LogDebug("RECV: [" .. id1 .. '] [' .. id2 .. ']\n' .. singleLine(data));
end;

function HOOK_NetProtocol_DispatchListener(id1, id2, data)
	if id1 == 5 and id2 == 16 then
		if data.charid == Game.Myself.data.id then
			LogDebug("RECV: MoveTo (ME) [" .. tostring(data.pos.x) .. "," .. tostring(data.pos.y) .. ',' .. tostring(data.pos.z) .. "]");
		else
			--LogDebug("RECV: MoveTo " .. tostring(data.charid) .. " " .. tostring(data.pos));
		end;
	else
		ROM_HandleRecv(id1,id2,data);
		--LogDebug("RECV: [" .. id1 .. '] [' .. id2 .. '] ' .. tostring(data));
	end;
	NetProtocol._DispatchListener(id1, id2, data);
end;

if CommonFun ~= nil then
	function CommonFun.StealMoney(srcUser, targetUser)
	  LogDebug("CommonFun.StealMoney");	
	  local skilllv_1 = srcUser:GetLernedSkillLevel(474) ---偷钱
	  local skilllv_2 = srcUser:GetLernedSkillLevel(473) ---强夺
	  local Dex = srcUser:GetProperty("Dex")
	  local Luk = srcUser:GetProperty("Luk")
	  local Rate = math.min(20,(Dex + Luk)/10)  ----D,L影响成功率
	  local RateSum = Rate + 5

	  local A = skilllv_1*0.05 +  skilllv_2*0.02

	  if  CommonFun.IsInRate(RateSum, srcUser:GetRandom())  then
			return  A
	  end 

	  return 0
	end
	
	function CommonFun.IsInRate(rate, random)
	  if rate == nil or random == nil then
		LogDebug("IsInRate false");	
		return false
	  end
	  LogDebug("IsInRate " .. rate .. " " .. random);	
	  return rate > random
	end
	
	function CommonFun.IsMiss(srcUser, targetUser, skillParams)
		-- 必定命中且暴击
		local AttrEffect = srcUser:GetProperty("AttrEffect")
		local StateEffect2 = targetUser:GetProperty("StateEffect")
		local bits=CommonFun.getBits(AttrEffect)
		local bits2=CommonFun.getBits(StateEffect2)
	  
		--------------------------------------------------------------------------------------------------------并定名中且暴击，或者睡眠情况下 是不会闪避的
		if bits[CommonFun.AttrEffect.MustHitAndCri] == 1 or bits2[CommonFun.StateEffect.Sleep]==1 then
		  return false
		end

		-- 1----------------------------------------------------------------------------------------------------判断自己对敌方的命中是否成立，不成立则返回闪避
		local hitRate = CommonFun.CalcHitRate(srcUser, targetUser, skillParams)
			local index = Game.Myself.data.randomFunc.index
			if CommonFun.IsInRate(hitRate, srcUser:GetRandom()) == false then
				LogDebug("IsMiss true " .. hitRate .. ' ' .. index)		
			   return true
			end
			LogDebug("IsMiss false " .. hitRate .. ' ' .. index)				
		-- 2----------------------------------------------------------------------------------------------------判断自己对敌方的闪避是否成立，成立则返回闪避
		--local fleeRate = CommonFun.CalcFleeRate(srcUser, targetUser, skillParams)
		--local random = srcUser:GetRandom()
		--if CommonFun.IsInRate(fleeRate, random) then
		  --return true
		--end

		return false
	end
	

	function CommonFun.IsCrit(srcUser, targetUser, skillParams)
		-- 必定命中且暴击
		local AttrEffect = srcUser:GetProperty("AttrEffect")
		local AttrEffect2 = targetUser:GetProperty("AttrEffect")
		local StateEffect2 = targetUser:GetProperty("StateEffect")
		local bits=CommonFun.getBits(AttrEffect)
		local bits1=CommonFun.getBits(AttrEffect2)
		local bits2=CommonFun.getBits(StateEffect2)
		local skillID = skillParams.id
		if math.floor(skillID/1000)== 91001 then-----------------------波利乱斗技能撞击判断不会暴击
		  return false
		end

		-----------------------------------------------------------------------------------------------------并定名中且暴击属性和睡眠属性都会导致必定被暴击
		if bits[CommonFun.AttrEffect.MustHitAndCri] == 1 or bits2[CommonFun.StateEffect.Sleep]==1 then
		  return true
		end
		-----------------------------------------------------------------------------------------------------必定无法被暴击属性导致不会受到暴击
		if bits1[CommonFun.AttrEffect.MustNotCri] == 1 then
		   return false
		end   

		local critRate = CommonFun.CalcCritRate(srcUser, targetUser, skillParams)
		
		-----------------------------------------------------------------------------------------------------判断自己对敌方暴击是否成立，成立返回暴击值
		if CommonFun.IsInRate(critRate, srcUser:GetRandom()) then
		  LogDebug("IsCrit true " .. critRate)		
		  return true
		end
		LogDebug("IsCrit false " .. critRate)		
		return false
	end


	function CommonFun.CalcDamage(srcUser, targetUser, params, logger)
	  -- 基础伤害计算
      local indexBefore = Game.Myself.data.randomFunc.index;
	  local damage, damagetype = CommonFun.CalcBaseDamage(srcUser, targetUser, params, logger)
	  local sharedam = nil
	  LogDebug("CalcDamage " .. damage .. ' ' .. tostring(damagetype) .. ' before='  .. indexBefore .. ' after=' .. Game.Myself.data.randomFunc.index);
      --ListField(srcUser.randomFunc,"",{}," ");
	  --damage = 0;
	  -- 承担伤害计算
	  if damage > 0 then
		if targetUser.isServerCall then -- 服务端调用
			LogDebug("server");
		  if targetUser.have_sharedam_server ~= nil and targetUser.have_sharedam_server == true then
			damage, sharedam, damagetype = CommonFun.CalcShareDamage(srcUser, targetUser, damage, damagetype)
		  end
		else -- 客户端调用
		  damage, sharedam, damagetype = CommonFun.CalcShareDamage(srcUser, targetUser, damage, damagetype)
		end
	  end

	  return damage, damagetype, sharedam
	end
	function CommonFun.CalcBaseDamage(srcUser, targetUser, params, logger)

    -- 参数检查
    if nil == srcUser then
        logger.error(string.format("srcUser is nil"))
        return 0, CommonFun.DamageType.None
    end
    if nil == targetUser then
        logger.error(string.format("targetUser is nil"))
        return 0, CommonFun.DamageType.None
    end

    if nil == Table_Skill then
        logger.error("Table_Skill is nil")
        return 0, CommonFun.DamageType.None
    end

    local skillParams = Table_Skill[params.skillIDAndLevel]
    if nil == skillParams then
        logger.error(string.format("Table_Skill[%d] is nil", params.skillIDAndLevel))
        return 0, CommonFun.DamageType.None
    end

    local paramList = skillParams.Damage
    if nil == paramList or 0 >= #paramList then
        return 0, CommonFun.DamageType.None
    end

    local mapid,maptype = srcUser:GetMapInfo()-----------------获取所在地图
    local AttrFunction = srcUser:GetProperty("AttrFunction")
    local bitfunc = CommonFun.getBits(AttrFunction)
    if (targetUser.boss or targetUser.mini or targetUser.changelinepunish) and targetUser.zoneType == 1  then
      if bitfunc[CommonFun.AttrFunction.JustInViceZone] == 1 then
        return 0, CommonFun.DamageType.Miss
      end
    end
     

    --  普攻和物理类技能 考虑命中
    --  or params.skillIDAndLevel == srcUser:GetAttackSkillIDAndLevel()
    --  只有物理类技能才会考虑命中
    local  iscrit = CommonFun.IsCrit(srcUser, targetUser, skillParams)
    local  isNormal = srcUser:GetAttackSkillIDAndLevel()---------------------------判断普通攻击

    if CommonFun.RollType.Attack == skillParams.RollType  then  --------------物理类型攻击
      if isNormal == params.skillIDAndLevel then         ---------------------普攻
        if  iscrit == false and CommonFun.IsMiss(srcUser, targetUser, skillParams) == true then
            return 0, CommonFun.DamageType.Miss
        end
      elseif isNormal ~= params.skillIDAndLevel then  ------------技能
        if CommonFun.IsMiss(srcUser, targetUser, skillParams) == true then
            return 0, CommonFun.DamageType.Miss
        end
      end
    end

    local skillID, skillLevel = CommonFun.UnmergeSkillID(params.skillIDAndLevel)
    local enemy = srcUser:IsEnemy(targetUser)
    local DefAttr2=targetUser:GetProperty("DefAttr")
    local AttrEffect2 = targetUser:GetProperty("AttrEffect")
    local bits2=CommonFun.getBits(AttrEffect2)
    local AttrEffect3 = targetUser:GetProperty("AttrEffect2")
    local bits3=CommonFun.getBits(AttrEffect3)

    if enemy then
      -- 免疫某些技能id
      if targetUser:IsImmuneSkill(skillID) then
        return 0, CommonFun.DamageType.Miss
      end

      -- 特殊技能伤害计算(ex. 转生术概率必杀不死系)
      
      if skillID == 160 and DefAttr2 == CommonFun.Nature.Undead and targetUser.boss == false and targetUser.mini == false and targetUser:GetNpcID() ~= 18143 and targetUser:GetNpcID() ~= 18144 and targetUser:GetNpcID() ~= 18145 then
        local Luk=srcUser:GetProperty("Luk")
        local Int=srcUser:GetProperty("Int")
        local BaseLv = srcUser.BaseLv
        local Hp=targetUser:GetProperty("Hp")
        local MaxHp=targetUser:GetProperty("MaxHp")
        local rate = ((20*skillLevel+Luk+Int+BaseLv+(1-Hp/MaxHp)*200)/10)
        ---------------------------------------------------------------------------------------------------星盘加成获得没有一击必杀不死属性怪时的回复量

        if rate >=70 then
            rate=70
        end   
        local beforeIndex = Game.Myself.data.randomFunc.index;
        local randValue =  srcUser:GetRandom();
		LogDebug("rate=" .. rate .. ' randValue=' .. randValue .. ' beforeIndex=' .. beforeIndex);		
		--while randValue > rate do
        --    beforeIndex = Game.Myself.data.randomFunc.index;
		--	randValue =  srcUser:GetRandom();
		--	LogDebug("rate=" .. rate .. ' randValue=' .. randValue .. ' beforeIndex=' .. beforeIndex);
		--end;
        --Game.Myself.data.randomFunc.index = beforeIndex;
		
        if CommonFun.IsInRate(rate, randValue) then
			LogDebug("HIT");
            return targetUser:GetProperty("MaxHp"), CommonFun.DamageType.Normal   
        end
      end

      -- 无视魔法伤害的判定
      if bits2[CommonFun.AttrEffect.NoMagicDamage]==1 and CommonFun.RollType.Magic == skillParams.RollType then
        return 0, CommonFun.DamageType.Miss
      end

      -- 无视物理伤害的判定
      if bits2[CommonFun.AttrEffect.NoPhysicalDamage]==1 and CommonFun.RollType.Attack == skillParams.RollType then
        return 0, CommonFun.DamageType.Miss
      end

      -- 魔法伤害变为1点
      if bits3[CommonFun.AttrEffect2.MDamageTo1]==1 and CommonFun.RollType.Magic == skillParams.RollType then
        return 1, CommonFun.DamageType.Normal
      end

      -- 物理伤害变为1点
      if bits3[CommonFun.AttrEffect2.DamageTo1]==1 and CommonFun.RollType.Attack == skillParams.RollType then
        return 1, CommonFun.DamageType.Normal
      end

      -- 无视近战普攻的判定
      if bits2[CommonFun.AttrEffect.IgnoreNearNormalSkill]==1 and nil ~= skillParams.Launch_Type and CommonFun.LaunchType.CloseAttack == skillParams.Launch_Type then
          return 0, CommonFun.DamageType.Miss
      end

      -- 无视近战物理的判定(暗之屏障)
      if bits2[CommonFun.AttrEffect.IgnoreNearPhysicalSkill]==1 and skillParams.Launch_Range ~= nil and CommonFun.IsLongSkill(skillParams.Launch_Range) == false and skillParams.RollType==1 and skillID~=319 then
        return 0, CommonFun.DamageType.Barrier
      end

      -- 无视远战物理的判定(光之壁障)
      if bits2[CommonFun.AttrEffect.IgnoreFarSkill]==1 and skillParams.Launch_Range ~= nil and CommonFun.IsLongSkill(skillParams.Launch_Range) == true and skillParams.RollType==1 then
        return 0, CommonFun.DamageType.Barrier
      end
      -- 闪避魔法伤害
      if CommonFun.RollType.Magic == skillParams.RollType and targetUser:HasBuffID(32980) then    ------魔法伤害
            local Flee = targetUser:GetProperty("Flee")
            local Rate = 5 + math.min(Flee/50,15)
            if CommonFun.IsInRate(Rate, srcUser:GetRandom()) then
                return 0,CommonFun.DamageType.Miss
            end
      end
      -- 免疫所有伤害的判定 (ex:双剑格挡)
      local HarmImmune = targetUser:GetProperty("HarmImmune")
      if nil ~= HarmImmune and 0 < HarmImmune then
          local harmImmuneInfo = Table_BuffStateOdds[HarmImmune]
          -----------------------------------------------------------------双剑格挡 概率在pvp地图里受双方的敏捷和灵巧影响(阿修罗霸皇拳不会受到双剑格挡的效果)
          if nil ~= harmImmuneInfo then
              local rate = harmImmuneInfo.Odds*100
                       if params.pvpMap then
                             local Dex=srcUser:GetProperty("Dex")
                             local Agi=targetUser:GetProperty("Agi")
                             local rate1 = math.min(Dex *0.1-Agi*0.1,20)
                             if rate1 < 0 then
                                  rate1 = 0
                             end
                             rate = rate - rate1
                             if rate < 0 then 
                                rate = 0
                             end 
                       end
              if CommonFun.IsInRate(rate, srcUser:GetRandom()) and math.floor(params.skillIDAndLevel/1000) ~= 306 and math.floor(params.skillIDAndLevel/1000) ~=422 and math.floor(params.skillIDAndLevel/1000) ~=1122 then
                  return 0, CommonFun.DamageType.Block
              end
          end
      end
      -- 自动防御 免疫物理伤害判定(阿修罗霸皇拳,强酸攻击等 会导致自动防御无效)
      if bits3[CommonFun.AttrEffect2.AutoDef]==1 then
        local skilllv_1 = targetUser:GetLernedSkillLevel(356)
        local rate = skilllv_1*4 + 10
              if CommonFun.IsInRate(rate, srcUser:GetRandom()) and math.floor(params.skillIDAndLevel/1000) ~= 306 and math.floor(params.skillIDAndLevel/1000) ~=411 and math.floor(params.skillIDAndLevel/1000) ~=422 and math.floor(params.skillIDAndLevel/1000) ~=1122 then
                      local skilllv_weiw = targetUser:GetLernedSkillLevel(1190)----获取对方 威望 等级
                      if skilllv_weiw > 0 then
                          ------------------------------只服务端调用
                          if srcUser.isServerCall then
                              targetUser:AddBuff(116700, srcUser:GetGuid()) 
                          end
                      end
                  return 0, CommonFun.DamageType.AutoBlock
              end
      end
      --武器格挡  免疫近战物理伤害
      if bits3[CommonFun.AttrEffect2.WeaponBlock]==1 then
          local skilllv_1 = targetUser:GetLernedSkillLevel(1107)
          local rate = skilllv_1*7
          if CommonFun.IsInRate(rate, srcUser:GetRandom()) and skillParams.Launch_Range ~= nil and CommonFun.IsLongSkill(skillParams.Launch_Range) == false and skillParams.RollType==1 and math.floor(params.skillIDAndLevel/1000) ~= 306 then
                      local RuneNum = targetUser:GetRunePoint(34030)----获取对方 星盘 反击斩 点数
                      if RuneNum > 0 then
                          ------------------------------只服务端调用
                          if srcUser.isServerCall and CommonFun.IsInRate(RuneNum*15, srcUser:GetRandom()) then
                              targetUser:AddBuff(116041, srcUser:GetGuid()) 
                          end
                      end
              return 0, CommonFun.DamageType.WeaponBlock
          end
      end
      -- 飞行特性怪物免疫特定技能
      if targetUser:IsFly() then
          if CommonFun.TableHasValue(NpcFeatures.Flight.ImmuneSkill, skillID) then
              return 0, CommonFun.DamageType.Miss
          end
      end
    end

    local damageType = CommonFun.DamageType.Normal
    local damage, forceDamageType = CommonFun.DoCalcDamage(srcUser, targetUser, params, logger)

    if nil ~= forceDamageType then
        damageType = forceDamageType
        if CommonFun.DamageType.None == damageType
            or CommonFun.DamageType.Miss == damageType
            or CommonFun.DamageType.Block == damageType then
            return damage,damageType
        end
    else
        if 0 == damage then
            return 0, CommonFun.DamageType.Miss
        elseif 0 > damage then
            damageType = CommonFun.DamageType.Treatment
        end
    end

    -- buff begin

    -- change skill begin
    -- local skillIDAndLevel_0 = CommonFun.MergeSkillID(skillID, 0)
    -- local buffParams = srcUser:SelfBuffChangeSkill(skillIDAndLevel_0)
    -- if nil ~= buffParams then
    --    damage = damage * (buffParams.damChangePer or 1) + (buffParams.damChange or 0)
    -- end
    -- change skill end

    -- buff end

    -- random begin
    if CommonFun.DamageType.Normal == damageType
        or CommonFun.DamageType.Crit == damageType or CommonFun.DamageType.ErLianJi == damageType then

        local profressionID = srcUser:GetProfressionID()
        if 0 < profressionID then
            local randomRange = Table_Class[profressionID].DamRandom
            if nil ~= randomRange then
                damage = damage * CommonFun.RandomRange(randomRange[1], randomRange[2], srcUser:GetRandom())
            end
        end
    end

    -- 暴击判断, (特殊:二刀连击触发时暴击不生效)
    if damageType == nil or damageType == CommonFun.DamageType.Normal or damageType == CommonFun.DamageType.Crit then
      if CommonFun.RollType.Attack == skillParams.RollType then
          local attackSkillIDAndLevel = srcUser:GetAttackSkillIDAndLevel()
          if attackSkillIDAndLevel == params.skillIDAndLevel and iscrit then
              damageType = CommonFun.DamageType.Crit
              -------------------------------------------------------------------------------------------判断暴击时无视防御
              local damageParam   = skillParams.Damage
              if damageparam ~= nil and damageParam[1] ~= nil then
                 damageParam = damageParam[1]
              end  
              local raceparam     = CommonFun.CalcRaceParam(srcUser, targetUser, params, damageParam, logger)
              local bodyparam     = CommonFun.CalcBodyParam(srcUser, targetUser, params, damageParam, logger)
              local elementparam  = CommonFun.CalcElementParam(srcUser, targetUser, params, damageParam, logger)
              local bossparam     = CommonFun.CalcBossParam(srcUser, targetUser, params, damageParam, logger)

                ----------------------------------------------------------------------------------------------------------------种族，体型，属性，BOSS减伤效果
              local raceparam2    = CommonFun.CalcRaceParam2(srcUser, targetUser, params, damageParam, logger)
              local bodyparam2    = CommonFun.CalcBodyParam2(srcUser, targetUser, params, damageParam, logger)
              local elementparam2 = CommonFun.CalcElementParam2(srcUser, targetUser, params, damageParam, logger)
              local bossparam2    = CommonFun.CalcBossParam2(srcUser, targetUser, params, damageParam, logger) 


              local Str1 = srcUser:GetProperty("Str")
              --------------------------------------------------------------------------------------------------------商人,牧师,炼金星盘加成的力量转换的普攻加成率提升百分比
              local Num1 = srcUser:GetRunePoint(62080)
              local Num2 = srcUser:GetRunePoint(51013)
              local Num3 = srcUser:GetRunePoint(120010)
              local Numlianj = srcUser:GetRunePoint(130110)
              local RuneDamage = Num1*0.01 + Num2*0.05 + Num3*0.05 + Numlianj*0.03 + 1
              local Str = Str1*RuneDamage
              ---------------------------------------
              local Dex = srcUser:GetProperty("Dex")
              local Luk = srcUser:GetProperty("Luk")
              local Int = srcUser:GetProperty("Int")
              local Agi = srcUser:GetProperty("Agi")
              local DamIncrease = srcUser:GetProperty("DamIncrease")
              local MDamIncrease = CommonFun.calcMDamIncrease(srcUser, targetUser)
              

              local race2 = targetUser.race
              local DefAttr2=targetUser:GetProperty("DefAttr")
              local skillLevel = srcUser:GetLernedSkillLevel(29)
              
              local skillLevel2 = 0
              if race2==3 or DefAttr2==9 then
                 skillLevel2=srcUser:GetLernedSkillLevel(234)
                 if skillLevel2>10 then
                    skillLevel2=10
                 end
              end   
              ----------------------------------------灵气剑
              local SkillRealDamage=0
              if skillLevel<=5 then
                  SkillRealDamage=skillLevel*20
              elseif skillLevel>5 and skillLevel<=10 then
                  SkillRealDamage=100+math.floor(Agi/5)*((skillLevel-5)*0.5+0.5)
              else 
                  SkillRealDamage=100+(skillLevel-10)*20+math.floor(Agi/5)*3+Luk*2
              end
              ---print(skillLevel)
              ---print(SkillRealDamage)

              local BaseAtk  = 0
              local BaseMAtk = Int*2 + math.floor(Int*Int/100)
              local BaseAtk1 = Str1*2 + math.floor(Str1*Str1/100) + math.floor(Dex/5) + math.floor(Luk/5)
              local BaseAtk2 = Dex*2 + math.floor(Dex*Dex/100) + math.floor(Str/5) + math.floor(Luk/5)
              local BaseAtk3 = Str*2 + math.floor(Str*Str/100) + math.floor(Dex/5) + math.floor(Luk/5)  

              local NoramlAtkAdd = 5*Str
              ------------------------------------------------------------------------------------------基础攻击力  Dex Str 远程判断
              local profressionID = srcUser:GetProfressionID()
              local WeaponType =srcUser:GetEquipedWeaponType()
              if (profressionID==92 or profressionID==93 or profressionID==94) and WeaponType==210 then
                  BaseAtk1=BaseAtk2
                  BaseAtk3=BaseAtk2
                  NoramlAtkAdd = 3*Dex
              end

              for k,v in pairs(GameConfig.Atkcalculate) do
                if(v == profressionID) then
                  BaseAtk1=BaseAtk2
                  BaseAtk3=BaseAtk2
                  NoramlAtkAdd = 3*Dex
                end
              end
              -------------------------------------------------------------------------------------------------------星盘加成的牧师普攻会受到魔法攻击影响
              local Num4 = srcUser:GetRunePoint(52013)
              local Num5 = srcUser:GetRunePoint(52014)
              local Num6 = srcUser:GetRunePoint(52015)
              local Num7 = srcUser:GetRunePoint(52016)
              local Num8 = srcUser:GetRunePoint(52017)
              local Num9 = srcUser:GetRunePoint(52018)
              local RuneDamage1 = (Num4 + Num5 + Num6 + Num7 + Num8 + Num9)*0.07
              local Atk1 = srcUser:GetProperty("Atk")
              local MAtk = srcUser:GetProperty("MAtk")
              local MAtkPer = srcUser:GetProperty("MAtkPer")
              local MonkAtk = 0
              --------------------------------------------武僧爆气
              if srcUser:HasBuffID(100510) then
                  MonkAtk = 5*Int
              end
              ---------------------------剑速增加
              local AtkSpdAdd = 0
              local skilllv_SpdAdd = srcUser:GetLernedSkillLevel(22)
              if srcUser:HasBuffID(80082) and skilllv_SpdAdd>10 then
                    AtkSpdAdd = (skilllv_SpdAdd-10)*120
              end

              ----------------------------------------------------------------------------------------------------------------元素箭额外增加物理伤害      
              local skilllv_element = srcUser:GetLernedSkillLevel(127)
              local atk_element = 0
              if skilllv_element >10 then
                atk_element = Dex * ((skilllv_element-10) * 0.5)
              end
              -------------------------------------------------------普攻攻击力
              local NormalAtk = srcUser:GetProperty("NormalAtk")
                    NormalAtk = NormalAtk + NoramlAtkAdd
              local Atk  = Atk1 + RuneDamage1*MAtk*(1+MAtkPer) + MonkAtk + AtkSpdAdd + atk_element + NormalAtk
              ----------------------------------------------------------------------------------------------------------------------------普攻-强效
              local Num10 = srcUser:GetRunePoint(11022)
              local Num11 = srcUser:GetRunePoint(11023)
              local Num12 = srcUser:GetRunePoint(11024)
              local Num13 = srcUser:GetRunePoint(12004)
              local Num14 = srcUser:GetRunePoint(12011)
              local Num16 = srcUser:GetRunePoint(70010)
              local RuneDamage2 = (Num10 + Num11 + Num12 + Num13 + Num14 + Num16)*0.03
              
              local Num15 = srcUser:GetRunePoint(120020)
              local RuneDamage3 = Num15*0.03
              local AtkPer1 = srcUser:GetProperty("AtkPer")
              local AtkPer  = AtkPer1 + RuneDamage2 + RuneDamage3
              ------------------------------------------------------------------------------------------------------------------------------分割线
              local MAtkPer = srcUser:GetProperty("MAtkPer")
              local Refine = srcUser:GetProperty("Refine")
              local MRefine = srcUser:GetProperty("MRefine")

              local Vit2 = targetUser:GetProperty("Vit")
              local VitPer2 = targetUser:GetProperty("VitPer")
              local DamReduc2 = CommonFun.calcDamReDuc(srcUser, targetUser)--------------------------------------------------------------------------替换成穿刺函数
              local RefineDamReduc = targetUser:GetProperty("RefineDamReduc")

              local RealDamage = targetUser:GetProperty("RealDamage")
              ---------------------------------------------------------------------神之威压不受天怒影响
              if targetUser:HasBuffID(96050) and RealDamage>=1 then
                     local skillID, skillLevel = CommonFun.UnmergeSkillID(params.skillIDAndLevel)
                      if skillID==359 then
                      RealDamage=RealDamage-1
                      end 
              end
              local AttrEffect = srcUser:GetProperty("AttrEffect")
              local bits=CommonFun.getBits(AttrEffect)
              local AttrEffect2 = targetUser:GetProperty("AttrEffect")
              local bits2=CommonFun.getBits(AttrEffect2)

              local StateEffect = targetUser:GetProperty("StateEffect")
              local bits3=CommonFun.getBits(StateEffect)
              local Weapon=srcUser:GetEquipedID(7)

              
              if skillParams.RollType==1  then
                  if bits[CommonFun.AttrEffect.NextAttackIncrease]==1 then
                     damage = (((Atk-BaseAtk1)*(1+AtkPer)*CommonFun.ShapeCorrection(srcUser,targetUser)*bodyparam*elementparam*bodyparam2*elementparam2+BaseAtk3)*raceparam*bossparam*raceparam2*bossparam2*(1-DamReduc2) + Refine+SkillRealDamage - Vit2*(1+VitPer2) )*CommonFun.CalcCrit(srcUser, targetUser, skillParams)*(1-RefineDamReduc)*(1+DamIncrease)*2*(1+RealDamage)*(1+skillLevel2*0.05)
                     if damage<=0 then
                        damage = 0
                     end 
                  elseif  bits2[CommonFun.AttrEffect.NormalSkillDam]==1 and (profressionID == 42 or profressionID == 43 or profressionID==44)  then
                       local targetid = targetUser:GetGuid()
                       local distance = srcUser:GetDistance(targetid)
                       local skilllv_1 = srcUser:GetLernedSkillLevel(133)
                       local DisDam= 1
                       if skilllv_1>10 then 
                          DisDam = 1 + distance/7.5*(skilllv_1-10)*0.06
                       end
                     damage = (((Atk-BaseAtk1)*(1+AtkPer)*CommonFun.ShapeCorrection(srcUser,targetUser)*bodyparam*elementparam*bodyparam2*elementparam2+BaseAtk3)*raceparam*bossparam*raceparam2*bossparam2*(1-DamReduc2) + Refine+SkillRealDamage - Vit2*(1+VitPer2) )*CommonFun.CalcCrit(srcUser, targetUser, skillParams)*(1-RefineDamReduc)*(1+DamIncrease)*1.3*(1+RealDamage)*(1+skillLevel2*0.05)*DisDam
                     if damage<=0 then
                        damage = 0
                     end                   
                  elseif bits3[CommonFun.StateEffect.Dizzy]==1 and (Weapon == 40322 or Weapon == 140322) then
                     damage = (((Atk-BaseAtk1)*(1+AtkPer)*CommonFun.ShapeCorrection(srcUser,targetUser)*bodyparam*elementparam*bodyparam2*elementparam2+BaseAtk3)*raceparam*bossparam*raceparam2*bossparam2*(1-DamReduc2) + Refine+SkillRealDamage - Vit2*(1+VitPer2) )*CommonFun.CalcCrit(srcUser, targetUser, skillParams)*(1-RefineDamReduc)*(1+DamIncrease)*(1+RealDamage)*(1+skillLevel2*0.05)*1.5
                     if damage<=0 then
                        damage = 0
                     end
                  elseif skillID == 300 or skillID == 469 then
                       local targetid = targetUser:GetGuid()
                       local distance = srcUser:GetDistance(targetid)
                       local skilllv_1 = srcUser:GetLernedSkillLevel(133)
                       local skilllv_2 = srcUser:GetLernedSkillLevel(478)
                       local DisDam= 1
                       if skilllv_1>10 then 
                          DisDam = 1 + distance/7.5*(skilllv_1-10)*0.06
                       elseif skilllv_2>10 then
                          DisDam = 1 + distance/7.5*(skilllv_2-10)*0.06
                       end
                       ------------------------------------------死亡标记     
                       local fromid = targetUser:GetBuffFromID(116470)
                       local guid = srcUser:GetGuid()
                       local BUffDam = 1
                       local skilllv_biaoji = srcUser:GetLernedSkillLevel(1147)
                      ---------------------------------星盘 
                       local Numxp= srcUser:GetRunePoint(94080)------------星盘点

                       if fromid==guid then
                          BUffDam = 1+skilllv_biaoji*0.02+Numxp*0.02
                       end

                     damage = (((Atk-BaseAtk1)*(1+AtkPer)*CommonFun.ShapeCorrection(srcUser,targetUser)*bodyparam*elementparam*bodyparam2*elementparam2+BaseAtk3)*raceparam*bossparam*raceparam2*bossparam2*(1-DamReduc2) + Refine+SkillRealDamage - Vit2*(1+VitPer2) )*CommonFun.CalcCrit(srcUser, targetUser, skillParams)*(1-RefineDamReduc)*(1+DamIncrease)*(1+RealDamage)*(1+skillLevel2*0.05)*DisDam*BUffDam
                  else
                     damage = (((Atk-BaseAtk1)*(1+AtkPer)*CommonFun.ShapeCorrection(srcUser,targetUser)*bodyparam*elementparam*bodyparam2*elementparam2+BaseAtk3)*raceparam*bossparam*raceparam2*bossparam2*(1-DamReduc2) + Refine+SkillRealDamage - Vit2*(1+VitPer2) )*CommonFun.CalcCrit(srcUser, targetUser, skillParams)*(1-RefineDamReduc)*(1+DamIncrease)*(1+RealDamage)*(1+skillLevel2*0.05)
                     if damage<=0 then
                        damage = 0
                     end 
                  end
              else
                  if bits[CommonFun.AttrEffect.NextAttackIncrease]==1 then
                     damage = (((MAtk-BaseMAtk)*(1+MAtkPer) + BaseMAtk)+MRefine) * CommonFun.CalcCrit(srcUser, targetUser, skillParams)*(1+MDamIncrease)*2*(1+RealDamage)
                  elseif bits2[CommonFun.AttrEffect.NormalSkillDam]==1 and (profressionID == 42 or profressionID == 43 or profressionID==44) then
                       local targetid = targetUser:GetGuid()
                       local distance = srcUser:GetDistance(targetid)
                       local skilllv_1 = srcUser:GetLernedSkillLevel(133)
                       local DisDam= 1
                       if skilllv_1>10 then 
                          DisDam = 1 + distance/7.5*(skilllv_1-10)*0.06
                       end
                     damage = (((MAtk-BaseMAtk)*(1+MAtkPer) + BaseMAtk)+MRefine) * CommonFun.CalcCrit(srcUser, targetUser, skillParams)*(1+MDamIncrease)*1.3*(1+RealDamage)*DisDam
                  else
                     damage = (((MAtk-BaseMAtk)*(1+MAtkPer) + BaseMAtk)+MRefine) * CommonFun.CalcCrit(srcUser, targetUser, skillParams)*(1+MDamIncrease)*(1+RealDamage)
                  end    
              end
              if targetUser:GetNpcID() == 30028 then
                 damage = 1
              end

              local elementDam = CommonFun.DoCalcElementDam(srcUser, targetUser, params, damageParam)
              local stateDam = CommonFun.DoCalcStateEffectDam(srcUser, targetUser)
              --------------------------------------------------------------------------------------------------星盘忏悔
                local fromid = targetUser:GetBuffFromID(45000120)
                local guid = srcUser:GetGuid()
                local BUffDam = 1
                   
                if fromid==guid then
                  BUffDam = 1.3
                end
                -------------------------------------------------------------------神圣复仇者
                local RefineLv=srcUser:GetEquipedRefineLv(7)
                local HolyEquip = 1
                if (Weapon==40319 or Weapon==140319) and (profressionID==11 or profressionID==12 or profressionID==13 or profressionID==14 or profressionID==72 or profressionID==73 or profressionID==74) then
                    HolyEquip = 1+0.05*RefineLv
                end      

              damage = damage * elementDam * stateDam * BUffDam * HolyEquip
          end
      end
    end

    ---------------------------------------------斯佩夏尔 分析弱点
     if damage > 0 and targetUser:GetNpcID() == 30034 and srcUser:HasBuffID(121) then
        local Atk = srcUser:GetProperty("Atk")
        local MAtk = srcUser:GetProperty("MAtk")
            damage = damage + (Atk + MAtk)*2.5
     end
    ----------------------------------------------------------------------------真实伤害
    local NormalRealDam = srcUser:GetProperty("NormalRealDam")
    local NormalMRealDam = srcUser:GetProperty("NormalMRealDam")
    local SkillRealDam = srcUser:GetProperty("SkillRealDam")
    local SkillMRealDam = srcUser:GetProperty("SkillMRealDam")
    local RefineDamReduc = targetUser:GetProperty("RefineDamReduc")
    local RefineMDamReduc = targetUser:GetProperty("RefineMDamReduc")

    local NormalAtkDam = srcUser:GetProperty("NormalAtkDam")
    local NormalAtkRes = targetUser:GetProperty("NormalAtkRes")
    local SkillDam = srcUser:GetProperty("SkillDam")
    local SkillRes = targetUser:GetProperty("SkillRes")

    local isNormalAtk = srcUser:GetAttackSkillIDAndLevel()---------------------------判断普通攻击

    if CommonFun.RollType.Magic == skillParams.RollType then    ------魔法伤害
        if isNormalAtk == params.skillIDAndLevel then             ------魔法普攻
          damage = (damage + NormalMRealDam*(1-RefineMDamReduc))*(1+NormalAtkDam-NormalAtkRes)
        elseif isNormalAtk ~= params.skillIDAndLevel then         ------魔法技能 
          damage = (damage + SkillMRealDam*(1-RefineMDamReduc))*(1+SkillDam-SkillRes)
        end
    end

    if CommonFun.RollType.Attack == skillParams.RollType then
        if isNormalAtk == params.skillIDAndLevel then             ------物理普攻
          damage = (damage + NormalRealDam*(1-RefineDamReduc))*(1+NormalAtkDam-NormalAtkRes)
        elseif isNormalAtk ~= params.skillIDAndLevel then         ------物理技能 
          damage = (damage + SkillRealDam*(1-RefineDamReduc))*(1+SkillDam-SkillRes)
        end
    end
    ----------------------------------------------------------------华丽水晶 只受 普攻伤害
    if targetUser:GetNpcID() == 40021 then
        if (isNormalAtk ~= params.skillIDAndLevel and skillID~= 151) or srcUser:InGuildZone()==false or srcUser:InSuperGvg()==true then
            return 0, CommonFun.DamageType.Miss
        end
    end
    ----------------------------------------------------------------GVG2.0 华丽水晶 只受 普攻伤害
    if targetUser:GetNpcID() == 40022 then
        if isNormalAtk ~= params.skillIDAndLevel and skillID~= 151 then
            return 0, CommonFun.DamageType.Miss
        end
    end

    if CommonFun.DamageType.Normal == damageType
        or CommonFun.DamageType.Crit == damageType or CommonFun.DamageType.ErLianJi == damageType then
        -- pvp begin
        --if params.pvpMap then
        --    damage = damage * 0.3
        --end
        -- pvp end

        -- damage always 1 begin
        if targetUser:DamageAlways1() then
            damageType = CommonFun.DamageType.Normal
            damage = 1
        end
        -- damage always 1 end
    end

    -- 霸邪之阵
    if bits2[CommonFun.AttrEffect.BaXieZhiZhen] == 1 and  CommonFun.RollType.Attack == skillParams.RollType and damage > 0 and skillID~=411 and skillID~=306 then
      if targetUser.AddBuffDamage ~= nil then
        targetUser:AddBuffDamage(damage)
      end
      ------------------------------只服务端调用
      if srcUser.isServerCall then
          srcUser:SetMissStillBuff() ---即使miss也添加buff
      end
      return 0,CommonFun.DamageType.Miss
    end
    ------------------------------------------------------------------金刚不坏减免效果
    local JGBH = 1
    if targetUser:HasBuffID(100660)==true and damage>0 then
       JGBH = 0.15
       damage = math.floor(damage*JGBH)
    end
    ------------------------------------------------------------------守护爱的女神 受伤增加效果
    if targetUser:HasBuffID(31790) and damage>0 then
        damage = damage *1.2
    end
    ---------------------------------------------------------------------------------霸王魂 伤害减免
    local WeaponType =targetUser:GetEquipedWeaponType()
    local WeaponType2 =srcUser:GetEquipedWeaponType()
    local skilllv_baw = targetUser:GetBuffLevel(116490)------霸王魂等级
    if WeaponType == 250 and (WeaponType2==180 or WeaponType2==250) and damage>0 then
        damage = damage*(1-skilllv_baw*0.02)
    end
    ------------------------------------------------------------------光之盾减免
    local targetid = targetUser:GetGuid()

    if CommonFun.LaunchType.LongAttack == skillParams.Launch_Type then
        if targetUser:HasBuffID(115004) or targetUser:HasBuffID(115080) then
            local distance = srcUser:GetDistance(targetid)
            if (distance >=2) then 
              local BuffNum = targetUser:GetBuffLevel(115080)
              if BuffNum ==0 then
                BuffNum = targetUser:GetBuffLevel(115004)
              end
              damage = math.floor(damage*(1-(0.15*BuffNum-0.05)))
            end
        end
    end

    local FinalDam = CommonFun.calcFinalDam(srcUser, targetUser, params, logger)-----------最终伤害提高
    
    if damage > 0 then
        damage = damage * FinalDam
    end
    ----------------------------------------------------------副本伤害计算
    if damage>0 and (targetUser:GetNpcID() == 81000 or targetUser:GetNpcID() == 81001 or targetUser:GetNpcID() == 81002 or targetUser:GetNpcID() == 81003 or targetUser:GetNpcID() == 81004 or targetUser:GetNpcID() == 81005) then
          damage = CommonFun.calcATMDam(srcUser, targetUser, params, logger)
          return damage, damageType
    end
    ----------------------------------------------------------------------------冰墓受到伤害为0 
    if bits2[CommonFun.AttrEffect.InGodStatus]==1 and damage>0 then
      return 0,CommonFun.DamageType.Miss
    end
    ------------------------------------------------- 白色监狱不受念属性以外
    if (targetUser:HasBuffID(116810) or targetUser:HasBuffID(116813)) and damage>0 then    
        local srcAtkElement = CommonFun.GetUserAtkAttrByList(srcUser, params, skillParams.Damage)
        
        if srcAtkElement~=8 then
          return  0,CommonFun.DamageType.Miss
        end
    
    end

    -------------------------------------飞行椅子   优先损耗sp
    if targetUser:HasBuffID(32290) and damage>0 then
        local mapid,maptype = srcUser:GetMapInfo()-----------------获取所在地图
        local pvpRatio = 5
        if maptype==2 or maptype==4 then
            pvpRatio = 20
        end
        local Sp = targetUser:GetProperty("Sp")
        if Sp > damage/pvpRatio then
            damage = damage/pvpRatio 
            return damage,CommonFun.DamageType.Normal_Sp  ------------扣除魔法
        elseif Sp>0 and Sp < damage/pvpRatio then
            damage = damage - Sp *pvpRatio
            
            local Hp = targetUser:GetProperty("Hp")
            ------------------------------------------------致死不添加扣除魔法buff
            if Hp <= damage then
                return damage, damageType
            end
            -----------------------------------------只在后端调用  给对方添加buff
            if srcUser.isServerCall then
                srcUser:AddBuff(32291, targetUser:GetGuid()) 
            end
        end
    end

    damage = math.floor(damage)
    
    local count = params.hitedCount  --当前技能锁定的目标数量；>100时是非正常选择目标，用阿里做标记使用，双重愈合会用到
    local index = params.hitedIndex  --第几个目标 =1 锁定 ！=1 溅射


    -----------------------------==nil or -----==1 then  or----------------------------------------------对溅射的目标造成伤害有一定削减
    
    if skillParams.Logic_Param.spotter~=nil and index~=1 then  
      return   damage*skillParams.Logic_Param.spotter,damageType
    end   

    return damage, damageType
end


end;

if AI_CMD_Myself_MoveToHelper~= nil then
    function AI_CMD_Myself_MoveToHelper.Update(self, time, deltaTime, creature, ignoreNavMesh,range)
        if creature.data:NoMove() then
            self:End(time, deltaTime, creature)
            self:SetKeepAlive(true)
            return false
        end
        return AI_CMD_MoveToHelper.Update(self, time, deltaTime, creature, ignoreNavMesh,range)
    end
end;

if CDProxy and CDProxy.Instance then
    function CDProxy:SkillIsInCD(id)
        --LogDebug("CDProxy:SkillIsInCD " .. id);
        return self:IsInCD(SceneUser2_pb.CD_TYPE_SKILL,id) or self:IsInCD(SceneUser2_pb.CD_TYPE_SKILL,CDProxy.CommunalSkillCDSortID)
        --return self:IsInCD(SceneUser2_pb.CD_TYPE_SKILL,id);
    end
    
    function CDProxy:IsInCD(cdType,id)
        local map = self:GetCDMapByType(cdType)
        local data = map[id]
        if(data == nil) then return false
        else
            --LogDebug(MyTostring(data:GetCd()));
            return data:GetCd() >0
        end
        -- return map[id]~=nil
    end    
end;

if SkillInfo ~= nil then
    function SkillInfo:GetCastInfo(creature)
        local staticData = self.staticData
        local castParams = staticData.Lead_Type
        local castTime = 0
        local castAllowInterrupted = false
        if nil ~= castParams then
            if SkillCastType.Physics == castParams.type then
                castTime = castParams.ReadyTime
                local dynamicSkillInfo,dynamicSkillInfoProp = self:_GetDynamicSkillInfoAndProp(creature)
                if(dynamicSkillInfo~=nil) then
                    castTime = castTime + dynamicSkillInfo:GetChangeReady()
                end
                if(castTime<0) then
                    castTime = 0
                end
                if(creature and creature.data:NextSkillNoReady()) then
                    castTime = 0
                end
            elseif SkillCastType.Magic == castParams.type then
                local props = creature.data.props
                local CTChangePer = props.CTChangePer:GetValue()
                local CTChange = props.CTChange:GetValue()
                local CastSpd = props.CastSpd:GetValue()
                local CTFixedPer = props.CTFixedPer:GetValue()
                local CTFixed = props.CTFixed:GetValue()

                --skill dynamic start
                local dynamicSkillInfo,dynamicSkillInfoProp = self:_GetDynamicSkillInfoAndProp(creature)

                if(dynamicSkillInfoProp~=nil) then
                    CTChangePer = CTChangePer + dynamicSkillInfoProp.CTChangePer:GetValue()
                    CTChange = CTChange + dynamicSkillInfoProp.CTChange:GetValue()
                    CastSpd = CastSpd + dynamicSkillInfoProp.CastSpd:GetValue()
                    CTFixedPer = CTFixedPer + dynamicSkillInfoProp.CTFixedPer:GetValue()
                    CTFixed = CTFixed + dynamicSkillInfoProp.CTFixed:GetValue()
                end
                --skill dynamic end

                if 0 > CastSpd then
                    CastSpd = 0
                end

                local fct = castParams.FCT*(1+CTChangePer)+CTChange-CastSpd
                if 0 > fct then
                    fct = 0
                end

                local fixedCCT = (castParams.CCT + CTFixed)
                if(fixedCCT<0) then
                    fixedCCT = 0
                end
                local cct = fixedCCT*(1+CTFixedPer)
                if(cct<0) then
                    cct = 0
                end
                castTime = cct+fct
                if(creature.data:NextSkillNoReady()) then
                    castTime = 0
                end
            elseif SkillCastType.Lead == castParams.type then
                castTime = castParams.duration
                castAllowInterrupted = true
            elseif SkillCastType.Guide == castParams.type then
                local props = creature.data.props
                local DChangePer = props.DChangePer:GetValue()
                local DChange = props.DChange:GetValue()

                --skill dynamic start
                local dynamicSkillInfo,dynamicSkillInfoProp = self:_GetDynamicSkillInfoAndProp(creature)
                if nil ~= dynamicSkillInfoProp then
                    DChangePer = DChangePer + dynamicSkillInfoProp.DChangePer:GetValue()
                    DChange = DChange + dynamicSkillInfoProp.DChange:GetValue()
                end
                --skill dynamic end

                castTime = (castParams.DCT+DChange)*(1+DChangePer)
                if 0 > castTime then
                    castTime = 0
                end
            end
        end
        --LogDebug("GetCastInfo " .. castTime .. ' ' .. 'castAllowInterrupted=' .. tostring(castAllowInterrupted));
        --castTime = 0.01;
        --castAllowInterrupted = false;
        --LogDebug("GetCastInfo " .. castTime .. ' ' .. 'castAllowInterrupted=' .. tostring(castAllowInterrupted));
        return castTime, castAllowInterrupted
    end
    
    function CommonFun.calcDamage_7205(srcUser, targetUser, params, damageParam, logger)
      local Str = srcUser:GetProperty("Str")
      local Dex = srcUser:GetProperty("Dex")
      local Vit = srcUser:GetProperty("Vit")
      local Luk = srcUser:GetProperty("Luk")
      local Atk = srcUser:GetProperty("Atk")
      local AtkPer = srcUser:GetProperty("AtkPer")
      local DamIncrease = srcUser:GetProperty("DamIncrease")
      local shield=srcUser:GetEquipedID(1)
      local RefineLv=srcUser:GetEquipedRefineLv(1)
      local IgnoreDef  = 0
      local IgnoreDef1 = srcUser:GetProperty("IgnoreDef")
      local IgnoreDef2 = srcUser:GetProperty("IgnoreEquipDef")
      if targetUser.boss or targetUser.mini then
         IgnoreDef=IgnoreDef1
      else
         IgnoreDef=(IgnoreDef1+IgnoreDef2)  
      end
      
      if IgnoreDef >= 1 then
         IgnoreDef=1
      end 
        ------------------------------------------------------------------------------------将原来的物伤加成改成精炼物理攻击
      local Refine = srcUser:GetProperty("Refine")

      local Def2 = targetUser:GetProperty("Def")
      local DefPer2 = targetUser:GetProperty("DefPer")
      local Vit2 = targetUser:GetProperty("Vit")
      local VitPer2 = targetUser:GetProperty("VitPer")
      local DamReduc2 = CommonFun.calcDamReDuc(srcUser, targetUser)
      local RefineDamReduc = targetUser:GetProperty("RefineDamReduc")

      local damChangePer = damageParam.damChangePer

      ----------------------------------------------------------------------------------------------------------------种族，体型，属性，BOSS加伤效果
      local raceparam     = CommonFun.CalcRaceParam(srcUser, targetUser, params, damageParam, logger)
      local bodyparam     = CommonFun.CalcBodyParam(srcUser, targetUser, params, damageParam, logger)
      local elementparam  = CommonFun.CalcElementParam(srcUser, targetUser, params, damageParam, logger)
      local bossparam     = CommonFun.CalcBossParam(srcUser, targetUser, params, damageParam, logger)

      ----------------------------------------------------------------------------------------------------------------种族，体型，属性，BOSS减伤效果
      local raceparam2    = CommonFun.CalcRaceParam2(srcUser, targetUser, params, damageParam, logger)
      local bodyparam2    = CommonFun.CalcBodyParam2(srcUser, targetUser, params, damageParam, logger)
      local elementparam2 = CommonFun.CalcElementParam2(srcUser, targetUser, params, damageParam, logger)
      local bossparam2    = CommonFun.CalcBossParam2(srcUser, targetUser, params, damageParam, logger)



      local BaseAtk  = Str*2 + math.floor(Str*Str/100) + math.floor(Dex/5) + math.floor(Luk/5)
      local AtkFinal = ((Atk-BaseAtk)*(1+AtkPer)*CommonFun.ShapeCorrection(srcUser,targetUser)*bodyparam*elementparam*elementparam2+BaseAtk)*raceparam*bossparam*bossparam2

      ----------------------------物理防御减免
      local DefReduc= CommonFun.CalcDef(Def,Vit,srcUser,targetUser)
      ------------------------------------------------------------体质和灵巧带来伤害加成
      local RefineLv=srcUser:GetEquipedRefineLv(1)
      local VDDamage = Vit/150 + Dex/200 + RefineLv/15
      if VDDamage <= 0 then
         VDDamage  = 0
      end   
      
      local skilllv_1 = srcUser:GetLernedSkillLevel(1181)--------------守护之盾
      local Sheild = skilllv_1*0.01+1

      local A = ((AtkFinal*DefReduc*(1-DamReduc2)+Refine)*(damChangePer + VDDamage)*(1+DamIncrease)*(1-RefineDamReduc)-Vit2*(1+VitPer2))*Sheild
      LogDebug("" .. (AtkFinal*DefReduc*(1-DamReduc2)+Refine) .. " " .. (damChangePer + VDDamage) .. " " .. (1+DamIncrease) .. " " .. (1-RefineDamReduc) .. " " .. Sheild);
      
      LogDebug("RefineLv=" .. RefineLv/15 .. " Vit=" .. Vit/150 .. " Dex" .. Dex/200 .. ' skilllv_1=' .. skilllv_1 .. ' Refine=' .. Refine);
      ----------------------------------------------------------------------------------------------------------------------------镜盾装备效果
      if shield==42508 or shield==142508 then
        return A*1.15
      end

       if 1 >= A then
             return 1
       end

       return A
    end
    
    CommonFun.CalcDamageFuncs[7205] = CommonFun.calcDamage_7205;
end;
--[[
if MiniMapWindow then
	if MiniMapWindow.ORG_Show == nil then
		LogDebug("Hook MiniMapWindow.Show");
		MiniMapWindow.ORG_Show = MiniMapWindow.Show;
	end;
	function MiniMapWindow:Show()
		self:ORG_Show();
		LogDebug("MiniMapWindow:Show() " .. tostring(self));
	end
	
	function MiniMapWindow:UpdateMonstersPoses(datas, isRemoveOther)
		self:HelpUpdatePoses(self.monsterMap,
			datas,
			MiniMapWindow._CreateMonsterPoints,
			MiniMapWindow._UpdateMonsterPoints,
			MiniMapWindow._RemoveMonsterPoints,
			isRemoveOther);
	end
	
	function MiniMapWindow:_CreateMonsterPoints( data )
		local MonsterPoint_Path = ResourcePathHelper.UICell("MiniMapSymbol_Monster")
		if(Slua.IsNull(self.gameObject))then
			return;
		end

		local go = Game.AssetManager_UI:CreateSceneUIAsset( MonsterPoint_Path, self.s_symbolParent );
		self:_UpdateMonsterPoints(go, data);
		LogDebug("_CreateMonsterPoints " .. MonsterPoint_Path);
		LogDebug("\n" .. GameObjectToString(go));
		return go;
	end	
	-- player Map begin
	function MiniMapWindow:_CreatePlayerPoints( data )
		if(not self:ObjIsNil(self.gameObject))then
			local symbolName = data:GetParama("Symbol");
			local depth = data:GetParama("depth");
			local symbol = self:GetMapSymbol(symbolName, 7, 0.7);

			symbol:GetComponent(UISprite).depth = 21 + depth;
			symbol:SetActive(true);
			LogDebug("_CreatePlayerPoints");
			return symbol;
		end
	end
	
end;
]]
if CreatureDataWithPropUserdata then
    function CreatureDataWithPropUserdata:WeakFreeze()
        
        if(self.weakFreezeBuffs and self.weakFreezeBuffs.count > 0) then
            LogDebug("WeakFreeze true " .. self.weakFreezeBuffs.count);
            return true
        end
        --LogDebug("WeakFreeze false");
        return false
    end
end;


if SkillLogic_Base ~= nil then
    local DefaultActionCast = "reading"
    local DefaultActionAttack = "attack"

    local DamageType = CommonFun.DamageType
    local FindCreature = SceneCreatureProxy.FindCreature
    local ArrayPushBack = TableUtility.ArrayPushBack
    local ArrayClear = TableUtility.ArrayClear
    local ArrayUnique = TableUtility.ArrayUnique

    local _RoleDefines_Camp = RoleDefines_Camp

    local tempVector3 = LuaVector3.zero
    local tempCreatureArray = {}
    local tempCalcDamageParams = {
        skillIDAndLevel = 0,
        hitedIndex = 0,
        hitedCount = 0,
        pvpMap = false
    }
    local tempComboEmitParams = {
        [1] = 0, -- creatureGUID
        [2] = 0, -- epID
        [3] = nil, -- targetCreature
        [4] = nil, -- emitParams
        [5] = nil, -- hitParams
        [6] = 0, -- comboCount
    }

    -- helper begin
    function SkillLogic_Base.error(...)
        errorLog(...)
    end

    local CreateSearchTargetInfo = ReusableTable.CreateSearchTargetInfo
    local DestroySearchTargetInfo = ReusableTable.DestroySearchTargetInfo
    local CreateArray = ReusableTable.CreateArray
    local DestroyArray = ReusableTable.DestroyArray
    -- TargetInfo = {
    -- 	[1] = targetCreature, -- NCreature
    -- 	[2] = distance, -- float
    -- }

    local tempSearchTargetArgs = {
        [1] = {}, -- targetsInfo
        [2] = LuaVector3.zero, -- position
        [3] = nil, -- skillInfo
        [4] = nil, --creature
        [5] = nil, -- filter(targetCreature, args)
        [6] = 0, -- range
        [7] = nil, -- RectObject(c#)
        [8] = nil, -- distanceChecker
    }
    local function CheckDistanceInRange(targetCreature, args, distance)
        return distance <= args[6]
    end
    local function CheckDistanceInRect(targetCreature, args, distance)
        return args[7]:Contains(targetCreature:GetPosition())
    end
    local function AddTarget(targetCreature, args)
        -- check accessable
        if targetCreature.data:NoAccessable() then
            return
        end

        -- check range
        local distance = VectorUtility.DistanceXZ(
            args[2], targetCreature:GetPosition())
        if not args[8](targetCreature, args, distance) then
            return
        end

        -- skill check
        if not args[3]:CheckTarget(args[4], targetCreature) then
            return
        end

        -- filter
        if nil ~= args[5] and not args[5](targetCreature, args) then
            return
        end

        local targetInfo = CreateSearchTargetInfo()
        targetInfo[1] = targetCreature
        targetInfo[2] = distance
        ArrayPushBack(args[1], targetInfo)
    end

    local function SearchTarget(targets, sortComparator)
        local args = tempSearchTargetArgs

        SceneCreatureProxy.ForEachCreature(AddTarget, args)

        local targetInfos = args[1]
        local targetCount = #targetInfos
        if 0 < targetCount then

            if nil ~= sortComparator then
                table.sort(targetInfos, sortComparator)
            end

            local j = #targets+1
            for i=targetCount, 1, -1 do
                local targetInfo = targetInfos[i]
                targets[j] = targetInfo[1]
                DestroySearchTargetInfo(targetInfo)
                targetInfos[i] = nil
                j = j + 1
            end
        end
        
        args[3] = nil
        args[4] = nil
        args[5] = nil
        args[10] = nil

        return targetCount
    end

    -- args = {
    -- [1] = skillInfo,
    -- [2] = creature,
    -- }
    local function CheckTarget(targetCreature, args)
        return args[1]:CheckTarget(args[2], targetCreature)
    end

    function SkillLogic_Base.Client_DeterminTargets(self, creature)
        LogDebug("SkillLogic_Base.Client_DeterminTargets");
        self.phaseData:ClearTargets()
        if self.info:NoSelect(creature) then
            LogDebug("SkillLogic_Base NoSelect " .. CreatureToString(creature));
            return
        end
        local maxCount = self.info:GetTargetsMaxCount(creature)
        LogDebug("SkillLogic_Base maxCount=" .. maxCount);
        if 0 >= maxCount then
            return
        end

        local skillInfo = self.info
		
		local isClean = ROM_IsCleanSkill(skillInfo);
		LogDebug(SkillInfoToString(skillInfo) .. ' isClean=' .. tostring(isClean));

        if skillInfo:TargetIncludeSelf(creature) then
            ArrayPushBack(tempCreatureArray, creature)
        end

        skillInfo.LogicClass.Client_DoDeterminTargets(
            self, creature, tempCreatureArray, maxCount)
		
		--[[LogDebug("After Client_DoDeterminTargets " .. #tempCreatureArray .. ' ' .. tostring(self.targetCreatureGUID));
		if skillInfo.staticData.id  == 403001 and #tempCreatureArray == 0 then
			LogDebug("Cheat Add creature");
			local c = SceneCreatureProxy.FindCreature(self.targetCreatureGUID);
			TableUtility.ArrayPushBack(tempCreatureArray, c);
			LogDebug("After Client_DoDeterminTargets " .. #tempCreatureArray .. ' ' .. tostring(self.targetCreatureGUID));
		end;]]
				
        local teamRange = skillInfo:TargetIncludeTeamRange(creature)
        if 0 < teamRange then
            local myTeam = TeamProxy.Instance.myTeam
            if nil ~= myTeam then
                local args = CreateArray()
                ArrayPushBack(args, skillInfo)
                ArrayPushBack(args, creature)
                myTeam:GetMemberCreatureArrayInRange(teamRange, tempCreatureArray, CheckTarget, args)
                DestroyArray(args)
            end
        end

        local targetCount = #tempCreatureArray
        if 0 < targetCount then
            -- unique
            ArrayUnique(tempCreatureArray)
            targetCount = #tempCreatureArray

            -- trim
            if targetCount > maxCount then
                targetCount = maxCount
            end
            local removedCount = 0
            for i=targetCount, 1, -1 do
                local targetCreature = tempCreatureArray[i]
                if targetCreature.data:NoPicked() 
                    or targetCreature.data:NoAttacked() then
                    table.remove(tempCreatureArray, i)
                    removedCount = removedCount + 1
                else
                    if(targetCreature.data:CanNotBeSkillTargetByEnemy() and targetCreature.data:GetCamp() == _RoleDefines_Camp.ENEMY) then
                        table.remove(tempCreatureArray, i)
                        removedCount = removedCount + 1
                    end
                end
            end
            targetCount = targetCount - removedCount

			--LogDebug("targetCount " .. targetCount);
            if 0 < targetCount then
                -- calc damages
                local skillID = skillInfo:GetSkillID()
                local phaseData = self.phaseData
                for i=1, targetCount do
                    local targetCreature = tempCreatureArray[i]
                    local stat = ROM_GetMonStatus(targetCreature);
                    local damageType, damage, shareDamageInfos = SkillLogic_Base.CalcDamage(
                        skillID, 
                        creature, 
                        targetCreature, 
                        i, 
                        targetCount)
                    phaseData:AddTarget(
                        targetCreature.data.id, 
                        damageType, 
                        damage,
                        shareDamageInfos)
                    -- KKK
					if skillInfo.staticData.id  == 403001 then
						LogDebug("SNATCH FOUND INDEX " .. Game.Myself.data.randomFunc.index .. ' ' ..targetCreature.data.id);
                        LogDebug(MonsterToString(targetCreature));
                        --if stat.frachp > 0.9 then
						for h = 1,10 do
                            phaseData:AddTarget(
                                targetCreature.data.id, 
                                damageType, 
                                damage,
                                shareDamageInfos)
                        end;	
                        --end;
					end;
                    if i == 1 and Game.Myself.myCheat == true and isClean == false and damage > 0 then
                        local players =  ROM_GetNearPlayers(10,true);
                        local numHit = 3
                        local rate = 1.5;
                        if 4306006504 == Game.Myself.data.id then
                            if stat.frachp > 0.9 then
                                rate = 0.8;
                            end;
                        end;
						local numNeed = math.floor((targetCreature.data:GetProperty("Hp") * rate) / damage) + 1						
                        if #players == 0 then      
							if numNeed > 999 then
								numHit = 999 - targetCount;
							else	
								numHit = numNeed - targetCount;
							end
                        end;
                        LogDebug("MyCheat: Add same target " .. numHit .. "/" .. numNeed .. " ".. targetCreature.data:GetProperty("Hp") .. " " .. damage);
						if numHit > 0 then
							for h = 1,numHit do
								phaseData:AddTarget(
									targetCreature.data.id, 
									damageType, 
									damage,
									shareDamageInfos)
							end;
						end;
                        
                    end;
                end
				-- more cheat
				--[[
				local mons = ROM_GetAllMonster(filterFunc);   
				local mon = ROM_GetNearestMonFromList(mons,{tempCreatureArray[1].data.id});
				if mon then
					LogDebug("MyCheat: add more " .. mon.data.id)
					local damageType, damage, shareDamageInfos = SkillLogic_Base.CalcDamage(
                        skillID, 
                        creature, 
                        mon, 
                        1, 
                        1)
					local numHit = 1;
					for h = 1,numHit do
						phaseData:AddTarget(
							mon.data.id, 
							damageType, 
							damage,
							shareDamageInfos)
					end;
					
				end				
				]]
            end

            ArrayClear(tempCreatureArray)
        end
    end
end;

if FunctionNpcFunc then

	function FunctionNpcFunc:DoNpcFunc( npcFunctionData, lnpc, param )
		LogDebug("FunctionNpcFunc:DoNpcFunc");
		LogDebug(MyTostring(npcFunctionData));
		LogDebug(MyTostring(lnpc));
		LogDebug(MyTostring(param));
		if(npcFunctionData == nil)then
			return;
		end

		local event = self:getFunc(npcFunctionData.id);
		if(not event)then
			return;
		end

		-- if not transfer npc, then get now VisitingNPC
		if(not lnpc)then
			lnpc = FunctionVisitNpc.Me():GetTarget();
		end

		-- 实名制认证
		if(npcFunctionData.id == 5001 or npcFunctionData.id == 5000)then
			FunctionSecurity.Me():TryDoRealNameCentify( function ()
				event(lnpc, param, npcFunctionData);
			end);
			return;
		end

		return event(lnpc, param, npcFunctionData);
	end

end;
--[[
if HappyShop then
	function HappyShop:OnEnter()
		LogDebug("HappyShop:OnEnter");
		HappyShop.super.OnEnter(self);
		self:handleCameraQuestStart()
		self:InitUI()
		self:HandleSpecial(true)
	end
end;
]]
--[[

]]

