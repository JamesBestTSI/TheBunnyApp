#include "../include/BunnyManager.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <limits>

BunnyManager::BunnyManager(){
    AddBunny();
    AddBunny();
    AddBunny();
    AddBunny();
    AddBunny();
};

BunnyManager::~BunnyManager(){};

void BunnyManager::AddBunny()
{
    std::shared_ptr<Bunny> bun(new Bunny());
    DisplayBunnyBirth(*bun);
    bunnies.push_back(std::move(bun));
    gridManager.AddBunnyToGrid(bunnies.back());
};

/**
 * @brief Ages up all the bunnies by one year, and tracks if we have a healthy mature male who can breed,
 * also keeps track of all the mothers that can breed so we know what new bunnies we will have to create.
 */
void BunnyManager::UpdateAll()
{
    infectedCount = 0;
    matureMale = false;
    mothers.clear();
    infected.clear();
    std::list<std::shared_ptr<Bunny>>::iterator bunny = bunnies.begin();
    while (bunny != bunnies.end()){
        // Test to see if the bunny should die of old age
        if ((*bunny)->GetAge() > MAX_HEALTHY_AGE && !(*bunny)->GetInfected() || (*bunny)->GetAge() > MAX_INFECTED_AGE){
            // Death
            DisplayBunnyDeath(*(*bunny));
            gridManager.RemoveBunnyFromGrid((*bunny)->GetLocation());
            bunnies.erase(bunny++);
        }
        // If the bunny did not die of old age
        else{
            if ((*bunny)->GetInfected())    { infectedCount++; infected.push_back((*bunny));}
            else if ((*bunny)->GetAge() >= BREEDING_AGE){
                switch ((*bunny)->GetSex()) {
                    case Gender::Female:    { mothers.push_back((*bunny));  break;}
                    case Gender::Male:      { matureMale = true;            break;}
                }
            }
            (*bunny)->GrowUp();

            // Move bunny
            std::vector<std::shared_ptr<GridSpace>> availableSpaces = gridManager.GetEmptyConnectingGridSpaces((*bunny)->GetLocation());
            if (availableSpaces.size()>0){
                int bunnyLocation = (*bunny)->GetLocation();
                gridManager.RemoveBunnyFromGrid((*bunny)->GetLocation());                
                std::shared_ptr<GridSpace> space = availableSpaces[rand() % availableSpaces.size()];
                space->AddBunnyToSpace((*bunny));
            }
            ++bunny;
        }
    }
};

/**
 * @brief Creates new bunnies based on the mothers colours 
 */
void BunnyManager::BirthNewBunnies(){
    if (matureMale){
        for (std::list<std::shared_ptr<Bunny>>::iterator mother = mothers.begin(); mother != mothers.end(); ++mother) {
            std::vector<std::shared_ptr<GridSpace>> availableSpaces = gridManager.GetEmptyConnectingGridSpaces((*mother)->GetLocation());
            if (availableSpaces.size() > 0)
            {
                std::shared_ptr<Bunny> babyBunny(new Bunny((*mother)->GetColour()));
                DisplayBunnyBirth(*babyBunny);
                bunnies.push_back(std::move(babyBunny));
                std::shared_ptr<GridSpace> space = availableSpaces[rand() % availableSpaces.size()];
                space->AddBunnyToSpace(bunnies.back());
            }
        }
    }
    mothers.clear();
};

/**
 * @brief Turns some bunnies infected based on how many are currently infected
 */
void BunnyManager::TurnBunnyInfected(){
    for (std::list<std::shared_ptr<Bunny>>::iterator Infected = infected.begin(); Infected != infected.end(); ++Infected)
    {
        std::vector<std::shared_ptr<GridSpace>> spacesWithBunnies = gridManager.GetUsedConnectingGridSpaces((*Infected)->GetLocation());
        if (spacesWithBunnies.size() > 0)
        {
            std::shared_ptr<Bunny> bun = spacesWithBunnies[rand() % spacesWithBunnies.size()]->GetBunnyFromSpace();
            bun->Infect();
            DisplayBunnyTurned(*bun);
        }
    }

    /*
    int healthybunnies = bunnies.size()- infectedCount;
    int healthyoffset = healthybunnies / (infectedCount + 1);
    if (healthyoffset <= 0){healthyoffset = 0;}

    int currentOffset = 0;
    int infected = 0;
    for (std::list<std::shared_ptr<Bunny>>::iterator bunny = bunnies.begin(); bunny != bunnies.end(); ++bunny)
    {
        if (!(*bunny)->GetInfected()){
            if (currentOffset == healthyoffset){
                (*bunny)->Infect();
                DisplayBunnyTurned(*(*bunny));
                currentOffset = 0;
                infected++;
            }
            else{
                currentOffset++;
            }
        }
        if (infected == infectedCount)
            return;
    }*/
};

bool BunnyManager::CheckForCullKey()
{
    std::cout << "Press any key to cull the rabbits" << std::endl;
    float seconds = 0;
    while (seconds < 2)
    {
        if (_kbhit())
        {
            char dumpBuffer = getch(); // Empties the keyboard buffer so we dont loop
            return true;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        seconds += 0.1;
    }
    return false;
}

/**
 * @brief Kills off half the bunnies randomly
 */
void BunnyManager::CullBunnies(){
    if (bunnies.size() > CULL_AT_NUMBER || CheckForCullKey())
    {
        std::cout << "######################################################" << std::endl;
        std::cout << "                        Culling" << std::endl;
        std::cout << "######################################################" << std::endl;
        int cullAmount = bunnies.size() / 2;
        int culled = 0;
        bool toggle = rand() % 2 == 0;

        std::list<std::shared_ptr<Bunny>>::iterator bunny = bunnies.begin();
        while (bunny != bunnies.end()) {
            if (toggle){
                DisplayBunnyDeath(*(*bunny));
                gridManager.RemoveBunnyFromGrid((*bunny)->GetLocation());
                bunnies.erase(bunny++);
                culled++;
            }
            else{
                ++bunny;
            }
            if (culled == cullAmount){return;}
            toggle = !toggle;
        }
    }
}

/**
 * @brief Counts how many bunnies there are
 * 
 * @return int the amount of bunnies
 */
int BunnyManager::BunnyCount(){
    return bunnies.size();
}


void BunnyManager::DisplayBunnyBirth(Bunny &bunny){
    if (bunny.GetInfected()) {std::cout << "Infected ";}
    else                     {std::cout << "Normal ";}
    std::cout << bunny.GetColourAsString();
    (bunny.GetSex() == Gender::Male) ? (std::cout << " Male ") : (std::cout << " Female ");
    std::cout << "called " << bunny.GetName() << " was born!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(MESSAGE_TIME));
};

void BunnyManager::DisplayBunnyDeath(Bunny &bunny){
    if (bunny.GetInfected()) {std::cout << "Infected ";}
    else                        {std::cout << "Normal ";}
    std::cout << bunny.GetAge() << " year old ";
    // Colour
    std::cout << bunny.GetColourAsString();
    (bunny.GetSex() == Gender::Male) ? (std::cout << " Male ") : (std::cout << " Female ");
    std::cout << "called " << bunny.GetName() << " died!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(MESSAGE_TIME));
};

void BunnyManager::DisplayBunnyTurned(Bunny &bunny){
    std::cout << "Normal bunny " << bunny.GetName() << " became Infected!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(MESSAGE_TIME));
};

void BunnyManager::DisplayBunnies(){
    for (std::list<std::shared_ptr<Bunny>>::iterator bunny = bunnies.begin(); bunny != bunnies.end(); ++bunny)
    {
        if ((*bunny)->GetInfected()) {std::cout << "Infected ";}
        else                            {std::cout << "Normal ";}
        std::cout << (*bunny)->GetAge() << " year old ";
        // Colour
        std::cout << (*bunny)->GetColourAsString();
        ((*bunny)->GetSex() == Gender::Male) ? (std::cout << " Male ") : (std::cout << " Female ");
        std::cout << "bunny called " << (*bunny)->GetName() << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(MESSAGE_TIME));
    std::cout << std::endl;
};

void BunnyManager::KillRandomBunny(){
    int randomValue = rand() % bunnies.size();
    std::list<std::shared_ptr<Bunny>>::iterator bunny = bunnies.begin();
    std::advance(bunny, randomValue);
    DisplayBunnyDeath(*(*bunny));
    bunnies.erase(bunny++);
}


void BunnyManager::DrawGrid()
{
    gridManager.DrawGrid();
};