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

/**
 * テクスチャ描画クリップ
 *
 * @param x         転送先X座標
 * @param y         転送先Y座標
 * @param graphicId グラフィックID
 * @param sx        転送元X座標
 * @param sy        転送元Y座標
 * @param sw        転送元矩形サイズ（幅）
 * @param sh        転送元矩形サイズ（高さ）
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int DrawTextureClip(int x, int y, int graphicId, int sx, int sy, int sw, int sh);

/**
 * テクスチャ描画クリップ（透過あり）
 *
 * @param x         転送先X座標
 * @param y         転送先Y座標
 * @param graphicId グラフィックID
 * @param sx        転送元X座標
 * @param sy        転送元Y座標
 * @param sw        転送元矩形サイズ（幅）
 * @param sh        転送元矩形サイズ（高さ）
 * @param opacity   不透明度（透明 0.0f ～ 1.0f 不透明）
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int DrawTextureClipAlpha(int x, int y, int graphicId, int sx, int sy, int sw, int sh, float opacity);

/**
 * 文字列描画
 *
 * @param x             X座標
 * @param y             Y座標
 * @param text          テキスト
 * @param fontId        フォントID
 * @param hexColorCode  16進数カラーコード
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int DrawString(int x, int y, const char* text, int fontId, UINT32 hexColorCode);

/**
 * 文字列描画（透過あり）
 *
 * @param x             X座標
 * @param y             Y座標
 * @param text          テキスト
 * @param fontId        フォントID
 * @param hexColorCode  16進数カラーコード
 * @param opacity       不透明度（透明 0.0f ～ 1.0f 不透明）
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int DrawStringAlpha(int x, int y, const char* text, int fontId, UINT32 hexColorCode, float opacity);

/**
 * キーを押したか確認
 *
 * @param keyCode キーコード
 * @return 0：押していない、1：押した
 */
extern "C" __declspec (dllexport) int CheckPressedKey(int keyCode);

/**
 * キーを押しているか確認
 *
 * @param keyCode キーコード
 * @return 0：押していない、1：押している
 */
extern "C" __declspec (dllexport) int CheckPressKey(int keyCode);

/**
 * ファイルからサウンド再生
 *
 * @param fileName ファイル名
 * @param playType 再生タイプ
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int PlaySoundFromFile(const char* fileName, int playType);

/**
 * 登録・再生状態チェック
 *
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int CheckSoundPlay();

/**
 * アプリケーション終了
 */
extern "C" __declspec (dllexport) void ApplicationQuit();

/**
 * ウィンドウタイトル設定
 *
 * @param title タイトル
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int SetWindowTitle(const char* title);

extern "C" __declspec (dllexport) int DrawLine(int x, int y, int ax, int ay, UINT32 hexColorCode, float width);

#endif
