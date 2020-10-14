#pragma once

namespace Emerald
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define EM_KEY_SPACE           ::Emerald::Key::Space
#define EM_KEY_APOSTROPHE      ::Emerald::Key::Apostrophe    /* ' */
#define EM_KEY_COMMA           ::Emerald::Key::Comma         /* , */
#define EM_KEY_MINUS           ::Emerald::Key::Minus         /* - */
#define EM_KEY_PERIOD          ::Emerald::Key::Period        /* . */
#define EM_KEY_SLASH           ::Emerald::Key::Slash         /* / */
#define EM_KEY_0               ::Emerald::Key::D0
#define EM_KEY_1               ::Emerald::Key::D1
#define EM_KEY_2               ::Emerald::Key::D2
#define EM_KEY_3               ::Emerald::Key::D3
#define EM_KEY_4               ::Emerald::Key::D4
#define EM_KEY_5               ::Emerald::Key::D5
#define EM_KEY_6               ::Emerald::Key::D6
#define EM_KEY_7               ::Emerald::Key::D7
#define EM_KEY_8               ::Emerald::Key::D8
#define EM_KEY_9               ::Emerald::Key::D9
#define EM_KEY_SEMICOLON       ::Emerald::Key::Semicolon     /* ; */
#define EM_KEY_EQUAL           ::Emerald::Key::Equal         /* = */
#define EM_KEY_A               ::Emerald::Key::A
#define EM_KEY_B               ::Emerald::Key::B
#define EM_KEY_C               ::Emerald::Key::C
#define EM_KEY_D               ::Emerald::Key::D
#define EM_KEY_E               ::Emerald::Key::E
#define EM_KEY_F               ::Emerald::Key::F
#define EM_KEY_G               ::Emerald::Key::G
#define EM_KEY_H               ::Emerald::Key::H
#define EM_KEY_I               ::Emerald::Key::I
#define EM_KEY_J               ::Emerald::Key::J
#define EM_KEY_K               ::Emerald::Key::K
#define EM_KEY_L               ::Emerald::Key::L
#define EM_KEY_M               ::Emerald::Key::M
#define EM_KEY_N               ::Emerald::Key::N
#define EM_KEY_O               ::Emerald::Key::O
#define EM_KEY_P               ::Emerald::Key::P
#define EM_KEY_Q               ::Emerald::Key::Q
#define EM_KEY_R               ::Emerald::Key::R
#define EM_KEY_S               ::Emerald::Key::S
#define EM_KEY_T               ::Emerald::Key::T
#define EM_KEY_U               ::Emerald::Key::U
#define EM_KEY_V               ::Emerald::Key::V
#define EM_KEY_W               ::Emerald::Key::W
#define EM_KEY_X               ::Emerald::Key::X
#define EM_KEY_Y               ::Emerald::Key::Y
#define EM_KEY_Z               ::Emerald::Key::Z
#define EM_KEY_LEFT_BRACKET    ::Emerald::Key::LeftBracket   /* [ */
#define EM_KEY_BACKSLASH       ::Emerald::Key::Backslash     /* \ */
#define EM_KEY_RIGHT_BRACKET   ::Emerald::Key::RightBracket  /* ] */
#define EM_KEY_GRAVE_ACCENT    ::Emerald::Key::GraveAccent   /* ` */
#define EM_KEY_WORLD_1         ::Emerald::Key::World1        /* non-US #1 */
#define EM_KEY_WORLD_2         ::Emerald::Key::World2        /* non-US #2 */

/* Function keys */
#define EM_KEY_ESCAPE          ::Emerald::Key::Escape
#define EM_KEY_ENTER           ::Emerald::Key::Enter
#define EM_KEY_TAB             ::Emerald::Key::Tab
#define EM_KEY_BACKSPACE       ::Emerald::Key::Backspace
#define EM_KEY_INSERT          ::Emerald::Key::Insert
#define EM_KEY_DELETE          ::Emerald::Key::Delete
#define EM_KEY_RIGHT           ::Emerald::Key::Right
#define EM_KEY_LEFT            ::Emerald::Key::Left
#define EM_KEY_DOWN            ::Emerald::Key::Down
#define EM_KEY_UP              ::Emerald::Key::Up
#define EM_KEY_PAGE_UP         ::Emerald::Key::PageUp
#define EM_KEY_PAGE_DOWN       ::Emerald::Key::PageDown
#define EM_KEY_HOME            ::Emerald::Key::Home
#define EM_KEY_END             ::Emerald::Key::End
#define EM_KEY_CAPS_LOCK       ::Emerald::Key::CapsLock
#define EM_KEY_SCROLL_LOCK     ::Emerald::Key::ScrollLock
#define EM_KEY_NUM_LOCK        ::Emerald::Key::NumLock
#define EM_KEY_PRINT_SCREEN    ::Emerald::Key::PrintScreen
#define EM_KEY_PAUSE           ::Emerald::Key::Pause
#define EM_KEY_F1              ::Emerald::Key::F1
#define EM_KEY_F2              ::Emerald::Key::F2
#define EM_KEY_F3              ::Emerald::Key::F3
#define EM_KEY_F4              ::Emerald::Key::F4
#define EM_KEY_F5              ::Emerald::Key::F5
#define EM_KEY_F6              ::Emerald::Key::F6
#define EM_KEY_F7              ::Emerald::Key::F7
#define EM_KEY_F8              ::Emerald::Key::F8
#define EM_KEY_F9              ::Emerald::Key::F9
#define EM_KEY_F10             ::Emerald::Key::F10
#define EM_KEY_F11             ::Emerald::Key::F11
#define EM_KEY_F12             ::Emerald::Key::F12
#define EM_KEY_F13             ::Emerald::Key::F13
#define EM_KEY_F14             ::Emerald::Key::F14
#define EM_KEY_F15             ::Emerald::Key::F15
#define EM_KEY_F16             ::Emerald::Key::F16
#define EM_KEY_F17             ::Emerald::Key::F17
#define EM_KEY_F18             ::Emerald::Key::F18
#define EM_KEY_F19             ::Emerald::Key::F19
#define EM_KEY_F20             ::Emerald::Key::F20
#define EM_KEY_F21             ::Emerald::Key::F21
#define EM_KEY_F22             ::Emerald::Key::F22
#define EM_KEY_F23             ::Emerald::Key::F23
#define EM_KEY_F24             ::Emerald::Key::F24
#define EM_KEY_F25             ::Emerald::Key::F25

/* Keypad */
#define EM_KEY_KP_0            ::Emerald::Key::KP0
#define EM_KEY_KP_1            ::Emerald::Key::KP1
#define EM_KEY_KP_2            ::Emerald::Key::KP2
#define EM_KEY_KP_3            ::Emerald::Key::KP3
#define EM_KEY_KP_4            ::Emerald::Key::KP4
#define EM_KEY_KP_5            ::Emerald::Key::KP5
#define EM_KEY_KP_6            ::Emerald::Key::KP6
#define EM_KEY_KP_7            ::Emerald::Key::KP7
#define EM_KEY_KP_8            ::Emerald::Key::KP8
#define EM_KEY_KP_9            ::Emerald::Key::KP9
#define EM_KEY_KP_DECIMAL      ::Emerald::Key::KPDecimal
#define EM_KEY_KP_DIVIDE       ::Emerald::Key::KPDivide
#define EM_KEY_KP_MULTIPLY     ::Emerald::Key::KPMultiply
#define EM_KEY_KP_SUBTRACT     ::Emerald::Key::KPSubtract
#define EM_KEY_KP_ADD          ::Emerald::Key::KPAdd
#define EM_KEY_KP_ENTER        ::Emerald::Key::KPEnter
#define EM_KEY_KP_EQUAL        ::Emerald::Key::KPEqual

#define EM_KEY_LEFT_SHIFT      ::Emerald::Key::LeftShift
#define EM_KEY_LEFT_CONTROL    ::Emerald::Key::LeftControl
#define EM_KEY_LEFT_ALT        ::Emerald::Key::LeftAlt
#define EM_KEY_LEFT_SUPER      ::Emerald::Key::LeftSuper
#define EM_KEY_RIGHT_SHIFT     ::Emerald::Key::RightShift
#define EM_KEY_RIGHT_CONTROL   ::Emerald::Key::RightControl
#define EM_KEY_RIGHT_ALT       ::Emerald::Key::RightAlt
#define EM_KEY_RIGHT_SUPER     ::Emerald::Key::RightSuper
#define EM_KEY_MENU            ::Emerald::Key::Menu