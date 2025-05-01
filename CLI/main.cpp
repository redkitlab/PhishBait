#include <iostream>

#include "phishbait.h"

using namespace PhishBait;

const std::string PhishBait::phishBaitVersion = "v0.0.0";

int main()
{
    clearTerminal();
    while(true)
    {
        int choice;
        clearTerminal();
        homeDisplay(choice);
        switch(choice)
        {
            case 0:
                killServer();
                clearTerminal();
                return 0;
            case 1:
                openFile("Demo/demo.html");
                break;
            case 2:
                openFile("Google/googlebait.html");
                break;
        }
    }
    return 0;
}