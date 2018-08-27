#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <dlfcn.h>
#include <stdarg.h>
#include <string>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include "../util/logger.h"
#include "../util/util.hpp"
#include "../util/payload.hpp"
#include "../util/ProcessScanner.hpp"
#include "../luac/luascript.h"
#include "MonoObjectIndex.hpp"
#include "lua_upgrade.hpp"
#include "shell.hpp"
#include "upgrade.hpp"

std::string CreatureDataMonoObject::ToString(ProcessScanner &pscan)
{
    std::string name = pscan.readMonoString(this->name);
    std::string title = pscan.readMonoString(this->title);
    std::string graphicPrefeb = pscan.readMonoString(this->graphicPrefeb);
    std::string creatureIcon = pscan.readMonoString(this->creatureIcon);
    std::string description = pscan.readMonoString(this->description);
    std::string out;
    char tmp[1024];
    sprintf(tmp,"{%d,%d,%d,%d,%d,%f,%f,%f,%d,%f,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%d,%d,0,0,0,0,0,\"%s\",\"%s\",\"%s\",\"%s\"},",
	creatureData.creatureId,
	creatureData.combatType,
	creatureData.baseHp,
	creatureData.hpf,
	creatureData.baseMp,
	creatureData.mpf,
	creatureData.baseMpRegen,
	creatureData.mprf,
	creatureData.baseAttackPoint,
	creatureData.apf,
	creatureData.movePoint,
	creatureData.baseDr,
	creatureData.drf,
	creatureData.baseCr,
	creatureData.crf,
	creatureData.baseDgr,
	creatureData.dgrf,
	creatureData.baseHr,
	creatureData.hrf,
	creatureData.baseCar,
	creatureData.carf,
	creatureData.baseCadr,
	creatureData.cadrf,
	creatureData.mastery,
	creatureData.skill0,
	creatureData.skill1,
	creatureData.skill2,
	creatureData.skill3,
	creatureData.skill4,
	name.c_str(),
	graphicPrefeb.c_str(),
	creatureIcon.c_str(),
	description.c_str()
    );
    out = tmp;
    return out;
}

 std::string DungeonData::ToString(ProcessScanner& pscan){
    char tmp[1024];
    std::vector<std::string> vStringList;
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_dgName)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_epiName)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_bgTheme)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_mapPrefeb)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_mainDesc)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_dgDesc)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_bgmPlayerStart)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_bgmPlayerBattle)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_bgmPlayerEnd)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_dungeonWeather)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_dungeonRepresenttile)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_dgId);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_regionId);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_dgType);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_dgNo);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_miNo);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_costStamina);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_joinLimit);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_endTurn);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_extraLevel);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_extraSkillLevel);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_main01);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_recomGrade);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_recomLevel);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_combatpower);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_strategy);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_maxMon);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_dungeonGeneId);vStringList.push_back(tmp);
    std::string ret;
    ret += "{";
    ret += ConcatStrings(vStringList,",");
    ret += "}";
    return ret;
}
 
 std::string EnchantData::ToString(ProcessScanner& pscan)
 {
    char tmp[1024];
    std::vector<std::string> vStringList;
    sprintf(tmp,"%d",this->_weaponKind);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_grade);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_enchantNum);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_ap);vStringList.push_back(tmp);
    sprintf(tmp,"%f",this->_mastery);vStringList.push_back(tmp);
    sprintf(tmp,"%f",this->_cr);vStringList.push_back(tmp);
    sprintf(tmp,"%f",this->_dr);vStringList.push_back(tmp);
    sprintf(tmp,"%d",this->_hp);vStringList.push_back(tmp);
    sprintf(tmp,"%f",this->_dgr);vStringList.push_back(tmp);
    sprintf(tmp,"%f",this->_hr);vStringList.push_back(tmp);
    sprintf(tmp,"%f",this->_car);vStringList.push_back(tmp);
    sprintf(tmp,"%f",this->_cadr);vStringList.push_back(tmp);
    std::string ret;
    ret += "{";
    ret += ConcatStrings(vStringList,",");
    ret += "},";
    return ret;
}

std::string FaceData::ToString(ProcessScanner& pscan){
    char tmp[1024];
    std::vector<std::string> vStringList;
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_faceillust)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_emo1)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_emo2)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_emo3)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_emo4)).c_str());vStringList.push_back(tmp);
    sprintf(tmp,"%f",this->_emo1x);vStringList.push_back(tmp);
    sprintf(tmp,"%f",this->_emo1y);vStringList.push_back(tmp);
    sprintf(tmp,"%f",this->_emo2x);vStringList.push_back(tmp);
    sprintf(tmp,"%f",this->_emo2y);vStringList.push_back(tmp);
    sprintf(tmp,"%f",this->_emo3x);vStringList.push_back(tmp);
    sprintf(tmp,"%f",this->_emo3y);vStringList.push_back(tmp);
    sprintf(tmp,"%f",this->_emo4x);vStringList.push_back(tmp);
    sprintf(tmp,"%f",this->_emo4y);vStringList.push_back(tmp);
    std::string ret;
    ret += "{";
    ret += ConcatStrings(vStringList,",");
    ret += "},";
    return ret;
 } 


std::string GameConfig::ToString(ProcessScanner& pscan){
	char tmp[1024];
	std::vector<std::string> vStringList;
	sprintf(tmp,"%d",this->_nativePlatformOption);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_isGuestMode);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_logOutType);vStringList.push_back(tmp);
	sprintf(tmp,"%f",this->_timeScale);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_isTimeStop);vStringList.push_back(tmp);
	sprintf(tmp,"%f",this->_dungeonTimeScale_ref);vStringList.push_back(tmp);
	sprintf(tmp,"%f",this->_dungeonTimeScale);vStringList.push_back(tmp);
	sprintf(tmp,"%f",this->restoreTimeScale);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_isUsedAuto);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->isAutoReserverLordSkill);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->isAutoPlay_ref);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_doesGameDirectionShow);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_clearDirectRegionID);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_isShowedFiveStar);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_openDirectDungeonID);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_creatureIconMode);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_showOnlyHaveHero);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_creatureSortType);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_smallInventorySortIndex);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_mercenaryInventorySortIndex);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_equipSortType);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_equipNormalDictionarySortIndex);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_equipSetDictionarySortIndex);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_equipPlatinumDictionarySortIndex);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_monsterSortType);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_friendSortType);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_subScenarioReadInde);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_detailStatViewPercent);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_guildSortType);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_language);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_country);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_serverNode);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_reservedServerNode);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->isChangingServerNode);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_chattingChannel);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_chattingWithGuild);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_chattingGuildAlarm);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->guildRaidRewardReceiveButton);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_isShowPromotion);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_ageLimitAgreement);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_policyTermsAgreement);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_autoSelectExpeditionMercenary);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_autoSelectMercenary);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_optionSoundBGM);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_optionSoundEffect);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_optionShake);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_optionScene);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_optionGraphicQuality);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_optionGraphicFrame);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_optionDungeonUI);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_dungeonEnterEventRewardType);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->statusForEnterToy);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_isEnteredToy);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_isShowTitleAtFirstTime);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_isShowLobbyAtFirstTime);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_isConnectAccoutnAtTitle);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_isInspectServer);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_requireGoogleGamesLogin);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_gameRunCount);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->gcCollect);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->objectCaching);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->assetBundleCaching);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->unloadAsset);vStringList.push_back(tmp);
	//sprintf(tmp,"%d",this-><isAutoPlay>k__BackingField);vStringList.push_back(tmp);
	std::string ret;
	ret += "{";
	ret += ConcatStrings(vStringList,",");
	ret += "},";
	return ret;
}
void GameConfig::Show(ProcessScanner& pscan){
	printf("_nativePlatformOption=%08X\n",this->_nativePlatformOption);
	printf("_isGuestMode=%d\n",this->_isGuestMode);
	printf("_logOutType=%d\n",this->_logOutType);
	printf("_timeScale=%f\n",this->_timeScale);
	printf("_isTimeStop=%d\n",this->_isTimeStop);
	printf("_dungeonTimeScale_ref=%f\n",this->_dungeonTimeScale_ref);
	printf("_dungeonTimeScale=%f\n",this->_dungeonTimeScale);
	printf("restoreTimeScale=%f\n",this->restoreTimeScale);
	printf("_isUsedAuto=%d\n",this->_isUsedAuto);
	printf("isAutoReserverLordSkill=%d\n",this->isAutoReserverLordSkill);
	printf("isAutoPlay_ref=%d\n",this->isAutoPlay_ref);
	printf("_doesGameDirectionShow=%d\n",this->_doesGameDirectionShow);
	printf("_clearDirectRegionID=%d\n",this->_clearDirectRegionID);
	printf("_isShowedFiveStar=%d\n",this->_isShowedFiveStar);
	printf("_openDirectDungeonID=%d\n",this->_openDirectDungeonID);
	printf("_creatureIconMode=%d\n",this->_creatureIconMode);
	printf("_showOnlyHaveHero=%d\n",this->_showOnlyHaveHero);
	printf("_creatureSortType=%d\n",this->_creatureSortType);
	printf("_smallInventorySortIndex=%d\n",this->_smallInventorySortIndex);
	printf("_mercenaryInventorySortIndex=%d\n",this->_mercenaryInventorySortIndex);
	printf("_equipSortType=%d\n",this->_equipSortType);
	printf("_equipNormalDictionarySortIndex=%d\n",this->_equipNormalDictionarySortIndex);
	printf("_equipSetDictionarySortIndex=%d\n",this->_equipSetDictionarySortIndex);
	printf("_equipPlatinumDictionarySortIndex=%d\n",this->_equipPlatinumDictionarySortIndex);
	printf("_monsterSortType=%d\n",this->_monsterSortType);
	printf("_friendSortType=%d\n",this->_friendSortType);
	printf("_subScenarioReadInde=%d\n",this->_subScenarioReadInde);
	printf("_detailStatViewPercent=%d\n",this->_detailStatViewPercent);
	printf("_guildSortType=%d\n",this->_guildSortType);
	printf("_language=%d\n",this->_language);
	printf("_country=%d\n",this->_country);
	printf("_serverNode=%d\n",this->_serverNode);
	printf("_reservedServerNode=%d\n",this->_reservedServerNode);
	printf("isChangingServerNode=%d\n",this->isChangingServerNode);
	printf("_chattingChannel=%d\n",this->_chattingChannel);
	printf("_chattingWithGuild=%d\n",this->_chattingWithGuild);
	printf("_chattingGuildAlarm=%d\n",this->_chattingGuildAlarm);
	printf("guildRaidRewardReceiveButton=%d\n",this->guildRaidRewardReceiveButton);
	printf("_isShowPromotion=%d\n",this->_isShowPromotion);
	printf("_ageLimitAgreement=%d\n",this->_ageLimitAgreement);
	printf("_policyTermsAgreement=%d\n",this->_policyTermsAgreement);
	printf("_autoSelectExpeditionMercenary=%d\n",this->_autoSelectExpeditionMercenary);
	printf("_autoSelectMercenary=%d\n",this->_autoSelectMercenary);
	printf("_optionSoundBGM=%d\n",this->_optionSoundBGM);
	printf("_optionSoundEffect=%d\n",this->_optionSoundEffect);
	printf("_optionShake=%d\n",this->_optionShake);
	printf("_optionScene=%d\n",this->_optionScene);
	printf("_optionGraphicQuality=%d\n",this->_optionGraphicQuality);
	printf("_optionGraphicFrame=%d\n",this->_optionGraphicFrame);
	printf("_optionDungeonUI=%d\n",this->_optionDungeonUI);
	printf("_dungeonEnterEventRewardType=%d\n",this->_dungeonEnterEventRewardType);
	printf("statusForEnterToy=%d\n",this->statusForEnterToy);
	printf("_isEnteredToy=%d\n",this->_isEnteredToy);
	printf("_isShowTitleAtFirstTime=%d\n",this->_isShowTitleAtFirstTime);
	printf("_isShowLobbyAtFirstTime=%d\n",this->_isShowLobbyAtFirstTime);
	printf("_isConnectAccoutnAtTitle=%d\n",this->_isConnectAccoutnAtTitle);
	printf("_isInspectServer=%d\n",this->_isInspectServer);
	printf("_requireGoogleGamesLogin=%d\n",this->_requireGoogleGamesLogin);
	printf("_gameRunCount=%d\n",this->_gameRunCount);
	printf("gcCollect=%d\n",this->gcCollect);
	printf("objectCaching=%d\n",this->objectCaching);
	printf("assetBundleCaching=%d\n",this->assetBundleCaching);
	printf("unloadAsset=%d\n",this->unloadAsset);
}

std::string GradeReward::ToString(ProcessScanner& pscan){
	 char tmp[1024];
	 std::vector<std::string> vStringList;
	 sprintf(tmp,"%d",this->_creatureId);vStringList.push_back(tmp);
	 sprintf(tmp,"%d",this->_creatureGrade);vStringList.push_back(tmp);
	 sprintf(tmp,"%d",this->_hpBonus);vStringList.push_back(tmp);
	 sprintf(tmp,"%d",this->_mpBonus);vStringList.push_back(tmp);
	 sprintf(tmp,"%d",this->_apBonus);vStringList.push_back(tmp);
	 sprintf(tmp,"%f",this->_drBonus);vStringList.push_back(tmp);
	 sprintf(tmp,"%f",this->_crBonus);vStringList.push_back(tmp);
	 sprintf(tmp,"%f",this->_dgrBonus);vStringList.push_back(tmp);
	 sprintf(tmp,"%f",this->_hrBonus);vStringList.push_back(tmp);
	 std::string ret;
	 ret += "{";
	 ret += ConcatStrings(vStringList,",");
	 ret += "},";
	 return ret;
 }
 void GradeReward::Show(ProcessScanner& pscan){
	 printf("_creatureId=%d\n",this->_creatureId);
	 printf("_creatureGrade=%d\n",this->_creatureGrade);
	 printf("_hpBonus=%d\n",this->_hpBonus);
	 printf("_mpBonus=%d\n",this->_mpBonus);
	 printf("_apBonus=%d\n",this->_apBonus);
	 printf("_drBonus=%f\n",this->_drBonus);
	 printf("_crBonus=%f\n",this->_crBonus);
	 printf("_dgrBonus=%f\n",this->_dgrBonus);
	 printf("_hrBonus=%f\n",this->_hrBonus);
 }

std::string MapObjectData::ToString(ProcessScanner& pscan){
	char tmp[1024];
	std::vector<std::string> vStringList;
	sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_objectName)).c_str());vStringList.push_back(tmp);
	sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_graphic)).c_str());vStringList.push_back(tmp);
	sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_objectString)).c_str());vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_objectId);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_objectType);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_objectGroup);vStringList.push_back(tmp);
	sprintf(tmp,"%f",this->_summonRate);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_hp);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_turnskip);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_getitem);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_attacked);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_movable);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_actioncameraskip);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_deathSkill);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_lifeSkill);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_lifeSkillUseTurn);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_lifeSkillUseTime);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_lifeSkillStart);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_skillTurnTiming);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_lifeSkillEnd);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_endEtcfx);vStringList.push_back(tmp);
	std::string ret;
	ret += "{";
	ret += ConcatStrings(vStringList,",");
	ret += "},";
	return ret;
}

void MapObjectData::Show(ProcessScanner& pscan){
	printf("_objectName=[%s]\n",SaveCString(pscan.readMonoString(this->_objectName)).c_str());
	printf("_graphic=[%s]\n",SaveCString(pscan.readMonoString(this->_graphic)).c_str());
	printf("_objectString=[%s]\n",SaveCString(pscan.readMonoString(this->_objectString)).c_str());
	printf("_objectId=%d\n",this->_objectId);
	printf("_objectType=%d\n",this->_objectType);
	printf("_objectGroup=%d\n",this->_objectGroup);
	printf("_summonRate=%f\n",this->_summonRate);
	printf("_hp=%d\n",this->_hp);
	printf("_turnskip=%d\n",this->_turnskip);
	printf("_getitem=%d\n",this->_getitem);
	printf("_attacked=%d\n",this->_attacked);
	printf("_movable=%d\n",this->_movable);
	printf("_actioncameraskip=%d\n",this->_actioncameraskip);
	printf("_deathSkill=%d\n",this->_deathSkill);
	printf("_lifeSkill=%d\n",this->_lifeSkill);
	printf("_lifeSkillUseTurn=%d\n",this->_lifeSkillUseTurn);
	printf("_lifeSkillUseTime=%d\n",this->_lifeSkillUseTime);
	printf("_lifeSkillStart=%d\n",this->_lifeSkillStart);
	printf("_skillTurnTiming=%d\n",this->_skillTurnTiming);
	printf("_lifeSkillEnd=%d\n",this->_lifeSkillEnd);
	printf("_endEtcfx=%d\n",this->_endEtcfx);
}

std::string RepeatPlayManager::ToString(ProcessScanner& pscan){
	char tmp[1024];
	std::vector<std::string> vStringList;
	sprintf(tmp,"%d",this->_rewardList);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_isRepeating);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_repeatCount);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_clearCount);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_repeatCountAfterLogin);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_accmulateCostStamina);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_repeatPlayStopReason);vStringList.push_back(tmp);
	std::string ret;
	ret += "{";
	ret += ConcatStrings(vStringList,",");
	ret += "},";
	return ret;
}
void RepeatPlayManager::Show(ProcessScanner& pscan){
	printf("_rewardList=%08X\n",this->_rewardList);
	printf("_isRepeating=%d\n",this->_isRepeating);
	printf("_repeatCount=%d\n",this->_repeatCount);
	printf("_clearCount=%d\n",this->_clearCount);
	printf("_repeatCountAfterLogin=%d\n",this->_repeatCountAfterLogin);
	printf("_accmulateCostStamina=%d\n",this->_accmulateCostStamina);
	printf("_repeatPlayStopReason=%d\n",this->_repeatPlayStopReason);
}

std::string GUIManager::ToString(ProcessScanner& pscan){
	char tmp[1024];
	std::vector<std::string> vStringList;
	sprintf(tmp,"%d",this->uiAnchor);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->uiTopPanel);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->uiRoot);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_rewardManager);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_composeDirectManager);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_dungeonGUIManager);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_touchEffectManager);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_tutorialGUIManager);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_menuNotifyManager);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_guiPrefabListManager);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_UIRootGameObject);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_uibattleInfo);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_uiStrategyInfo);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_uiGameGUI);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_uiLaboratoryGUI);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->memberModels);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->memberScales);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_visitReserveMode);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_visitMode);vStringList.push_back(tmp);
	sprintf(tmp,"%lld",this->_visitingLordID);vStringList.push_back(tmp);
	sprintf(tmp,"%f",this->visitingDataCachingTime);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->isLoading);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->isContentAlram);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_requestEnableCount);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->isStrongWayHidePopup);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->isActiveOffDirect);vStringList.push_back(tmp);
	sprintf(tmp,"%f",this->_uiWidth);vStringList.push_back(tmp);
	sprintf(tmp,"%f",this->_uiHeight);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_packagePopupID);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_isNeedBackHeroDetail);vStringList.push_back(tmp);
	sprintf(tmp,"%f",this->playOnTime);vStringList.push_back(tmp);
	sprintf(tmp,"%lld",this->notHaveCretureInstanceID);vStringList.push_back(tmp);
	std::string ret;
	ret += "{";
	ret += ConcatStrings(vStringList,",");
	ret += "},";
	return ret;
}
void GUIManager::Show(ProcessScanner& pscan){
	printf("uiAnchor=%08X\n",this->uiAnchor);
	printf("uiTopPanel=%08X\n",this->uiTopPanel);
	printf("uiRoot=%08X\n",this->uiRoot);
	printf("_rewardManager=%08X\n",this->_rewardManager);
	printf("_composeDirectManager=%08X\n",this->_composeDirectManager);
	printf("_dungeonGUIManager=%08X\n",this->_dungeonGUIManager);
	printf("_touchEffectManager=%08X\n",this->_touchEffectManager);
	printf("_tutorialGUIManager=%08X\n",this->_tutorialGUIManager);
	printf("_menuNotifyManager=%08X\n",this->_menuNotifyManager);
	printf("_guiPrefabListManager=%08X\n",this->_guiPrefabListManager);
	printf("_UIRootGameObject=%08X\n",this->_UIRootGameObject);
	printf("_uibattleInfo=%08X\n",this->_uibattleInfo);
	printf("_uiStrategyInfo=%08X\n",this->_uiStrategyInfo);
	printf("_uiGameGUI=%08X\n",this->_uiGameGUI);
	printf("_uiLaboratoryGUI=%08X\n",this->_uiLaboratoryGUI);
	printf("memberModels=%08X\n",this->memberModels);
	printf("memberScales=%08X\n",this->memberScales);
	printf("_visitReserveMode=%d\n",this->_visitReserveMode);
	printf("_visitMode=%d\n",this->_visitMode);
	printf("_visitingLordID=%lld\n",this->_visitingLordID);
	printf("visitingDataCachingTime=%f\n",this->visitingDataCachingTime);
	printf("isLoading=%d\n",this->isLoading);
	printf("isContentAlram=%d\n",this->isContentAlram);
	printf("_requestEnableCount=%d\n",this->_requestEnableCount);
	printf("isStrongWayHidePopup=%d\n",this->isStrongWayHidePopup);
	printf("isActiveOffDirect=%d\n",this->isActiveOffDirect);
	printf("_uiWidth=%f\n",this->_uiWidth);
	printf("_uiHeight=%f\n",this->_uiHeight);
	printf("_packagePopupID=%d\n",this->_packagePopupID);
	printf("_isNeedBackHeroDetail=%d\n",this->_isNeedBackHeroDetail);
	printf("playOnTime=%f\n",this->playOnTime);
	printf("notHaveCretureInstanceID=%lld\n",this->notHaveCretureInstanceID);
}

std::string GameApp::ToString(ProcessScanner& pscan){
	char tmp[1024];
	std::vector<std::string> vStringList;
	sprintf(tmp,"%d",this->loadingGUI);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->backgroundGo);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_territoryIndex);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_stageIndex);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_isDebugMode);vStringList.push_back(tmp);
	sprintf(tmp,"%f",this->timeWhenStop);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_gameSceneType);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->_isCreateData);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->isShowGUI);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->isShowMap);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->isShowAlly);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->isShowEnemy);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->isShowBackground);vStringList.push_back(tmp);
	sprintf(tmp,"%d",this->isReqPotential);vStringList.push_back(tmp);
	std::string ret;
	ret += "{";
	ret += ConcatStrings(vStringList,",");
	ret += "},";
	return ret;
}
void GameApp::Show(ProcessScanner& pscan){
	printf("loadingGUI=%08X\n",this->loadingGUI);
	printf("backgroundGo=%08X\n",this->backgroundGo);
	printf("_territoryIndex=%d\n",this->_territoryIndex);
	printf("_stageIndex=%d\n",this->_stageIndex);
	printf("_isDebugMode=%d\n",this->_isDebugMode);
	printf("timeWhenStop=%f\n",this->timeWhenStop);
	printf("_gameSceneType=%d\n",this->_gameSceneType);
	printf("_isCreateData=%d\n",this->_isCreateData);
	printf("isShowGUI=%d\n",this->isShowGUI);
	printf("isShowMap=%d\n",this->isShowMap);
	printf("isShowAlly=%d\n",this->isShowAlly);
	printf("isShowEnemy=%d\n",this->isShowEnemy);
	printf("isShowBackground=%d\n",this->isShowBackground);
	printf("isReqPotential=%d\n",this->isReqPotential);
}



