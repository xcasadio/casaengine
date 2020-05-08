
#include "Base.h"
#include "Game/Input.h"
#include "Maths/Math.h"
#include <string.h>
#include "SFML/Window/Event.hpp"
#include "Game.h"

namespace CasaEngine
{

Input::Input()
{
	ResetStates();
}


Input::~Input()
{
}

void Input::Initialize()
{
	
}

void Input::Update()
{
	memcpy(m_LastKeys, m_Keys, sizeof(bool) * sf::Keyboard::KeyCount);
	memcpy(m_LastMouseButtons, m_MouseButtons, sizeof(bool) * sf::Mouse::ButtonCount);
	m_LastMouseX = m_MouseX;
	m_LastMouseY = m_MouseY;
	m_LastMouseDeltaX = m_MouseDeltaX;
	m_LastMouseDeltaY = m_MouseDeltaY;
	m_LastMouseWheel = m_MouseWheel;
	memcpy(m_LastJoystickButtons, m_JoystickButtons, sizeof(bool) * sf::Joystick::Count * sf::Joystick::ButtonCount);
	memcpy(m_LastJoystickAxis, m_JoystickAxis, sizeof(float) * sf::Joystick::Count * sf::Joystick::AxisCount);

	m_MouseDeltaX = 0;
	m_MouseDeltaY = 0;
	m_MouseWheel = 0;
}

//
void Input::OnEvent(sf::Event &event_)
{
	switch (event_.type)
	{
	case sf::Event::KeyPressed:
		m_Keys[event_.key.code] = true;
		break;

	case sf::Event::KeyReleased:
		m_Keys[event_.key.code] = false;
		break;

	case sf::Event::MouseWheelMoved:
		m_MouseWheel = event_.mouseWheel.delta;
		break;

	case sf::Event::MouseButtonPressed:
		m_MouseButtons[event_.mouseButton.button] = true;
		break;

	case sf::Event::MouseButtonReleased:
		m_MouseButtons[event_.mouseButton.button] = false;
		break;

	case sf::Event::MouseMoved:
		m_MouseDeltaX = event_.mouseMove.x - m_MouseX;
		m_MouseDeltaY = event_.mouseMove.y - m_MouseY;
		m_MouseX = event_.mouseMove.x;
		m_MouseY = event_.mouseMove.y;
		break;

	case sf::Event::JoystickButtonPressed:
		m_JoystickButtons[event_.joystickButton.joystickId][event_.joystickButton.button] = true;
		break;

	case sf::Event::JoystickButtonReleased:
		m_JoystickButtons[event_.joystickButton.joystickId][event_.joystickButton.button] = false;
		break;

	case sf::Event::JoystickMoved:
		m_JoystickAxis[event_.joystickMove.joystickId][event_.joystickMove.axis] = event_.joystickMove.position;
		break;

	case sf::Event::JoystickConnected:
		break;

	case sf::Event::JoystickDisconnected:
		break;

	case sf::Event::TouchBegan:

		break;

	case sf::Event::TouchMoved:

		break;

	case sf::Event::TouchEnded:

		break;

	case sf::Event::SensorChanged:
		break;

	case sf::Event::LostFocus :
		ResetStates();
		break;
	}
}

void Input::ResetStates()
{
	m_MouseX = 0;
	m_MouseY = 0;
	m_MouseDeltaX = 0;
	m_MouseDeltaY = 0;
	m_MouseWheel = 0;

	memset(m_Keys, 0, sizeof(bool) * sf::Keyboard::Key::KeyCount);
	memset(m_MouseButtons, 0, sizeof(bool) * sf::Mouse::ButtonCount);
	memset(m_JoystickButtons[0], 0, sizeof(bool) * sf::Joystick::Count * sf::Joystick::ButtonCount);
	memset(m_JoystickAxis[0], 0, sizeof(float) * sf::Joystick::Count * sf::Joystick::AxisCount);

	m_LastMouseX = 0;
	m_LastMouseY = 0;
	m_LastMouseDeltaX = 0;
	m_LastMouseDeltaY = 0;
	m_LastMouseWheel = 0;

	memset(m_LastKeys, 0, sizeof(bool) * sf::Keyboard::Key::KeyCount);
	memset(m_LastMouseButtons, 0, sizeof(bool) * sf::Mouse::ButtonCount);
	memset(m_LastJoystickButtons[0], 0, sizeof(bool) * sf::Joystick::Count * sf::Joystick::ButtonCount);
	memset(m_LastJoystickAxis[0], 0, sizeof(float) * sf::Joystick::Count * sf::Joystick::AxisCount);

	/*for (int i = 0; i < Touch::Count; ++i)
	{
		m_Touch[i].IsDown = false;
		m_Touch[i].Positions.clear();
	}*/
}

/**
 * 
 */
bool Input::IsKeyDown( sf::Keyboard::Key KeyCode ) const
{
	return m_Keys[KeyCode];
}

/**
 * 
 */
bool Input::IsKeyJustDown( sf::Keyboard::Key KeyCode ) const
{
	return m_Keys[KeyCode]
		&& m_LastKeys[KeyCode] == false;
}

/**
 * 
 */
bool Input::IsMouseButtonDown( sf::Mouse::Button Button ) const
{
	return m_MouseButtons[Button];
}

/**
 * 
 */
bool Input::IsMouseButtonJustDown( sf::Mouse::Button Button ) const
{
	return m_MouseButtons[Button]
		&& m_LastMouseButtons[Button] == false;
}

/**
 * 
 */
bool Input::IsJoystickButtonDown( unsigned int JoyId, unsigned int Button ) const
{
	if ((JoyId < sf::Joystick::Count) && (Button < sf::Joystick::ButtonCount))
		return m_JoystickButtons[JoyId][Button];
	else
		return false;
}

/**
 * 
 */
bool Input::IsJoystickButtonJustDown( unsigned int JoyId, unsigned int Button ) const
{
	return IsJoystickButtonDown(JoyId, Button)
		&& m_LastJoystickButtons[Button] == false;
}

/**
 * 
 */
int Input::GetDeltaMouseX() const
{
	return m_LastMouseDeltaX;
}

/**
 * 
 */
int Input::GetDeltaMouseY() const
{
	return m_LastMouseDeltaY;
}

/**
 * 
 */
int Input::GetMouseX() const
{
	return m_MouseX;
}

/**
 * 
 */
int Input::GetMouseY() const
{
	return m_MouseY;
}

/**
 * 
 */
int Input::GetMouseWheel() const
{
	return m_LastMouseWheel;
}

/**
 * 
 */
float Input::GetJoystickAxis( unsigned int JoyId, sf::Joystick::Axis Axis ) const
{
	if (JoyId < sf::Joystick::Count)
		return m_JoystickAxis[JoyId][Axis];
	else
		return 0.f;
}

float Input::GetJoystickLeftStickX(unsigned JoyId) const
{
	return GetJoystickAxis(JoyId, sf::Joystick::X);
}

float Input::GetJoystickLeftStickY(unsigned JoyId) const
{
	return GetJoystickAxis(JoyId, sf::Joystick::Y);
}

float Input::GetJoystickRightStickX(unsigned JoyId) const
{
	return GetJoystickAxis(JoyId, sf::Joystick::U);
}

float Input::GetJoystickRightStickY(unsigned JoyId) const
{
	return GetJoystickAxis(JoyId, sf::Joystick::V);
}

float Input::GetJoystickLeftTrigger(unsigned JoyId) const
{
	float val = GetJoystickAxis(JoyId, sf::Joystick::Z);
	return val > 0.0f ? val : 0.0f;
}

float Input::GetJoystickRightTrigger(unsigned JoyId) const
{
	float val = GetJoystickAxis(JoyId, sf::Joystick::Z);
	return val < 0.0f ? std::abs(val) : 0.0f;
}

/**
 * 
 */
bool Input::IsTouchDown(unsigned int index_) const
{
	return false; //m_pInput->IsTouchDown(index_);
}

/**
 * 
 */
bool Input::IsTouchJustDown(unsigned int index_) const
{
	return false; //m_pInput->IsTouchDown(index_) && m_LastTouchData[index_].IsDown == false;
}

/**
 * 
 */
bool Input::IsTouchUp(unsigned int index_) const
{
	return false; //m_pInput->IsTouchUp(index_);
}

/**
 * 
 */
bool Input::IsTouchJustUp(unsigned int index_) const
{
	return false; //return m_pInput->IsTouchUp(index_) && m_LastTouchData[index_].IsDown == true;
}

/**
 * 
 */
void Input::TouchPosition(unsigned int index_, float &x, float &y) const
{
	//x = m_pInput->TouchPositionX(index_);
	//y = m_pInput->TouchPositionY(index_);
}

/**
 * 
 */
bool Input::IsTouchMove(unsigned int index_) const
{
	return false; /*return m_pInput->TouchPositions(index_).size() > m_LastTouchData[index_].Positions.size()
		&& m_LastTouchData[index_].Positions.size() > 1
		&& m_pInput->IsTouchDown(index_) == true;*/
}

/**
 * 
 */
float Input::TouchMoveDeltaX(unsigned int index_) const
{
	return 0.0f; //return m_pInput->TouchPositionX(index_) - m_LastTouchData[index_].Positions.back().x;
}

/**
 * 
 */
float Input::TouchMoveDeltaY(unsigned int index_) const
{
	return 0.0f; //return m_pInput->TouchPositionY(index_) - m_LastTouchData[index_].Positions.back().y;
}

}
