/*
** Lua binding: lua_upgrade
*/

#include "tolua.h"

#ifndef __cplusplus
#include <stdlib.h>
#endif
#ifdef __cplusplus
 extern "C" int tolua_bnd_takeownership (lua_State* L); // from tolua_map.c
#else
 int tolua_bnd_takeownership (lua_State* L); /* from tolua_map.c */
#endif
#include <string.h>

/* Exported function */
TOLUA_API int tolua_lua_upgrade_open (lua_State* tolua_S);
LUALIB_API int luaopen_lua_upgrade (lua_State* tolua_S);

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

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_MonoClassData (lua_State* tolua_S)
{
 MonoClassData* self = (MonoClassData*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_HeroData (lua_State* tolua_S)
{
 HeroData* self = (HeroData*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_MonoVTableData (lua_State* tolua_S)
{
 MonoVTableData* self = (MonoVTableData*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_MonoArrayData (lua_State* tolua_S)
{
 MonoArrayData* self = (MonoArrayData*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_CreatureData (lua_State* tolua_S)
{
 CreatureData* self = (CreatureData*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_BattleManager (lua_State* tolua_S)
{
 BattleManager* self = (BattleManager*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_MonsterData (lua_State* tolua_S)
{
 MonsterData* self = (MonsterData*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_MonoObjectData (lua_State* tolua_S)
{
 MonoObjectData* self = (MonoObjectData*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_MonoClassFieldData (lua_State* tolua_S)
{
 MonoClassFieldData* self = (MonoClassFieldData*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_MonoMethodData (lua_State* tolua_S)
{
 MonoMethodData* self = (MonoMethodData*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_MonoTypeData (lua_State* tolua_S)
{
 MonoTypeData* self = (MonoTypeData*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_gunichar2 (lua_State* tolua_S)
{
 gunichar2* self = (gunichar2*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"HeroData");
 tolua_usertype(tolua_S,"MonoType");
 tolua_usertype(tolua_S,"MonoMethod");
 tolua_usertype(tolua_S,"MonoClassField");
 tolua_usertype(tolua_S,"mono_array_lower_bound_t");
 tolua_usertype(tolua_S,"MonoArray");
 tolua_usertype(tolua_S,"gunichar2");
 tolua_usertype(tolua_S,"CreatureData");
 tolua_usertype(tolua_S,"MonoClassRuntimeInfo");
 tolua_usertype(tolua_S,"ProcessScanner");
 tolua_usertype(tolua_S,"mono_array_size_t");
 tolua_usertype(tolua_S,"MonsterData");
 tolua_usertype(tolua_S,"_CreatureData");
 tolua_usertype(tolua_S,"MonoThreadsSync");
 tolua_usertype(tolua_S,"MonoClass");
 tolua_usertype(tolua_S,"MonoObjectData");
 tolua_usertype(tolua_S,"gpointer");
 tolua_usertype(tolua_S,"MonoGenericClass");
 tolua_usertype(tolua_S,"MonoVTableData");
 tolua_usertype(tolua_S,"BattleManager");
 tolua_usertype(tolua_S,"MonoMethodData");
 tolua_usertype(tolua_S,"MonoClassFieldData");
 tolua_usertype(tolua_S,"LuaShell");
 tolua_usertype(tolua_S,"MonoTypeData");
 tolua_usertype(tolua_S,"MonoObject");
 tolua_usertype(tolua_S,"MonoClassData");
 tolua_usertype(tolua_S,"MonoArrayData");
 tolua_usertype(tolua_S,"MonoVTable");
 tolua_usertype(tolua_S,"MonoMethodSignature");
 tolua_usertype(tolua_S,"MonoArrayBounds");
 tolua_usertype(tolua_S,"guint16");
 tolua_usertype(tolua_S,"MonoMarshalType");
 tolua_usertype(tolua_S,"MonoString");
 tolua_usertype(tolua_S,"MonoClassExt");
 tolua_usertype(tolua_S,"MonoRuntimeGenericContext");
 tolua_usertype(tolua_S,"guint8");
 tolua_usertype(tolua_S,"gint32");
 tolua_usertype(tolua_S,"MonoDomain");
 tolua_usertype(tolua_S,"MonoGenericContainer");
 tolua_usertype(tolua_S,"guint32");
 tolua_usertype(tolua_S,"MonoImage");
}

/* get function: creatureId of class  HeroData */
static int tolua_get_HeroData_HeroData_unsigned_creatureId(lua_State* tolua_S)
{
  HeroData* self = (HeroData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'creatureId'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->creatureId);
 return 1;
}

/* set function: creatureId of class  HeroData */
static int tolua_set_HeroData_HeroData_unsigned_creatureId(lua_State* tolua_S)
{
  HeroData* self = (HeroData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'creatureId'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->creatureId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: title of class  HeroData */
static int tolua_get_HeroData_HeroData_title(lua_State* tolua_S)
{
  HeroData* self = (HeroData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'title'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->title);
 return 1;
}

/* set function: title of class  HeroData */
static int tolua_set_HeroData_HeroData_title(lua_State* tolua_S)
{
  HeroData* self = (HeroData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'title'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->title = ((char*)  tolua_tostring(tolua_S,2,0));
 return 0;
}

/* get function: name of class  HeroData */
static int tolua_get_HeroData_HeroData_name(lua_State* tolua_S)
{
  HeroData* self = (HeroData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->name);
 return 1;
}

/* set function: name of class  HeroData */
static int tolua_set_HeroData_HeroData_name(lua_State* tolua_S)
{
  HeroData* self = (HeroData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->name = ((char*)  tolua_tostring(tolua_S,2,0));
 return 0;
}

/* get function: combatType of class  HeroData */
static int tolua_get_HeroData_HeroData_unsigned_combatType(lua_State* tolua_S)
{
  HeroData* self = (HeroData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'combatType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->combatType);
 return 1;
}

/* set function: combatType of class  HeroData */
static int tolua_set_HeroData_HeroData_unsigned_combatType(lua_State* tolua_S)
{
  HeroData* self = (HeroData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'combatType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->combatType = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseHp of class  HeroData */
static int tolua_get_HeroData_HeroData_unsigned_baseHp(lua_State* tolua_S)
{
  HeroData* self = (HeroData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseHp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseHp);
 return 1;
}

/* set function: baseHp of class  HeroData */
static int tolua_set_HeroData_HeroData_unsigned_baseHp(lua_State* tolua_S)
{
  HeroData* self = (HeroData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseHp'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseHp = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: creatureId of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_unsigned_creatureId(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'creatureId'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->creatureId);
 return 1;
}

/* set function: creatureId of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_unsigned_creatureId(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'creatureId'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->creatureId = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: combatType of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_unsigned_combatType(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'combatType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->combatType);
 return 1;
}

/* set function: combatType of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_unsigned_combatType(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'combatType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->combatType = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseHp of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_unsigned_baseHp(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseHp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseHp);
 return 1;
}

/* set function: baseHp of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_unsigned_baseHp(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseHp'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseHp = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: hpf of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_unsigned_hpf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hpf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->hpf);
 return 1;
}

/* set function: hpf of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_unsigned_hpf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hpf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hpf = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseMp of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_unsigned_baseMp(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseMp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseMp);
 return 1;
}

/* set function: baseMp of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_unsigned_baseMp(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseMp'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseMp = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: mpf of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_mpf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mpf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->mpf);
 return 1;
}

/* set function: mpf of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_mpf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mpf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mpf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseMpRegen of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_baseMpRegen(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseMpRegen'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseMpRegen);
 return 1;
}

/* set function: baseMpRegen of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_baseMpRegen(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseMpRegen'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseMpRegen = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: mprf of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_mprf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mprf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->mprf);
 return 1;
}

/* set function: mprf of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_mprf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mprf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mprf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseAttackPoint of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_unsigned_baseAttackPoint(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseAttackPoint'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseAttackPoint);
 return 1;
}

/* set function: baseAttackPoint of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_unsigned_baseAttackPoint(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseAttackPoint'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseAttackPoint = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: apf of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_apf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'apf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->apf);
 return 1;
}

/* set function: apf of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_apf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'apf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->apf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: movePoint of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_unsigned_movePoint(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'movePoint'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->movePoint);
 return 1;
}

/* set function: movePoint of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_unsigned_movePoint(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'movePoint'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->movePoint = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseDr of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_baseDr(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseDr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseDr);
 return 1;
}

/* set function: baseDr of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_baseDr(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseDr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseDr = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: drf of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_drf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'drf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->drf);
 return 1;
}

/* set function: drf of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_drf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'drf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->drf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseCr of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_baseCr(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseCr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseCr);
 return 1;
}

/* set function: baseCr of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_baseCr(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseCr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseCr = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: crf of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_crf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'crf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->crf);
 return 1;
}

/* set function: crf of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_crf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'crf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->crf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseDgr of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_baseDgr(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseDgr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseDgr);
 return 1;
}

/* set function: baseDgr of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_baseDgr(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseDgr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseDgr = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: dgrf of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_dgrf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dgrf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dgrf);
 return 1;
}

/* set function: dgrf of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_dgrf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dgrf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dgrf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseHr of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_baseHr(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseHr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseHr);
 return 1;
}

/* set function: baseHr of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_baseHr(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseHr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseHr = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: hrf of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_hrf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hrf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->hrf);
 return 1;
}

/* set function: hrf of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_hrf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hrf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hrf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseCar of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_baseCar(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseCar'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseCar);
 return 1;
}

/* set function: baseCar of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_baseCar(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseCar'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseCar = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: carf of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_carf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'carf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->carf);
 return 1;
}

/* set function: carf of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_carf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'carf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->carf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseCadr of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_baseCadr(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseCadr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseCadr);
 return 1;
}

/* set function: baseCadr of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_baseCadr(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseCadr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseCadr = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: cadrf of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_cadrf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cadrf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->cadrf);
 return 1;
}

/* set function: cadrf of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_cadrf(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cadrf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->cadrf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: mastery of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_mastery(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mastery'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->mastery);
 return 1;
}

/* set function: mastery of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_mastery(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mastery'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mastery = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: skill0 of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_skill0(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill0'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill0);
 return 1;
}

/* set function: skill0 of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_skill0(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill0'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skill0 = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: skill1 of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_skill1(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill1'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill1);
 return 1;
}

/* set function: skill1 of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_skill1(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill1'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skill1 = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: skill2 of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_skill2(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill2'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill2);
 return 1;
}

/* set function: skill2 of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_skill2(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill2'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skill2 = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: skill3 of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_skill3(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill3'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill3);
 return 1;
}

/* set function: skill3 of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_skill3(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill3'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skill3 = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: skill4 of class  _CreatureData */
static int tolua_get__CreatureData__CreatureData_skill4(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill4'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill4);
 return 1;
}

/* set function: skill4 of class  _CreatureData */
static int tolua_set__CreatureData__CreatureData_skill4(lua_State* tolua_S)
{
  _CreatureData* self = (_CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill4'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skill4 = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: monsterId of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_monsterId(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'monsterId'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->monsterId);
 return 1;
}

/* set function: monsterId of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_monsterId(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'monsterId'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->monsterId = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: creatureid of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_creatureid(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'creatureid'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->creatureid);
 return 1;
}

/* set function: creatureid of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_creatureid(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'creatureid'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->creatureid = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: cognitionRange of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_cognitionRange(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cognitionRange'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->cognitionRange);
 return 1;
}

/* set function: cognitionRange of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_cognitionRange(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cognitionRange'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->cognitionRange = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: boss of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_boss(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'boss'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->boss);
 return 1;
}

/* set function: boss of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_boss(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'boss'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->boss = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: level of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_level(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'level'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->level);
 return 1;
}

/* set function: level of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_level(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'level'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->level = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: hpRate of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_hpRate(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hpRate'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->hpRate);
 return 1;
}

/* set function: hpRate of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_hpRate(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hpRate'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hpRate = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: apRate of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_apRate(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'apRate'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->apRate);
 return 1;
}

/* set function: apRate of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_apRate(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'apRate'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->apRate = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: hp of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_hp(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->hp);
 return 1;
}

/* set function: hp of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_hp(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hp'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hp = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: mp of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_mp(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->mp);
 return 1;
}

/* set function: mp of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_mp(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mp'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mp = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: ap of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_ap(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ap'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->ap);
 return 1;
}

/* set function: ap of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_ap(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ap'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ap = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: dr of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_dr(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dr);
 return 1;
}

/* set function: dr of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_dr(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dr = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: cr of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_cr(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->cr);
 return 1;
}

/* set function: cr of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_cr(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->cr = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: dodge of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_dodge(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dodge'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dodge);
 return 1;
}

/* set function: dodge of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_dodge(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dodge'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dodge = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: hr of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_hr(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->hr);
 return 1;
}

/* set function: hr of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_hr(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hr = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: car of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_car(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'car'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->car);
 return 1;
}

/* set function: car of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_car(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'car'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->car = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: cadr of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_cadr(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cadr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->cadr);
 return 1;
}

/* set function: cadr of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_cadr(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cadr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->cadr = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: movePoint of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_movePoint(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'movePoint'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->movePoint);
 return 1;
}

/* set function: movePoint of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_movePoint(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'movePoint'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->movePoint = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: skill0Lv of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_skill0Lv(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill0Lv'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill0Lv);
 return 1;
}

/* set function: skill0Lv of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_skill0Lv(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill0Lv'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skill0Lv = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: skill1Lv of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_skill1Lv(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill1Lv'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill1Lv);
 return 1;
}

/* set function: skill1Lv of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_skill1Lv(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill1Lv'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skill1Lv = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: skill2Lv of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_skill2Lv(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill2Lv'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill2Lv);
 return 1;
}

/* set function: skill2Lv of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_skill2Lv(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill2Lv'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skill2Lv = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: passiveLv of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_passiveLv(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'passiveLv'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->passiveLv);
 return 1;
}

/* set function: passiveLv of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_passiveLv(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'passiveLv'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->passiveLv = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: tribalism of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_tribalism(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tribalism'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->tribalism);
 return 1;
}

/* set function: tribalism of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_tribalism(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tribalism'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->tribalism = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: moveSpeed of class  MonsterData */
static int tolua_get_MonsterData_MonsterData_moveSpeed(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'moveSpeed'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->moveSpeed);
 return 1;
}

/* set function: moveSpeed of class  MonsterData */
static int tolua_set_MonsterData_MonsterData_moveSpeed(lua_State* tolua_S)
{
  MonsterData* self = (MonsterData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'moveSpeed'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->moveSpeed = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: creatureId of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_creatureId(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'creatureId'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->creatureId);
 return 1;
}

/* set function: creatureId of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_creatureId(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'creatureId'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->creatureId = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: combatType of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_combatType(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'combatType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->combatType);
 return 1;
}

/* set function: combatType of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_combatType(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'combatType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->combatType = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseHp of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_baseHp(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseHp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseHp);
 return 1;
}

/* set function: baseHp of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_baseHp(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseHp'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseHp = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: hpf of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_hpf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hpf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->hpf);
 return 1;
}

/* set function: hpf of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_hpf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hpf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hpf = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseMp of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_baseMp(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseMp'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseMp);
 return 1;
}

/* set function: baseMp of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_baseMp(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseMp'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseMp = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: mpf of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_mpf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mpf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->mpf);
 return 1;
}

/* set function: mpf of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_mpf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mpf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mpf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseMpRegen of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_baseMpRegen(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseMpRegen'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseMpRegen);
 return 1;
}

/* set function: baseMpRegen of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_baseMpRegen(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseMpRegen'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseMpRegen = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: mprf of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_mprf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mprf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->mprf);
 return 1;
}

/* set function: mprf of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_mprf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mprf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mprf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseAttackPoint of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_baseAttackPoint(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseAttackPoint'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseAttackPoint);
 return 1;
}

/* set function: baseAttackPoint of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_baseAttackPoint(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseAttackPoint'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseAttackPoint = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: apf of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_apf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'apf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->apf);
 return 1;
}

/* set function: apf of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_apf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'apf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->apf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: movePoint of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_movePoint(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'movePoint'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->movePoint);
 return 1;
}

/* set function: movePoint of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_movePoint(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'movePoint'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->movePoint = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseDr of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_baseDr(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseDr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseDr);
 return 1;
}

/* set function: baseDr of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_baseDr(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseDr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseDr = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: drf of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_drf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'drf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->drf);
 return 1;
}

/* set function: drf of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_drf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'drf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->drf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseCr of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_baseCr(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseCr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseCr);
 return 1;
}

/* set function: baseCr of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_baseCr(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseCr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseCr = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: crf of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_crf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'crf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->crf);
 return 1;
}

/* set function: crf of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_crf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'crf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->crf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseDgr of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_baseDgr(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseDgr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseDgr);
 return 1;
}

/* set function: baseDgr of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_baseDgr(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseDgr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseDgr = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: dgrf of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_dgrf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dgrf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->dgrf);
 return 1;
}

/* set function: dgrf of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_dgrf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dgrf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dgrf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseHr of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_baseHr(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseHr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseHr);
 return 1;
}

/* set function: baseHr of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_baseHr(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseHr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseHr = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: hrf of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_hrf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hrf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->hrf);
 return 1;
}

/* set function: hrf of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_hrf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hrf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hrf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseCar of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_baseCar(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseCar'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseCar);
 return 1;
}

/* set function: baseCar of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_baseCar(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseCar'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseCar = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: carf of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_carf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'carf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->carf);
 return 1;
}

/* set function: carf of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_carf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'carf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->carf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: baseCadr of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_baseCadr(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseCadr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->baseCadr);
 return 1;
}

/* set function: baseCadr of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_baseCadr(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseCadr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseCadr = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: cadrf of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_cadrf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cadrf'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->cadrf);
 return 1;
}

/* set function: cadrf of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_cadrf(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cadrf'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->cadrf = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: mastery of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_mastery(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mastery'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->mastery);
 return 1;
}

/* set function: mastery of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_mastery(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mastery'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mastery = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: skill0 of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_skill0(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill0'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill0);
 return 1;
}

/* set function: skill0 of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_skill0(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill0'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skill0 = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: skill1 of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_skill1(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill1'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill1);
 return 1;
}

/* set function: skill1 of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_skill1(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill1'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skill1 = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: skill2 of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_skill2(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill2'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill2);
 return 1;
}

/* set function: skill2 of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_skill2(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill2'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skill2 = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: skill3 of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_skill3(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill3'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill3);
 return 1;
}

/* set function: skill3 of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_skill3(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill3'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skill3 = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: skill4 of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_skill4(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill4'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->skill4);
 return 1;
}

/* set function: skill4 of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_skill4(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skill4'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skill4 = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: levelType of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_levelType(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'levelType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->levelType);
 return 1;
}

/* set function: levelType of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_levelType(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'levelType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->levelType = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: creatureType of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_creatureType(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'creatureType'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->creatureType);
 return 1;
}

/* set function: creatureType of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_creatureType(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'creatureType'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->creatureType = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: moveType0 of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_moveType0(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'moveType0'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->moveType0);
 return 1;
}

/* set function: moveType0 of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_moveType0(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'moveType0'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->moveType0 = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: moveType1 of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_moveType1(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'moveType1'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->moveType1);
 return 1;
}

/* set function: moveType1 of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_moveType1(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'moveType1'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->moveType1 = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: moveType2 of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_moveType2(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'moveType2'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->moveType2);
 return 1;
}

/* set function: moveType2 of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_moveType2(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'moveType2'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->moveType2 = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: name of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_name(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->name);
 return 1;
}

/* set function: name of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_name(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->name = ((char*)  tolua_tostring(tolua_S,2,0));
 return 0;
}

/* get function: graphicPrefeb of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_graphicPrefeb(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'graphicPrefeb'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->graphicPrefeb);
 return 1;
}

/* set function: graphicPrefeb of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_graphicPrefeb(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'graphicPrefeb'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->graphicPrefeb = ((char*)  tolua_tostring(tolua_S,2,0));
 return 0;
}

/* get function: creatureIcon of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_creatureIcon(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'creatureIcon'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->creatureIcon);
 return 1;
}

/* set function: creatureIcon of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_creatureIcon(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'creatureIcon'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->creatureIcon = ((char*)  tolua_tostring(tolua_S,2,0));
 return 0;
}

/* get function: description of class  CreatureData */
static int tolua_get_CreatureData_CreatureData_description(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'description'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->description);
 return 1;
}

/* set function: description of class  CreatureData */
static int tolua_set_CreatureData_CreatureData_description(lua_State* tolua_S)
{
  CreatureData* self = (CreatureData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'description'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->description = ((char*)  tolua_tostring(tolua_S,2,0));
 return 0;
}

/* get function: pscan of class  LuaShell */
static int tolua_get_LuaShell_LuaShell_pscan(lua_State* tolua_S)
{
  LuaShell* self = (LuaShell*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pscan'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->pscan,"ProcessScanner");
 return 1;
}

/* set function: pscan of class  LuaShell */
static int tolua_set_LuaShell_LuaShell_pscan(lua_State* tolua_S)
{
  LuaShell* self = (LuaShell*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pscan'",NULL);
 if (!tolua_isusertype(tolua_S,2,"ProcessScanner",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pscan = *((ProcessScanner*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: element_class of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_element_class_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'element_class'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->element_class,"MonoClass");
 return 1;
}

/* set function: element_class of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_element_class_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'element_class'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->element_class = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: cast_class of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_cast_class_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cast_class'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->cast_class,"MonoClass");
 return 1;
}

/* set function: cast_class of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_cast_class_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cast_class'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->cast_class = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: idepth of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_idepth(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'idepth'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->idepth,"guint16");
 return 1;
}

/* set function: idepth of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_idepth(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'idepth'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint16",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->idepth = *((guint16*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: rank of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_rank(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rank'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->rank,"guint8");
 return 1;
}

/* set function: rank of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_rank(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rank'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint8",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rank = *((guint8*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: instance_size of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_instance_size(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'instance_size'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->instance_size);
 return 1;
}

/* set function: instance_size of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_instance_size(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'instance_size'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->instance_size = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: exception_type of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_exception_type(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'exception_type'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->exception_type,"guint8");
 return 1;
}

/* set function: exception_type of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_exception_type(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'exception_type'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint8",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->exception_type = *((guint8*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: parent of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_parent_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'parent'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->parent,"MonoClass");
 return 1;
}

/* set function: parent of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_parent_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'parent'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->parent = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: nested_in of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_nested_in_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nested_in'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->nested_in,"MonoClass");
 return 1;
}

/* set function: nested_in of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_nested_in_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nested_in'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nested_in = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: image of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_image_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'image'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->image,"MonoImage");
 return 1;
}

/* set function: image of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_image_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'image'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoImage",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->image = ((MonoImage*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: name of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_name(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->name);
 return 1;
}

/* get function: name_space of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_name_space(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name_space'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->name_space);
 return 1;
}

/* get function: type_token of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_type_token(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type_token'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->type_token,"guint32");
 return 1;
}

/* set function: type_token of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_type_token(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type_token'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint32",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->type_token = *((guint32*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: vtable_size of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_vtable_size(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vtable_size'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->vtable_size);
 return 1;
}

/* set function: vtable_size of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_vtable_size(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vtable_size'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->vtable_size = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: interface_count of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_interface_count(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'interface_count'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->interface_count,"guint16");
 return 1;
}

/* set function: interface_count of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_interface_count(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'interface_count'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint16",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->interface_count = *((guint16*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: interface_id of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_interface_id(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'interface_id'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->interface_id,"guint16");
 return 1;
}

/* set function: interface_id of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_interface_id(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'interface_id'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint16",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->interface_id = *((guint16*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: max_interface_id of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_max_interface_id(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'max_interface_id'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->max_interface_id,"guint16");
 return 1;
}

/* set function: max_interface_id of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_max_interface_id(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'max_interface_id'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint16",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->max_interface_id = *((guint16*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: interface_offsets_count of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_interface_offsets_count(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'interface_offsets_count'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->interface_offsets_count,"guint16");
 return 1;
}

/* set function: interface_offsets_count of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_interface_offsets_count(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'interface_offsets_count'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint16",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->interface_offsets_count = *((guint16*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: interface_offsets_packed of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_interface_offsets_packed_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'interface_offsets_packed'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->interface_offsets_packed,"guint16");
 return 1;
}

/* set function: interface_offsets_packed of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_interface_offsets_packed_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'interface_offsets_packed'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint16",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->interface_offsets_packed = ((guint16*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: interface_bitmap of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_interface_bitmap_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'interface_bitmap'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->interface_bitmap,"guint8");
 return 1;
}

/* set function: interface_bitmap of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_interface_bitmap_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'interface_bitmap'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint8",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->interface_bitmap = ((guint8*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: flags of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_flags(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'flags'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->flags,"guint32");
 return 1;
}

/* set function: flags of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_flags(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'flags'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint32",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->flags = *((guint32*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: marshal_info of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_marshal_info_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'marshal_info'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->marshal_info,"MonoMarshalType");
 return 1;
}

/* set function: marshal_info of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_marshal_info_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'marshal_info'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoMarshalType",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->marshal_info = ((MonoMarshalType*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: fields of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_fields_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fields'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->fields,"MonoClassField");
 return 1;
}

/* set function: fields of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_fields_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fields'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoClassField",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fields = ((MonoClassField*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: this_arg of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_this_arg(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'this_arg'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->this_arg,"MonoType");
 return 1;
}

/* set function: this_arg of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_this_arg(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'this_arg'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoType",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->this_arg = *((MonoType*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: byval_arg of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_byval_arg(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byval_arg'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->byval_arg,"MonoType");
 return 1;
}

/* set function: byval_arg of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_byval_arg(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'byval_arg'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoType",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->byval_arg = *((MonoType*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: generic_class of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_generic_class_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'generic_class'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->generic_class,"MonoGenericClass");
 return 1;
}

/* set function: generic_class of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_generic_class_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'generic_class'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoGenericClass",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->generic_class = ((MonoGenericClass*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: generic_container of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_generic_container_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'generic_container'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->generic_container,"MonoGenericContainer");
 return 1;
}

/* set function: generic_container of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_generic_container_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'generic_container'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoGenericContainer",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->generic_container = ((MonoGenericContainer*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: reflection_info of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_reflection_info(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'reflection_info'",NULL);
#endif
 tolua_pushuserdata(tolua_S,(void*)self->reflection_info);
 return 1;
}

/* set function: reflection_info of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_reflection_info(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'reflection_info'",NULL);
 if (!tolua_isuserdata(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->reflection_info = ((void*)  tolua_touserdata(tolua_S,2,0));
 return 0;
}

/* get function: gc_descr of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_gc_descr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gc_descr'",NULL);
#endif
 tolua_pushuserdata(tolua_S,(void*)self->gc_descr);
 return 1;
}

/* set function: gc_descr of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_gc_descr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gc_descr'",NULL);
 if (!tolua_isuserdata(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->gc_descr = ((void*)  tolua_touserdata(tolua_S,2,0));
 return 0;
}

/* get function: runtime_info of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_runtime_info_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'runtime_info'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->runtime_info,"MonoClassRuntimeInfo");
 return 1;
}

/* set function: runtime_info of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_runtime_info_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'runtime_info'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoClassRuntimeInfo",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->runtime_info = ((MonoClassRuntimeInfo*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: next_class_cache of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_unsigned_next_class_cache(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'next_class_cache'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->next_class_cache);
 return 1;
}

/* set function: next_class_cache of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_unsigned_next_class_cache(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'next_class_cache'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->next_class_cache = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: ext of class  MonoClass */
static int tolua_get_MonoClass_MonoClass_ext_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ext'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->ext,"MonoClassExt");
 return 1;
}

/* set function: ext of class  MonoClass */
static int tolua_set_MonoClass_MonoClass_ext_ptr(lua_State* tolua_S)
{
  MonoClass* self = (MonoClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ext'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoClassExt",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ext = ((MonoClassExt*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: klass of class  MonoVTable */
static int tolua_get_MonoVTable_MonoVTable_klass_ptr(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'klass'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->klass,"MonoClass");
 return 1;
}

/* set function: klass of class  MonoVTable */
static int tolua_set_MonoVTable_MonoVTable_klass_ptr(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'klass'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->klass = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: gc_descr of class  MonoVTable */
static int tolua_get_MonoVTable_MonoVTable_gc_descr(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gc_descr'",NULL);
#endif
 tolua_pushuserdata(tolua_S,(void*)self->gc_descr);
 return 1;
}

/* set function: gc_descr of class  MonoVTable */
static int tolua_set_MonoVTable_MonoVTable_gc_descr(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gc_descr'",NULL);
 if (!tolua_isuserdata(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->gc_descr = ((void*)  tolua_touserdata(tolua_S,2,0));
 return 0;
}

/* get function: domain of class  MonoVTable */
static int tolua_get_MonoVTable_MonoVTable_domain_ptr(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'domain'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->domain,"MonoDomain");
 return 1;
}

/* set function: domain of class  MonoVTable */
static int tolua_set_MonoVTable_MonoVTable_domain_ptr(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'domain'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoDomain",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->domain = ((MonoDomain*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: data of class  MonoVTable */
static int tolua_get_MonoVTable_MonoVTable_data(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'data'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->data,"gpointer");
 return 1;
}

/* set function: data of class  MonoVTable */
static int tolua_set_MonoVTable_MonoVTable_data(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'data'",NULL);
 if (!tolua_isusertype(tolua_S,2,"gpointer",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->data = *((gpointer*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: type of class  MonoVTable */
static int tolua_get_MonoVTable_MonoVTable_type(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->type,"gpointer");
 return 1;
}

/* set function: type of class  MonoVTable */
static int tolua_set_MonoVTable_MonoVTable_type(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type'",NULL);
 if (!tolua_isusertype(tolua_S,2,"gpointer",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->type = *((gpointer*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: interface_bitmap of class  MonoVTable */
static int tolua_get_MonoVTable_MonoVTable_interface_bitmap_ptr(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'interface_bitmap'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->interface_bitmap,"guint8");
 return 1;
}

/* set function: interface_bitmap of class  MonoVTable */
static int tolua_set_MonoVTable_MonoVTable_interface_bitmap_ptr(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'interface_bitmap'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint8",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->interface_bitmap = ((guint8*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: max_interface_id of class  MonoVTable */
static int tolua_get_MonoVTable_MonoVTable_max_interface_id(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'max_interface_id'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->max_interface_id,"guint16");
 return 1;
}

/* set function: max_interface_id of class  MonoVTable */
static int tolua_set_MonoVTable_MonoVTable_max_interface_id(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'max_interface_id'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint16",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->max_interface_id = *((guint16*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: rank of class  MonoVTable */
static int tolua_get_MonoVTable_MonoVTable_rank(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rank'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->rank,"guint8");
 return 1;
}

/* set function: rank of class  MonoVTable */
static int tolua_set_MonoVTable_MonoVTable_rank(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rank'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint8",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rank = *((guint8*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: imt_collisions_bitmap of class  MonoVTable */
static int tolua_get_MonoVTable_MonoVTable_imt_collisions_bitmap(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'imt_collisions_bitmap'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->imt_collisions_bitmap,"guint32");
 return 1;
}

/* set function: imt_collisions_bitmap of class  MonoVTable */
static int tolua_set_MonoVTable_MonoVTable_imt_collisions_bitmap(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'imt_collisions_bitmap'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint32",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->imt_collisions_bitmap = *((guint32*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: runtime_generic_context of class  MonoVTable */
static int tolua_get_MonoVTable_MonoVTable_runtime_generic_context_ptr(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'runtime_generic_context'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->runtime_generic_context,"MonoRuntimeGenericContext");
 return 1;
}

/* set function: runtime_generic_context of class  MonoVTable */
static int tolua_set_MonoVTable_MonoVTable_runtime_generic_context_ptr(lua_State* tolua_S)
{
  MonoVTable* self = (MonoVTable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'runtime_generic_context'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoRuntimeGenericContext",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->runtime_generic_context = ((MonoRuntimeGenericContext*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: vtable of class  MonoObject */
static int tolua_get_MonoObject_MonoObject_vtable_ptr(lua_State* tolua_S)
{
  MonoObject* self = (MonoObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vtable'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->vtable,"MonoVTable");
 return 1;
}

/* set function: vtable of class  MonoObject */
static int tolua_set_MonoObject_MonoObject_vtable_ptr(lua_State* tolua_S)
{
  MonoObject* self = (MonoObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vtable'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoVTable",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->vtable = ((MonoVTable*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: synchronisation of class  MonoObject */
static int tolua_get_MonoObject_MonoObject_synchronisation_ptr(lua_State* tolua_S)
{
  MonoObject* self = (MonoObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'synchronisation'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->synchronisation,"MonoThreadsSync");
 return 1;
}

/* set function: synchronisation of class  MonoObject */
static int tolua_set_MonoObject_MonoObject_synchronisation_ptr(lua_State* tolua_S)
{
  MonoObject* self = (MonoObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'synchronisation'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoThreadsSync",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->synchronisation = ((MonoThreadsSync*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: object of class  MonoString */
static int tolua_get_MonoString_MonoString_object(lua_State* tolua_S)
{
  MonoString* self = (MonoString*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'object'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->object,"MonoObject");
 return 1;
}

/* set function: object of class  MonoString */
static int tolua_set_MonoString_MonoString_object(lua_State* tolua_S)
{
  MonoString* self = (MonoString*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'object'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoObject",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->object = *((MonoObject*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: length of class  MonoString */
static int tolua_get_MonoString_MonoString_length(lua_State* tolua_S)
{
  MonoString* self = (MonoString*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'length'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->length,"gint32");
 return 1;
}

/* set function: length of class  MonoString */
static int tolua_set_MonoString_MonoString_length(lua_State* tolua_S)
{
  MonoString* self = (MonoString*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'length'",NULL);
 if (!tolua_isusertype(tolua_S,2,"gint32",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->length = *((gint32*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: chars of class  MonoString */
static int tolua_get_lua_upgrade_MonoString_chars(lua_State* tolua_S)
{
 int tolua_index;
  MonoString* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (MonoString*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MONO_ZERO_LEN_ARRAY)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->chars[tolua_index],"gunichar2");
 return 1;
}

/* set function: chars of class  MonoString */
static int tolua_set_lua_upgrade_MonoString_chars(lua_State* tolua_S)
{
 int tolua_index;
  MonoString* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (MonoString*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MONO_ZERO_LEN_ARRAY)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->chars[tolua_index] = *((gunichar2*)  tolua_tousertype(tolua_S,3,0));
 return 0;
}

/* get function: length of class  MonoArrayBounds */
static int tolua_get_MonoArrayBounds_MonoArrayBounds_length(lua_State* tolua_S)
{
  MonoArrayBounds* self = (MonoArrayBounds*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'length'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->length,"mono_array_size_t");
 return 1;
}

/* set function: length of class  MonoArrayBounds */
static int tolua_set_MonoArrayBounds_MonoArrayBounds_length(lua_State* tolua_S)
{
  MonoArrayBounds* self = (MonoArrayBounds*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'length'",NULL);
 if (!tolua_isusertype(tolua_S,2,"mono_array_size_t",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->length = *((mono_array_size_t*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: lower_bound of class  MonoArrayBounds */
static int tolua_get_MonoArrayBounds_MonoArrayBounds_lower_bound(lua_State* tolua_S)
{
  MonoArrayBounds* self = (MonoArrayBounds*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lower_bound'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->lower_bound,"mono_array_lower_bound_t");
 return 1;
}

/* set function: lower_bound of class  MonoArrayBounds */
static int tolua_set_MonoArrayBounds_MonoArrayBounds_lower_bound(lua_State* tolua_S)
{
  MonoArrayBounds* self = (MonoArrayBounds*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lower_bound'",NULL);
 if (!tolua_isusertype(tolua_S,2,"mono_array_lower_bound_t",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->lower_bound = *((mono_array_lower_bound_t*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: obj of class  MonoArray */
static int tolua_get_MonoArray_MonoArray_obj(lua_State* tolua_S)
{
  MonoArray* self = (MonoArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'obj'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->obj,"MonoObject");
 return 1;
}

/* set function: obj of class  MonoArray */
static int tolua_set_MonoArray_MonoArray_obj(lua_State* tolua_S)
{
  MonoArray* self = (MonoArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'obj'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoObject",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->obj = *((MonoObject*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: bounds of class  MonoArray */
static int tolua_get_MonoArray_MonoArray_bounds_ptr(lua_State* tolua_S)
{
  MonoArray* self = (MonoArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bounds'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->bounds,"MonoArrayBounds");
 return 1;
}

/* set function: bounds of class  MonoArray */
static int tolua_set_MonoArray_MonoArray_bounds_ptr(lua_State* tolua_S)
{
  MonoArray* self = (MonoArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bounds'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoArrayBounds",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bounds = ((MonoArrayBounds*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: max_length of class  MonoArray */
static int tolua_get_MonoArray_MonoArray_max_length(lua_State* tolua_S)
{
  MonoArray* self = (MonoArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'max_length'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->max_length,"mono_array_size_t");
 return 1;
}

/* set function: max_length of class  MonoArray */
static int tolua_set_MonoArray_MonoArray_max_length(lua_State* tolua_S)
{
  MonoArray* self = (MonoArray*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'max_length'",NULL);
 if (!tolua_isusertype(tolua_S,2,"mono_array_size_t",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->max_length = *((mono_array_size_t*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: vector of class  MonoArray */
static int tolua_get_lua_upgrade_MonoArray_vector(lua_State* tolua_S)
{
 int tolua_index;
  MonoArray* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (MonoArray*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MONO_ZERO_LEN_ARRAY)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->vector[tolua_index]);
 return 1;
}

/* set function: vector of class  MonoArray */
static int tolua_set_lua_upgrade_MonoArray_vector(lua_State* tolua_S)
{
 int tolua_index;
  MonoArray* self;
 lua_pushstring(tolua_S,".self");
 lua_rawget(tolua_S,1);
 self = (MonoArray*)  lua_touserdata(tolua_S,-1);
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=MONO_ZERO_LEN_ARRAY)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  self->vector[tolua_index] = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
 return 0;
}

/* get function: flags of class  MonoMethod */
static int tolua_get_MonoMethod_MonoMethod_flags(lua_State* tolua_S)
{
  MonoMethod* self = (MonoMethod*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'flags'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->flags,"guint16");
 return 1;
}

/* set function: flags of class  MonoMethod */
static int tolua_set_MonoMethod_MonoMethod_flags(lua_State* tolua_S)
{
  MonoMethod* self = (MonoMethod*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'flags'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint16",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->flags = *((guint16*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: iflags of class  MonoMethod */
static int tolua_get_MonoMethod_MonoMethod_iflags(lua_State* tolua_S)
{
  MonoMethod* self = (MonoMethod*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iflags'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->iflags,"guint16");
 return 1;
}

/* set function: iflags of class  MonoMethod */
static int tolua_set_MonoMethod_MonoMethod_iflags(lua_State* tolua_S)
{
  MonoMethod* self = (MonoMethod*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iflags'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint16",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iflags = *((guint16*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: token of class  MonoMethod */
static int tolua_get_MonoMethod_MonoMethod_token(lua_State* tolua_S)
{
  MonoMethod* self = (MonoMethod*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'token'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->token,"guint32");
 return 1;
}

/* set function: token of class  MonoMethod */
static int tolua_set_MonoMethod_MonoMethod_token(lua_State* tolua_S)
{
  MonoMethod* self = (MonoMethod*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'token'",NULL);
 if (!tolua_isusertype(tolua_S,2,"guint32",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->token = *((guint32*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: klass of class  MonoMethod */
static int tolua_get_MonoMethod_MonoMethod_klass_ptr(lua_State* tolua_S)
{
  MonoMethod* self = (MonoMethod*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'klass'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->klass,"MonoClass");
 return 1;
}

/* set function: klass of class  MonoMethod */
static int tolua_set_MonoMethod_MonoMethod_klass_ptr(lua_State* tolua_S)
{
  MonoMethod* self = (MonoMethod*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'klass'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoClass",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->klass = ((MonoClass*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: signature of class  MonoMethod */
static int tolua_get_MonoMethod_MonoMethod_signature_ptr(lua_State* tolua_S)
{
  MonoMethod* self = (MonoMethod*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'signature'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)self->signature,"MonoMethodSignature");
 return 1;
}

/* set function: signature of class  MonoMethod */
static int tolua_set_MonoMethod_MonoMethod_signature_ptr(lua_State* tolua_S)
{
  MonoMethod* self = (MonoMethod*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'signature'",NULL);
 if (!tolua_isusertype(tolua_S,2,"MonoMethodSignature",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->signature = ((MonoMethodSignature*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: name of class  MonoMethod */
static int tolua_get_MonoMethod_MonoMethod_name(lua_State* tolua_S)
{
  MonoMethod* self = (MonoMethod*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->name);
 return 1;
}

/* method: get of class  MonoArrayData */
static int tolua_lua_upgrade_MonoArrayData_get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoArrayData",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoArrayData* self = (MonoArrayData*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->get(index);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}

/* get function: thisAddr of class  MonoClassData */
static int tolua_get_MonoClassData_MonoClassData_unsigned_thisAddr(lua_State* tolua_S)
{
  MonoClassData* self = (MonoClassData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'thisAddr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->thisAddr);
 return 1;
}

/* set function: thisAddr of class  MonoClassData */
static int tolua_set_MonoClassData_MonoClassData_unsigned_thisAddr(lua_State* tolua_S)
{
  MonoClassData* self = (MonoClassData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'thisAddr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->thisAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* method: show of class  MonoClassData */
static int tolua_lua_upgrade_MonoClassData_show00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoClassData",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoClassData* self = (MonoClassData*)  tolua_tousertype(tolua_S,1,0);
  ProcessScanner* pscan = ((ProcessScanner*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'show'",NULL);
#endif
 {
  self->show(*pscan);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'show'.",&tolua_err);
 return 0;
#endif
}

/* method: isValid of class  MonoClassData */
static int tolua_lua_upgrade_MonoClassData_isValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoClassData",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoClassData* self = (MonoClassData*)  tolua_tousertype(tolua_S,1,0);
  ProcessScanner* pscan = ((ProcessScanner*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isValid'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isValid(*pscan);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isValid'.",&tolua_err);
 return 0;
#endif
}

/* get function: thisAddr of class  MonoClassFieldData */
static int tolua_get_MonoClassFieldData_MonoClassFieldData_unsigned_thisAddr(lua_State* tolua_S)
{
  MonoClassFieldData* self = (MonoClassFieldData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'thisAddr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->thisAddr);
 return 1;
}

/* set function: thisAddr of class  MonoClassFieldData */
static int tolua_set_MonoClassFieldData_MonoClassFieldData_unsigned_thisAddr(lua_State* tolua_S)
{
  MonoClassFieldData* self = (MonoClassFieldData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'thisAddr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->thisAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* method: show of class  MonoClassFieldData */
static int tolua_lua_upgrade_MonoClassFieldData_show00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoClassFieldData",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoClassFieldData* self = (MonoClassFieldData*)  tolua_tousertype(tolua_S,1,0);
  ProcessScanner* pscan = ((ProcessScanner*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'show'",NULL);
#endif
 {
  self->show(*pscan);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'show'.",&tolua_err);
 return 0;
#endif
}

/* get function: thisAddr of class  MonoTypeData */
static int tolua_get_MonoTypeData_MonoTypeData_unsigned_thisAddr(lua_State* tolua_S)
{
  MonoTypeData* self = (MonoTypeData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'thisAddr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->thisAddr);
 return 1;
}

/* set function: thisAddr of class  MonoTypeData */
static int tolua_set_MonoTypeData_MonoTypeData_unsigned_thisAddr(lua_State* tolua_S)
{
  MonoTypeData* self = (MonoTypeData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'thisAddr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->thisAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* method: show of class  MonoTypeData */
static int tolua_lua_upgrade_MonoTypeData_show00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoTypeData",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoTypeData* self = (MonoTypeData*)  tolua_tousertype(tolua_S,1,0);
  ProcessScanner* pscan = ((ProcessScanner*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'show'",NULL);
#endif
 {
  self->show(*pscan);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'show'.",&tolua_err);
 return 0;
#endif
}

/* get function: thisAddr of class  MonoVTableData */
static int tolua_get_MonoVTableData_MonoVTableData_unsigned_thisAddr(lua_State* tolua_S)
{
  MonoVTableData* self = (MonoVTableData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'thisAddr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->thisAddr);
 return 1;
}

/* set function: thisAddr of class  MonoVTableData */
static int tolua_set_MonoVTableData_MonoVTableData_unsigned_thisAddr(lua_State* tolua_S)
{
  MonoVTableData* self = (MonoVTableData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'thisAddr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->thisAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* method: show of class  MonoVTableData */
static int tolua_lua_upgrade_MonoVTableData_show00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoVTableData",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoVTableData* self = (MonoVTableData*)  tolua_tousertype(tolua_S,1,0);
  ProcessScanner* pscan = ((ProcessScanner*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'show'",NULL);
#endif
 {
  self->show(*pscan);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'show'.",&tolua_err);
 return 0;
#endif
}

/* get function: thisAddr of class  MonoMethodData */
static int tolua_get_MonoMethodData_MonoMethodData_unsigned_thisAddr(lua_State* tolua_S)
{
  MonoMethodData* self = (MonoMethodData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'thisAddr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->thisAddr);
 return 1;
}

/* set function: thisAddr of class  MonoMethodData */
static int tolua_set_MonoMethodData_MonoMethodData_unsigned_thisAddr(lua_State* tolua_S)
{
  MonoMethodData* self = (MonoMethodData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'thisAddr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->thisAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* method: show of class  MonoMethodData */
static int tolua_lua_upgrade_MonoMethodData_show00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoMethodData",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoMethodData* self = (MonoMethodData*)  tolua_tousertype(tolua_S,1,0);
  ProcessScanner* pscan = ((ProcessScanner*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'show'",NULL);
#endif
 {
  self->show(*pscan);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'show'.",&tolua_err);
 return 0;
#endif
}

/* get function: thisAddr of class  MonoObjectData */
static int tolua_get_MonoObjectData_MonoObjectData_unsigned_thisAddr(lua_State* tolua_S)
{
  MonoObjectData* self = (MonoObjectData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'thisAddr'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->thisAddr);
 return 1;
}

/* set function: thisAddr of class  MonoObjectData */
static int tolua_set_MonoObjectData_MonoObjectData_unsigned_thisAddr(lua_State* tolua_S)
{
  MonoObjectData* self = (MonoObjectData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'thisAddr'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->thisAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* method: show of class  MonoObjectData */
static int tolua_lua_upgrade_MonoObjectData_show00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoObjectData",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoObjectData* self = (MonoObjectData*)  tolua_tousertype(tolua_S,1,0);
  ProcessScanner* pscan = ((ProcessScanner*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'show'",NULL);
#endif
 {
  self->show(*pscan);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'show'.",&tolua_err);
 return 0;
#endif
}

/* method: GetName of class  MonoObjectData */
static int tolua_lua_upgrade_MonoObjectData_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"MonoObjectData",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  MonoObjectData* self = (MonoObjectData*)  tolua_tousertype(tolua_S,1,0);
  ProcessScanner* pscan = ((ProcessScanner*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetName'",NULL);
#endif
 {
  char* tolua_ret = (char*)  self->GetName(*pscan);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetName'.",&tolua_err);
 return 0;
#endif
}

/* method: readMonoString of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_readMonoString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  unsigned int monoObjAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readMonoString'",NULL);
#endif
 {
  char* tolua_ret = (char*)  self->readMonoString(monoObjAddr);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readMonoString'.",&tolua_err);
 return 0;
#endif
}

/* method: IntFromHex of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_IntFromHex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  char* hex = ((char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IntFromHex'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->IntFromHex(hex);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IntFromHex'.",&tolua_err);
 return 0;
#endif
}

/* method: readMonoClassName of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_readMonoClassName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  unsigned int monoClassAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readMonoClassName'",NULL);
#endif
 {
  char* tolua_ret = (char*)  self->readMonoClassName(monoClassAddr);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readMonoClassName'.",&tolua_err);
 return 0;
#endif
}

/* method: readCString of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_readCString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  unsigned int monoClassAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readCString'",NULL);
#endif
 {
  char* tolua_ret = (char*)  self->readCString(monoClassAddr);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readCString'.",&tolua_err);
 return 0;
#endif
}

/* method: MonoClassScan of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_MonoClassScan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MonoClassScan'",NULL);
#endif
 {
  self->MonoClassScan();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MonoClassScan'.",&tolua_err);
 return 0;
#endif
}

/* method: MonoFindClass of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_MonoFindClass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  char* className = ((char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MonoFindClass'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->MonoFindClass(className);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MonoFindClass'.",&tolua_err);
 return 0;
#endif
}

/* method: MonoFindVtable of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_MonoFindVtable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  unsigned int classAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MonoFindVtable'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->MonoFindVtable(classAddr);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MonoFindVtable'.",&tolua_err);
 return 0;
#endif
}

/* method: ReadInt of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_ReadInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  unsigned int targetAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReadInt'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->ReadInt(targetAddr);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReadInt'.",&tolua_err);
 return 0;
#endif
}

/* method: MonoFindObject of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_MonoFindObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  unsigned int vTableAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MonoFindObject'",NULL);
#endif
 {
  self->MonoFindObject(vTableAddr);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MonoFindObject'.",&tolua_err);
 return 0;
#endif
}

/* method: isDataAddress of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_isDataAddress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  unsigned int addr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDataAddress'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isDataAddress(addr);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isDataAddress'.",&tolua_err);
 return 0;
#endif
}

/* method: readMonoClass of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_readMonoClass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  unsigned int monoClassAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readMonoClass'",NULL);
#endif
 {
  MonoClassData tolua_ret =  self->readMonoClass(monoClassAddr);
 {
#ifdef __cplusplus
 void* tolua_obj = new MonoClassData(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_MonoClassData),"MonoClassData");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(MonoClassData));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"MonoClassData");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readMonoClass'.",&tolua_err);
 return 0;
#endif
}

/* method: readMonoArray of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_readMonoArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  unsigned int monoArrayAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readMonoArray'",NULL);
#endif
 {
  MonoArrayData tolua_ret =  self->readMonoArray(monoArrayAddr);
 {
#ifdef __cplusplus
 void* tolua_obj = new MonoArrayData(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_MonoArrayData),"MonoArrayData");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(MonoArrayData));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"MonoArrayData");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readMonoArray'.",&tolua_err);
 return 0;
#endif
}

/* method: readMonoClassField of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_readMonoClassField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  unsigned int monoAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readMonoClassField'",NULL);
#endif
 {
  MonoClassFieldData tolua_ret =  self->readMonoClassField(monoAddr);
 {
#ifdef __cplusplus
 void* tolua_obj = new MonoClassFieldData(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_MonoClassFieldData),"MonoClassFieldData");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(MonoClassFieldData));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"MonoClassFieldData");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readMonoClassField'.",&tolua_err);
 return 0;
#endif
}

/* method: readMonoType of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_readMonoType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  unsigned int monoAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readMonoType'",NULL);
#endif
 {
  MonoTypeData tolua_ret =  self->readMonoType(monoAddr);
 {
#ifdef __cplusplus
 void* tolua_obj = new MonoTypeData(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_MonoTypeData),"MonoTypeData");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(MonoTypeData));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"MonoTypeData");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readMonoType'.",&tolua_err);
 return 0;
#endif
}

/* method: readMonoVTable of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_readMonoVTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  unsigned int monoAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readMonoVTable'",NULL);
#endif
 {
  MonoVTableData tolua_ret =  self->readMonoVTable(monoAddr);
 {
#ifdef __cplusplus
 void* tolua_obj = new MonoVTableData(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_MonoVTableData),"MonoVTableData");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(MonoVTableData));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"MonoVTableData");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readMonoVTable'.",&tolua_err);
 return 0;
#endif
}

/* method: readMonoMethod of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_readMonoMethod00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  unsigned int monoAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readMonoMethod'",NULL);
#endif
 {
  MonoMethodData tolua_ret =  self->readMonoMethod(monoAddr);
 {
#ifdef __cplusplus
 void* tolua_obj = new MonoMethodData(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_MonoMethodData),"MonoMethodData");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(MonoMethodData));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"MonoMethodData");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readMonoMethod'.",&tolua_err);
 return 0;
#endif
}

/* method: readMonoObject of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_readMonoObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  unsigned int monoAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readMonoObject'",NULL);
#endif
 {
  MonoObjectData tolua_ret =  self->readMonoObject(monoAddr);
 {
#ifdef __cplusplus
 void* tolua_obj = new MonoObjectData(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_MonoObjectData),"MonoObjectData");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(MonoObjectData));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"MonoObjectData");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readMonoObject'.",&tolua_err);
 return 0;
#endif
}

/* method: GetStaticClassFieldInt of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_GetStaticClassFieldInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isstring(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  char* className = ((char*)  tolua_tostring(tolua_S,2,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStaticClassFieldInt'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->GetStaticClassFieldInt(className,fieldName);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStaticClassFieldInt'.",&tolua_err);
 return 0;
#endif
}

/* method: GetStaticClassFieldShort of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_GetStaticClassFieldShort00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isstring(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  char* className = ((char*)  tolua_tostring(tolua_S,2,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStaticClassFieldShort'",NULL);
#endif
 {
  unsigned short tolua_ret = (unsigned short)  self->GetStaticClassFieldShort(className,fieldName);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStaticClassFieldShort'.",&tolua_err);
 return 0;
#endif
}

/* method: GetStaticClassFieldByte of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_GetStaticClassFieldByte00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isstring(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  char* className = ((char*)  tolua_tostring(tolua_S,2,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStaticClassFieldByte'",NULL);
#endif
 {
  unsigned char tolua_ret = (unsigned char)  self->GetStaticClassFieldByte(className,fieldName);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStaticClassFieldByte'.",&tolua_err);
 return 0;
#endif
}

/* method: GetStaticClassFieldCString of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_GetStaticClassFieldCString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isstring(tolua_S,3,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  char* className = ((char*)  tolua_tostring(tolua_S,2,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStaticClassFieldCString'",NULL);
#endif
 {
  char* tolua_ret = (char*)  self->GetStaticClassFieldCString(className,fieldName);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStaticClassFieldCString'.",&tolua_err);
 return 0;
#endif
}

/* method: GetInstanceClassFieldInt of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_GetInstanceClassFieldInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isstring(tolua_S,3,0,&tolua_err) || 
 !tolua_isstring(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  unsigned int objAddr = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  char* className = ((char*)  tolua_tostring(tolua_S,3,0));
  char* fieldName = ((char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInstanceClassFieldInt'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->GetInstanceClassFieldInt(objAddr,className,fieldName);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInstanceClassFieldInt'.",&tolua_err);
 return 0;
#endif
}

/* method: GetClassVTable of class  ProcessScanner */
static int tolua_lua_upgrade_ProcessScanner_GetClassVTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* self = (ProcessScanner*)  tolua_tousertype(tolua_S,1,0);
  char* className = ((char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetClassVTable'",NULL);
#endif
 {
  MonoVTableData tolua_ret =  self->GetClassVTable(className);
 {
#ifdef __cplusplus
 void* tolua_obj = new MonoVTableData(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_MonoVTableData),"MonoVTableData");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(MonoVTableData));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"MonoVTableData");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetClassVTable'.",&tolua_err);
 return 0;
#endif
}

/* function: FindCreatureByID */
static int tolua_lua_upgrade_FindCreatureByID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int creatureID = ((int)  tolua_tonumber(tolua_S,1,0));
 {
  CreatureData* tolua_ret = (CreatureData*)  FindCreatureByID(creatureID);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"CreatureData");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindCreatureByID'.",&tolua_err);
 return 0;
#endif
}

/* function: FindHeroByName */
static int tolua_lua_upgrade_FindHeroByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isstring(tolua_S,1,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  char* name = ((char*)  tolua_tostring(tolua_S,1,0));
 {
  struct HeroData* tolua_ret = (struct HeroData*)  FindHeroByName(name);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"HeroData");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindHeroByName'.",&tolua_err);
 return 0;
#endif
}

/* get function: monsters */
static int tolua_get_lua_upgrade_monsters(lua_State* tolua_S)
{
 int tolua_index;
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=10000000)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&monsters[tolua_index],"MonsterData");
 return 1;
}

/* set function: monsters */
static int tolua_set_lua_upgrade_monsters(lua_State* tolua_S)
{
 int tolua_index;
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=10000000)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  monsters[tolua_index] = *((struct MonsterData*)  tolua_tousertype(tolua_S,3,0));
 return 0;
}

/* get function: heros */
static int tolua_get_lua_upgrade_heros(lua_State* tolua_S)
{
 int tolua_index;
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=10000000)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&heros[tolua_index],"HeroData");
 return 1;
}

/* set function: heros */
static int tolua_set_lua_upgrade_heros(lua_State* tolua_S)
{
 int tolua_index;
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=10000000)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  heros[tolua_index] = *((struct HeroData*)  tolua_tousertype(tolua_S,3,0));
 return 0;
}

/* get function: creatures */
static int tolua_get_lua_upgrade_creatures(lua_State* tolua_S)
{
 int tolua_index;
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=10000000)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&creatures[tolua_index],"CreatureData");
 return 1;
}

/* set function: creatures */
static int tolua_set_lua_upgrade_creatures(lua_State* tolua_S)
{
 int tolua_index;
#ifndef TOLUA_RELEASE
 {
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in array indexing.",&tolua_err);
 }
#endif
 tolua_index = (int)tolua_tonumber(tolua_S,2,0)-1;
#ifndef TOLUA_RELEASE
 if (tolua_index<0 || tolua_index>=10000000)
 tolua_error(tolua_S,"array indexing out of range.",NULL);
#endif
  creatures[tolua_index] = *((struct CreatureData*)  tolua_tousertype(tolua_S,3,0));
 return 0;
}

/* get function: paramCharacterData */
static int tolua_get_paramCharacterData(lua_State* tolua_S)
{
 tolua_pushusertype(tolua_S,(void*)&paramCharacterData,"_CreatureData");
 return 1;
}

/* set function: paramCharacterData */
static int tolua_set_paramCharacterData(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isusertype(tolua_S,2,"_CreatureData",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  paramCharacterData = *((_CreatureData*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: flgShouldUpdate */
static int tolua_get_flgShouldUpdate(lua_State* tolua_S)
{
 tolua_pushboolean(tolua_S,(bool)flgShouldUpdate);
 return 1;
}

/* set function: flgShouldUpdate */
static int tolua_set_flgShouldUpdate(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  flgShouldUpdate = ((bool)  tolua_toboolean(tolua_S,2,0));
 return 0;
}

/* get function: luaResultInt */
static int tolua_get_unsigned_luaResultInt(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)luaResultInt);
 return 1;
}

/* set function: luaResultInt */
static int tolua_set_unsigned_luaResultInt(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  luaResultInt = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: luaShell */
static int tolua_get_luaShell(lua_State* tolua_S)
{
 tolua_pushusertype(tolua_S,(void*)&luaShell,"LuaShell");
 return 1;
}

/* set function: luaShell */
static int tolua_set_luaShell(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isusertype(tolua_S,2,"LuaShell",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  luaShell = *((LuaShell*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: luaMonsterList */
static int tolua_get_luaMonsterList(lua_State* tolua_S)
{
 tolua_pushstring(tolua_S,(const char*)luaMonsterList);
 return 1;
}

/* set function: luaMonsterList */
static int tolua_set_luaMonsterList(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy(luaMonsterList,tolua_tostring(tolua_S,2,0),1024-1);
 return 0;
}

/* function: GetBattleManager */
static int tolua_lua_upgrade_GetBattleManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"ProcessScanner",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  ProcessScanner* pscan = ((ProcessScanner*)  tolua_tousertype(tolua_S,1,0));
 {
  BattleManager tolua_ret =  GetBattleManager(*pscan);
 {
#ifdef __cplusplus
 void* tolua_obj = new BattleManager(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_BattleManager),"BattleManager");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(BattleManager));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"BattleManager");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBattleManager'.",&tolua_err);
 return 0;
#endif
}

/* Open lib function */
LUALIB_API int luaopen_lua_upgrade (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,1);
 tolua_beginmodule(tolua_S,NULL);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"HeroData","HeroData","",tolua_collect_HeroData);
#else
 tolua_cclass(tolua_S,"HeroData","HeroData","",NULL);
#endif
 tolua_beginmodule(tolua_S,"HeroData");
 tolua_variable(tolua_S,"creatureId",tolua_get_HeroData_HeroData_unsigned_creatureId,tolua_set_HeroData_HeroData_unsigned_creatureId);
 tolua_variable(tolua_S,"title",tolua_get_HeroData_HeroData_title,tolua_set_HeroData_HeroData_title);
 tolua_variable(tolua_S,"name",tolua_get_HeroData_HeroData_name,tolua_set_HeroData_HeroData_name);
 tolua_variable(tolua_S,"combatType",tolua_get_HeroData_HeroData_unsigned_combatType,tolua_set_HeroData_HeroData_unsigned_combatType);
 tolua_variable(tolua_S,"baseHp",tolua_get_HeroData_HeroData_unsigned_baseHp,tolua_set_HeroData_HeroData_unsigned_baseHp);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"_CreatureData","_CreatureData","",NULL);
 tolua_beginmodule(tolua_S,"_CreatureData");
 tolua_variable(tolua_S,"creatureId",tolua_get__CreatureData__CreatureData_unsigned_creatureId,tolua_set__CreatureData__CreatureData_unsigned_creatureId);
 tolua_variable(tolua_S,"combatType",tolua_get__CreatureData__CreatureData_unsigned_combatType,tolua_set__CreatureData__CreatureData_unsigned_combatType);
 tolua_variable(tolua_S,"baseHp",tolua_get__CreatureData__CreatureData_unsigned_baseHp,tolua_set__CreatureData__CreatureData_unsigned_baseHp);
 tolua_variable(tolua_S,"hpf",tolua_get__CreatureData__CreatureData_unsigned_hpf,tolua_set__CreatureData__CreatureData_unsigned_hpf);
 tolua_variable(tolua_S,"baseMp",tolua_get__CreatureData__CreatureData_unsigned_baseMp,tolua_set__CreatureData__CreatureData_unsigned_baseMp);
 tolua_variable(tolua_S,"mpf",tolua_get__CreatureData__CreatureData_mpf,tolua_set__CreatureData__CreatureData_mpf);
 tolua_variable(tolua_S,"baseMpRegen",tolua_get__CreatureData__CreatureData_baseMpRegen,tolua_set__CreatureData__CreatureData_baseMpRegen);
 tolua_variable(tolua_S,"mprf",tolua_get__CreatureData__CreatureData_mprf,tolua_set__CreatureData__CreatureData_mprf);
 tolua_variable(tolua_S,"baseAttackPoint",tolua_get__CreatureData__CreatureData_unsigned_baseAttackPoint,tolua_set__CreatureData__CreatureData_unsigned_baseAttackPoint);
 tolua_variable(tolua_S,"apf",tolua_get__CreatureData__CreatureData_apf,tolua_set__CreatureData__CreatureData_apf);
 tolua_variable(tolua_S,"movePoint",tolua_get__CreatureData__CreatureData_unsigned_movePoint,tolua_set__CreatureData__CreatureData_unsigned_movePoint);
 tolua_variable(tolua_S,"baseDr",tolua_get__CreatureData__CreatureData_baseDr,tolua_set__CreatureData__CreatureData_baseDr);
 tolua_variable(tolua_S,"drf",tolua_get__CreatureData__CreatureData_drf,tolua_set__CreatureData__CreatureData_drf);
 tolua_variable(tolua_S,"baseCr",tolua_get__CreatureData__CreatureData_baseCr,tolua_set__CreatureData__CreatureData_baseCr);
 tolua_variable(tolua_S,"crf",tolua_get__CreatureData__CreatureData_crf,tolua_set__CreatureData__CreatureData_crf);
 tolua_variable(tolua_S,"baseDgr",tolua_get__CreatureData__CreatureData_baseDgr,tolua_set__CreatureData__CreatureData_baseDgr);
 tolua_variable(tolua_S,"dgrf",tolua_get__CreatureData__CreatureData_dgrf,tolua_set__CreatureData__CreatureData_dgrf);
 tolua_variable(tolua_S,"baseHr",tolua_get__CreatureData__CreatureData_baseHr,tolua_set__CreatureData__CreatureData_baseHr);
 tolua_variable(tolua_S,"hrf",tolua_get__CreatureData__CreatureData_hrf,tolua_set__CreatureData__CreatureData_hrf);
 tolua_variable(tolua_S,"baseCar",tolua_get__CreatureData__CreatureData_baseCar,tolua_set__CreatureData__CreatureData_baseCar);
 tolua_variable(tolua_S,"carf",tolua_get__CreatureData__CreatureData_carf,tolua_set__CreatureData__CreatureData_carf);
 tolua_variable(tolua_S,"baseCadr",tolua_get__CreatureData__CreatureData_baseCadr,tolua_set__CreatureData__CreatureData_baseCadr);
 tolua_variable(tolua_S,"cadrf",tolua_get__CreatureData__CreatureData_cadrf,tolua_set__CreatureData__CreatureData_cadrf);
 tolua_variable(tolua_S,"mastery",tolua_get__CreatureData__CreatureData_mastery,tolua_set__CreatureData__CreatureData_mastery);
 tolua_variable(tolua_S,"skill0",tolua_get__CreatureData__CreatureData_skill0,tolua_set__CreatureData__CreatureData_skill0);
 tolua_variable(tolua_S,"skill1",tolua_get__CreatureData__CreatureData_skill1,tolua_set__CreatureData__CreatureData_skill1);
 tolua_variable(tolua_S,"skill2",tolua_get__CreatureData__CreatureData_skill2,tolua_set__CreatureData__CreatureData_skill2);
 tolua_variable(tolua_S,"skill3",tolua_get__CreatureData__CreatureData_skill3,tolua_set__CreatureData__CreatureData_skill3);
 tolua_variable(tolua_S,"skill4",tolua_get__CreatureData__CreatureData_skill4,tolua_set__CreatureData__CreatureData_skill4);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"MonsterData","MonsterData","",tolua_collect_MonsterData);
#else
 tolua_cclass(tolua_S,"MonsterData","MonsterData","",NULL);
#endif
 tolua_beginmodule(tolua_S,"MonsterData");
 tolua_variable(tolua_S,"monsterId",tolua_get_MonsterData_MonsterData_monsterId,tolua_set_MonsterData_MonsterData_monsterId);
 tolua_variable(tolua_S,"creatureid",tolua_get_MonsterData_MonsterData_creatureid,tolua_set_MonsterData_MonsterData_creatureid);
 tolua_variable(tolua_S,"cognitionRange",tolua_get_MonsterData_MonsterData_cognitionRange,tolua_set_MonsterData_MonsterData_cognitionRange);
 tolua_variable(tolua_S,"boss",tolua_get_MonsterData_MonsterData_boss,tolua_set_MonsterData_MonsterData_boss);
 tolua_variable(tolua_S,"level",tolua_get_MonsterData_MonsterData_level,tolua_set_MonsterData_MonsterData_level);
 tolua_variable(tolua_S,"hpRate",tolua_get_MonsterData_MonsterData_hpRate,tolua_set_MonsterData_MonsterData_hpRate);
 tolua_variable(tolua_S,"apRate",tolua_get_MonsterData_MonsterData_apRate,tolua_set_MonsterData_MonsterData_apRate);
 tolua_variable(tolua_S,"hp",tolua_get_MonsterData_MonsterData_hp,tolua_set_MonsterData_MonsterData_hp);
 tolua_variable(tolua_S,"mp",tolua_get_MonsterData_MonsterData_mp,tolua_set_MonsterData_MonsterData_mp);
 tolua_variable(tolua_S,"ap",tolua_get_MonsterData_MonsterData_ap,tolua_set_MonsterData_MonsterData_ap);
 tolua_variable(tolua_S,"dr",tolua_get_MonsterData_MonsterData_dr,tolua_set_MonsterData_MonsterData_dr);
 tolua_variable(tolua_S,"cr",tolua_get_MonsterData_MonsterData_cr,tolua_set_MonsterData_MonsterData_cr);
 tolua_variable(tolua_S,"dodge",tolua_get_MonsterData_MonsterData_dodge,tolua_set_MonsterData_MonsterData_dodge);
 tolua_variable(tolua_S,"hr",tolua_get_MonsterData_MonsterData_hr,tolua_set_MonsterData_MonsterData_hr);
 tolua_variable(tolua_S,"car",tolua_get_MonsterData_MonsterData_car,tolua_set_MonsterData_MonsterData_car);
 tolua_variable(tolua_S,"cadr",tolua_get_MonsterData_MonsterData_cadr,tolua_set_MonsterData_MonsterData_cadr);
 tolua_variable(tolua_S,"movePoint",tolua_get_MonsterData_MonsterData_movePoint,tolua_set_MonsterData_MonsterData_movePoint);
 tolua_variable(tolua_S,"skill0Lv",tolua_get_MonsterData_MonsterData_skill0Lv,tolua_set_MonsterData_MonsterData_skill0Lv);
 tolua_variable(tolua_S,"skill1Lv",tolua_get_MonsterData_MonsterData_skill1Lv,tolua_set_MonsterData_MonsterData_skill1Lv);
 tolua_variable(tolua_S,"skill2Lv",tolua_get_MonsterData_MonsterData_skill2Lv,tolua_set_MonsterData_MonsterData_skill2Lv);
 tolua_variable(tolua_S,"passiveLv",tolua_get_MonsterData_MonsterData_passiveLv,tolua_set_MonsterData_MonsterData_passiveLv);
 tolua_variable(tolua_S,"tribalism",tolua_get_MonsterData_MonsterData_tribalism,tolua_set_MonsterData_MonsterData_tribalism);
 tolua_variable(tolua_S,"moveSpeed",tolua_get_MonsterData_MonsterData_moveSpeed,tolua_set_MonsterData_MonsterData_moveSpeed);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"CreatureData","CreatureData","",tolua_collect_CreatureData);
#else
 tolua_cclass(tolua_S,"CreatureData","CreatureData","",NULL);
#endif
 tolua_beginmodule(tolua_S,"CreatureData");
 tolua_variable(tolua_S,"creatureId",tolua_get_CreatureData_CreatureData_creatureId,tolua_set_CreatureData_CreatureData_creatureId);
 tolua_variable(tolua_S,"combatType",tolua_get_CreatureData_CreatureData_combatType,tolua_set_CreatureData_CreatureData_combatType);
 tolua_variable(tolua_S,"baseHp",tolua_get_CreatureData_CreatureData_baseHp,tolua_set_CreatureData_CreatureData_baseHp);
 tolua_variable(tolua_S,"hpf",tolua_get_CreatureData_CreatureData_hpf,tolua_set_CreatureData_CreatureData_hpf);
 tolua_variable(tolua_S,"baseMp",tolua_get_CreatureData_CreatureData_baseMp,tolua_set_CreatureData_CreatureData_baseMp);
 tolua_variable(tolua_S,"mpf",tolua_get_CreatureData_CreatureData_mpf,tolua_set_CreatureData_CreatureData_mpf);
 tolua_variable(tolua_S,"baseMpRegen",tolua_get_CreatureData_CreatureData_baseMpRegen,tolua_set_CreatureData_CreatureData_baseMpRegen);
 tolua_variable(tolua_S,"mprf",tolua_get_CreatureData_CreatureData_mprf,tolua_set_CreatureData_CreatureData_mprf);
 tolua_variable(tolua_S,"baseAttackPoint",tolua_get_CreatureData_CreatureData_baseAttackPoint,tolua_set_CreatureData_CreatureData_baseAttackPoint);
 tolua_variable(tolua_S,"apf",tolua_get_CreatureData_CreatureData_apf,tolua_set_CreatureData_CreatureData_apf);
 tolua_variable(tolua_S,"movePoint",tolua_get_CreatureData_CreatureData_movePoint,tolua_set_CreatureData_CreatureData_movePoint);
 tolua_variable(tolua_S,"baseDr",tolua_get_CreatureData_CreatureData_baseDr,tolua_set_CreatureData_CreatureData_baseDr);
 tolua_variable(tolua_S,"drf",tolua_get_CreatureData_CreatureData_drf,tolua_set_CreatureData_CreatureData_drf);
 tolua_variable(tolua_S,"baseCr",tolua_get_CreatureData_CreatureData_baseCr,tolua_set_CreatureData_CreatureData_baseCr);
 tolua_variable(tolua_S,"crf",tolua_get_CreatureData_CreatureData_crf,tolua_set_CreatureData_CreatureData_crf);
 tolua_variable(tolua_S,"baseDgr",tolua_get_CreatureData_CreatureData_baseDgr,tolua_set_CreatureData_CreatureData_baseDgr);
 tolua_variable(tolua_S,"dgrf",tolua_get_CreatureData_CreatureData_dgrf,tolua_set_CreatureData_CreatureData_dgrf);
 tolua_variable(tolua_S,"baseHr",tolua_get_CreatureData_CreatureData_baseHr,tolua_set_CreatureData_CreatureData_baseHr);
 tolua_variable(tolua_S,"hrf",tolua_get_CreatureData_CreatureData_hrf,tolua_set_CreatureData_CreatureData_hrf);
 tolua_variable(tolua_S,"baseCar",tolua_get_CreatureData_CreatureData_baseCar,tolua_set_CreatureData_CreatureData_baseCar);
 tolua_variable(tolua_S,"carf",tolua_get_CreatureData_CreatureData_carf,tolua_set_CreatureData_CreatureData_carf);
 tolua_variable(tolua_S,"baseCadr",tolua_get_CreatureData_CreatureData_baseCadr,tolua_set_CreatureData_CreatureData_baseCadr);
 tolua_variable(tolua_S,"cadrf",tolua_get_CreatureData_CreatureData_cadrf,tolua_set_CreatureData_CreatureData_cadrf);
 tolua_variable(tolua_S,"mastery",tolua_get_CreatureData_CreatureData_mastery,tolua_set_CreatureData_CreatureData_mastery);
 tolua_variable(tolua_S,"skill0",tolua_get_CreatureData_CreatureData_skill0,tolua_set_CreatureData_CreatureData_skill0);
 tolua_variable(tolua_S,"skill1",tolua_get_CreatureData_CreatureData_skill1,tolua_set_CreatureData_CreatureData_skill1);
 tolua_variable(tolua_S,"skill2",tolua_get_CreatureData_CreatureData_skill2,tolua_set_CreatureData_CreatureData_skill2);
 tolua_variable(tolua_S,"skill3",tolua_get_CreatureData_CreatureData_skill3,tolua_set_CreatureData_CreatureData_skill3);
 tolua_variable(tolua_S,"skill4",tolua_get_CreatureData_CreatureData_skill4,tolua_set_CreatureData_CreatureData_skill4);
 tolua_variable(tolua_S,"levelType",tolua_get_CreatureData_CreatureData_levelType,tolua_set_CreatureData_CreatureData_levelType);
 tolua_variable(tolua_S,"creatureType",tolua_get_CreatureData_CreatureData_creatureType,tolua_set_CreatureData_CreatureData_creatureType);
 tolua_variable(tolua_S,"moveType0",tolua_get_CreatureData_CreatureData_moveType0,tolua_set_CreatureData_CreatureData_moveType0);
 tolua_variable(tolua_S,"moveType1",tolua_get_CreatureData_CreatureData_moveType1,tolua_set_CreatureData_CreatureData_moveType1);
 tolua_variable(tolua_S,"moveType2",tolua_get_CreatureData_CreatureData_moveType2,tolua_set_CreatureData_CreatureData_moveType2);
 tolua_variable(tolua_S,"name",tolua_get_CreatureData_CreatureData_name,tolua_set_CreatureData_CreatureData_name);
 tolua_variable(tolua_S,"graphicPrefeb",tolua_get_CreatureData_CreatureData_graphicPrefeb,tolua_set_CreatureData_CreatureData_graphicPrefeb);
 tolua_variable(tolua_S,"creatureIcon",tolua_get_CreatureData_CreatureData_creatureIcon,tolua_set_CreatureData_CreatureData_creatureIcon);
 tolua_variable(tolua_S,"description",tolua_get_CreatureData_CreatureData_description,tolua_set_CreatureData_CreatureData_description);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"LuaShell","LuaShell","",NULL);
 tolua_beginmodule(tolua_S,"LuaShell");
 tolua_variable(tolua_S,"pscan",tolua_get_LuaShell_LuaShell_pscan,tolua_set_LuaShell_LuaShell_pscan);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoClass","MonoClass","",NULL);
 tolua_beginmodule(tolua_S,"MonoClass");
 tolua_variable(tolua_S,"element_class",tolua_get_MonoClass_MonoClass_element_class_ptr,tolua_set_MonoClass_MonoClass_element_class_ptr);
 tolua_variable(tolua_S,"cast_class",tolua_get_MonoClass_MonoClass_cast_class_ptr,tolua_set_MonoClass_MonoClass_cast_class_ptr);
 tolua_variable(tolua_S,"idepth",tolua_get_MonoClass_MonoClass_idepth,tolua_set_MonoClass_MonoClass_idepth);
 tolua_variable(tolua_S,"rank",tolua_get_MonoClass_MonoClass_rank,tolua_set_MonoClass_MonoClass_rank);
 tolua_variable(tolua_S,"instance_size",tolua_get_MonoClass_MonoClass_instance_size,tolua_set_MonoClass_MonoClass_instance_size);
 tolua_variable(tolua_S,"exception_type",tolua_get_MonoClass_MonoClass_exception_type,tolua_set_MonoClass_MonoClass_exception_type);
 tolua_variable(tolua_S,"parent",tolua_get_MonoClass_MonoClass_parent_ptr,tolua_set_MonoClass_MonoClass_parent_ptr);
 tolua_variable(tolua_S,"nested_in",tolua_get_MonoClass_MonoClass_nested_in_ptr,tolua_set_MonoClass_MonoClass_nested_in_ptr);
 tolua_variable(tolua_S,"image",tolua_get_MonoClass_MonoClass_image_ptr,tolua_set_MonoClass_MonoClass_image_ptr);
 tolua_variable(tolua_S,"name",tolua_get_MonoClass_MonoClass_name,NULL);
 tolua_variable(tolua_S,"name_space",tolua_get_MonoClass_MonoClass_name_space,NULL);
 tolua_variable(tolua_S,"type_token",tolua_get_MonoClass_MonoClass_type_token,tolua_set_MonoClass_MonoClass_type_token);
 tolua_variable(tolua_S,"vtable_size",tolua_get_MonoClass_MonoClass_vtable_size,tolua_set_MonoClass_MonoClass_vtable_size);
 tolua_variable(tolua_S,"interface_count",tolua_get_MonoClass_MonoClass_interface_count,tolua_set_MonoClass_MonoClass_interface_count);
 tolua_variable(tolua_S,"interface_id",tolua_get_MonoClass_MonoClass_interface_id,tolua_set_MonoClass_MonoClass_interface_id);
 tolua_variable(tolua_S,"max_interface_id",tolua_get_MonoClass_MonoClass_max_interface_id,tolua_set_MonoClass_MonoClass_max_interface_id);
 tolua_variable(tolua_S,"interface_offsets_count",tolua_get_MonoClass_MonoClass_interface_offsets_count,tolua_set_MonoClass_MonoClass_interface_offsets_count);
 tolua_variable(tolua_S,"interface_offsets_packed",tolua_get_MonoClass_MonoClass_interface_offsets_packed_ptr,tolua_set_MonoClass_MonoClass_interface_offsets_packed_ptr);
 tolua_variable(tolua_S,"interface_bitmap",tolua_get_MonoClass_MonoClass_interface_bitmap_ptr,tolua_set_MonoClass_MonoClass_interface_bitmap_ptr);
 tolua_variable(tolua_S,"flags",tolua_get_MonoClass_MonoClass_flags,tolua_set_MonoClass_MonoClass_flags);
 tolua_variable(tolua_S,"marshal_info",tolua_get_MonoClass_MonoClass_marshal_info_ptr,tolua_set_MonoClass_MonoClass_marshal_info_ptr);
 tolua_variable(tolua_S,"fields",tolua_get_MonoClass_MonoClass_fields_ptr,tolua_set_MonoClass_MonoClass_fields_ptr);
 tolua_variable(tolua_S,"this_arg",tolua_get_MonoClass_MonoClass_this_arg,tolua_set_MonoClass_MonoClass_this_arg);
 tolua_variable(tolua_S,"byval_arg",tolua_get_MonoClass_MonoClass_byval_arg,tolua_set_MonoClass_MonoClass_byval_arg);
 tolua_variable(tolua_S,"generic_class",tolua_get_MonoClass_MonoClass_generic_class_ptr,tolua_set_MonoClass_MonoClass_generic_class_ptr);
 tolua_variable(tolua_S,"generic_container",tolua_get_MonoClass_MonoClass_generic_container_ptr,tolua_set_MonoClass_MonoClass_generic_container_ptr);
 tolua_variable(tolua_S,"reflection_info",tolua_get_MonoClass_MonoClass_reflection_info,tolua_set_MonoClass_MonoClass_reflection_info);
 tolua_variable(tolua_S,"gc_descr",tolua_get_MonoClass_MonoClass_gc_descr,tolua_set_MonoClass_MonoClass_gc_descr);
 tolua_variable(tolua_S,"runtime_info",tolua_get_MonoClass_MonoClass_runtime_info_ptr,tolua_set_MonoClass_MonoClass_runtime_info_ptr);
 tolua_variable(tolua_S,"next_class_cache",tolua_get_MonoClass_MonoClass_unsigned_next_class_cache,tolua_set_MonoClass_MonoClass_unsigned_next_class_cache);
 tolua_variable(tolua_S,"ext",tolua_get_MonoClass_MonoClass_ext_ptr,tolua_set_MonoClass_MonoClass_ext_ptr);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoVTable","MonoVTable","",NULL);
 tolua_beginmodule(tolua_S,"MonoVTable");
 tolua_variable(tolua_S,"klass",tolua_get_MonoVTable_MonoVTable_klass_ptr,tolua_set_MonoVTable_MonoVTable_klass_ptr);
 tolua_variable(tolua_S,"gc_descr",tolua_get_MonoVTable_MonoVTable_gc_descr,tolua_set_MonoVTable_MonoVTable_gc_descr);
 tolua_variable(tolua_S,"domain",tolua_get_MonoVTable_MonoVTable_domain_ptr,tolua_set_MonoVTable_MonoVTable_domain_ptr);
 tolua_variable(tolua_S,"data",tolua_get_MonoVTable_MonoVTable_data,tolua_set_MonoVTable_MonoVTable_data);
 tolua_variable(tolua_S,"type",tolua_get_MonoVTable_MonoVTable_type,tolua_set_MonoVTable_MonoVTable_type);
 tolua_variable(tolua_S,"interface_bitmap",tolua_get_MonoVTable_MonoVTable_interface_bitmap_ptr,tolua_set_MonoVTable_MonoVTable_interface_bitmap_ptr);
 tolua_variable(tolua_S,"max_interface_id",tolua_get_MonoVTable_MonoVTable_max_interface_id,tolua_set_MonoVTable_MonoVTable_max_interface_id);
 tolua_variable(tolua_S,"rank",tolua_get_MonoVTable_MonoVTable_rank,tolua_set_MonoVTable_MonoVTable_rank);
 tolua_variable(tolua_S,"imt_collisions_bitmap",tolua_get_MonoVTable_MonoVTable_imt_collisions_bitmap,tolua_set_MonoVTable_MonoVTable_imt_collisions_bitmap);
 tolua_variable(tolua_S,"runtime_generic_context",tolua_get_MonoVTable_MonoVTable_runtime_generic_context_ptr,tolua_set_MonoVTable_MonoVTable_runtime_generic_context_ptr);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoObject","MonoObject","",NULL);
 tolua_beginmodule(tolua_S,"MonoObject");
 tolua_variable(tolua_S,"vtable",tolua_get_MonoObject_MonoObject_vtable_ptr,tolua_set_MonoObject_MonoObject_vtable_ptr);
 tolua_variable(tolua_S,"synchronisation",tolua_get_MonoObject_MonoObject_synchronisation_ptr,tolua_set_MonoObject_MonoObject_synchronisation_ptr);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoString","MonoString","",NULL);
 tolua_beginmodule(tolua_S,"MonoString");
 tolua_variable(tolua_S,"object",tolua_get_MonoString_MonoString_object,tolua_set_MonoString_MonoString_object);
 tolua_variable(tolua_S,"length",tolua_get_MonoString_MonoString_length,tolua_set_MonoString_MonoString_length);
 tolua_array(tolua_S,"chars",tolua_get_lua_upgrade_MonoString_chars,tolua_set_lua_upgrade_MonoString_chars);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoArrayBounds","MonoArrayBounds","",NULL);
 tolua_beginmodule(tolua_S,"MonoArrayBounds");
 tolua_variable(tolua_S,"length",tolua_get_MonoArrayBounds_MonoArrayBounds_length,tolua_set_MonoArrayBounds_MonoArrayBounds_length);
 tolua_variable(tolua_S,"lower_bound",tolua_get_MonoArrayBounds_MonoArrayBounds_lower_bound,tolua_set_MonoArrayBounds_MonoArrayBounds_lower_bound);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoArray","MonoArray","",NULL);
 tolua_beginmodule(tolua_S,"MonoArray");
 tolua_variable(tolua_S,"obj",tolua_get_MonoArray_MonoArray_obj,tolua_set_MonoArray_MonoArray_obj);
 tolua_variable(tolua_S,"bounds",tolua_get_MonoArray_MonoArray_bounds_ptr,tolua_set_MonoArray_MonoArray_bounds_ptr);
 tolua_variable(tolua_S,"max_length",tolua_get_MonoArray_MonoArray_max_length,tolua_set_MonoArray_MonoArray_max_length);
 tolua_array(tolua_S,"vector",tolua_get_lua_upgrade_MonoArray_vector,tolua_set_lua_upgrade_MonoArray_vector);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MonoMethod","MonoMethod","",NULL);
 tolua_beginmodule(tolua_S,"MonoMethod");
 tolua_variable(tolua_S,"flags",tolua_get_MonoMethod_MonoMethod_flags,tolua_set_MonoMethod_MonoMethod_flags);
 tolua_variable(tolua_S,"iflags",tolua_get_MonoMethod_MonoMethod_iflags,tolua_set_MonoMethod_MonoMethod_iflags);
 tolua_variable(tolua_S,"token",tolua_get_MonoMethod_MonoMethod_token,tolua_set_MonoMethod_MonoMethod_token);
 tolua_variable(tolua_S,"klass",tolua_get_MonoMethod_MonoMethod_klass_ptr,tolua_set_MonoMethod_MonoMethod_klass_ptr);
 tolua_variable(tolua_S,"signature",tolua_get_MonoMethod_MonoMethod_signature_ptr,tolua_set_MonoMethod_MonoMethod_signature_ptr);
 tolua_variable(tolua_S,"name",tolua_get_MonoMethod_MonoMethod_name,NULL);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"MonoArrayData","MonoArrayData","MonoArray",tolua_collect_MonoArrayData);
#else
 tolua_cclass(tolua_S,"MonoArrayData","MonoArrayData","MonoArray",NULL);
#endif
 tolua_beginmodule(tolua_S,"MonoArrayData");
 tolua_function(tolua_S,"get",tolua_lua_upgrade_MonoArrayData_get00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"MonoClassData","MonoClassData","MonoClass",tolua_collect_MonoClassData);
#else
 tolua_cclass(tolua_S,"MonoClassData","MonoClassData","MonoClass",NULL);
#endif
 tolua_beginmodule(tolua_S,"MonoClassData");
 tolua_variable(tolua_S,"thisAddr",tolua_get_MonoClassData_MonoClassData_unsigned_thisAddr,tolua_set_MonoClassData_MonoClassData_unsigned_thisAddr);
 tolua_function(tolua_S,"show",tolua_lua_upgrade_MonoClassData_show00);
 tolua_function(tolua_S,"isValid",tolua_lua_upgrade_MonoClassData_isValid00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"MonoClassFieldData","MonoClassFieldData","MonoClassField",tolua_collect_MonoClassFieldData);
#else
 tolua_cclass(tolua_S,"MonoClassFieldData","MonoClassFieldData","MonoClassField",NULL);
#endif
 tolua_beginmodule(tolua_S,"MonoClassFieldData");
 tolua_variable(tolua_S,"thisAddr",tolua_get_MonoClassFieldData_MonoClassFieldData_unsigned_thisAddr,tolua_set_MonoClassFieldData_MonoClassFieldData_unsigned_thisAddr);
 tolua_function(tolua_S,"show",tolua_lua_upgrade_MonoClassFieldData_show00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"MonoTypeData","MonoTypeData","MonoType",tolua_collect_MonoTypeData);
#else
 tolua_cclass(tolua_S,"MonoTypeData","MonoTypeData","MonoType",NULL);
#endif
 tolua_beginmodule(tolua_S,"MonoTypeData");
 tolua_variable(tolua_S,"thisAddr",tolua_get_MonoTypeData_MonoTypeData_unsigned_thisAddr,tolua_set_MonoTypeData_MonoTypeData_unsigned_thisAddr);
 tolua_function(tolua_S,"show",tolua_lua_upgrade_MonoTypeData_show00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"MonoVTableData","MonoVTableData","MonoVTable",tolua_collect_MonoVTableData);
#else
 tolua_cclass(tolua_S,"MonoVTableData","MonoVTableData","MonoVTable",NULL);
#endif
 tolua_beginmodule(tolua_S,"MonoVTableData");
 tolua_variable(tolua_S,"thisAddr",tolua_get_MonoVTableData_MonoVTableData_unsigned_thisAddr,tolua_set_MonoVTableData_MonoVTableData_unsigned_thisAddr);
 tolua_function(tolua_S,"show",tolua_lua_upgrade_MonoVTableData_show00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"MonoMethodData","MonoMethodData","MonoMethod",tolua_collect_MonoMethodData);
#else
 tolua_cclass(tolua_S,"MonoMethodData","MonoMethodData","MonoMethod",NULL);
#endif
 tolua_beginmodule(tolua_S,"MonoMethodData");
 tolua_variable(tolua_S,"thisAddr",tolua_get_MonoMethodData_MonoMethodData_unsigned_thisAddr,tolua_set_MonoMethodData_MonoMethodData_unsigned_thisAddr);
 tolua_function(tolua_S,"show",tolua_lua_upgrade_MonoMethodData_show00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"MonoObjectData","MonoObjectData","MonoObject",tolua_collect_MonoObjectData);
#else
 tolua_cclass(tolua_S,"MonoObjectData","MonoObjectData","MonoObject",NULL);
#endif
 tolua_beginmodule(tolua_S,"MonoObjectData");
 tolua_variable(tolua_S,"thisAddr",tolua_get_MonoObjectData_MonoObjectData_unsigned_thisAddr,tolua_set_MonoObjectData_MonoObjectData_unsigned_thisAddr);
 tolua_function(tolua_S,"show",tolua_lua_upgrade_MonoObjectData_show00);
 tolua_function(tolua_S,"GetName",tolua_lua_upgrade_MonoObjectData_GetName00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"BattleManager","BattleManager","MonoObject",tolua_collect_BattleManager);
#else
 tolua_cclass(tolua_S,"BattleManager","BattleManager","MonoObject",NULL);
#endif
 tolua_beginmodule(tolua_S,"BattleManager");
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"ProcessScanner","ProcessScanner","",NULL);
 tolua_beginmodule(tolua_S,"ProcessScanner");
 tolua_function(tolua_S,"readMonoString",tolua_lua_upgrade_ProcessScanner_readMonoString00);
 tolua_function(tolua_S,"IntFromHex",tolua_lua_upgrade_ProcessScanner_IntFromHex00);
 tolua_function(tolua_S,"readMonoClassName",tolua_lua_upgrade_ProcessScanner_readMonoClassName00);
 tolua_function(tolua_S,"readCString",tolua_lua_upgrade_ProcessScanner_readCString00);
 tolua_function(tolua_S,"MonoClassScan",tolua_lua_upgrade_ProcessScanner_MonoClassScan00);
 tolua_function(tolua_S,"MonoFindClass",tolua_lua_upgrade_ProcessScanner_MonoFindClass00);
 tolua_function(tolua_S,"MonoFindVtable",tolua_lua_upgrade_ProcessScanner_MonoFindVtable00);
 tolua_function(tolua_S,"ReadInt",tolua_lua_upgrade_ProcessScanner_ReadInt00);
 tolua_function(tolua_S,"MonoFindObject",tolua_lua_upgrade_ProcessScanner_MonoFindObject00);
 tolua_function(tolua_S,"isDataAddress",tolua_lua_upgrade_ProcessScanner_isDataAddress00);
 tolua_function(tolua_S,"readMonoClass",tolua_lua_upgrade_ProcessScanner_readMonoClass00);
 tolua_function(tolua_S,"readMonoArray",tolua_lua_upgrade_ProcessScanner_readMonoArray00);
 tolua_function(tolua_S,"readMonoClassField",tolua_lua_upgrade_ProcessScanner_readMonoClassField00);
 tolua_function(tolua_S,"readMonoType",tolua_lua_upgrade_ProcessScanner_readMonoType00);
 tolua_function(tolua_S,"readMonoVTable",tolua_lua_upgrade_ProcessScanner_readMonoVTable00);
 tolua_function(tolua_S,"readMonoMethod",tolua_lua_upgrade_ProcessScanner_readMonoMethod00);
 tolua_function(tolua_S,"readMonoObject",tolua_lua_upgrade_ProcessScanner_readMonoObject00);
 tolua_function(tolua_S,"GetStaticClassFieldInt",tolua_lua_upgrade_ProcessScanner_GetStaticClassFieldInt00);
 tolua_function(tolua_S,"GetStaticClassFieldShort",tolua_lua_upgrade_ProcessScanner_GetStaticClassFieldShort00);
 tolua_function(tolua_S,"GetStaticClassFieldByte",tolua_lua_upgrade_ProcessScanner_GetStaticClassFieldByte00);
 tolua_function(tolua_S,"GetStaticClassFieldCString",tolua_lua_upgrade_ProcessScanner_GetStaticClassFieldCString00);
 tolua_function(tolua_S,"GetInstanceClassFieldInt",tolua_lua_upgrade_ProcessScanner_GetInstanceClassFieldInt00);
 tolua_function(tolua_S,"GetClassVTable",tolua_lua_upgrade_ProcessScanner_GetClassVTable00);
 tolua_endmodule(tolua_S);
 tolua_function(tolua_S,"FindCreatureByID",tolua_lua_upgrade_FindCreatureByID00);
 tolua_function(tolua_S,"FindHeroByName",tolua_lua_upgrade_FindHeroByName00);
 tolua_array(tolua_S,"monsters",tolua_get_lua_upgrade_monsters,tolua_set_lua_upgrade_monsters);
 tolua_array(tolua_S,"heros",tolua_get_lua_upgrade_heros,tolua_set_lua_upgrade_heros);
 tolua_array(tolua_S,"creatures",tolua_get_lua_upgrade_creatures,tolua_set_lua_upgrade_creatures);
 tolua_variable(tolua_S,"paramCharacterData",tolua_get_paramCharacterData,tolua_set_paramCharacterData);
 tolua_variable(tolua_S,"flgShouldUpdate",tolua_get_flgShouldUpdate,tolua_set_flgShouldUpdate);
 tolua_variable(tolua_S,"luaResultInt",tolua_get_unsigned_luaResultInt,tolua_set_unsigned_luaResultInt);
 tolua_variable(tolua_S,"luaShell",tolua_get_luaShell,tolua_set_luaShell);
 tolua_variable(tolua_S,"luaMonsterList",tolua_get_luaMonsterList,tolua_set_luaMonsterList);
 tolua_function(tolua_S,"GetBattleManager",tolua_lua_upgrade_GetBattleManager00);
 tolua_endmodule(tolua_S);
 return 1;
}
/* Open tolua function */
TOLUA_API int tolua_lua_upgrade_open (lua_State* tolua_S)
{
 lua_pushcfunction(tolua_S, luaopen_lua_upgrade);
 lua_pushstring(tolua_S, "lua_upgrade");
 lua_call(tolua_S, 1, 0);
 return 1;
}
