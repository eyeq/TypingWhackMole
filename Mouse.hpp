#pragma once

#include <windows.h>

void MouseMove(LPARAM);
void MouseDown(LPARAM);
void MouseUp();
bool IsMousePressed();
int GetMouseX();
int GetMouseY();
