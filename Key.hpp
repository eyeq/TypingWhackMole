#pragma once

#include <Windows.h>

void KeyInit();
void KeyDown(WPARAM);
void KeyUp(WPARAM);
bool IsKeyPressed(WPARAM);
bool IsKeyPushed(WPARAM);
WPARAM GetPressedKey();
const wchar_t* GetKeyWchar(WPARAM);
