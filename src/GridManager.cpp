#include <iostream>
#include "../include/GridManager.h"

GridManager::GridManager(){
    for (int space = 0; space < GRID_HEIGHT * GRID_WIDTH; space++){
        std::shared_ptr<GridSpace>newSpace(new GridSpace(space));
        grid.push_back(std::move(newSpace));            // Forms grid where 0 is top left
        availableSpaces.push_back(grid[space]);
    }
};
GridManager::~GridManager(){};

void GridManager::DrawGrid(){
    for (int gridspot = 0; gridspot < GRID_HEIGHT * GRID_WIDTH; gridspot++){
        if (gridspot%GRID_WIDTH == 0){
            std::cout << std::endl;
        }
        if (grid[gridspot]->GetBunnyFromSpace() != nullptr){
            std::cout << grid[gridspot]->GetBunnyFromSpace()->GetIcon();
        }
        else{
            std::cout << "`";
        }
    }
};

void GridManager::AddBunnyToGrid(std::shared_ptr<Bunny> &bunny){
    int spaceIndex = rand() % availableSpaces.size();
    std::list<std::shared_ptr<GridSpace>>::iterator availableSpace = availableSpaces.begin();
    std::advance(availableSpace, spaceIndex);
    std::shared_ptr<GridSpace> space = *availableSpace;
    space->AddBunnyToSpace(bunny);
    bunny->SetLocation(space->GetIndex());
    availableSpaces.erase(availableSpace);
};

void GridManager::AddBunnyToGrid(std::shared_ptr<Bunny> bunny, int location){
    grid[location]->AddBunnyToSpace(bunny);
};

void GridManager::RemoveBunnyFromGrid(int location)
{
    grid[location]->ClearSpace();
};

std::vector<std::shared_ptr<GridSpace>> GridManager::GetGridConnectingGridSpaces(int location)
{
    // Remember 0 is top left
    std::vector<std::shared_ptr<GridSpace>> ConnectedSpaces;
    int Above = location - GRID_WIDTH;
    int Below = location + GRID_WIDTH;
    int Left = location - 1;
    int Right = location + 1;

    if (Above >= 0)
    {
        // Add to connected spaces
        ConnectedSpaces.push_back(grid[Above]);
    }
    if (Below < GRID_HEIGHT * GRID_WIDTH)
    {
        // Add to connected spaces
        ConnectedSpaces.push_back(grid[Below]);
    }
    if (Left > 0 && Left % GRID_WIDTH != GRID_WIDTH - 1)
    {
        // Add to connected spaces
        ConnectedSpaces.push_back(grid[Left]);
    }
    if (Right < GRID_HEIGHT*GRID_WIDTH && Right % GRID_WIDTH != 0)
    {
        // Add to connected spaces
        ConnectedSpaces.push_back(grid[Right]);
    }

    return ConnectedSpaces;
}

std::vector<std::shared_ptr<GridSpace>> GridManager::GetEmptyConnectingGridSpaces(int location)
{
    // Remember 0 is top left
    std::vector<std::shared_ptr<GridSpace>> ConnectedSpaces;
    int Above = location - GRID_WIDTH;
    int Below = location + GRID_WIDTH;
    int Left = location - 1;
    int Right = location + 1;

    if (Above >= 0)
    {
        // Add to connected spaces
        if (grid[Above]->GetBunnyFromSpace() == nullptr){ConnectedSpaces.push_back(grid[Above]);}
    }
    if (Below < GRID_HEIGHT * GRID_WIDTH)
    {
        // Add to connected spaces
        if (grid[Below]->GetBunnyFromSpace() == nullptr){ConnectedSpaces.push_back(grid[Below]);}
    }
    if (Left > 0 && Left % GRID_WIDTH != GRID_WIDTH - 1)
    {
        // Add to connected spaces
        if (grid[Left]->GetBunnyFromSpace() == nullptr){ConnectedSpaces.push_back(grid[Left]);}
    }
    if (Right < GRID_HEIGHT * GRID_WIDTH && Right % GRID_WIDTH != 0)
    {
        // Add to connected spaces
        if (grid[Right]->GetBunnyFromSpace() == nullptr){ConnectedSpaces.push_back(grid[Right]);}
    }

    return ConnectedSpaces;
}

std::vector<std::shared_ptr<GridSpace>> GridManager::GetUsedConnectingGridSpaces(int location)
{
    // Remember 0 is top left
    std::vector<std::shared_ptr<GridSpace>> ConnectedSpaces;
    int Above = location - GRID_WIDTH;
    int Below = location + GRID_WIDTH;
    int Left = location - 1;
    int Right = location + 1;

    if (Above >= 0)
    {
        // Add to connected spaces
        if (grid[Above]->GetBunnyFromSpace() != nullptr){ConnectedSpaces.push_back(grid[Above]);}
    }
    if (Below < GRID_HEIGHT * GRID_WIDTH)
    {
        // Add to connected spaces
        if (grid[Below]->GetBunnyFromSpace() != nullptr){ConnectedSpaces.push_back(grid[Below]);}
    }
    if (Left > 0 && Left % GRID_WIDTH != GRID_WIDTH - 1)
    {
        // Add to connected spaces
        if (grid[Left]->GetBunnyFromSpace() != nullptr){ConnectedSpaces.push_back(grid[Left]);}
    }
    if (Right < GRID_HEIGHT * GRID_WIDTH && Right % GRID_WIDTH != 0)
    {
        // Add to connected spaces
        if (grid[Right]->GetBunnyFromSpace() != nullptr){ConnectedSpaces.push_back(grid[Right]);}
    }

    return ConnectedSpaces;
}