/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BaseCommandService.h
 * Author: Administrator
 *
 * Created on December 5, 2018, 10:42 AM
 */

#ifndef BASECOMMANDSERVICE_H
#define BASECOMMANDSERVICE_H

#define BSC_OK      "OK"
#define BSC_HELP    "HELP"          //HELP
#define BSC_DUMPMEM    "DUMPMEM"    // DUMPMEM addr size

class BaseCommandService {
public:
    BaseCommandService();
    BaseCommandService(const BaseCommandService& orig);
    virtual void doLine(SimpleSocket &sock,char *);
    virtual void help(SimpleSocket &sock);
    virtual ~BaseCommandService();
private:

};

#endif /* BASECOMMANDSERVICE_H */

