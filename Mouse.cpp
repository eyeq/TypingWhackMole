#include "Mouse.hpp"

bool isMousePressed = false;
int x = 0;
int y = 0;

void MouseMove(LPARAM lParam)
{
	x = LOWORD(lParam);
	y = HIWORD(lParam);
}

void MouseDown(LPARAM lParam)
{
	isMousePressed = true;
	MouseMove(lParam);
}

void MouseUp()
{
	isMousePressed = false;
}

bool IsMousePressed()
{
	return isMousePressed;
}

int GetMouseX()
{
	return x;
}

int GetMouseY()
{
	return y;
}
