#pragma once
#include "../input/IInput.h"
#include "KeyCodes.h"
class Input : public IInput
{
public:
	Input();
	virtual ~Input();
	
	virtual bool IsKeyPressed(KeyCode code);
	virtual bool IsMouseButtonPressed(KeyCode code);

	virtual bool IsKeyJustPressed(KeyCode code);
	virtual bool IsMouseButtonJustPressed(KeyCode code);

	virtual bool IsKeyJustReleased(KeyCode code);
	virtual bool IsMouseButtonJustReleased(KeyCode code);

	virtual void Update(float delta);

	virtual void Init(Engine* engine);
	virtual const char* GetName() { return "Input"; }
	virtual void Destroy();

	friend class Window;

private:
	virtual void KeyPress(KeyCode);
	virtual void MouseButtonPress(KeyCode);
};

