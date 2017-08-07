#pragma once
#include "../core/IModule.h"
class Physics : public IModule
{
public:
    Physics();
    ~Physics();

    void Update(float delta);

private:
    //AVector<Component*> m_Components;
};

