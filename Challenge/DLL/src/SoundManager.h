//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#ifndef UQ_LIB_SOUNDMANAGER_H
#define UQ_LIB_SOUNDMANAGER_H

#include <windows.h>
#include <mutex>
#include <string>
#include <dsound.h>
#include "Logger.h"

namespace uq_lib {

	class SoundManager
	{
	public:

		/**
		 * インスタンス取得
		 *
		 * @return インスタンス
		 */
		 // インスタンス取得
		static SoundManager* GetInstance() {
			if (!m_sm && m_destroyFlg == true) m_sm = new SoundManager();
			return m_sm;
		}

		/**
		 * 破棄
		 */
		static void Destroy() {
			m_destroyFlg = false;
			delete m_sm;
			m_sm = NULL;
		}

		/**
		 * デストラクタ
		 */
		virtual ~SoundManager();


		/**
		 * 初期化
		 *
		 * @param hWnd ウィンドウハンドル
		 * @return 成功（0）、失敗（-1）
		 */
		int Init(HWND hWnd);

		/**
		 * ファイルからサウンド再生
		 *
		 * @param fileName ファイル名
		 * @param playType 再生タイプ
		 * @return 成功（0）、失敗（-1）
		 */
		int PlaySoundFromFile(std::string fileName, int playType);

		/**
		 * サウンド停止
		 *
		 * @param slotNum スロット番号
		 */
		void StopSoundEX(int slotNum);

		/**
		 * サウンド全停止
		 */
		void AllStop();

		/**
		 * 登録・再生状態チェック
		 *
		 * @return 成功（0）、失敗（-1）
		 */
		int IsPlay();

	private:
		// シングルトン
		static SoundManager* m_sm;
		static bool m_destroyFlg; // Phoenix Singleton回避用
		HWND m_hwnd;
		IDirectSound8* m_pDS8;

		//! サウンドバッファ領域(要検討 サウンドポート分やBGMやSEから分離するなどの検討)
		IDirectSoundBuffer8* m_pSoundBuffer[D_SOUND_MAX];

		/**
		 * コンストラクタ
		 */
		SoundManager();

		/**
		 * 再生可能スロット取得
		 *
		 * @return スロット番号
		 */
		int GetPlaySlot();

		/**
		 * サウンドファイル読み込み
		 *
		 * @param fileName ファイル名
		 * @param playType 再生タイプ
		 * @param port     ポート
		 * @return 成功（0）、失敗（-1）
		 */
		int SoundFileOpen(std::string fileName, int playType, int port);

		/**
		 * サウンド再生
		 *
		 * @param pWaveData wavデータ
		 * @param waveSize  wavサイズ
		 * @param wFmt      フォーマット
		 * @param playType  再生タイプ
		 * @param port      ポート
		 * @return 成功（0）、失敗（-1）
		 */
		int MyPlaySound(char* pWaveData, DWORD waveSize, WAVEFORMATEX wFmt, int playType, int port);

		/**
		 * ファイルからWavファイルオープン
		 *
		 * @param filePath     ファイルパス
		 * @param waveFormatEx wavフォーマット
		 * @param ppData       データ
		 * @param dataSize     データサイズ
		 * @return 成功（0）、失敗（-1）
		 */
		int OpenWaveFromFile(std::string filePath, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize);

		/**
		 * wav読み込み
		 *
		 * @param hMmio        マルチメディアファイル入出力のハンドル
		 * @param waveFormatEx wavフォーマット
		 * @param ppData       データ
		 * @param dataSize     データサイズ
		 * @return 成功（0）、失敗（-1）
		 */
		int OpenWave(HMMIO hMmio, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize);
	};
}

#endif // UQ_LIB_SOUNDMANAGER_H
