#include "Background.hpp"

Background::Background(HWND& hWnd)
{
	baseHdc = front = GetDC(hWnd);
	CreateMDC(back, WIDTH, HEIGHT);
	SetBkMode(back, TRANSPARENT);

	CreateSprite(gameBack, L"img/back/game.bmp");

	DirectSoundCreate8(NULL, &lpDS, NULL);
	lpDS->SetCooperativeLevel(hWnd, DSSCL_EXCLUSIVE | DSSCL_PRIORITY);
	CreatePrimaryBuffer(&lpDS, &primaryBuffer);
	CreateSecondryBuffer(&lpDS, &titleBGM, L"msc/bgm/title.wav");
	CreateSecondryBuffer(&lpDS, &gameBGM, L"msc/bgm/game.wav");

	SetVolume(&primaryBuffer, 100);
	SetVolume(&titleBGM, 100);
	SetVolume(&gameBGM, 100);

	panel = NULL;
	config = new Configuration();
	SetBack(TITLE);
}

Background::~Background()
{
	SetBack(NONE);
	delete config;

	DeleteDC(front);
	DeleteDC(back);
	DeleteDC(gameBack);

	ReleaseSoundBuffer(&titleBGM);
	ReleaseSoundBuffer(&gameBGM);
	ReleaseSoundBuffer(&primaryBuffer);
	ReleaseSound8(&lpDS);
}

HDC& Background::GetHdc()
{
	return back;
}

void Background::SetBack(MODE m)
{
	switch(mode)
	{
	case TITLE:
		StopSoundBuffer(&titleBGM);
		break;
	case GAME:
		StopSoundBuffer(&gameBGM);
		break;
	}
	mode = m;
	delete panel;
	switch(mode)
	{
	case NONE:
		return;
	case TITLE:
		PlayLoopSoundBuffer(&titleBGM);
		panel = new Title(config, &lpDS);
		break;
	case GAME:
		PlayLoopSoundBuffer(&gameBGM);
		panel = new Game(config, &lpDS);
		break;
	}
	(*panel).Init();
}

void Background::Paint()
{
	Draw(back, gameBack, WIDTH, HEIGHT);
	(*panel).Paint(back);
	if ((*panel).Tick()) {
		switch (mode)
		{
		case TITLE:
			SetBack(GAME);
			break;
		case GAME:
			SetBack(TITLE);
			break;
		}
	}
}

void Background::Repaint()
{
	Draw(front, back, WIDTH, HEIGHT);
}
