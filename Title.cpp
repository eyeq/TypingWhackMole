#include "Title.hpp"

const HFONT TEXT_FONT = CreateFont(32, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET,
	OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, L"ÉÅÉCÉäÉI");

Title::Title(Configuration* conf, LPDIRECTSOUND8* lp)
{
	config = conf;
	lpDS = lp;
	
	CreateSpriteandMask(allowSprite, allowMask, L"img/allow.bmp");

	CreateSecondryBuffer(lpDS, &returnSE, L"msc/se/return.wav");
	CreateSecondryBuffer(lpDS, &selectSE, L"msc/se/select.wav");

	Init();
}

Title::~Title()
{
	DeleteDC(allowSprite);
	DeleteDC(allowMask);

	ReleaseSoundBuffer(&returnSE);
	ReleaseSoundBuffer(&selectSE);
}

void Title::Init()
{
	select = 0;
	tempMouseY = 0;
	KeyInit();
}

void Title::Paint(HDC& hdc)
{
	COLORREF cr = SetTextColor(hdc, RGB(128, 0, 86));
	HFONT hf = (HFONT)SelectObject(hdc, TEXT_FONT);
	wchar_t c[10];
	TextOut(hdc, 380, 20, L"HIGH_SCORE:", 11);
	_itow((*config).GetHighScore(selectDifficulty()), c, 10);
	TextOut(hdc, 540, 20, c, wcslen(c));
	TextOut(hdc, 354, 60, L"LATEST_SCORE:", 13);
	_itow((*config).GetLatestScore(selectDifficulty()), c, 10);
	TextOut(hdc, 540, 60, c, wcslen(c));

	SetTextColor(hdc, RGB(128, 0, 0));
	TextOut(hdc, 10, 10, L"TypingWhackMole", 16);
	TextOut(hdc, 10, 12, L"TypingWhackMole", 16);
	TextOut(hdc, 10, 16, L"TypingWhackMole", 16);
	TextOut(hdc, 300, 300, L"EASY", 4);
	TextOut(hdc, 300, 340, L"NORMAL", 6);
	TextOut(hdc, 300, 380, L"HARD", 4);

	SetTextColor(hdc, cr);
	SelectObject(hdc, hf);
	
	int top = 300 + 40 * select;
	RECT rect = {268, top, 300, top + 32};
	MaskBlt(hdc, rect, allowSprite, allowMask, 0, 0);
}

DIFFICULTY Title::selectDifficulty()
{
	switch(select)
	{
	case 0:
		return EASY;
	case 1:
		return NORMAL;
	default:
		return HARD;
	}
}

bool Title::Tick()
{
	if(IsKeyPushed(VK_RETURN) || IsMousePressed())
	{
		PlaySoundBuffer(&returnSE);
		(*config).SetDifficulty(selectDifficulty());
		return true;
	}
	int preSelect = select;
	if(IsKeyPushed(VK_UP))
	{
		if(select == 0)
			select = 2;
		else
			--select;
	}
	if(IsKeyPushed(VK_DOWN))
	{
		if(select == 2)
			select = 0;
		else
			++select;
	}
	int y = GetMouseY();
	if(tempMouseY != y)
	{
		if(y < 340)
			select = 0;
		else if(y < 380)
			select = 1;
		else
			select = 2;
	}
	tempMouseY = y;
	if(preSelect != select)
		PlaySoundBuffer(&selectSE);
	return false;
}
