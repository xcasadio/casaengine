#include "ImGuiAdapter.h"
#include "imgui/bgfx-imgui.h"

namespace CasaEngine
{
	std::map<int, int> ImGuiAdapter::m_Vars;

	void addKeyEvent(sf::Event event, ImGuiIO& io, bool isDown);
	void addMouseButtonEvent(sf::Event event, ImGuiIO& io, bool isDown);

	void ImGuiAdapter::Create(float _fontSize)
	{
		::imguiCreate(_fontSize);
	}

	void ImGuiAdapter::Destroy()
	{
		::imguiDestroy();
	}

	void ImGuiAdapter::BeginFrame(unsigned short _width, unsigned short _height, unsigned char _view)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(_width, _height);
		::imguiBeginFrame(_view);
	}

	void ImGuiAdapter::EndFrame()
	{
		::imguiEndFrame();
	}

	void ImGuiAdapter::UpdateInput(const sf::Event& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		switch (event.type)
		{
		case sf::Event::GainedFocus:
			io.AppFocusLost = false;
			break;

		case sf::Event::LostFocus:
			io.ClearInputKeys();
			io.AppFocusLost = true;
			break;

		case sf::Event::KeyPressed:
			addKeyEvent(event, io, true);

			switch (event.key.code)
			{
			case sf::Keyboard::LAlt:
			case sf::Keyboard::RAlt:
				io.KeyAlt = true;
				break;

			case sf::Keyboard::LControl:
			case sf::Keyboard::RControl:
				io.KeyCtrl = true;
				break;

			case sf::Keyboard::LShift:
			case sf::Keyboard::RShift:
				io.KeyShift = true;
				break;

			default:
				break;
			}
			break;

		case sf::Event::KeyReleased:
			addKeyEvent(event, io, false);

			switch (event.key.code)
			{
			case sf::Keyboard::LAlt:
			case sf::Keyboard::RAlt:
				io.KeyAlt = false;
				break;

			case sf::Keyboard::LControl:
			case sf::Keyboard::RControl:
				io.KeyCtrl = false;
				break;

			case sf::Keyboard::LShift:
			case sf::Keyboard::RShift:
				io.KeyShift = false;
				break;
			}
			break;

		case sf::Event::TextEntered:
			io.AddInputCharacter(event.text.unicode);
			break;

		case sf::Event::MouseButtonPressed:
			addMouseButtonEvent(event, io, true);
			break;

		case sf::Event::MouseButtonReleased:
			addMouseButtonEvent(event, io, false);
			break;

		case sf::Event::MouseMoved:
			io.AddMousePosEvent(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
			io.MouseDelta.x = event.mouseMove.x - io.MousePos.x;
			io.MouseDelta.y = event.mouseMove.y - io.MousePos.y;
			io.MousePos.x = event.mouseMove.x;
			io.MousePos.y = event.mouseMove.y;
			break;

		case sf::Event::MouseWheelScrolled:
			io.AddMouseWheelEvent(0.0f, event.mouseWheelScroll.delta);
			break;
		}
	}

	void ImGuiAdapter::DisplayUI4Material(Material& mat_, int x_, int y_, int width_, int height_, bool enabled_)
	{
		int id = (int)&mat_;

		if (m_Vars.find(id) == m_Vars.end())
		{
			m_Vars[id] = 0;
		}
		/*
		::imguiBeginScrollArea((std::string("Material ") + mat_.GetName()).c_str(), x_, y_, width_, height_, &m_Vars[id], enabled_);
		::imguiSeparatorLine();

		::imguiCollapse("Test collapse", "sub text", false, true);

		::imguiSlider("Texture repetition U", mat_.m_Texture0Repeat.x, 0.01f, 100.0f, 0.1f);
		::imguiSeparator();
		::imguiSlider("Texture repetition V", mat_.m_Texture0Repeat.y, 0.01f, 100.0f, 0.1f);

		::imguiEndScrollArea();
		*/
	}

	void ImGuiAdapter::Update(const GameTime& gameTime)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = gameTime.FrameTime();
	}


	std::map< sf::Keyboard::Key, ImGuiKey_> keyMapper =
	{
		{ sf::Keyboard::Key::A			 , ImGuiKey_A},
		{ sf::Keyboard::Key::B           , ImGuiKey_B},
		{ sf::Keyboard::Key::C           , ImGuiKey_C},
		{ sf::Keyboard::Key::D           , ImGuiKey_D},
		{ sf::Keyboard::Key::E           , ImGuiKey_E},
		{ sf::Keyboard::Key::F           , ImGuiKey_F},
		{ sf::Keyboard::Key::G           , ImGuiKey_G},
		{ sf::Keyboard::Key::H           , ImGuiKey_H},
		{ sf::Keyboard::Key::I           , ImGuiKey_I},
		{ sf::Keyboard::Key::J           , ImGuiKey_J},
		{ sf::Keyboard::Key::K           , ImGuiKey_K},
		{ sf::Keyboard::Key::L           , ImGuiKey_L},
		{ sf::Keyboard::Key::M           , ImGuiKey_M},
		{ sf::Keyboard::Key::N           , ImGuiKey_N},
		{ sf::Keyboard::Key::O           , ImGuiKey_O},
		{ sf::Keyboard::Key::P           , ImGuiKey_P},
		{ sf::Keyboard::Key::Q           , ImGuiKey_Q},
		{ sf::Keyboard::Key::R           , ImGuiKey_R},
		{ sf::Keyboard::Key::S           , ImGuiKey_S},
		{ sf::Keyboard::Key::T           , ImGuiKey_T},
		{ sf::Keyboard::Key::U           , ImGuiKey_U},
		{ sf::Keyboard::Key::V           , ImGuiKey_V},
		{ sf::Keyboard::Key::W           , ImGuiKey_W},
		{ sf::Keyboard::Key::X           , ImGuiKey_X},
		{ sf::Keyboard::Key::Y           , ImGuiKey_Y},
		{ sf::Keyboard::Key::Z           , ImGuiKey_Z},
		{ sf::Keyboard::Key::Num0        , ImGuiKey_0},
		{ sf::Keyboard::Key::Num1        , ImGuiKey_1},
		{ sf::Keyboard::Key::Num2        , ImGuiKey_2},
		{ sf::Keyboard::Key::Num3        , ImGuiKey_3},
		{ sf::Keyboard::Key::Num4        , ImGuiKey_4},
		{ sf::Keyboard::Key::Num5        , ImGuiKey_5},
		{ sf::Keyboard::Key::Num6        , ImGuiKey_6},
		{ sf::Keyboard::Key::Num7        , ImGuiKey_7},
		{ sf::Keyboard::Key::Num8        , ImGuiKey_8},
		{ sf::Keyboard::Key::Num9        , ImGuiKey_9},
		{ sf::Keyboard::Key::Escape      , ImGuiKey_Escape},
		{ sf::Keyboard::Key::LControl    , ImGuiKey_LeftCtrl},
		{ sf::Keyboard::Key::LShift      , ImGuiKey_LeftShift},
		{ sf::Keyboard::Key::LAlt        , ImGuiKey_LeftAlt},
		{ sf::Keyboard::Key::LSystem     , ImGuiKey_LeftSuper},
		{ sf::Keyboard::Key::RControl    , ImGuiKey_RightCtrl},
		{ sf::Keyboard::Key::RShift      , ImGuiKey_RightShift},
		{ sf::Keyboard::Key::RAlt        , ImGuiKey_RightAlt},
		{ sf::Keyboard::Key::RSystem     , ImGuiKey_RightSuper},
		{ sf::Keyboard::Key::Menu        , ImGuiKey_Menu},
		{ sf::Keyboard::Key::LBracket    , ImGuiKey_LeftBracket},
		{ sf::Keyboard::Key::RBracket    , ImGuiKey_RightBracket},
		{ sf::Keyboard::Key::Semicolon   , ImGuiKey_Semicolon},
		{ sf::Keyboard::Key::Comma       , ImGuiKey_Comma},
		{ sf::Keyboard::Key::Period      , ImGuiKey_Period},
		{ sf::Keyboard::Key::Quote       , ImGuiKey_Apostrophe},
		{ sf::Keyboard::Key::Slash       , ImGuiKey_Slash},
		{ sf::Keyboard::Key::Backslash   , ImGuiKey_Backslash},
		{ sf::Keyboard::Key::Equal       , ImGuiKey_Equal},
		{ sf::Keyboard::Key::Hyphen      , ImGuiKey_Minus},
		{ sf::Keyboard::Key::Space       , ImGuiKey_Space},
		{ sf::Keyboard::Key::Enter       , ImGuiKey_Enter},
		{ sf::Keyboard::Key::Backspace   , ImGuiKey_Backspace},
		{ sf::Keyboard::Key::Tab         , ImGuiKey_Tab},
		{ sf::Keyboard::Key::PageUp      , ImGuiKey_PageUp},
		{ sf::Keyboard::Key::PageDown    , ImGuiKey_PageDown},
		{ sf::Keyboard::Key::End         , ImGuiKey_End},
		{ sf::Keyboard::Key::Home        , ImGuiKey_Home},
		{ sf::Keyboard::Key::Insert      , ImGuiKey_Insert},
		{ sf::Keyboard::Key::Delete      , ImGuiKey_Delete},
		{ sf::Keyboard::Key::Add         , ImGuiKey_KeypadAdd},
		{ sf::Keyboard::Key::Subtract    , ImGuiKey_KeypadSubtract},
		{ sf::Keyboard::Key::Multiply    , ImGuiKey_KeypadMultiply},
		{ sf::Keyboard::Key::Divide      , ImGuiKey_KeypadDivide},
		{ sf::Keyboard::Key::Left        , ImGuiKey_LeftArrow},
		{ sf::Keyboard::Key::Right       , ImGuiKey_RightArrow},
		{ sf::Keyboard::Key::Up          , ImGuiKey_UpArrow},
		{ sf::Keyboard::Key::Down        , ImGuiKey_DownArrow},
		{ sf::Keyboard::Key::Numpad0     , ImGuiKey_Keypad0},
		{ sf::Keyboard::Key::Numpad1     , ImGuiKey_Keypad1},
		{ sf::Keyboard::Key::Numpad2     , ImGuiKey_Keypad2},
		{ sf::Keyboard::Key::Numpad3     , ImGuiKey_Keypad3},
		{ sf::Keyboard::Key::Numpad4     , ImGuiKey_Keypad4},
		{ sf::Keyboard::Key::Numpad5     , ImGuiKey_Keypad5},
		{ sf::Keyboard::Key::Numpad6     , ImGuiKey_Keypad6},
		{ sf::Keyboard::Key::Numpad7     , ImGuiKey_Keypad7},
		{ sf::Keyboard::Key::Numpad8     , ImGuiKey_Keypad8},
		{ sf::Keyboard::Key::Numpad9     , ImGuiKey_Keypad9},
		{ sf::Keyboard::Key::F1          , ImGuiKey_F1},
		{ sf::Keyboard::Key::F2          , ImGuiKey_F2},
		{ sf::Keyboard::Key::F3          , ImGuiKey_F3},
		{ sf::Keyboard::Key::F4          , ImGuiKey_F4},
		{ sf::Keyboard::Key::F5          , ImGuiKey_F5},
		{ sf::Keyboard::Key::F6          , ImGuiKey_F6},
		{ sf::Keyboard::Key::F7          , ImGuiKey_F7},
		{ sf::Keyboard::Key::F8          , ImGuiKey_F8},
		{ sf::Keyboard::Key::F9          , ImGuiKey_F9},
		{ sf::Keyboard::Key::F10         , ImGuiKey_F10},
		{ sf::Keyboard::Key::F11         , ImGuiKey_F11},
		{ sf::Keyboard::Key::F12         , ImGuiKey_F12},
		{ sf::Keyboard::Key::Pause       , ImGuiKey_Pause}
	};

	void addKeyEvent(sf::Event event, ImGuiIO& io, bool isDown)
	{
		const auto key = keyMapper.find(event.key.code);
		if (key != keyMapper.end())
		{
			io.AddKeyEvent(key->second, isDown);
		}
	}

	std::map< sf::Mouse::Button, int> mouseButtonMapper =
	{
		{ sf::Mouse::Button::Left			 , ImGuiMouseButton_Left},
		{ sf::Mouse::Button::Right           , ImGuiMouseButton_Right},
		{ sf::Mouse::Button::Middle          , ImGuiMouseButton_Middle},
	};

	void addMouseButtonEvent(sf::Event event, ImGuiIO& io, bool isDown)
	{
		const auto key = mouseButtonMapper.find(event.mouseButton.button);
		if (key != mouseButtonMapper.end())
		{
			io.AddMouseButtonEvent(key->second, isDown);
			io.MouseDown[key->second] = isDown; // legacy
		}
	}
}
