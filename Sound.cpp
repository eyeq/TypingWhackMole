#include "Sound.hpp"

void CreatePrimaryBuffer(const LPDIRECTSOUND8* lpDS, LPDIRECTSOUNDBUFFER* primaryBuffer)
{
	DSBUFFERDESC dsdesc =
	{
		sizeof(DSBUFFERDESC),																//DWORD dwSize					�T�C�Y
		DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN,	//DWORD dwFlags					�t���O
		0,																					//DWORD dwBufferBytes			0�Œ�
		0,																					//DWORD dwReserved				0�Œ�
		NULL,																				//LPWAVEFORMATEX lpwfxFormat	NULL�Œ�
		GUID_NULL																			//GUID guid3DAlgorithm			GUID_NULL�Œ�
	};
	(*lpDS)->CreateSoundBuffer(&dsdesc, primaryBuffer, NULL);
	WAVEFORMATEX wfx =
	{
		WAVE_FORMAT_PCM,	//WORD wFormatTag		�`��
		2,					//WORD nChannels		�`�����l��(1or2)
		44100,				//DWORD nSamplesPerSec	�T���v�����O���[�g
		176400,				//DWORD nAvgBytesPerSec	���σf�[�^�]�����x
		4,					//WORD nBlockAlign		�u���b�N �A���C�����g
		16,					//WORD wBitsPerSample	�ʎq���r�b�g(8or16)
		0,					//WORD cbSize			0�Œ�
	};
	(*primaryBuffer)->SetFormat(&wfx);
	memset(&dsdesc, 0, sizeof(DSBUFFERDESC));
}

void CreateSecondryBuffer(const LPDIRECTSOUND8* lpDS, LPDIRECTSOUNDBUFFER* secondryBuffer, wchar_t* path)
{
	//WAVE�t�@�C�������[�h
	HMMIO hSrc = mmioOpen(path, NULL, MMIO_ALLOCBUF | MMIO_READ | MMIO_COMPAT);
	if(!hSrc)
		return;
	//WAVE�`�����N�`�F�b�N
	MMCKINFO mSrcWaveFile;
	ZeroMemory(&mSrcWaveFile, sizeof(mSrcWaveFile));
	mmioDescend(hSrc, &mSrcWaveFile, NULL, MMIO_FINDRIFF);
	//fmt�`�����N�`�F�b�N
	MMCKINFO mSrcWaveFmt;
	ZeroMemory(&mSrcWaveFmt, sizeof(mSrcWaveFmt));
	mmioDescend(hSrc, &mSrcWaveFmt, &mSrcWaveFile, MMIO_FINDCHUNK);
	//�w�b�_�T�C�Y�̌v�Z
	int iSrcHeaderSize = max(mSrcWaveFmt.cksize, sizeof(WAVEFORMATEX));
	//�w�b�_�������m��
	LPWAVEFORMATEX wf = (LPWAVEFORMATEX)malloc(iSrcHeaderSize);
	ZeroMemory(wf, iSrcHeaderSize);
	//WAVE�t�H�[�}�b�g�̃��[�h
	mmioRead(hSrc, (char*)wf,mSrcWaveFmt.cksize);
	//fmt�`�����N�ɖ߂�
	mmioAscend(hSrc, &mSrcWaveFmt, 0);
	//data�`�����N��T��
	MMCKINFO mSrcWaveData;
	mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, 0);
	while(mSrcWaveData.ckid != mmioStringToFOURCC(L"data", 0))
	{
		mmioAscend(hSrc, &mSrcWaveData, 0);
		mmioDescend(hSrc, &mSrcWaveData, &mSrcWaveFile, 0);
	}
	//�T�E���h�o�b�t�@�̍쐬
	DSBUFFERDESC dsdesc =
	{
		sizeof(DSBUFFERDESC),																	//DWORD dwSize					�T�C�Y
		DSBCAPS_CTRLVOLUME | DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER,	//DWORD dwFlags					�t���O
		mSrcWaveData.cksize,																	//DWORD dwBufferBytes			0�Œ�
		0,																						//DWORD dwReserved				0�Œ�
		wf,																						//LPWAVEFORMATEX lpwfxFormat	NULL�Œ�
		DS3DALG_DEFAULT																			//GUID guid3DAlgorithm			GUID_NULL�Œ�
	};
	(*lpDS)->CreateSoundBuffer(&dsdesc, secondryBuffer, NULL);
	//���b�N�J�n
	LPVOID pMem1, pMem2;
	DWORD dwSize1,dwSize2;
	(*secondryBuffer)->Lock(0, mSrcWaveData.cksize, &pMem1, &dwSize1, &pMem2, &dwSize2, 0);
	//�f�[�^��������
	mmioRead(hSrc, (char*)pMem1, dwSize1);
	mmioRead(hSrc, (char*)pMem2, dwSize2);
	//���b�N����
	(*secondryBuffer)->Unlock(pMem1, dwSize1, pMem2, dwSize2);
	//�w�b�_�p���������J��
	free(wf);
	//WAVE�����
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
