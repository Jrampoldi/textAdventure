//Program Written By: Jourdan Rampoldi//
//File: npc.h                         //
////////////////////////////////////////
#include <npc.h>

NPC::NPC()
{
    //default constructor
}

void NPC::setName(std::string charName)
{
    name = charName;
}

void NPC::setDialogue()
{
    fileName = "src/charDialogue/" + name + ".txt";
    std::fstream file;
    fileContents = "init"; //initialize for while loop
    try
    {
        file.open(fileName);
        if (file.is_open())
        {
            while (true)
            {
                getline(file, fileContents);
                if (fileContents == "intro")
                {
                    getline(file, fileContents);
                    while (fileContents != "***")
                    {
                        introDialogue += "\n" + fileContents;
                        getline(file, fileContents);
                    }
                }
                if (fileContents == talkCommands[0])
                {
                    getline(file, fileContents);
                    while (fileContents != "***")
                    {
                        charResponse[0] += "\n" + fileContents;
                        getline(file, fileContents);
                    }
                }
                if (fileContents == talkCommands[1])
                {
                    getline(file, fileContents);
                    while (fileContents != "***")
                    {
                        charResponse[1] += "\n" + fileContents;
                        getline(file, fileContents);
                    }
                }
                if (fileContents == talkCommands[2])
                {
                    getline(file, fileContents);
                    while (fileContents != "***")
                    {
                        charResponse[2] += "\n" + fileContents;
                        getline(file, fileContents);
                    }
                }
                if (fileContents == talkCommands[3])
                {
                    getline(file, fileContents);
                    while (fileContents != "***")
                    {
                        charResponse[3] += "\n" + fileContents;
                        getline(file, fileContents);
                    }
                }
                if (fileContents == talkCommands[4])
                {
                    getline(file, fileContents);
                    while (fileContents != "***")
                    {
                        charResponse[4] += "\n" + fileContents;
                        getline(file, fileContents);
                    }
                }
                if (fileContents == "goodbye")
                {
                    getline(file, fileContents);
                    while (fileContents != "***")
                    {
                        endDialogue += "\n" + fileContents;
                        getline(file, fileContents);
                    }
                    break; //end of file, end while loop
                }
            }
        }
        else
            throw 13;
    }
    catch(...)
    {
        std::cout << "ERROR: FILE NOT LOCATED::LOCATION NPC::SETDIALOGUE";
    }
}

std::string NPC::getName()
{
    return name;
}

void NPC::enterConversation()
{
    setDialogue();
    bool commandFound = false;
    std::cout << introDialogue << "\n" << std::endl;
    while (true)
    {
        commandFound = false;
        std::cout << "What do you want to ask: ";
        std::cin >> playerResponse;

        for(int letter = 0; letter < playerResponse.length(); letter++)
            playerResponse[letter] = tolower(playerResponse[letter]);

        if (playerResponse == "goodbye")
            break;
        else
        {
            if (playerResponse == "hello")
                std::cout << "Yes... you said that already...";
            for (int response = 0; response < 5; response++)
            {
                if (playerResponse == talkCommands[response])
                {
                    commandFound = true;
                    std::cout << charResponse[response] << "\n" << std::endl;
                }
            }
            if (!commandFound)
            {
                std::cout << "err... Im not sure that is a question I know...\nYou should ask me who, what, when, where, or why..." << std::endl;
            }
        }
    }
}

int NPC::enterConflict()
{

    std::cout << "A creature approaches in front of you... Seems aggressive." << std::endl;
    std::cout << "Little is known about these creatures. What is known is that you have a 50 percent chance of escape." << std::endl;
    std::cout << "Press enter to see how lucky you are, adventurer: ";
    std::cin.ignore(); // clear stream
    std::cin.get(); //allow player to press enter

    srand(time(0));//set random seed 
    int odds = (rand() % 2);

    if (odds == 1)
    {
        std::cout << "The creature strikes at you." << std::endl;
        std::cout << "Down you fall." << std::endl;
        std::cout << "Lights turn to black." << std::endl;
        std::cout << "You recieve damage." << std::endl;
        std::cout << "When you awake, the creature is gone. You can only assume it will be back. Best not to be here when it does." << std::endl;
    }
    else
    {
        std::cout << "The creature strikes at you." << std::endl;
        std::cout << "You are quick and jump out of the way." << std::endl;
        std::cout << "The creature bounds back while you get up." << std::endl;
        std::cout << "With one swift kick, you strike at the last second." << std::endl;
        std::cout << "The creature runs and you take no damage." << std::endl;
        std::cout << "You can only assume it will be back. Best not to be here when it does." << std::endl;
    }

    return odds;

}