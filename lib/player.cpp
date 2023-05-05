//Program Written By: Jourdan Rampoldi//
//File: player.cpp                    //
////////////////////////////////////////
#include <player.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>

Player::Player(){mHealth = 10;};
Player::~Player(){};

int Player::getSector()
{
    return mLocation[0];
}
int Player::getSection()
{
    return mLocation[1];
}

std::string Player::getUnlockDirection()
{
    return gate;
}

int Player::getLockKey()
{
    return key;
}

int Player::getHealth()
{
    return mHealth;
}

void Player::setSector(int nSector)
{
    mLocation[0] = nSector;
}
void Player::setSection(int nSection)
{
    mLocation[1] = nSection;
}
void Player::setBlock(std::string direction, int index)
{
    movementBlocks[index] = direction;
}

void Player::setHealth(int newHealth)
{
    mHealth = newHealth;
}

void Player::setKey(int keyValue)
{
    key = keyValue;
}

void Player::setUnlock(std::string direction)
{
    gate = direction;
}

void Player::setCharacterInteraction(NPC* characterHere)
{
    characterWithinRange = new NPC();
    characterWithinRange->setName(characterHere->getName());
}

void Player::interactWithCharacter()
{
    characterWithinRange->enterConversation();
}

void Player::updateAction()
{    //declare and initialize pointer boolean for finding action in action array
    bool* actionFound = new bool(false);

    try
    {

        std::cin >> currentAction;
        for(int letter = 0; letter < currentAction.length(); letter++)
            currentAction[letter] = tolower(currentAction[letter]);
        for (int action = 0; action < (sizeof(ACTION_LIST) / sizeof(*ACTION_LIST)); action++)
        {
            if (currentAction == ACTION_LIST[action])
                *actionFound = true;

        }
        if (!*actionFound)
        {
            delete actionFound; //deallocate memory used
            throw 13; //error message for action not found
        }
    }
    catch (...)
    {
        while (!*actionFound)
        {
            std::cout << mUserName << ", you must enter a defined action.\n" << "What will you do: ";
            std::cin >> currentAction;
            for(int letter = 0; letter < currentAction.length(); letter++)
                currentAction[letter] = tolower(currentAction[letter]);
            for (int action = 0; action < (sizeof(ACTION_LIST) / sizeof(*ACTION_LIST)); action++)
            {
                if (currentAction == ACTION_LIST[action])
                    *actionFound = true;
            }
        }
    }
}

void Player::storeItem(Item& otherItem)
{
    itemStorage = new Item();
    
    itemStorage->setName(otherItem.getName());
    itemStorage->setDesc(otherItem.getDesc());
    itemStorage->setMatchKey(otherItem.getMatchKey());


}

void Player::itemPickUp()
{
    for (int item = 0; item < 25; item++)
    {
        if (inventory[item] == nullptr && itemStorage != nullptr)
        {
            inventory[item] = new Item();
            inventory[item]->copyItem(itemStorage);
            sortItems(item);
            break;
        }
    }
    numberOfItems++;
    std::cout << "You have picked up: " << itemStorage->getName() << std::endl;
}

void Player::clearItemStorage()
{
    itemStorage = nullptr;
}

void Player::clearCharacter()
{
    characterWithinRange = nullptr;
}

int Player::getActionCallCode()
{
    for (int index = 0; index < (sizeof(ACTION_LIST) / sizeof(*ACTION_LIST)); index++)
    {
        if (currentAction == ACTION_LIST[index])
            return index;
    }
    return 13;
}

void Player::removeBlock()
{
    for (int direction = 0; direction < 4; direction++)
    {

        if (movementBlocks[direction] == gate)
        {
            movementBlocks[direction] = " ";
        }
    }

    std::cout << "Path is opened..." << std::endl;
}

void Player::interactWithItem()
{
    std::cout << "What is the item name: ";
    std::getline(std::cin >> std::ws, itemInHand);

    if (searchItems(itemInHand) == key)
    {
        removeBlock();
    }
    else
        std::cout << "Hmm... Nothing happened." << std::endl;


}

bool Player::isItemAvailable()
{
    if (itemStorage != nullptr)
        return true;
    return false;
}

bool Player::characterIsHere()
{
    if (characterWithinRange != nullptr)
        return true;
    return false;
}

std::string Player::getCurrentAction()
{
    return currentAction;
}

std::string Player::getBlock(int index)
{
    return movementBlocks[index];
}

bool Player::loadGame()
{
    bool fileExist = false;
    std::cout << "Please enter your username: ";
    std::cin >> locateFileName;

    std::cout << "Attempting to open file..." << std::endl;

    fileIdentification = "data/playerSave/" + locateFileName + ".txt";


    std::fstream file;
    file.open(fileIdentification, std::ios::in);
    
    //ensure file is open
    if (file.is_open()) 
    {
        
        
        std::string* healthAsString = new std::string();
        std::string* sectorString = new std::string();
        std::string* sectionString = new std::string();
        std::string* numberItemsString = new std::string();
        std::string* keyVal = new std::string();
        std::string* itemKeyVal = new std::string();
        std::string* itemName = new std::string();
        std::string* itemDesc = new std::string();
        int* intTempVal = new int();
        
        //save important data
        getline(file, mUserName);
        getline(file, *healthAsString);
        getline(file, *sectorString);
        getline(file, *sectionString);
        for (int direction = 0; direction < 4; direction++)
            getline(file, movementBlocks[direction]);
        getline(file, gate);
        getline(file, *keyVal);
        getline(file, *numberItemsString);

        std::istringstream(*healthAsString) >> mHealth;
        std::istringstream(*sectorString) >> mLocation[0];
        std::istringstream(*sectionString) >> mLocation[1];
        std::istringstream(*keyVal) >> key;
        std::istringstream(*numberItemsString) >> numberOfItems;

        for (int item = 0; item < numberOfItems; item++)
        {
            inventory[item] = new Item();
            getline(file, *itemName);
            getline(file, *itemDesc);
            getline(file, *itemKeyVal);

            inventory[item]->setName(*itemName);
            inventory[item]->setDesc(*itemDesc);

            std::istringstream(*itemKeyVal) >> *intTempVal;

            inventory[item]->setMatchKey(*intTempVal);
        }

        //deallocate memory space
        delete healthAsString;
        delete sectorString;
        delete sectionString;
        delete numberItemsString;
        delete keyVal;
        delete itemKeyVal;
        delete itemName;
        delete itemDesc;
        delete intTempVal;

        fileExist = true;
        
    }

    else
    {
        std::cout << "File not found... Loading new game." << std::endl;
    }

    file.close(); //close file 


    return fileExist;
}

void Player::saveGame()
{
    //saveGame() will open/create file for user to hold important game data for reload
    fileIdentification = "data/playerSave/" + mUserName + ".txt";

    std::fstream file;
    file.open(fileIdentification, std::ios::out);
    
    //ensure file is open
    if (file.is_open()) 
    {
        //save important data
        file << mUserName << std::endl;
        file << std::to_string(mHealth) << std::endl;
        file << std::to_string(mLocation[0]) << std::endl;
        file << std::to_string(mLocation[1]) << std::endl;
        for (int direction = 0; direction < 4; direction++)
            file << movementBlocks[direction] << std::endl;
        file << gate << std::endl;
        file << key << std::endl;
        file << numberOfItems << std::endl;
        for (int item = 0; item < numberOfItems; item++)
        {
            file << inventory[item]->getName() << std::endl;
            file << inventory[item]->getDesc() << std::endl;
            file << inventory[item]->getMatchKey() << std::endl;
        }

    }
    file.close(); //close file 


    std::cout << "Game saved..." << std::endl; //msg to user notifying successful save
}

void Player::newPlayer()
{
    std::cout << "Enter a username you would like to use, adventurer: ";
    std::cin >> mUserName;
}

void Player::printInventory()
{
    std::cout << "Item\t\tDescription" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "\n";
    for (int item = 0; item < 25; item++)
    {
        if (inventory[item] == nullptr)
            break;
        else
            inventory[item]->print();
    }
}

void Player::printIntro()
{
    std::fstream file;
    file.open("images/startGame.txt");
    if (file.is_open())
    {
        while (file)
        {
            getline(file, fileContents);
            if (fileContents == "")
                break;
            std::cout << fileContents << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR: FILE NOT FOUND." << std::endl;
    }
    file.close();
}

void Player::printGameOver()
{
    std::fstream file;
    file.open("images/gameover.txt");
    if (file.is_open())
    {
        while (file)
        {
            getline(file, fileContents);
            if (fileContents == "")
                break;
            std::cout << fileContents << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR: FILE NOT FOUND." << std::endl;
    }
    file.close();
}

void Player::printHelp()
{
    std::cout << "Here are the commands you can use: " << std::endl;
    std::cout << "\n";
    std::cout << "\tmove *direction*\tMove allows you to traverse the world in the direction\n"
            << "\t\t\t\tof North, South, East, or West" << std::endl;
    std::cout << "\n";
    std::cout << "\tgrab\t\t\tGrab allows you to put an item that is in the same location\n"
            << "\t\t\t\tas you into your inventory." << std::endl;
    std::cout << "\n";
    std::cout << "\tuse\t\t\tUse allows you to interact with other objects of this\n"
            << "\t\t\t\tworld. A gate for example and a key in your inventory." << std::endl;
    std::cout << "\n";
    std::cout << "\thello\t\t\thello will allow you to speak to characters in the ad astra\n"
            << "\t\t\t\tper infernum world. goodbye is how you exit conversations." << std::endl;
    std::cout << "\n";
    std::cout << "\tinventory\t\tinventory will show you what you have currently in inventory."
            << std::endl;
    std::cout << "\tstats\t\tstats will show you your health and current location" << std::endl;
    std::cout << "\n";
}

void Player::printStats()
{
    std::cout << "\nHealth: " << mHealth << std::endl;
    std::cout << "Sector: " << mLocation[0] + 1 << std::endl;
    std::cout << "Section: " << mLocation[1] + 1 << std::endl;
    std::cout << "\n" << std::endl;
}

void Player::sortItems(int length)
{
    Algorithms::quickSort(inventory, length);
}

int Player::searchItems(std::string item)
{
    int length = 0;
    for (int i = 0; i < 25; i++)
    {
        if (inventory[i] == nullptr)
        {
            length = i;
            break;
        }
    }

    return Algorithms::binarySearch(inventory, length, item);
}