#include "input.h"


const char* const KeyNames[] = {
	"None",
	"Mouse 1",
	"Mouse 2",
	"Cancel",
	"Mouse 2",
	"Mouse 4",
	"Mouse 5",
	"Unknown",
	"Back",
	"Tab",
	"Unknown",
	"Unknown",
	"Clear",
	"Return",
	"Unknown",
	"Unknown",
	"Shift",
	"Control",
	"Menu",
	"Pause",
	"Capital",
	"Kana",
	"Unknown",
	"Junja",
	"Final",
	"Kanji",
	"Unknown",
	"Esc",
	"Convert",
	"VK_NONCONVERT",
	"VK_ACCEPT",
	"VK_MODECHANGE",
	"VK_SPACE",
	"VK_PRIOR",
	"VK_NEXT",
	"VK_END",
	"VK_HOME",
	"VK_LEFT",
	"VK_UP",
	"VK_RIGHT",
	"VK_DOWN",
	"VK_SELECT",
	"VK_PRINT",
	"VK_EXECUTE",
	"VK_SNAPSHOT",
	"VK_INSERT",
	"VK_DELETE",
	"VK_HELP",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"VK_LWIN",
	"VK_RWIN",
	"VK_APPS",
	"Unknown",
	"VK_SLEEP",
	"VK_NUMPAD0",
	"VK_NUMPAD1",
	"VK_NUMPAD2",
	"VK_NUMPAD3",
	"VK_NUMPAD4",
	"VK_NUMPAD5",
	"VK_NUMPAD6",
	"VK_NUMPAD7",
	"VK_NUMPAD8",
	"VK_NUMPAD9",
	"VK_MULTIPLY",
	"VK_ADD",
	"VK_SEPARATOR",
	"VK_SUBTRACT",
	"VK_DECIMAL",
	"VK_DIVIDE",
	"VK_F1",
	"VK_F2",
	"VK_F3",
	"VK_F4",
	"VK_F5",
	"VK_F6",
	"VK_F7",
	"VK_F8",
	"VK_F9",
	"VK_F10",
	"VK_F11",
	"VK_F12",
	"VK_F13",
	"VK_F14",
	"VK_F15",
	"VK_F16",
	"VK_F17",
	"VK_F18",
	"VK_F19",
	"VK_F20",
	"VK_F21",
	"VK_F22",
	"VK_F23",
	"VK_F24",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Numlock",
	"VK_SCROLL",
	"VK_OEM_NEC_EQUAL",
	"VK_OEM_FJ_MASSHOU",
	"VK_OEM_FJ_TOUROKU",
	"VK_OEM_FJ_LOYA",
	"VK_OEM_FJ_ROYA",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"LShift",
	"RShift",
	"LControl",
	"RControl",
	"LMenu",
	"RMenu"
};

namespace input
{
	HWND m_window = NULL;
	WNDPROC m_original_wndproc = nullptr;

	char m_last_char;
	std::array<key_info_t, 256> m_key_info{};

	mouse_info_t m_mouse_info;

	BOOL CALLBACK enum_windows(HWND hWnd, LPARAM lParam)
	{
		auto process_id = DWORD{};
		GetWindowThreadProcessId(hWnd, &process_id);

		// Ignore other processes
		if (process_id != lParam)
			return true;

		if (hWnd == GetConsoleWindow())
			return true;

		//if ( GetWindow( hWnd, GW_OWNER ) != 0 )
		//	return true;

		//if ( !IsWindowVisible( hWnd ) )
		//	return true;

		return (m_window = hWnd) == NULL;
	}

	void init(HWND window)
	{
	
	}

	void init(std::wstring_view window)
	{
		
	}

	void undo()
	{
		if (m_original_wndproc)
			SetWindowLongPtrW(m_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_original_wndproc));

		m_original_wndproc = NULL;
	}

	bool handle_mouse(const UINT msg)
	{
		switch (msg)
		{
			/// Left mouse button
		case WM_LBUTTONDOWN:
		case WM_LBUTTONDBLCLK:
			if (m_mouse_info.m_state == e_state::IDLE)
				m_mouse_info.m_state = e_state::PRESSED;
			return true;
		case WM_LBUTTONUP:
			m_mouse_info.m_state = e_state::IDLE;
			return true;

			/// Right mouse button
		case WM_RBUTTONDOWN:
		case WM_RBUTTONDBLCLK:
			if (m_mouse_info.m_state_right == e_state::IDLE)
				m_mouse_info.m_state_right = e_state::PRESSED;
			return true;
		case WM_RBUTTONUP:
			m_mouse_info.m_state_right = e_state::IDLE;
			return true;
		default:
			break;
		}

		/// Mouse has been pressed for more than 1 input tick
		if (m_mouse_info.m_state == e_state::PRESSED)
			m_mouse_info.m_state = e_state::HELD;

		if (m_mouse_info.m_state_right == e_state::PRESSED)
			m_mouse_info.m_state_right = e_state::HELD;

		return msg == WM_MOUSEMOVE || msg == WM_NCMOUSEMOVE;
	}

	bool handle_keyboard(const UINT msg, const WPARAM param)
	{
		auto changed_state = false;

		for (auto i = 0; i < 256; i++)
		{
			if (m_key_info.at(i).m_state == e_state::PRESSED)
			{
				m_key_info.at(i).m_state = e_state::HELD;
				changed_state = true;
			}
		}

		switch (msg)
		{
			/// Input character
		case WM_CHAR:
			if (param > 0 && param < 0x10000)
				m_last_char = static_cast<char>(param);
			return true;

			/// "Normal" keys
		case WM_KEYDOWN:
			if (param >= 0 && param < 256)
				m_key_info.at(param).m_state = e_state::PRESSED;
			return true;
		case WM_KEYUP:
			if (param >= 0 && param < 256)
			{
				m_key_info.at(param).m_state = e_state::IDLE;
			}
			return true;

			/// Side mouse buttons
		case WM_XBUTTONDOWN:
		case WM_XBUTTONDBLCLK:
			if (GET_XBUTTON_WPARAM(param) & XBUTTON1)
				m_key_info.at(VK_XBUTTON1).m_state = e_state::PRESSED;
			else if (GET_XBUTTON_WPARAM(param) & XBUTTON2)
				m_key_info.at(VK_XBUTTON2).m_state = e_state::PRESSED;
			return true;
		case WM_XBUTTONUP:
			if (GET_XBUTTON_WPARAM(param) & XBUTTON1)
				m_key_info.at(VK_XBUTTON1).m_state = e_state::IDLE;
			else if (GET_XBUTTON_WPARAM(param) & XBUTTON2)
				m_key_info.at(VK_XBUTTON2).m_state = e_state::IDLE;
			return true;

			/// System keys
		case WM_SYSKEYDOWN:
			if (param >= 0 && param < 256)
				m_key_info.at(param).m_state = e_state::PRESSED;
			return true;
		case WM_SYSKEYUP:
			if (param >= 0 && param < 256)
				m_key_info.at(param).m_state = e_state::IDLE;
			return true;

			/// Middle button
		case WM_MBUTTONDOWN:
		case WM_MBUTTONDBLCLK:
			m_key_info.at(VK_MBUTTON).m_state = e_state::PRESSED;
			return true;
		case WM_MBUTTONUP:
			m_key_info.at(VK_MBUTTON).m_state = e_state::IDLE;
			return true;

			/// Left mouse button
		case WM_LBUTTONDOWN:
		case WM_LBUTTONDBLCLK:
			m_key_info.at(VK_LBUTTON).m_state = e_state::PRESSED;
			return true;
		case WM_LBUTTONUP:
			m_key_info.at(VK_LBUTTON).m_state = e_state::IDLE;
			return true;

			/// Right mouse button
		case WM_RBUTTONDOWN:
		case WM_RBUTTONDBLCLK:
			m_key_info.at(VK_RBUTTON).m_state = e_state::PRESSED;
			return true;
		case WM_RBUTTONUP:
			m_key_info.at(VK_RBUTTON).m_state = e_state::IDLE;
			return true;

			/// Mouse wheel
		case WM_MOUSEWHEEL:
			m_mouse_info.m_scroll = GET_WHEEL_DELTA_WPARAM(param) / WHEEL_DELTA;
			return true;
		default:;
		}

		return changed_state;
	}

	/// Mouse info
	void update_mouse()
	{
		POINT p;
		if (!GetCursorPos(&p))
			return;

		ScreenToClient(m_window, &p);

		m_mouse_info.m_pos = {
			static_cast<float>(p.x),
			static_cast<float>(p.y) };
	}

	mouse_info_t& get_mouse()
	{
		return m_mouse_info;
	}

	void reset_mouse()
	{
		m_mouse_info.m_state = e_state::IDLE;
		m_mouse_info.m_state_right = e_state::IDLE;
		m_mouse_info.m_scroll = 0;
	}

	bool mouse_in_bounds(const vec2_t& pos, const vec2_t& size)
	{
		const auto mouse_pos = m_mouse_info.m_pos;

		return mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + size.x
			&& mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + size.y;
	}

	bool mouse_in_bounds(const vec4_t& bounds)
	{
		return mouse_in_bounds(bounds.get_pos(), bounds.get_size());
	}

	/// Key info
	key_info_t& get_key_info(const int key)
	{
		return m_key_info.at(key);
	}

	std::string_view get_key_name(const int key)
	{
		if (key < 512)
			return KeyNames[key];

		switch (key)
		{
		case 0x10000100:
			return "D-Pad Up";
		case 0x10000200:
			return "D-Pad Down";
		case 0x10000400:
			return "D-Pad Left";
		case 0x10000800:
			return "D-Pad Right";
		case 0x10000004:
			return "Start";
		case 0x10000008:
			return "Back";
		case 0x10004000:
			return "L3";
		case 0x10008000:
			return "R3";
		case 0x10000010:
			return "Gamepad A";
		case 0x10000020:
			return "Gamepad B";
		case 0x10000040:
			return "Gamepad X";
		case 0x10000080:
			return "Gamepad Y";
		case 0x10001000:
			return "Left Bumper";
		case 0x10002000:
			return "Right Bumper";
		case 0x20000000:
			return "Left Trigger";
		case 0x20000001:
			return "Right Trigger";
		default:
			return {};
		}
	}

	char get_last_char()
	{
		return m_last_char;
	}

	void clear_char()
	{
		m_last_char = '\0';
	}

	HWND get_window()
	{
		return m_window;
	}

	
}