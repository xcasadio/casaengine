#include "Game/Input.h"
#include "SFML/Window/Event.hpp"
#include "Game.h"

namespace CasaEngine
{
	Input::Input()
	{
		ResetStates();
	}

	Input::~Input()
		= default;

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
	void Input::OnEvent(const sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			m_Keys[event.key.code] = true;
			break;

		case sf::Event::KeyReleased:
			m_Keys[event.key.code] = false;
			break;

		case sf::Event::MouseWheelMoved:
			m_MouseWheel = event.mouseWheel.delta;
			break;

		case sf::Event::MouseButtonPressed:
			m_MouseButtons[event.mouseButton.button] = true;
			break;

		case sf::Event::MouseButtonReleased:
			m_MouseButtons[event.mouseButton.button] = false;
			break;

		case sf::Event::MouseMoved:
			m_MouseDeltaX = event.mouseMove.x - m_MouseX;
			m_MouseDeltaY = event.mouseMove.y - m_MouseY;
			m_MouseX = event.mouseMove.x;
			m_MouseY = event.mouseMove.y;
			break;

		case sf::Event::JoystickButtonPressed:
			m_JoystickButtons[event.joystickButton.joystickId][event.joystickButton.button] = true;
			break;

		case sf::Event::JoystickButtonReleased:
			m_JoystickButtons[event.joystickButton.joystickId][event.joystickButton.button] = false;
			break;

		case sf::Event::JoystickMoved:
			m_JoystickAxis[event.joystickMove.joystickId][event.joystickMove.axis] = event.joystickMove.position;
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

		case sf::Event::LostFocus:
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
		memset(m_JoystickButtons, 0, sizeof(bool) * sf::Joystick::Count * sf::Joystick::ButtonCount);
		memset(m_JoystickAxis, 0, sizeof(float) * sf::Joystick::Count * sf::Joystick::AxisCount);

		m_LastMouseX = 0;
		m_LastMouseY = 0;
		m_LastMouseDeltaX = 0;
		m_LastMouseDeltaY = 0;
		m_LastMouseWheel = 0;

		memset(m_LastKeys, 0, sizeof(bool) * sf::Keyboard::Key::KeyCount);
		memset(m_LastMouseButtons, 0, sizeof(bool) * sf::Mouse::ButtonCount);
		memset(m_LastJoystickButtons, 0, sizeof(bool) * sf::Joystick::Count * sf::Joystick::ButtonCount);
		memset(m_LastJoystickAxis, 0, sizeof(float) * sf::Joystick::Count * sf::Joystick::AxisCount);

		/*for (int i = 0; i < Touch::Count; ++i)
		{
			m_Touch[i].IsDown = false;
			m_Touch[i].Positions.clear();
		}*/
	}

	bool Input::IsKeyDown(sf::Keyboard::Key keyCode) const
	{
		return m_Keys[keyCode];
	}

	bool Input::IsKeyJustDown(sf::Keyboard::Key keyCode) const
	{
		return m_Keys[keyCode]
			&& m_LastKeys[keyCode] == false;
	}

	bool Input::IsMouseButtonDown(sf::Mouse::Button button) const
	{
		return m_MouseButtons[button];
	}

	bool Input::IsMouseButtonJustDown(sf::Mouse::Button button) const
	{
		return m_MouseButtons[button] && m_LastMouseButtons[button] == false;
	}

	bool Input::IsJoystickButtonDown(unsigned int joyId, unsigned int button) const
	{
		if (joyId < sf::Joystick::Count && button < sf::Joystick::ButtonCount)
		{
			return m_JoystickButtons[joyId][button];
		}
		return false;
	}

	bool Input::IsJoystickButtonJustDown(unsigned int joyId, const unsigned int button) const
	{
		return IsJoystickButtonDown(joyId, button) && !m_LastJoystickButtons[button];
	}

	int Input::GetDeltaMouseX() const
	{
		return m_LastMouseDeltaX;
	}

	int Input::GetDeltaMouseY() const
	{
		return m_LastMouseDeltaY;
	}

	int Input::GetMouseX() const
	{
		return m_MouseX;
	}

	int Input::GetMouseY() const
	{
		return m_MouseY;
	}

	int Input::GetMouseWheel() const
	{
		return m_LastMouseWheel;
	}

	float Input::GetJoystickAxis(unsigned int joyId, const sf::Joystick::Axis axis) const
	{
		if (joyId < sf::Joystick::Count)
		{
			return m_JoystickAxis[joyId][axis];
		}

		return 0.f;
	}

	float Input::GetJoystickLeftStickX(unsigned joyId) const
	{
		return GetJoystickAxis(joyId, sf::Joystick::X);
	}

	float Input::GetJoystickLeftStickY(unsigned joyId) const
	{
		return GetJoystickAxis(joyId, sf::Joystick::Y);
	}

	float Input::GetJoystickRightStickX(unsigned joyId) const
	{
		return GetJoystickAxis(joyId, sf::Joystick::U);
	}

	float Input::GetJoystickRightStickY(unsigned joyId) const
	{
		return GetJoystickAxis(joyId, sf::Joystick::V);
	}

	float Input::GetJoystickLeftTrigger(unsigned joyId) const
	{
		float val = GetJoystickAxis(joyId, sf::Joystick::Z);
		return val > 0.0f ? val : 0.0f;
	}

	float Input::GetJoystickRightTrigger(unsigned joyId) const
	{
		float val = GetJoystickAxis(joyId, sf::Joystick::Z);
		return val < 0.0f ? std::abs(val) : 0.0f;
	}

	bool Input::IsTouchDown(unsigned int index_) const
	{
		return false; //m_pInput->IsTouchDown(index_);
	}

	bool Input::IsTouchJustDown(unsigned int index_) const
	{
		return false; //m_pInput->IsTouchDown(index_) && m_LastTouchData[index_].IsDown == false;
	}

	bool Input::IsTouchUp(unsigned int index_) const
	{
		return false; //m_pInput->IsTouchUp(index_);
	}

	bool Input::IsTouchJustUp(unsigned int index_) const
	{
		return false; //return m_pInput->IsTouchUp(index_) && m_LastTouchData[index_].IsDown == true;
	}

	void Input::TouchPosition(unsigned int index_, float& x, float& y) const
	{
		//x = m_pInput->TouchPositionX(index_);
		//y = m_pInput->TouchPositionY(index_);
	}

	bool Input::IsTouchMove(unsigned int index_) const
	{
		return false; /*return m_pInput->TouchPositions(index_).size() > m_LastTouchData[index_].Positions.size()
			&& m_LastTouchData[index_].Positions.size() > 1
			&& m_pInput->IsTouchDown(index_) == true;*/
	}

	float Input::TouchMoveDeltaX(unsigned int index_) const
	{
		return 0.0f; //return m_pInput->TouchPositionX(index_) - m_LastTouchData[index_].Positions.back().x;
	}

	float Input::TouchMoveDeltaY(unsigned int index_) const
	{
		return 0.0f; //return m_pInput->TouchPositionY(index_) - m_LastTouchData[index_].Positions.back().y;
	}
}
