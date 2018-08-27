/*
** Lua binding: lua_hello
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
TOLUA_API int tolua_lua_hello_open (lua_State* tolua_S);
LUALIB_API int luaopen_lua_hello (lua_State* tolua_S);

#include "hello.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* function: dumpoffset */
static int tolua_lua_hello_dumpoffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  dumpoffset();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dumpoffset'.",&tolua_err);
 return 0;
#endif
}

/* Open lib function */
LUALIB_API int luaopen_lua_hello (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_function(tolua_S,"dumpoffset",tolua_lua_hello_dumpoffset00);
 tolua_endmodule(tolua_S);
 return 1;
}
/* Open tolua function */
TOLUA_API int tolua_lua_hello_open (lua_State* tolua_S)
{
 lua_pushcfunction(tolua_S, luaopen_lua_hello);
 lua_pushstring(tolua_S, "lua_hello");
 lua_call(tolua_S, 1, 0);
 return 1;
}
