//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#include "SoundManager.h"

using namespace std;

namespace uq_lib {

	SoundManager* SoundManager::m_sm = NULL;
	bool SoundManager::m_destroyFlg = true; // Phoenix Singleton回避用

	SoundManager::SoundManager() {
		m_hwnd = NULL;
		m_pDS8 = NULL;
		ZeroMemory(m_pSoundBuffer, sizeof(D_SOUND_MAX));
	}

	SoundManager::~SoundManager() {
	}

	int SoundManager::Init(HWND hWnd) {
		m_hwnd = hWnd;
		DirectSoundCreate8(NULL, &m_pDS8, NULL);
		m_pDS8->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);

		for (int i = 0; i < D_SOUND_MAX; i++) {
			m_pSoundBuffer[i] = NULL;
		}
		return 0;
	}

	int SoundManager::PlaySoundFromFile(string fileName, int playType) {
		int ret = 0;
		switch (playType) {
		case D_PLAY_SOUND_BGM:
			StopSoundEX(0); // BGMが再生されているのにＢＧＭを登録しようとした際は削除し再セット（仕様変更の場合はここ修正
			ret = SoundFileOpen(fileName, DSBPLAY_LOOPING, 0);
			break;
		case D_PLAY_SOUND_SE:
		{
			int num = GetPlaySlot();
			if (num == -1) break;
			ret = SoundFileOpen(fileName, 0, num);
		}
		break;
		default: break;
		}
		return ret;
	}

	void SoundManager::StopSoundEX(int slotNum) {
		switch (slotNum) {
		case D_PLAY_SOUND_BGM:
			if (m_pSoundBuffer[0] != NULL) {
				m_pSoundBuffer[0]->Stop();
				SAFE_RELEASE(m_pSoundBuffer[0]);
			}
			break;
		case D_PLAY_SOUND_SE:
			for (int i = 1; i < D_SOUND_MAX; i++) {
				if (m_pSoundBuffer[i] != NULL) {
					m_pSoundBuffer[i]->Stop();
					SAFE_RELEASE(m_pSoundBuffer[i]);
				}
			}
			break;
		default: break;
		}
	}

	void SoundManager::AllStop() {
		for (int i = D_PLAY_SOUND_BGM; i < D_PLAY_SOUND_MAX; i++) {
			StopSoundEX(i);
		}
		m_pDS8->Release();
		m_pDS8 = NULL;
	}

	int SoundManager::IsPlay() {
		for (int i = 0; i < D_SOUND_MAX; i++) {
			if (m_pSoundBuffer[i] != NULL) {
				DWORD state;
				m_pSoundBuffer[i]->GetStatus(&state);
				// ステータスが０の場合は終了状態
				if (state == 0) {
					m_pSoundBuffer[i]->Stop();
					SAFE_RELEASE(m_pSoundBuffer[i]);
				}
			}
		}
		return 0;
	}

	int SoundManager::GetPlaySlot() {
		for (int i = 1; i < D_SOUND_MAX; i++) {
			if (m_pSoundBuffer[i] == NULL) {
				return i;
			}
		}

		return -1;
	}

	int SoundManager::SoundFileOpen(string fileName, int playType, int port) {
		// Waveファイルオープン
		WAVEFORMATEX wFmt;
		char* pWaveData = 0;
		DWORD waveSize = 0;
		char str[256] = { 0 };
		sprintf_s(str, "%s", fileName.c_str());
		if (!OpenWaveFromFile(str, wFmt, &pWaveData, waveSize)) {
			Logger::OutputDebug("SoundManager.cpp SoundFileOpen end #1");
			return -1;
		}
		MyPlaySound(pWaveData, waveSize, wFmt, playType, port);
		return 0;
	}

	int SoundManager::MyPlaySound(char* pWaveData, DWORD waveSize, WAVEFORMATEX wFmt, int playType, int port) {
		DSBUFFERDESC dSBufferDesc;
		dSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
		dSBufferDesc.dwFlags = 0;
		dSBufferDesc.dwBufferBytes = waveSize;
		dSBufferDesc.dwReserved = 0;
		dSBufferDesc.lpwfxFormat = &wFmt;
		dSBufferDesc.guid3DAlgorithm = GUID_NULL;

		IDirectSoundBuffer* ptmpBuf = 0;
		m_pDS8->CreateSoundBuffer(&dSBufferDesc, &ptmpBuf, NULL);
		ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&m_pSoundBuffer[port]);
		ptmpBuf->Release();
		if (m_pSoundBuffer[port] == 0) {
			m_pDS8->Release();
			Logger::OutputDebug("SoundManager.cpp playSound end #1");
			return -1;
		}

		// セカンダリバッファにWaveデータ書き込み
		LPVOID lpvWrite = 0;
		DWORD dwLength = 0;
		if (DS_OK == m_pSoundBuffer[port]->Lock(0, 0, &lpvWrite, &dwLength, NULL, NULL, DSBLOCK_ENTIREBUFFER)) {
			memcpy(lpvWrite, pWaveData, dwLength);
			m_pSoundBuffer[port]->Unlock(lpvWrite, dwLength, NULL, 0);
		}
		delete[] pWaveData; // 元音はもういらない

		// 再生
		m_pSoundBuffer[port]->Play(0, 0, playType);
		return 0;
	}

	int SoundManager::OpenWaveFromFile(string filePath, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize) {
		if (filePath.c_str() == 0) {
			Logger::OutputDebug("SoundManager.cpp OpenWaveFromFile end #1");
			return -1;
		}

		HMMIO hMmio = NULL;
		MMIOINFO mmioInfo;

		// Waveファイルオープン
		memset(&mmioInfo, 0, sizeof(MMIOINFO));
		hMmio = mmioOpen(const_cast<LPSTR>(filePath.c_str()), &mmioInfo, MMIO_READ);
		if (!hMmio) {
			Logger::OutputDebug("SoundManager.cpp OpenWaveFromFile end #2");
			return -1; // ファイルオープン失敗
		}
		return OpenWave(hMmio, waveFormatEx, ppData, dataSize);
	}

	int SoundManager::OpenWave(HMMIO hMmio, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize) {
		// RIFFチャンク検索
		MMRESULT mmRes = NULL;
		MMCKINFO riffChunk;
		riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);
		if (mmRes != MMSYSERR_NOERROR) {
			mmioClose(hMmio, 0);
			Logger::OutputDebug("SoundManager.cpp OpenWave end #3");
			return -1;
		}

		// フォーマットチャンク検索
		MMCKINFO formatChunk;
		formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);
		if (mmRes != MMSYSERR_NOERROR) {
			mmioClose(hMmio, 0);
			Logger::OutputDebug("SoundManager.cpp OpenWave end #4");
			return -1;
		}
		DWORD fmsize = formatChunk.cksize;
		DWORD size = mmioRead(hMmio, (HPSTR)&waveFormatEx, fmsize);
		if (size != fmsize) {
			mmioClose(hMmio, 0);
			Logger::OutputDebug("SoundManager.cpp OpenWave end #5");
			return -1;
		}

		mmioAscend(hMmio, &formatChunk, 0);

		// データチャンク検索
		MMCKINFO dataChunk;
		dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);
		if (mmRes != MMSYSERR_NOERROR) {
			mmioClose(hMmio, 0);
			Logger::OutputDebug("SoundManager.cpp OpenWave end #6");
			return -1;
		}
		*ppData = new char[dataChunk.cksize];
		size = mmioRead(hMmio, (HPSTR)*ppData, dataChunk.cksize);
		if (size != dataChunk.cksize) {
			delete[] * ppData;
			Logger::OutputDebug("SoundManager.cpp OpenWave end #7");
			return -1;
		}
		dataSize = size;

		// ハンドルクローズ
		mmioClose(hMmio, 0);
		return 0;
	}
}
