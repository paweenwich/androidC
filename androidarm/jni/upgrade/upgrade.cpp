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

LuaShell luaShell;
Logger logger(NULL,0);
CharacterDataIndexManager characterDataIndexManager;
unsigned int luaResultInt;

struct MonsterData monsters[] = {
#include "../../data/monsters.inc"    
};

struct CreatureData creatures[] = {
#include "../../data/creatures.inc"    
};

struct HeroData heros[] = {
#include "../../data/heros.inc"    
};

LuaScript *script;// = new LuaScript(tolua_lua_hello_open);
_CreatureData paramCharacterData;
bool flgShouldUpdate = false;
char luaMonsterList[1024];

struct HeroData * FindHeroByName(char *name)
{
    for(int i=0;i<heros[i].creatureId !=0;i++){
	if(strcasecmp(name,heros[i].name)==0){
	    return &heros[i];
	}
    }
    return NULL;
}


void FindCreatureByName(char *name,std::vector<struct CreatureData *> &vret)
{
    for(int i=0;i<creatures[i].creatureId !=0;i++){
	if(strcasecmp(name,creatures[i].name)==0){
	    //return &creatures[i];
            vret.push_back(&creatures[i]);
	}
    }
    //return NULL;
}

CreatureData *FindCreatureByID(int creatureID)
{
    for(int i=0;i<creatures[i].creatureId !=0;i++){
	if(creatures[i].creatureId == creatureID){
	    return &creatures[i];
	}
    }
    return NULL;
}

void FindMonsterDataByID(int creatureID,std::vector<struct MonsterData *> &vret)
{
    for(int i=0;i<monsters[i].monsterId !=0;i++){
	if(monsters[i].creatureid == creatureID){
	    //return &creatures[i];
            vret.push_back(&monsters[i]);
	}
    }

}

void GetHeroName(char *hernoName,std::vector<std::string> &vNames)
{
    char *pch = strtok (hernoName,"-._:,/");
    while (pch != NULL)
    {
	vNames.push_back(std::string(pch));
	printf ("Hero %s\n",pch);
	pch = strtok (NULL,"-._:,/");
    }
}


#define MONSTER_FILTER  0x01
#define HERO_FILTER     0x02
#define ALL_FILTER      (MONSTER_FILTER|HERO_FILTER)


void GetScanData(std::vector<std::string> &vNames,std::vector<ScanData> &vSearchList,int filter)
{
    for(int n=0;n<vNames.size();n++){
	char heroName[64];
	strcpy(heroName,vNames[n].c_str());
            std::vector<struct CreatureData *> vMonster;
            FindCreatureByName(heroName,vMonster);
	    if(vMonster.size()>0){
		for(int i=0;i<vMonster.size();i++){
		    struct CreatureData *pCreature = vMonster[i];
		    printf("Creature %s found %08X, %08X\n",pCreature->name,pCreature->creatureId,pCreature->combatType);
		    ScanData sd;
		    SearchData *psd = (SearchData *)&sd;
		    psd->creatureId = pCreature->creatureId;
		    psd->combatType = pCreature->combatType;
		    psd->baseHp = pCreature->baseHp;
		    sd.size = sizeof(SearchData);
                    if(psd->creatureId >= 0x200000){
                        if(filter & MONSTER_FILTER){
                            printf("Add monster\n");
                            vSearchList.push_back(sd);
                        }
                    }else{
                        if(filter & HERO_FILTER){
                            printf("Add Hero\n");
                            vSearchList.push_back(sd);
                        }
                    }
		}
		std::vector<struct MonsterData *> vMonsterData;
		for(int i=0;i<vMonster.size();i++){
		    FindMonsterDataByID(vMonster[i]->creatureId,vMonsterData);
		}
		printf("Found MonsterData %d (Do nothing for now)\n",vMonsterData.size());
	    }else{
		printf("WANRING: %s not found\n",heroName);
	    }
//        }
    }
    
}


void upgrade(int pid,char *nameParam,char *cmd)
{
    int filter = ALL_FILTER;
    if(strcmp(cmd,"UpdateMonster")==0){
        filter = MONSTER_FILTER;
    }
    if(strcmp(cmd,"Up")==0){
        filter = HERO_FILTER;
    }
    if(strcmp(cmd,"Down")==0){
        filter = HERO_FILTER;
    }
    printf("Filter=%02X\n",filter);
    std::vector<std::string> vNames;
    std::vector<ScanData> vSearchList;
    // check if heroName contain sperator "-","." or "_"
    GetHeroName(nameParam,vNames);
    GetScanData(vNames,vSearchList,filter);
    //return;
    ProcessScanner pscan;
    if(pscan.open(pid)){
	printf("Open success\n");
	std::vector<ScanResult> result;
	std::vector<WriteData> vWriteData;
	pscan.scanRange(0x70000000,0x90000000,vSearchList,result,4,true);
	printf("Found %d/%d\n",result.size(),vSearchList.size());
	if(result.size()==vSearchList.size()){
	    for(int i=0;i<result.size();i++){
		//CharacterData charData;
		//pscan.dump(result[i].addr,64);
		pscan.read(result[i].addr,sizeof(paramCharacterData),(unsigned int)&paramCharacterData);
                flgShouldUpdate = true;
		//if(script->execString("if UpdateCharacter ~= nil then return true else return false end")){
                char command[256];
                sprintf(command,"%s()",cmd);
		script->execString(command);
                if(flgShouldUpdate){
                    WriteData w;
                    w.load(result[i].addr,(unsigned char *)&paramCharacterData,sizeof(paramCharacterData));
                    vWriteData.push_back(w);
                }
		//pscan.write(result[i].addr,sizeof(charData),(unsigned int)&charData);
		//pscan.dump(result[i].addr,64);
	    }
	    if(vWriteData.size()>0){
		pscan.writeAll(vWriteData);
		//printf("RESULT: Update done\n");
	    }else{
                //printf("RESULT: Noting to update\n");
            }
	}else{
	    for(int i=0;i<result.size();i++){
	       //CharacterData charData;
	       pscan.dump(result[i].addr,64);
	    }
	    //printf("RESULT: Character count not match\n");
	}
	pscan.close();
    }else{
	//printf("RESULT: can not open %d\n",pid);
    }
}

struct CompareByScanData {
    // This is a pointer-to-member, it represents a member of class T
    // The data member has type U
    bool operator()(const ScanResult &lhs, const ScanResult &rhs) {
	SearchData *lp = (SearchData *)&lhs.scanData;
	SearchData *rp = (SearchData *)&rhs.scanData;
        return lp->creatureId < rp->creatureId;
    }
};


void index(int pid)
{
    characterDataIndexManager.index.clear();
    std::vector<ScanData> vSearchList;
    printf("Index Mode\n");
    ScanData sd;
    //unsigned int *p = (unsigned int *)&sd.data[0];
    
    std::vector<std::string> vNames;
    GetHeroName("Kai",vNames);
    GetScanData(vNames,vSearchList,HERO_FILTER);
    
    /*struct HeroData *pHero = FindHeroByName("Kai");
    //std::vector<std::string> vNames;
    for(int i=0;i<5;i++){
	ScanData sd;
	SearchData *psd = (SearchData *)&sd;
	psd->creatureId = pHero->creatureId + i;
	psd->combatType = pHero->combatType;
	psd->baseHp = pHero->baseHp;
	sd.size = sizeof(SearchData);
	vSearchList.push_back(sd);
	      //logger.logHex((unsigned char *)&sd,sd.size);
    }*/
    std::vector<ScanResult> result;
    ProcessScanner pscan;
    if(pscan.open(pid)){
	pscan.scanRange(0x70000000,0x90000000,vSearchList,result,4,true);
	printf("result.size()=%d vSearchList.size()=%d\n",result.size(),vSearchList.size());
	ScanData sd;
	std::vector<ScanData> vSearchList2;
	unsigned int *p = (unsigned int *)&sd;
	if(result.size() == vSearchList.size()){
	    std::sort(result.begin(), result.end(),CompareByScanData());
	    for(int i=0;i<result.size();i++){
		p[i] = result[i].addr - ((5+2)*4);
		SearchData *psd = (SearchData *)&result[i].scanData;
		//printf("%d %08X %08X\n",psd->creatureId,result[i].addr,p[i]);
	    }
	    sd.size = sizeof(int) * vSearchList.size();
	    logger.logHex((unsigned char *)&sd,sd.size);
	    vSearchList2.push_back(sd);
	    std::vector<ScanResult> result2;
	    pscan.scanRange(0x70000000,0x90000000,vSearchList2,result2,4,true);
	    if(result2.size() == 1){
		printf("Found %08X\n",result2[0].addr);
		unsigned int objaddr = result2[0].addr - (3*4);  //[vtable][lock][size]
		printf("Found CreatureDataManager._data at %08X\n",objaddr);
		unsigned int count=0;
		pscan.readInt(objaddr + 8,count);
		printf("count=%d\n",count);
		for(int i=0;i<count;i++){
		    unsigned int targetAddr = (objaddr + 12) + (i*4);
		    unsigned int addr_creatureData_obj;
		    pscan.readInt(targetAddr,addr_creatureData_obj);
		    //printf("#%d %08X\n",i,addr_creatureData_obj);
		    unsigned int addr_creatureData =addr_creatureData_obj +  ((5+2)*4);
		    _CreatureData cdata;
		    pscan.read(addr_creatureData,sizeof(_CreatureData),(unsigned int)&cdata);
		    
		    unsigned int nameAddr = pscan.ReadInt(addr_creatureData_obj+12);
		    char *strMonName = pscan.readMonoString(nameAddr);
		    printf("objAddr=%08X  [%s]\n",addr_creatureData_obj,strMonName);
		    //pscan.dump(addr_creatureData_obj,32);
		    CreatureData *creaturep = FindCreatureByID(cdata.creatureId);
		    if(creaturep!=NULL){
			printf("Index [%s] %d %d\n",creaturep->name,cdata.combatType,cdata.baseHp);
			// put into cache
			ScanResult sr;
			SearchData *psd = (SearchData *)&sr.scanData;
			psd->creatureId = cdata.creatureId;
			psd->combatType = cdata.combatType;
			psd->baseHp = cdata.baseHp;
			sr.scanData.size = sizeof(SearchData);
			sr.addr = addr_creatureData;
			pscan.cache.put(sr);
			//
			characterDataIndexManager.put(cdata.creatureId,addr_creatureData);
		    }else{
			//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"","","",""},
			printf("/*NEW*/ {%d,%d,%d,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\"%s\",\"\",\"\",\"\"},\n",
			    cdata.creatureId,cdata.combatType,cdata.baseHp,strMonName
			);
			//printf("%d %d %d not found\n",cdata.creatureId,cdata.combatType,cdata.baseHp);
		    }
		}
		pscan.cache.save();
		characterDataIndexManager.save();
		printf("Index done %d",pscan.cache.cache.size());
	    }else{
		printf("Not Found\n");
	    }
	}else{
	    printf("index: Scan not found\n");
	}
	pscan.close();
    }
}

void dumpAddr(int pid,unsigned int addr)
{
    printf("dumpAddr %d %08X\n",pid,addr);
    ProcessScanner pscan;
    pscan.logger = &logger;
    if(pscan.open(pid))
    {
	pscan.dump(addr,64);
	pscan.close();
    }
}

_CreatureData* GetCurrentCharacterData(ProcessScanner *pscan,int creatureID)
{
    static _CreatureData ret;
    unsigned int addr = characterDataIndexManager.get(creatureID);
    if(addr!=0){
	pscan->read(addr,sizeof(_CreatureData),(unsigned int)&ret);
	return &ret;
    }
    return NULL;
}

void status(int pid)
{
    ProcessScanner pscan;
    if(pscan.open(pid)){
	for(int i=0;i<heros[i].creatureId !=0;i++){
	    bool isChanged = false;
	    for(int j=0;(j<5) && (isChanged==false);j++){
		int creatureID = heros[i].creatureId + j;
		_CreatureData *cdata = GetCurrentCharacterData(&pscan,creatureID);
		if(cdata==NULL){
		    printf("# status creatureID=%d not found\n",creatureID);
		}
		CreatureData *cdataFromDB = FindCreatureByID(creatureID);
		if((cdata!=NULL)&&(cdataFromDB!=NULL)){
		    //isChanged = cdataFromDB->movePoint != cdata->movePoint;
		    isChanged = (cdata->baseHp == 70000);
		    //printf("# %d\n",cdata->baseHp);
		}
		
	    }
	    std::string name = heros[i].name;
	    std::replace(name.begin(),name.end(),' ', '_');
	    if(isChanged){
		printf("STATUS: %s CHANGED\n",name.c_str());
	    }else{
		printf("STATUS: %s ORIGINAL\n",name.c_str());
	    }
	}
	pscan.close();
    }
}

void dumpCreature(int pid)
{
    ProcessScanner pscan;
    if(pscan.open(pid)){
	// Find CreatureDataManager class 
	unsigned int creatureDataManager_classAddr = pscan.MonoFindClass("CreatureDataManager");
	printf("creatureDataManager_classAddr = 0x%08X\n",creatureDataManager_classAddr);
	if(creatureDataManager_classAddr!=0){
	    unsigned int creatureDataManager_vTableAddr = pscan.MonoFindVtable(creatureDataManager_classAddr);
	    printf("creatureDataManager_vTableAddr = 0x%08X\n",creatureDataManager_vTableAddr);
	    if(creatureDataManager_vTableAddr!=0){
		pscan.MonoFindObject(creatureDataManager_vTableAddr);
		// check all possible object to find real object
		unsigned int creatureData_arrayAddr = 0;
		for(int i=0;i<pscan.vFindObjectResult.size();i++){
		    CreatureDataManager cm;
		    pscan.read(pscan.vFindObjectResult[i],sizeof(CreatureDataManager),(unsigned int)&cm);
		    if(pscan.isDataAddress(cm._data)){
			MonoObjectData mo = pscan.readMonoObject(cm._data);
			char *className = mo.GetName(pscan);
			printf("checking %s\n",className);
			if(strcmp(className,"CreatureData[]")==0){
			    creatureData_arrayAddr = cm._data;
			    
			    break;
			}
		    }
		}
		if(creatureData_arrayAddr!=0){
		    printf("Found creatureData[] at 0x%08X\n",creatureData_arrayAddr);
		    MonoArray ar;
		    pscan.read(creatureData_arrayAddr,sizeof(ar),(unsigned int)&ar);
		    printf("size=%ld\n",ar.max_length);
		    int bufferSize = ar.max_length * sizeof(int);
		    unsigned int *pAddr = (unsigned int *)malloc(bufferSize);
		    pscan.read(creatureData_arrayAddr + 16,bufferSize,(unsigned int)pAddr);
		    if(ar.max_length>0){
			FILE *fout = fopen("creatures.inc","w");
			if(fout!=NULL){
			    for(int i=0;i<ar.max_length;i++){
				CreatureDataMonoObject cd;
				pscan.read(pAddr[i],sizeof(cd),(unsigned int)&cd);
				fprintf(fout,"%s\n",cd.ToString(pscan).c_str());
			    };
			}
			fprintf(fout,"{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\"\",\"\",\"\",\"\"},\n");
			fclose(fout);
			printf("creatures.inc created for %ld records\n",ar.max_length);
		    }
		    free(pAddr);
		}
		
	    }
	}
	pscan.close();
    }    
    return;
}

void GetDimensionBreakManager(ProcessScanner &pscan)
{
    unsigned int addr = pscan.GetStaticClassFieldInt("DimensionBreakManager","_instance");
    printf("0x%08X\n",addr);
    char *str = pscan.GetStaticClassFieldCString("DimensionBreakManager","SAVE_FILE_PATH_FORMAT");
    printf("%s\n",str);
    
}



template<typename T>
void DumpDataManager(ProcessScanner &pscan,char *managerName,char *fileName)
{
    unsigned int instanceAddr = pscan.GetStaticClassFieldInt(managerName,"_instance");
    printf("instanceAddr %08X\n",instanceAddr);
    unsigned int array_addr = pscan.GetInstanceClassFieldInt(instanceAddr,managerName,"_data");
    if(array_addr!=0){
        MonoArray ar;
        pscan.read(array_addr,sizeof(ar),(unsigned int)&ar);
        printf("size=%ld\n",ar.max_length);
        int bufferSize = ar.max_length * sizeof(int);
        unsigned int *pAddr = (unsigned int *)malloc(bufferSize);
        pscan.read(array_addr + 16,bufferSize,(unsigned int)pAddr);
        if(ar.max_length>0){
            FILE *fout = fopen(fileName,"w");
            if(fout!=NULL){
                for(int i=0;i<ar.max_length;i++){
                    T cd;
                    pscan.read(pAddr[i],sizeof(cd),(unsigned int)&cd);
                    //printf("%s\n",cd.ToString(pscan).c_str());
                    fprintf(fout,"%s\n",cd.ToString(pscan).c_str());
                };
            }
            //fprintf(fout,"{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\"\",\"\",\"\",\"\"},\n");
            fclose(fout);
            printf("%s created for %ld records\n",fileName,ar.max_length);
        }
        free(pAddr);        
    }    
}

template<typename T>
T DumpInstance(ProcessScanner &pscan,char *className,char *instanceName = "_instance")
{
    T cd;
    unsigned int instanceAddr = pscan.GetStaticClassFieldInt(className,instanceName);
    printf("instanceAddr %08X\n",instanceAddr);  
    if(instanceAddr!=0){
	MonoObjectData objData = pscan.readMonoObject(instanceAddr);
	MonoVTableData vTableData = objData.GetVTable(pscan);
	if(vTableData.isInit()){
	    vTableData.show(pscan);    
	    pscan.read(instanceAddr,sizeof(cd),(unsigned int)&cd);
	    cd.Show(pscan); 
	}else{
	    printf("VTable not found\n");
	}
    }
    return cd;    
}

BattleManager GetBattleManager(ProcessScanner &pscan)
{
    BattleManager bm = DumpInstance<BattleManager>(pscan,"BattleManager");
    if(bm._mainCastee!=0){
	char instanceClassName[64];
	strcpy(instanceClassName,pscan.GetInstanceClassName(bm._mainCastee));
	if(strcmp(instanceClassName,"Player")==0){
	    Player _mainCastee = pscan.read<Player>(bm._mainCastee);
	    _mainCastee.Show(pscan); 
	    printf("_data = %s\n",pscan.GetInstanceClassName(_mainCastee._data));
	    printf("_assets = %s\n",pscan.GetInstanceClassName(_mainCastee._assets));
	    printf("_ai = %s\n",pscan.GetInstanceClassName(_mainCastee._ai));
	}
	if(strcmp(instanceClassName,"Monster")==0){
	    Monster _mainCastee = pscan.read<Monster>(bm._mainCastee);
	    _mainCastee.Show(pscan); 
	}
	{
	printf("-- _attackerMemberList [%s]---\n",pscan.GetInstanceClassName(bm._attackerMemberList));
	MonoList monoList =  pscan.read<MonoList>(bm._attackerMemberList);
	printf("%08X %d %d\n",(unsigned int)monoList._items,monoList._size,monoList._version);
	printf("-- _items [%s]---\n",pscan.GetInstanceClassName((unsigned int)monoList._items));
	MonoArray monoArray = pscan.read<MonoArray>((unsigned int)monoList._items);
	printf("%ld\n",monoArray.max_length);
	}
	
	
	{
	printf("-- _targetMemberList [%s]---\n",pscan.GetInstanceClassName(bm._targetMemberList));
	MonoList monoList =  pscan.read<MonoList>(bm._targetMemberList);
	printf("%08X %d %d\n",(unsigned int)monoList._items,monoList._size,monoList._version);
	printf("-- _items [%s]---\n",pscan.GetInstanceClassName((unsigned int)monoList._items));
	MonoArray monoArray = pscan.read<MonoArray>((unsigned int)monoList._items);
	printf("%ld\n",monoArray.max_length);
	}
    }
    return bm;
}

void GetDungeonDataManager(ProcessScanner &pscan)
{
    DumpDataManager<DungeonData>(pscan,"DungeonDataManager","DungeonData.inc");
}

void GetEnchantData(ProcessScanner &pscan)
{
    DumpDataManager<EnchantData>(pscan,"EnchantDataManager","EnchantData.inc");
}

void GetGradeReward(ProcessScanner &pscan)
{
    DumpDataManager<GradeReward>(pscan,"GradeRewardManager","GradeReward.inc");
}

void GetMapObjectData(ProcessScanner &pscan)
{
    DumpDataManager<MapObjectData>(pscan,"MapObjectDataManager","MapObjectData.inc");
}

void GetActiveData(ProcessScanner &pscan)
{
    DumpDataManager<ActiveData>(pscan,"ActiveDataManager","ActiveData.inc");
}


void GetGameConfig(ProcessScanner &pscan)
{
    unsigned int instanceAddr = pscan.GetStaticClassFieldInt("GameConfig","_instance");
    printf("instanceAddr %08X\n",instanceAddr);
    GameConfig cd;
    pscan.read(instanceAddr,sizeof(cd),(unsigned int)&cd);
    //printf("%s\n",cd.ToString(pscan).c_str());
    cd.Show(pscan);
    pscan.PutInstanceClassField(instanceAddr,"GameConfig","_isShowPromotion",(unsigned int)0);
    pscan.read(instanceAddr,sizeof(cd),(unsigned int)&cd);
    cd.Show(pscan);    
}

void GetRepeatPlayManager(ProcessScanner &pscan)
{
    unsigned int instanceAddr = pscan.GetStaticClassFieldInt("RepeatPlayManager","_instance");
    printf("instanceAddr %08X\n",instanceAddr);
    RepeatPlayManager cd;
    pscan.read(instanceAddr,sizeof(cd),(unsigned int)&cd);
    //printf("%s\n",cd.ToString(pscan).c_str());
    cd.Show(pscan);
    
}

void GetGUIManager(ProcessScanner &pscan)
{
    unsigned int instanceAddr = pscan.GetStaticClassFieldInt("GUIManager","_instance");
    printf("instanceAddr %08X\n",instanceAddr);
    GUIManager cd;
    pscan.read(instanceAddr,sizeof(cd),(unsigned int)&cd);
    //printf("%s\n",cd.ToString(pscan).c_str());
    cd.Show(pscan);
    
}

void GetGameApp(ProcessScanner &pscan)
{
    unsigned int instanceAddr = pscan.GetStaticClassFieldInt("GameApp","_instance");
    printf("instanceAddr %08X\n",instanceAddr);
    GameApp cd;
    pscan.read(instanceAddr,sizeof(cd),(unsigned int)&cd);
    //printf("%s\n",cd.ToString(pscan).c_str());
    cd.Show(pscan);
    if(pscan.PutInstanceClassField(instanceAddr,"GameApp","isShowBackground",(unsigned char)0)){
	pscan.PutInstanceClassField(instanceAddr,"GameApp","isShowGUI",(unsigned char)0);
	pscan.PutInstanceClassField(instanceAddr,"GameApp","isShowEnemy",(unsigned char)0);
	pscan.PutInstanceClassField(instanceAddr,"GameApp","isShowAlly",(unsigned char)0);
	pscan.read(instanceAddr,sizeof(cd),(unsigned int)&cd);
	cd.Show(pscan);    
    }
    
}

void GetGameStage(ProcessScanner &pscan)
{
    unsigned int instanceAddr = pscan.GetStaticClassFieldInt("GameStage","_instance");
    printf("instanceAddr %08X\n",instanceAddr);
    GameStage cd;
    pscan.read(instanceAddr,sizeof(cd),(unsigned int)&cd);
    printf("--- GameStage -----\n");
    cd.Show(pscan);
    //GameMap gameMap;
    //pscan.read(cd._currentMap,sizeof(gameMap),(unsigned int)&gameMap);
    //printf("--- Game map -----\n");
    //gameMap.Show(pscan);
    if(cd._camps!=0){
	printf("-- _camps [%s]---\n",pscan.GetInstanceClassName(cd._camps));
	MonoList monoList =  pscan.read<MonoList>(cd._camps);
	printf("%08X %d %d\n",(unsigned int)monoList._items,monoList._size,monoList._version);
	printf("-- _items [%s]---\n",pscan.GetInstanceClassName((unsigned int)monoList._items));
	MonoArrayData monoArray = monoList.readData(pscan);
	for(int i=0;i<monoArray.vAddr.size();i++){
	    printf("%d 0x%08X %s\n",i,monoArray.vAddr[i],pscan.GetInstanceClassName(monoArray.vAddr[i]));
	    Camp camp = pscan.read<Camp>(monoArray.vAddr[i]);
	    camp.Show(pscan);
	    printf("%s\n",pscan.GetInstanceClassName(camp.members));
	    //break;
	}
	
    }
    
}
/*
void GetBannerManager(ProcessScanner &pscan)
{
    unsigned int instanceAddr = pscan.GetStaticClassFieldInt("BannerManager","_instance");
    printf("instanceAddr %08X\n",instanceAddr);
    BannerManager cd;
    pscan.read(instanceAddr,sizeof(cd),(unsigned int)&cd);
    //printf("%s\n",cd.ToString(pscan).c_str());
    cd.Show(pscan);    
}
*/

void ToC(ProcessScanner &pscan,char *className)
{
    MonoClassData d = pscan.GetClassData(className);
    if(d.isInit()){
	d.ToCClass(pscan);
    }
}

int main(int argc,char *argv[])
{
    if(geteuid()!=0){
	printf("RESULT: Error not root user %d:\n",geteuid());
	return -1;
    }
    if(argc!=3){
        printf("Usage:\n");
        printf("%s hero cmd\n",argv[0]);
	printf("RESULT: need parameter\n");
        return 0;
    }
    
    int pid;
    script = new LuaScript(tolua_lua_upgrade_open);
    luaLogger = &logger;
    script->execFile("upgrade.lua");
    //if(isdigit(argv[1][0])){
    //	pid = atoi(argv[1]);
    //}else{
	//printf("Find by name [%s]\n",argv[1]);
	pid = FindProcessByName("com.nexon.fwar",NULL);
	printf("pid=%d\n",pid);
	if((pid==getpid())||(pid == 0)){
	    printf("RESULT: Error process (%d) not found\n",pid);
	    return 0;
	}
    //}
    if(strcmp(argv[1],"index")==0){
	index(pid);
	return 0;
    }
    if(strcmp(argv[1],"dump")==0){
	unsigned int addr;
	sscanf(argv[2],"%x",&addr);
	dumpAddr(pid,addr);
	return 0;
    }

    if(strcmp(argv[1],"shell")==0){
	luaShell.scriptFile = "upgrade.lua";
        luaShell.Shell(pid,&logger,script);
	printf("RESULT: End\n");
	return 0;
    }
    if(strcmp(argv[1],"dumpCreature")==0){
	dumpCreature(pid);
	return 0;
    }
    if(strcmp(argv[1],"BattleManager")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    GetBattleManager(pscan);
	    pscan.close();
	}
	return 0;
    }
    if(strcmp(argv[1],"DimensionBreakManager")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    GetDimensionBreakManager(pscan);
	    pscan.close();
	}
	return 0;
    }
    if(strcmp(argv[1],"DungeonDataManager")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    GetDungeonDataManager(pscan);
	    pscan.close();
	}
	return 0;
    } 
    if(strcmp(argv[1],"EnchantDataManager")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    GetEnchantData(pscan);
	    pscan.close();
	}
	return 0;
    } 
    if(strcmp(argv[1],"GradeRewardManager")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    GetGradeReward(pscan);
	    pscan.close();
	}
	return 0;
    } 
    if(strcmp(argv[1],"MapObjectDataManager")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    GetMapObjectData(pscan);
	    pscan.close();
	}
	return 0;
    } 
	
    if(strcmp(argv[1],"RepeatPlayManager")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    GetRepeatPlayManager(pscan);
	    pscan.close();
	}
	return 0;
    } 	
    if(strcmp(argv[1],"GUIManager")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    GetGUIManager(pscan);
	    pscan.close();
	}
	return 0;
    }	

    if(strcmp(argv[1],"ActiveDataManager")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    GetActiveData(pscan);
	    pscan.close();
	}
	return 0;
    }	
	
    if(strcmp(argv[1],"ActiveSkillValueManager")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    DumpDataManager<ActiveSkillValue>(pscan,"ActiveSkillValueManager","ActiveSkillValue.inc");
	    pscan.close();
	}
	return 0;
    }		
    if(strcmp(argv[1],"AttendanceDataManager")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    DumpDataManager<AttendanceData>(pscan,"AttendanceDataManager","AttendanceData.inc");
	    pscan.close();
	}
	return 0;
    }
	
    if(strcmp(argv[1],"SkillDataManager")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    DumpDataManager<SkillData>(pscan,"SkillDataManager","SkillData.inc");
	    pscan.close();
	}
	return 0;
    }
	
    if(strcmp(argv[1],"MessageBoxManager")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    MessageBoxManager m = DumpInstance<MessageBoxManager>(pscan,"MessageBoxManager");
	    if(m.currectMessageBoxData!=0){
		MessageBoxData d = pscan.read<MessageBoxData>(m.currectMessageBoxData);
		d.Show(pscan);
	    }
	    pscan.close();
	}
	return 0;
    }
	
    if(strcmp(argv[1],"FWT")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    DumpInstance<FantasyWarTactic_FWT>(pscan,"FantasyWarTactic.FWT");
	    //GetBannerManager(pscan);
	    pscan.close();
	}
	return 0;
    } 	
	

    if(strcmp(argv[1],"BannerManager")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    DumpInstance<BannerManager>(pscan,"BannerManager");
	    //GetBannerManager(pscan);
	    pscan.close();
	}
	return 0;
    } 	
	
    if(strcmp(argv[1],"NPAccount")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    DumpInstance<NPA_NPAccount>(pscan,"NPA.NPAccount.Nested","instance");
	    pscan.close();
	}
	return 0;
    } 
	
    if(strcmp(argv[1],"NetworkManager")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    DumpInstance<NetworkManager>(pscan,"NetworkManager");
	    pscan.close();
	}
	return 0;
    } 

    if(strcmp(argv[1],"InjectionDetector")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    DumpInstance<NetworkManager>(pscan,"CodeStage.AntiCheat.Detectors.InjectionDetector","<Instance>k__BackingField");
	    pscan.close();
	}
	return 0;
    } 
	


	
    if(strcmp(argv[1],"GameConfig")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    GetGameConfig(pscan);
	    pscan.close();
	}
	return 0;
    } 
    if(strcmp(argv[1],"GameApp")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    GetGameApp(pscan);
	    pscan.close();
	}
	return 0;
    } 
    if(strcmp(argv[1],"GameStage")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    GetGameStage(pscan);
	    pscan.close();
	}
	return 0;
    } 	
	
	

    if(strcmp(argv[1],"ToC")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    ToC(pscan,argv[2]);
	    pscan.close();
	}
	return 0;
    }
	
    if(strcmp(argv[1],"ClassScan")==0){
	ProcessScanner pscan;
	if(pscan.open(pid)){
	    pscan.MonoClassScan();
	    for(int i=0;i<pscan.vMonoClasses.size();i++){
		printf("0x%08X %s\n",pscan.vMonoClasses[i].addr,pscan.vMonoClasses[i].name);
	    }
	    pscan.close();
	}
	return 0;
    }
	
	
    characterDataIndexManager.load(pid);
    if(characterDataIndexManager.index.size()==0){
	printf("WARNING:No index found\n");
	index(pid);
    }
    
    if(strcmp(argv[1],"status")==0){
	status(pid);
	printf("RESULT: End\n");
	return 0;
    }    
    
    if(strcmp(argv[1],"MONSTER")==0){
	printf("Get monster from GetMonsterList()\n");
	luaMonsterList[0] = 0;
	script->execString("GetMonsterList()");
	printf("%s\n",luaMonsterList);
	upgrade(pid,luaMonsterList,argv[2]);
    }else{
	upgrade(pid,argv[1],argv[2]);
    }
    status(pid);
    printf("RESULT: End\n");
    
}

