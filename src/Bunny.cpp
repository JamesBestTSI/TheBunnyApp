#include "../include/Bunny.h"

Bunny::Bunny()
{
    // Get random value
    int randomValue = rand() % 100;

    // Set Age
    age = 0;
    // Set Gender
    (randomValue % 2 == 0) ? (sex = Gender::Male) : (sex = Gender::Female);
    // Set Colour
    if      (randomValue < 25)  {colour = Colours::White;}
    else if (randomValue < 50)  {colour = Colours::Brown;}
    else if (randomValue < 75)  {colour = Colours::Black;}
    else                        {colour = Colours::Spotted;}
    // Set radioactive
    randomValue = rand() % 100;
    (randomValue < 2) ? (radioactive = true) : (radioactive = false);
    // Set Name
    randomValue = rand() % bunnyNames.size();
    Name = bunnyNames[randomValue];

    personalID = 0;
};

Bunny::Bunny(Bunny &bunny1, Bunny &bunny2){
    Bunny *Mother;
    Bunny *Farther;

    if (bunny1.sex == Gender::Female) {Mother = &bunny1;        Farther = &bunny2;}
    else                              {Mother = &bunny2;        Farther = &bunny1;}

    // Get random value
    int randomValue = rand() % 100;     
    // Set Age
    age = 0;
    // Set Gender
    (randomValue % 2 == 0) ? (sex = Gender::Male) : (sex = Gender::Female);
    // Set Colour
    colour = Mother->colour;
    // Set radioactive
    (randomValue < 2) ? (radioactive = true) : (radioactive = false);
    // Set Name
    randomValue = rand() % bunnyNames.size();
    Name = bunnyNames[randomValue];
    personalID = 0;
}


Bunny::Bunny(Bunny &mother){
    Bunny *Mother = &mother;

    // Get random value
    int randomValue = rand() % 100;     
    // Set Age
    age = 0;
    // Set Gender
    (randomValue % 2 == 0) ? (sex = Gender::Male) : (sex = Gender::Female);
    // Set Colour
    colour = Mother->colour;
    // Set radioactive
    (randomValue < 2) ? (radioactive = true) : (radioactive = false);
    // Set Name
    randomValue = rand() % bunnyNames.size();
    Name = bunnyNames[randomValue];
    personalID = 0;
}


bool Bunny::operator<(const Bunny &bunnyObj) const
{
    return age < bunnyObj.age;
}

// Getters

Gender Bunny::GetSex()          { return sex;};
Colours Bunny::GetColour()      { return colour;};
int Bunny::GetAge()             { return age;};
std::string Bunny::GetName()    { return Name;};
bool Bunny::GetRadioactive()    { return radioactive;};
std::string Bunny::GetColourName(){
    switch (colour)
    {
    case Colours::White:
        return "White";
    case Colours::Brown:
        return "Brown";
    case Colours::Black:
        return "Black";
    case Colours::Spotted:
        return "Spotted";
    default:
        break;
    }
    return "";
}

// Setters

void Bunny::SetID(int id){
    personalID = id;
}

void Bunny::SetRadioactive(){
    radioactive = true;
}

// Methods

void Bunny::Age(){
    age++;
}