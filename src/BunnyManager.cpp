#include "../include/BunnyManager.h"
#include <iostream>
#include <thread>
#include <chrono>

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
    bun->SetID(currentBunnyID);
    DisplayBunnyBirth(*bun);
    currentBunnyID++;
    bunnies.push_back(std::move(bun));
};

void BunnyManager::RemoveBunny(int index)
{
    int count = 0;
    for (std::list<std::shared_ptr<Bunny>>::iterator bunny = bunnies.begin(); bunny != bunnies.end(); ++bunny)
    {
        if (count == index)
        {
            bunnies.erase(bunny++);
            // bunnies.remove(*bunny);
            return;
        }
    }
};

void BunnyManager::AgeAll(){
    std::list<std::shared_ptr<Bunny>>::iterator bunny = bunnies.begin();
    while (bunny != bunnies.end()){
        bool bunnyDeath = false;
        (*bunny)->Age();
        if ((*bunny)->GetAge() > 10){
            if (!(*bunny)->GetRadioactive() || (*bunny)->GetAge() > 50)
            {
                // Death
                DisplayBunnyDeath(*(*bunny));
                bunnies.erase(bunny++);
                bunnyDeath = true;
            }
        }
        if (!bunnyDeath)
            ++bunny;
    }
};

void BunnyManager::TurnBunnyRadioactive(){
    for (std::list<std::shared_ptr<Bunny>>::iterator bunny = bunnies.begin(); bunny != bunnies.end(); ++bunny)
    {
        if (!(*bunny)->GetRadioactive()){
            (*bunny)->SetRadioactive();
            DisplayBunnyTurned(*(*bunny));
            return;
        }
    }
};

bool BunnyManager::ElderlyMale()
{
    for (std::list<std::shared_ptr<Bunny>>::iterator bunny = bunnies.begin(); bunny != bunnies.end(); ++bunny)
    {
        if ((*bunny)->GetAge() > 2 && (*bunny)->GetSex() ==Gender::Male && !(*bunny)->GetRadioactive()){
            return true;
        }
    }
    return false;
};

int BunnyManager::ElderlyFemales()
{
    int counter = 0;
    for (std::list<std::shared_ptr<Bunny>>::iterator bunny = bunnies.begin(); bunny != bunnies.end(); ++bunny)
    {
        if ((*bunny)->GetAge() > 2 && (*bunny)->GetSex() == Gender::Female && !(*bunny)->GetRadioactive())
        {
            counter++;
        }
    }
    return counter;
};

void BunnyManager::BirthNewBunnies(){
    for (std::list<std::shared_ptr<Bunny>>::iterator bunny = bunnies.begin(); bunny != bunnies.end(); ++bunny)
    {
        if ((*bunny)->GetAge() > 2 && (*bunny)->GetSex() == Gender::Female && !(*bunny)->GetRadioactive())
        {
            std::shared_ptr<Bunny> bun(new Bunny(*(*bunny)));
            bun->SetID(currentBunnyID);
            DisplayBunnyBirth(*bun);
            currentBunnyID++;
            bunnies.push_back(std::move(bun));
        }
    }
};

int BunnyManager::RadioactiveBunnies(){
    int counter = 0;
    for (std::list<std::shared_ptr<Bunny>>::iterator bunny = bunnies.begin(); bunny != bunnies.end(); ++bunny)
    {
        if ((*bunny)->GetRadioactive()){
            counter++;
        }
    }
    return counter;
};

void BunnyManager::DisplayBunnyBirth(Bunny &bunny){
    if (bunny.GetRadioactive()) {std::cout << "Radioactive ";}
    else                    {std::cout << "Normal ";}
    std::cout << bunny.GetColourName();
    (bunny.GetSex() == Gender::Male) ? (std::cout << " Male ") : (std::cout << " Female ");
    std::cout << "called " << bunny.GetName() << " was born!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
};

void BunnyManager::DisplayBunnyDeath(Bunny &bunny){
    if (bunny.GetRadioactive()) {std::cout << "Radioactive ";}
    else                        {std::cout << "Normal ";}
    std::cout << bunny.GetAge() << " year old ";
    // Colour
    std::cout << bunny.GetColourName();
    (bunny.GetSex() == Gender::Male) ? (std::cout << " Male ") : (std::cout << " Female ");
    std::cout << "called " << bunny.GetName() << " died!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
};

void BunnyManager::DisplayBunnyTurned(Bunny &bunny){
    std::cout << "Normal bunny " << bunny.GetName() << " turned Radioactive!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
};

void BunnyManager::DisplayBunnies(){
    std::list<std::shared_ptr<Bunny>> bunniesSorted = bunnies;
    //bunniesSorted.sort();

    for (std::list<std::shared_ptr<Bunny>>::iterator bunny = bunniesSorted.begin(); bunny != bunniesSorted.end(); ++bunny)
    {
        if ((*bunny)->GetRadioactive()) {std::cout << "Radioactive bunny ";}
        else                            {std::cout << "Normal bunny ";}
        std::cout << (*bunny)->GetAge() << " year old ";
        // Colour
        std::cout << (*bunny)->GetColourName();
        ((*bunny)->GetSex() == Gender::Male) ? (std::cout << " Male ") : (std::cout << " Female ");
        std::cout << "called " << (*bunny)->GetName() << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    std::cout << std::endl;
};

int BunnyManager::BunnyCount(){
    return bunnies.size();
};

void BunnyManager::KillRandomBunny(){
    int randomValue = rand() % BunnyCount();
    std::list<std::shared_ptr<Bunny>>::iterator bunny = bunnies.begin();
    std::advance(bunny, randomValue);
    DisplayBunnyDeath(*(*bunny));
    bunnies.erase(bunny++);
}