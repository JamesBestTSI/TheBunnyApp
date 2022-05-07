#ifndef BUNNYMANAGER_H
#define BUNNYMANAGER_H
#include <string>
#include <list>
#include <memory>
#include "Bunny.h"

class BunnyManager{
private:
    std::list<std::shared_ptr<Bunny>> bunnies;
    bool matureMale=false;
    int infectedCount=0;
    const int CULL_AT_NUMBER = 1000; // 20;
    const int BREEDING_AGE = 2;
    const int MAX_HEALTHY_AGE = 10;
    const int MAX_INFECTED_AGE = 50;
    const int MESSAGE_TIME = 400;
    std::list<std::shared_ptr<Bunny>> mothers;

public:
    BunnyManager();
    ~BunnyManager();
    
    bool CheckForCullKey();

    void AddBunny();

    void AgeAll();
    void BirthNewBunnies();
    void TurnBunnyInfected();
    void CullBunnies();
    int BunnyCount();

    void DisplayBunnyBirth(Bunny &bunny);
    void DisplayBunnyDeath(Bunny &bunny);
    void DisplayBunnyTurned(Bunny &bunny);
    void DisplayBunnies();
    void KillRandomBunny();
};
#endif