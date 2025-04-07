#ifndef PHISHBAIT_H
#define PHISHBAIT_H

#include <iostream>
#include <cstdlib>
#include <string>

namespace PhishBait
{
    extern const std::string phishBaitVersion;

    int homeDisplay(int& choice)
    {
        std::cout << " ___ _    _    _    ___       _ _\n";
        std::cout << "| _ \\ |_ (_)__| |_ | _ ) __ _(_) |_\n";
        std::cout << "|  _/ ' \\| (_-< ' \\| _ \\/ _` | |  _|\n";
        std::cout << "|_| |_||_|_|__/_||_|___/\\__,_|_|\\__|  " <<  phishBaitVersion << "\n\n\n";
        std::cout << "[0] Quit\n";
        std::cout << "[1] Open Demo\n";
        std::cout << "\nSelect an option: ";
        
        while (true) 
        {
            if (std::cin >> choice && (choice == 0 || choice == 1))
            {
                break;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Not an option, try again: ";
            }
        }
        
        return choice;
    }

    void openFile(const std::string& file)
    {
        std::string command;
        
        #ifdef __APPLE__
        command = "open " + file;
        #elif _WIN32
        command = "start " + file;
        #else
        command = "xdg-open " + file;
        #endif
        
        system(command.c_str());
    }

    void clearTerminal()
    {
        #ifdef _WIN32
        system("cls");
        #elif __APPLE__
        system("clear && printf '\e[3J'");
        #else
        system("clear");
        #endif
    }
}

#endif