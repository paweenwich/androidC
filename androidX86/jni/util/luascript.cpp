#include "luascript.h"
#include "../util/logger.h"

#define debug	lua_debug

Logger *luaLogger = NULL;

void lua_debug(char *format,...)
{
    char buff[2048];
    va_list args;
    va_start(args, format);
    vsprintf(buff,format, args);
    va_end(args);
    if(luaLogger!=NULL){
	luaLogger->logStr(buff);
    }
}


/*
   Lua Glue function
*/
int l_alert(lua_State* luaVM)
{
   const char *data = lua_tostring(luaVM,-1);
   //MessageBox(0,data,"alert",MB_OK);
   printf("alert [%s]\n",data);
   lua_pushnumber(luaVM,0);
   return(0);
}


/*

   Lua Script class

*/
//LuaScript luaScript;

LuaScript::LuaScript(tolua_script_open_t openFunc,Logger *logger)
{
    if(logger == NULL){
	luaLogger = new StdOutLogger("LuaScript");
    }else{
	luaLogger = logger;
    }
    openFunction = openFunc;
    MutexCreate(&mutex);
//    lua = lua_open(1024);   //FOR VERSION 4
    lua = lua_open();

    openFunction(lua);
    // open library
    luaL_openlibs(lua);
    // register function
    registerFunctions();
}
LuaScript::~LuaScript()
{
    lua_close(lua);
}

bool LuaScript::execString(char *data)
{
    bool ret = false;
    MutexLock(&mutex);
//	EnterCriticalSection(&criticalSection);
    int error= luaL_loadbuffer(lua, data, strlen(data), "line") ||
                lua_pcall(lua, 0, 0, 0);
    if (error) {
          char tmp[1024]={0};
          sprintf(tmp, "%s", lua_tostring(lua, -1));
          lua_pop(lua, 1);  /* pop error message from the stack */
          debug("--Script Error [%s]--",data);
          debug("%s",tmp);
          debug("--end---");
          ret = false;
    }else{
	 ret = true;
    }
    MutexUnlock(&mutex);    
    return ret;

}

void LuaScript::registerFunctions()
{
   // register glue function
   lua_register(lua,"alert",l_alert);
}


void LuaScript::execFile(char *filename)
{
   FILE *fin = fopen(filename,"rb");
   if(fin==NULL){
       debug("LuaScript::addScriptFromFile file not found [%s]",filename);
       return;
   }
   fseek(fin,0,SEEK_END);
   int size = ftell(fin);
   fseek(fin,0,SEEK_SET);

    MutexLock(&mutex);   
    if(size>0){
	char *data = (char *)malloc(size+1);
	int count = 0;
	while(count < size){
	    int numread;
	    if((numread=fread(&data[count],1,size-count,fin))>0){
		count+=numread;
	    }else{
		debug("execFile error read %s %d",filename,count);
		break;
	    }
	}
	data[size] = 0;
	int error=0;
	error = luaL_loadbuffer(lua, data, strlen(data), "line") ||
		  lua_pcall(lua, 0, 0, 0);
	if (error) {
	    static char tmp[1024]={0};
	    sprintf(tmp, "%s", lua_tostring(lua, -1));
	    lua_pop(lua, 1);  /* pop error message from the stack */
	    debug("--Script Error [%s]--",filename);
	    debug("%s",tmp);
	    debug("--end---");          
	}
        free(data);
    }
    fclose(fin);
    MutexUnlock(&mutex);
}


