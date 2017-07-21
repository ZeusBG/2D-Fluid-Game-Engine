#pragma once
#include "../core/IModule.h"
#include "KeyCodes.h"
class IInput : public IModule
{
public:
	virtual ~IInput() {};
	
	virtual bool IsKeyPressed(KeyCode code) = 0;
	virtual bool IsMouseButtonPressed(KeyCode code) = 0;

	virtual bool IsKeyJustPressed(KeyCode code) = 0;
	virtual bool IsMouseButtonJustPressed(KeyCode code) = 0;

	virtual bool IsKeyJustReleased(KeyCode code) = 0;
	virtual bool IsMouseButtonJustReleased(KeyCode code) = 0;

	friend class Window;

private:
	virtual void KeyPress(KeyCode) = 0;
	virtual void MouseButtonPress(KeyCode) = 0;
};

