#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "../include/Bunny.h"
#include "../include/BunnyManager.h"
const int TURN_DURATION = 2000;
int main()
{
    BunnyManager bunnyManager;

    while (bunnyManager.BunnyCount()>0)
    {
        // system("cls") but working in terminal
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        fflush(stdout);
        //  Display all the bunnies
        std::cout << "######################################################" << std::endl;
        std::cout << "                     "<<bunnyManager.BunnyCount()<<" Bunnies" << std::endl;
        std::cout << "######################################################" << std::endl;
        bunnyManager.DisplayBunnies();

        bunnyManager.CullBunnies();

        // Age all the bunnies
        std::cout << "\n######################################################" << std::endl;
        std::cout << "                        Deaths" << std::endl;
        std::cout << "######################################################" << std::endl;
        bunnyManager.AgeAll();
        std::cout << "\n######################################################" << std::endl;
        std::cout << "                        Births" << std::endl;
        std::cout << "######################################################" << std::endl;
        bunnyManager.BirthNewBunnies();
        std::cout << "\n######################################################" << std::endl;
        std::cout << "                        Infected" << std::endl;
        std::cout << "######################################################" << std::endl;
        bunnyManager.TurnBunnyInfected();
        std::this_thread::sleep_for(std::chrono::milliseconds(TURN_DURATION));

        std::cout << std::endl;
    }

    return 0;
}
