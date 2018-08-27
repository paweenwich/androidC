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
#include <dirent.h>
#include "../util/logger.h"
#include "../util/util.hpp"
#include "../util/payload.hpp"
#include "../util/ProcessScanner.hpp"

Logger logger(NULL,0);
struct HeroData {
    unsigned int creatureId;
    char *title;
    char *name; 
    unsigned int combatType;
    unsigned int baseHp;
};

struct HeroData heros[] = {
    {1114113,"Hero","Kai",3,430},  
    {1245201,"White Knight","Chris",1,490},
    {1179681,"Orc Warrior","Sraka",2,430},
    {1114161,"Werewolf","Jack",1,510},
    {1114177,"Resistance","Dominique",2,410},
    {1114193,"Wild Boy","Lilid",1,510},
    {1114209,"Android","Kitty",4,330},
    {1245297,"Cowgirl","Jenny",4,370},
    {1114241,"Black Cat","Ian",3,330},
    {1114257,"Gunner","Rage",2,410},
    {1179905,"Ninja","Sonic Boom",3,330},
    {1179921,"Psychokinetic","Lee",2,410},
    {1245473,"Bard","Mas",5,290},
    {1179953,"Magician","Chenny",3,410},
    {1179969,"Magician","Deborah",4,330},
    {1245521,"Succubus","Cleo",3,370},
    {1245537,"Black Wizard","Moa",4,370},
    {1180017,"Pyromaniac","Muang",4,410},
    {1245569,"Lancer","Alex",3,510},
    {1114513,"Killing Machine","Henry",2,410},
    {1245697,"Nouveau Riche","Dolores",3,390},
    {1180177,"Fonea Queen","Elektra",5,390},
    {1245729,"General","Raboff",1,450},
    {1180209,"Reinforced Human","Bearman",1,640},
    {1180225,"Combat Ranger","Fruel",2,350},
    {1114705,"Professor","Alfred",4,370},
    {1114721,"Aide","Hella",5,450},
    {1245809,"Wanderer","Unknown",2,410},
    {1180289,"Golem","Lance",1,400},
    {1245841,"Archmage","Klein",4,400},
    {1180417,"Black Bride","Sione",2,390},
    {1180497,"Mercenary Captain","Jin",2,410},
    {1246049,"Big Shot","Carrot",2,290},
    {1180529,"Kung Fu Girl","Tao",2,430},
    {1115009,"Little Angel","Shu-Shu",5,350},
    {1115025,"Assassin","Zero",3,430},
    {1115137,"Drug Master","Gillan",5,330},
    {1180689,"Pirate","Shark",3,410},
    {1180705,"Phoenix","Poni",3,400},
    {1246257,"Maid","Lily",2,430},
    {1246273,"Iron Princess","Angela",3,450},
    {1180753,"Healer","Belle",5,320},
    {1115233,"Dryad","Serendi",3,370},
    {1115249,"Phantom Thief","Persona",3,390},
    {1115265,"White Rabbit","Momo",2,390},
    {1246353,"Healer","Nirvana",5,450},
    {1180929,"Diva","Lena",3,390},
    {1246481,"Vampire","Nox",2,370},
    {1246497,"Artificial Angel","Azrael",2,450},
    {1246513,"Exorcist","Mu",3,430},
    {1115457,"Magician","Yekaterina",4,350},
    {1181009,"Butler","Frankenstein",2,370},
    {1115489,"Werewolf","Muzaka",1,400},
    {1246577,"Reaper","Seira",2,410},
    {1181057,"Lord","Raskreia",4,430},
    {1115537,"Orc Warrior","Krut",2,420},
    {1246721,"Soul Gear","Valkyrie",1,350},
    {1246737,"Noblesse","Raizel",2,490},
    {1181217,"Wolf Hunter","Reina",3,640},
    {1246769,"Dragon","Celestial",5,380},
    {1181249,"Tyrant","Deimos",1,670},
    {0,"","",0,0},
};

struct CharacterData {
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
};

struct SearchData {
    unsigned int creatureId;
    unsigned int combatType;    
    unsigned int baseHp;
};



struct HeroData * FindHeroByName(char *name)
{
    for(int i=0;i<heros[i].creatureId !=0;i++){
	if(strcasecmp(name,heros[i].name)==0){
	    return &heros[i];
	}
    }
    return NULL;
}



void upgrade(int pid,char *heroName)
{
    std::vector<ScanData> vSearchList;
    struct HeroData *pHero = FindHeroByName(heroName);
    if(pHero!=NULL){
	printf("Hero %s found %08X, %08X\n",pHero->name,pHero->creatureId,pHero->combatType);
	for(int i=0;i<5;i++){
	    ScanData sd;
	    SearchData *psd = (SearchData *)&sd;
	    psd->creatureId = pHero->creatureId + i;
	    psd->combatType = pHero->combatType;
	    psd->baseHp = pHero->baseHp;
	    sd.size = sizeof(SearchData);
	    vSearchList.push_back(sd);
	    logger.logHex((unsigned char *)&sd,sd.size);
	}
    }
    //return;
    ProcessScanner pscan;
    if(pscan.open(pid)){
	printf("Open success\n");
	std::vector<ScanResult> result;
	std::vector<WriteData> vWriteData;
	pscan.scanRange(0x80000000,0x90000000,vSearchList,result,4,true);
	printf("Found %d\n",result.size());
	if(result.size()==5){
	    for(int i=0;i<result.size();i++){
		CharacterData charData;
		//pscan.dump(result[i].addr,64);
		pscan.read(result[i].addr,sizeof(charData),(unsigned int)&charData);
		//kai.baseHp += 1000;
		charData.baseAttackPoint = 10000;
		charData.baseDr = 0.8;
		charData.baseDgr = 0.5;

		WriteData w;
		w.load(result[i].addr,(unsigned char *)&charData,sizeof(charData));
		vWriteData.push_back(w);
		//pscan.write(result[i].addr,sizeof(charData),(unsigned int)&charData);
		//pscan.dump(result[i].addr,64);
	    }
	    if(vWriteData.size()>0){
		pscan.writeAll(vWriteData);
		printf("Update done");
	    }
	}else{
	    for(int i=0;i<result.size();i++){
	       //CharacterData charData;
	       pscan.dump(result[i].addr,64);
	    }
	}
	pscan.close();
    }else{
	printf("can not open %d\n",pid);
    }
}

int main(int argc,char *argv[])
{
    if(argc!=3){
        printf("Usage:\n");
        printf("%s pid|pname hero\n",argv[0]);
        return 0;
    }
    int pid;
    if(isdigit(argv[1][0])){
	pid = atoi(argv[1]);
    }else{
	printf("Find by name [%s]\n",argv[1]);
	pid = FindProcessByName(argv[1],NULL);
	printf("pid=%d\n",pid);
	if(pid==getpid()){
	    printf("Error: process (%d) not found\n",pid);
	    return 0;
	}
    }
    upgrade(pid,argv[2]);
}