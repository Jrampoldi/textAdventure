//Program Written By: Jourdan Rampoldi//
//File: world.cpp                     //
////////////////////////////////////////
#include <world.h>


#include <fstream>
#include <sstream>
#include <iostream>
#include <string>



void World::setDesc(Player& p)
{ //class method takes in player class object and will use object to gain information about file name structure
    std::string  fileName;
    std::string fileContents;
    fileName = "src/worldDesc/sector" + std::to_string(p.getSector() + 1) + ".txt";
    std::ifstream file;
    try
    {
        file.open(fileName, std::ios::in);
        
        if (file.is_open())
        {
            for (int i = 0; i <= p.getSection(); i++)
            {
                getline(file, fileContents);
            }
            mlocationDescription = fileContents;

        }
        else
            throw 13;
        
        file.close();
    }
    catch(...)
    {
        std::cout << "file does not exist, ERRORLOC:WORLD::SETDESC in file WORLD.CPP" << std::endl;
    }

}

std::string World::getDesc()
{ //returns location string
    return mlocationDescription;
}

void World::move(Player& p)
{
    //determine action of player movement

    std::string direction;

    p.clearItemStorage();
    p.clearCharacter();

    try
    {
        std::cin >> direction;

        //edit user input to all lowercase
        for (int ch = 0; ch < direction.length(); ch++)
            direction[ch] = tolower(direction[ch]);

        if (direction == "north")
        {
            moveNorth(p);
            this->setDesc(p);
        }
        else if (direction == "south")
        {
            moveSouth(p);
            this->setDesc(p);
        }
        else if (direction == "east")
        {
            moveEast(p);
            this->setDesc(p);
        }
        else if (direction == "west")
        {
            moveWest(p);
            this->setDesc(p);

        }
        else
        {
            throw 13;
        }
        
    }
    catch(...)
    {
        while (true)
        {
            std::cout << "hmm... maybe you should pick a direction: ";
            std::cin >> direction;

            //edit user input to all lowercase
            for (int ch = 0; ch < direction.length(); ch++)
            {
                direction[ch] = tolower(direction[ch]);
            }
            if (direction == "north" || direction == "south" || direction == "east" || direction == "west")
                break;
        }
        if (direction == "north")
        {
            moveNorth(p);
            this->setDesc(p);
        }
        else if (direction == "south")
        {
            moveSouth(p);
            this->setDesc(p);
        }
        else if (direction == "east")
        {
            moveEast(p);
            this->setDesc(p);
        }
        else if (direction == "west")
        {
            moveWest(p);
            this->setDesc(p);
        }
    }
    if (itemHere)
        p.storeItem(itemInLocation);

    if (characterHere)
        p.setCharacterInteraction(&characterInLocation);
 
    if (enemyInLocation)
    {
        p.setHealth(p.getHealth() - NPC::enterConflict());
        std::cout << "Health: " << p.getHealth() << std::endl;
    }
}
void World::moveNorth(Player& p)
{ //if player can move north, according to locationindex
    try
    {
        for (int index = 0; index < 4; index++)
        {
            if (p.getBlock(index) == "north")
            {
                throw 13;
            }
        }
        if (p.getSector() < 5)
        {
            if (p.getSection() < 2)
            {
                throw 13;
            }
            else
            {
                if (p.getSection() == 2)
                    p.setSection(0);
                else
                    p.setSection(1);
            }
        }
        else
        {
            switch(p.getSection())
            {
                case 0:
                    p.setSector(p.getSector() - 5);
                    p.setSection(2);
                    break;
                case 1:
                    p.setSector(p.getSector() - 5);
                    p.setSection(3);
                    break;
                case 2:
                    p.setSection(0);
                    break;
                case 3:
                    p.setSection(1);
                    break;
            }
        }
        setLocationAssets(p);

    }
	catch(int x)
    {
        std::cout << "Hmm... You cant seem to move north anymore..." << std::endl;
    }
}
void World::moveSouth(Player& p)
{   //if player can move south, according to locationindex
    try
    {
        for (int index = 0; index < 4; index++)
        {
          if (p.getBlock(index) == "south")
              throw 13;
        }
        if (p.getSector() > 30)
        {
            if (p.getSection() > 1)
            {
                throw 13;
            }
            else
            {
                if (p.getSection() == 2)
                    p.setSection(0);
                else
                    p.setSection(1);
            }
        }
        else
        {
            switch(p.getSection())
            {
                case 0:
                    p.setSection(2);
                    break;
                case 1:
                    p.setSection(3);
                    break;
                case 2:
                    p.setSector(p.getSector() + 5);
                    p.setSection(0);
                    break;
                case 3:
                    p.setSector(p.getSector() + 5);
                    p.setSection(1);
                    break;
            }
        }
    }
		catch(int x)
		{
			std::cout << "hmm... you can't seem to move south anymore." << std::endl;
		}
    setLocationAssets(p);
}
void World::moveEast(Player& p)
{ //if player can move south, according to locationindex
    try
    {
        for (int index = 0; index < 4; index++)
        {
            if (p.getBlock(index) == "east")
                throw 13;
        }
        if (p.getSector() == 0 || p.getSector() % 5 == 0)
        {
            if (p.getSection() == 0 || p.getSection() == 2)
                p.setSection(p.getSection() + 1);
            else
                throw 13;
        }
        else
        {
            switch(p.getSection())
            {
                case 0:
                    p.setSection(1);
                    break;
                case 1:
                    p.setSector(p.getSector() + 1);
                    p.setSection(0);
                    break;
                case 2:
                    p.setSection(3);
                    break;
                case 3:
                    p.setSector(p.getSector() + 1);
                    p.setSection(2);
                    break;
            }
        }
    }
    catch(int x)
    {
        std::cout << "hmm... you can't seem to move east anymore." << std::endl;
    }
    setLocationAssets(p);
}
void World::moveWest(Player& p)
{
    try
    {
        for (int index = 0; index < 4; index++)
        {
            if (p.getBlock(index) == "west")
                throw 13;
        }
        if ((p.getSector() + 1) % 5 == 0)
        {
            if (p.getSection() == 1 || p.getSection() == 3)
                p.setSection(p.getSection() - 1);
            else
                throw 13;
        }
        else
        {
            switch(p.getSection())
            {
                case 0:
                    p.setSector(p.getSector() - 1);
                    p.setSection(1);
                    break;
                case 1:
                    p.setSection(0);
                    break;
                case 2:
                    p.setSector(p.getSector() - 1);
                    p.setSection(3);
                    break;
                case 3:
                    p.setSection(2);
                    break;
            }
        }
    }
    catch(int x)
    {
        std::cout << "hmm... you can't seem to move west anymore." << std::endl;
    }
    setLocationAssets(p);
}

void World::setLocationAssets(Player& p)
{

    std::string  fileName;
    std::string fileContents;
    int intValue = 0;
    fileName = "src/locationInfo/sector" + std::to_string(p.getSector() + 1) + ".txt";
    std::ifstream file;

    try
    {
        file.open(fileName, std::ios::in);
        if (file.is_open())
        {
            while(!file.eof())
            {
                getline(file, fileContents);
                if (fileContents == std::to_string(p.getSection() + 1))
                {
                    bool doneReadingLocation = false;
                    getline(file, fileContents);
                    while (!doneReadingLocation)
                    {
                        if (fileContents == "movementBlock")
                        {
                            //following three lines clears variables
                            for (int index = 0; index < 4; index++)
                                p.setBlock("", index);
                            p.setUnlock("");
                            getline(file, fileContents);
                            int index = 0;
                            while (fileContents != "***")
                            {
                                if (fileContents == "gate")
                                {
                                    getline(file, fileContents);
                                    p.setBlock(fileContents, index);
                                    p.setUnlock(fileContents);
                                    getline(file, fileContents);
                                    std::istringstream(fileContents) >> intValue;
                                    p.setKey(intValue);
                                }
                                else
                                    p.setBlock(fileContents, index);
                                index++;
                                getline(file, fileContents);
                            }
                            getline(file, fileContents); // skip symbol ***
                        }
                        if (fileContents == "itemLocation")
                        {
                            itemHere = true;


                            getline(file, fileContents);
                            itemInLocation.setName(fileContents);

                            getline(file, fileContents);
                            itemInLocation.setDesc(fileContents);
                            
                            getline(file, fileContents);
                            std::istringstream(fileContents) >> intValue;
                            itemInLocation.setMatchKey(intValue);

                            getline(file, fileContents);
                            //clear following seperation symbol "***"
                        }
                        if (fileContents == "characterInteraction")
                        {
                            characterHere = true;
                            getline(file, fileContents);
                            characterInLocation.setName(fileContents);

                            getline(file, fileContents);
                            //clear following seperation symbol "***"
                        }
                        if (fileContents == "enemyInteraction")
                        {
                            enemyInLocation = true;
                            getline(file, fileContents);
                            //clear following seperation symbol
                        }
                        if (fileContents != "movementBlock" || fileContents != "itemLocation" || fileContents != "characterInteraction" || fileContents != "enemyInteraction")
                        {
                            doneReadingLocation = true;
                        }
                    }        
                    
                }
            }
        }
        else
            throw 13;
        
        file.close();
    }
    catch(...)
    {
        std::cout << "file does not exist, ERRORLOC:WORLD::SETLOCATIONASSETS in file WORLD.CPP" << std::endl;
    }
}

Item* World::getItemInLocation()
{
        return &itemInLocation;
}

bool World::itemFound()
{
    return itemHere;
}

World::World()
{

}

World::~World()
{

}