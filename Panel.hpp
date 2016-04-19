#pragma once

#include <windows.h>

#include "Configuration.hpp"
#include "Key.hpp"
#include "Mouse.hpp"

class Panel
{
protected:
	Panel(){}
	~Panel(){}
public:
	void Init(){}
	void Paint(HDC& hdc){ TextOut(hdc, 10, 10, L"panel", 5); }
	bool Tick(){ return false; }
};
