#pragma once

#include <windows.h>
#include <dsound.h>

#pragma comment(lib, "dsound.lib")

void CreatePrimaryBuffer(const LPDIRECTSOUND8*, LPDIRECTSOUNDBUFFER*);
void CreateSecondryBuffer(const LPDIRECTSOUND8*, LPDIRECTSOUNDBUFFER*, wchar_t*);
void PlaySoundBuffer(const LPDIRECTSOUNDBUFFER*);
void PlayLoopSoundBuffer(const LPDIRECTSOUNDBUFFER*);
void StopSoundBuffer(const LPDIRECTSOUNDBUFFER*);
void SetVolume(const LPDIRECTSOUNDBUFFER*, int);
void ReleaseSoundBuffer(LPDIRECTSOUNDBUFFER*);
void ReleaseSound8(LPDIRECTSOUND8*);
