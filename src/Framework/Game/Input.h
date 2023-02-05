#pragma once

#include "CA_Export.h"

#include <SFML/Window/Event.hpp>
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/Joystick.hpp"
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
		void OnEvent(const sf::Event& event);

		bool IsKeyDown(sf::Keyboard::Key keyCode) const;
		bool IsKeyJustDown(sf::Keyboard::Key keyCode) const;
		bool IsMouseButtonDown(sf::Mouse::Button button) const;
		bool IsMouseButtonJustDown(sf::Mouse::Button button) const;
		bool IsJoystickButtonDown(unsigned int joyId, unsigned int button) const;
		bool IsJoystickButtonJustDown(unsigned int joyId, unsigned int button) const;

		float GetJoystickAxis(unsigned int joyId, sf::Joystick::Axis axis) const;
		float GetJoystickLeftStickX(unsigned int joyId) const;
		float GetJoystickLeftStickY(unsigned int joyId) const;
		float GetJoystickRightStickX(unsigned int joyId) const;
		float GetJoystickRightStickY(unsigned int joyId) const;
		float GetJoystickLeftTrigger(unsigned int joyId) const;
		float GetJoystickRightTrigger(unsigned int joyId) const;

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
