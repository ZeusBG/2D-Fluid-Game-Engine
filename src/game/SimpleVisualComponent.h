#pragma once
#include <engine/object/VisualComponent.h>

class SimpleVisualComponent : public VisualComponent
{
	std::unique_ptr<Engine> m_Engine;
public:
	SimpleVisualComponent();
};

