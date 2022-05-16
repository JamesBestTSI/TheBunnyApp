#ifndef GRIDSPACE_H
#define GRIDSPACE_H
#include <string>
#include <list>
#include <memory>
#include "Bunny.h"

class GridSpace
{
private:
    std::shared_ptr<Bunny> bunny;
    int indexValue;

public:
    GridSpace();
    explicit GridSpace(int index);
    ~GridSpace();
    void AddBunnyToSpace(std::shared_ptr<Bunny> bun);
    void ClearSpace();
    std::shared_ptr<Bunny> GetBunnyFromSpace();
    int GetIndex();
};

#endif