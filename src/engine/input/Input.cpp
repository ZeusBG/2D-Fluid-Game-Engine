#include "Input.h"
#pragma once

Input::Input()
{
}

Input::~Input()
{
}

bool Input::IsKeyPressed(KeyCode code)
{
	return false;
}

bool Input::IsMouseButtonPressed(KeyCode code)
{
	return false;
}

bool Input::IsKeyJustPressed(KeyCode code)
{
	return false;
}

bool Input::IsMouseButtonJustPressed(KeyCode code)
{
	return false;
}

bool Input::IsKeyJustReleased(KeyCode code)
{
	return false;
}

bool Input::IsMouseButtonJustReleased(KeyCode code)
{
	return false;
}

void Input::Update(float delta)
{
}

void Input::Init(Engine * engine)
{
}

void Input::Destroy()
{
}

void Input::KeyPress(KeyCode)
{
}

void Input::MouseButtonPress(KeyCode)
{
}
