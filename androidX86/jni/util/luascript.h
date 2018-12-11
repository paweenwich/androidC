#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "..\tolua\tolua.h"
#include "..\luac\lualib.h"

#ifdef __cplusplus
}
#endif

#include "..\util\Mutex.hpp"
#include "..\util\logger.h"

#define lua_open()  luaL_newstate()

typedef int (*tolua_script_open_t)(lua_State* tolua_S);
typedef int (*tolua_script_close_t)(lua_State* tolua_S);

//extern Logger *luaLogger;
class LuaScript {
protected:
   void registerFunctions();
public:
   Mutex mutex;
   lua_State *lua ;
   tolua_script_open_t openFunction;
   Logger *luaLogger;
   LuaScript(tolua_script_open_t openFunc,Logger *logger=NULL);
   ~LuaScript();

   bool execString(char *);
   void execFile(char *filename);

   virtual void beforeExec() {
   };

};

#endif
