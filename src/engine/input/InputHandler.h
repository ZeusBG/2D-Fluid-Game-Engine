#pragma once
#include "engine/core/IModule.h"

#include "util/Collections.h"
#include "util/math/Vec.h"

#include <SDL.h>

class InputHandler : public IModule
{
public :
    enum MouseButton
    {
        LEFT = 0,
        MIDDLE = 1,
        RIGHT = 2,
        COUNT
    };

public:

    bool IsMouseButtonJustPressed(MouseButton mouseButton) const { return !m_MousePreviousButtonStates[mouseButton] && m_MouseButtonStates[mouseButton]; }
    bool IsMouseButtonJustReleased(MouseButton mouseButton) const { return m_MousePreviousButtonStates[mouseButton] && !m_MouseButtonStates[mouseButton]; }
    bool IsMouseButtonPressed(MouseButton mouseButton) const { return m_MousePreviousButtonStates[mouseButton] && m_MouseButtonStates[mouseButton]; }

    bool IsKeyPressed(SDL_Scancode key);
    bool IsKeyJustPressed(SDL_Scancode key);
    bool IsKeyJustReleased(SDL_Scancode key);
    bool QuitRequested() { return m_QuitRequested; };

    inline const Vec2& GetMousePosition() const { return m_MousePosition; }
    bool GetMousePositionChanged() const { return m_MousePreviousPosition != m_MousePosition; }

    //Overrides
    virtual void Update(float delta);

    virtual void Init(Engine* engine) {}
    virtual const char* GetName() { return "Input"; }

    virtual void Destroy() {}
    
    InputHandler();
    virtual ~InputHandler();


private:
    
    bool m_QuitRequested;

    void Reset();

    bool m_MousePreviousButtonStates[MouseButton::COUNT];
    bool m_MouseButtonStates[MouseButton::COUNT];

    Vec2 m_MousePreviousPosition;
    Vec2 m_MousePosition;

    Uint8 m_PtrPreviousKeyState[SDL_Scancode::SDL_NUM_SCANCODES];
    Uint8 m_PtrKeyState[SDL_Scancode::SDL_NUM_SCANCODES];
};

