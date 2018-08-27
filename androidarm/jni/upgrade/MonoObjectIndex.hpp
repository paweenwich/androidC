/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MonoObjectIndex.hpp
 * Author: kwang
 *
 * Created on September 2, 2016, 8:37 AM
 */

#ifndef MONOOBJECTINDEX_HPP
#define MONOOBJECTINDEX_HPP

struct CharacterDataIndex {
    unsigned int creatureId;
    unsigned int addr;
};

class CharacterDataIndexManager {
public:
    int pid;
    std::vector<CharacterDataIndex> index;
    void load(int pid);
    void save();
    unsigned int get(int creatureID);
    void put(int creatureID,unsigned int addr);
};


#endif /* MONOOBJECTINDEX_HPP */

