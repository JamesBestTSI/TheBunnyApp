#include <stdlib.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "../include/Bunny.h"
#include "../include/BunnyManager.h"

int main()
{
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    fflush(stdout);
    // Initialize random 
    srand(time(NULL));
    bool active = true;
    int day = 1;

    BunnyManager bunnyManager;

    while (active)
    {
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        fflush(stdout);
        std::cout << "Day " << day << std::endl;
        //  Display all the bunnies
        bunnyManager.DisplayBunnies();

        // Get User Input
        std::cout << "Press K to kill off half or any other key to continue.. ";
        char option = std::toupper(getchar());
        std::cin.ignore();
        if (option == 'K'){
            int half = bunnyManager.BunnyCount() / 2;
            for (int kill = 0; kill < half; kill++){
                bunnyManager.KillRandomBunny();
            }
        }

        // Age all the bunnies
        bunnyManager.AgeAll();

        // Make sure we have bunnies left
        (bunnyManager.BunnyCount() == 0) ? active = false : active = true;

        if (active){
            // If more than 1000, Kill half (randomly)
            if (bunnyManager.BunnyCount() > 1000){
                int half = bunnyManager.BunnyCount() / 2;
                for (int kill = 0; kill < half; kill++){
                    bunnyManager.KillRandomBunny();
                }
            };

            // Find out how many radioactive bunnies there are
            int radioactiveBunnies = bunnyManager.RadioactiveBunnies();

            // Find out how many new bunnies will be born
            int newBunniesRequired = 0;
            if (bunnyManager.ElderlyMale())
            {
                bunnyManager.BirthNewBunnies();
            }

            // Create New Bunnies
            for (int newBunny = 0; newBunny < newBunniesRequired; newBunny++)   {bunnyManager.AddBunny();}
            
            // Turn Bunnies Radioactive
            for (int newBunny = 0; newBunny < radioactiveBunnies; newBunny++)   {bunnyManager.TurnBunnyRadioactive();}
        }
        day++;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
    return 0;
}
