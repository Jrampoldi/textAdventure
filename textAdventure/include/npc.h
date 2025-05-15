//Program Written By: Jourdan Rampoldi//
//File: npc.h                         //
////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <stdlib.h>

#ifndef NPC_H
#define NPC_H

class NPC
{
    private:
        std::string name;
        std::string playerResponse;
        std::string introDialogue = "";
        std::string endDialogue = "";
        std::string talkCommands[5] = {"who", "what", "when", "where", "why"};
        std::string charResponse[5] = {"", "", "", "", ""}; //init character responses
        
        //declare once, file variables
        std::string fileName;
        std::string fileContents;
        
    public:
        NPC(); //default constructor
        void setName(std::string); //setter
        void setDialogue();
        //function will read through file using the NPC name
        //and set dialogue variables for player interaction

        std::string getName();
        //returns name of character 

        void enterConversation();
        //function will allow player to enter conversation
        //mode, interact with the character, and leave when
        //player enters command

        static int enterConflict();
        //function will enter player in conflict mode
        //where player will have a chance to escape or 
        //lose health. 
};

#endif