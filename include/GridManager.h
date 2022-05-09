#ifndef GRIDMANAGER_H
#define GRIDMANAGER_H
#include <string>
#include <list>
#include <memory>
#include "GridSpace.h"

class GridManager
{
private:
    const static int GRID_WIDTH = 160;
    const static int GRID_HEIGHT = 40;
    std::vector<std::shared_ptr<GridSpace>> grid;
    std::list<std::shared_ptr<GridSpace>> availableSpaces;

public:
    GridManager();
    ~GridManager();
    void DrawGrid();
    void AddBunnyToGrid(std::shared_ptr<Bunny> &bunny);
    void AddBunnyToGrid(std::shared_ptr<Bunny> bunny, int location);
    void RemoveBunnyFromGrid(int location);
    std::vector<std::shared_ptr<GridSpace>> GetGridConnectingGridSpaces(int location);
    std::vector<std::shared_ptr<GridSpace>> GetEmptyConnectingGridSpaces(int location);
    std::vector<std::shared_ptr<GridSpace>> GetUsedConnectingGridSpaces(int location);
};

#endif