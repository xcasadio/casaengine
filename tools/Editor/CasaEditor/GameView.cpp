#include "GameView.h"
#include "qevent.h"
#include "Window\Event.h"
#include "QMenu"


/**
 * 
 */
GameView::GameView(QWidget *parent)
	: QGraphicsView(parent),
	m_pGameEditor(nullptr)
{

}

/**
 * 
 */
GameView::~GameView()
{

}

/**
 * 
 */
CasaEngine::GameEditor * GameView::GameEditor() const
{
	return m_pGameEditor;
}

/**
 * 
 */
void GameView::GameEditor( CasaEngine::GameEditor * val )
{
	m_pGameEditor = val;
}

void GameView::CutMenuClicked()
{

}

/**
 * Don't work, why ?
 */
void GameView::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);
	QAction *action = new QAction(this);
	action->setObjectName(QStringLiteral("Cut"));
	menu.addAction(action); // CutMenuClicked
	menu.exec(event->globalPos());
}

void GameView::mousePressEvent( QMouseEvent *event)
{

}

void GameView::mouseReleaseEvent( QMouseEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

void GameView::mouseDoubleClickEvent( QMouseEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

void GameView::mouseMoveEvent( QMouseEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

void GameView::wheelEvent( QWheelEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

void GameView::keyPressEvent( QKeyEvent *event)
{
	if (m_pGameEditor != nullptr)
	{
		CasaEngine::SystemEvent Evt;
		Evt.Type		= CasaEngine::SystemEvent::KeyPressed;
		Evt.Key.Alt     = (Qt::AltModifier & event->nativeModifiers()) != 0;//enum KeyboardModifier
		Evt.Key.Control = (Qt::ControlModifier & event->nativeModifiers()) != 0;
		Evt.Key.Shift   = (Qt::ShiftModifier & event->nativeModifiers()) != 0;
		Evt.Key.Code    = VirtualKeyCodeToSF(event->key()); // VirtualKeyCodeToSF(WParam, LParam);

		/*Logging.Log(CasaEngine::Trace,
			"mdf=%d, code=%d, key=%d\n", 
			event->nativeModifiers(), event->nativeScanCode(), event->nativeVirtualKey());*/

		m_pGameEditor->GetInput().OnEvent(Evt);
	}
}

void GameView::keyReleaseEvent( QKeyEvent *event)
{
	if (m_pGameEditor != nullptr)
	{
		CasaEngine::SystemEvent Evt;
		Evt.Type		= CasaEngine::SystemEvent::KeyReleased;
		Evt.Key.Alt     = (Qt::AltModifier & event->nativeModifiers()) != 0;//enum KeyboardModifier
		Evt.Key.Control = (Qt::ControlModifier & event->nativeModifiers()) != 0;
		Evt.Key.Shift   = (Qt::ShiftModifier & event->nativeModifiers()) != 0;
		Evt.Key.Code    = VirtualKeyCodeToSF(event->key()); // VirtualKeyCodeToSF(WParam, LParam);

		/*Logging.Log(CasaEngine::Trace,
			"mdf=%d, code=%d, key=%d\n", 
			event->nativeModifiers(), event->nativeScanCode(), event->nativeVirtualKey());*/

		m_pGameEditor->GetInput().OnEvent(Evt);
	}
}

void GameView::focusInEvent( QFocusEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

void GameView::focusOutEvent( QFocusEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

void GameView::enterEvent( QEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

void GameView::leaveEvent( QEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

void GameView::moveEvent( QMoveEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

void GameView::resizeEvent( QResizeEvent *event)
{
	if (m_pGameEditor != nullptr)
	{
		CasaEngine::SystemEvent systemEvent;

		systemEvent.Type = CasaEngine::SystemEvent::Resized;
		systemEvent.Size.Width = event->size().width();
		systemEvent.Size.Height = event->size().height();

		m_pGameEditor->OnEvent(systemEvent);
	}
}

void GameView::closeEvent( QCloseEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

void GameView::dragEnterEvent( QDragEnterEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

void GameView::dragMoveEvent( QDragMoveEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

void GameView::dragLeaveEvent( QDragLeaveEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

void GameView::dropEvent( QDropEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

void GameView::showEvent( QShowEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

void GameView::hideEvent( QHideEvent *event)
{
	//throw std::exception("The method or operation is not implemented.");
}

CasaEngine::Key::Code GameView::VirtualKeyCodeToSF(int val_)
{
	switch(val_) 
	{
	case Qt::Key_Escape: return CasaEngine::Key::Escape;
	case Qt::Key_Tab: return CasaEngine::Key::Tab;
	//case Qt::Key_Backtab: return CasaEngine::Key::Backtab;
	case Qt::Key_Backspace: return CasaEngine::Key::Back;
	case Qt::Key_Return: return CasaEngine::Key::Return;
	//case Qt::Key_Enter: return CasaEngine::Key::Enter;
	case Qt::Key_Insert: return CasaEngine::Key::Insert;
	case Qt::Key_Delete: return CasaEngine::Key::Delete;
	case Qt::Key_Pause: return CasaEngine::Key::Pause;
	//case Qt::Key_Print: return CasaEngine::Key::Print;
	//case Qt::Key_SysReq: return CasaEngine::Key::SysReq;
	//case Qt::Key_Clear: return CasaEngine::Key::Clear;
	case Qt::Key_Home: return CasaEngine::Key::Home;
	case Qt::Key_End: return CasaEngine::Key::End;
	case Qt::Key_Left: return CasaEngine::Key::Left;
	case Qt::Key_Up: return CasaEngine::Key::Up;
	case Qt::Key_Right: return CasaEngine::Key::Right;
	case Qt::Key_Down: return CasaEngine::Key::Down;
	case Qt::Key_PageUp: return CasaEngine::Key::PageUp;
	case Qt::Key_PageDown: return CasaEngine::Key::PageDown;
	case Qt::Key_Shift: return CasaEngine::Key::LShift;
	case Qt::Key_Control: return CasaEngine::Key::LControl;
	//case Qt::Key_Meta: return CasaEngine::Key::Meta:;
	case Qt::Key_Alt: return CasaEngine::Key::LAlt;
	//case Qt::Key_CapsLock: return CasaEngine::Key::CapsLock;
	//case Qt::Key_NumLock: return CasaEngine::Key::NumLock;
	//case Qt::Key_ScrollLock: return CasaEngine::Key::ScrollLock;
	case Qt::Key_F1: return CasaEngine::Key::F1;
	case Qt::Key_F2: return CasaEngine::Key::F2;
	case Qt::Key_F3: return CasaEngine::Key::F3;
	case Qt::Key_F4: return CasaEngine::Key::F4;
	case Qt::Key_F5: return CasaEngine::Key::F5;
	case Qt::Key_F6: return CasaEngine::Key::F6;
	case Qt::Key_F7: return CasaEngine::Key::F7;
	case Qt::Key_F8: return CasaEngine::Key::F8;
	case Qt::Key_F9: return CasaEngine::Key::F9;
	case Qt::Key_F10: return CasaEngine::Key::F10;
	case Qt::Key_F11: return CasaEngine::Key::F11;
	case Qt::Key_F12: return CasaEngine::Key::F12;
	case Qt::Key_F13: return CasaEngine::Key::F13;
	case Qt::Key_F14: return CasaEngine::Key::F14;
	case Qt::Key_F15: return CasaEngine::Key::F15;
	/*case Qt::Key_F16: return CasaEngine::Key::F16;
	case Qt::Key_F17: return CasaEngine::Key::F17;
	case Qt::Key_F18: return CasaEngine::Key::F18;
	case Qt::Key_F19: return CasaEngine::Key::F19;
	case Qt::Key_F20: return CasaEngine::Key::F20;
	case Qt::Key_F21: return CasaEngine::Key::F21;
	case Qt::Key_F22: return CasaEngine::Key::F22;
	case Qt::Key_F23: return CasaEngine::Key::F23;
	case Qt::Key_F24: return CasaEngine::Key::F24;
	case Qt::Key_F25: return CasaEngine::Key::F25;
	case Qt::Key_F26: return CasaEngine::Key::F26;
	case Qt::Key_F27: return CasaEngine::Key::F27;
	case Qt::Key_F28: return CasaEngine::Key::F28;
	case Qt::Key_F29: return CasaEngine::Key::F29;
	case Qt::Key_F30: return CasaEngine::Key::F30;
	case Qt::Key_F31: return CasaEngine::Key::F31;
	case Qt::Key_F32: return CasaEngine::Key::F32;
	case Qt::Key_F33: return CasaEngine::Key::F33;
	case Qt::Key_F34: return CasaEngine::Key::F34;
	case Qt::Key_F35: return CasaEngine::Key::F35;
	case Qt::Key_Super_L: return CasaEngine::Key::Escape;
	case Qt::Key_Super_R: return CasaEngine::Key::Escape;*/
	case Qt::Key_Menu: return CasaEngine::Key::Menu;
	/*case Qt::Key_Hyper_L: return CasaEngine::Key::Escape;
	case Qt::Key_Hyper_R: return CasaEngine::Key::Escape;
	case Qt::Key_Help: return CasaEngine::Key::Escape;
	case Qt::Key_Direction_L: return CasaEngine::Key::Escape;
	case Qt::Key_Direction_R: return CasaEngine::Key::Escape;*/
	case Qt::Key_Space: return CasaEngine::Key::Space;
	//case Qt::Key_Exclam: return CasaEngine::Key::Exclam;
	case Qt::Key_QuoteDbl: return CasaEngine::Key::Quote;
	case Qt::Key_NumberSign: return CasaEngine::Key::Dash;
	/*case Qt::Key_Dollar: return CasaEngine::Key::Escape;
	case Qt::Key_Percent: return CasaEngine::Key::Escape;
	case Qt::Key_Ampersand: return CasaEngine::Key::Escape;
	case Qt::Key_Apostrophe: return CasaEngine::Key::Escape;
	case Qt::Key_ParenLeft: return CasaEngine::Key::Escape;
	case Qt::Key_ParenRight: return CasaEngine::Key::Escape;*/
	case Qt::Key_Asterisk: return CasaEngine::Key::Multiply;
	case Qt::Key_Plus: return CasaEngine::Key::Add;
	case Qt::Key_Comma: return CasaEngine::Key::Comma;
	case Qt::Key_Minus: return CasaEngine::Key::Subtract;
	//case Qt::Key_Period: return CasaEngine::Key::Escape;
	case Qt::Key_Slash: return CasaEngine::Key::Slash;
	case Qt::Key_0: return CasaEngine::Key::Num0;
	case Qt::Key_1: return CasaEngine::Key::Num1;
	case Qt::Key_2: return CasaEngine::Key::Num2;
	case Qt::Key_3: return CasaEngine::Key::Num3;
	case Qt::Key_4: return CasaEngine::Key::Num4;
	case Qt::Key_5: return CasaEngine::Key::Num5;
	case Qt::Key_6: return CasaEngine::Key::Num6;
	case Qt::Key_7: return CasaEngine::Key::Num7;
	case Qt::Key_8: return CasaEngine::Key::Num8;
	case Qt::Key_9: return CasaEngine::Key::Num9;
	case Qt::Key_Colon: return CasaEngine::Key::SemiColon;
	case Qt::Key_Semicolon: return CasaEngine::Key::SemiColon;
	case Qt::Key_Less: return CasaEngine::Key::Subtract;
	case Qt::Key_Equal: return CasaEngine::Key::Equal;
	/*case Qt::Key_Greater: return CasaEngine::Key::Greater;
	case Qt::Key_Question: return CasaEngine::Key::Question;
	case Qt::Key_At: return CasaEngine::Key::At;*/
	case Qt::Key_A: return CasaEngine::Key::A;
	case Qt::Key_B: return CasaEngine::Key::B;
	case Qt::Key_C: return CasaEngine::Key::C;
	case Qt::Key_D: return CasaEngine::Key::D;
	case Qt::Key_E: return CasaEngine::Key::E;
	case Qt::Key_F: return CasaEngine::Key::F;
	case Qt::Key_G: return CasaEngine::Key::G;
	case Qt::Key_H: return CasaEngine::Key::H;
	case Qt::Key_I: return CasaEngine::Key::I;
	case Qt::Key_J: return CasaEngine::Key::J;
	case Qt::Key_K: return CasaEngine::Key::K;
	case Qt::Key_L: return CasaEngine::Key::L;
	case Qt::Key_M: return CasaEngine::Key::M;
	case Qt::Key_N: return CasaEngine::Key::N;
	case Qt::Key_O: return CasaEngine::Key::O;
	case Qt::Key_P: return CasaEngine::Key::P;
	case Qt::Key_Q: return CasaEngine::Key::Q;
	case Qt::Key_R: return CasaEngine::Key::R;
	case Qt::Key_S: return CasaEngine::Key::S;
	case Qt::Key_T: return CasaEngine::Key::T;
	case Qt::Key_U: return CasaEngine::Key::U;
	case Qt::Key_V: return CasaEngine::Key::V;
	case Qt::Key_W: return CasaEngine::Key::W;
	case Qt::Key_X: return CasaEngine::Key::X;
	case Qt::Key_Y: return CasaEngine::Key::Y;
	case Qt::Key_Z: return CasaEngine::Key::Z;
	case Qt::Key_BracketLeft: return CasaEngine::Key::LBracket;
	case Qt::Key_Backslash: return CasaEngine::Key::BackSlash;
	case Qt::Key_BracketRight: return CasaEngine::Key::RBracket;
	/*case Qt::Key_AsciiCircum: return CasaEngine::Key::Escape;
	case Qt::Key_Underscore: return CasaEngine::Key::Escape;
	case Qt::Key_QuoteLeft: return CasaEngine::Key::Escape;
	case Qt::Key_BraceLeft: return CasaEngine::Key::Escape;
	case Qt::Key_Bar: return CasaEngine::Key::Escape;
	case Qt::Key_BraceRight: return CasaEngine::Key::Escape;
	case Qt::Key_AsciiTilde: return CasaEngine::Key::Escape;*/
	/*
	case Qt::Key_nobreakspace: return CasaEngine::Key::Escape;
	case Qt::Key_exclamdown: return CasaEngine::Key::Escape;
	case Qt::Key_cent: return CasaEngine::Key::Escape;
	case Qt::Key_sterling: return CasaEngine::Key::Escape;
	case Qt::Key_currency: return CasaEngine::Key::Escape;
	case Qt::Key_yen: return CasaEngine::Key::Escape;
	case Qt::Key_brokenbar: return CasaEngine::Key::Escape;
	case Qt::Key_section: return CasaEngine::Key::Escape;
	case Qt::Key_diaeresis: return CasaEngine::Key::Escape;
	case Qt::Key_copyright: return CasaEngine::Key::Escape;
	case Qt::Key_ordfeminine: return CasaEngine::Key::Escape;
	case Qt::Key_guillemotleft: return CasaEngine::Key::Escape;
	case Qt::Key_notsign: return CasaEngine::Key::Escape;
	case Qt::Key_hyphen: return CasaEngine::Key::Escape;
	case Qt::Key_registered: return CasaEngine::Key::Escape;
	case Qt::Key_macron: return CasaEngine::Key::Escape;
	case Qt::Key_degree: return CasaEngine::Key::Escape;
	case Qt::Key_plusminus: return CasaEngine::Key::Escape;
	case Qt::Key_twosuperior: return CasaEngine::Key::Escape;
	case Qt::Key_threesuperior: return CasaEngine::Key::Escape;
	case Qt::Key_acute: return CasaEngine::Key::Escape;
	case Qt::Key_mu: return CasaEngine::Key::Escape;
	case Qt::Key_paragraph: return CasaEngine::Key::Escape;
	case Qt::Key_periodcentered: return CasaEngine::Key::Escape;
	case Qt::Key_cedilla: return CasaEngine::Key::Escape;
	case Qt::Key_onesuperior: return CasaEngine::Key::Escape;
	case Qt::Key_masculine: return CasaEngine::Key::Escape;
	case Qt::Key_guillemotright: return CasaEngine::Key::Escape;
	case Qt::Key_onequarter: return CasaEngine::Key::Escape;
	case Qt::Key_onehalf: return CasaEngine::Key::Escape;
	case Qt::Key_threequarters: return CasaEngine::Key::Escape;
	case Qt::Key_questiondown: return CasaEngine::Key::Escape;
	case Qt::Key_Agrave: return CasaEngine::Key::Escape;
	case Qt::Key_Aacute: return CasaEngine::Key::Escape;
	case Qt::Key_Acircumflex: return CasaEngine::Key::Escape;
	case Qt::Key_Atilde: return CasaEngine::Key::Escape;
	case Qt::Key_Adiaeresis: return CasaEngine::Key::Escape;
	case Qt::Key_Aring: return CasaEngine::Key::Escape;
	case Qt::Key_AE: return CasaEngine::Key::Escape;
	case Qt::Key_Ccedilla: return CasaEngine::Key::Escape;
	case Qt::Key_Egrave: return CasaEngine::Key::Escape;
	case Qt::Key_Eacute: return CasaEngine::Key::Escape;
	case Qt::Key_Ecircumflex: return CasaEngine::Key::Escape;
	case Qt::Key_Ediaeresis: return CasaEngine::Key::Escape;
	case Qt::Key_Igrave: return CasaEngine::Key::Escape;
	case Qt::Key_Iacute: return CasaEngine::Key::Escape;
	case Qt::Key_Icircumflex: return CasaEngine::Key::Escape;
	case Qt::Key_Idiaeresis: return CasaEngine::Key::Escape;
	case Qt::Key_ETH: return CasaEngine::Key::Escape;
	case Qt::Key_Ntilde: return CasaEngine::Key::Escape;
	case Qt::Key_Ograve: return CasaEngine::Key::Escape;
	case Qt::Key_Oacute: return CasaEngine::Key::Escape;
	case Qt::Key_Ocircumflex: return CasaEngine::Key::Escape;
	case Qt::Key_Otilde: return CasaEngine::Key::Escape;
	case Qt::Key_Odiaeresis: return CasaEngine::Key::Escape;
	case Qt::Key_multiply: return CasaEngine::Key::Escape;
	case Qt::Key_Ooblique: return CasaEngine::Key::Escape;
	case Qt::Key_Ugrave: return CasaEngine::Key::Escape;
	case Qt::Key_Uacute: return CasaEngine::Key::Escape;
	case Qt::Key_Ucircumflex: return CasaEngine::Key::Escape;
	case Qt::Key_Udiaeresis: return CasaEngine::Key::Escape;
	case Qt::Key_Yacute: return CasaEngine::Key::Escape;
	case Qt::Key_THORN: return CasaEngine::Key::Escape;
	case Qt::Key_ssharp: return CasaEngine::Key::Escape;
	case Qt::Key_division: return CasaEngine::Key::Escape;
	case Qt::Key_ydiaeresis: return CasaEngine::Key::Escape;
	
	// International input method support (X keycode - 0xEE00, the
	// definition follows Qt/Embedded 2.3.7) Only interesting if
	// you are writing your own input method

	// International & multi-key character composition
	case Qt::Key_AltGr              : return CasaEngine::Key::Escape;
	case Qt::Key_Multi_key          : return CasaEngine::Key::Escape;
	case Qt::Key_Codeinput          : return CasaEngine::Key::Escape;
	case Qt::Key_SingleCandidate    : return CasaEngine::Key::Escape;
	case Qt::Key_MultipleCandidate  : return CasaEngine::Key::Escape;
	case Qt::Key_PreviousCandidate  : return CasaEngine::Key::Escape;

	// Misc Functions
	case Qt::Key_Mode_switch        : return CasaEngine::Key::Escape;
	//Key_script_switch      : return CasaEngine::Key::Escape;

	// Japanese keyboard support
	case Qt::Key_Kanji              : return CasaEngine::Key::Escape;
	case Qt::Key_Muhenkan           : return CasaEngine::Key::Escape;
	//Key_Henkan_Mode        : return CasaEngine::Key::Escape;
	case Qt::Key_Henkan             : return CasaEngine::Key::Escape;
	case Qt::Key_Romaji             : return CasaEngine::Key::Escape;
	case Qt::Key_Hiragana           : return CasaEngine::Key::Escape;
	case Qt::Key_Katakana           : return CasaEngine::Key::Escape;
	case Qt::Key_Hiragana_Katakana  : return CasaEngine::Key::Escape;
	case Qt::Key_Zenkaku            : return CasaEngine::Key::Escape;
	case Qt::Key_Hankaku            : return CasaEngine::Key::Escape;
	case Qt::Key_Zenkaku_Hankaku    : return CasaEngine::Key::Escape;
	case Qt::Key_Touroku            : return CasaEngine::Key::Escape;
	case Qt::Key_Massyo             : return CasaEngine::Key::Escape;
	case Qt::Key_Kana_Lock          : return CasaEngine::Key::Escape;
	case Qt::Key_Kana_Shift         : return CasaEngine::Key::Escape;
	case Qt::Key_Eisu_Shift         : return CasaEngine::Key::Escape;
	case Qt::Key_Eisu_toggle        : return CasaEngine::Key::Escape;
	//Key_Kanji_Bangou       : return CasaEngine::Key::Escape;
	//Key_Zen_Koho           : return CasaEngine::Key::Escape;
	//Key_Mae_Koho           : return CasaEngine::Key::Escape;
	
	// Korean keyboard support
	//
	// In fact, many Korean users need only 2 keys, Key_Hangul and
	// Key_Hangul_Hanja. But rest of the keys are good for future.
	
	case Qt::Key_Hangul             : return CasaEngine::Key::Escape;
	case Qt::Key_Hangul_Start       : return CasaEngine::Key::Escape;
	case Qt::Key_Hangul_End         : return CasaEngine::Key::Escape;
	case Qt::Key_Hangul_Hanja       : return CasaEngine::Key::Escape;
	case Qt::Key_Hangul_Jamo        : return CasaEngine::Key::Escape;
	case Qt::Key_Hangul_Romaja      : return CasaEngine::Key::Escape;
	//Key_Hangul_Codeinput   : return CasaEngine::Key::Escape;
	case Qt::Key_Hangul_Jeonja      : return CasaEngine::Key::Escape;
	case Qt::Key_Hangul_Banja       : return CasaEngine::Key::Escape;
	case Qt::Key_Hangul_PreHanja    : return CasaEngine::Key::Escape;
	case Qt::Key_Hangul_PostHanja   : return CasaEngine::Key::Escape;
	//Key_Hangul_SingleCandidate  : return CasaEngine::Key::Escape;
	//Key_Hangul_MultipleCandidate: return CasaEngine::Key::Escape;
	//Key_Hangul_PreviousCandidate: return CasaEngine::Key::Escape;
	case Qt::Key_Hangul_Special     : return CasaEngine::Key::Escape;
	//Key_Hangul_switch      : return CasaEngine::Key::Escape;
	case 
	// dead keys (X keycode - 0xED00 to avoid the conflict)
	case Qt::Key_Dead_Grave         : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Acute         : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Circumflex    : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Tilde         : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Macron        : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Breve         : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Abovedot      : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Diaeresis     : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Abovering     : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Doubleacute   : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Caron         : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Cedilla       : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Ogonek        : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Iota          : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Voiced_Sound  : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Semivoiced_Sound: return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Belowdot      : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Hook          : return CasaEngine::Key::Escape;
	case Qt::Key_Dead_Horn          : return CasaEngine::Key::Escape;
	
	// multimedia/internet keys - ignored by default - see QKeyEvent c'tor
	case Qt::Key_Back : return CasaEngine::Key::Escape;
	case Qt::Key_Forward : return CasaEngine::Key::Escape;
	case Qt::Key_Stop : return CasaEngine::Key::Escape;
	case Qt::Key_Refresh : return CasaEngine::Key::Escape;
	case Qt::Key_VolumeDown: return CasaEngine::Key::Escape;
	case Qt::Key_VolumeMute : return CasaEngine::Key::Escape;
	case Qt::Key_VolumeUp: return CasaEngine::Key::Escape;
	case Qt::Key_BassBoost: return CasaEngine::Key::Escape;
	case Qt::Key_BassUp: return CasaEngine::Key::Escape;
	case Qt::Key_BassDown: return CasaEngine::Key::Escape;
	case Qt::Key_TrebleUp: return CasaEngine::Key::Escape;
	case Qt::Key_TrebleDown: return CasaEngine::Key::Escape;
	case Qt::Key_MediaPlay : return CasaEngine::Key::Escape;
	case Qt::Key_MediaStop : return CasaEngine::Key::Escape;
	case Qt::Key_MediaPrevious : return CasaEngine::Key::Escape;
	case Qt::Key_MediaNext : return CasaEngine::Key::Escape;
	case Qt::Key_MediaRecord: return CasaEngine::Key::Escape;
	case Qt::Key_MediaPause: return CasaEngine::Key::Escape;
	case Qt::Key_MediaTogglePlayPause: return CasaEngine::Key::Escape;
	case Qt::Key_HomePage : return CasaEngine::Key::Escape;
	case Qt::Key_Favorites : return CasaEngine::Key::Escape;
	case Qt::Key_Search : return CasaEngine::Key::Escape;
	case Qt::Key_Standby: return CasaEngine::Key::Escape;
	case Qt::Key_OpenUrl: return CasaEngine::Key::Escape;
	case Qt::Key_LaunchMail : return CasaEngine::Key::Escape;
	case Qt::Key_LaunchMedia: return CasaEngine::Key::Escape;
	case Qt::Key_Launch0 : return CasaEngine::Key::Escape;
	case Qt::Key_Launch1 : return CasaEngine::Key::Escape;
	case Qt::Key_Launch2 : return CasaEngine::Key::Escape;
	case Qt::Key_Launch3 : return CasaEngine::Key::Escape;
	case Qt::Key_Launch4 : return CasaEngine::Key::Escape;
	case Qt::Key_Launch5 : return CasaEngine::Key::Escape;
	case Qt::Key_Launch6 : return CasaEngine::Key::Escape;
	case Qt::Key_Launch7 : return CasaEngine::Key::Escape;
	case Qt::Key_Launch8 : return CasaEngine::Key::Escape;
	case Qt::Key_Launch9 : return CasaEngine::Key::Escape;
	case Qt::Key_LaunchA : return CasaEngine::Key::Escape;
	case Qt::Key_LaunchB : return CasaEngine::Key::Escape;
	case Qt::Key_LaunchC : return CasaEngine::Key::Escape;
	case Qt::Key_LaunchD : return CasaEngine::Key::Escape;
	case Qt::Key_LaunchE : return CasaEngine::Key::Escape;
	case Qt::Key_LaunchF : return CasaEngine::Key::Escape;
	case Qt::Key_MonBrightnessUp: return CasaEngine::Key::Escape;
	case Qt::Key_MonBrightnessDown: return CasaEngine::Key::Escape;
	case Qt::Key_KeyboardLightOnOff: return CasaEngine::Key::Escape;
	case Qt::Key_KeyboardBrightnessUp: return CasaEngine::Key::Escape;
	case Qt::Key_KeyboardBrightnessDown: return CasaEngine::Key::Escape;
	case Qt::Key_PowerOff: return CasaEngine::Key::Escape;
	case Qt::Key_WakeUp: return CasaEngine::Key::Escape;
	case Qt::Key_Eject: return CasaEngine::Key::Escape;
	case Qt::Key_ScreenSaver: return CasaEngine::Key::Escape;
	case Qt::Key_WWW: return CasaEngine::Key::Escape;
	case Qt::Key_Memo: return CasaEngine::Key::Escape;
	case Qt::Key_LightBulb: return CasaEngine::Key::Escape;
	case Qt::Key_Shop: return CasaEngine::Key::Escape;
	case Qt::Key_History: return CasaEngine::Key::Escape;
	case Qt::Key_AddFavorite: return CasaEngine::Key::Escape;
	case Qt::Key_HotLinks: return CasaEngine::Key::Escape;
	case Qt::Key_BrightnessAdjust: return CasaEngine::Key::Escape;
	case Qt::Key_Finance: return CasaEngine::Key::Escape;
	case Qt::Key_Community: return CasaEngine::Key::Escape;
	case Qt::Key_AudioRewind: return CasaEngine::Key::Escape;
	case Qt::Key_BackForward: return CasaEngine::Key::Escape;
	case Qt::Key_ApplicationLeft: return CasaEngine::Key::Escape;
	case Qt::Key_ApplicationRight: return CasaEngine::Key::Escape;
	case Qt::Key_Book: return CasaEngine::Key::Escape;
	case Qt::Key_CD: return CasaEngine::Key::Escape;
	case Qt::Key_Calculator: return CasaEngine::Key::Escape;
	case Qt::Key_ToDoList: return CasaEngine::Key::Escape;
	case Qt::Key_ClearGrab: return CasaEngine::Key::Escape;
	case Qt::Key_Close: return CasaEngine::Key::Escape;
	case Qt::Key_Copy: return CasaEngine::Key::Escape;
	case Qt::Key_Cut: return CasaEngine::Key::Escape;
	case Qt::Key_Display: return CasaEngine::Key::Escape;
	case Qt::Key_DOS: return CasaEngine::Key::Escape;
	case Qt::Key_Documents: return CasaEngine::Key::Escape;
	case Qt::Key_Excel: return CasaEngine::Key::Escape;
	case Qt::Key_Explorer: return CasaEngine::Key::Escape;
	case Qt::Key_Game: return CasaEngine::Key::Escape;
	case Qt::Key_Go: return CasaEngine::Key::Escape;
	case Qt::Key_iTouch: return CasaEngine::Key::Escape;
	case Qt::Key_LogOff: return CasaEngine::Key::Escape;
	case Qt::Key_Market: return CasaEngine::Key::Escape;
	case Qt::Key_Meeting: return CasaEngine::Key::Escape;
	case Qt::Key_MenuKB: return CasaEngine::Key::Escape;
	case Qt::Key_MenuPB: return CasaEngine::Key::Escape;
	case Qt::Key_MySites: return CasaEngine::Key::Escape;
	case Qt::Key_News: return CasaEngine::Key::Escape;
	case Qt::Key_OfficeHome: return CasaEngine::Key::Escape;
	case Qt::Key_Option: return CasaEngine::Key::Escape;
	case Qt::Key_Paste: return CasaEngine::Key::Escape;
	case Qt::Key_Phone: return CasaEngine::Key::Escape;
	case Qt::Key_Calendar: return CasaEngine::Key::Escape;
	case Qt::Key_Reply: return CasaEngine::Key::Escape;
	case Qt::Key_Reload: return CasaEngine::Key::Escape;
	case Qt::Key_RotateWindows: return CasaEngine::Key::Escape;
	case Qt::Key_RotationPB: return CasaEngine::Key::Escape;
	case Qt::Key_RotationKB: return CasaEngine::Key::Escape;
	case Qt::Key_Save: return CasaEngine::Key::Escape;
	case Qt::Key_Send: return CasaEngine::Key::Escape;
	case Qt::Key_Spell: return CasaEngine::Key::Escape;
	case Qt::Key_SplitScreen: return CasaEngine::Key::Escape;
	case Qt::Key_Support: return CasaEngine::Key::Escape;
	case Qt::Key_TaskPane: return CasaEngine::Key::Escape;
	case Qt::Key_Terminal: return CasaEngine::Key::Escape;
	case Qt::Key_Tools: return CasaEngine::Key::Escape;
	case Qt::Key_Travel: return CasaEngine::Key::Escape;
	case Qt::Key_Video: return CasaEngine::Key::Escape;
	case Qt::Key_Word: return CasaEngine::Key::Escape;
	case Qt::Key_Xfer: return CasaEngine::Key::Escape;
	case Qt::Key_ZoomIn: return CasaEngine::Key::Escape;
	case Qt::Key_ZoomOut: return CasaEngine::Key::Escape;
	case Qt::Key_Away: return CasaEngine::Key::Escape;
	case Qt::Key_Messenger: return CasaEngine::Key::Escape;
	case Qt::Key_WebCam: return CasaEngine::Key::Escape;
	case Qt::Key_MailForward: return CasaEngine::Key::Escape;
	case Qt::Key_Pictures: return CasaEngine::Key::Escape;
	case Qt::Key_Music: return CasaEngine::Key::Escape;
	case Qt::Key_Battery: return CasaEngine::Key::Escape;
	case Qt::Key_Bluetooth: return CasaEngine::Key::Escape;
	case Qt::Key_WLAN: return CasaEngine::Key::Escape;
	case Qt::Key_UWB: return CasaEngine::Key::Escape;
	case Qt::Key_AudioForward: return CasaEngine::Key::Escape;
	case Qt::Key_AudioRepeat: return CasaEngine::Key::Escape;
	case Qt::Key_AudioRandomPlay: return CasaEngine::Key::Escape;
	case Qt::Key_Subtitle: return CasaEngine::Key::Escape;
	case Qt::Key_AudioCycleTrack: return CasaEngine::Key::Escape;
	case Qt::Key_Time: return CasaEngine::Key::Escape;
	case Qt::Key_Hibernate: return CasaEngine::Key::Escape;
	case Qt::Key_View: return CasaEngine::Key::Escape;
	case Qt::Key_TopMenu: return CasaEngine::Key::Escape;
	case Qt::Key_PowerDown: return CasaEngine::Key::Escape;
	case Qt::Key_Suspend: return CasaEngine::Key::Escape;
	case Qt::Key_ContrastAdjust: return CasaEngine::Key::Escape;
	 
	case Qt::Key_LaunchG : return CasaEngine::Key::Escape;
	case Qt::Key_LaunchH : return CasaEngine::Key::Escape;
	 
	case Qt::Key_TouchpadToggle: return CasaEngine::Key::Escape;
	case Qt::Key_TouchpadOn: return CasaEngine::Key::Escape;
	case Qt::Key_TouchpadOff: return CasaEngine::Key::Escape;
	 
	case Qt::Key_MicMute: return CasaEngine::Key::Escape;
	 
	case Qt::Key_Red: return CasaEngine::Key::Escape;
	case Qt::Key_Green: return CasaEngine::Key::Escape;
	case Qt::Key_Yellow: return CasaEngine::Key::Escape;
	case Qt::Key_Blue: return CasaEngine::Key::Escape;
	 
	case Qt::Key_ChannelUp: return CasaEngine::Key::Escape;
	case Qt::Key_ChannelDown: return CasaEngine::Key::Escape;
	 
	case Qt::Key_Guide   : return CasaEngine::Key::Escape;
	case Qt::Key_Info    : return CasaEngine::Key::Escape;
	case Qt::Key_Settings: return CasaEngine::Key::Escape;
	 
	case Qt::Key_MediaLast: return CasaEngine::Key::Escape;
	 
	// Keypad navigation keys
	case Qt::Key_Select: return CasaEngine::Key::Escape;
	case Qt::Key_Yes: return CasaEngine::Key::Escape;
	case Qt::Key_No: return CasaEngine::Key::Escape;
	 
	// Newer misc keys
	case Qt::Key_Cancel : return CasaEngine::Key::Escape;
	case Qt::Key_Printer: return CasaEngine::Key::Escape;
	case Qt::Key_Execute: return CasaEngine::Key::Escape;
	case Qt::Key_Sleep  : return CasaEngine::Key::Escape;
	case Qt::Key_Play   : return CasaEngine::Key::Escape;
	case Qt::Key_Zoom   : return CasaEngine::Key::Escape;
	//Key_Jisho  : return CasaEngine::Key::Escape;
	//Key_Oyayubi_Left: return CasaEngine::Key::Escape;
	//Key_Oyayubi_Right: return CasaEngine::Key::Escape;
	case Qt::Key_Exit   : return CasaEngine::Key::Escape;
	 
	// Device keys
	case Qt::Key_Context1: return CasaEngine::Key::Escape;
	case Qt::Key_Context2: return CasaEngine::Key::Escape;
	case Qt::Key_Context3: return CasaEngine::Key::Escape;
	case Qt::Key_Context4: return CasaEngine::Key::Escape;
	case Qt::Key_Call: return CasaEngine::Key::Escape;
	case Qt::Key_Hangup: return CasaEngine::Key::Escape;
	case Qt::Key_Flip: return CasaEngine::Key::Escape;
	case Qt::Key_ToggleCallHangup: return CasaEngine::Key::Escape;
	case Qt::Key_VoiceDial: return CasaEngine::Key::Escape;
	case Qt::Key_LastNumberRedial: return CasaEngine::Key::Escape;
	
	case Qt::Key_Camera: return CasaEngine::Key::Escape;
	case Qt::Key_CameraFocus: return CasaEngine::Key::Escape;
	
	case Qt::Key_unknown: return CasaEngine::Key::Escape;*/
	}

	return CasaEngine::Key::Code(0);
}