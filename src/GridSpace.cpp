#include "../include/GridSpace.h"

GridSpace::GridSpace() : bunny{nullptr}
{
    indexValue = 0;
};

GridSpace::GridSpace(int index) : bunny{nullptr}
{
    indexValue = index;
};

GridSpace::~GridSpace(){
};

void GridSpace::AddBunnyToSpace(std::shared_ptr<Bunny> bun){
    bunny = bun;
    bunny->SetLocation(indexValue);
};

void GridSpace::ClearSpace(){
    bunny = nullptr;
};

std::shared_ptr<Bunny> GridSpace::GetBunnyFromSpace(){
    return bunny;
};

int GridSpace::GetIndex() { return indexValue; };