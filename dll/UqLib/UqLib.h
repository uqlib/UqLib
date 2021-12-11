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
 * 画面サイズ初期化
 *
 * @param width  幅
 * @param height 高さ
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int InitScreenSize(int width, int height);

/**
 * アプリケーション終了
 */
extern "C" __declspec (dllexport) void ApplicationQuit();

/**
 * 待機処理
 *
 * @param waitTime 待機時間（msec）
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int WaitProcessing(int waitTime);

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
 * ウィンドウタイトル設定
 *
 * @param title タイトル
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int SetWindowTitle(const char* title);

/**
 * ライン描画
 *
 * @param x             X座標
 * @param y             Y座標
 * @param ax            追加X座標
 * @param ay            追加Y座標
 * @param hexColorCode  16進数カラーコード
 * @param width         幅
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int DrawLine(int x, int y, int ax, int ay, UINT32 hexColorCode, float width);

/**
 * ライン描画（透過あり）
 *
 * @param x             X座標
 * @param y             Y座標
 * @param ax            追加X座標
 * @param ay            追加Y座標
 * @param hexColorCode  16進数カラーコード
 * @param width         幅
 * @param opacity       不透明度（透明 0.0f ～ 1.0f 不透明）
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int DrawLineAlpha(int x, int y, int ax, int ay, UINT32 hexColorCode, float width, float opacity);

/**
 * 四角形描画
 *
 * @param x             X座標
 * @param y             Y座標
 * @param ax            追加X座標
 * @param ay            追加Y座標
 * @param hexColorCode  16進数カラーコード
 * @param strokeWidth   線の太さ
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int DrawSquare(int x, int y, int sx, int sy, UINT32 hexColorCode, float strokeWidth);

/**
 * 四角形描画（透過あり）
 *
 * @param x             X座標
 * @param y             Y座標
 * @param ax            追加X座標
 * @param ay            追加Y座標
 * @param hexColorCode  16進数カラーコード
 * @param strokeWidth   線の太さ
 * @param opacity       不透明度（透明 0.0f ～ 1.0f 不透明）
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int DrawSquareAlpha(int x, int y, int sx, int sy, UINT32 hexColorCode, float strokeWidth, float opacity);

/**
 * 四角形 塗りつぶし描画
 *
 * @param x             X座標
 * @param y             Y座標
 * @param ax            追加X座標
 * @param ay            追加Y座標
 * @param hexColorCode  16進数カラーコード
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int FillSquare(int x, int y, int sx, int sy, UINT32 hexColorCode);

/**
 * 四角形 塗りつぶし描画（透過あり）
 *
 * @param x             X座標
 * @param y             Y座標
 * @param ax            追加X座標
 * @param ay            追加Y座標
 * @param hexColorCode  16進数カラーコード
 * @param opacity       不透明度（透明 0.0f ～ 1.0f 不透明）
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int FillSquareAlpha(int x, int y, int sx, int sy, UINT32 hexColorCode, float opacity);

/**
 * 丸め四角形描画
 *
 * @param x             X座標
 * @param y             Y座標
 * @param ax            追加X座標
 * @param ay            追加Y座標
 * @param hexColorCode  16進数カラーコード
 * @param strokeWidth   線の太さ
 * @param radius        0：角のまま　、0.1以上（角を丸める）
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int DrawRoundedSquare(int x, int y, int sx, int sy, UINT32 hexColorCode, float strokeWidth, float radius);

/**
 * 丸め四角形描画（透過あり）
 *
 * @param x             X座標
 * @param y             Y座標
 * @param ax            追加X座標
 * @param ay            追加Y座標
 * @param hexColorCode  16進数カラーコード
 * @param strokeWidth   線の太さ
 * @param radius        0：角のまま　、0.1以上（角を丸める）
 * @param opacity       不透明度（透明 0.0f ～ 1.0f 不透明）
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int DrawRoundedSquareAlpha(int x, int y, int sx, int sy, UINT32 hexColorCode, float strokeWidth, float radius, float opacity);

/**
 * 丸め四角形 塗りつぶし描画
 *
 * @param x             X座標
 * @param y             Y座標
 * @param ax            追加X座標
 * @param ay            追加Y座標
 * @param hexColorCode  16進数カラーコード
 * @param radius        0：角のまま　、0.1以上（角を丸める）
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int FillRoundedSquare(int x, int y, int sx, int sy, UINT32 hexColorCode, float radius);

/**
 * 丸め四角形 塗りつぶし描画（透過あり）
 *
 * @param x             X座標
 * @param y             Y座標
 * @param ax            追加X座標
 * @param ay            追加Y座標
 * @param hexColorCode  16進数カラーコード
 * @param radius        0：角のまま　、0.1以上（角を丸める）
 * @param opacity       不透明度（透明 0.0f ～ 1.0f 不透明）
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int FillRoundedSquareAlpha(int x, int y, int sx, int sy, UINT32 hexColorCode, float radius, float opacity);

/**
 * 楕円描画
 *
 * @param x             X座標
 * @param y             Y座標
 * @param width         幅（半径）
 * @param height        高さ（半径）
 * @param hexColorCode  16進数カラーコード
 * @param strokeWidth   線の太さ
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int DrawEllipse(int x, int y, int width, int height, UINT32 hexColorCode, float strokeWidth);

/**
 * 楕円描画（透過あり）
 *
 * @param x             X座標
 * @param y             Y座標
 * @param width         幅（半径）
 * @param height        高さ（半径）
 * @param hexColorCode  16進数カラーコード
 * @param strokeWidth   線の太さ
 * @param opacity       不透明度（透明 0.0f ～ 1.0f 不透明）
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int DrawEllipseAlpha(int x, int y, int width, int height, UINT32 hexColorCode, float strokeWidth, float opacity);

/**
 * 楕円 塗りつぶし描画
 *
 * @param x             X座標
 * @param y             Y座標
 * @param width         幅（半径）
 * @param height        高さ（半径）
 * @param hexColorCode  16進数カラーコード
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int FillEllipse(int x, int y, int width, int height, UINT32 hexColorCode);

/**
 * 楕円 塗りつぶし描画（透過あり）
 *
 * @param x             X座標
 * @param y             Y座標
 * @param width         幅（半径）
 * @param height        高さ（半径）
 * @param hexColorCode  16進数カラーコード
 * @param opacity       不透明度（透明 0.0f ～ 1.0f 不透明）
 * @return 成功（0）、失敗（-1）
 */
extern "C" __declspec (dllexport) int FillEllipseAlpha(int x, int y, int width, int height, UINT32 hexColorCode, float opacity);

/**
 * 左クリックポイント取得
 *
 * @param x X座標
 * @param y Y座標
 */
extern "C" __declspec (dllexport) void GetLeftClickPoint(int* x, int* y);

#endif
