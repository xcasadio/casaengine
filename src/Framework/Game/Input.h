#ifndef INPUT_H_
#define INPUT_H_

#include <SFML/Window/Event.hpp>

#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/Joystick.hpp"
#include "CA_Export.h"
#include "SFML/Window/Keyboard.hpp"

namespace CasaEngine
{
	class CA_EXPORT Input
	{
	public:
		Input();
		~Input();

		void Initialize();
		void Update();
		void OnEvent(sf::Event& event_);

		bool IsKeyDown(sf::Keyboard::Key KeyCode) const;
		bool IsKeyJustDown(sf::Keyboard::Key KeyCode) const;
		bool IsMouseButtonDown(sf::Mouse::Button Button) const;
		bool IsMouseButtonJustDown(sf::Mouse::Button Button) const;
		bool IsJoystickButtonDown(unsigned int JoyId, unsigned int Button) const;
		bool IsJoystickButtonJustDown(unsigned int JoyId, unsigned int Button) const;

		float GetJoystickAxis(unsigned int JoyId, sf::Joystick::Axis Axis) const;
		float GetJoystickLeftStickX(unsigned int JoyId) const;
		float GetJoystickLeftStickY(unsigned int JoyId) const;
		float GetJoystickRightStickX(unsigned int JoyId) const;
		float GetJoystickRightStickY(unsigned int JoyId) const;
		float GetJoystickLeftTrigger(unsigned int JoyId) const;
		float GetJoystickRightTrigger(unsigned int JoyId) const;

		int GetDeltaMouseX() const;
		int GetDeltaMouseY() const;
		int GetMouseX() const;
		int GetMouseY() const;
		int GetMouseWheel() const;

		//
		bool IsTouchDown(unsigned int index_) const;
		bool IsTouchJustDown(unsigned int index_) const;
		bool IsTouchUp(unsigned int index_) const;
		bool IsTouchJustUp(unsigned int index_) const;
		void TouchPosition(unsigned int index_, float& x, float& y) const;

		bool IsTouchMove(unsigned int index_) const;
		float TouchMoveDeltaX(unsigned int index_) const;
		float TouchMoveDeltaY(unsigned int index_) const;

		void ResetStates();

	private:
		bool  m_Keys[sf::Keyboard::KeyCount];
		bool  m_MouseButtons[sf::Mouse::ButtonCount];
		int   m_MouseX;
		int   m_MouseY;
		int   m_MouseDeltaX;
		int   m_MouseDeltaY;
		int   m_MouseWheel;
		bool  m_JoystickButtons[sf::Joystick::Count][sf::Joystick::ButtonCount];
		float m_JoystickAxis[sf::Joystick::Count][sf::Joystick::AxisCount];
		bool  m_TouchDown[2];

		//save last state
		bool  m_LastKeys[sf::Keyboard::KeyCount];
		bool  m_LastMouseButtons[sf::Mouse::ButtonCount];
		int   m_LastMouseX;
		int   m_LastMouseY;
		int   m_LastMouseDeltaX;
		int   m_LastMouseDeltaY;
		int   m_LastMouseWheel;
		bool  m_LastJoystickButtons[sf::Joystick::Count][sf::Joystick::ButtonCount];
		float m_LastJoystickAxis[sf::Joystick::Count][sf::Joystick::AxisCount];
		bool  m_LastTouchDown[2];
	};

}

#endif
