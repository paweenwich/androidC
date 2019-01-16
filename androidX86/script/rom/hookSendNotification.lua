function HOOK_SendNotification(self,p1,p2)
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
		if p1 == UIEvent.JumpPanel then
			ListField(p2,"",{},"  ");
			
			LogDebug(MonsterToString(p2.viewdata.npcTarget));
		end;
		--if(TableUtil.HasValue(MyselfEvent,p1)) then
			
			--LogDebug(MyTostring(p2));
		--	ListField(p2,"",{}," ");
		--end;
		--if(TableUtil.HasValue(ChatRoomEvent,p1)) then
		--	ListField(p2,"",{}," ");
		--end;
	end;
	GameFacade.Instance:_sendNotification(p1,p2);
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