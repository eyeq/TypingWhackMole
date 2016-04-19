#include "Game.hpp"

const HFONT MOLE_FONT = CreateFont(32, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET,
	OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, L"‚l‚r –¾’©");
const HFONT TEXT_FONT = CreateFont(32, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET,
	OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, L"Arial");

const int LIMIT_TIME = 2000;
const int WAIT_TIME = 300;

int tempMole;
int score;

Game::Game(Configuration* conf, LPDIRECTSOUND8* lp)
{
	config = conf;
	lpDS = lp;

	moles[0] = new Mole(  0, 128, 'Q');
	moles[1] = new Mole( 64, 128, 'W');
	moles[2] = new Mole(128, 128, 'E');
	moles[3] = new Mole(192, 128, 'R');
	moles[4] = new Mole(256, 128, 'T');
	moles[5] = new Mole(320, 128, 'Y');
	moles[6] = new Mole(384, 128, 'U');
	moles[7] = new Mole(448, 128, 'I');
	moles[8] = new Mole(512, 128, 'O');
	moles[9] = new Mole(576, 128, 'P');

	moles[10] = new Mole( 16, 256, 'A');
	moles[11] = new Mole( 80, 256, 'S');
	moles[12] = new Mole(144, 256, 'D');
	moles[13] = new Mole(208, 256, 'F');
	moles[14] = new Mole(272, 256, 'G');
	moles[15] = new Mole(336, 256, 'H');
	moles[16] = new Mole(400, 256, 'J');
	moles[17] = new Mole(464, 256, 'K');
	moles[18] = new Mole(528, 256, 'L');

	moles[19] = new Mole( 32, 384, 'Z');
	moles[20] = new Mole( 96, 384, 'X');
	moles[21] = new Mole(160, 384, 'C');
	moles[22] = new Mole(224, 384, 'V');
	moles[23] = new Mole(288, 384, 'B');
	moles[24] = new Mole(352, 384, 'N');
	moles[25] = new Mole(416, 384, 'M');

	CreateSecondryBuffer(lpDS, &hitSE, L"msc/se/hit.wav");
	CreateSecondryBuffer(lpDS, &missSE, L"msc/se/miss.wav");

	Init();
}

Game::~Game()
{
	for (int i = 0; i < 26; ++i)
		delete moles[i];
	ReleaseSoundBuffer(&hitSE);
	ReleaseSoundBuffer(&missSE);
}

void Game::Init()
{
	SetTime(0);
	tempMole = -1;
	score = 0;
	for (int i = 0; i < 26; ++i)
	{
		(*moles[i]).Init();
	}
	KeyInit();
}

bool Game::Tick()
{
	SetTime(GetTime() + 1);
	if(GetTime() < WAIT_TIME)
		return false;
	bool is, vi;
	const bool isMax = GetCount() > (*config).GetMaxNum();
	int x, y;
	if(!IsMousePressed())
	{
		tempMole = -1;
		x = -1;
		y = -1;
	} else
	{
		x = GetMouseX();
		y = GetMouseY();
	}
	for(int i = 0; i < 26; ++i)
	{
		bool mouse = false;
		if(i != tempMole && (*moles[i]).IsIn(x, y))
		{
			mouse = true;
			tempMole = i;
		}
		if(IsKeyPushed((WPARAM)(*moles[i]).GetKey()) || mouse)
		{
			int n = (*moles[i]).Hit();
			if(n > 0)
				PlaySoundBuffer(&hitSE);
			else if(n < 0)
				PlaySoundBuffer(&missSE);
			score += n;
		}
		vi = (*moles[i]).IsVisible();
		if(vi)
			is = (*config).IsVanish() && (*moles[i]).GetTime() > (*config).GetMinTime();
		else
			is = (*config).IsEmarge() && !isMax;
		(*moles[i]).Tick(is);
	}
	if(!(*moles[tempMole]).IsIn(x, y))
		tempMole = -1;
	(*config).SetScore(score);
	return GetTime() > LIMIT_TIME + WAIT_TIME;
}

void Game::Paint(HDC& hdc)
{
	COLORREF cr = SetTextColor(hdc, RGB(224, 224, 224));
	HFONT hf = (HFONT)SelectObject(hdc, MOLE_FONT);
	for(int i = 0; i < 26; ++i)
	{
		(*moles[i]).Paint(hdc);
	}
	SetTextColor(hdc, RGB(0, 32, 32));
	SelectObject(hdc, TEXT_FONT);
	wchar_t c[10];
	textOut(hdc, 10, 10, L"SCORE:", 6);
	_itow(score, c, 10);
	textOut(hdc, 110, 10, c, wcslen(c));

	textOut(hdc, 300, 10, L"HIGH_SCORE:", 11);
	_itow((*config).GetHighScore(), c, 10);
	textOut(hdc, 480, 10, c, wcslen(c));

	textOut(hdc, 10, 440, L"TIME_LEFT:", 10);
	if(GetTime() < WAIT_TIME)
		_itow(LIMIT_TIME, c, 10);
	else
		_itow(WAIT_TIME + LIMIT_TIME - GetTime(), c, 10);
	textOut(hdc, 170, 440, c, wcslen(c));

	if(GetTime() < WAIT_TIME || WAIT_TIME+ LIMIT_TIME - GetTime() < WAIT_TIME)
	{
		SetTextColor(hdc, RGB(255, 0, 0));
		int size = 320-(GetTime()%100)*2;
		SelectObject(hdc, CreateFont(size, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, L"Arial"));
		if(GetTime() < WAIT_TIME)
			_itow((int)((WAIT_TIME-GetTime())/100)+1, c, 10);
		else
			_itow((int)((WAIT_TIME+LIMIT_TIME-GetTime())/100)+1, c, 10);
		textOut(hdc, 320-size/4, 10, c, 1);
	}

	SetTextColor(hdc, cr);
	SelectObject(hdc, hf);
}

void Game::textOut(HDC& hdc, int x, int y, wchar_t* text, int size)
{
	TextOut(hdc, x, y, text, size);
	TextOut(hdc, x+1, y+1, text, size);
}

void Game::SetTime(int num)
{
	time = num;
}

int Game::GetTime()
{
	return time;
}

int Game::GetCount()
{
	int count = 0;
	for(int i = 0; i < 26; ++i)
		if((*moles[i]).IsVisible())
			++count;
	return count;
}
