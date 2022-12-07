#include <iostream>
#include <stdlib.h>
#include <windows.h>
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

// Change the colors of the console and text
void GameUI::changeToBattleColors()
{
    // Get the console object
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //system("color ggf");

    // Change the color of the text to red
    SetConsoleTextAttribute(hConsole, 4);
}

// Change back to white text
void GameUI::changeToNormalColors()
{
    // Get the console object
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Change the color of the text to white
    SetConsoleTextAttribute(hConsole, 7);
}

// Change to whatever text the developer wants
void GameUI::changeColor(int color)
{
    // Get the console object
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Change the color of the text to white
    SetConsoleTextAttribute(hConsole, color);
}