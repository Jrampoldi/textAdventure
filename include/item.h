//Program Written By: Jourdan Rampoldi//
//File: item.h                        //
////////////////////////////////////////
#include <iostream>
#include <algorithms.h>

#ifndef ITEM_H
#define ITEM_H

class Item
{
    private:
        //item attributes
        std::string name;
        std::string desc;

        bool playerHas = false;
        bool itemForPickUp = false;

        int matchKey;
        
    
    public:
        Item();

        void copyItem(Item*);
        //takes in another object to copy all 
        //attributes that copy has, as long as it 
        //is not itself.

        //setters for item class
        void setName(std::string);
        void setDesc(std::string);
        void setPlayerHas(bool);
        void setMatchKey(int);
        
        //getters for item class
        std::string getName();
        std::string getDesc();
        int getMatchKey();
        bool doesPlayerHave();


        void print();
        //function will print item information and item name
        //formatted along with the call to print an item
        //in Player class.
};

#endif