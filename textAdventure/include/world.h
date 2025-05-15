//Program Written By: Jourdan Rampoldi//
//File: world.h                       //
////////////////////////////////////////
#ifndef WORLD_H
#define WORLD_H

#include <player.h>


#include <iostream>
#include <string>

class World
{
    private:
        std::string mlocationDescription = "init";
        
        //location asset variables
        Item itemInLocation;
        NPC characterInLocation;
        bool itemHere = false;
        bool characterHere = false;
        bool enemyInLocation = false;
        
        //declare once, file variables
        std::string fileName;
        std::string fileContents;

    public:
        void setDesc(Player& p);
        //setDesc will look for a file in src/worldDesc. All files
        //will be labeled with their sector and the corresponding 
        //number. This will give the world its description of 
        //the players current location.
        //If file is not found, an exception will be thrown this
        //is not due to user error, and files must be corrected.

        void setLocationAssets(Player& p);
        //function will load assets into player current location 
        //depending on what sector the player is in. A file located
        //in src/locationInfo will be loaded and contain all of the 
        //location information.
        
        std::string getDesc();
        //getter method to return the location string to 
        //be printed.

        bool itemFound();
        //Returns itemHere which will be false
        //if item was not found in sector
        //and true if item was found.

        Item* getItemInLocation();
        //function will return item found in
        //location. If null, it will return 
        //nothin.

        void move(Player& p);
        //The move method will take the players current action 
        //request and determine if the player is running or 
        //moving locations. Will then call the direction 
        //player is attempting to move.

        void moveNorth(Player& p);
        //moveNorth method takes players current location, 
        //and compares the current sector and section to that
        //of the northern borders of Ad Astra Per Infernum

        void moveSouth(Player& p);
        //moveSouth method takes players current location, 
        //and compares the current sector and section to that
        //of the southern borders of Ad Astra Per Infernum

        void moveEast(Player& p);
        //moveEast method takes players current location, 
        //and compares the current sector and section to that
        //of the eastern borders of Ad Astra Per Infernum
        
        void moveWest(Player& p);
        //moveWest method takes players current location, 
        //and compares the current sector and section to that
        //of the western borders of Ad Astra Per Infernum

        World(); //constructor
        ~World(); //destructor
};
#endif