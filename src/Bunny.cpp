#include "../include/Bunny.h"

/**
 * @brief Construct a new Bunny:: Bunny object
 * Sets:
 *  age to 0,
 *  colour to a random colour,
 *  infected based on a 2% chance,
 *  name to a random name from our names list.
 */
Bunny::Bunny(){
    // Set Age
    age = 0;
    location = -1;
    // Get random value
    int randomValue = rand() % 100;
    // Set Gender
    (randomValue % 2 == 0) ? (sex = Gender::Male) : (sex = Gender::Female);
    // Set Colour
    colour = static_cast<Colours>(randomValue % Colours::END_OF_ENUM);
        // if      (randomValue < 25)  {colour = Colours::White;}
        // else if (randomValue < 50)  {colour = Colours::Brown;}
        // else if (randomValue < 75)  {colour = Colours::Black;}
        // else                        {colour = Colours::Spotted;}
    // Set infected
    randomValue = rand() % 100;
    (randomValue < 2) ? (infected = true) : (infected = false);
    // Set Name
    randomValue = rand() % bunnyNames.size();
    name = bunnyNames[randomValue];
    // Set Icon
    (sex == Gender::Male) ? (Icon = 'm') : (Icon = 'f');
    if (infected)
        Icon = 'X';
};

/**
 * @brief Construct a new Bunny:: Bunny object
 * Sets:
 *  age to 0,
 *  colour to the colour passed in,
 *  infected based on a 2% chance,
 *  name to a random name from our names list.
 */
Bunny::Bunny(Colours colourWanted){
    // Get random value
    int randomValue = rand() % 100;
    // Set Age
    age = 0;
    // Set Gender
    (randomValue % 2 == 0) ? (sex = Gender::Male) : (sex = Gender::Female);
    // Set Colour
    colour = colourWanted;
    // Set infected
    (randomValue < 2) ? (infected = true) : (infected = false);
    // Set Name
    randomValue = rand() % bunnyNames.size();
    name = bunnyNames[randomValue];
    // Set Icon
    (sex == Gender::Male) ? (Icon = 'm') : (Icon = 'f');
    if (infected)
        Icon = 'X';
}


// Getters

Gender      Bunny::GetSex()             { return sex;};
Colours     Bunny::GetColour()          { return colour;};
int         Bunny::GetAge()             { return age;};
std::string Bunny::GetName()            { return name;};
bool        Bunny::GetInfected()        { return infected; };
std::string Bunny::GetColourAsString()  { return ColourNames[colour];}
char        Bunny::GetIcon()            { return Icon; }
int         Bunny::GetLocation()        { return location; }
void        Bunny::SetLocation(int loc) { location = loc; }

// Methods

void Bunny::Infect()    { 
    infected = true;
    Icon = 'X';
}
void Bunny::GrowUp()    { 
    age++; 
    if (age == 2 && !infected)
    {
        // Set Icon
        (sex == Gender::Male) ? (Icon = 'M') : (Icon = 'F');
    }
}