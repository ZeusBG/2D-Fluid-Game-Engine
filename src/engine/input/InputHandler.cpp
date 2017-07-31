#include "engine/input/InputHandler.h"

InputHandler::InputHandler() :
    m_MousePosition (0,0),
    m_MousePreviousPosition(0,0),
    m_QuitRequested(false)
{
    Reset();
}

InputHandler::~InputHandler()
{
}

void InputHandler::Update(float dt)
{
    SDL_Event event;

    m_MousePreviousPosition = m_MousePosition;

    memcpy(m_MousePreviousButtonStates, m_MouseButtonStates, sizeof(m_MouseButtonStates));

    int mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    m_MousePosition.x = ((float)mouseX);
    m_MousePosition.y = ((float)mouseY);

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(event.button.button == SDL_BUTTON_LEFT)   { m_MouseButtonStates[MouseButton::LEFT] = true;}
            if(event.button.button == SDL_BUTTON_MIDDLE) { m_MouseButtonStates[MouseButton::MIDDLE] = true;}
            if(event.button.button == SDL_BUTTON_RIGHT)  { m_MouseButtonStates[MouseButton::RIGHT] = true;}
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            if(event.button.button == SDL_BUTTON_LEFT) {m_MouseButtonStates[MouseButton::LEFT] = false;}
            if(event.button.button == SDL_BUTTON_MIDDLE) {m_MouseButtonStates[MouseButton::MIDDLE] = false;}
            if(event.button.button == SDL_BUTTON_RIGHT) {m_MouseButtonStates[MouseButton::RIGHT] = false;}
        }
        else if (event.type == SDL_QUIT || IsKeyPressed(SDL_SCANCODE_ESCAPE))
        {
            m_QuitRequested = true;
        }


        memcpy(m_PtrPreviousKeyState, m_PtrKeyState, SDL_NUM_SCANCODES);
        memcpy(m_PtrKeyState, SDL_GetKeyboardState(0),SDL_NUM_SCANCODES);
    }
}

bool InputHandler::IsKeyPressed(SDL_Scancode key)
{
    if (m_PtrKeyState != 0)
    {
        if (m_PtrKeyState[key] == 1)
        {
            return true;
        }
    }

    return false;
}

bool InputHandler::IsKeyJustPressed(SDL_Scancode key)
{
    if (m_PtrKeyState)
    {
        if (m_PtrKeyState[key] == 1)
        {
            if (m_PtrPreviousKeyState)
            {
                return m_PtrPreviousKeyState[key] == 0;
            }

            return true;
        }

    }

    return false;
}

bool InputHandler::IsKeyJustReleased(SDL_Scancode key)
{
    if (m_PtrKeyState)
    {
        if (m_PtrKeyState[key] == 0)
        {
            if (m_PtrPreviousKeyState)
            {
                return m_PtrPreviousKeyState[key] == 1;
            }

            return true;
        }

    }

    return false;
}

void InputHandler::Reset()
{
    m_QuitRequested = false;
    memset(m_MouseButtonStates, 0 , sizeof(m_MouseButtonStates));
    memset(m_MousePreviousButtonStates, 0 , sizeof(m_MousePreviousButtonStates));
    memset(m_PtrKeyState, 0 , sizeof(m_PtrKeyState));
    memset(m_PtrPreviousKeyState, 0 , sizeof(m_PtrPreviousKeyState));
}