myMonsterList = {

	10004, -- name=Tarou
    10005,    --Thief Bug      
    10006,    --Spore   
    10007,  --Familiar
--    40013,  --Thief Bug Egg
--    110002, --Huge Thief Bug
	10012, -- name=Rocker
	10013, -- name=Willow
	10020, -- name=Pirate Skeleton Type=Monster
--	10017, -- name=Hydra Type=Monster
--  10021, -- name=Poison Spore Type=Monster
--	10019, -- name=Whisper Type=Monster
    10022, -- name=Skeleton Type=Monster
--  40003, -- name=Yellow Plant Type=Monster
--  10024, -- name=Thara Frog Type=Monster
	10025, -- name=Marina Type=Monster
--  10023, -- name=Vadon Type=Monster
	10050, -- name=Soldier Skeleton
    10037, -- name=Flora Type=Monster    
--	10051, -- name=Matyr	
	10052, -- name=Mummy
    10063, -- name=Archer Skeleton
	

};

myMonsterRules = {
--    {func= ROM_FindMiniBoss}, -- priority to miniboss
    {func= ROM_FindStaticMonster},  -- priority to static monster
--    {func= ROM_FindNearestMonsterEx, param=myMonsterList},  -- selected monster
    {func= ROM_FindNearestMonsterEx2, monlist={},selectFunc=ROM_GetBestScoreMonFromList},  -- selected monster
};

myAIRules = {
--	{func=ROM_Follow},
    {name="Play Dead", func=ROM_FakeDead, fracsp=0.2},    --fake dead
	{name="Blessing", func=ROM_BuffNoTarget},  -- bless    	
--	{name="Bash", func=ROM_NeverMiss,filter=function(mon) return ROM_IsEliteMonster(mon) end},    	
    {name="Endure", func=ROM_BuffNoTarget, ignoreLockTarget=true},
--	{name="Shield Charge", func=ROM_NeverMiss,filter=function(mon) return ROM_IsEliteMonster(mon) end},    	
	{name="Auto", func=ROM_SkillTarget, filter1 = ROM_NoPlayerAround},    
--    {name="Crasher", func=ROM_SkillTarget},
	{name="Auto", func=ROM_SkillTarget, 
		filter = function(mon) 
			return (mon == ROM_GetMonsterLockTarget()) or (ROM_IsStaticMonster(mon))
		end
	},    
--	{name="Auto", func=ROM_SkillTarget},    


--    {name="Blessing", func=ROM_BuffNoTarget},  -- bless    
--	{name="Gloria", func=ROM_BuffNoTarget},  -- Gloria    
--	{name="Magnif", func=ROM_BuffNoTarget, fracsp=0.5},  -- Gloria    
--	{name="WalkToRange", func=ROM_WalkToRange,range=5},  		
--	{name="Heal", func=ROM_Heal,frachp=0.6},  -- bless    
--	{name="Turn", func=ROM_TurnUndead, frachp=0.6},  
--    {name="Holy Light Strike", func=ROM_SkillTarget},  	
};

ignoreMonList = {
    60132, -- name=Sumina
    10084, -- name=Abysmal Knight
    10081, -- name=Gargoyle
	17301, -- name=Weak Puppet
	20022, -- name=Dark Illusion
	18055, -- name=Dark Illusion 
    40015, -- mimic
}

avoidMonList = {
	10084, -- name=Abysmal Knight
	20022, -- name=Dark Illusion
	18055, -- name=Dark Illusion [
}


cleanSkill = {
	"Turn","Heal","Bolt"
};

walkBack = false;

ROM_Config = {};
ROM_Config[4313990901] = {
    myMonsterList = {
    	10052, -- name=Mummy
        10063, -- name=Archer Skeleton
        10061, --  name=Bongun
        10060, --  name=Munak
        10120, --  name=Evil Druid
        10121,--  name=Dark Priest
        10080, --  name=Wraith Type=Monster
    },
    myMonsterRules ={
        --{func= ROM_FindStaticMonster},  -- priority to static monster
        --{func= ROM_FindNearestMonsterEx2, monlist={}, filter=ROM_MonFullHP, selectFunc=ROM_GetBestScoreMonFromList},  -- selected monster
		{func= ROM_FindNearestMonsterEx2, monlist={}, ignore=ignoreMonList, selectFunc=ROM_GetBestScoreMonFromList},  -- selected monster
    },
    myAIRules = {
        {name="Play Dead", func=ROM_FakeDead, fracsp=0.2},    --fake dead
        {name="Blessing", func=ROM_BuffNoTarget},  -- bless    
        {name="Gloria", func=ROM_BuffNoTarget},  -- Gloria    
        {name="Magnif", func=ROM_BuffNoTarget, fracsp=0.5},  -- Gloria    
        {name="WalkToRange", func=ROM_WalkToRange, filter = ROM_NoPlayerAround, range=6},  		
        {name="Heal", func=ROM_Heal,frachp=0.7},  -- bless    
		{name="Holy Light Strike", func=ROM_SkillTarget, filter = ROM_NoPlayerAround},    
        {name="Turn", func=ROM_TurnUndead, frachp=0.6},  
        {name="Holy Light Strike", func=ROM_SkillTarget,
            filter = function(mon) 
                return (mon == ROM_GetMonsterLockTarget()) or (ROM_IsStaticMonster(mon))
            end
        },  	
    },
	walkBack = true,
}
ROM_Config[4300736919] = {  -- Sniper
    myMonsterList = {},
    myMonsterRules ={
        --{func= ROM_FindStaticMonster},  -- priority to static monster
        --{func= ROM_FindNearestMonsterEx2, monlist={}, filter=ROM_MonFullHP, selectFunc=ROM_GetBestScoreMonFromList},  -- selected monster
		{func= ROM_FindNearestMonsterEx2, monlist={}, ignore=ignoreMonList, selectFunc=ROM_GetBestScoreMonFromList},  -- selected monster
    },
    myAIRules = {
        {name="True Sight", func=ROM_BuffNoTarget}, 
        {name="Auto", func=ROM_SkillTarget, filter = ROM_NoPlayerAround},    
        {name="Double Strafe", func=ROM_SkillTarget},    
        {name="Auto", func=ROM_SkillTarget,
            filter = function(mon) 
                return (mon == ROM_GetMonsterLockTarget()) or (ROM_IsStaticMonster(mon))
            end
        },
	},
	walkBack = false,
}

ROM_Config[4299674004] = {  -- priest
    myMonsterList = {},
    myMonsterRules ={
        --{func= ROM_FindStaticMonster},  -- priority to static monster
        --{func= ROM_FindNearestMonsterEx2, monlist={}, filter=ROM_MonFullHP, selectFunc=ROM_GetBestScoreMonFromList},  -- selected monster
		{func= ROM_FindNearestMonsterEx2, monlist={}, ignore=ignoreMonList, selectFunc=ROM_GetBestScoreMonFromList},  -- selected monster
    },
    myAIRules = {
		{func=ROM_Follow},
		{name="Heal", func=ROM_Heal,frachp=0.7},  -- bless    
        {name="Blessing", func=ROM_BuffNoTarget},  -- bless    
        {name="Gloria", func=ROM_BuffNoTarget},  -- Gloria    
        {name="Magnif", func=ROM_BuffNoTarget, fracsp=0.5},  -- Gloria    
		{name="Angelus", func=ROM_BuffNoTarget},
		{name="Kyrie Eleison", func=ROM_BuffTeam},
        --{name="True Sight", func=ROM_BuffNoTarget}, 
        {name="Holy Light Strike", func=ROM_SkillTarget, filter = ROM_TargetInRange, range = 5.5},    
        --{name="Double Strafe", func=ROM_SkillTarget},    
        --{name="Auto", func=ROM_SkillTarget,
        --    filter = function(mon) 
        --        return (mon == ROM_GetMonsterLockTarget()) or (ROM_IsStaticMonster(mon))
        --    end
        --},  
	},
	walkBack = false,
}

ROM_Config[4315742181] = {  -- paladin
    myMonsterList = {},
    myMonsterRules ={
        --{func= ROM_FindStaticMonster},  -- priority to static monster
        --{func= ROM_FindNearestMonsterEx2, monlist={}, filter=ROM_MonFullHP, selectFunc=ROM_GetBestScoreMonFromList},  -- selected monster
		{func= ROM_FindNearestMonsterEx2, monlist={}, ignore=ignoreMonList, selectFunc=ROM_GetBestScoreMonFromList},  -- selected monster
    },
    myAIRules = {
		{name="Play Dead", func=ROM_FakeDead, fracsp=0.2},    --fake dead
		{name="Endure", func=ROM_BuffNoTarget, ignoreLockTarget=true},
	--	{name="Shield Boomerang", func=ROM_NeverMiss,filter1=function(mon) return ROM_IsEliteMonster(mon) end},    			
	--	{name="Shield Charge", func=ROM_NeverMiss,filter=function(mon) return ROM_IsEliteMonster(mon) end},    	
		{name="Auto", func=ROM_SkillTarget, filter1 = ROM_NoPlayerAround},    
	--    {name="Crasher", func=ROM_SkillTarget},
		{name="Shield Boomerang", func=ROM_SkillTarget, 
			filter = function(mon) 
				return (mon == ROM_GetMonsterLockTarget()) or (ROM_IsStaticMonster(mon))
			end
		},    
	},
	walkBack = false,
}


if Game and Game.Myself and Game.Myself.data then
    if ROM_Config[Game.Myself.data.id] ~= nil then
        LogDebug("Use ROM_Config for " .. Game.Myself.data.id);
        local conf = ROM_Config[Game.Myself.data.id];
        myMonsterList = conf.myMonsterList;
        myMonsterRules = conf.myMonsterRules;
        myAIRules = conf.myAIRules;
		walkBack = conf.walkBack;
    end;
end;
