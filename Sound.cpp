#include "Sound.hpp"

void CreatePrimaryBuffer(const LPDIRECTSOUND8* lpDS, LPDIRECTSOUNDBUFFER* primaryBuffer)
{
	DSBUFFERDESC dsdesc =
	{
		sizeof(DSBUFFERDESC),																//DWORD dwSize					サイズ
		DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN,	//DWORD dwFlags					フラグ
		0,																					//DWORD dwBufferBytes			0固定
		0,																					//DWORD dwReserved				0固定
		NULL,																				//LPWAVEFORMATEX lpwfxFormat	NULL固定
		GUID_NULL																			//GUID guid3DAlgorithm			GUID_NULL固定
	};
	(*lpDS)->CreateSoundBuffer(&dsdesc, primaryBuffer, NULL);
	WAVEFORMATEX wfx =
	{
		WAVE_FORMAT_PCM,	//WORD wFormatTag		形式
		2,					//WORD nChannels		チャンネル(1or2)
		44100,				//DWORD nSamplesPerSec	サンプリングレート
		176400,				//DWORD nAvgBytesPerSec	平均データ転送速度
		4,					//WORD nBlockAlign		ブロック アライメント
		16,					//WORD wBitsPerSample	量子化ビット(8or16)
		0,					//WORD cbSize			0固定
	};
	(*primaryBuffer)->SetFormat(&wfx);
	memset(&dsdesc, 0, sizeof(DSBUFFERDESC));
}

void CreateSecondryBuffer(const LPDIRECTSOUND8* lpDS, LPDIRECTSOUNDBUFFER* secondryBuffer, wchar_t* path)
{
	//WAVEファイルをロード
	HMMIO hSrc = mmioOpen(path, NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);
	if(!hSrc)
		return;
	//WAVEチャンクチェック
	MMCKINFO mSrcWaveFile;
	ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
	mmioDescend(hSrc, &mSrcWaveFile, NULL, MMIO_FINDRIFF);
	//fmtチャンクチェック
	MMCKINFO mSrcWaveFmt;
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);
	//ヘッダサイズの計算
	int iSrcHeaderSize = max(mSrcWaveFmt.cksize, sizeof(WAVEFORMATEX));
	//ヘッダメモリ確保
	LPWAVEFORMATEX wf = (LPWAVEFORMATEX)malloc(iSrcHeaderSize);
	ZeroMemory(wf, iSrcHeaderSize);
	//WAVEフォーマットのロード
	mmioRead(hSrc, (char*)wf,mSrcWaveFmt.cksize);
	//fmtチャンクに戻る
	mmioAscend(hSrc, &mSrcWaveFmt, 0);
	//dataチャンクを探す
	MMCKINFO mSrcWaveData;
	mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, 0);
	while(mSrcWaveData.ckid != mmioStringToFOURCC(L"data", 0))
	{
		mmioAscend(hSrc, &mSrcWaveData, 0);
		mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, 0);
	}
	//サウンドバッファの作成
	DSBUFFERDESC dsdesc =
	{
		sizeof(DSBUFFERDESC),																	//DWORD dwSize					サイズ
		DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER,	//DWORD dwFlags					フラグ
		mSrcWaveData.cksize,																	//DWORD dwBufferBytes			0固定
		0,																						//DWORD dwReserved				0固定
		wf,																						//LPWAVEFORMATEX lpwfxFormat	NULL固定
		DS3DALG_DEFAULT																			//GUID guid3DAlgorithm			GUID_NULL固定
	};
	(*lpDS)->CreateSoundBuffer(&dsdesc, secondryBuffer, NULL);
	//ロック開始
	LPVOID pMem1, pMem2;
	DWORD dwSize1,dwSize2;
	(*secondryBuffer)->Lock(0, mSrcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0);
	//データ書き込み
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);
	//ロック解除
	(*secondryBuffer)->Unlock(pMem1, dwSize1, pMem2, dwSize2);
	//ヘッダ用メモリを開放
	free(wf);
	//WAVEを閉じる
	mmioClose(hSrc, 0);
}

void PlaySoundBuffer(const LPDIRECTSOUNDBUFFER* soundBuffer)
{
	if(!(*soundBuffer))
		return;
	(*soundBuffer)->SetCurrentPosition(0);
	(*soundBuffer)->Play(0, 0, 0);
}

void PlayLoopSoundBuffer(const LPDIRECTSOUNDBUFFER* soundBuffer)
{
	if(!(*soundBuffer))
		return;
	(*soundBuffer)->SetCurrentPosition(0);
	(*soundBuffer)->Play(0, 0, DSBPLAY_LOOPING);
}

void StopSoundBuffer(const LPDIRECTSOUNDBUFFER* soundBuffer)
{
	if(!(*soundBuffer))
		return;
	(*soundBuffer)->Stop();
}

void SetVolume(const LPDIRECTSOUNDBUFFER* soundBuffer, int volume)
{
	if(!(*soundBuffer))
		return;
	(*soundBuffer)->SetVolume(volume);
}

void ReleaseSoundBuffer(LPDIRECTSOUNDBUFFER* soundBuffer)
{
	if(!(*soundBuffer))
		return;
	(*soundBuffer)->Release();
	*soundBuffer = NULL;
}

void ReleaseSound8(LPDIRECTSOUND8* lpDS)
{
	if(!(*lpDS))
		return;
	(*lpDS)->Release();
	*lpDS = NULL;
}
