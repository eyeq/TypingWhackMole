#include "Mole.hpp"

bool Mole::isInit = false;

int Mole::count = 0;

HDC Mole::holeS;
HDC Mole::holeM;
HDC Mole::moleS;
HDC Mole::moleM;
HDC Mole::moleHitS;
HDC Mole::moleHitM;

Mole::Mole(int x, int y, wchar_t k)
{
	++count;
	initX = x;
	initY = y;
	key = (wchar_t*)malloc(sizeof(wchar_t));
	*key = k;

	holeSprite = &holeS;
	holeMask = &holeM;
	moleSprite = &moleS;
	moleMask = &moleM;
	moleHitSprite = &moleHitS;
	moleHitMask = &moleHitM;
	Init();
}

#include <fstream>
Mole::~Mole()
{
	--count;
	if(count != 0)
		return;
	DeleteDC(holeS);
	DeleteDC(holeM);
	DeleteDC(moleS);
	DeleteDC(moleM);
	DeleteDC(moleHitS);
	DeleteDC(moleHitM);
	isInit = false;
}

void Mole::Init()
{
	isVisible = false;
	isHit = false;
	isBack = false;
	time = 0;

	holeRect.top = initY - 32;
	holeRect.bottom = initY;
	holeRect.left = initX;
	holeRect.right = initX + 64;
	moleRect.top = initY - 14;
	moleRect.bottom = initY - 14;
	moleRect.left = initX;
	moleRect.right = initX + 64;
	if(isInit)
		return;
	isInit = true;
	CreateSpriteandMask(holeS, holeM, L"img/hole.bmp");
	CreateSpriteandMask(moleS, moleM, L"img/mole.bmp");
	CreateSpriteandMask(moleHitS, moleHitM, L"img/mole_hit.bmp");
}

void Mole::SetVisible(bool is)
{
	isVisible = is;
}

bool Mole::IsVisible()
{
	return isVisible;
}

int Mole::GetTime()
{
	return time;
}

wchar_t Mole::GetKey()
{
	return *key;
}

bool isIn(RECT rect, int x, int y)
{
	return rect.top <= y && y <= rect.bottom
		&& rect.left <= x && x <= rect.right;
}

bool Mole::IsIn(int x, int y)
{
	if(isIn(holeRect, x, y))
		if(!GetPixel(*holeMask, x - holeRect.left, y - holeRect.top))
			return true;
	if(isIn(moleRect, x, y))
		if(!GetPixel(*moleMask, x - moleRect.left, y - moleRect.top))
			return true;
	return false;
}

void Mole::Tick(bool is)
{
	++time;
	if(is)
	{
		if(isVisible)
			isBack = true;
		else
		{
			isVisible = true;
			isHit = false;
			isBack = false;
		}
	}
	if(!isVisible)
	{
		time = 0;
		return;
	}
	if(isBack)
		if(moleRect.top == moleRect.bottom)
			isVisible = false;
		else
			++moleRect.top;
	else if(moleRect.bottom - moleRect.top < 64)
		--moleRect.top;
}

int Mole::Hit()
{
	if(!isVisible)
	{
		isBack = true;
		return -1;
	}
	if(isHit)
		return 0;
	isHit = true;
	isBack = true;
	return 1;
}

void Mole::Paint(HDC& hdc)
{
	MaskBlt(hdc, holeRect, *holeSprite, *holeMask, 0, 0);
	if(isHit)
		MaskBlt(hdc, moleRect, *moleHitSprite, *moleHitMask, 0, 0);
	else
		MaskBlt(hdc, moleRect, *moleSprite, *moleMask, 0, 0);
	textOut(hdc);
}

void Mole::textOut(HDC& hdc)
{
	TextOut(hdc, moleRect.left, moleRect.top, key, 1);
	TextOut(hdc, moleRect.left+1, moleRect.top, key, 1);
}
