#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>

inline int serverPid = -1;

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
        std::cout << "[1] Demo\n";
        std::cout << "[2] Google\n";
        std::cout << "\nSelect an option: ";
        
        while (true) 
        {
            if (std::cin >> choice && (choice >= 0 && choice <= 2))
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

    inline int startServer()
    {
        system("python3 ../../TackleBox/server.py > /dev/null 2>&1 &");
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        std::ifstream pidFile("../../TackleBox/server.pid");
        if (!pidFile.is_open()) return -1;
        pidFile >> serverPid;
        pidFile.close();
    
        return serverPid;
    }
    
    inline void killServer()
    {
        if (serverPid <= 0) return;

        std::string command =
        #ifdef _WIN32
            "taskkill /F /PID " + std::to_string(serverPid);
        #else
            "kill " + std::to_string(serverPid);
        #endif

        system(command.c_str());
        std::remove("../../TackleBox/server.pid");
        serverPid = -1;
    }

    inline void openFile(const std::string& file)
    {
        if (startServer() < 0) {
            std::cerr << "Failed to start server\n";
            return;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::string url = "http://localhost:8080/" + file;
        std::string command;

        #ifdef _WIN32
        command = "start " + url;
        #elif __APPLE__
        command = "open " + url;
        #else
        command = "xdg-open " + url;
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
