#pragma once
#include "mapElements.h"

class Empty :
    public MapElements
{
public:
    Empty(float x, float y, float width, float height, int type);
};

