#pragma once
#include "mapElements.h"
class Wall :
    public MapElements
{
public:
	Wall(float x, float y, float width, float height, int type);
};

