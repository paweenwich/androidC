--md5:e12dcff0b824ed265263d0b70b5326e9
Table_Class = {
	[1] = {id = 1, NameZh = '初心者', NameEn = 'Novice', MaleBody = 1, FemaleBody = 2, Desc = '刚进游戏的萌萌哒小白，请大家多多关照。', Skill = {11001,10020001,30000001,50023001,50025001,50018001,50044001}, MaxJobLevel = 10, AdvancedOccupation = _EmptyTable, AdvanceClass = {11,21,31,41,51,61}, Type = 0, TypeBranch = 0, icon = 'icon_1_0', InitialAttr = {{name='Str',value=40},{name='Vit',value=40},{name='Luk',value=40},{name='Int',value=40},{name='Dex',value=40},{name='Agi',value=40}}, AddPointSolution = {1000}, Explain = '', DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[11] = {id = 11, NameZh = '剑士', NameEn = 'Swordman', MaleBody = 3, FemaleBody = 4, Desc = '战士使用中重量级武器，敏捷度较低，但攻击是极强有力的。', Skill = {14001,15001,16001,17001,18001,19001}, MaxJobLevel = 50, AdvancedOccupation = { BaseLv=40}, AdvanceClass = {12,72}, Type = 1, TypeBranch = 11, icon = 'icon_1_1', InitialAttr = {{name='Str',value=96},{name='Vit',value=72},{name='Luk',value=24},{name='Int',value=24},{name='Dex',value=48},{name='Agi',value=24}}, AddPointSolution = {1,2,3,4}, Explain = '近战、物理、攻守兼备', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[12] = {id = 12, NameZh = '骑士', NameEn = 'Knight', MaleBody = 5, FemaleBody = 6, Desc = '剑士的进阶职业－骑士，威风八面，不论是攻击强度还是攻击范围，和之前相比都有大大的提升！', Skill = {20001,21001,22001,23001,24001,45001,26001,29001,32001,44001}, MaxJobLevel = 90, AdvancedOccupation = {BaseLv=70}, AdvanceClass = {13}, Type = 1, TypeBranch = 11, icon = 'icon_1_2', InitialAttr = {{name='Str',value=96},{name='Vit',value=72},{name='Luk',value=24},{name='Int',value=24},{name='Dex',value=48},{name='Agi',value=24}}, AddPointSolution = {1,2,3,4}, Explain = '近战、物理、攻守兼备', AdvancedTeacher = 1050, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[13] = {id = 13, NameZh = '骑士领主', NameEn = 'LordKnight', MaleBody = 7, FemaleBody = 8, Desc = '战士使用中重量级武器，敏捷度较低，但攻击是极强有力的。', Skill = {25001,27001,28001,30001,31001,33001,34001,68001,69001}, MaxJobLevel = 130, MaxPeak = 160, AdvancedOccupation = {BaseLv=100}, AdvanceClass = _EmptyTable, Type = 1, TypeBranch = 11, icon = 'icon_1_3', InitialAttr = {{name='Str',value=96},{name='Vit',value=72},{name='Luk',value=24},{name='Int',value=24},{name='Dex',value=48},{name='Agi',value=24}}, AddPointSolution = {1,2,3,4}, Explain = '近战、物理、攻守兼备', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Str=4}},
	[14] = {id = 14, NameZh = '符文骑士', NameEn = 'RuneKnight', MaleBody = 9, FemaleBody = 10, Desc = '战士使用中重量级武器，敏捷度较低，但攻击是极强有力的。', Skill = _EmptyTable, MaxJobLevel = 200, AdvancedOccupation = _EmptyTable, AdvanceClass = _EmptyTable, Type = 1, TypeBranch = 11, icon = 'icon_1_4', InitialAttr = {{name='Str',value=96},{name='Vit',value=72},{name='Luk',value=24},{name='Int',value=24},{name='Dex',value=48},{name='Agi',value=24}}, AddPointSolution = {31,32,33,34}, Explain = '近战、物理、攻守兼备', AdvancedTeacher = 1050, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Str=6}},
	[21] = {id = 21, NameZh = '魔法师', NameEn = 'Magician', MaleBody = 11, FemaleBody = 12, Desc = '魔法师的体力防御较低，可使用魔法技能进行强大的法术攻击。', Skill = {74001,75001,76001,78001,79001,107001,108001}, MaxJobLevel = 50, AdvancedOccupation = { BaseLv=40}, AdvanceClass = {22,82}, Type = 2, TypeBranch = 21, icon = 'icon_2_1', InitialAttr = {{name='Str',value=12},{name='Vit',value=48},{name='Luk',value=24},{name='Int',value=96},{name='Dex',value=72},{name='Agi',value=12}}, AddPointSolution = {5,6,7}, Explain = '远程、魔法、范围伤害', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[22] = {id = 22, NameZh = '巫师', NameEn = 'Wizard', MaleBody = 13, FemaleBody = 14, Desc = '魔法师转职成巫师后，法术威力提升显著，同时也能轻松地掌握及施放出各属性的强力魔法。', Skill = {77001,80001,81001,82001,84001,86001,92001,93001,95001,98001}, MaxJobLevel = 90, AdvancedOccupation = {BaseLv=70}, AdvanceClass = {23}, Type = 2, TypeBranch = 21, icon = 'icon_2_2', InitialAttr = {{name='Str',value=12},{name='Vit',value=48},{name='Luk',value=24},{name='Int',value=96},{name='Dex',value=72},{name='Agi',value=12}}, AddPointSolution = {5,6,7}, Explain = '远程、魔法、范围伤害', AdvancedTeacher = 1051, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[23] = {id = 23, NameZh = '超魔导士', NameEn = 'HighWizard', MaleBody = 15, FemaleBody = 16, Desc = '魔法师的体力防御较低，可使用魔法技能进行强大的法术攻击。', Skill = {83001,85001,88001,89001,90001,91001,94001,96001}, MaxJobLevel = 130, MaxPeak = 160, AdvancedOccupation = {BaseLv=100}, AdvanceClass = _EmptyTable, Type = 2, TypeBranch = 21, icon = 'icon_2_3', InitialAttr = {{name='Str',value=12},{name='Vit',value=48},{name='Luk',value=24},{name='Int',value=96},{name='Dex',value=72},{name='Agi',value=12}}, AddPointSolution = {5,6,7}, Explain = '远程、魔法、范围伤害', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Int=4}},
	[24] = {id = 24, NameZh = '大法师', NameEn = 'Warlock', MaleBody = 17, FemaleBody = 18, Desc = '魔法师的体力防御较低，可使用魔法技能进行强大的法术攻击。', Skill = _EmptyTable, MaxJobLevel = 200, AdvancedOccupation = _EmptyTable, AdvanceClass = _EmptyTable, Type = 2, TypeBranch = 21, icon = 'icon_2_4', InitialAttr = {{name='Str',value=12},{name='Vit',value=48},{name='Luk',value=24},{name='Int',value=96},{name='Dex',value=72},{name='Agi',value=12}}, AddPointSolution = {35,36,37}, Explain = '远程、魔法、范围伤害', AdvancedTeacher = 1051, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Int=6}},
	[31] = {id = 31, NameZh = '盗贼', NameEn = 'Thief', MaleBody = 19, FemaleBody = 20, Desc = '盗贼的防御低而敏捷高，善于快速移动暗杀，有较高的爆发。', Skill = {176001,179001,184001,177001,180001,178001,174001,185001}, MaxJobLevel = 50, AdvancedOccupation = { BaseLv=40}, AdvanceClass = {32,92}, Type = 3, TypeBranch = 31, icon = 'icon_3_1', InitialAttr = {{name='Str',value=48},{name='Vit',value=24},{name='Luk',value=96},{name='Int',value=24},{name='Dex',value=48},{name='Agi',value=96}}, AddPointSolution = {14,15,16}, Explain = '近战、物理、高爆发', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = {Knife="KnifeAS"}, UnlockAttr = _EmptyTable},
	[32] = {id = 32, NameZh = '刺客', NameEn = 'Assassin', MaleBody = 21, FemaleBody = 22, Desc = '当盗贼转职成光听名字就很酷的职业－刺客后，可使用攻速和暴击率都极高的拳刃作为武器。', Skill = {181001,186001,189001,182001,183001,187001,191001,175001,240001}, MaxJobLevel = 90, AdvancedOccupation = {BaseLv=70}, AdvanceClass = {33}, Type = 3, TypeBranch = 31, icon = 'icon_3_2', InitialAttr = {{name='Str',value=48},{name='Vit',value=24},{name='Luk',value=96},{name='Int',value=24},{name='Dex',value=48},{name='Agi',value=96}}, AddPointSolution = {14,15,16}, Explain = '近战、物理、高爆发', AdvancedTeacher = 1052, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = {Knife="KnifeAS"}, UnlockAttr = _EmptyTable},
	[33] = {id = 33, NameZh = '十字刺客', NameEn = 'AssassinCross', MaleBody = 23, FemaleBody = 24, Desc = '盗贼的防御低而敏捷高，善于快速移动暗杀，有较高的爆发。', Skill = {196001,193001,198001,192001,197001,188001,190001,199001}, MaxJobLevel = 130, MaxPeak = 160, AdvancedOccupation = {BaseLv=100}, AdvanceClass = _EmptyTable, Type = 3, TypeBranch = 31, icon = 'icon_3_3', InitialAttr = {{name='Str',value=48},{name='Vit',value=24},{name='Luk',value=96},{name='Int',value=24},{name='Dex',value=48},{name='Agi',value=96}}, AddPointSolution = {14,15,16}, Explain = '近战、物理、高爆发', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = {Knife="KnifeAS"}, UnlockAttr = {Agi=4}},
	[34] = {id = 34, NameZh = '十字切割者', NameEn = 'GuillotineCross', MaleBody = 25, FemaleBody = 26, Desc = '盗贼的防御低而敏捷高，善于快速移动暗杀，有较高的爆发。', Skill = _EmptyTable, MaxJobLevel = 200, AdvancedOccupation = _EmptyTable, AdvanceClass = _EmptyTable, Type = 3, TypeBranch = 31, icon = 'icon_3_4', InitialAttr = {{name='Str',value=48},{name='Vit',value=24},{name='Luk',value=96},{name='Int',value=24},{name='Dex',value=48},{name='Agi',value=96}}, AddPointSolution = {46,47,48}, Explain = '近战、物理、高爆发', AdvancedTeacher = 1052, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = {Knife="KnifeAS"}, UnlockAttr = {Agi=6}},
	[41] = {id = 41, NameZh = '弓箭手', NameEn = 'Archer', MaleBody = 27, FemaleBody = 28, Desc = '弓箭手攻击灵活、移动迅速，能从较远的距离或高处攻击敌人。', Skill = {114001,121001,124001,117001,118001,133001,127001}, MaxJobLevel = 50, AdvancedOccupation = { BaseLv=40}, AdvanceClass = {42,102,112}, Type = 4, TypeBranch = 41, icon = 'icon_4_1', InitialAttr = {{name='Str',value=12},{name='Vit',value=24},{name='Luk',value=72},{name='Int',value=12},{name='Dex',value=96},{name='Agi',value=48}}, AddPointSolution = {8,9,10}, Explain = '超长远程、物理、单体高伤害', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[42] = {id = 42, NameZh = '猎人', NameEn = 'Hunter', MaleBody = 29, FemaleBody = 30, Desc = '弓箭手转职为猎人后，能对目标进行更有效的远程打击，还可使用各类陷阱和猎鹰来辅助战斗。', Skill = {126001,132001,135001,136001,137001,138001,120001,125001,129001,115001}, MaxJobLevel = 90, AdvancedOccupation = {BaseLv=70}, AdvanceClass = {43}, Type = 4, TypeBranch = 41, icon = 'icon_4_2', InitialAttr = {{name='Str',value=12},{name='Vit',value=24},{name='Luk',value=72},{name='Int',value=12},{name='Dex',value=96},{name='Agi',value=48}}, AddPointSolution = {8,9,10}, Explain = '超长远程、物理、单体高伤害', AdvancedTeacher = 1053, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[43] = {id = 43, NameZh = '神射手', NameEn = 'Sniper', MaleBody = 31, FemaleBody = 32, Desc = '弓箭手攻击灵活、移动迅速，能从较远的距离或高处攻击敌人。', Skill = {130001,134001,128001,123001,116001,122001,142001,131001,119001,251001,250001}, MaxJobLevel = 130, MaxPeak = 160, AdvancedOccupation = {BaseLv=100}, AdvanceClass = _EmptyTable, Type = 4, TypeBranch = 41, icon = 'icon_4_3', InitialAttr = {{name='Str',value=12},{name='Vit',value=24},{name='Luk',value=72},{name='Int',value=12},{name='Dex',value=96},{name='Agi',value=48}}, AddPointSolution = {8,9,10}, Explain = '超长远程、物理、单体高伤害', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Dex=4}},
	[44] = {id = 44, NameZh = '游侠', NameEn = 'Ranger', MaleBody = 33, FemaleBody = 34, Desc = '弓箭手攻击灵活、移动迅速，能从较远的距离或高处攻击敌人。', Skill = _EmptyTable, MaxJobLevel = 200, AdvancedOccupation = _EmptyTable, AdvanceClass = _EmptyTable, Type = 4, TypeBranch = 41, icon = 'icon_4_4', InitialAttr = {{name='Str',value=12},{name='Vit',value=24},{name='Luk',value=72},{name='Int',value=12},{name='Dex',value=96},{name='Agi',value=48}}, AddPointSolution = {38,39,40}, Explain = '超长远程、物理、单体高伤害', AdvancedTeacher = 1053, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Dex=6}},
	[51] = {id = 51, NameZh = '服事', NameEn = 'Acolyte', MaleBody = 35, FemaleBody = 36, Desc = '服事有治愈及治疗能力，拥有很强的力量对付不死系的敌人。', Skill = {144001,145001,146001,147001,148001,149001,150001,157001}, MaxJobLevel = 50, AdvancedOccupation = { BaseLv=40}, AdvanceClass = {52,122}, Type = 5, TypeBranch = 51, icon = 'icon_5_1', InitialAttr = {{name='Str',value=24},{name='Vit',value=60},{name='Luk',value=20},{name='Int',value=96},{name='Dex',value=48},{name='Agi',value=12}}, AddPointSolution = {11,12,13}, Explain = '远程、魔法、治疗、辅助', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[52] = {id = 52, NameZh = '牧师', NameEn = 'Priest', MaleBody = 37, FemaleBody = 38, Desc = '服事的进阶职业－牧师，战斗时能施放队伍不可或缺的强力辅助技能，集万千宠爱于一身！', Skill = {151001,152001,153001,154001,155001,156001,159001,160001,161001,163001,235001}, MaxJobLevel = 90, AdvancedOccupation = {BaseLv=70}, AdvanceClass = {53}, Type = 5, TypeBranch = 51, icon = 'icon_5_2', InitialAttr = {{name='Str',value=24},{name='Vit',value=60},{name='Luk',value=20},{name='Int',value=96},{name='Dex',value=48},{name='Agi',value=12}}, AddPointSolution = {11,12,13}, Explain = '远程、魔法、治疗、辅助', AdvancedTeacher = 1054, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[53] = {id = 53, NameZh = '神官', NameEn = 'HighPriest', MaleBody = 39, FemaleBody = 40, Desc = '服事有治愈及治疗能力，拥有很强的力量对付不死系的敌人。', Skill = {158001,162001,164001,165001,171001,172001,230001,231001,232001,233001,234001}, MaxJobLevel = 130, MaxPeak = 160, AdvancedOccupation = {BaseLv=100}, AdvanceClass = _EmptyTable, Type = 5, TypeBranch = 51, icon = 'icon_5_3', InitialAttr = {{name='Str',value=24},{name='Vit',value=60},{name='Luk',value=20},{name='Int',value=96},{name='Dex',value=48},{name='Agi',value=12}}, AddPointSolution = {11,12,13}, Explain = '远程、魔法、治疗、辅助', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Vit=4}},
	[54] = {id = 54, NameZh = '大主教', NameEn = 'Archbishop', MaleBody = 41, FemaleBody = 42, Desc = '服事有治愈及治疗能力，拥有很强的力量对付不死系的敌人。', Skill = _EmptyTable, MaxJobLevel = 200, AdvancedOccupation = _EmptyTable, AdvanceClass = _EmptyTable, Type = 5, TypeBranch = 51, icon = 'icon_5_4', InitialAttr = {{name='Str',value=24},{name='Vit',value=60},{name='Luk',value=20},{name='Int',value=96},{name='Dex',value=48},{name='Agi',value=12}}, AddPointSolution = {41,42,43}, Explain = '远程、魔法、治疗、辅助', AdvancedTeacher = 1054, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Vit=6}},
	[61] = {id = 61, NameZh = '商人', NameEn = 'Merchant', MaleBody = 43, FemaleBody = 44, Desc = '拥有基本的攻击力及一般的能力。', Skill = {204001,228001,208001,263001,264001,265001,266001,267001}, MaxJobLevel = 50, AdvancedOccupation = { BaseLv=40}, AdvanceClass = {62,132}, Type = 6, TypeBranch = 61, icon = 'icon_6_1', InitialAttr = {{name='Str',value=96},{name='Vit',value=72},{name='Luk',value=24},{name='Int',value=24},{name='Dex',value=72},{name='Agi',value=48}}, AddPointSolution = {17,18}, Explain = '战斗、辅助、交易大师', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[62] = {id = 62, NameZh = '铁匠', NameEn = 'Blacksmith', MaleBody = 45, FemaleBody = 46, Desc = '拥有基本的攻击力及一般的能力。', Skill = {205001,210001,211001,212001,213001,214001,260001,261001,269001,270001,272001,273001,274001}, MaxJobLevel = 90, AdvancedOccupation = {BaseLv=70}, AdvanceClass = {63}, Type = 6, TypeBranch = 61, icon = 'icon_6_2', InitialAttr = {{name='Str',value=96},{name='Vit',value=72},{name='Luk',value=24},{name='Int',value=24},{name='Dex',value=72},{name='Agi',value=48}}, AddPointSolution = {17,18}, Explain = '战斗、辅助、交易大师', AdvancedTeacher = 1055, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[63] = {id = 63, NameZh = '神工匠', NameEn = 'Whitesmith', MaleBody = 47, FemaleBody = 48, Desc = '拥有基本的攻击力及一般的能力。', Skill = {206001,215001,216001,217001,218001,219001,220001,221001,226001,262001,268001}, MaxJobLevel = 130, MaxPeak = 160, AdvancedOccupation = {BaseLv=100}, AdvanceClass = _EmptyTable, Type = 6, TypeBranch = 61, icon = 'icon_6_3', InitialAttr = {{name='Str',value=96},{name='Vit',value=72},{name='Luk',value=24},{name='Int',value=24},{name='Dex',value=72},{name='Agi',value=48}}, AddPointSolution = {17,18}, Explain = '战斗、辅助、交易大师', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Luk=4}},
	[64] = {id = 64, NameZh = '机匠', NameEn = 'Mechanic', MaleBody = 49, FemaleBody = 50, Desc = '拥有基本的攻击力及一般的能力。', Skill = _EmptyTable, MaxJobLevel = 200, AdvancedOccupation = _EmptyTable, AdvanceClass = _EmptyTable, Type = 6, TypeBranch = 61, icon = 'icon_6_4', InitialAttr = {{name='Str',value=96},{name='Vit',value=72},{name='Luk',value=24},{name='Int',value=24},{name='Dex',value=72},{name='Agi',value=48}}, AddPointSolution = {44,45}, Explain = '战斗、辅助、交易大师', AdvancedTeacher = 1055, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Luk=6}},
	[72] = {id = 72, NameZh = '十字军', NameEn = 'Crusader', MaleBody = 53, FemaleBody = 54, Desc = '侍奉神的战士，拥有强大的耐力和防御力，攻击手段也多样。', Skill = {350001,353001,354001,355001,356001,367001,368001,369001,370001,371001,360001}, MaxJobLevel = 90, AdvancedOccupation = {BaseLv=70}, AdvanceClass = {73}, Type = 1, TypeBranch = 12, icon = 'icon_7_2', InitialAttr = {{name='Str',value=72},{name='Vit',value=96},{name='Luk',value=24},{name='Int',value=72},{name='Dex',value=48},{name='Agi',value=24}}, AddPointSolution = {22,23,24}, Explain = '近战、守护、生存能力强', AdvancedTeacher = 1050, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[73] = {id = 73, NameZh = '圣殿十字军', NameEn = 'Paladin', MaleBody = 55, FemaleBody = 56, Desc = '侍奉神的战士，拥有强大的耐力和防御力，攻击手段也多样。', Skill = {351001,357001,358001,361001,362001,363001,364001,365001,366001,352001}, MaxJobLevel = 130, MaxPeak = 160, AdvancedOccupation = {BaseLv=100}, AdvanceClass = _EmptyTable, Type = 1, TypeBranch = 12, icon = 'icon_7_3', InitialAttr = {{name='Str',value=72},{name='Vit',value=96},{name='Luk',value=24},{name='Int',value=72},{name='Dex',value=48},{name='Agi',value=24}}, AddPointSolution = {22,23,24}, Explain = '近战、守护、生存能力强', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Vit=4}},
	[74] = {id = 74, NameZh = '皇家卫士', NameEn = 'RoyalGuard', MaleBody = 57, FemaleBody = 58, Desc = '侍奉神的战士，拥有强大的耐力和防御力，攻击手段也多样。', Skill = _EmptyTable, MaxJobLevel = 200, AdvancedOccupation = _EmptyTable, AdvanceClass = _EmptyTable, Type = 1, TypeBranch = 12, icon = 'icon_7_4', InitialAttr = {{name='Str',value=72},{name='Vit',value=96},{name='Luk',value=24},{name='Int',value=72},{name='Dex',value=48},{name='Agi',value=24}}, AddPointSolution = {59,60,61}, Explain = '近战、守护、生存能力强', AdvancedTeacher = 1050, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Vit=6}},
	[82] = {id = 82, NameZh = '贤者', NameEn = 'Sage', MaleBody = 57, FemaleBody = 58, Desc = '', Skill = _EmptyTable, MaxJobLevel = 90, AdvancedOccupation = {BaseLv=70}, AdvanceClass = {83}, Type = 2, TypeBranch = 22, icon = '', InitialAttr = {{name='Str',value=12},{name='Vit',value=48},{name='Luk',value=24},{name='Int',value=96},{name='Dex',value=72},{name='Agi',value=12}}, AddPointSolution = _EmptyTable, Explain = '', DamRandom = {1,1}, IsOpen = 0, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[83] = {id = 83, NameZh = '智者', NameEn = 'Professor', MaleBody = 59, FemaleBody = 60, Desc = '', Skill = _EmptyTable, MaxJobLevel = 130, MaxPeak = 160, AdvancedOccupation = {BaseLv=100}, AdvanceClass = _EmptyTable, Type = 2, TypeBranch = 22, icon = '', InitialAttr = {{name='Str',value=24},{name='Vit',value=36},{name='Luk',value=48},{name='Int',value=96},{name='Dex',value=96},{name='Agi',value=24}}, AddPointSolution = _EmptyTable, Explain = '', DamRandom = {1,1}, IsOpen = 0, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[84] = {id = 84, NameZh = '元素使', NameEn = 'Sorcerer', MaleBody = 61, FemaleBody = 62, Desc = '', Skill = _EmptyTable, MaxJobLevel = 200, AdvancedOccupation = _EmptyTable, AdvanceClass = _EmptyTable, Type = 2, TypeBranch = 22, icon = '', InitialAttr = {{name='Str',value=24},{name='Vit',value=36},{name='Luk',value=48},{name='Int',value=96},{name='Dex',value=96},{name='Agi',value=24}}, AddPointSolution = _EmptyTable, Explain = '', DamRandom = {1,1}, IsOpen = 0, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[92] = {id = 92, NameZh = '流氓', NameEn = 'Rogue', MaleBody = 73, FemaleBody = 74, Desc = '', Skill = {465001,467001,468001,471001,472001,474001,475001,477001,478001,479001,480001,481001}, MaxJobLevel = 90, AdvancedOccupation = {BaseLv=70}, AdvanceClass = {93}, Type = 3, TypeBranch = 32, icon = 'icon_9_2', InitialAttr = {{name='Str',value=48},{name='Vit',value=24},{name='Luk',value=96},{name='Int',value=24},{name='Dex',value=48},{name='Agi',value=96}}, AddPointSolution = {28,29,30}, Explain = '偷袭、卸除、远近程兼备', AdvancedTeacher = 1052, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[93] = {id = 93, NameZh = '神行', NameEn = 'Stalker', MaleBody = 75, FemaleBody = 76, Desc = '', Skill = {473001,476001,482001,483001,484001,485001,486001,487001,491001,492001,493001,494001,495001,496001,497001}, MaxJobLevel = 130, MaxPeak = 160, AdvancedOccupation = {BaseLv=100}, AdvanceClass = _EmptyTable, Type = 3, TypeBranch = 32, icon = 'icon_9_3', InitialAttr = {{name='Str',value=48},{name='Vit',value=24},{name='Luk',value=96},{name='Int',value=24},{name='Dex',value=48},{name='Agi',value=96}}, AddPointSolution = {28,29,30}, Explain = '偷袭、卸除、远近程兼备', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Luk=4}},
	[94] = {id = 94, NameZh = '逐影', NameEn = 'ShadowChaser', MaleBody = 77, FemaleBody = 78, Desc = '', Skill = _EmptyTable, MaxJobLevel = 200, AdvancedOccupation = _EmptyTable, AdvanceClass = _EmptyTable, Type = 3, TypeBranch = 32, icon = 'icon_9_4', InitialAttr = {{name='Str',value=48},{name='Vit',value=24},{name='Luk',value=96},{name='Int',value=24},{name='Dex',value=48},{name='Agi',value=96}}, AddPointSolution = {52,53,54}, Explain = '偷袭、卸除、远近程兼备', AdvancedTeacher = 1052, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Luk=6}},
	[102] = {id = 102, NameZh = '诗人', NameEn = 'Bard', MaleBody = 79, FemaleBody = 80, Desc = '', Skill = _EmptyTable, MaxJobLevel = 90, AdvancedOccupation = {BaseLv=70}, AdvanceClass = {103}, Type = 4, TypeBranch = 42, icon = '', InitialAttr = {{name='Str',value=24},{name='Vit',value=48},{name='Luk',value=48},{name='Int',value=24},{name='Dex',value=96},{name='Agi',value=96}}, AddPointSolution = _EmptyTable, Explain = '', DamRandom = {1,1}, IsOpen = 0, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[103] = {id = 103, NameZh = '搞笑艺人', NameEn = 'Clown', MaleBody = 81, FemaleBody = 72, Desc = '', Skill = _EmptyTable, MaxJobLevel = 130, MaxPeak = 160, AdvancedOccupation = {BaseLv=100}, AdvanceClass = _EmptyTable, Type = 4, TypeBranch = 42, icon = '', InitialAttr = {{name='Str',value=24},{name='Vit',value=48},{name='Luk',value=48},{name='Int',value=24},{name='Dex',value=96},{name='Agi',value=96}}, AddPointSolution = _EmptyTable, Explain = '', DamRandom = {1,1}, IsOpen = 0, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[104] = {id = 104, NameZh = '宫廷乐师', NameEn = 'Minstrel', MaleBody = 83, FemaleBody = 74, Desc = '', Skill = _EmptyTable, MaxJobLevel = 200, AdvancedOccupation = _EmptyTable, AdvanceClass = _EmptyTable, Type = 4, TypeBranch = 42, icon = '', InitialAttr = {{name='Str',value=24},{name='Vit',value=48},{name='Luk',value=48},{name='Int',value=24},{name='Dex',value=96},{name='Agi',value=96}}, AddPointSolution = _EmptyTable, Explain = '', DamRandom = {1,1}, IsOpen = 0, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[112] = {id = 112, NameZh = '舞娘', NameEn = 'Dancer', MaleBody = 79, FemaleBody = 80, Desc = '', Skill = _EmptyTable, MaxJobLevel = 90, AdvancedOccupation = {BaseLv=70}, AdvanceClass = {113}, Type = 4, TypeBranch = 43, icon = '', InitialAttr = {{name='Str',value=24},{name='Vit',value=48},{name='Luk',value=48},{name='Int',value=24},{name='Dex',value=96},{name='Agi',value=96}}, AddPointSolution = _EmptyTable, Explain = '', DamRandom = {1,1}, IsOpen = 0, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[113] = {id = 113, NameZh = '冷艳舞姬', NameEn = 'Gypsy', MaleBody = 81, FemaleBody = 82, Desc = '', Skill = _EmptyTable, MaxJobLevel = 130, MaxPeak = 160, AdvancedOccupation = {BaseLv=100}, AdvanceClass = _EmptyTable, Type = 4, TypeBranch = 43, icon = '', InitialAttr = {{name='Str',value=24},{name='Vit',value=48},{name='Luk',value=48},{name='Int',value=24},{name='Dex',value=96},{name='Agi',value=96}}, AddPointSolution = _EmptyTable, Explain = '', DamRandom = {1,1}, IsOpen = 0, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[114] = {id = 114, NameZh = '漫游舞者', NameEn = 'Wanderer', MaleBody = 83, FemaleBody = 84, Desc = '', Skill = _EmptyTable, MaxJobLevel = 200, AdvancedOccupation = _EmptyTable, AdvanceClass = _EmptyTable, Type = 4, TypeBranch = 43, icon = '', InitialAttr = {{name='Str',value=24},{name='Vit',value=48},{name='Luk',value=48},{name='Int',value=24},{name='Dex',value=96},{name='Agi',value=96}}, AddPointSolution = _EmptyTable, Explain = '', DamRandom = {1,1}, IsOpen = 0, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[122] = {id = 122, NameZh = '武僧', NameEn = 'Monk', MaleBody = 60, FemaleBody = 61, Desc = '极限修炼肉体的圣职者，拥有超绝的爆发力。', Skill = {301001,303001,304001,305001,306001,307001,309001,310001,311001,312001,313001,314001,315001}, MaxJobLevel = 90, AdvancedOccupation = {BaseLv=70}, AdvanceClass = {123}, Type = 5, TypeBranch = 52, icon = 'icon_12_2', InitialAttr = {{name='Str',value=24},{name='Vit',value=72},{name='Luk',value=24},{name='Int',value=96},{name='Dex',value=48},{name='Agi',value=24}}, AddPointSolution = {19,20,21}, Explain = '近战、辅助、爆发', AdvancedTeacher = 1054, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[123] = {id = 123, NameZh = '武术宗师', NameEn = 'Champion', MaleBody = 62, FemaleBody = 63, Desc = '极限修炼肉体的圣职者，拥有超绝的爆发力。', Skill = {316001,317001,318001,319001,320001,321001,322001,323001,324001,325001}, MaxJobLevel = 130, MaxPeak = 160, AdvancedOccupation = {BaseLv=100}, AdvanceClass = _EmptyTable, Type = 5, TypeBranch = 52, icon = 'icon_12_3', InitialAttr = {{name='Str',value=24},{name='Vit',value=72},{name='Luk',value=24},{name='Int',value=96},{name='Dex',value=48},{name='Agi',value=24}}, AddPointSolution = {19,20,21}, Explain = '近战、辅助、爆发', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Int=4}},
	[124] = {id = 124, NameZh = '修罗', NameEn = 'Shura', MaleBody = 64, FemaleBody = 65, Desc = '极限修炼肉体的圣职者，拥有超绝的爆发力。', Skill = _EmptyTable, MaxJobLevel = 200, AdvancedOccupation = _EmptyTable, AdvanceClass = _EmptyTable, Type = 5, TypeBranch = 52, icon = 'icon_12_4', InitialAttr = {{name='Str',value=24},{name='Vit',value=72},{name='Luk',value=24},{name='Int',value=96},{name='Dex',value=48},{name='Agi',value=24}}, AddPointSolution = {49,50,51}, Explain = '近战、辅助、爆发', AdvancedTeacher = 1054, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Int=6}},
	[132] = {id = 132, NameZh = '炼金术士', NameEn = 'Alchemist', MaleBody = 67, FemaleBody = 68, Desc = '', Skill = {410001,411001,412001,413001,414001,415001,416001,417001,418001,419001,420001,421001}, MaxJobLevel = 90, AdvancedOccupation = {BaseLv=70}, AdvanceClass = {133}, Type = 6, TypeBranch = 62, icon = 'icon_13_2', InitialAttr = {{name='Str',value=72},{name='Vit',value=96},{name='Luk',value=24},{name='Int',value=72},{name='Dex',value=48},{name='Agi',value=24}}, AddPointSolution = {25,26,27}, Explain = '药剂、装备破坏、生命体', AdvancedTeacher = 1055, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
	[133] = {id = 133, NameZh = '创造者', NameEn = 'Creator', MaleBody = 69, FemaleBody = 70, Desc = '', Skill = {422001,423001,424001,425001,426001,427001,428001,429001,430001,431001,432001,463001,464001}, MaxJobLevel = 130, MaxPeak = 160, AdvancedOccupation = {BaseLv=100}, AdvanceClass = _EmptyTable, Type = 6, TypeBranch = 62, icon = 'icon_13_3', InitialAttr = {{name='Str',value=72},{name='Vit',value=96},{name='Luk',value=24},{name='Int',value=72},{name='Dex',value=48},{name='Agi',value=24}}, AddPointSolution = {25,26,27}, Explain = '药剂、装备破坏、生命体', AdvancedTeacher = 10, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Str=4}},
	[134] = {id = 134, NameZh = '基因学者', NameEn = 'Genetic', MaleBody = 71, FemaleBody = 72, Desc = '', Skill = _EmptyTable, MaxJobLevel = 200, AdvancedOccupation = _EmptyTable, AdvanceClass = _EmptyTable, Type = 6, TypeBranch = 62, icon = 'icon_13_4', InitialAttr = {{name='Str',value=72},{name='Vit',value=96},{name='Luk',value=24},{name='Int',value=72},{name='Dex',value=48},{name='Agi',value=24}}, AddPointSolution = {55,56,57,58}, Explain = '药剂、装备破坏、生命体', AdvancedTeacher = 1055, DamRandom = {1,1}, IsOpen = 1, ActionSuffixMap = _EmptyTable, UnlockAttr = {Str=6}},
	[500] = {id = 500, NameZh = '冒险技能', NameEn = 'RiskSkill', Desc = '', Skill = _EmptyTable, MaxJobLevel = 100, AdvancedOccupation = _EmptyTable, AdvanceClass = _EmptyTable, Type = 9, TypeBranch = 91, icon = '', InitialAttr = _EmptyTable, AddPointSolution = _EmptyTable, Explain = '', DamRandom = {1,1}, ActionSuffixMap = _EmptyTable, UnlockAttr = _EmptyTable},
}
Table_Class_fields = { "id","NameZh","NameEn","MaleBody","FemaleBody","Desc","Skill","MaxJobLevel","MaxPeak","AdvancedOccupation","AdvanceClass","Type","TypeBranch","icon","InitialAttr","AddPointSolution","Explain","AdvancedTeacher","DamRandom","IsOpen","ActionSuffixMap","UnlockAttr",}
return Table_Class
