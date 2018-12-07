/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MonoEval.hpp
 * Author: kwang
 *
 * Created on August 16, 2016, 4:26 PM
 */

#ifndef MONOEVAL_HPP
#define MONOEVAL_HPP

#include "MonoHooker.hpp"
#include "../util/Mutex.hpp"
class MonoEval
{

public:
    std::vector<MonoAssembly *> vAssembly;    
    MonoEval();
    void eval(char *str);
    void GetAllAssembly();
    MonoClass * GetClassFromName(char *klassNameSpace,char *klassName);
    MonoClassField * GetFieldFromName(MonoClass *klass,char *name);
    void SetFieldBool(MonoClass *klass,MonoObject *obj,char *fieldName,bool value);
    void GetField(MonoClass *klass,MonoObject *obj,char *fieldName,bool &bValue);
    bool GetFieldAsBool(MonoClass *klass,MonoObject *obj,char *fieldName);
    void SetFieldInt(MonoClass *klass,MonoObject *obj,char *fieldName,int value);
    void GetField(MonoClass *klass,MonoObject *obj,char *fieldName,int &iValue);
    int  GetFieldAsInt(MonoClass *klass,MonoObject *obj,char *fieldName);
    void SetFieldString(MonoClass *klass,MonoObject *obj,char *fieldName,char *str);
    void GetField(MonoClass *klass,MonoObject *obj,char *fieldName,char *str);
    char *GetFieldAsString(MonoClass *klass,MonoObject *obj,char *fieldName);
    
    int GetPropertyAsInt(MonoClass *klass,MonoObject *obj,char *fieldName);
    char *GetPropertyAsString(MonoClass *klass,MonoObject *obj,char *fieldName);
    bool GetPropertyAsBool(MonoClass *klass,MonoObject *obj,char *fieldName);
    void SetProperty(MonoClass *klass,MonoObject *obj,char *fieldName,int value);
    void SetPropertyString(MonoClass *klass,MonoObject *obj,char *fieldName,char *str);
    MonoObject* IntToMonoObject(int x);
    void InvokeStatic(char *klassNameSpace,char *klassName,const char* methodName,char *param,bool flgQueue);
    void attatch();
};

class RunTimeInvokeData 
{
public:
    MonoMethod *method;
    MonoObject *obj;
    unsigned int params;
    unsigned int exec;
    RunTimeInvokeData(){
	method = NULL;
    }
};

class RunTimeInvokeQueue
{
public:
    Mutex mutex;
    std::vector<RunTimeInvokeData> vQueue;
    RunTimeInvokeQueue();
    void add(RunTimeInvokeData data);
    int size();
    RunTimeInvokeData pop();
};
extern RunTimeInvokeQueue *runTimeInvokeQueue;

#endif /* MONOEVAL_HPP */

