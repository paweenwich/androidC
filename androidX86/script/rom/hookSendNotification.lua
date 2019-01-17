function HOOK_SendNotification(self,p1,p2)
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
    LogDebug("SEND: " .. tostring(data));
    NetProtocol._SendProto(data);
end;

function HOOK_Send(id1, id2, data)
    LogDebug("SEND: [" .. id1 .. '] [' .. id2 .. '] ' .. tostring(data));
    NetProtocol._Send(data);
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

{12,1,"RecvAddMapItem"},
{12,2,"RecvPickupItem"},
{12,3,"RecvAddMapUser"},
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
{9,3,"RecvNpcDataSync"},
{9,4,"RecvUserNineSyncCmd"},
{9,5,"RecvUserActionNtf"},
{9,6,"RecvUserBuffNineSyncCmd"},
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
{25,2,"RecvDamageNpcUserEvent"},
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
{5,27,"SkillBroadcast"},
{5,12,"MapOtherUserIn"},
{5,23,"MapChange"},
{5,18,"MapOtherUserOut"},
{5,38,"MapObjectData"},

{5,32,"NpcDie"},
{5,37,"NpcChangeHp"},

{5,33,"RecvUserActionNtf"},
{5,42,"RecvGoToUserCmd"},

};

function ROM_HandleRecv(id1, id2, data)
	for i=1,#ROM_Packets do
		local pkt = ROM_Packets[i];
		if id1 == pkt[1] and id2 == pkt[2] then
			LogDebug("RECV: " .. pkt[3] .. " " .. tostring(data));
			return;
		end;
	end;
	LogDebug("RECV: [" .. id1 .. '] [' .. id2 .. '] [' .. tostring(data) ..']');
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
--[[

]]

