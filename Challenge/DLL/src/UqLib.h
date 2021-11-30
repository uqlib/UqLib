//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#ifndef UQ_LIB_H
#define UQ_LIB_H

#include "SystemClass.h"
#include "Logger.h"
#include "Constants.h"

/**
 * UqLib初期化
 *
 * @param title タイトル
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int UqLibInit(const char* title);

/**
 * UqLib終了処理
 *
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int UqLibEnd();

/**
 * 描画開始
 *
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int BeginDrawing();

/**
 * 描画終了
 *
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int EndDrawing();

/**
 * ウィンドウメッセージ更新
 *
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int UpdateWindowMessage();

/**
 * フォントコンテナ作成
 *
 * @param height   高さ
 * @param fontName フォント名
 * @return フォントID
 */
extern "C" __declspec (dllexport) int CreateFontContener(int height, const char* fontName);

/**
 * ファイルからテクスチャ作成
 *
 * @param filename ファイル名
 * @return グラフィックID（失敗時は-1）
 */
extern "C" __declspec (dllexport) int CreateTextureFromFile(const char * filename);

/**
 * Datファイルからテクスチャ作成
 * 
 * @param filename ファイル名
 * @return グラフィックID（失敗時は-1）
 */
extern "C" __declspec (dllexport) int CreateTextureFromDatFile(const char* fileName);

/**
 * テクスチャ描画
 *
 * @param x         X座標
 * @param y         Y座標
 * @param graphicId グラフィックID
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int DrawTexture(int x, int y, int graphicId);

/**
 * テクスチャ描画（透過あり）
 *
 * @param x         X座標
 * @param y         Y座標
 * @param graphicId グラフィックID
 * @param opacity   不透明度（透明 0.0f ～ 1.0f 不透明）
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int DrawTextureAlpha(int x, int y, int graphicId, float opacity);

extern "C" __declspec (dllexport) int DrawString(int x, int y, const char* text, int fontId, UINT32 hexColorCode);

extern "C" __declspec (dllexport) int DrawLine(int x, int y, int ax, int ay, UINT32 hexColorCode, float width);

#endif
