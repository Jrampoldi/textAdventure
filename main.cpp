//Program Written By: Jourdan Rampoldi/
//File: main.cpp                     //
///////////////////////////////////////

#include <player.h>
#include <world.h>

#include <iostream>



void executeAction(int, Player&);
//function will recieve an action call as well as the player
//object then perform the necessary action that the player
//is requesting. 

int main()
{
    //declare and initialize main program variables
    Player player;
    std::string msgToPlayer = "What will you do: ";
    bool playerExist = false;
    bool playerExit = false;
    int actionCode;

    player.printIntro();
    playerExist = player.loadGame(); //if player exist, load player current stats;

    if (!playerExist)
        player.newPlayer(); //will create a new player with username

    while (!playerExit)
    {   //main game loop
        if (player.getHealth() == 0)
        {
            player.printGameOver();
            playerExit = true;
        }
        std::cout << msgToPlayer;
        player.updateAction(); //get player next move
        actionCode = player.getActionCallCode(); //execute action depending on type
        if (player.getCurrentAction() == "quit")
        {
            player.saveGame(); //save player object information for later use
            player.printGameOver();
            playerExit = true;
        }
        executeAction(actionCode, player);
    }
    return 0;
}

void executeAction(int callCode, Player& p)
{
    World world;
    Item item;

    switch(callCode)
    {
        case 1:
            world.move(p);
            std::cout << world.getDesc() << std::endl;
            break;
        case 2:
            if (p.isItemAvailable())
                p.itemPickUp();
            else
                std::cout << "There is nothing to grab here. " << std::endl;
            break;
        case 3:
            p.interactWithItem();
            break;
        case 4:
            if (p.characterIsHere())
                p.interactWithCharacter();
            else
                std::cout << "You hear the wind blow a little bit more and small creatures rustle in the distance...\n"
                        << "not much else though..." << std::endl;
            break;
        case 5:
            p.printInventory();
            break;
        case 6:
            p.printHelp();
            break;
        case 7:
            p.printStats();
            break;
    }
    
}