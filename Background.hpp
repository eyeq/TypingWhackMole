#pragma once

#include "Main.hpp"
#include "Image.hpp"
#include "Sound.hpp"
#include "Panel.hpp"
#include "Title.hpp"
#include "Game.hpp"

const enum MODE
{
	NONE,
	TITLE,
	GAME,
};

class Background
{
public:
	Background(HWND&);
	~Background();
	HDC& GetHdc();
	void SetBack(MODE);
	void Paint();
	void Repaint();
private:
	Title* title;
	Game* game;
	Configuration* config;
	HDC front;
	HDC back;
	HDC gameBack;
	LPDIRECTSOUND8 lpDS;
	LPDIRECTSOUNDBUFFER primaryBuffer;
	LPDIRECTSOUNDBUFFER titleBGM;
	LPDIRECTSOUNDBUFFER gameBGM;
	MODE mode;
};
