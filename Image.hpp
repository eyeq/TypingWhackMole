#pragma once

#include <windows.h>

void CreateMDC(HDC&, int, int);
void CreateSprite(HDC&, const wchar_t*);
void CreateSpriteandMask(HDC&, HDC&, const wchar_t*);
void MaskBlt(const HDC&, RECT, const HDC&, const HDC&, int, int);
void Draw(const HDC&, const HDC&, int, int);

extern HDC baseHdc;
