#pragma once
#include "mapElements.h"

class Stain :
	public MapElements
{
public:

	Stain(float x, float y, float width, float height);
	Stain(float x, float y, float width, float height, std::string text);

};
