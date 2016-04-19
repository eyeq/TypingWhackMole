#include "Key.hpp"

bool isKeyPressed[256];
bool isKeyReleased[256];

bool isFirstCall = true;
bool isPressed = false;

WPARAM pressedKey;

void KeyInit()
{
	for(int i = 0; i < 256; ++i)
	{
		isKeyPressed[i] = false;
		isKeyReleased[i] = false;
	}
}

void KeyDown(WPARAM wParam)
{
	isKeyPressed[wParam] = true;
	if(!isPressed)
	{
		pressedKey = wParam;
		isPressed = true;
	}
}

void KeyUp(WPARAM wParam)
{
	isKeyPressed[wParam] = false;
}

bool IsKeyPressed(WPARAM wParam)
{
	return isKeyPressed[wParam];
}

bool IsKeyPushed(WPARAM wParam)
{
	bool is = isKeyReleased[wParam];
	isKeyReleased[wParam] = !isKeyPressed[wParam];
	return IsKeyPressed(wParam) && is;
}

WPARAM GetPressedKey()
{
	if(isFirstCall)
	{
		isFirstCall = false;
		isPressed = false;
	}
	if(isPressed)
	{
		isFirstCall = true;
		return pressedKey;
	}
	return NULL;
}

const wchar_t* GetKeyWchar(WPARAM wParam)
{
	switch(wParam)
	{
	case VK_LBUTTON:
		return L"LEFT_BUTTON";
	case VK_RBUTTON:
		return L"RIGHT_BUTTON";
	case VK_CANCEL:
		return L"CONTROL_BREAK";
	case VK_MBUTTON:
		return L"MIDDLE_BUTTON";
	case VK_XBUTTON1:
		return L"X1_BUTTON";
	case VK_XBUTTON2:
		return L"X2_BUTTON";
	case VK_BACK:
		return L"BACKSPACE";
	case VK_TAB:
		return L"TAB";
	case VK_CLEAR:
		return L"CLEAR";
	case VK_RETURN:
		return L"ENTER";
	case VK_SHIFT:
		return L"SHIFT";
	case VK_CONTROL:
		return L"CTRL";
	case VK_MENU:
		return L"ALT";
	case VK_PAUSE:
		return L"PAUSE";
	case VK_CAPITAL:
		return L"CAPS_LOCK";
	case VK_KANA:
		return L"IME_KANA";
	case VK_JUNJA:
		return L"IME_JUNJA";
	case VK_FINAL:
		return L"IME_FINAL";
	case VK_KANJI:
		return L"IME_KANJI";
	case VK_ESCAPE:
		return L"ESC";
	case VK_CONVERT:
		return L"IME_CONVERT";
	case VK_NONCONVERT:
		return L"IME_NONCONVERT";
	case VK_ACCEPT:
		return L"IME_ACCEPT";
	case VK_MODECHANGE:
		return L"IME_CHANGE";
	case VK_SPACE:
		return L"SPACEBAR";
	case VK_PRIOR:
		return L"PAGE_UP";
	case VK_NEXT:
		return L"PAGE_DOWN";
	case VK_END:
		return L"END";
	case VK_HOME:
		return L"HOME";
	case VK_LEFT:
		return L"LEFT";
	case VK_UP:
		return L"UP";
	case VK_RIGHT:
		return L"RIGHT";
	case VK_DOWN:
		return L"DOWN";
	case VK_SELECT:
		return L"SELECT";
	case VK_PRINT:
		return L"PAINT";
	case VK_EXECUTE:
		return L"EXECUTE";
	case VK_SNAPSHOT:
		return L"PAINT_SCREEN";
	case VK_INSERT:
		return L"INS";
	case VK_DELETE:
		return L"DEL";
	case VK_HELP:
		return L"HELP";
	case 0x30:
		return L"0";
	case 0x31:
		return L"1";
	case 0x32:
		return L"2";
	case 0x33:
		return L"3";
	case 0x34:
		return L"4";
	case 0x35:
		return L"5";
	case 0x36:
		return L"6";
	case 0x37:
		return L"7";
	case 0x38:
		return L"8";
	case 0x39:
		return L"9";
	case 0x41:
		return L"A";
	case 0x42:
		return L"B";
	case 0x43:
		return L"C";
	case 0x44:
		return L"D";
	case 0x45:
		return L"E";
	case 0x46:
		return L"F";
	case 0x47:
		return L"G";
	case 0x48:
		return L"H";
	case 0x49:
		return L"I";
	case 0x4A:
		return L"J";
	case 0x4B:
		return L"K";
	case 0x4C:
		return L"L";
	case 0x4D:
		return L"M";
	case 0x4E:
		return L"N";
	case 0x4F:
		return L"O";
	case 0x50:
		return L"P";
	case 0x51:
		return L"Q";
	case 0x52:
		return L"R";
	case 0x53:
		return L"S";
	case 0x54:
		return L"T";
	case 0x55:
		return L"U";
	case 0x56:
		return L"V";
	case 0x57:
		return L"W";
	case 0x58:
		return L"X";
	case 0x59:
		return L"Y";
	case 0x5A:
		return L"Z";
	case VK_LWIN:
		return L"LEFT_WINDOWS";
	case VK_RWIN:
		return L"RIGHT_WINDOWS";
	case VK_APPS:
		return L"APPLICATIONS";
	case VK_SLEEP:
		return L"COMPUTER_SLEEP";
	case VK_NUMPAD0:
		return L"NUMPAD_0";
	case VK_NUMPAD1:
		return L"NUMPAD_1";
	case VK_NUMPAD2:
		return L"NUMPAD_2";
	case VK_NUMPAD3:
		return L"NUMPAD_3";
	case VK_NUMPAD4:
		return L"NUMPAD_4";
	case VK_NUMPAD5:
		return L"NUMPAD_5";
	case VK_NUMPAD6:
		return L"NUMPAD_6";
	case VK_NUMPAD7:
		return L"NUMPAD_7";
	case VK_NUMPAD8:
		return L"NUMPAD_8";
	case VK_NUMPAD9:
		return L"NUMPAD_9";
	case VK_MULTIPLY:
		return L"MULTIPLY";
	case VK_ADD:
		return L"ADD";
	case VK_SEPARATOR:
		return L"SEPARATOR";
	case VK_SUBTRACT:
		return L"SUBTRACT";
	case VK_DECIMAL:
		return L"DECIMAL";
	case VK_DIVIDE:
		return L"DIVIDE";
	case VK_F1:
		return L"F1";
	case VK_F2:
		return L"F2";
	case VK_F3:
		return L"F3";
	case VK_F4:
		return L"F4";
	case VK_F5:
		return L"F5";
	case VK_F6:
		return L"F6";
	case VK_F7:
		return L"F7";
	case VK_F8:
		return L"F8";
	case VK_F9:
		return L"F9";
	case VK_F10:
		return L"F10";
	case VK_F11:
		return L"F11";
	case VK_F12:
		return L"F12";
	case VK_F13:
		return L"F13";
	case VK_F14:
		return L"F14";
	case VK_F15:
		return L"F15";
	case VK_F16:
		return L"F16";
	case VK_F17:
		return L"F17";
	case VK_F18:
		return L"F18";
	case VK_F19:
		return L"F19";
	case VK_F20:
		return L"F20";
	case VK_F21:
		return L"F21";
	case VK_F22:
		return L"F22";
	case VK_F23:
		return L"F23";
	case VK_F24:
		return L"F24";
	case VK_NUMLOCK:
		return L"NUM_LOCK";
	case VK_SCROLL:
		return L"SCROLL_LOCK";
	case VK_LSHIFT:
		return L"LEFT_SHIFT";
	case VK_RSHIFT:
		return L"RIGHT_SHIFT";
	case VK_LCONTROL:
		return L"LEFT_CONTROL";
	case VK_RCONTROL:
		return L"RIGHT_CONTROL";
	case VK_LMENU:
		return L"LEFT_MENU";
	case VK_RMENU:
		return L"RIGHT_MENU";
	case VK_BROWSER_BACK:
		return L"BROWSER_BACK";
	case VK_BROWSER_FORWARD:
		return L"BROWSER_FORWARD";
	case VK_BROWSER_REFRESH:
		return L"BROWSER_REFRESH";
	case VK_BROWSER_STOP:
		return L"BROWSER_STOP";
	case VK_BROWSER_SEARCH:
		return L"BROWSER_SEARCH";
	case VK_BROWSER_FAVORITES:
		return L"BROWSER_FAVORITES";
	case VK_BROWSER_HOME:
		return L"BROWSER_HOME";
	case VK_VOLUME_MUTE:
		return L"VOLUME_MUTE";
	case VK_VOLUME_DOWN:
		return L"VOLUME_DOWN";
	case VK_VOLUME_UP:
		return L"VOLUME_UP";
	case VK_MEDIA_NEXT_TRACK:
		return L"NEXT_TRACK";
	case VK_MEDIA_PREV_TRACK:
		return L"PREVIOUS_TRACK";
	case VK_MEDIA_STOP:
		return L"STOP_MEDIA";
	case VK_MEDIA_PLAY_PAUSE:
		return L"PLAY_MEDIA";
	case VK_LAUNCH_MAIL:
		return L"START_MAIL";
	case VK_LAUNCH_MEDIA_SELECT:
		return L"SELECT_MEDIA";
	case VK_LAUNCH_APP1:
		return L"SELECT_APPLICATION_1";
	case VK_LAUNCH_APP2:
		return L"SELECT_APPLICATION_2";
	case VK_OEM_1:
		return L"COLON";
	case VK_OEM_PLUS:
		return L"PLUS";
	case VK_OEM_COMMA:
		return L"COMMA";
	case VK_OEM_MINUS:
		return L"MINUS";
	case VK_OEM_PERIOD:
		return L"PERIOD";
	case VK_OEM_2:
		return L"QUESTION_MARK";
	case VK_OEM_3:
		return L"TILDE";
	case VK_OEM_4:
		return L"LEFT_BRACKET";
	case VK_OEM_5:
		return L"VERTICAL_BAR";
	case VK_OEM_6:
		return L"RIGHT_BRACKET";
	case VK_OEM_7:
		return L"QUOTE";
	case VK_OEM_8:
		return L"SOMEONE";
	case VK_OEM_102:
		return L"BACKSLACH";
	case VK_PROCESSKEY:
		return L"IME_PROSESS";
	case VK_PACKET:
		return L"PACKET";
	case VK_ATTN:
		return L"ATTN";
	case VK_CRSEL:
		return L"CRSEL";
	case VK_EXSEL:
		return L"EXSEL";
	case VK_EREOF:
		return L"ERASE_EOF";
	case VK_PLAY:
		return L"PLAY";
	case VK_ZOOM:
		return L"ZOOM";
	case VK_NONAME:
		return L"RESERVED";
	case VK_PA1:
		return L"PA_1";
	case VK_OEM_CLEAR:
		return L"CLEAR";
	}
	return L"NULL";
}