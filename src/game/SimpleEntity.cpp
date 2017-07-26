#pragma once
#include "SimpleEntity.h"
#include "game/SimpleVisualComponent.h"
#include "engine/rendering/shaderobjects/SimplePS.h"
#include "engine/rendering/shaderobjects/SimpleVS.h"

SimpleEntity::SimpleEntity()
{
	//ComponentSharedPtr c(new SimpleVisualComponent());
	AddComponent(new SimpleVisualComponent());
}

void SimpleEntity::Update(float delta)
{
	Entity::Update(delta);
}