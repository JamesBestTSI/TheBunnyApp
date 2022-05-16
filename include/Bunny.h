#ifndef BUNNY_H
#define BUNNY_H
#include "DataTypes.h"

class Bunny{
private:
    Gender sex;
    Colours colour;
    int age;
    std::string name;
    bool infected;
    char Icon;
    int location;

public:
    Bunny();
    explicit Bunny(Colours colourWanted);

    // Get/Set
    Gender      GetSex();
    Colours     GetColour();
    int         GetAge();
    std::string GetName();
    bool        GetInfected();
    std::string GetColourAsString();
    char        GetIcon();
    int         GetLocation();
    void        SetLocation(int loc);

    // Methods
    void Infect();
    void GrowUp();
};

#endif