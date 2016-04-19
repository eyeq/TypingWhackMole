#pragma once

#include "Panel.hpp"
#include "Image.hpp"
#include "Sound.hpp"

class Title : public Panel
{
public:
	Title(Configuration*, LPDIRECTSOUND8*);
	~Title();
	void Init();
	void Paint(HDC&);
	bool Tick();
private:
	Configuration* config;
	LPDIRECTSOUND8* lpDS;
	LPDIRECTSOUNDBUFFER returnSE;
	LPDIRECTSOUNDBUFFER selectSE;
	int select;
	int tempMouseY;
	HDC allowSprite;
	HDC allowMask;
	DIFFICULTY selectDifficulty();
};
