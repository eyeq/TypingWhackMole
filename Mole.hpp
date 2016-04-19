#pragma once

#include "Image.hpp"

class Mole
{
public:
	Mole(int, int, wchar_t);
	~Mole();

	void Init();
	void SetVisible(bool);
	bool IsVisible();
	int GetTime();
	wchar_t GetKey();
	bool IsIn(int, int);
	void Tick(bool);
	int Hit();
	void Paint(HDC&);
private:
	void textOut(HDC&);

	static bool isInit;
	static int count;

	bool isVisible;
	bool isHit;
	bool isBack;

	int time;
	wchar_t* key;
	int initX;
	int initY;

	RECT holeRect;
	RECT moleRect;

	static HDC holeS;
	static HDC holeM;
	static HDC moleS;
	static HDC moleM;
	static HDC moleHitS;
	static HDC moleHitM;

	HDC* holeSprite;
	HDC* holeMask;
	HDC* moleSprite;
	HDC* moleMask;
	HDC* moleHitSprite;
	HDC* moleHitMask;
};
