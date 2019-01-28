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

function HOOK_SendProto(data)
	local id1 = data.cmd;
	local id2 = data.param;
    --LogDebug("SEND: " .. tostring(data));
	LogDebug("SENDPROTO [" .. id1 .. '] [' .. id2 .. '] ' .. singleLine(data));
    NetProtocol._SendProto(data);
end;

function HOOK_Send(id1, id2, data)
    LogDebug("SEND: [" .. id1 .. '] [' .. id2 .. '] ' .. singleLine(data));
    NetProtocol._Send(data);
end;

function ROM_RecvSKIP()
	--return true;
	return false;
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


ROM_Packets = {
{17,1,"RecvQueryUserResumeAchCmd"},
{17,2,"RecvQueryAchieveDataAchCmd"},
{17,3,"RecvNewAchieveNtfAchCmd"},
{17,4,"RecvRewardGetAchCmd"},

{60,1,"RecvStartActCmd"},
{60,4,"RecvStopActCmd"},
{60,2,"RecvBCatUFOPosActCmd"},
{60,3,"RecvActProgressNtfCmd"},
{60,5,"RecvStartGlobalActCmd"},

{64,1,"RecvActivityEventNtf"},
{64,2,"RecvActivityEventUserDataNtf"},
{64,3,"RecvActivityEventNtfEventCntCmd"},

{28,1,"RecvAstrolabeQueryCmd"},
{28,2,"RecvAstrolabeActivateStarCmd"},
{28,3,"RecvAstrolabeQueryResetCmd"},
{28,4,"RecvAstrolabeResetCmd"},

{63,1,"RecvNtfAuctionStateCCmd"},
{63,2,"RecvOpenAuctionPanelCCmd"},
{63,3,"RecvNtfSignUpInfoCCmd"},
{63,14,"RecvNtfMySignUpInfoCCmd"},
{63,12,"RecvSignUpItemCCmd"},
{63,4,"RecvNtfAuctionInfoCCmd"},
{63,5,"RecvUpdateAuctionInfoCCmd"},
{63,6,"RecvReqAuctionFlowingWaterCCmd"},
{63,7,"RecvUpdateAuctionFlowingWaterCCmd"},
{63,8,"RecvReqLastAuctionInfoCCmd"},
{63,9,"RecvOfferPriceCCmd"},
{63,10,"RecvReqAuctionRecordCCmd"},
{63,11,"RecvTakeAuctionRecordCCmd"},
{63,13,"RecvNtfCanTakeCntCCmd"},
{63,15,"RecvNtfMyOfferPriceCCmd"},
{63,16,"RecvNtfNextAuctionInfoCCmd"},
{63,17,"RecvReqAuctionInfoCCmd"},
{63,18,"RecvNtfCurAuctionInfoCCmd"},
{63,19,"RecvNtfOverTakePriceCCmd"},
{63,20,"RecvReqMyTradedPriceCCmd"},
{63,21,"RecvNtfMaskPriceCCmd"},
{63,22,"RecvAuctionDialogCCmd"},

{62,1,"RecvSetAuthorizeUserCmd"},
{62,2,"RecvResetAuthorizeUserCmd"},
{62,3,"RecvSyncAuthorizeToSession"},
{62,4,"RecvNotifyAuthorizeUserCmd"},
{62,5,"RecvSyncRealAuthorizeToSession"},

{15,1,"RecvBossListUserCmd"},
{15,2,"RecvBossPosUserCmd"},
{15,3,"RecvKillBossUserCmd"},

{16,1,"RecvCarrierInfoUserCmd"},
{16,6,"RecvCreateCarrierUserCmd"},
{16,10,"RecvInviteCarrierUserCmd"},
{16,2,"RecvJoinCarrierUserCmd"},
{16,3,"RecvRetJoinCarrierUserCmd"},
{16,4,"RecvLeaveCarrierUserCmd"},
{16,9,"RecvReachCarrierUserCmd"},
{16,5,"RecvCarrierMoveUserCmd"},
{16,7,"RecvCarrierStartUserCmd"},
{16,8,"RecvCarrierWaitListUserCmd"},
{16,11,"RecvChangeCarrierUserCmd"},
{16,12,"RecvFerrisWheelInviteCarrierCmd"},
{16,13,"RecvFerrisWheelProcessInviteCarrierCmd"},
{16,14,"RecvStartFerrisWheelUserCmd"},
{16,15,"RecvCatchUserJoinCarrierUserCmd"},

{59,1,"RecvQueryItemData"},
{59,2,"RecvPlayExpressionChatCmd"},
{59,3,"RecvQueryUserInfoChatCmd"},
{59,4,"RecvBarrageChatCmd"},
{59,5,"RecvBarrageMsgChatCmd"},
{59,6,"RecvChatCmd"},
{59,7,"RecvChatRetCmd"},
{59,8,"RecvQueryVoiceUserCmd"},
{59,10,"RecvGetVoiceIDChatCmd"},
{59,11,"RecvLoveLetterNtf"},
{59,12,"RecvChatSelfNtf"},
{59,13,"RecvNpcChatNtf"},
{59,14,"RecvQueryRealtimeVoiceIDCmd"},

{19,1,"RecvCreateChatRoom"},
{19,2,"RecvJoinChatRoom"},
{19,3,"RecvExitChatRoom"},
{19,4,"RecvKickChatMember"},
{19,5,"RecvExchangeRoomOwner"},
{19,7,"RecvRoomMemberUpdate"},
{19,6,"RecvEnterChatRoom"},
{19,8,"RecvChatRoomDataSync"},
{19,9,"RecvChatRoomTip"},

{58,1,"RecvDojoPrivateInfoCmd"},
{58,2,"RecvDojoPublicInfoCmd"},
{58,3,"RecvDojoInviteCmd"},
{58,4,"RecvDojoReplyCmd"},
{58,5,"RecvEnterDojo"},
{58,6,"RecvDojoAddMsg"},
{58,7,"RecvDojoPanelOper"},
{58,9,"RecvDojoSponsorCmd"},
{58,10,"RecvDojoQueryStateCmd"},
{58,11,"RecvDojoRewardCmd"},

{2,1,"RecvRegErrUserCmd"},
{2,2,"RecvKickUserErrorCmd"},
{2,3,"RecvMaintainUserCmd"},

{11,1,"RecvTrackFuBenUserCmd"},
{11,2,"RecvFailFuBenUserCmd"},
{11,3,"RecvLeaveFuBenUserCmd"},
{11,4,"RecvSuccessFuBenUserCmd"},
{11,5,"RecvWorldStageUserCmd"},
{11,6,"RecvStageStepUserCmd"},
{11,7,"RecvStartStageUserCmd"},
{11,8,"RecvGetRewardStageUserCmd"},
{11,9,"RecvStageStepStarUserCmd"},
{11,11,"RecvMonsterCountUserCmd"},
{11,12,"RecvFubenStepSyncCmd"},
{11,13,"RecvFuBenProgressSyncCmd"},
{11,15,"RecvFuBenClearInfoCmd"},
{11,16,"RecvUserGuildRaidFubenCmd"},
{11,17,"RecvGuildGateOptCmd"},
{11,18,"RecvGuildFireInfoFubenCmd"},
{11,19,"RecvGuildFireStopFubenCmd"},
{11,20,"RecvGuildFireDangerFubenCmd"},
{11,21,"RecvGuildFireMetalHpFubenCmd"},
{11,22,"RecvGuildFireCalmFubenCmd"},
{11,23,"RecvGuildFireNewDefFubenCmd"},
{11,24,"RecvGuildFireRestartFubenCmd"},
{11,25,"RecvGuildFireStatusFubenCmd"},
{11,26,"RecvGvgDataSyncCmd"},
{11,27,"RecvGvgDataUpdateCmd"},
{11,28,"RecvGvgDefNameChangeFubenCmd"},
{11,29,"RecvSyncMvpInfoFubenCmd"},
{11,30,"RecvBossDieFubenCmd"},
{11,31,"RecvUpdateUserNumFubenCmd"},
{11,32,"RecvSuperGvgSyncFubenCmd"},
{11,33,"RecvGvgTowerUpdateFubenCmd"},
{11,39,"RecvGvgMetalDieFubenCmd"},
{11,34,"RecvGvgCrystalUpdateFubenCmd"},
{11,35,"RecvQueryGvgTowerInfoFubenCmd"},
{11,36,"RecvSuperGvgRewardInfoFubenCmd"},
{11,37,"RecvSuperGvgQueryUserDataFubenCmd"},
{11,38,"RecvMvpBattleReportFubenCmd"},

{50,1,"RecvQueryGuildListGuildCmd"},
{50,2,"RecvCreateGuildGuildCmd"},
{50,3,"RecvEnterGuildGuildCmd"},
{50,4,"RecvGuildMemberUpdateGuildCmd"},
{50,5,"RecvGuildApplyUpdateGuildCmd"},
{50,6,"RecvGuildDataUpdateGuildCmd"},
{50,7,"RecvGuildMemberDataUpdateGuildCmd"},
{50,8,"RecvApplyGuildGuildCmd"},
{50,9,"RecvProcessApplyGuildCmd"},
{50,10,"RecvInviteMemberGuildCmd"},
{50,11,"RecvProcessInviteGuildCmd"},
{50,12,"RecvSetGuildOptionGuildCmd"},
{50,13,"RecvKickMemberGuildCmd"},
{50,14,"RecvChangeJobGuildCmd"},
{50,15,"RecvExitGuildGuildCmd"},
{50,16,"RecvExchangeChairGuildCmd"},
{50,17,"RecvDismissGuildCmd"},
{50,18,"RecvLevelupGuildCmd"},
{50,19,"RecvDonateGuildCmd"},
{50,25,"RecvDonateListGuildCmd"},
{50,26,"RecvUpdateDonateItemGuildCmd"},
{50,27,"RecvDonateFrameGuildCmd"},
{50,20,"RecvEnterTerritoryGuildCmd"},
{50,21,"RecvPrayGuildCmd"},
{50,22,"RecvGuildInfoNtf"},
{50,23,"RecvGuildPrayNtfGuildCmd"},
{50,24,"RecvLevelupEffectGuildCmd"},
{50,28,"RecvQueryPackGuildCmd"},
{50,32,"RecvPackUpdateGuildCmd"},
{50,29,"RecvExchangeZoneGuildCmd"},
{50,30,"RecvExchangeZoneNtfGuildCmd"},
{50,31,"RecvExchangeZoneAnswerGuildCmd"},
{50,33,"RecvQueryEventListGuildCmd"},
{50,34,"RecvNewEventGuildCmd"},
{50,35,"RecvApplyRewardConGuildCmd"},
{50,37,"RecvFrameStatusGuildCmd"},
{50,38,"RecvModifyAuthGuildCmd"},
{50,39,"RecvJobUpdateGuildCmd"},
{50,40,"RecvRenameQueryGuildCmd"},
{50,41,"RecvQueryGuildCityInfoGuildCmd"},
{50,42,"RecvCityActionGuildCmd"},
{50,43,"RecvGuildIconSyncGuildCmd"},
{50,44,"RecvGuildIconAddGuildCmd"},
{50,45,"RecvGuildIconUploadGuildCmd"},
{50,47,"RecvOpenFunctionGuildCmd"},
{50,48,"RecvBuildGuildCmd"},
{50,49,"RecvSubmitMaterialGuildCmd"},
{50,50,"RecvBuildingNtfGuildCmd"},
{50,51,"RecvBuildingSubmitCountGuildCmd"},
{50,52,"RecvChallengeUpdateNtfGuildCmd"},
{50,53,"RecvWelfareNtfGuildCmd"},
{50,54,"RecvGetWelfareGuildCmd"},
{50,55,"RecvBuildingLvupEffGuildCmd"},
{50,56,"RecvArtifactUpdateNtfGuildCmd"},
{50,57,"RecvArtifactProduceGuildCmd"},
{50,58,"RecvArtifactOptGuildCmd"},
{50,59,"RecvQueryGQuestGuildCmd"},
{50,60,"RecvTreasureActionGuildCmd"},
{50,61,"RecvQueryBuildingRankGuildCmd"},
{50,62,"RecvQueryTreasureResultGuildCmd"},
{50,63,"RecvQueryGCityShowInfoGuildCmd"},
{50,64,"RecvGvgOpenFireGuildCmd"},
{50,66,"RecvEnterPunishTimeNtfGuildCmd"},
{50,65,"RecvOpenRealtimeVoiceGuildCmd"},

{20,1,"RecvTeamTowerInfoCmd"},
{20,2,"RecvTeamTowerSummaryCmd"},
{20,3,"RecvTeamTowerInviteCmd"},
{20,4,"RecvTeamTowerReplyCmd"},
{20,5,"RecvEnterTower"},
{20,7,"RecvUserTowerInfoCmd"},
{20,8,"RecvTowerLayerSyncTowerCmd"},
{20,10,"RecvTowerInfoCmd"},

{6,1,"RecvPackageItem"},
{6,2,"RecvPackageUpdate"},
{6,3,"RecvItemUse"},
{6,4,"RecvPackageSort"},
{6,5,"RecvEquip"},
{6,6,"RecvSellItem"},
{6,7,"RecvEquipStrength"},
{6,9,"RecvProduce"},
{6,10,"RecvProduceDone"},
{6,11,"RecvEquipRefine"},
{6,12,"RecvEquipDecompose"},
{6,27,"RecvQueryDecomposeResultItemCmd"},
{6,13,"RecvQueryEquipData"},
{6,14,"RecvBrowsePackage"},
{6,15,"RecvEquipCard"},
{6,16,"RecvItemShow"},
{6,35,"nil"},
{6,17,"RecvEquipRepair"},
{6,18,"RecvHintNtf"},
{6,19,"RecvEnchantEquip"},
{6,20,"RecvProcessEnchantItemCmd"},
{6,21,"RecvEquipExchangeItemCmd"},
{6,22,"RecvOnOffStoreItemCmd"},
{6,23,"RecvPackSlotNtfItemCmd"},
{6,24,"RecvRestoreEquipItemCmd"},
{6,25,"RecvUseCountItemCmd"},
{6,28,"RecvExchangeCardItemCmd"},
{6,29,"RecvGetCountItemCmd"},
{6,30,"RecvSaveLoveLetterCmd"},
{6,31,"RecvItemDataShow"},
{6,32,"RecvLotteryCmd"},
{6,33,"RecvLotteryRecoveryCmd"},
{6,34,"RecvQueryLotteryInfo"},
{6,40,"RecvReqQuotaLogCmd"},
{6,41,"RecvReqQuotaDetailCmd"},
{6,42,"RecvEquipPosDataUpdate"},
{6,36,"RecvHighRefineMatComposeCmd"},
{6,37,"RecvHighRefineCmd"},
{6,38,"RecvNtfHighRefineDataCmd"},
{6,39,"RecvUpdateHighRefineDataCmd"},
{6,43,"RecvUseCodItemCmd"},
{6,44,"RecvAddJobLevelItemCmd"},
{6,46,"RecvLotterGivBuyCountCmd"},
{6,47,"RecvGiveWeddingDressCmd"},
{6,48,"RecvQuickStoreItemCmd"},
{6,49,"RecvQuickSellItemCmd"},
{6,50,"RecvEnchantTransItemCmd"},
{6,51,"RecvQueryLotteryHeadItemCmd"},
{6,52,"RecvLotteryRateQueryCmd"},

{1,4,"RecvRegResultUserCmd"},
{1,5,"RecvCreateCharUserCmd"},
{1,6,"RecvSnapShotUserCmd"},
{1,7,"RecvSelectRoleUserCmd"},
{1,8,"RecvLoginResultUserCmd"},
{1,9,"RecvDeleteCharUserCmd"},
{1,10,"RecvHeartBeatUserCmd"},
{1,11,"RecvServerTimeUserCmd"},
{1,12,"RecvGMDeleteCharUserCmd"},
{1,13,"RecvClientInfoUserCmd"},
{1,14,"RecvReqLoginUserCmd"},
{1,15,"RecvReqLoginParamUserCmd"},
{1,16,"RecvKickParamUserCmd"},
{1,17,"RecvCancelDeleteCharUserCmd"},
{1,18,"RecvClientFrameUserCmd"},
{1,19,"RecvSafeDeviceUserCmd"},
{1,20,"RecvConfirmAuthorizeUserCmd"},
{1,21,"RecvSyncAuthorizeGateCmd"},
{1,22,"RecvRealAuthorizeUserCmd"},
{1,23,"RecvRealAuthorizeServerCmd"},

{12,1,"RecvAddMapItem",ROM_RecvAddMapItem},
{12,2,"RecvPickupItem",ROM_RecvPLAYERGUIDSkip},
{12,3,"RecvAddMapUser",ROM_RecvSKIP},
{12,4,"RecvAddMapNpc"},
{12,5,"RecvAddMapTrap"},
{12,6,"RecvAddMapAct"},
{12,7,"RecvExitPointState"},
{12,8,"RecvMapCmdEnd"},
{12,9,"RecvNpcSearchRangeCmd"},
{12,10,"RecvUserHandsCmd"},
{12,11,"RecvSpEffectCmd"},
{12,12,"RecvUserHandNpcCmd"},
{12,13,"RecvGingerBreadNpcCmd"},
{12,14,"RecvGoCityGateMapCmd"},

{61,1,"RecvReqMyRoomMatchCCmd"},
{61,2,"RecvReqRoomListCCmd"},
{61,3,"RecvReqRoomDetailCCmd"},
{61,4,"RecvJoinRoomCCmd"},
{61,5,"RecvLeaveRoomCCmd"},
{61,7,"RecvNtfRoomStateCCmd"},
{61,8,"RecvNtfFightStatCCmd"},
{61,9,"RecvJoinFightingCCmd"},
{61,10,"RecvComboNotifyCCmd"},
{61,11,"RecvRevChallengeCCmd"},
{61,12,"RecvKickTeamCCmd"},
{61,13,"RecvFightConfirmCCmd"},
{61,14,"RecvPvpResultCCmd"},
{61,15,"RecvPvpTeamMemberUpdateCCmd"},
{61,16,"RecvPvpMemberDataUpdateCCmd"},
{61,17,"RecvNtfMatchInfoCCmd"},
{61,18,"RecvGodEndTimeCCmd"},
{61,19,"RecvNtfRankChangeCCmd"},
{61,20,"RecvOpenGlobalShopPanelCCmd"},
{61,21,"RecvTutorMatchResultNtfMatchCCmd"},
{61,22,"RecvTutorMatchResponseMatchCCmd"},

{9,1,"RecvGoCity"},
{9,2,"RecvSysMsg"},
{9,3,"RecvNpcDataSync",ROM_RecvSKIP},
{9,4,"RecvUserNineSyncCmd",ROM_RecvGUIDSkip},
{9,5,"RecvUserActionNtf 9_5",ROM_RecvCHARIDSkip},
{9,6,"RecvUserBuffNineSyncCmd",ROM_RecvGUIDSkip},
{9,7,"RecvExitPosUserCmd"},
{9,8,"RecvRelive"},
{9,9,"RecvVarUpdate"},
{9,10,"RecvTalkInfo"},
{9,11,"RecvServerTime"},
{9,14,"RecvEffectUserCmd"},
{9,15,"RecvMenuList"},
{9,16,"RecvNewMenu"},
{9,17,"RecvTeamInfoNine"},
{9,18,"RecvUsePortrait"},
{9,19,"RecvUseFrame"},
{9,20,"RecvNewPortraitFrame"},
{9,24,"RecvQueryPortraitListUserCmd"},
{9,25,"RecvUseDressing"},
{9,26,"RecvNewDressing"},
{9,27,"RecvDressingListUserCmd"},
{9,21,"RecvAddAttrPoint"},
{9,22,"RecvQueryShopGotItem"},
{9,23,"RecvUpdateShopGotItem"},
{9,29,"RecvOpenUI"},
{9,30,"RecvDbgSysMsg"},
{9,32,"RecvFollowTransferCmd"},
{9,33,"RecvCallNpcFuncCmd"},
{9,34,"RecvModelShow"},
{9,35,"RecvSoundEffectCmd"},
{9,36,"RecvPresetMsgCmd"},
{9,37,"RecvChangeBgmCmd"},
{9,38,"RecvQueryFighterInfo"},
{9,40,"RecvGameTimeCmd"},
{9,41,"RecvCDTimeUserCmd"},
{9,42,"RecvStateChange"},
{9,44,"RecvPhoto"},
{9,45,"RecvShakeScreen"},
{9,47,"RecvQueryShortcut"},
{9,48,"RecvPutShortcut"},
{9,49,"RecvNpcChangeAngle"},
{9,50,"RecvCameraFocus"},
{9,51,"RecvGoToListUserCmd"},
{9,52,"RecvGoToGearUserCmd"},
{9,12,"RecvNewTransMapCmd"},
{9,53,"RecvFollowerUser"},
{9,96,"RecvBeFollowUserCmd"},
{9,54,"RecvLaboratoryUserCmd"},
{9,57,"RecvGotoLaboratoryUserCmd"},
{9,56,"RecvExchangeProfession"},
{9,58,"RecvSceneryUserCmd"},
{9,59,"RecvGoMapQuestUserCmd"},
{9,60,"RecvGoMapFollowUserCmd"},
{9,61,"RecvUserAutoHitCmd"},
{9,62,"RecvUploadSceneryPhotoUserCmd"},
{9,80,"RecvDownloadSceneryPhotoUserCmd"},
{9,63,"RecvQueryMapArea"},
{9,64,"RecvNewMapAreaNtf"},
{9,66,"RecvBuffForeverCmd"},
{9,67,"RecvInviteJoinHandsUserCmd"},
{9,68,"RecvBreakUpHandsUserCmd"},
{9,95,"RecvHandStatusUserCmd"},
{9,69,"RecvQueryShow"},
{9,70,"RecvQueryMusicList"},
{9,71,"RecvDemandMusic"},
{9,72,"RecvCloseMusicFrame"},
{9,73,"RecvUploadOkSceneryUserCmd"},
{9,74,"RecvJoinHandsUserCmd"},
{9,75,"RecvQueryTraceList"},
{9,76,"RecvUpdateTraceList"},
{9,77,"RecvSetDirection"},
{9,82,"RecvBattleTimelenUserCmd"},
{9,83,"RecvSetOptionUserCmd"},
{9,84,"RecvQueryUserInfoUserCmd"},
{9,85,"RecvCountDownTickUserCmd"},
{9,86,"RecvItemMusicNtfUserCmd"},
{9,87,"RecvShakeTreeUserCmd"},
{9,88,"RecvTreeListUserCmd"},
{9,89,"RecvActivityNtfUserCmd"},
{9,91,"RecvQueryZoneStatusUserCmd"},
{9,92,"RecvJumpZoneUserCmd"},
{9,93,"RecvItemImageUserNtfUserCmd"},
{9,97,"RecvInviteFollowUserCmd"},
{9,98,"RecvChangeNameUserCmd"},
{9,99,"RecvChargePlayUserCmd"},
{9,100,"RecvRequireNpcFuncUserCmd"},
{9,101,"RecvCheckSeatUserCmd"},
{9,102,"RecvNtfSeatUserCmd"},
{9,114,"RecvYoyoSeatUserCmd"},
{9,115,"RecvShowSeatUserCmd"},
{9,103,"RecvSetNormalSkillOptionUserCmd"},
{9,106,"RecvNewSetOptionUserCmd"},
{9,104,"RecvUnsolvedSceneryNtfUserCmd"},
{9,105,"RecvNtfVisibleNpcUserCmd"},
{9,107,"RecvUpyunAuthorizationCmd"},
{9,108,"RecvTransformPreDataCmd"},
{9,109,"RecvUserRenameCmd"},
{9,111,"RecvBuyZenyCmd"},
{9,112,"RecvCallTeamerUserCmd"},
{9,113,"RecvCallTeamerReplyUserCmd"},
{9,116,"RecvSpecialEffectCmd"},
{9,117,"RecvMarriageProposalCmd"},
{9,118,"RecvMarriageProposalReplyCmd"},
{9,119,"RecvUploadWeddingPhotoUserCmd"},
{9,120,"RecvMarriageProposalSuccessCmd"},
{9,121,"RecvInviteeWeddingStartNtfUserCmd"},
{9,128,"RecvKFCShareUserCmd"},
{9,130,"RecvCheckRelationUserCmd"},
{9,129,"RecvTwinsActionUserCmd"},
{9,122,"RecvShowServantUserCmd"},
{9,123,"RecvReplaceServantUserCmd"},
{9,124,"RecvServantService"},
{9,125,"RecvRecommendServantUserCmd"},
{9,126,"RecvReceiveServantUserCmd"},
{9,127,"RecvServantRewardStatusUserCmd"},
{9,131,"RecvProfessionQueryUserCmd"},
{9,132,"RecvProfessionBuyUserCmd"},
{9,133,"RecvProfessionChangeUserCmd"},
{9,134,"RecvUpdateRecordInfoUserCmd"},
{9,135,"RecvSaveRecordUserCmd"},
{9,136,"RecvLoadRecordUserCmd"},
{9,137,"RecvChangeRecordNameUserCmd"},
{9,138,"RecvBuyRecordSlotUserCmd"},
{9,139,"RecvDeleteRecordUserCmd"},
{9,140,"RecvUpdateBranchInfoUserCmd"},
{9,110,"RecvEnterCapraActivityCmd"},
{9,142,"RecvInviteWithMeUserCmd"},
{9,143,"RecvQueryAltmanKillUserCmd"},
{9,144,"RecvBoothReqUserCmd"},
{9,145,"RecvBoothInfoSyncUserCmd"},

{80,1,"RecvTaiwanFbLikeProgressCmd"},
{80,2,"RecvTaiwanFbLikeUserRedeemCmd"},
{81,1,"RecvOverseasPhotoUploadCmd"},
{81,2,"RecvOverseasPhotoPathPrefixCmd"},
{80,10,"RecvTaiwanFbShareProgressCmd"},
{80,11,"RecvTaiwanFbShareRedeemCmd"},

{30,1,"RecvPhotoQueryListCmd"},
{30,2,"RecvPhotoOptCmd"},
{30,3,"RecvPhotoUpdateNtf"},
{30,4,"RecvFrameActionPhotoCmd"},
{30,5,"RecvQueryFramePhotoListPhotoCmd"},
{30,6,"RecvQueryUserPhotoListPhotoCmd"},
{30,7,"RecvUpdateFrameShowPhotoCmd"},
{30,8,"RecvFramePhotoUpdatePhotoCmd"},
{30,9,"nil"},
{30,10,"nil"},
{30,11,"nil"},

{66,1,"RecvInvitePveCardCmd"},
{66,2,"RecvReplyPveCardCmd"},
{66,3,"RecvEnterPveCardCmd"},
{66,4,"RecvQueryCardInfoCmd"},
{66,5,"RecvSelectPveCardCmd"},
{66,6,"RecvSyncProcessPveCardCmd"},
{66,7,"RecvUpdateProcessPveCardCmd"},
{66,8,"RecvBeginFirePveCardCmd"},
{66,9,"RecvFinishPlayCardCmd"},
{66,10,"RecvPlayPveCardCmd"},

{8,1,"RecvQuestList"},
{8,2,"RecvQuestUpdate"},
{8,5,"RecvQuestStepUpdate"},
{8,3,"RecvQuestAction"},
{8,4,"RecvRunQuestStep"},
{8,6,"RecvQuestTrace"},
{8,7,"RecvQuestDetailList"},
{8,8,"RecvQuestDetailUpdate"},
{8,9,"RecvQuestRaidCmd"},
{8,10,"RecvQuestCanAcceptListChange"},
{8,11,"RecvVisitNpcUserCmd"},
{8,12,"RecvQueryOtherData"},
{8,13,"RecvQueryWantedInfoQuestCmd"},
{8,14,"RecvInviteHelpAcceptQuestCmd"},
{8,16,"RecvInviteAcceptQuestCmd"},
{8,15,"RecvReplyHelpAccelpQuestCmd"},
{8,17,"RecvQueryWorldQuestCmd"},
{8,18,"RecvQuestGroupTraceQuestCmd"},
{8,19,"RecvHelpQuickFinishBoardQuestCmd"},

{57,1,"RecvBriefPendingListRecordTradeCmd"},
{57,3,"RecvDetailPendingListRecordTradeCmd"},
{57,4,"RecvItemSellInfoRecordTradeCmd"},
{57,7,"RecvMyPendingListRecordTradeCmd"},
{57,9,"RecvMyTradeLogRecordTradeCmd"},
{57,27,"RecvTakeLogCmd"},
{57,28,"RecvAddNewLog"},
{57,29,"RecvFetchNameInfoCmd"},
{57,14,"RecvReqServerPriceRecordTradeCmd"},
{57,15,"RecvBuyItemRecordTradeCmd"},
{57,20,"RecvSellItemRecordTradeCmd"},
{57,22,"RecvCancelItemRecordTrade"},
{57,23,"RecvResellPendingRecordTrade"},
{57,24,"RecvPanelRecordTrade"},
{57,25,"RecvListNtfRecordTrade"},
{57,26,"RecvHotItemidRecordTrade"},
{57,30,"RecvNtfCanTakeCountTradeCmd"},
{57,31,"RecvGiveTradeCmd"},
{57,33,"RecvAcceptTradeCmd"},
{57,34,"RecvRefuseTradeCmd"},
{57,32,"RecvReqGiveItemInfoCmd"},
{57,35,"RecvCheckPackageSizeTradeCmd"},
{57,36,"RecvQucikTakeLogTradeCmd"},
{57,37,"RecvQueryItemCountTradeCmd"},
{57,38,"RecvLotteryGiveCmd"},
{57,39,"RecvTodayFinanceRank"},
{57,40,"RecvTodayFinanceDetail"},
{57,41,"RecvBoothPlayerPendingListCmd"},
{57,42,"RecvUpdateOrderTradeCmd"},

{27,1,"RecvAuguryInvite"},
{27,2,"RecvAuguryInviteReply"},
{27,3,"RecvAuguryChat"},
{27,4,"RecvAuguryTitle"},
{27,5,"RecvAuguryAnswer"},
{27,6,"RecvAuguryQuit"},

{32,1,"RecvBeingSkillQuery"},
{32,2,"RecvBeingSkillUpdate"},
{32,3,"RecvBeingSkillLevelUp"},
{32,4,"RecvBeingInfoQuery"},
{32,5,"RecvBeingInfoUpdate"},
{32,7,"RecvBeingSwitchState"},
{32,6,"RecvBeingOffCmd"},
{32,8,"RecvChangeBodyBeingCmd"},

{29,1,"RecvCookStateNtf"},
{29,2,"RecvPrepareCook"},
{29,3,"RecvSelectCookType"},
{29,4,"RecvStartCook"},
{29,5,"RecvPutFood"},
{29,6,"RecvEditFoodPower"},
{29,8,"RecvQueryFoodNpcInfo"},
{29,9,"RecvStartEat"},
{29,10,"RecvStopEat"},
{29,7,"RecvEatProgressNtf"},
{29,11,"RecvFoodInfoNtf"},
{29,16,"RecvUpdateFoodInfo"},
{29,12,"RecvUnlockRecipeNtf"},
{29,13,"RecvQueryFoodManualData"},
{29,14,"RecvNewFoodDataNtf"},
{29,15,"RecvClickFoodManualData"},

{22,1,"RecvNewInter"},
{22,2,"RecvAnswer"},
{22,3,"RecvQuery"},

{23,1,"RecvQueryVersion"},
{23,2,"RecvQueryManualData"},
{23,3,"RecvPointSync"},
{23,4,"RecvManualUpdate"},
{23,5,"RecvGetAchieveReward"},
{23,6,"RecvUnlock"},
{23,7,"RecvSkillPointSync"},
{23,8,"RecvLevelSync"},
{23,9,"RecvGetQuestReward"},
{23,10,"RecvStoreManualCmd"},
{23,11,"RecvGetManualCmd"},
{23,12,"RecvGroupActionManualCmd"},
{23,13,"RecvQueryUnsolvedPhotoManualCmd"},
{23,14,"RecvUpdateSolvedPhotoManualCmd"},

{10,1,"RecvPetList"},
{10,2,"RecvFireCatPetCmd"},
{10,3,"RecvHireCatPetCmd"},
{10,4,"RecvEggHatchPetCmd"},
{10,5,"RecvEggRestorePetCmd"},
{10,6,"RecvCatchValuePetCmd"},
{10,7,"RecvCatchResultPetCmd"},
{10,8,"RecvCatchPetPetCmd"},
{10,12,"RecvCatchPetGiftPetCmd"},
{10,9,"RecvPetInfoPetCmd"},
{10,10,"RecvPetInfoUpdatePetCmd"},
{10,11,"RecvPetOffPetCmd"},
{10,13,"RecvGetGiftPetCmd"},
{10,14,"RecvEquipOperPetCmd"},
{10,15,"RecvEquipUpdatePetCmd"},
{10,16,"RecvQueryPetAdventureListPetCmd"},
{10,17,"RecvPetAdventureResultNtfPetCmd"},
{10,18,"RecvStartAdventurePetCmd"},
{10,19,"RecvGetAdventureRewardPetCmd"},
{10,20,"RecvQueryBattlePetCmd"},
{10,21,"RecvHandPetPetCmd"},
{10,22,"RecvGiveGiftPetCmd"},
{10,23,"RecvUnlockNtfPetCmd"},
{10,24,"RecvResetSkillPetCmd"},
{10,26,"RecvChangeNamePetCmd"},
{10,27,"RecvSwitchSkillPetCmd"},
{10,28,"RecvUnlockPetWorkManualPetCmd"},
{10,29,"RecvStartWorkPetCmd"},
{10,30,"RecvStopWorkPetCmd"},
{10,31,"RecvQueryPetWorkManualPetCmd"},
{10,32,"RecvQueryPetWorkDataPetCmd"},
{10,33,"RecvGetPetWorkRewardPetCmd"},
{10,34,"RecvWorkSpaceUpdate"},
{10,35,"RecvPetExtraUpdatePetCmd"},

{21,1,"RecvQuerySeal"},
{21,2,"RecvUpdateSeal"},
{21,3,"RecvSealTimer"},
{21,4,"RecvBeginSeal"},
{21,5,"RecvEndSeal"},
{21,6,"RecvSealUserLeave"},
{21,7,"RecvSealQueryList"},
{21,8,"RecvSealAcceptCmd"},

{18,1,"RecvGameTipCmd"},
{18,2,"RecvBrowseRedTipCmd"},
{18,3,"RecvAddRedTip"},

{55,1,"RecvQueryAllMail"},
{55,2,"RecvMailUpdate"},
{55,3,"RecvGetMailAttach"},

{52,1,"RecvBuyShopItem"},
{52,2,"RecvQueryShopConfigCmd"},
{52,3,"RecvQueryQuickBuyConfigCmd"},
{52,4,"RecvQueryShopSoldCountCmd"},
{52,5,"RecvShopDataUpdateCmd"},
{52,6,"RecvUpdateShopConfigCmd"},

{56,1,"RecvQuerySocialData"},
{56,2,"RecvFindUser"},
{56,3,"RecvSocialUpdate"},
{56,4,"RecvSocialDataUpdate"},
{56,5,"RecvFrameStatusSocialCmd"},
{56,6,"RecvUseGiftCodeSocialCmd"},
{56,7,"RecvOperateQuerySocialCmd"},
{56,8,"RecvOperateTakeSocialCmd"},
{56,9,"RecvQueryDataNtfSocialCmd"},
{56,10,"RecvOperActivityNtfSocialCmd"},
{56,11,"RecvAddRelation"},
{56,12,"RecvRemoveRelation"},
{56,13,"RecvQueryRecallListSocialCmd"},
{56,14,"RecvRecallFriendSocialCmd"},
{56,15,"RecvAddRelationResultSocialCmd"},
{56,16,"RecvQueryChargeVirginCmd"},
{56,17,"RecvQueryUserInfoCmd"},

{51,1,"RecvTeamList"},
{51,2,"RecvTeamDataUpdate"},
{51,3,"RecvTeamMemberUpdate"},
{51,4,"RecvTeamApplyUpdate"},
{51,5,"RecvCreateTeam"},
{51,6,"RecvInviteMember"},
{51,7,"RecvProcessTeamInvite"},
{51,8,"RecvTeamMemberApply"},
{51,9,"RecvProcessTeamApply"},
{51,10,"RecvKickMember"},
{51,11,"RecvExchangeLeader"},
{51,12,"RecvExitTeam"},
{51,13,"RecvEnterTeam"},
{51,14,"RecvMemberPosUpdate"},
{51,15,"RecvMemberDataUpdate"},
{51,16,"RecvLockTarget"},
{51,17,"RecvTeamSummon"},
{51,18,"RecvClearApplyList"},
{51,19,"RecvQuickEnter"},
{51,20,"RecvSetTeamOption"},
{51,21,"RecvQueryUserTeamInfoTeamCmd"},
{51,22,"RecvSetMemberOptionTeamCmd"},
{51,23,"RecvQuestWantedQuestTeamCmd"},
{51,24,"RecvUpdateWantedQuestTeamCmd"},
{51,25,"RecvAcceptHelpWantedTeamCmd"},
{51,26,"RecvUpdateHelpWantedTeamCmd"},
{51,27,"RecvQueryHelpWantedTeamCmd"},
{51,28,"RecvQueryMemberCatTeamCmd"},
{51,29,"RecvMemberCatUpdateTeam"},

{7,1,"RecvReqSkillData"},
{7,2,"RecvSkillUpdate"},
{7,3,"RecvLevelupSkill"},
{7,4,"RecvEquipSkill"},
{7,5,"RecvResetSkill"},
{7,6,"RecvSkillValidPos"},
{7,7,"RecvChangeSkillCmd"},
{7,8,"RecvUpSkillInfoSkillCmd"},
{7,9,"RecvSelectRuneSkillCmd"},
{7,10,"RecvMarkSkillNpcSkillCmd"},
{7,11,"RecvTriggerSkillNpcSkillCmd"},
{7,12,"RecvSkillOptionSkillCmd"},
{7,13,"RecvDynamicSkillCmd"},
{7,14,"RecvUpdateDynamicSkillCmd"},

{67,1,"RecvTeamRaidInviteCmd"},
{67,2,"RecvTeamRaidReplyCmd"},
{67,3,"RecvTeamRaidEnterCmd"},
{67,4,"RecvTeamRaidAltmanShowCmd"},

{31,1,"RecvTutorTaskUpdateNtf"},
{31,2,"RecvTutorTaskQueryCmd"},
{31,3,"RecvTutorTaskTeacherRewardCmd"},
{31,4,"RecvTutorGrowRewardUpdateNtf"},
{31,5,"RecvTutorGetGrowRewardCmd"},

{25,1,"RecvFirstActionUserEvent"},
{25,2,"RecvDamageNpcUserEvent",ROM_RecvUSERIDSkip},
{25,3,"RecvNewTitle"},
{25,4,"RecvAllTitle"},
{25,5,"RecvUpdateRandomUserEvent"},
{25,6,"RecvBuffDamageUserEvent"},
{25,7,"RecvChargeNtfUserEvent"},
{25,8,"RecvChargeQueryCmd"},
{25,9,"RecvDepositCardInfo"},
{25,10,"RecvDelTransformUserEvent"},
{25,11,"RecvInviteCatFailUserEvent"},
{25,12,"RecvTrigNpcFuncUserEvent"},
{25,13,"RecvSystemStringUserEvent"},
{25,14,"RecvHandCatUserEvent"},
{25,15,"RecvChangeTitle"},
{25,16,"RecvQueryChargeCnt"},
{25,17,"RecvNTFMonthCardEnd"},
{25,18,"RecvLoveLetterUse"},
{25,19,"RecvQueryActivityCnt"},
{25,20,"RecvUpdateActivityCnt"},
{25,23,"RecvNtfVersionCardInfo"},
{25,24,"RecvDieTimeCountEventCmd"},
{25,22,"RecvGetFirstShareRewardUserEvent"},
{25,25,"RecvQueryResetTimeEventCmd"},
{25,26,"RecvInOutActEventCmd"},
{25,27,"RecvUserEventMailCmd"},

{53,1,"RecvWeatherChange"},
{53,2,"RecvSkyChange"},

{65,1,"RecvReqWeddingDateListCCmd"},
{65,3,"RecvReqWeddingOneDayListCCmd"},
{65,4,"RecvReqWeddingInfoCCmd"},
{65,5,"RecvReserveWeddingDateCCmd"},
{65,6,"RecvNtfReserveWeddingDateCCmd"},
{65,7,"RecvReplyReserveWeddingDateCCmd"},
{65,8,"RecvGiveUpReserveCCmd"},
{65,9,"RecvReqDivorceCCmd"},
{65,10,"RecvUpdateWeddingManualCCmd"},
{65,11,"RecvBuyWeddingPackageCCmd"},
{65,12,"RecvBuyWeddingRingCCmd"},
{65,13,"RecvWeddingInviteCCmd"},
{65,14,"RecvUploadWeddingPhotoCCmd"},
{65,15,"RecvCheckCanReserveCCmd"},
{65,16,"RecvReqPartnerInfoCCmd"},
{65,17,"RecvNtfWeddingInfoCCmd"},
{65,18,"RecvInviteBeginWeddingCCmd"},
{65,19,"RecvReplyBeginWeddingCCmd"},
{65,20,"RecvGoToWeddingPosCCmd"},
{65,21,"RecvQuestionWeddingCCmd"},
{65,22,"RecvAnswerWeddingCCmd"},
{65,23,"RecvWeddingEventMsgCCmd"},
{65,24,"RecvWeddingOverCCmd"},
{65,25,"RecvWeddingSwitchQuestionCCmd"},
{65,26,"RecvEnterRollerCoasterCCmd"},
{65,27,"RecvDivorceRollerCoasterInviteCCmd"},
{65,28,"RecvDivorceRollerCoasterReplyCCmd"},
{65,29,"RecvEnterWeddingMapCCmd"},
{65,30,"RecvMissyouInviteWedCCmd"},
{65,31,"RecvMisccyouReplyWedCCmd"},
{65,32,"RecvWeddingCarrierCCmd"},

{5,22,"ChangeDress"},
{5,13,"AddMapNpc"},
{5,16,"MoveTo"},
{3,1,"OldUserAttrSyncCmd"},
{5,1,"UserAttrSyncCmd"},
{5,27,"SkillBroadcast",ROM_RecvCHARIDSkip},
{5,12,"MapOtherUserIn"},
{5,23,"MapChange"},
{5,18,"MapOtherUserOut",ROM_RecvSKIP},
{5,38,"MapObjectData"},

{5,32,"NpcDie"},
{5,37,"NpcChangeHp"},

{5,33,"RecvUserActionNtf 5_33"},
{5,42,"RecvGoToUserCmd"},

};

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

]]

