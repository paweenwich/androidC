print("upgrade.lua loading");

function GetMonsterList()
	luaMonsterList = "Forest Golem.Pink Fairy.Blue Fairy.Red Fairy.Green Fairy.Shadow Arrow.Shadow Spear.Napalm Ghost.Hellhound.Shadow Knight.Shadow Witch.Killer Machine.Shadow Hammer.Reaper Guardian.Magma Giant.Abyss Dragon.Fortress Sentinel.Fortress Sniper.Fortress Destroyer.Parsifal.Hellmaster.Trishula.Chronos.Juggernaut.Bathory.Deimos.Ancient Keeper.Celestial";
end;

function UpdateHero()
    print("UpdateHero:" .. GetCreatureByID(paramCharacterData.creatureId).name);
	Up();
end;

function UpdateMonster()
    print("UpdateMonster:" .. GetCreatureByID(paramCharacterData.creatureId).name);
--    paramCharacterData.baseAttackPoint = 40000;
--    paramCharacterData.baseDr = 2.0;
--    paramCharacterData.baseDgr = 2.0;
--    paramCharacterData.baseMpRegen = 100;
--	if(GetCreatureByID(paramCharacterData.creatureId).name == "Chris") then
--		print("Persona Chris");
--		paramCharacterData.skill0 = 1049714;
--		paramCharacterData.skill1 = 1049715;
--		paramCharacterData.skill2 = 1049716;
--		paramCharacterData.skill3 = 1049713;
--	end;
	paramCharacterData.skill0 = -1;
	paramCharacterData.skill1 = -1;
	paramCharacterData.skill2 = -1;
	paramCharacterData.skill3 = -1;
	paramCharacterData.movePoint = 1;
	paramCharacterData.baseAttackPoint = 50;
    paramCharacterData.baseDr = 0.05;
    paramCharacterData.baseDgr = 0.01;
    paramCharacterData.baseMpRegen = 100;	
	if(GetCreatureByID(paramCharacterData.creatureId).name == "Napalm Ghost") then
		paramCharacterData.skill3 = 2195490;
	end;	
end;
-- "Chris.Mu.Alfred.Jenny.Reina"
-- "Shadow Arrow.Shadow Spear.Napalm Ghost.Hellhound.Shadow Knight.Shadow Witch.Killer Machine.Shadow Hammer.Reaper Guardian.Magma Giant.Abyss Dragon" UpdateMonster
function UpdateCharacter()
	if(IsHeroID(paramCharacterData.creatureId)) then
		UpdateHero();
	else
		UpdateMonster();
	end;
end;

function Down()
	local oldData = GetCreatureByID(paramCharacterData.creatureId);
	if oldData ~= nil then
		paramCharacterData.baseAttackPoint = oldData.baseAttackPoint;
		paramCharacterData.baseDr = oldData.baseDr;
		paramCharacterData.baseDgr = oldData.baseDgr;
		paramCharacterData.baseMpRegen = oldData.baseMpRegen;
		paramCharacterData.movePoint = oldData.movePoint;
		paramCharacterData.baseHp = oldData.baseHp;
	else
		paramCharacterData.baseAttackPoint = 50;
		paramCharacterData.baseDr = 0.09;
		paramCharacterData.baseDgr = 0.01;
		paramCharacterData.baseMpRegen = 100;
		paramCharacterData.movePoint = 1;
	--	paramCharacterData.baseHp = 450;		
	end;


end;

function Up()
    paramCharacterData.baseHp = 70000;
    paramCharacterData.baseAttackPoint = 70000;
    paramCharacterData.baseDr = 5.0;
    paramCharacterData.baseDgr = 3.0;
    paramCharacterData.baseMpRegen = 100;
    paramCharacterData.movePoint = 9;	
	--if(GetCreatureByID(paramCharacterData.creatureId).name == "Chris0") then
	--	print("Persona Chris");
	--	paramCharacterData.skill1 = 1049714;
	--	paramCharacterData.skill0 = 1049715;
	--	paramCharacterData.skill2 = 1049716;
	--	paramCharacterData.skill3 = 1049713;
	--end;
	--if(GetCreatureByID(paramCharacterData.creatureId).name == "Dominique") then
	--	print("Lilid Dominique");
	--	paramCharacterData.skill0 = 1048657;
	--	paramCharacterData.skill1 = 1048658;
	--	paramCharacterData.skill2 = 1048660;
	--	paramCharacterData.skill3 = 1048659;
	--end;

end;

function Dump()
	print('creatureId=' .. paramCharacterData.creatureId);
	print(GetCreatureByID(paramCharacterData.creatureId).name);
    flgShouldUpdate = false;
	print("baseHp=" ..paramCharacterData.baseHp);
	print("hpf=" ..paramCharacterData.hpf);
	print("baseMp=" ..paramCharacterData.baseMp);
	print("mpf=" ..paramCharacterData.mpf);
	print("baseMpRegen=" ..paramCharacterData.baseMpRegen);
	print("mprf=" ..paramCharacterData.mprf);
	print("baseAttackPoint=" ..paramCharacterData.baseAttackPoint);
	print("apf=" ..paramCharacterData.apf);
	print("movePoint=" ..paramCharacterData.movePoint);
	print("baseDr=" ..paramCharacterData.baseDr);
	print("drf=" ..paramCharacterData.drf);
	print("baseCr=" ..paramCharacterData.baseCr);
	print("crf=" ..paramCharacterData.crf);
	print("baseDgr=" ..paramCharacterData.baseDgr);
	print("dgrf=" ..paramCharacterData.dgrf);
	print("baseHr=" ..paramCharacterData.baseHr);
	print("hrf=" ..paramCharacterData.hrf);
	print("baseCar=" ..paramCharacterData.baseCar);
	print("carf=" ..paramCharacterData.carf);
	print("baseCadr=" ..paramCharacterData.baseCadr);
	print("cadrf=" ..paramCharacterData.cadrf);
	print("mastery=" ..paramCharacterData.mastery);
	print("skill0=" ..paramCharacterData.skill0);
	print("skill1=" ..paramCharacterData.skill1);	
	print("skill2=" ..paramCharacterData.skill2);
	print("skill3=" ..paramCharacterData.skill3);
	print("skill4=" ..paramCharacterData.skill4);	
--	print("levelType=" ..paramCharacterData.levelType);		
--	print("creatureType=" ..paramCharacterData.creatureType);	
--	print("moveType0=" ..paramCharacterData.moveType0);	
--	print("moveType1=" ..paramCharacterData.moveType1);	
--	print("moveType2=" ..paramCharacterData.moveType2);			
end;

function GetCreatureByID(id)
	for i=1,10000000 do
		--print(heros[i].creatureId);
		if creatures[i].creatureId == 0 then
			return nil;
		end;
		if id == creatures[i].creatureId then
			return creatures[i];
		end;
	end;
end;

function IsHeroID(id)
	for i=1,10000000 do
		--print(heros[i].creatureId);
		if heros[i].creatureId == 0 then
			return false;
		end;
		if id >= heros[i].creatureId and id <= heros[i].creatureId + 5 then
			return true;
		end;
	end;
end;

function MonoString(addr)
	return luaShell.pscan:readMonoString(addr);
end;

function IntFromHex(hex)
	return luaShell.pscan:IntFromHex(hex);
end;

function MonoClassName(addr)
	return luaShell.pscan:readMonoClassName(addr);
end;

function MonoClass(addr)
	return luaShell.pscan:readMonoClass(addr);
end;

function MonoClassNextAddr(addr)
	return addr + 0xD0;
end;

function printx(value)
	print(string.format('%08X',value));
end;

function MonoFindVtable(addr)
	return luaShell.pscan:MonoFindVtable(addr);
end;

function MonoFindClass(name)
	return luaShell.pscan:MonoFindClass(name);
end;

function MonoFindObject(addr)
	return luaShell.pscan:MonoFindObject(addr);
end;

function MonoFindObjectOfClass(name)
	local classAddr = MonoFindClass(name);
	if classAddr == 0 then
		print('Class ' .. name .. ' not found');
		return;
	end;
	printx(classAddr);
	local vTableAddr = MonoFindVtable(classAddr);
	printx(vTableAddr);
	if vTableAddr == 0 then
		print('Vtable of class ' .. name .. ' not found');
		return;
	end;
	MonoFindObject(vTableAddr);
end;

function GetStaticInt(cName,method)
    return luaShell.pscan:GetStaticClassFiledInt(cName,method);
end;

function ShowMonoClass(classAddr)
	local myClassData = MonoClass(classAddr);
	myClassData:show(luaShell.pscan);
end;

function ShowMonoVTable(addr)
	local myVTablData = luaShell.pscan:readMonoVTable(addr);
	myVTablData:show(luaShell.pscan);
end;

--MonoFindObjectOfClass('CreatureData');
--MonoFindObjectOfClass('CreatureDataManager');
--MonoFindObjectOfClass('MonsterDataManager');
--luaShell.pscan:readMonoArray();
-->vTableAddr = MonoFindVtable(0xBAE81170)

--MonoFindObjectOfClass('MonsterFirstTurnManager');
--MonoFindObjectOfClass('MessageBoxManager');
print("upgrade.lua done");