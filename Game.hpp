#pragma once

#include <stdlib.h>

#include "Panel.hpp"
#include "Mole.hpp"
#include "Sound.hpp"

class Game : public Panel
{
public:
	Game(Configuration*, LPDIRECTSOUND8*);
	~Game();
	void Init();
	bool Tick();
	void Paint(HDC&);
	void SetTime(int);
	int GetTime();
	int GetCount();
private:
	void textOut(HDC&, int, int, wchar_t*, int);
	Configuration* config;
	Mole* moles[26];
	LPDIRECTSOUND8* lpDS;
	LPDIRECTSOUNDBUFFER hitSE;
	LPDIRECTSOUNDBUFFER missSE;
	int time;
};
