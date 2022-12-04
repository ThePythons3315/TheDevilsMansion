#include <iostream>
#include <stdlib.h>
#include "GameUI.h"

GameUI::GameUI()
{
    // null constructor
}

// Gets input from the user
std::string GameUI::getUserInput(std::string prompt)
{
    std::string userInput;

    writeOutput(prompt);
    std::getline(std::cin, userInput);

    std::cout << std::endl;

    return userInput;
}

// Writes output to the console
int GameUI::writeOutput(std::string output)
{
    std::cout << output;

    return(0);
}