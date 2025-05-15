//Program Written By: Jourdan Rampoldi//
//File: item.cpp                      //
////////////////////////////////////////
#include <item.h>


Item::Item()
{
    name = "";
    desc = "";
    matchKey = 13;
};
void Item::setName(std::string itemName)
{
    name = itemName;
}

void Item::setDesc(std::string description)
{
    desc = description;
}

void Item::setPlayerHas(bool value)
{
    playerHas = value;
}


void Item::setMatchKey(int keyValue)
{
    matchKey = keyValue;
}


std::string Item::getName()
{
    return name;
}

std::string Item::getDesc()
{
    return desc;
}

int Item::getMatchKey()
{
    return matchKey;
}


bool Item::doesPlayerHave()
{
    return playerHas;
}


void Item::print()
{
    std::cout << name << "\t";
    if (desc.length() > 20)
    {
        for (int letter = 0; letter < 28; letter++)
            std::cout << desc[letter];
        std::cout << "\n\t\t";
        for (int letter = 28; letter < desc.length(); letter++)
            std::cout << desc[letter];
        std::cout << "\n";
    }
    else
        std::cout << desc << std::endl;
}

void Item::copyItem(Item* otherItem)
{
    if (this != otherItem)
    {
        name = otherItem->name;
        desc = otherItem->desc;
        matchKey = otherItem->matchKey;
    }
}