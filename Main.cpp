#include "Main.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void gameLoop();

const wchar_t* TEXT_TITLE = L"もぐらたたきタイピング";

const int WIDTH = 640;
const int HEIGHT = 480;

const int GAP_X = GetSystemMetrics(SM_CXDLGFRAME) * 2;
const int GAP_Y = GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);

Background* back;

/*
 * Windows_Main関数
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウクラスを生成
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),						//UINT cbSize			サイズ
		CS_HREDRAW | CS_VREDRAW,				//UINT style			スタイル
		WndProc,								//WNDPROC lpfnWndProc	プロシージャのアドレス
		0,										//int cbClsExtra		0固定
		0,										//int cbWndExtra		0固定
		hInstance,								//HINSTANCE hInstance	ハンドル
		LoadIcon(NULL, IDI_APPLICATION),		//HICON hIcon			アイコン
		LoadCursor(NULL, IDC_ARROW),			//HCURSOR hCursor		マウスカーソル
		(HBRUSH)GetStockObject(WHITE_BRUSH),	//HBRUSH hbrBackground	背景色
		TEXT_TITLE,								//LPCTSTR lpszMenuName	メニュー
		TEXT_TITLE,								//LPCTSTR lpszClassName	クラス名
		LoadIcon(NULL , IDI_APPLICATION)		//HICON hIconSm			小さいアイコン
	};
	//ウインドウクラスを登録
	if(!RegisterClassEx(&wcex))
		return 0;
	//ウインドウを生成
	HWND hWnd = CreateWindowEx(
		WS_EX_LEFT,										//DWORD dwExStyle		拡張スタイル
		TEXT_TITLE,										//LPCTSTR lpClassName	クラス名
		TEXT_TITLE,										//LPCTSTR lpWindowName	タイトル
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,	//DWORD dwStyle			スタイル
		CW_USEDEFAULT,									//int x					x座標
		CW_USEDEFAULT,									//int y					y座標
		WIDTH + GAP_X,									//int nWidth			幅
		HEIGHT + GAP_Y,									//int nHeight			高さ
		NULL,											//HWND hWndParent		親のウィンドウ
		NULL,											//HMENU hMenu			メニュー
		hInstance,										//HINSTANCE hInstance	ハンドル
		NULL											//LPVOID lpParam		データ
	);
	if(!hWnd)
		return 0;
	back = new Background(hWnd);

	ShowWindow(hWnd, nCmdShow);	//ウィンドウを表示
	SetFocus(hWnd);				//フォーカスを設定
	HANDLE gameLoopThread = CreateThread( 
		0,									//LPSECURITY_ATTRIBUTES lpThreadAttributes	セキュリティ記述子
		0,									//DWORD dwStackSize							初期のスタックサイズ
		(LPTHREAD_START_ROUTINE)&gameLoop,	//LPTHREAD_START_ROUTINE lpStartAddress		スレッドの機能
		NULL,								//LPVOID lpParameter						スレッドの引数
		0,									//DWORD dwCreationFlags						作成オプション
		0									//LPDWORD lpThreadId						スレッド識別子
	);

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);	//仮想キーメッセージの変換
		DispatchMessage(&msg);	//ウインドウプロシージャへ転送
	}
	//メモリ解放
	CloseHandle(gameLoopThread);
	delete back;
	return msg.wParam;
}

/*
 * Windws イベント用関数
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//渡された message から、イベントの種類を解析する
	switch(uMsg)
	{
	//終了処理
	case WM_CLOSE:
		ShowWindow(hWnd, SW_RESTORE);
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		MouseMove(lParam);
		break;
	case WM_LBUTTONDOWN:
		MouseDown(lParam);
		break;
	case WM_LBUTTONUP:
		MouseUp();
		break;
	//キー入力
	case WM_KEYDOWN:
		KeyDown(wParam);
		break;
	case WM_KEYUP:
		KeyUp(wParam);
		break;
	}
	//デフォルトの処理
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int wait(unsigned int lastTime, unsigned int wait)
{
	while(wait > timeGetTime() - lastTime)
		Sleep(1);
	return lastTime + wait;
}

void gameLoop()
{
	unsigned int lastTime = timeGetTime();
	while(true)
	{
		(*back).Paint();
		(*back).Repaint();
		lastTime = wait(lastTime, 10);
	}
}
