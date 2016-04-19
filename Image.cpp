#include "Image.hpp"

HDC baseHdc;

/*
 * 
 */
void CreateHDC(HDC& create, const HBITMAP& hBit)
{
	create = CreateCompatibleDC(baseHdc);
	SelectObject(create, hBit);
}

/*
 *
 */
void CreateMDC(HDC& mdc, int width, int height)
{
	HBITMAP hBit = CreateCompatibleBitmap(baseHdc, width, height);
	CreateHDC(mdc, hBit);
	DeleteObject(hBit);
}

/*
 *
 */
void CreateSprite(HDC& spr, const wchar_t* filename)
{
	HBITMAP hBit = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0,  LR_LOADFROMFILE);
	CreateHDC(spr, hBit);
	DeleteObject(hBit);
}

/*
 * ç∂è„(0, 0)Ç∆ìØÇ∂Ç≈Ç»Ç¢Ç»ÇÁï`âÊÇ∑ÇÈ
 */
void CreateMask(const HDC& spr, HDC& msk, const BITMAP& bit, const wchar_t* filename)
{
	int width = bit.bmWidth;
	int height = bit.bmHeight;
	HBITMAP hBit = CreateCompatibleBitmap(baseHdc, width, height);
	CreateHDC(msk, hBit);
	DeleteObject(hBit);
	COLORREF trans = GetPixel(spr, 0, 0);
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(GetPixel(spr, j, i) == trans)
				SetPixel(msk, j, i, RGB(255, 255, 255));
			else
				SetPixel(msk, j, i, RGB(0, 0, 0));
		}
	}
}

/*
 *
 */
void CreateSpriteandMask(HDC& spr, HDC& msk, const wchar_t* filename)
{
	//createSprite
	CreateSprite(spr, filename);
	//createMask
	HBITMAP hBit = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	BITMAP bit;
	GetObject(hBit, sizeof(BITMAP), &bit);
	CreateMask(spr, msk, bit, filename);
	//createMdc
	int width = bit.bmWidth;
	int height = bit.bmHeight;
	HDC mdc;
	CreateMDC(mdc, width, height);
	
	BitBlt(mdc, 0, 0, width, height, msk, 0, 0, NOTSRCCOPY);
	BitBlt(spr, 0, 0, width, height, mdc, 0, 0, SRCAND);
}

/*
 *
 */
void MaskBlt(const HDC& hdc, RECT rect, const HDC& sprite, const HDC& mask, int bx, int by)
{
	BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, mask, bx, by, SRCAND);
	BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, sprite, bx, by, SRCPAINT);
}

void Draw(const HDC& front, const HDC& back, int width, int height)
{
	BitBlt(front, 0, 0, width, height, back, 0, 0, SRCCOPY);
}
