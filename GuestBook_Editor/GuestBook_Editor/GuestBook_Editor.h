#pragma once

#include "resource.h"

#include "../../GB_moudle/GB_moudles.h"
#include "../../GB_moudle/GB_palette.h"
#include "../../GB_moudle/GB_Button.h"
#include "../../GB_moudle/GB_Sscreen_Save.h"
#include "../../GB_moudle/GB_Image.h"
#include "../../GB_moudle/GB_FIle_io.h"

using namespace std;


DWORD WINAPI drawing(LPVOID points);    // ���÷��� ������
DWORD WINAPI Scr_Save_thread(LPVOID points);
bool is_area(LPARAM lParam);            // ��ĥ ���� �������� ��ȯ���ִ� �Լ�
void paint_signed_area(HWND hWnd, HDC hdc);
void mouse_proc(HWND hWnd, UINT message, LPARAM lParam, int size, COLORREF col);
void mouse_paint(HDC hdc);
DWORD button_check(LPARAM lParam);
void Center_Screen(HWND window, DWORD style, DWORD exStyle); // Window ȭ�� ��� ��ġ�� �ű�� �Լ�
void Critical_flag(bool flag);
void Scr_Creitical_flag(bool flag);

#pragma once

// ���� ���α׷����� ����� �����
#ifndef WINDOW_COLOR
#define WINDOW_COLOR RGB(230,230,230)
#endif
#define Window_Size_Width 1420                  // ������ ����
#define Window_Size_Height 900                  // ������ ����

#define SRC_TIME 30000							// 30��

#define RAINBOW 1

#define FILE_PATH L"../../page"

// ���� ����
#define BOUNDARY_LEFT 70
#define BOUNDARY_RIGHT 1350
#define BOUNDARY_TOP 140
#define BOUNDARY_BOTTOM 800

// �ȷ�Ʈ
#define Palette_x 72
#define Palette_y 32

// ��
#define Pen_x 820		// �� ���� ���â ��ġ
#define Pen_y 25
#define Pen_width 200
#define Pen_height 50

#define Pen_text_x 700	// ��Ʈ ������ ��� ��ġ
#define Pen_text_y 35
#define Pen_size 30		// ��Ʈ������


// +��ư
#define PLUS 1001
#define PLUS_text L"+"	// ���� ��½� ����
#define PLUS_x 750
#define PLUS_y 30
#define PLUS_size 40

// - ��ư
#define MINUS 1002
#define MINUS_text L"��"
#define MINUS_x 650
#define MINUS_y 30
#define MINUS_size 40 

// CLEAR ��ư
#define CLEAR 1003
#define CLEAR_text L"CLEAR"
#define CLEAR_x 1250
#define CLEAR_y 30
#define CLEAR_width 100
#define CLEAR_height 40

// REPLAY ��ư
#define REPLAY 1004
#define REPLAY_text L"REPLAY"
#define REPLAY_x 1140
#define REPLAY_y 30
#define REPLAY_width 100
#define REPLAY_height 40

// RANDOM ��ư
#define RANDOM 1005
#define RANDOM_text L"RANDOM"
#define RANDOM_x 220
#define RANDOM_y 75
#define RANDOM_width 130
#define RANDOM_height 40

// CREDIT ��ư
#define CREDIT 1006
#define CREDIT_text L"CREDIT"
#define CREDIT_x 70
#define CREDIT_y 75
#define CREDIT_width 130
#define CREDIT_height 40



/*
#define
#define _text L""
#define _x
#define _y
#define _size
#define _width
#define _height
*/
