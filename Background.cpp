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

	config = new Configuration();
	game = new Game(config, &lpDS);
	title = new Title(config, &lpDS);
	SetBack(TITLE);
}

Background::~Background()
{
	SetBack(NONE);
	delete title;
	delete game;
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
	switch(mode)
	{
	case NONE:
		break;
	case TITLE:
		PlayLoopSoundBuffer(&titleBGM);
		(*title).Init();
		break;
	case GAME:
		PlayLoopSoundBuffer(&gameBGM);
		(*game).Init();
		break;
	}
}

void Background::Paint()
{
	Draw(back, gameBack, WIDTH, HEIGHT);
	switch(mode)
	{
	case TITLE:
		(*title).Paint(back);
		if((*title).Tick())
			SetBack(GAME);
		break;
	case GAME:
		(*game).Paint(back);
		if((*game).Tick())
			SetBack(TITLE);
		break;
	}
}

void Background::Repaint()
{
	Draw(front, back, WIDTH, HEIGHT);
}
