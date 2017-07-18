#pragma once
#include "Interface.h"
class Physics : public Interface
{
public:
	Physics();
	~Physics();

	void Update(float delta);
};

