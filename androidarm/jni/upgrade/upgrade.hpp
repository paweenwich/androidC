#pragma pack(1)

struct HeroData {
    unsigned int creatureId;
    char *title;
    char *name; 
    unsigned int combatType;
    unsigned int baseHp;
};



struct _CreatureData {
    unsigned int creatureId;
    unsigned int combatType;
    unsigned int baseHp;
    unsigned int hpf;
    unsigned int baseMp;
    float mpf;
    float baseMpRegen;
    float mprf;
    unsigned int baseAttackPoint;
    float apf;
    unsigned int movePoint;
    float baseDr;
    float drf;
    float baseCr;
    float crf;
    float baseDgr;
    float dgrf;
    float baseHr;
    float hrf;
    float baseCar;
    float carf;
    float baseCadr;
    float cadrf;
    float mastery;
    int skill0;
    int skill1;
    int skill2;
    int skill3;
    int skill4;
//    int levelType;
//    int creatureType;
//    int moveType0;
//    int moveType1;
//    int moveType2;
    
};

struct MonsterData {
    int monsterId;
    int creatureid;
    int cognitionRange;
    int boss;
    int level;
    float hpRate;
    float apRate;
    int hp;
    int mp;
    int ap;
    float dr;
    float cr;
    float dodge;
    float hr;
    float car;
    float cadr;
    int movePoint;
    int skill0Lv;
    int skill1Lv;
    int skill2Lv;
    int passiveLv;
    int tribalism;
    float moveSpeed;
};

struct CreatureData {
    int creatureId;
    int combatType;
    int baseHp;
    int hpf;
    int baseMp;
    float mpf;
    float baseMpRegen;
    float mprf;
    int baseAttackPoint;
    float apf;
    int movePoint;
    float baseDr;
    float drf;
    float baseCr;
    float crf;
    float baseDgr;
    float dgrf;
    float baseHr;
    float hrf;
    float baseCar;
    float carf;
    float baseCadr;
    float cadrf;
    float mastery;
    int skill0;
    int skill1;
    int skill2;
    int skill3;
    int skill4;
    int levelType;
    int creatureType;
    int moveType0;
    int moveType1;
    int moveType2;
    char *name;
    char *graphicPrefeb;
    char *creatureIcon;
    char *description;
};


struct SearchData {
    unsigned int creatureId;
    unsigned int combatType;    
    unsigned int baseHp;
};

struct MonsterSearchData {
    unsigned int monsterId;
    unsigned int creatureid;    
};

class CreatureDataManager: MonoObject {
public:    
    unsigned int unk1;
    unsigned int unk2;
    unsigned int _data;
    
};

class CreatureDataMonoObject: MonoObject {
public:    
    unsigned int title;
    unsigned int name;
    unsigned int graphicPrefeb;
    unsigned int creatureIcon;
    unsigned int description;
    _CreatureData creatureData;
    std::string ToString(ProcessScanner &pscan);
};


class DungeonData: MonoObject{
public:
        unsigned int _dgName; //8 String
        unsigned int _epiName; //12 String
        unsigned int _bgTheme; //16 String
        unsigned int _mapPrefeb; //20 String
        unsigned int _mainDesc; //24 String
        unsigned int _dgDesc; //28 String
        unsigned int _bgmPlayerStart; //32 String
        unsigned int _bgmPlayerBattle; //36 String
        unsigned int _bgmPlayerEnd; //40 String
        unsigned int _dungeonWeather; //44 String
        unsigned int _dungeonRepresenttile; //48 String
        unsigned int _dgId; //52 Int
        unsigned int _regionId; //56 Int
        unsigned char _dgType; //60 UByte
        unsigned char _dgNo; //61 UByte
        unsigned char _miNo; //62 UByte
        unsigned char _costStamina; //63 UByte
        unsigned char _joinLimit; //64 UByte
        unsigned char _endTurn; //65 UByte
        unsigned char unk0[2];
        unsigned int _extraLevel; //68 Int
        unsigned char _extraSkillLevel; //72 UByte
        unsigned char unk1[3];
        unsigned int _main01; //76 Int
        unsigned char _recomGrade; //80 UByte
        unsigned char _recomLevel; //81 UByte
        unsigned char unk2[2];
        unsigned int _combatpower; //84 Int
        unsigned char _strategy; //88 UByte
        unsigned char unk3[3];
        unsigned int _maxMon; //92 Int
        unsigned int _dungeonGeneId; //96 Int
        std::string ToString(ProcessScanner &pscan);
};

class EnchantData: MonoObject{
public:
    unsigned char _weaponKind; //8 UByte
    unsigned char _grade; //9 UByte
    unsigned char _enchantNum; //10 UByte
    unsigned char unk0[1];
    unsigned int _ap; //12 Int
    float _mastery; //16 float
    float _cr; //20 float
    float _dr; //24 float
    unsigned int _hp; //28 Int
    float _dgr; //32 float
    float _hr; //36 float
    float _car; //40 float
    float _cadr; //44 float
    std::string ToString(ProcessScanner& pscan);
};

class FaceData: MonoObject{
public:
    unsigned int _faceillust; //8 String
    unsigned int _emo1; //12 String
    unsigned int _emo2; //16 String
    unsigned int _emo3; //20 String
    unsigned int _emo4; //24 String
    float _emo1x; //28 float
    float _emo1y; //32 float
    float _emo2x; //36 float
    float _emo2y; //40 float
    float _emo3x; //44 float
    float _emo3y; //48 float
    float _emo4x; //52 float
    float _emo4y; //56 float
    std::string ToString(ProcessScanner& pscan);
};

class GameConfig: MonoObject{
public:
        unsigned int _nativePlatformOption; //8 Class
        unsigned char _isGuestMode; //12 Bool
        unsigned char unk0[3];
        unsigned int _logOutType; //16 VALUE
        float _timeScale; //20 float
        unsigned char _isTimeStop; //24 Bool
        unsigned char unk1[3];
        float _dungeonTimeScale_ref; //28 float
        float _dungeonTimeScale; //32 float
        float restoreTimeScale; //36 float
        unsigned char _isUsedAuto; //40 Bool
        unsigned char isAutoReserverLordSkill; //41 Bool
        unsigned char isAutoPlay_ref; //42 Bool
        unsigned char unk2[1];
        unsigned int _doesGameDirectionShow; //44 Int
        unsigned int _clearDirectRegionID; //48 Int
        unsigned int _isShowedFiveStar; //52 Int
        unsigned int _openDirectDungeonID; //56 Int
        unsigned int _creatureIconMode; //60 VALUE
        unsigned char _showOnlyHaveHero; //64 Bool
        unsigned char unk3[3];
        unsigned int _creatureSortType; //68 VALUE
        unsigned int _smallInventorySortIndex; //72 Int
        unsigned int _mercenaryInventorySortIndex; //76 Int
        unsigned int _equipSortType; //80 VALUE
        unsigned int _equipNormalDictionarySortIndex; //84 Int
        unsigned int _equipSetDictionarySortIndex; //88 Int
        unsigned int _equipPlatinumDictionarySortIndex; //92 Int
        unsigned int _monsterSortType; //96 VALUE
        unsigned int _friendSortType; //100 VALUE
        unsigned int _subScenarioReadInde; //104 Int
        unsigned char _detailStatViewPercent; //108 Bool
        unsigned char unk4[3];
        unsigned int _guildSortType; //112 VALUE
        unsigned int _language; //116 VALUE
        unsigned int _country; //120 VALUE
        unsigned int _serverNode; //124 Int
        unsigned int _reservedServerNode; //128 VALUE
        unsigned char isChangingServerNode; //132 Bool
        unsigned char unk5[3];
        unsigned int _chattingChannel; //136 Int
        unsigned char _chattingWithGuild; //140 Bool
        unsigned char _chattingGuildAlarm; //141 Bool
        unsigned char guildRaidRewardReceiveButton; //142 Bool
        unsigned char unk6[1];
        unsigned int _isShowPromotion; //144 Int
        unsigned int _ageLimitAgreement; //148 Int
        unsigned int _policyTermsAgreement; //152 Int
        unsigned int _autoSelectExpeditionMercenary; //156 Int
        unsigned int _autoSelectMercenary; //160 Int
        unsigned int _optionSoundBGM; //164 Int
        unsigned int _optionSoundEffect; //168 Int
        unsigned int _optionShake; //172 Int
        unsigned int _optionScene; //176 Int
        unsigned int _optionGraphicQuality; //180 Int
        unsigned int _optionGraphicFrame; //184 Int
        unsigned int _optionDungeonUI; //188 Int
        unsigned int _dungeonEnterEventRewardType; //192 VALUE
        unsigned int statusForEnterToy; //196 VALUE
        unsigned int _isEnteredToy; //200 Int
        unsigned char _isShowTitleAtFirstTime; //204 Bool
        unsigned char _isShowLobbyAtFirstTime; //205 Bool
        unsigned char _isConnectAccoutnAtTitle; //206 Bool
        unsigned char _isInspectServer; //207 Bool
        unsigned int _requireGoogleGamesLogin; //208 VALUE
        unsigned int _gameRunCount; //212 UInt
        unsigned char gcCollect; //216 Bool
        unsigned char objectCaching; //217 Bool
        unsigned char assetBundleCaching; //218 Bool
        unsigned char unloadAsset; //219 Bool
        //unsigned char <isAutoPlay>k__BackingField; //220 Bool
        std::string ToString(ProcessScanner& pscan);
	void Show(ProcessScanner& pscan);
	
};

class GradeReward: MonoObject{
public:
        unsigned int _creatureId; //8 Int
        unsigned char _creatureGrade; //12 UByte
        unsigned char unk0[3];
        unsigned int _hpBonus; //16 Int
        unsigned int _mpBonus; //20 Int
        unsigned int _apBonus; //24 Int
        float _drBonus; //28 float
        float _crBonus; //32 float
        float _dgrBonus; //36 float
        float _hrBonus; //40 float
        std::string ToString(ProcessScanner& pscan);
        void Show(ProcessScanner& pscan);
};

class MapObjectData: MonoObject{
public:
        unsigned int _objectName; //8 String
        unsigned int _graphic; //12 String
        unsigned int _objectString; //16 String
        unsigned int _objectId; //20 Int
        unsigned char _objectType; //24 UByte
        unsigned char _objectGroup; //25 UByte
        unsigned char unk0[2];
        float _summonRate; //28 float
        unsigned int _hp; //32 Int
        unsigned char _turnskip; //36 UByte
        unsigned char _getitem; //37 UByte
        unsigned char _attacked; //38 UByte
        unsigned char _movable; //39 UByte
        unsigned char _actioncameraskip; //40 UByte
        unsigned char unk1[3];
        unsigned int _deathSkill; //44 Int
        unsigned int _lifeSkill; //48 Int
        unsigned char _lifeSkillUseTurn; //52 UByte
        unsigned char _lifeSkillUseTime; //53 UByte
        unsigned char _lifeSkillStart; //54 UByte
        unsigned char _skillTurnTiming; //55 UByte
        unsigned char _lifeSkillEnd; //56 UByte
        unsigned char unk2[3];
        unsigned int _endEtcfx; //60 Int
        std::string ToString(ProcessScanner& pscan);
        void Show(ProcessScanner& pscan);
};

class RepeatPlayManager: MonoObject{
public:
        unsigned int _rewardList; //8 List
        unsigned char _isRepeating; //12 Bool
        unsigned char unk0[3];
        unsigned int _repeatCount; //16 Int
        unsigned int _clearCount; //20 Int
        unsigned int _repeatCountAfterLogin; //24 Int
        unsigned int _accmulateCostStamina; //28 Int
        unsigned int _repeatPlayStopReason; //32 VALUE
        std::string ToString(ProcessScanner& pscan);
        void Show(ProcessScanner& pscan);
};

class GUIManager: MonoObject{
public:
        unsigned char unk0[8];
        unsigned int uiAnchor; //16 Class
        unsigned int uiTopPanel; //20 Class
        unsigned int uiRoot; //24 Class
        unsigned int _rewardManager; //28 Class
        unsigned int _composeDirectManager; //32 Class
        unsigned int _dungeonGUIManager; //36 Class
        unsigned int _touchEffectManager; //40 Class
        unsigned int _tutorialGUIManager; //44 Class
        unsigned int _menuNotifyManager; //48 Class
        unsigned int _guiPrefabListManager; //52 Class
        unsigned int _UIRootGameObject; //56 Class
        unsigned int _uibattleInfo; //60 Class
        unsigned int _uiStrategyInfo; //64 Class
        unsigned int _uiGameGUI; //68 Class
        unsigned int _uiLaboratoryGUI; //72 Class
        unsigned int memberModels; //76 List
        unsigned int memberScales; //80 List
        unsigned int _visitReserveMode; //84 VALUE
        unsigned int _visitMode; //88 VALUE
        long long int _visitingLordID; //92 Int64
        double visitingDataCachingTime; //100 doube
        unsigned char isLoading; //108 Bool
        unsigned char isContentAlram; //109 Bool
        unsigned char unk1[2];
        unsigned int _requestEnableCount; //112 Int
        unsigned char isStrongWayHidePopup; //116 Bool
        unsigned char isActiveOffDirect; //117 Bool
        unsigned char unk2[2];
        float _uiWidth; //120 float
        float _uiHeight; //124 float
        unsigned int _packagePopupID; //128 Int
        unsigned char _isNeedBackHeroDetail; //132 Bool
        unsigned char unk3[3];
        float playOnTime; //136 float
        long long int notHaveCretureInstanceID; //140 Int64
        std::string ToString(ProcessScanner& pscan);
        void Show(ProcessScanner& pscan);
};

class GameApp: MonoObject{
public:
        unsigned char unk0[8];
        unsigned int loadingGUI; //16 Class
        unsigned int backgroundGo; //20 Class
        unsigned int _territoryIndex; //24 Int
        unsigned int _stageIndex; //28 Int
        unsigned char _isDebugMode; //32 Bool
        unsigned char unk1[3];
        float timeWhenStop; //36 float
        unsigned char _gameSceneType; //40 VALUE
        unsigned char _isCreateData; //41 Bool
        unsigned char isShowGUI; //42 Bool
        unsigned char isShowMap; //43 Bool
        unsigned char isShowAlly; //44 Bool
        unsigned char isShowEnemy; //45 Bool
        unsigned char isShowBackground; //46 Bool
        unsigned char isReqPotential; //47 Bool
        std::string ToString(ProcessScanner& pscan);
        void Show(ProcessScanner& pscan);
};

#include "fwtMonoObject.hpp"

BattleManager GetBattleManager(ProcessScanner &pscan);

CreatureData *FindCreatureByID(int creatureID);
struct HeroData * FindHeroByName(char *name);
unsigned int ParseInt(char *data);

void shell(int pid,char *param);

extern struct HeroData heros[];
extern struct MonsterData monsters[];
extern struct CreatureData creatures[];
extern _CreatureData paramCharacterData;
extern bool flgShouldUpdate;
extern unsigned int luaResultInt;
extern LuaShell luaShell;
extern char luaMonsterList[1024];