//Program Written By: Jourdan Rampoldi//
//File: player.h                      //
////////////////////////////////////////
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <algorithms.h>
#include <npc.h>



class Player
{ //class for player of game
    
    public:
        //getters
        std::string getCurrentAction();
        std::string getUserName();
        int getHealth();  
        int getSector();
        int getSection();
        std::string getBlock(int);
        bool isItemAvailable();
        bool characterIsHere();
        std::string getUnlockDirection();
        int getLockKey();
        
        // setters
        void setHealth(int);
        void setSector(int);
        void setSection(int);
        void setBlock(std::string, int);
        void setCharacterInteraction(NPC*); //sets up possible player interaction
        void setUnlock(std::string);
        void setKey(int);

        //player game interactions
        int getActionCallCode();
        //getActionCallCode method will return an integer that will 
        //get passed for execution of action. This method will take the current
        //action and determine which call code to pass.

        void updateAction();
        //updateAction method will take user action and assign it with 
        //currentAction attribute. This will go through a loop process, transforming 
        //user input to lowercase, then pass through a comparison which will 
        //compare each individual action in ACTION_LIST. If not found, exception thrown,
        //and user must reenter a command.

        void removeBlock();
        //will loop through block and remove direction specified 
        //by gate.

        void storeItem(Item&);
        //function will store item found in location
        //for player pick up. 

        void sortItems(int length);
        //calls on algorithms to use a quicksort with Item
        //class adjustment to sort player item inventory 
        //array.

        int searchItems(std::string);
        //will take string and check for item 
        //existence within our inventory.

        void itemPickUp();
        //function will store item in player
        //inventory if player chooses to grab item.

        void clearItemStorage();
        //if player leaves location, item storage 
        //will be cleared. Player will not be 
        //able to grab items

        void clearCharacter();
        //if player moves to a section where character
        //is not located, player will not be able to 
        //interact with character. 
        //PostCondition: characterWithinRange = nullptr

        void interactWithCharacter();
        //function will initiate the interaction with the 
        //NPC, allowing user to enter conversation mode

        void interactWithItem();
        //will take item expressed by player and check if in inventory.
        //function will also check if there is a gate and if so, if the
        //item expressed will work with gate using the matchKey.

        bool loadGame();
        //loadGame method gets called from the main.cpp program, which will 
        //look through files, searching for user, by username. If file not found,
        //user will start a new game.

        void saveGame();
        //saveGame will turn each important attribute of player object,
        //into savable data, then will save it to file named after,
        //player username. Gets called from main menu upon player exit.

        void newPlayer();
        //assigns username to new player

        void printInventory();
        //function will print the currrent inventory of
        //player, using the print function in the Item class

        void printIntro();
        //the printIntro method will strictly print out a 
        //predefined introduction to the game located in images/. 
        //It will be played each start of the game.
        
        void printGameOver();
        //the printGameOver method will print out predefined end 
        //game text, located in images/ directory. File will print
        //contents upon player exit.

        void printHelp();
        //will print all commands and descriptions of commands to
        //console 

        void printStats();
        //will print the health and location of player. 

        Player();
        ~Player();

    private:
        std::string mUserName;
        std::string currentAction = "";

        //restrict player movement block
        std::string movementBlocks[4];
        std::string gate;
        int key;

        int mHealth = 10;
        int mLocation[2] = {12, 2};

        //item involvment var
        std::string itemInHand;
        int numberOfItems = 0;
        Item* inventory[25];
        Item* itemStorage;
        
        //character involvment var
        NPC* characterWithinRange = new NPC();

        //array of possible player actions
        std::string ACTION_LIST[8] = {"quit", "move", "grab", "use", "hello", "inventory", "help", "stats"};

        //declare once, file search vars
        std::string fileIdentification;
        std::string fileContents;
        std::string locateFileName;
        
};
#endif