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
 * UqLib������
 *
 * @param title �^�C�g��
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int UqLibInit(const char* title);

/**
 * UqLib�I������
 *
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int UqLibEnd();

/**
 * �t�H���g�R���e�i�쐬
 *
 * @param height   ����
 * @param fontName �t�H���g��
 * @return �t�H���gID
 */
extern "C" __declspec (dllexport) int CreateFontContener(int height, const char* fontName);

/**
 * �t�@�C������e�N�X�`���쐬
 *
 * @param filename �t�@�C����
 * @return �O���t�B�b�NID�i���s����-1�j
 */
extern "C" __declspec (dllexport) int CreateTextureFromFile(const char * filename);

/**
 * Dat�t�@�C������e�N�X�`���쐬
 * 
 * @param filename �t�@�C����
 * @return �O���t�B�b�NID�i���s����-1�j
 */
extern "C" __declspec (dllexport) int CreateTextureFromDatFile(const char* fileName);

/**
 * �e�N�X�`���`��
 *
 * @param x         X���W
 * @param y         Y���W
 * @param graphicId �O���t�B�b�NID
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int DrawTexture(int x, int y, int graphicId);

/**
 * �e�N�X�`���`��i���߂���j
 *
 * @param x         X���W
 * @param y         Y���W
 * @param graphicId �O���t�B�b�NID
 * @param opacity   �s�����x�i���� 0.0f �` 1.0f �s�����j
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int DrawTextureAlpha(int x, int y, int graphicId, float opacity);

/**
 * �e�N�X�`���`��N���b�v
 *
 * @param x         �]����X���W
 * @param y         �]����Y���W
 * @param graphicId �O���t�B�b�NID
 * @param sx        �]����X���W
 * @param sy        �]����Y���W
 * @param sw        �]������`�T�C�Y�i���j
 * @param sh        �]������`�T�C�Y�i�����j
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int DrawTextureClip(int x, int y, int graphicId, int sx, int sy, int sw, int sh);

/**
 * �e�N�X�`���`��N���b�v�i���߂���j
 *
 * @param x         �]����X���W
 * @param y         �]����Y���W
 * @param graphicId �O���t�B�b�NID
 * @param sx        �]����X���W
 * @param sy        �]����Y���W
 * @param sw        �]������`�T�C�Y�i���j
 * @param sh        �]������`�T�C�Y�i�����j
 * @param opacity   �s�����x�i���� 0.0f �` 1.0f �s�����j
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int DrawTextureClipAlpha(int x, int y, int graphicId, int sx, int sy, int sw, int sh, float opacity);

/**
 * ������`��
 *
 * @param x             X���W
 * @param y             Y���W
 * @param text          �e�L�X�g
 * @param fontId        �t�H���gID
 * @param hexColorCode  16�i���J���[�R�[�h
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int DrawString(int x, int y, const char* text, int fontId, UINT32 hexColorCode);

/**
 * ������`��i���߂���j
 *
 * @param x             X���W
 * @param y             Y���W
 * @param text          �e�L�X�g
 * @param fontId        �t�H���gID
 * @param hexColorCode  16�i���J���[�R�[�h
 * @param opacity       �s�����x�i���� 0.0f �` 1.0f �s�����j
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int DrawStringAlpha(int x, int y, const char* text, int fontId, UINT32 hexColorCode, float opacity);

/**
 * �E�B���h�E���b�Z�[�W�X�V
 *
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int UpdateWindowMessage();

/**
 * �L�[�����������m�F
 *
 * @param keyCode �L�[�R�[�h
 * @return 0�F�����Ă��Ȃ��A1�F������
 */
extern "C" __declspec (dllexport) int CheckPressedKey(int keyCode);

/**
 * �L�[�������Ă��邩�m�F
 *
 * @param keyCode �L�[�R�[�h
 * @return 0�F�����Ă��Ȃ��A1�F�����Ă���
 */
extern "C" __declspec (dllexport) int CheckPressKey(int keyCode);

/**
 * �`��J�n
 *
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int BeginDrawing();

/**
 * �`��I��
 *
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int EndDrawing();

/**
 * �t�@�C������T�E���h�Đ�
 *
 * @param fileName �t�@�C����
 * @param playType �Đ��^�C�v
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int PlaySoundFromFile(const char* fileName, int playType);

/**
 * �o�^�E�Đ���ԃ`�F�b�N
 *
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int CheckSoundPlay();

/**
 * �A�v���P�[�V�����I��
 */
extern "C" __declspec (dllexport) void ApplicationQuit();

/**
 * �E�B���h�E�^�C�g���ݒ�
 *
 * @param title �^�C�g��
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int SetWindowTitle(const char* title);

/**
 * ���C���`��
 *
 * @param x             X���W
 * @param y             Y���W
 * @param ax            �ǉ�X���W
 * @param ay            �ǉ�Y���W
 * @param hexColorCode  16�i���J���[�R�[�h
 * @param width         ��
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int DrawLine(int x, int y, int ax, int ay, UINT32 hexColorCode, float width);

/**
 * ���C���`��i���߂���j
 *
 * @param x             X���W
 * @param y             Y���W
 * @param ax            �ǉ�X���W
 * @param ay            �ǉ�Y���W
 * @param hexColorCode  16�i���J���[�R�[�h
 * @param width         ��
 * @param opacity       �s�����x�i���� 0.0f �` 1.0f �s�����j
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int DrawLineAlpha(int x, int y, int ax, int ay, UINT32 hexColorCode, float width, float opacity);

/**
 * �l�p�`�`��
 *
 * @param x             X���W
 * @param y             Y���W
 * @param ax            �ǉ�X���W
 * @param ay            �ǉ�Y���W
 * @param hexColorCode  16�i���J���[�R�[�h
 * @param strokeWidth   ���̑���
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int DrawSquare(int x, int y, int sx, int sy, UINT32 hexColorCode, float strokeWidth);

/**
 * �l�p�`�`��i���߂���j
 *
 * @param x             X���W
 * @param y             Y���W
 * @param ax            �ǉ�X���W
 * @param ay            �ǉ�Y���W
 * @param hexColorCode  16�i���J���[�R�[�h
 * @param strokeWidth   ���̑���
 * @param opacity       �s�����x�i���� 0.0f �` 1.0f �s�����j
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int DrawSquareAlpha(int x, int y, int sx, int sy, UINT32 hexColorCode, float strokeWidth, float opacity);

/**
 * �l�p�` �h��Ԃ��`��
 *
 * @param x             X���W
 * @param y             Y���W
 * @param ax            �ǉ�X���W
 * @param ay            �ǉ�Y���W
 * @param hexColorCode  16�i���J���[�R�[�h
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int FillSquare(int x, int y, int sx, int sy, UINT32 hexColorCode);

/**
 * �l�p�` �h��Ԃ��`��i���߂���j
 *
 * @param x             X���W
 * @param y             Y���W
 * @param ax            �ǉ�X���W
 * @param ay            �ǉ�Y���W
 * @param hexColorCode  16�i���J���[�R�[�h
 * @param opacity       �s�����x�i���� 0.0f �` 1.0f �s�����j
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int FillSquareAlpha(int x, int y, int sx, int sy, UINT32 hexColorCode, float opacity);

/**
 * �ۂߎl�p�`�`��
 *
 * @param x             X���W
 * @param y             Y���W
 * @param ax            �ǉ�X���W
 * @param ay            �ǉ�Y���W
 * @param hexColorCode  16�i���J���[�R�[�h
 * @param strokeWidth   ���̑���
 * @param radius        0�F�p�̂܂܁@�A0.1�ȏ�i�p���ۂ߂�j
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int DrawRoundedSquare(int x, int y, int sx, int sy, UINT32 hexColorCode, float strokeWidth, float radius);

/**
 * �ۂߎl�p�`�`��i���߂���j
 *
 * @param x             X���W
 * @param y             Y���W
 * @param ax            �ǉ�X���W
 * @param ay            �ǉ�Y���W
 * @param hexColorCode  16�i���J���[�R�[�h
 * @param strokeWidth   ���̑���
 * @param radius        0�F�p�̂܂܁@�A0.1�ȏ�i�p���ۂ߂�j
 * @param opacity       �s�����x�i���� 0.0f �` 1.0f �s�����j
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int DrawRoundedSquareAlpha(int x, int y, int sx, int sy, UINT32 hexColorCode, float strokeWidth, float radius, float opacity);

/**
 * �ۂߎl�p�` �h��Ԃ��`��
 *
 * @param x             X���W
 * @param y             Y���W
 * @param ax            �ǉ�X���W
 * @param ay            �ǉ�Y���W
 * @param hexColorCode  16�i���J���[�R�[�h
 * @param radius        0�F�p�̂܂܁@�A0.1�ȏ�i�p���ۂ߂�j
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int FillRoundedSquare(int x, int y, int sx, int sy, UINT32 hexColorCode, float radius);

/**
 * �ۂߎl�p�` �h��Ԃ��`��i���߂���j
 *
 * @param x             X���W
 * @param y             Y���W
 * @param ax            �ǉ�X���W
 * @param ay            �ǉ�Y���W
 * @param hexColorCode  16�i���J���[�R�[�h
 * @param radius        0�F�p�̂܂܁@�A0.1�ȏ�i�p���ۂ߂�j
 * @param opacity       �s�����x�i���� 0.0f �` 1.0f �s�����j
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int FillRoundedSquareAlpha(int x, int y, int sx, int sy, UINT32 hexColorCode, float radius, float opacity);

/**
 * �ȉ~�`��
 *
 * @param x             X���W
 * @param y             Y���W
 * @param width         ���i���a�j
 * @param height        �����i���a�j
 * @param hexColorCode  16�i���J���[�R�[�h
 * @param strokeWidth   ���̑���
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int DrawEllipse(int x, int y, int width, int height, UINT32 hexColorCode, float strokeWidth);

/**
 * �ȉ~�`��i���߂���j
 *
 * @param x             X���W
 * @param y             Y���W
 * @param width         ���i���a�j
 * @param height        �����i���a�j
 * @param hexColorCode  16�i���J���[�R�[�h
 * @param strokeWidth   ���̑���
 * @param opacity       �s�����x�i���� 0.0f �` 1.0f �s�����j
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int DrawEllipseAlpha(int x, int y, int width, int height, UINT32 hexColorCode, float strokeWidth, float opacity);

/**
 * �ȉ~ �h��Ԃ��`��
 *
 * @param x             X���W
 * @param y             Y���W
 * @param width         ���i���a�j
 * @param height        �����i���a�j
 * @param hexColorCode  16�i���J���[�R�[�h
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int FillEllipse(int x, int y, int width, int height, UINT32 hexColorCode);

/**
 * �ȉ~ �h��Ԃ��`��i���߂���j
 *
 * @param x             X���W
 * @param y             Y���W
 * @param width         ���i���a�j
 * @param height        �����i���a�j
 * @param hexColorCode  16�i���J���[�R�[�h
 * @param opacity       �s�����x�i���� 0.0f �` 1.0f �s�����j
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int FillEllipseAlpha(int x, int y, int width, int height, UINT32 hexColorCode, float opacity);

/**
 * ���N���b�N�|�C���g�擾
 *
 * @param x X���W
 * @param y Y���W
 */
extern "C" __declspec (dllexport) void GetLeftClickPoint(int* x, int* y);

/**
 * �ҋ@����
 *
 * @param waitTime �ҋ@���ԁimsec�j
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int WaitProcessing(int waitTime);

/**
 * ��ʃT�C�Y������
 *
 * @param width  ��
 * @param height ����
 * @return �����i0�j�A���s�i-1�j
 */
extern "C" __declspec (dllexport) int InitScreenSize(int width, int height);

#endif
