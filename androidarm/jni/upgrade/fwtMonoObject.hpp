/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   fwtMonoObject.hpp
 * Author: kwang
 *
 * Created on September 14, 2016, 10:35 AM
 */

#ifndef FWTMONOOBJECT_HPP
#define FWTMONOOBJECT_HPP

class GameStage: MonoObject{
public:
        unsigned char unk0[8];
        unsigned int _stagePanel; //16 Class
        unsigned int stageSubjectPath; //20 String
        unsigned int _startMap; //24 Class
        unsigned int _currentMap; //28 Class
        unsigned int _backgroundmgr; //32 Class
        unsigned int _gameEventObjs; //36 SZARRAY
        unsigned int _camps; //40 List
        unsigned int _items; //44 List
        unsigned int _npcs; //48 List
        unsigned int _resurrectablePlayers; //52 SZARRAY
        unsigned int turnController; //56 Class
        unsigned int _skipButton; //60 Class
        unsigned int _scenarioTitle; //64 Class
        unsigned int dialogGUI; //68 Class
        unsigned int preserveSpawnList; //72 List
        unsigned int preserveGosDic; //76 List
        unsigned int _intrudedSpawnObjects; //80 List
        unsigned int _gameEventPanel; //84 Class
        unsigned int tk2dcollectionData; //88 Class
        unsigned int loseReason; //92 String
        unsigned int OnReadyGameEvent; //96 Class
        unsigned int OnEndGameEvent; //100 Class
        unsigned int OnStartTurnEvent; //104 Class
        unsigned int OnCampEndTurnEvent; //108 Class
        unsigned int OnEndTurnMemberEvent; //112 Class
        unsigned int OnRegisterSpawnMemberEvent; //116 Class
        unsigned int OnLoadProgressEvent; //120 Class
        unsigned int _missionMgr_k__BackingField; //124 Class
        unsigned int _forwardEffectObj_k__BackingField; //128 Class
        unsigned int _missonPanelTrans_k__BackingField; //132 Class
        unsigned char _stageType; //136 VALUE
        unsigned char _isClearedStage; //137 Bool
        unsigned char _HasSubMisson; //138 Bool
        unsigned char _firstTurnCamp; //139 VALUE
        unsigned int _currentCampIndex; //140 Int
        unsigned int _playerCampIndex; //144 Int
        unsigned int _opponentCampIndex; //148 Int
        unsigned int _mapobjCampIndex; //152 Int
        unsigned int _systemCampIndex; //156 Int
        unsigned char _currentTurnNo; //160 VALUE
        unsigned char unk1[3];
        unsigned char _isClearMission; //164 Bool
        unsigned char _winCampType; //165 VALUE
        unsigned char _playerSequence; //166 UByte
        unsigned char _opponentSequence; //167 UByte
        unsigned int _stageOpponentCount; //168 Int
        unsigned int _resurrectablePlayerCount; //172 Int
        unsigned int membernameindex; //176 Int
        unsigned char dialogEventType; //180 VALUE
        unsigned char unk2[3];
        unsigned int despawnCount; //184 Int
        unsigned char hasExcuteGameEventStart; //188 Bool
        unsigned char battleExitState; //189 VALUE
        unsigned char _IsFinishLoadDungeon_k__BackingField; //190 Bool
        unsigned char _isStartGame_k__BackingField; //191 Bool
        unsigned char _isDontOpenGUI_k__BackingField; //192 Bool
        unsigned char _isAlwaysCritical_k__BackingField; //193 Bool
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->_stagePanel);vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->stageSubjectPath)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_startMap);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_currentMap);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_backgroundmgr);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_gameEventObjs);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_camps);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_items);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_npcs);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_resurrectablePlayers);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->turnController);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skipButton);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_scenarioTitle);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->dialogGUI);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->preserveSpawnList);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->preserveGosDic);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_intrudedSpawnObjects);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_gameEventPanel);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->tk2dcollectionData);vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->loseReason)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnReadyGameEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnEndGameEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnStartTurnEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnCampEndTurnEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnEndTurnMemberEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnRegisterSpawnMemberEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnLoadProgressEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_missionMgr_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_forwardEffectObj_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_missonPanelTrans_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_stageType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_isClearedStage);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_HasSubMisson);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_firstTurnCamp);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_currentCampIndex);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_playerCampIndex);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_opponentCampIndex);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_mapobjCampIndex);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_systemCampIndex);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_currentTurnNo);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_isClearMission);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_winCampType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_playerSequence);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_opponentSequence);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_stageOpponentCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_resurrectablePlayerCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->membernameindex);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->dialogEventType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->despawnCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->hasExcuteGameEventStart);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->battleExitState);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_IsFinishLoadDungeon_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_isStartGame_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_isDontOpenGUI_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_isAlwaysCritical_k__BackingField);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("_stagePanel=%08X\n",this->_stagePanel);
                printf("stageSubjectPath=[%s]\n",SaveCString(pscan.readMonoString(this->stageSubjectPath)).c_str());
                printf("_startMap=%08X\n",this->_startMap);
                printf("_currentMap=%08X\n",this->_currentMap);
                printf("_backgroundmgr=%08X\n",this->_backgroundmgr);
                printf("_gameEventObjs=%d\n",this->_gameEventObjs);
                printf("_camps=%08X\n",this->_camps);
                printf("_items=%08X\n",this->_items);
                printf("_npcs=%08X\n",this->_npcs);
                printf("_resurrectablePlayers=%d\n",this->_resurrectablePlayers);
                printf("turnController=%08X\n",this->turnController);
                printf("_skipButton=%08X\n",this->_skipButton);
                printf("_scenarioTitle=%08X\n",this->_scenarioTitle);
                printf("dialogGUI=%08X\n",this->dialogGUI);
                printf("preserveSpawnList=%08X\n",this->preserveSpawnList);
                printf("preserveGosDic=%08X\n",this->preserveGosDic);
                printf("_intrudedSpawnObjects=%08X\n",this->_intrudedSpawnObjects);
                printf("_gameEventPanel=%08X\n",this->_gameEventPanel);
                printf("tk2dcollectionData=%08X\n",this->tk2dcollectionData);
                printf("loseReason=[%s]\n",SaveCString(pscan.readMonoString(this->loseReason)).c_str());
                printf("OnReadyGameEvent=%08X\n",this->OnReadyGameEvent);
                printf("OnEndGameEvent=%08X\n",this->OnEndGameEvent);
                printf("OnStartTurnEvent=%08X\n",this->OnStartTurnEvent);
                printf("OnCampEndTurnEvent=%08X\n",this->OnCampEndTurnEvent);
                printf("OnEndTurnMemberEvent=%08X\n",this->OnEndTurnMemberEvent);
                printf("OnRegisterSpawnMemberEvent=%08X\n",this->OnRegisterSpawnMemberEvent);
                printf("OnLoadProgressEvent=%08X\n",this->OnLoadProgressEvent);
                printf("_missionMgr_k__BackingField=%08X\n",this->_missionMgr_k__BackingField);
                printf("_forwardEffectObj_k__BackingField=%08X\n",this->_forwardEffectObj_k__BackingField);
                printf("_missonPanelTrans_k__BackingField=%08X\n",this->_missonPanelTrans_k__BackingField);
                printf("_stageType=%d\n",this->_stageType);
                printf("_isClearedStage=%d\n",this->_isClearedStage);
                printf("_HasSubMisson=%d\n",this->_HasSubMisson);
                printf("_firstTurnCamp=%d\n",this->_firstTurnCamp);
                printf("_currentCampIndex=%d\n",this->_currentCampIndex);
                printf("_playerCampIndex=%d\n",this->_playerCampIndex);
                printf("_opponentCampIndex=%d\n",this->_opponentCampIndex);
                printf("_mapobjCampIndex=%d\n",this->_mapobjCampIndex);
                printf("_systemCampIndex=%d\n",this->_systemCampIndex);
                printf("_currentTurnNo=%d\n",this->_currentTurnNo);
                printf("_isClearMission=%d\n",this->_isClearMission);
                printf("_winCampType=%d\n",this->_winCampType);
                printf("_playerSequence=%d\n",this->_playerSequence);
                printf("_opponentSequence=%d\n",this->_opponentSequence);
                printf("_stageOpponentCount=%d\n",this->_stageOpponentCount);
                printf("_resurrectablePlayerCount=%d\n",this->_resurrectablePlayerCount);
                printf("membernameindex=%d\n",this->membernameindex);
                printf("dialogEventType=%d\n",this->dialogEventType);
                printf("despawnCount=%d\n",this->despawnCount);
                printf("hasExcuteGameEventStart=%d\n",this->hasExcuteGameEventStart);
                printf("battleExitState=%d\n",this->battleExitState);
                printf("_IsFinishLoadDungeon_k__BackingField=%d\n",this->_IsFinishLoadDungeon_k__BackingField);
                printf("_isStartGame_k__BackingField=%d\n",this->_isStartGame_k__BackingField);
                printf("_isDontOpenGUI_k__BackingField=%d\n",this->_isDontOpenGUI_k__BackingField);
                printf("_isAlwaysCritical_k__BackingField=%d\n",this->_isAlwaysCritical_k__BackingField);
        }
};

class OccupyProcess: MonoObject{
public:
        unsigned int wholeOcuppyCount; //8 Int
        unsigned int opponentOccupyCount; //12 Int
        unsigned int playerOccupyCount; //16 Int
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->wholeOcuppyCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->opponentOccupyCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->playerOccupyCount);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("wholeOcuppyCount=%d\n",this->wholeOcuppyCount);
                printf("opponentOccupyCount=%d\n",this->opponentOccupyCount);
                printf("playerOccupyCount=%d\n",this->playerOccupyCount);
        }
};


class GameMap: MonoObject{
public:
        unsigned char unk0[8];
        unsigned int _boundaryTileTop; //16 Class UnityEngine.GameObject
        unsigned int _boundaryTileBottom; //20 Class UnityEngine.GameObject
        unsigned int _boundaryTileLeft; //24 Class UnityEngine.GameObject
        unsigned int _boundaryTileRight; //28 Class UnityEngine.GameObject
        unsigned int tiles; //32 Array GameMapTile
        unsigned int _HasTiles; //36 SZARRAY PathPoint
        unsigned int _portals; //40 SZARRAY System.Collections.Generic.List`1
        unsigned int _occupyTiles; //44 SZARRAY System.Collections.Generic.List`1
        unsigned int pathGridwithHeight; //48 SZARRAY System.Byte
        unsigned int pathFinder; //52 Class PathFinderFast
        unsigned int _switchedTiles; //56 List System.Collections.Generic.List`1
        unsigned int unableToSpawnTiles; //60 List System.Collections.Generic.List`1
        unsigned int unabltToSpawnCreatureProprty; //64 List System.Collections.Generic.List`1
        unsigned int _mapWidth; //68 Int
        unsigned int _mapLength; //72 Int
        unsigned int _mapHeight; //76 Int
        unsigned int _blockWidth; //80 Int
        unsigned int _blockLength; //84 Int
        unsigned int _blockHeight; //88 Int
        float _blockSlopeAngle; //92 float
        unsigned int _gridLength; //96 Int
        unsigned int _gridWidth; //100 Int
        OccupyProcess _OccupyProcessOfTiles; //104 VALUE size=12
        float TileComponentHeightOffset; //116 float
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->_boundaryTileTop);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_boundaryTileBottom);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_boundaryTileLeft);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_boundaryTileRight);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->tiles);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_HasTiles);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_portals);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_occupyTiles);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->pathGridwithHeight);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->pathFinder);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_switchedTiles);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->unableToSpawnTiles);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->unabltToSpawnCreatureProprty);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_mapWidth);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_mapLength);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_mapHeight);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_blockWidth);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_blockLength);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_blockHeight);vStringList.push_back(tmp);
                sprintf(tmp,"%f",this->_blockSlopeAngle);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_gridLength);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_gridWidth);vStringList.push_back(tmp);
                sprintf(tmp,"%f",this->TileComponentHeightOffset);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("_boundaryTileTop=%08X\n",this->_boundaryTileTop);
                printf("_boundaryTileBottom=%08X\n",this->_boundaryTileBottom);
                printf("_boundaryTileLeft=%08X\n",this->_boundaryTileLeft);
                printf("_boundaryTileRight=%08X\n",this->_boundaryTileRight);
                printf("tiles=%08X\n",this->tiles);
                printf("_HasTiles=%08X\n",this->_HasTiles);
                printf("_portals=%08X\n",this->_portals);
                printf("_occupyTiles=%08X\n",this->_occupyTiles);
                printf("pathGridwithHeight=%08X\n",this->pathGridwithHeight);
                printf("pathFinder=%08X\n",this->pathFinder);
                printf("_switchedTiles=%08X\n",this->_switchedTiles);
                printf("unableToSpawnTiles=%08X\n",this->unableToSpawnTiles);
                printf("unabltToSpawnCreatureProprty=%08X\n",this->unabltToSpawnCreatureProprty);
                printf("_mapWidth=%d\n",this->_mapWidth);
                printf("_mapLength=%d\n",this->_mapLength);
                printf("_mapHeight=%d\n",this->_mapHeight);
                printf("_blockWidth=%d\n",this->_blockWidth);
                printf("_blockLength=%d\n",this->_blockLength);
                printf("_blockHeight=%d\n",this->_blockHeight);
                printf("_blockSlopeAngle=%f\n",this->_blockSlopeAngle);
                printf("_gridLength=%d\n",this->_gridLength);
                printf("_gridWidth=%d\n",this->_gridWidth);
                printf("TileComponentHeightOffset=%f\n",this->TileComponentHeightOffset);
        }
};

class Vector3{
public:
    unsigned int x;
    unsigned int y;
    unsigned int z;
};
class GameMapTile: MonoObject{
public:
        unsigned char unk0[24];
        unsigned int _tile; //32 Class tk2dSprite
        unsigned int refgroundname; //36 String
        unsigned int _portal; //40 Class GameMapPortal
        unsigned int _linkedPortal; //44 Class GameMapPortal
        unsigned int _linkedTile; //48 Class GameMapTile
        unsigned int colorStack; //52 List System.Collections.Generic.Stack`1
        unsigned int spriteComponents; //56 List System.Collections.Generic.List`1
        unsigned int spriteColors; //60 List System.Collections.Generic.List`1
        unsigned int _gameTag; //64 String
        unsigned int _generalProps; //68 SZARRAY System.Boolean
        unsigned int _stringProps; //72 SZARRAY System.String
        unsigned int _gameObjectDecorationList; //76 List System.Collections.Generic.List`1
        unsigned int iconSequence; //80 Class Holoville.HOTween.Sequence
        unsigned int _mark_k__BackingField; //84 Class UnityEngine.GameObject
        unsigned int _effect_k__BackingField; //88 Class UnityEngine.GameObject
        unsigned int _reconizeEffect_k__BackingField; //92 Class UnityEngine.GameObject
        unsigned int _effectLockon_k__BackingField; //96 Class UnityEngine.GameObject
        unsigned int _icon_k__BackingField; //100 Class UISprite
        unsigned int _castskill_k__BackingField; //104 Class Skill
        unsigned char currentMarkType; //108 VALUE size=1
        unsigned char currentEffectType; //109 VALUE size=1
        unsigned char currentColorType; //110 VALUE size=1
        unsigned char _eventProps; //111 VALUE size=1
        unsigned int _skillProperty; //112 Int
        unsigned char _forOccupation; //116 Bool
        unsigned char _movingType; //117 VALUE size=1
        unsigned char _attribute; //118 VALUE size=1
        unsigned char unk1[1];
        unsigned char advantageType; //120 VALUE size=1
        unsigned char unk2[3];
        unsigned char reserveAdavantage; //124 VALUE size=1
        unsigned char unk3[3];
        float tileAlpha; //128 float
        unsigned char _occupyType_k__BackingField; //132 VALUE size=1
        unsigned char _isMoving_k__BackingField; //133 Bool
        unsigned char unk4[2];
        Vector3 _orgLocalPos_k__BackingField; //136 VALUE size=12
        unsigned char _IsTransparent_k__BackingField; //148 Bool
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->_tile);vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->refgroundname)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_portal);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_linkedPortal);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_linkedTile);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->colorStack);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->spriteComponents);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->spriteColors);vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_gameTag)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_generalProps);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_stringProps);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_gameObjectDecorationList);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->iconSequence);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_mark_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_effect_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_reconizeEffect_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_effectLockon_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_icon_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_castskill_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skillProperty);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_forOccupation);vStringList.push_back(tmp);
                sprintf(tmp,"%f",this->tileAlpha);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_isMoving_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_IsTransparent_k__BackingField);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("_tile=%08X\n",this->_tile);
                printf("refgroundname=[%s]\n",SaveCString(pscan.readMonoString(this->refgroundname)).c_str());
                printf("_portal=%08X\n",this->_portal);
                printf("_linkedPortal=%08X\n",this->_linkedPortal);
                printf("_linkedTile=%08X\n",this->_linkedTile);
                printf("colorStack=%08X\n",this->colorStack);
                printf("spriteComponents=%08X\n",this->spriteComponents);
                printf("spriteColors=%08X\n",this->spriteColors);
                printf("_gameTag=[%s]\n",SaveCString(pscan.readMonoString(this->_gameTag)).c_str());
                printf("_generalProps=%08X\n",this->_generalProps);
                printf("_stringProps=%08X\n",this->_stringProps);
                printf("_gameObjectDecorationList=%08X\n",this->_gameObjectDecorationList);
                printf("iconSequence=%08X\n",this->iconSequence);
                printf("_mark_k__BackingField=%08X\n",this->_mark_k__BackingField);
                printf("_effect_k__BackingField=%08X\n",this->_effect_k__BackingField);
                printf("_reconizeEffect_k__BackingField=%08X\n",this->_reconizeEffect_k__BackingField);
                printf("_effectLockon_k__BackingField=%08X\n",this->_effectLockon_k__BackingField);
                printf("_icon_k__BackingField=%08X\n",this->_icon_k__BackingField);
                printf("_castskill_k__BackingField=%08X\n",this->_castskill_k__BackingField);
                printf("_skillProperty=%d\n",this->_skillProperty);
                printf("_forOccupation=%d\n",this->_forOccupation);
                printf("tileAlpha=%f\n",this->tileAlpha);
                printf("_isMoving_k__BackingField=%d\n",this->_isMoving_k__BackingField);
                printf("_IsTransparent_k__BackingField=%d\n",this->_IsTransparent_k__BackingField);
        }
};

class ActiveData: MonoObject{
public:
        unsigned int _name; //8 String
        unsigned int _targetFxPrefab; //12 String
        unsigned int _iconString; //16 String
        unsigned int _desc; //20 String
        unsigned int _openString; //24 String
        unsigned int _lordskillId; //28 Int
        unsigned int _skilldataId; //32 Int
        unsigned char _effectType; //36 UByte
        unsigned char _skillTarget; //37 UByte
        unsigned char _affectedCount; //38 UByte
        unsigned char _shaderOff; //39 UByte
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_name)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_targetFxPrefab)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_iconString)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_desc)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_openString)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_lordskillId);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skilldataId);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_effectType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skillTarget);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_affectedCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_shaderOff);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("_name=[%s]\n",SaveCString(pscan.readMonoString(this->_name)).c_str());
                printf("_targetFxPrefab=[%s]\n",SaveCString(pscan.readMonoString(this->_targetFxPrefab)).c_str());
                printf("_iconString=[%s]\n",SaveCString(pscan.readMonoString(this->_iconString)).c_str());
                printf("_desc=[%s]\n",SaveCString(pscan.readMonoString(this->_desc)).c_str());
                printf("_openString=[%s]\n",SaveCString(pscan.readMonoString(this->_openString)).c_str());
                printf("_lordskillId=%d\n",this->_lordskillId);
                printf("_skilldataId=%d\n",this->_skilldataId);
                printf("_effectType=%d\n",this->_effectType);
                printf("_skillTarget=%d\n",this->_skillTarget);
                printf("_affectedCount=%d\n",this->_affectedCount);
                printf("_shaderOff=%d\n",this->_shaderOff);
        }
};

class ActiveSkillValue: MonoObject{
public:
        unsigned char _userLevel; //8 UByte
        unsigned char unk0[3];
        unsigned int _lordskillId; //12 Int
        unsigned char _skillLevel; //16 UByte
        unsigned char unk1[3];
        float _skillValue1; //20 float
        unsigned int _skillValue2; //24 Int
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->_userLevel);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_lordskillId);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skillLevel);vStringList.push_back(tmp);
                sprintf(tmp,"%f",this->_skillValue1);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skillValue2);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("_userLevel=%d\n",this->_userLevel);
                printf("_lordskillId=%d\n",this->_lordskillId);
                printf("_skillLevel=%d\n",this->_skillLevel);
                printf("_skillValue1=%f\n",this->_skillValue1);
                printf("_skillValue2=%d\n",this->_skillValue2);
        }
};

class AttendanceData: MonoObject{
public:
        unsigned char _attendanceNo; //8 UByte
        unsigned char unk0[3];
        unsigned int _attendanceYear; //12 Int
        unsigned char _attendanceDate; //16 UByte
        unsigned char unk1[3];
        unsigned int _attendanceGold; //20 Int
        unsigned int _attendanceCash; //24 Int
        unsigned int _attendanceManastone; //28 Int
        unsigned int _attendanceGene; //32 Int
        unsigned int _geneCount; //36 Int
        unsigned int _attendanceMonster; //40 Int
        unsigned int _monsterLevel; //44 Int
        unsigned int _attendanceWp; //48 Int
        unsigned int _attendanceEquip; //52 Int
        unsigned int _attendanceItem; //56 Int
        unsigned int _itemCount; //60 Int
        unsigned int _attendanceCapsule; //64 Int
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->_attendanceNo);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_attendanceYear);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_attendanceDate);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_attendanceGold);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_attendanceCash);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_attendanceManastone);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_attendanceGene);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_geneCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_attendanceMonster);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_monsterLevel);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_attendanceWp);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_attendanceEquip);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_attendanceItem);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_itemCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_attendanceCapsule);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("_attendanceNo=%d\n",this->_attendanceNo);
                printf("_attendanceYear=%d\n",this->_attendanceYear);
                printf("_attendanceDate=%d\n",this->_attendanceDate);
                printf("_attendanceGold=%d\n",this->_attendanceGold);
                printf("_attendanceCash=%d\n",this->_attendanceCash);
                printf("_attendanceManastone=%d\n",this->_attendanceManastone);
                printf("_attendanceGene=%d\n",this->_attendanceGene);
                printf("_geneCount=%d\n",this->_geneCount);
                printf("_attendanceMonster=%d\n",this->_attendanceMonster);
                printf("_monsterLevel=%d\n",this->_monsterLevel);
                printf("_attendanceWp=%d\n",this->_attendanceWp);
                printf("_attendanceEquip=%d\n",this->_attendanceEquip);
                printf("_attendanceItem=%d\n",this->_attendanceItem);
                printf("_itemCount=%d\n",this->_itemCount);
                printf("_attendanceCapsule=%d\n",this->_attendanceCapsule);
        }
};

class BannerManager: MonoObject{
public:
        unsigned int bannerPlacementNames; //8 SZARRAY System.String
        unsigned int bannerList; //12 List System.Collections.Generic.List`1
        unsigned int OnFinishBannerEvent; //16 Class OnFinishBannerHandler
        unsigned char currentBannerPlace; //20 VALUE size=1 BannerPlace
        unsigned char unk0[3];
        unsigned int bannerStepIndex; //24 Int
        unsigned char isRunningOpen; //28 Bool
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->bannerPlacementNames);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->bannerList);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnFinishBannerEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->currentBannerPlace);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->bannerStepIndex);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->isRunningOpen);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("bannerPlacementNames=%08X\n",this->bannerPlacementNames);
                printf("bannerList=%08X\n",this->bannerList);
                printf("OnFinishBannerEvent=%08X\n",this->OnFinishBannerEvent);
                printf("currentBannerPlace=%d\n",this->currentBannerPlace);
                printf("bannerStepIndex=%d\n",this->bannerStepIndex);
                printf("isRunningOpen=%d\n",this->isRunningOpen);
        }
};

class BattleManager: MonoObject{
public:
    long long int m_UnityRuntimeReferenceData; //8 VALUE size=8
    unsigned int _leadCaster; //16 Class Character
    unsigned int _mainCastee; //20 Class Character
    unsigned int _casteeDic; //24 List System.Collections.Generic.Dictionary`2
    unsigned int _accomplishedCastees; //28 List System.Collections.Generic.List`1
    unsigned int _moribundCastees; //32 List System.Collections.Generic.List`1
    unsigned int _passiveAttackers; //36 List System.Collections.Generic.List`1
    unsigned int _attackerMemberList; //40 List System.Collections.Generic.List`1
    unsigned int _targetMemberList; //44 List System.Collections.Generic.List`1
    unsigned int _recongnzationTiles; //48 List BetterList`1
    unsigned int _assignedTarget; //52 Class Character
    unsigned int _tagManager; //56 Class TagManager
    unsigned int _raidScoreManager; //60 Class BattleGuildRaidScore
    unsigned int restoreOrgTile; //64 List System.Collections.Generic.Stack`1
    unsigned int usedPortalTile; //68 List System.Collections.Generic.Stack`1
    unsigned int usedDistance; //72 List System.Collections.Generic.Stack`1
    unsigned int dicDestroyRelatedTargets; //76 List System.Collections.Generic.Dictionary`2
    unsigned int _lastLeadHitCreatureId; //80 Int
    unsigned char _lastLeadHitCreatureCampType; //84 VALUE size=1 GameCampType
    unsigned char _isOccurredPassiveAttacks; //85 Bool
    unsigned char _isCharacterMoving; //86 Bool
    unsigned char _IsDefaultAttacking; //87 Bool
    unsigned char _isCharacterAttacking; //88 Bool
    unsigned char _isLordSkillActing; //89 Bool
    unsigned char _isReserveLordSkill; //90 Bool
    unsigned char _isUsedResurrection; //91 Bool
    unsigned int _assignedSkillIndex; //92 Int
    std::string ToString(ProcessScanner& pscan){
	    char tmp[1024];
	    std::vector<std::string> vStringList;
	    sprintf(tmp,"%d",this->_leadCaster);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_mainCastee);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_casteeDic);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_accomplishedCastees);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_moribundCastees);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_passiveAttackers);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_attackerMemberList);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_targetMemberList);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_recongnzationTiles);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_assignedTarget);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_tagManager);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_raidScoreManager);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->restoreOrgTile);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->usedPortalTile);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->usedDistance);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->dicDestroyRelatedTargets);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_lastLeadHitCreatureId);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_lastLeadHitCreatureCampType);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_isOccurredPassiveAttacks);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_isCharacterMoving);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_IsDefaultAttacking);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_isCharacterAttacking);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_isLordSkillActing);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_isReserveLordSkill);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_isUsedResurrection);vStringList.push_back(tmp);
	    sprintf(tmp,"%d",this->_assignedSkillIndex);vStringList.push_back(tmp);
	    std::string ret;
	    ret += "{";
	    ret += ConcatStrings(vStringList,",");
	    ret += "},";
	    return ret;
    }
    void Show(ProcessScanner& pscan){
	    printf("_leadCaster=%08X\n",this->_leadCaster);
	    printf("_mainCastee=%08X\n",this->_mainCastee);
	    printf("_casteeDic=%08X\n",this->_casteeDic);
	    printf("_accomplishedCastees=%08X\n",this->_accomplishedCastees);
	    printf("_moribundCastees=%08X\n",this->_moribundCastees);
	    printf("_passiveAttackers=%08X\n",this->_passiveAttackers);
	    printf("_attackerMemberList=%08X\n",this->_attackerMemberList);
	    printf("_targetMemberList=%08X\n",this->_targetMemberList);
	    printf("_recongnzationTiles=%08X\n",this->_recongnzationTiles);
	    printf("_assignedTarget=%08X\n",this->_assignedTarget);
	    printf("_tagManager=%08X\n",this->_tagManager);
	    printf("_raidScoreManager=%08X\n",this->_raidScoreManager);
	    printf("restoreOrgTile=%08X\n",this->restoreOrgTile);
	    printf("usedPortalTile=%08X\n",this->usedPortalTile);
	    printf("usedDistance=%08X\n",this->usedDistance);
	    printf("dicDestroyRelatedTargets=%08X\n",this->dicDestroyRelatedTargets);
	    printf("_lastLeadHitCreatureId=%d\n",this->_lastLeadHitCreatureId);
	    printf("_lastLeadHitCreatureCampType=%d\n",this->_lastLeadHitCreatureCampType);
	    printf("_isOccurredPassiveAttacks=%d\n",this->_isOccurredPassiveAttacks);
	    printf("_isCharacterMoving=%d\n",this->_isCharacterMoving);
	    printf("_IsDefaultAttacking=%d\n",this->_IsDefaultAttacking);
	    printf("_isCharacterAttacking=%d\n",this->_isCharacterAttacking);
	    printf("_isLordSkillActing=%d\n",this->_isLordSkillActing);
	    printf("_isReserveLordSkill=%d\n",this->_isReserveLordSkill);
	    printf("_isUsedResurrection=%d\n",this->_isUsedResurrection);
	    printf("_assignedSkillIndex=%d\n",this->_assignedSkillIndex);
    }
    BattleManager(){
	_casteeDic = 0;
    }
    bool isInit(){
	return _casteeDic != 0;
    }	
};

class FWTCharacter: MonoObject{
public:
        long long int m_UnityRuntimeReferenceData; //8 VALUE size=8
        unsigned int _data; //16 Class ICharDataContainer
        unsigned int _assets; //20 Class ICharacterAsset
        unsigned int _ai; //24 Class ICharacterAI
        unsigned int _stats; //28 Class StatContainer
        unsigned int _skills; //32 Class SkillContainer
        unsigned int _effets; //36 Class StatusEffectContainer
        unsigned int _states; //40 Class GameStateMachine
        unsigned int containers; //44 SZARRAY IDataContainer
        unsigned int _gametag; //48 Class GameTag
        unsigned int specialspawn; //52 Class SpawnContainerAdditionalData
        unsigned int immuneMessageData; //56 List System.Collections.Generic.List`1
        unsigned int _immuneSkillEffectList; //60 List System.Collections.Generic.List`1
        unsigned int _creatureName; //64 String
        unsigned int CastableSkillDic; //68 List System.Collections.Generic.Dictionary`2
        unsigned int meshCollider; //72 Class UnityEngine.CapsuleCollider
        unsigned int _curSkillMoveData; //76 Class SkillMoveData
        unsigned int OnStartTurnEvent; //80 Class OnStartTurnHandler
        unsigned int OnEndTurnEvent; //84 Class OnEndTurnHandler
        unsigned int OnDieEvent; //88 Class OnDieHandler
        unsigned int OnDeadEvent; //92 Class OnDeadHandler
        unsigned int OnExitStateEvent; //96 Class OnExitStateHandler
        unsigned int OnTileTriggerEndTurnEvent; //100 Class OnTileTriggerEndTurnHandler
        unsigned int OnGuildRaidScoreEvent; //104 Class OnGuildRaidScoreUIHandler
        unsigned int _camp_k__BackingField; //108 Class Camp
        unsigned int _orgPositionTile_k__BackingField; //112 Class GameMapTile
        unsigned char _characterType; //116 VALUE size=1 CharacterType
        unsigned char _Isolated; //117 Bool
        unsigned char unk0[2];
        float spawningScale; //120 float
        Vector3 _boundsSize; //124 VALUE size=12
        Vector3 _offsetOnTile; //136 VALUE size=12
        unsigned int _turnNo; //148 Int
        long long int instanceID; //152 Int64
        long long int localInstanceID; //160 Int64
        unsigned char didAdvantageSet; //168 Bool
        unsigned char _IsArrivalEffected; //169 Bool
        unsigned char unk1[2];
        unsigned char exhaustionType; //172 VALUE size=1 ExhaustionType
        unsigned char unk2[3];
        unsigned char isContainerGameOver; //176 Bool
        unsigned char unk3[3];
        unsigned int canMoveCount; //180 Int
        unsigned int _activeSkillCount_k__BackingField; //184 Int
        unsigned char _IsTutorialInProgress_k__BackingField; //188 Bool
        unsigned char unk4[3];
        unsigned int _sequenceNumber_k__BackingField; //192 Int
        unsigned char _currentAction_k__BackingField; //196 VALUE size=1 ActionPhase
        unsigned char _isRunningAI_k__BackingField; //197 Bool
        unsigned char unk5[2];
        unsigned int _makeCreature_k__BackingField; //200 Int
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->_data);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_assets);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_ai);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_stats);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skills);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_effets);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_states);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->containers);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_gametag);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->specialspawn);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->immuneMessageData);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_immuneSkillEffectList);vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_creatureName)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->CastableSkillDic);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->meshCollider);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_curSkillMoveData);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnStartTurnEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnEndTurnEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnDieEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnDeadEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnExitStateEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnTileTriggerEndTurnEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnGuildRaidScoreEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_camp_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_orgPositionTile_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_characterType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_Isolated);vStringList.push_back(tmp);
                sprintf(tmp,"%f",this->spawningScale);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_turnNo);vStringList.push_back(tmp);
                sprintf(tmp,"%lld",this->instanceID);vStringList.push_back(tmp);
                sprintf(tmp,"%lld",this->localInstanceID);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->didAdvantageSet);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_IsArrivalEffected);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->exhaustionType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->isContainerGameOver);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->canMoveCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_activeSkillCount_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_IsTutorialInProgress_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_sequenceNumber_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_currentAction_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_isRunningAI_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_makeCreature_k__BackingField);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("_data=%08X\n",this->_data);
                printf("_assets=%08X\n",this->_assets);
                printf("_ai=%08X\n",this->_ai);
                printf("_stats=%08X\n",this->_stats);
                printf("_skills=%08X\n",this->_skills);
                printf("_effets=%08X\n",this->_effets);
                printf("_states=%08X\n",this->_states);
                printf("containers=%08X\n",this->containers);
                printf("_gametag=%08X\n",this->_gametag);
                printf("specialspawn=%08X\n",this->specialspawn);
                printf("immuneMessageData=%08X\n",this->immuneMessageData);
                printf("_immuneSkillEffectList=%08X\n",this->_immuneSkillEffectList);
                printf("_creatureName=[%s]\n",SaveCString(pscan.readMonoString(this->_creatureName)).c_str());
                printf("CastableSkillDic=%08X\n",this->CastableSkillDic);
                printf("meshCollider=%08X\n",this->meshCollider);
                printf("_curSkillMoveData=%08X\n",this->_curSkillMoveData);
                printf("OnStartTurnEvent=%08X\n",this->OnStartTurnEvent);
                printf("OnEndTurnEvent=%08X\n",this->OnEndTurnEvent);
                printf("OnDieEvent=%08X\n",this->OnDieEvent);
                printf("OnDeadEvent=%08X\n",this->OnDeadEvent);
                printf("OnExitStateEvent=%08X\n",this->OnExitStateEvent);
                printf("OnTileTriggerEndTurnEvent=%08X\n",this->OnTileTriggerEndTurnEvent);
                printf("OnGuildRaidScoreEvent=%08X\n",this->OnGuildRaidScoreEvent);
                printf("_camp_k__BackingField=%08X\n",this->_camp_k__BackingField);
                printf("_orgPositionTile_k__BackingField=%08X\n",this->_orgPositionTile_k__BackingField);
                printf("_characterType=%d\n",this->_characterType);
                printf("_Isolated=%d\n",this->_Isolated);
                printf("spawningScale=%f\n",this->spawningScale);
                printf("_turnNo=%d\n",this->_turnNo);
                printf("instanceID=%lld\n",this->instanceID);
                printf("localInstanceID=%lld\n",this->localInstanceID);
                printf("didAdvantageSet=%d\n",this->didAdvantageSet);
                printf("_IsArrivalEffected=%d\n",this->_IsArrivalEffected);
                printf("exhaustionType=%d\n",this->exhaustionType);
                printf("isContainerGameOver=%d\n",this->isContainerGameOver);
                printf("canMoveCount=%d\n",this->canMoveCount);
                printf("_activeSkillCount_k__BackingField=%d\n",this->_activeSkillCount_k__BackingField);
                printf("_IsTutorialInProgress_k__BackingField=%d\n",this->_IsTutorialInProgress_k__BackingField);
                printf("_sequenceNumber_k__BackingField=%d\n",this->_sequenceNumber_k__BackingField);
                printf("_currentAction_k__BackingField=%d\n",this->_currentAction_k__BackingField);
                printf("_isRunningAI_k__BackingField=%d\n",this->_isRunningAI_k__BackingField);
                printf("_makeCreature_k__BackingField=%d\n",this->_makeCreature_k__BackingField);
        }
};

class Player: MonoObject{
public:
        long long int m_UnityRuntimeReferenceData; //8 VALUE size=8
        unsigned int _data; //16 Class ICharDataContainer
        unsigned int _assets; //20 Class ICharacterAsset
        unsigned int _ai; //24 Class ICharacterAI
        unsigned int _stats; //28 Class StatContainer
        unsigned int _skills; //32 Class SkillContainer
        unsigned int _effets; //36 Class StatusEffectContainer
        unsigned int _states; //40 Class GameStateMachine
        unsigned int containers; //44 SZARRAY IDataContainer
        unsigned int _gametag; //48 Class GameTag
        unsigned int specialspawn; //52 Class SpawnContainerAdditionalData
        unsigned int immuneMessageData; //56 List System.Collections.Generic.List`1
        unsigned int _immuneSkillEffectList; //60 List System.Collections.Generic.List`1
        unsigned int _creatureName; //64 String
        unsigned int CastableSkillDic; //68 List System.Collections.Generic.Dictionary`2
        unsigned int meshCollider; //72 Class UnityEngine.CapsuleCollider
        unsigned int _curSkillMoveData; //76 Class SkillMoveData
        unsigned int OnStartTurnEvent; //80 Class OnStartTurnHandler
        unsigned int OnEndTurnEvent; //84 Class OnEndTurnHandler
        unsigned int OnDieEvent; //88 Class OnDieHandler
        unsigned int OnDeadEvent; //92 Class OnDeadHandler
        unsigned int OnExitStateEvent; //96 Class OnExitStateHandler
        unsigned int OnTileTriggerEndTurnEvent; //100 Class OnTileTriggerEndTurnHandler
        unsigned int OnGuildRaidScoreEvent; //104 Class OnGuildRaidScoreUIHandler
        unsigned int _camp_k__BackingField; //108 Class Camp
        unsigned int _orgPositionTile_k__BackingField; //112 Class GameMapTile
        unsigned char _characterType; //116 VALUE size=1 CharacterType
        unsigned char _Isolated; //117 Bool
        unsigned char unk0[2];
        float spawningScale; //120 float
        Vector3 _boundsSize; //124 VALUE size=12
        Vector3 _offsetOnTile; //136 VALUE size=12
        unsigned int _turnNo; //148 Int
        long long int instanceID; //152 Int64
        long long int localInstanceID; //160 Int64
        unsigned char didAdvantageSet; //168 Bool
        unsigned char _IsArrivalEffected; //169 Bool
        unsigned char unk1[2];
        unsigned char exhaustionType; //172 VALUE size=1 ExhaustionType
        unsigned char unk2[3];
        unsigned char isContainerGameOver; //176 Bool
        unsigned char unk3[3];
        unsigned int canMoveCount; //180 Int
        unsigned int _activeSkillCount_k__BackingField; //184 Int
        unsigned char _IsTutorialInProgress_k__BackingField; //188 Bool
        unsigned char unk4[3];
        unsigned int _sequenceNumber_k__BackingField; //192 Int
        unsigned char _currentAction_k__BackingField; //196 VALUE size=1 ActionPhase
        unsigned char _isRunningAI_k__BackingField; //197 Bool
        unsigned char unk5[2];
        unsigned int _makeCreature_k__BackingField; //200 Int
        unsigned int pai; //204 Class PlayerAI
        unsigned int OnSkillUseEvent; //208 Class OnSkillUseHandler
        unsigned char doesCompleteMovingPhase; //212 Bool
        unsigned char isOpponentIcon; //213 Bool
        unsigned char _isBackTurn; //214 Bool
        unsigned char _elapsedTurnCount; //215 UByte
        unsigned char isSummondeAutoPlay; //216 Bool
        unsigned char isAutoPlay; //217 Bool
        unsigned char _coopPlayState_k__BackingField; //218 VALUE size=1 CoopPlayStateType
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->_data);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_assets);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_ai);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_stats);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skills);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_effets);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_states);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->containers);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_gametag);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->specialspawn);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->immuneMessageData);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_immuneSkillEffectList);vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_creatureName)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->CastableSkillDic);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->meshCollider);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_curSkillMoveData);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnStartTurnEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnEndTurnEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnDieEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnDeadEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnExitStateEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnTileTriggerEndTurnEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnGuildRaidScoreEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_camp_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_orgPositionTile_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_characterType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_Isolated);vStringList.push_back(tmp);
                sprintf(tmp,"%f",this->spawningScale);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_turnNo);vStringList.push_back(tmp);
                sprintf(tmp,"%lld",this->instanceID);vStringList.push_back(tmp);
                sprintf(tmp,"%lld",this->localInstanceID);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->didAdvantageSet);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_IsArrivalEffected);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->exhaustionType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->isContainerGameOver);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->canMoveCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_activeSkillCount_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_IsTutorialInProgress_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_sequenceNumber_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_currentAction_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_isRunningAI_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_makeCreature_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->pai);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnSkillUseEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->doesCompleteMovingPhase);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->isOpponentIcon);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_isBackTurn);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_elapsedTurnCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->isSummondeAutoPlay);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->isAutoPlay);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_coopPlayState_k__BackingField);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
		printf("------ Show [%s] ------\n",pscan.GetVTableClassName((unsigned int)this->vtable));
                printf("_data=%08X\n",this->_data);
                printf("_assets=%08X\n",this->_assets);
                printf("_ai=%08X\n",this->_ai);
                printf("_stats=%08X\n",this->_stats);
                printf("_skills=%08X\n",this->_skills);
                printf("_effets=%08X\n",this->_effets);
                printf("_states=%08X\n",this->_states);
                printf("containers=%08X\n",this->containers);
                printf("_gametag=%08X\n",this->_gametag);
                printf("specialspawn=%08X\n",this->specialspawn);
                printf("immuneMessageData=%08X\n",this->immuneMessageData);
                printf("_immuneSkillEffectList=%08X\n",this->_immuneSkillEffectList);
                printf("_creatureName=[%s]\n",SaveCString(pscan.readMonoString(this->_creatureName)).c_str());
                printf("CastableSkillDic=%08X\n",this->CastableSkillDic);
                printf("meshCollider=%08X\n",this->meshCollider);
                printf("_curSkillMoveData=%08X\n",this->_curSkillMoveData);
                printf("OnStartTurnEvent=%08X\n",this->OnStartTurnEvent);
                printf("OnEndTurnEvent=%08X\n",this->OnEndTurnEvent);
                printf("OnDieEvent=%08X\n",this->OnDieEvent);
                printf("OnDeadEvent=%08X\n",this->OnDeadEvent);
                printf("OnExitStateEvent=%08X\n",this->OnExitStateEvent);
                printf("OnTileTriggerEndTurnEvent=%08X\n",this->OnTileTriggerEndTurnEvent);
                printf("OnGuildRaidScoreEvent=%08X\n",this->OnGuildRaidScoreEvent);
                printf("_camp_k__BackingField=%08X\n",this->_camp_k__BackingField);
                printf("_orgPositionTile_k__BackingField=%08X\n",this->_orgPositionTile_k__BackingField);
                printf("_characterType=%d\n",this->_characterType);
                printf("_Isolated=%d\n",this->_Isolated);
                printf("spawningScale=%f\n",this->spawningScale);
                printf("_turnNo=%d\n",this->_turnNo);
                printf("instanceID=%lld\n",this->instanceID);
                printf("localInstanceID=%lld\n",this->localInstanceID);
                printf("didAdvantageSet=%d\n",this->didAdvantageSet);
                printf("_IsArrivalEffected=%d\n",this->_IsArrivalEffected);
                printf("exhaustionType=%d\n",this->exhaustionType);
                printf("isContainerGameOver=%d\n",this->isContainerGameOver);
                printf("canMoveCount=%d\n",this->canMoveCount);
                printf("_activeSkillCount_k__BackingField=%d\n",this->_activeSkillCount_k__BackingField);
                printf("_IsTutorialInProgress_k__BackingField=%d\n",this->_IsTutorialInProgress_k__BackingField);
                printf("_sequenceNumber_k__BackingField=%d\n",this->_sequenceNumber_k__BackingField);
                printf("_currentAction_k__BackingField=%d\n",this->_currentAction_k__BackingField);
                printf("_isRunningAI_k__BackingField=%d\n",this->_isRunningAI_k__BackingField);
                printf("_makeCreature_k__BackingField=%d\n",this->_makeCreature_k__BackingField);
                printf("pai=%08X\n",this->pai);
                printf("OnSkillUseEvent=%08X\n",this->OnSkillUseEvent);
                printf("doesCompleteMovingPhase=%d\n",this->doesCompleteMovingPhase);
                printf("isOpponentIcon=%d\n",this->isOpponentIcon);
                printf("_isBackTurn=%d\n",this->_isBackTurn);
                printf("_elapsedTurnCount=%d\n",this->_elapsedTurnCount);
                printf("isSummondeAutoPlay=%d\n",this->isSummondeAutoPlay);
                printf("isAutoPlay=%d\n",this->isAutoPlay);
                printf("_coopPlayState_k__BackingField=%d\n",this->_coopPlayState_k__BackingField);
        }
};

class Monster: MonoObject{
public:
        long long int m_UnityRuntimeReferenceData; //8 VALUE size=8
        unsigned int _data; //16 Class ICharDataContainer
        unsigned int _assets; //20 Class ICharacterAsset
        unsigned int _ai; //24 Class ICharacterAI
        unsigned int _stats; //28 Class StatContainer
        unsigned int _skills; //32 Class SkillContainer
        unsigned int _effets; //36 Class StatusEffectContainer
        unsigned int _states; //40 Class GameStateMachine
        unsigned int containers; //44 SZARRAY IDataContainer
        unsigned int _gametag; //48 Class GameTag
        unsigned int specialspawn; //52 Class SpawnContainerAdditionalData
        unsigned int immuneMessageData; //56 List System.Collections.Generic.List`1
        unsigned int _immuneSkillEffectList; //60 List System.Collections.Generic.List`1
        unsigned int _creatureName; //64 String
        unsigned int CastableSkillDic; //68 List System.Collections.Generic.Dictionary`2
        unsigned int meshCollider; //72 Class UnityEngine.CapsuleCollider
        unsigned int _curSkillMoveData; //76 Class SkillMoveData
        unsigned int OnStartTurnEvent; //80 Class OnStartTurnHandler
        unsigned int OnEndTurnEvent; //84 Class OnEndTurnHandler
        unsigned int OnDieEvent; //88 Class OnDieHandler
        unsigned int OnDeadEvent; //92 Class OnDeadHandler
        unsigned int OnExitStateEvent; //96 Class OnExitStateHandler
        unsigned int OnTileTriggerEndTurnEvent; //100 Class OnTileTriggerEndTurnHandler
        unsigned int OnGuildRaidScoreEvent; //104 Class OnGuildRaidScoreUIHandler
        unsigned int _camp_k__BackingField; //108 Class Camp
        unsigned int _orgPositionTile_k__BackingField; //112 Class GameMapTile
        unsigned char _characterType; //116 VALUE size=1 CharacterType
        unsigned char _Isolated; //117 Bool
        unsigned char unk0[2];
        float spawningScale; //120 float
        Vector3 _boundsSize; //124 VALUE size=12
        Vector3 _offsetOnTile; //136 VALUE size=12
        unsigned int _turnNo; //148 Int
        long long int instanceID; //152 Int64
        long long int localInstanceID; //160 Int64
        unsigned char didAdvantageSet; //168 Bool
        unsigned char _IsArrivalEffected; //169 Bool
        unsigned char unk1[2];
        unsigned char exhaustionType; //172 VALUE size=1 ExhaustionType
        unsigned char unk2[3];
        unsigned char isContainerGameOver; //176 Bool
        unsigned char unk3[3];
        unsigned int canMoveCount; //180 Int
        unsigned int _activeSkillCount_k__BackingField; //184 Int
        unsigned char _IsTutorialInProgress_k__BackingField; //188 Bool
        unsigned char unk4[3];
        unsigned int _sequenceNumber_k__BackingField; //192 Int
        unsigned char _currentAction_k__BackingField; //196 VALUE size=1 ActionPhase
        unsigned char _isRunningAI_k__BackingField; //197 Bool
        unsigned char unk5[2];
        unsigned int _makeCreature_k__BackingField; //200 Int
        unsigned int mai; //204 Class CharactersAI
        unsigned int _powerMonData; //208 Class PowerMon
        unsigned int _mdata_k__BackingField; //212 Class MonsterData
        unsigned int _subordinatingObject_k__BackingField; //216 Class MapObject
        unsigned char _monsterAIType; //220 VALUE size=1 MonsterType
        unsigned char unk6[3];
        unsigned char IsDestroyDirectingEffect; //224 Bool
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->_data);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_assets);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_ai);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_stats);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skills);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_effets);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_states);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->containers);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_gametag);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->specialspawn);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->immuneMessageData);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_immuneSkillEffectList);vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_creatureName)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->CastableSkillDic);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->meshCollider);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_curSkillMoveData);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnStartTurnEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnEndTurnEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnDieEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnDeadEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnExitStateEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnTileTriggerEndTurnEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnGuildRaidScoreEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_camp_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_orgPositionTile_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_characterType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_Isolated);vStringList.push_back(tmp);
                sprintf(tmp,"%f",this->spawningScale);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_turnNo);vStringList.push_back(tmp);
                sprintf(tmp,"%lld",this->instanceID);vStringList.push_back(tmp);
                sprintf(tmp,"%lld",this->localInstanceID);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->didAdvantageSet);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_IsArrivalEffected);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->exhaustionType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->isContainerGameOver);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->canMoveCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_activeSkillCount_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_IsTutorialInProgress_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_sequenceNumber_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_currentAction_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_isRunningAI_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_makeCreature_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->mai);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_powerMonData);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_mdata_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_subordinatingObject_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_monsterAIType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->IsDestroyDirectingEffect);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("------ Show [%s] ------\n",pscan.GetVTableClassName((unsigned int)this->vtable));
                printf("_data=%08X\n",this->_data);
                printf("_assets=%08X\n",this->_assets);
                printf("_ai=%08X\n",this->_ai);
                printf("_stats=%08X\n",this->_stats);
                printf("_skills=%08X\n",this->_skills);
                printf("_effets=%08X\n",this->_effets);
                printf("_states=%08X\n",this->_states);
                printf("containers=%08X\n",this->containers);
                printf("_gametag=%08X\n",this->_gametag);
                printf("specialspawn=%08X\n",this->specialspawn);
                printf("immuneMessageData=%08X\n",this->immuneMessageData);
                printf("_immuneSkillEffectList=%08X\n",this->_immuneSkillEffectList);
                printf("_creatureName=[%s]\n",SaveCString(pscan.readMonoString(this->_creatureName)).c_str());
                printf("CastableSkillDic=%08X\n",this->CastableSkillDic);
                printf("meshCollider=%08X\n",this->meshCollider);
                printf("_curSkillMoveData=%08X\n",this->_curSkillMoveData);
                printf("OnStartTurnEvent=%08X\n",this->OnStartTurnEvent);
                printf("OnEndTurnEvent=%08X\n",this->OnEndTurnEvent);
                printf("OnDieEvent=%08X\n",this->OnDieEvent);
                printf("OnDeadEvent=%08X\n",this->OnDeadEvent);
                printf("OnExitStateEvent=%08X\n",this->OnExitStateEvent);
                printf("OnTileTriggerEndTurnEvent=%08X\n",this->OnTileTriggerEndTurnEvent);
                printf("OnGuildRaidScoreEvent=%08X\n",this->OnGuildRaidScoreEvent);
                printf("_camp_k__BackingField=%08X\n",this->_camp_k__BackingField);
                printf("_orgPositionTile_k__BackingField=%08X\n",this->_orgPositionTile_k__BackingField);
                printf("_characterType=%d\n",this->_characterType);
                printf("_Isolated=%d\n",this->_Isolated);
                printf("spawningScale=%f\n",this->spawningScale);
                printf("_turnNo=%d\n",this->_turnNo);
                printf("instanceID=%lld\n",this->instanceID);
                printf("localInstanceID=%lld\n",this->localInstanceID);
                printf("didAdvantageSet=%d\n",this->didAdvantageSet);
                printf("_IsArrivalEffected=%d\n",this->_IsArrivalEffected);
                printf("exhaustionType=%d\n",this->exhaustionType);
                printf("isContainerGameOver=%d\n",this->isContainerGameOver);
                printf("canMoveCount=%d\n",this->canMoveCount);
                printf("_activeSkillCount_k__BackingField=%d\n",this->_activeSkillCount_k__BackingField);
                printf("_IsTutorialInProgress_k__BackingField=%d\n",this->_IsTutorialInProgress_k__BackingField);
                printf("_sequenceNumber_k__BackingField=%d\n",this->_sequenceNumber_k__BackingField);
                printf("_currentAction_k__BackingField=%d\n",this->_currentAction_k__BackingField);
                printf("_isRunningAI_k__BackingField=%d\n",this->_isRunningAI_k__BackingField);
                printf("_makeCreature_k__BackingField=%d\n",this->_makeCreature_k__BackingField);
                printf("mai=%08X\n",this->mai);
                printf("_powerMonData=%08X\n",this->_powerMonData);
                printf("_mdata_k__BackingField=%08X\n",this->_mdata_k__BackingField);
                printf("_subordinatingObject_k__BackingField=%08X\n",this->_subordinatingObject_k__BackingField);
                printf("_monsterAIType=%d\n",this->_monsterAIType);
                printf("IsDestroyDirectingEffect=%d\n",this->IsDestroyDirectingEffect);
        }
};

class Camp: MonoObject{
public:
        long long int m_UnityRuntimeReferenceData; //8 VALUE size=8
        unsigned int members; //16 List System.Collections.Generic.List`1
        unsigned int coopPlayGUI; //20 Class CoopPlayDirectionGUI
        unsigned int OnDieMemberEvent; //24 Class OnDieMemberHandler
        unsigned int OnDeadMemberEvent; //28 Class OnDeadMemberHandler
        unsigned int OnEndCampTurnEvent; //32 Class OnEndTurnHandler
        unsigned int OnStartTurnOfMemberEvent; //36 Class OnStartTurnOfMemberHandler
        unsigned int OnGuildRaidScoreDirectingUIEvent; //40 Class OnGuildRaidScoresUIDirectingHandler
        unsigned char _turnType; //44 VALUE size=1 GameCampTurnType
        unsigned char unk0[3];
        unsigned int lastRemovedMemberIndex; //48 Int
        unsigned int currentMemberIndex; //52 Int
        unsigned int memberTurnCount; //56 Int
        unsigned int startDefenseTypeCount; //60 Int
        unsigned int startOffenseTypeCount; //64 Int
        unsigned int startBalanceTypeCount; //68 Int
        unsigned int startScopeTypeCount; //72 Int
        unsigned int startSupportTypeCount; //76 Int
        unsigned char allyTypeCounted; //80 Bool
        unsigned char _campType_k__BackingField; //81 VALUE size=1 GameCampType
        unsigned char _IsCoopPlay_k__BackingField; //82 Bool
        unsigned char _IsIntimacyCoopPlay_k__BackingField; //83 Bool
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->members);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->coopPlayGUI);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnDieMemberEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnDeadMemberEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnEndCampTurnEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnStartTurnOfMemberEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnGuildRaidScoreDirectingUIEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_turnType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->lastRemovedMemberIndex);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->currentMemberIndex);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->memberTurnCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->startDefenseTypeCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->startOffenseTypeCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->startBalanceTypeCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->startScopeTypeCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->startSupportTypeCount);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->allyTypeCounted);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_campType_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_IsCoopPlay_k__BackingField);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_IsIntimacyCoopPlay_k__BackingField);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("------ Show [%s] ------\n",pscan.GetVTableClassName((unsigned int)this->vtable));
                printf("members=%08X\n",this->members);
                printf("coopPlayGUI=%08X\n",this->coopPlayGUI);
                printf("OnDieMemberEvent=%08X\n",this->OnDieMemberEvent);
                printf("OnDeadMemberEvent=%08X\n",this->OnDeadMemberEvent);
                printf("OnEndCampTurnEvent=%08X\n",this->OnEndCampTurnEvent);
                printf("OnStartTurnOfMemberEvent=%08X\n",this->OnStartTurnOfMemberEvent);
                printf("OnGuildRaidScoreDirectingUIEvent=%08X\n",this->OnGuildRaidScoreDirectingUIEvent);
                printf("_turnType=%d\n",this->_turnType);
                printf("lastRemovedMemberIndex=%d\n",this->lastRemovedMemberIndex);
                printf("currentMemberIndex=%d\n",this->currentMemberIndex);
                printf("memberTurnCount=%d\n",this->memberTurnCount);
                printf("startDefenseTypeCount=%d\n",this->startDefenseTypeCount);
                printf("startOffenseTypeCount=%d\n",this->startOffenseTypeCount);
                printf("startBalanceTypeCount=%d\n",this->startBalanceTypeCount);
                printf("startScopeTypeCount=%d\n",this->startScopeTypeCount);
                printf("startSupportTypeCount=%d\n",this->startSupportTypeCount);
                printf("allyTypeCounted=%d\n",this->allyTypeCounted);
                printf("_campType_k__BackingField=%d\n",this->_campType_k__BackingField);
                printf("_IsCoopPlay_k__BackingField=%d\n",this->_IsCoopPlay_k__BackingField);
                printf("_IsIntimacyCoopPlay_k__BackingField=%d\n",this->_IsIntimacyCoopPlay_k__BackingField);
        }
};

class NPA_NPAccount: MonoObject{
public:
        unsigned int GAMEOBJECT_NAME; //8 String
        unsigned int mGameObject; //12 Class UnityEngine.GameObject
        unsigned int account; //16 Class UnityEngine.AndroidJavaObject
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->GAMEOBJECT_NAME)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->mGameObject);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->account);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("------ Show [%s] ------\n",pscan.GetVTableClassName((unsigned int)this->vtable));
                printf("GAMEOBJECT_NAME=[%s]\n",SaveCString(pscan.readMonoString(this->GAMEOBJECT_NAME)).c_str());
                printf("mGameObject=%08X\n",this->mGameObject);
                printf("account=%08X\n",this->account);
        }
};

class NPA_NPAccount_Nested: MonoObject{
public:
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("------ Show [%s] ------\n",pscan.GetVTableClassName((unsigned int)this->vtable));
        }
};

class NetworkManager: MonoObject{
public:
        long long int m_UnityRuntimeReferenceData; //8 VALUE size=8
        unsigned int chattingClient; //16 Class BestHTTP.SocketIO.SocketManager
        unsigned int chatCMDJoin; //20 SZARRAY System.String
        unsigned int chatCMDJoinAns; //24 SZARRAY System.String
        unsigned int chatCMDLeave; //28 SZARRAY System.String
        unsigned int chatCMDLeaveAns; //32 SZARRAY System.String
        unsigned int chatCMDChat; //36 SZARRAY System.String
        unsigned int _accessCode; //40 String
        unsigned int networkContentHelper; //44 Class NetworkContentHelper
        unsigned int _Send; //48 Class NetworkManager.Send
        unsigned int _siteID; //52 String
        unsigned int dungeonPostString; //56 String
        unsigned int dungeonResponseString; //60 String
        unsigned int retrySendPacketList; //64 List System.Collections.Generic.List`1
        unsigned int SENDER_ID_FOR_GCM; //68 String
        unsigned int msg; //72 String
        unsigned int npaResultMsg; //76 String
        unsigned int defferedLeaderboardID; //80 String
        unsigned int localPushIds; //84 SZARRAY System.Int32
        unsigned int OnCloseStartBannerEvent; //88 Class NetworkManager.OnCloseStartBannerHandler
        unsigned int packetNo; //92 Int
        long long int _lordIdx; //96 Int64
        unsigned char _isEnableLivePacket; //104 Bool
        unsigned char unk0[3];
        unsigned char gameUpdateStatus; //108 VALUE size=1 GameUpdateStatus
        unsigned char unk1[3];
        unsigned char npaRequestLoginType; //112 VALUE size=1 NPA.NPLoginType
        unsigned char unk2[3];
        unsigned char lastLoginType; //116 VALUE size=1 NPA.NPLoginType
        unsigned char unk3[3];
        unsigned char connectedWithAchievement; //120 Bool
        unsigned char connectedWithLeaderBoard; //121 Bool
        unsigned char connectedWithRecording; //122 Bool
        unsigned char unk4[1];
        unsigned int defferedLeaderboardType; //124 VALUE size=4
        long long int defferedOptainScore; //128 Int64
        unsigned char defferedAddValue; //136 Bool
        unsigned char updateLeaderboard; //137 Bool
        unsigned char unk5[2];
        float elapsedTimeForEnterToy; //140 float
        unsigned char npaLogoutRequestMode; //144 VALUE size=1 NetworkManager.NPALogoutRequestMode
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->chattingClient);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->chatCMDJoin);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->chatCMDJoinAns);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->chatCMDLeave);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->chatCMDLeaveAns);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->chatCMDChat);vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_accessCode)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->networkContentHelper);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_Send);vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_siteID)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->dungeonPostString)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->dungeonResponseString)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->retrySendPacketList);vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->SENDER_ID_FOR_GCM)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->msg)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->npaResultMsg)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->defferedLeaderboardID)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->localPushIds);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnCloseStartBannerEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->packetNo);vStringList.push_back(tmp);
                sprintf(tmp,"%lld",this->_lordIdx);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_isEnableLivePacket);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->gameUpdateStatus);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->npaRequestLoginType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->lastLoginType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->connectedWithAchievement);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->connectedWithLeaderBoard);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->connectedWithRecording);vStringList.push_back(tmp);
                sprintf(tmp,"%lld",this->defferedOptainScore);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->defferedAddValue);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->updateLeaderboard);vStringList.push_back(tmp);
                sprintf(tmp,"%f",this->elapsedTimeForEnterToy);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->npaLogoutRequestMode);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("------ Show [%s] ------\n",pscan.GetVTableClassName((unsigned int)this->vtable));
                printf("chattingClient=%08X\n",this->chattingClient);
                printf("chatCMDJoin=%08X\n",this->chatCMDJoin);
                printf("chatCMDJoinAns=%08X\n",this->chatCMDJoinAns);
                printf("chatCMDLeave=%08X\n",this->chatCMDLeave);
                printf("chatCMDLeaveAns=%08X\n",this->chatCMDLeaveAns);
                printf("chatCMDChat=%08X\n",this->chatCMDChat);
                printf("_accessCode=[%s]\n",SaveCString(pscan.readMonoString(this->_accessCode)).c_str());
                printf("networkContentHelper=%08X\n",this->networkContentHelper);
                printf("_Send=%08X\n",this->_Send);
                printf("_siteID=[%s]\n",SaveCString(pscan.readMonoString(this->_siteID)).c_str());
                printf("dungeonPostString=[%s]\n",SaveCString(pscan.readMonoString(this->dungeonPostString)).c_str());
                printf("dungeonResponseString=[%s]\n",SaveCString(pscan.readMonoString(this->dungeonResponseString)).c_str());
                printf("retrySendPacketList=%08X\n",this->retrySendPacketList);
                printf("SENDER_ID_FOR_GCM=[%s]\n",SaveCString(pscan.readMonoString(this->SENDER_ID_FOR_GCM)).c_str());
                printf("msg=[%s]\n",SaveCString(pscan.readMonoString(this->msg)).c_str());
                printf("npaResultMsg=[%s]\n",SaveCString(pscan.readMonoString(this->npaResultMsg)).c_str());
                printf("defferedLeaderboardID=[%s]\n",SaveCString(pscan.readMonoString(this->defferedLeaderboardID)).c_str());
                printf("localPushIds=%08X\n",this->localPushIds);
                printf("OnCloseStartBannerEvent=%08X\n",this->OnCloseStartBannerEvent);
                printf("packetNo=%d\n",this->packetNo);
                printf("_lordIdx=%lld\n",this->_lordIdx);
                printf("_isEnableLivePacket=%d\n",this->_isEnableLivePacket);
                printf("gameUpdateStatus=%d\n",this->gameUpdateStatus);
                printf("npaRequestLoginType=%d\n",this->npaRequestLoginType);
                printf("lastLoginType=%d\n",this->lastLoginType);
                printf("connectedWithAchievement=%d\n",this->connectedWithAchievement);
                printf("connectedWithLeaderBoard=%d\n",this->connectedWithLeaderBoard);
                printf("connectedWithRecording=%d\n",this->connectedWithRecording);
                printf("defferedOptainScore=%lld\n",this->defferedOptainScore);
                printf("defferedAddValue=%d\n",this->defferedAddValue);
                printf("updateLeaderboard=%d\n",this->updateLeaderboard);
                printf("elapsedTimeForEnterToy=%f\n",this->elapsedTimeForEnterToy);
                printf("npaLogoutRequestMode=%d\n",this->npaLogoutRequestMode);
        }
};

class SkillData: MonoObject{
public:
        unsigned int _skillName; //8 String
        unsigned int _creatureName; //12 String
        unsigned int _tooltip; //16 String
        unsigned int _iconName; //20 String
        unsigned int _precondition; //24 String
        unsigned int _skillId; //28 Int
        unsigned char _skillType; //32 UByte
        unsigned char _skillTarget; //33 UByte
        unsigned char _targetNo; //34 UByte
        unsigned char _range; //35 UByte
        unsigned char _skillRangeType; //36 UByte
        unsigned char _skillEffectRange; //37 UByte
        unsigned char _skillEffectRangeType; //38 UByte
        unsigned char unk0[1];
        float _effectChance; //40 float
        float _effectChanceFactor; //44 float
        unsigned char _turnStart; //48 UByte
        unsigned char _turnEnd; //49 UByte
        unsigned char _skillRespawn; //50 UByte
        unsigned char unk1[1];
        unsigned int _effect01; //52 Int
        unsigned int _effect02; //56 Int
        unsigned int _effect03; //60 Int
        unsigned int _effect04; //64 Int
        unsigned char _cooltime; //68 UByte
        unsigned char _useParameterKind; //69 UByte
        unsigned char unk2[2];
        unsigned int _useParameter; //72 Int
        unsigned char _heightAttack; //76 UByte
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_skillName)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_creatureName)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_tooltip)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_iconName)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->_precondition)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skillId);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skillType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skillTarget);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_targetNo);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_range);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skillRangeType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skillEffectRange);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skillEffectRangeType);vStringList.push_back(tmp);
                sprintf(tmp,"%f",this->_effectChance);vStringList.push_back(tmp);
                sprintf(tmp,"%f",this->_effectChanceFactor);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_turnStart);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_turnEnd);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_skillRespawn);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_effect01);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_effect02);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_effect03);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_effect04);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_cooltime);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_useParameterKind);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_useParameter);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_heightAttack);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("------ Show [%s] ------\n",pscan.GetVTableClassName((unsigned int)this->vtable));
                printf("_skillName=[%s]\n",SaveCString(pscan.readMonoString(this->_skillName)).c_str());
                printf("_creatureName=[%s]\n",SaveCString(pscan.readMonoString(this->_creatureName)).c_str());
                printf("_tooltip=[%s]\n",SaveCString(pscan.readMonoString(this->_tooltip)).c_str());
                printf("_iconName=[%s]\n",SaveCString(pscan.readMonoString(this->_iconName)).c_str());
                printf("_precondition=[%s]\n",SaveCString(pscan.readMonoString(this->_precondition)).c_str());
                printf("_skillId=%d\n",this->_skillId);
                printf("_skillType=%d\n",this->_skillType);
                printf("_skillTarget=%d\n",this->_skillTarget);
                printf("_targetNo=%d\n",this->_targetNo);
                printf("_range=%d\n",this->_range);
                printf("_skillRangeType=%d\n",this->_skillRangeType);
                printf("_skillEffectRange=%d\n",this->_skillEffectRange);
                printf("_skillEffectRangeType=%d\n",this->_skillEffectRangeType);
                printf("_effectChance=%f\n",this->_effectChance);
                printf("_effectChanceFactor=%f\n",this->_effectChanceFactor);
                printf("_turnStart=%d\n",this->_turnStart);
                printf("_turnEnd=%d\n",this->_turnEnd);
                printf("_skillRespawn=%d\n",this->_skillRespawn);
                printf("_effect01=%d\n",this->_effect01);
                printf("_effect02=%d\n",this->_effect02);
                printf("_effect03=%d\n",this->_effect03);
                printf("_effect04=%d\n",this->_effect04);
                printf("_cooltime=%d\n",this->_cooltime);
                printf("_useParameterKind=%d\n",this->_useParameterKind);
                printf("_useParameter=%d\n",this->_useParameter);
                printf("_heightAttack=%d\n",this->_heightAttack);
        }
};


class MessageBoxManager: MonoObject{
public:
        long long int m_UnityRuntimeReferenceData; //8 VALUE size=8
        unsigned int currectMessageBoxData; //16 Class MessageBoxData
        unsigned int messageBoxDataQueue; //20 List System.Collections.Generic.Queue`1
        unsigned int messageBox; //24 Class MessageBoxGUI
        unsigned int messageBoxGUIPortrait; //28 Class MessageBoxGUIPortrait
        unsigned int toastMessageBox; //32 Class ToastMessageBoxGUI
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->currectMessageBoxData);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->messageBoxDataQueue);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->messageBox);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->messageBoxGUIPortrait);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->toastMessageBox);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("------ Show [%s] ------\n",pscan.GetVTableClassName((unsigned int)this->vtable));
                printf("currectMessageBoxData=%08X\n",this->currectMessageBoxData);
                printf("messageBoxDataQueue=%08X\n",this->messageBoxDataQueue);
                printf("messageBox=%08X\n",this->messageBox);
                printf("messageBoxGUIPortrait=%08X\n",this->messageBoxGUIPortrait);
                printf("toastMessageBox=%08X\n",this->toastMessageBox);
        }
};

class MessageBoxData: MonoObject{
public:
        unsigned int messageText; //8 String
        unsigned int titleMessage; //12 String
        unsigned int warningMessage; //16 String
        unsigned int OKButtonText; //20 String
        unsigned int cancelButtonText; //24 String
        unsigned int checkBoxText; //28 String
        unsigned int _expandParams; //32 List System.Collections.Generic.List`1
        unsigned int OnResultHandler; //36 Class MessageBoxData.DelegateResultHanlder
        unsigned char messageBoxButtonType; //40 VALUE size=1 MessageBoxShowType
        unsigned char unk0[3];
        unsigned char isDevelopeMessage; //44 Bool
        unsigned char unk1[3];
        unsigned char OKButtonState; //48 VALUE size=1 ButtonState
        unsigned char unk2[3];
        float autoCloseTime; //52 float
        unsigned char messageBoxIconType; //56 VALUE size=1 MessageBoxIconType
        unsigned char unk3[3];
        long long int instanceID; //60 Int64
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->messageText)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->titleMessage)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->warningMessage)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->OKButtonText)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->cancelButtonText)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"\"%s\"",SaveCString(pscan.readMonoString(this->checkBoxText)).c_str());vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->_expandParams);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OnResultHandler);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->messageBoxButtonType);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->isDevelopeMessage);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->OKButtonState);vStringList.push_back(tmp);
                sprintf(tmp,"%f",this->autoCloseTime);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->messageBoxIconType);vStringList.push_back(tmp);
                sprintf(tmp,"%lld",this->instanceID);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("------ Show [%s] ------\n",pscan.GetVTableClassName((unsigned int)this->vtable));
                printf("messageText=[%s]\n",SaveCString(pscan.readMonoString(this->messageText)).c_str());
                printf("titleMessage=[%s]\n",SaveCString(pscan.readMonoString(this->titleMessage)).c_str());
                printf("warningMessage=[%s]\n",SaveCString(pscan.readMonoString(this->warningMessage)).c_str());
                printf("OKButtonText=[%s]\n",SaveCString(pscan.readMonoString(this->OKButtonText)).c_str());
                printf("cancelButtonText=[%s]\n",SaveCString(pscan.readMonoString(this->cancelButtonText)).c_str());
                printf("checkBoxText=[%s]\n",SaveCString(pscan.readMonoString(this->checkBoxText)).c_str());
                printf("_expandParams=%08X\n",this->_expandParams);
                printf("OnResultHandler=%08X\n",this->OnResultHandler);
                printf("messageBoxButtonType=%d\n",this->messageBoxButtonType);
                printf("isDevelopeMessage=%d\n",this->isDevelopeMessage);
                printf("OKButtonState=%d\n",this->OKButtonState);
                printf("autoCloseTime=%f\n",this->autoCloseTime);
                printf("messageBoxIconType=%d\n",this->messageBoxIconType);
                printf("instanceID=%lld\n",this->instanceID);
        }
};

class FantasyWarTactic_FWT: MonoObject{
public:
        long long int m_UnityRuntimeReferenceData; //8 VALUE size=8
        unsigned int serverWriter; //16 Class System.IO.StreamWriter
        unsigned int lua; //20 Class LuaInterface.Lua
        unsigned int buttonScripts; //24 List System.Collections.Generic.List`1
        unsigned int mySend; //28 Class FantasyWarTactic.FWT.Send
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->serverWriter);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->lua);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->buttonScripts);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->mySend);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("------ Show [%s] ------\n",pscan.GetVTableClassName((unsigned int)this->vtable));
                printf("serverWriter=%08X\n",this->serverWriter);
                printf("lua=%08X\n",this->lua);
                printf("buttonScripts=%08X\n",this->buttonScripts);
                printf("mySend=%08X\n",this->mySend);
        }
};

class PauseInGameGUI: MonoObject{
public:
        long long int m_UnityRuntimeReferenceData; //8 VALUE size=8
        unsigned int OnCloseEvent; //16 Class WindowGUI.OnCloseHandler
        unsigned char isPreparingWindow; //20 Bool
        unsigned char unk0[3];
        unsigned int uiTabButtonInMission; //24 SZARRAY SpriteOnOff
        unsigned int uiTabButtonInOther; //28 SZARRAY SpriteOnOff
        unsigned int uiGameQuitButton; //32 Class UIButton
        unsigned int uiCloseButton; //36 Class UIButton
        unsigned int uiMissionInfo; //40 Class PauseMissionInfo
        unsigned int uiMapInfo; //44 Class PauseMapInfo
        unsigned int uiGraphcis; //48 Class PauseInOption
        unsigned int uiTitle; //52 Class UILabel
        unsigned int uiTaticsParentGo; //56 Class UnityEngine.GameObject
        unsigned int uiPriorityLabel; //60 Class UILabel
        unsigned int uiTileStrategyLabel; //64 Class UILabel
        unsigned int uiDirectionLabe; //68 Class UILabel
        unsigned int uiCoopLabel; //72 Class UILabel
        unsigned char missionType; //76 VALUE size=1 DungeonMissionType
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->OnCloseEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->isPreparingWindow);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->uiTabButtonInMission);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->uiTabButtonInOther);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->uiGameQuitButton);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->uiCloseButton);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->uiMissionInfo);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->uiMapInfo);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->uiGraphcis);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->uiTitle);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->uiTaticsParentGo);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->uiPriorityLabel);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->uiTileStrategyLabel);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->uiDirectionLabe);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->uiCoopLabel);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->missionType);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("------ Show [%s] ------\n",pscan.GetVTableClassName((unsigned int)this->vtable));
                printf("OnCloseEvent=%08X\n",this->OnCloseEvent);
                printf("isPreparingWindow=%d\n",this->isPreparingWindow);
                printf("uiTabButtonInMission=%08X\n",this->uiTabButtonInMission);
                printf("uiTabButtonInOther=%08X\n",this->uiTabButtonInOther);
                printf("uiGameQuitButton=%08X\n",this->uiGameQuitButton);
                printf("uiCloseButton=%08X\n",this->uiCloseButton);
                printf("uiMissionInfo=%08X\n",this->uiMissionInfo);
                printf("uiMapInfo=%08X\n",this->uiMapInfo);
                printf("uiGraphcis=%08X\n",this->uiGraphcis);
                printf("uiTitle=%08X\n",this->uiTitle);
                printf("uiTaticsParentGo=%08X\n",this->uiTaticsParentGo);
                printf("uiPriorityLabel=%08X\n",this->uiPriorityLabel);
                printf("uiTileStrategyLabel=%08X\n",this->uiTileStrategyLabel);
                printf("uiDirectionLabe=%08X\n",this->uiDirectionLabe);
                printf("uiCoopLabel=%08X\n",this->uiCoopLabel);
                printf("missionType=%d\n",this->missionType);
        }
};

class CodeStage_AntiCheat_Detectors_InjectionDetector: MonoObject{
public:
        long long int m_UnityRuntimeReferenceData; //8 VALUE size=8
        unsigned int detectionEvent; //16 Class UnityEngine.Events.UnityEvent
        unsigned int detectionAction; //20 Class UnityEngine.Events.UnityAction
        unsigned char autoStart; //24 Bool
        unsigned char keepAlive; //25 Bool
        unsigned char autoDispose; //26 Bool
        unsigned char detectionEventHasListener; //27 Bool
        unsigned char isRunning; //28 Bool
        unsigned char started; //29 Bool
        unsigned char unk0[2];
        unsigned int detectionEvent2; //32 List UnityEngine.Events.UnityEvent`1
        unsigned int detectionAction2; //36 List UnityEngine.Events.UnityAction`1
        unsigned int allowedAssemblies; //40 SZARRAY CodeStage.AntiCheat.Detectors.InjectionDetector.AllowedAssembly
        unsigned int hexTable; //44 SZARRAY System.String
        unsigned char signaturesAreNotGenuine; //48 Bool
        std::string ToString(ProcessScanner& pscan){
                char tmp[1024];
                std::vector<std::string> vStringList;
                sprintf(tmp,"%d",this->detectionEvent);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->detectionAction);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->autoStart);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->keepAlive);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->autoDispose);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->detectionEventHasListener);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->isRunning);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->started);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->detectionEvent2);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->detectionAction);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->allowedAssemblies);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->hexTable);vStringList.push_back(tmp);
                sprintf(tmp,"%d",this->signaturesAreNotGenuine);vStringList.push_back(tmp);
                std::string ret;
                ret += "{";
                ret += ConcatStrings(vStringList,",");
                ret += "},";
                return ret;
        }
        void Show(ProcessScanner& pscan){
                printf("------ Show [%s] ------\n",pscan.GetVTableClassName((unsigned int)this->vtable));
                printf("detectionEvent=%08X\n",this->detectionEvent);
                printf("detectionAction=%08X\n",this->detectionAction);
                printf("autoStart=%d\n",this->autoStart);
                printf("keepAlive=%d\n",this->keepAlive);
                printf("autoDispose=%d\n",this->autoDispose);
                printf("detectionEventHasListener=%d\n",this->detectionEventHasListener);
                printf("isRunning=%d\n",this->isRunning);
                printf("started=%d\n",this->started);
                printf("detectionEvent2=%08X\n",this->detectionEvent2);
                printf("detectionAction=%08X\n",this->detectionAction);
                printf("allowedAssemblies=%08X\n",this->allowedAssemblies);
                printf("hexTable=%08X\n",this->hexTable);
                printf("signaturesAreNotGenuine=%d\n",this->signaturesAreNotGenuine);
        }
};

#endif /* FWTMONOOBJECT_HPP */

