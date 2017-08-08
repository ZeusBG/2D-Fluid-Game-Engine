#pragma once
#include <engine/object/VisualComponent.h>

class SimpleVisualComponent : public VisualComponent
{
    ADD_SOLID_CLASS_METADATA(SimpleVisualComponent)
    std::unique_ptr<Engine> m_Engine;
public:
    SimpleVisualComponent();
};

using SimpleVisualComponentSP = std::shared_ptr<SimpleVisualComponent>;