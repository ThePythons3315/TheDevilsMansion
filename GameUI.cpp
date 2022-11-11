#include <iostream>
#include <stdlib.h>
#include "GameUI.h"


// empty constructor
GameUI::GameUI()
{

}

// Gets input from the user
std::string GameUI::getUserInput(std::string prompt)
{
    std::string userInput;

    writeOutput(prompt);
    std::getline(std::cin, userInput);

    return userInput;
}

// Writes output to the console
int GameUI::writeOutput(std::string output)
{
    std::cout << output;

    return(0);
}