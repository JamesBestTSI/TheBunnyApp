#ifndef BUNNYMANAGER_H
#define BUNNYMANAGER_H
#include <string>
#include <list>
#include <memory>
#include "Bunny.h"

class BunnyManager{
private:
    int currentBunnyID = 0;
    const int waitTime = 400;

public:
    std::list<std::shared_ptr<Bunny>> bunnies;
    BunnyManager();
    ~BunnyManager();
    void AddBunny();
    void RemoveBunny(int index);
    void AgeAll();
    void TurnBunnyRadioactive();
    bool ElderlyMale();
    void BirthNewBunnies();
    int ElderlyFemales();
    int RadioactiveBunnies();
    void DisplayBunnyBirth(Bunny &bunny);
    void DisplayBunnyDeath(Bunny &bunny);
    void DisplayBunnyTurned(Bunny &bunny);
    void DisplayBunnies();
    int BunnyCount();
    void KillRandomBunny();
};
#endif