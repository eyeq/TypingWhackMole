#pragma once

#include <windows.h>

#include "Configuration.hpp"
#include "Key.hpp"
#include "Mouse.hpp"

class Panel
{
public:
	Panel(){}
	virtual ~Panel(){}
public:
	virtual void Init(){}
	virtual void Paint(HDC& hdc){ TextOut(hdc, 10, 10, L"panel", 5); }
	virtual bool Tick(){ return false; }
};
