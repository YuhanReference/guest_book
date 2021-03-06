// GuestBook_Editor.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#pragma once
#include "framework.h"
#include "GuestBook_Editor.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_ LPWSTR    lpCmdLine,
					 _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_GUESTBOOKEDITOR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GUESTBOOKEDITOR));

	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GUESTBOOKEDITOR));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = CreateSolidBrush(WINDOW_COLOR);
	wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GUESTBOOKEDITOR);
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	  CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
	  return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

//전역 변수 선언
vector<PINFO> g_Pinfo;
vector<GB_BUTTON *> buttons;
HWND g_hWnd;
bool is_replay = false;
HBRUSH win_brush;
HFONT font;
//GB_BUTTON* btn_test = new GB_BUTTON(L"테스트", 50, 30, 150, 50);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int pre_x, pre_y;
	static bool left = false;
	// 팔레트
	static Palette* palette;
	// PEN
	static GB_Pen* pen;

	//HDC hdc;
	COLORREF ret;
	//PINFO temp_pinfo;
	//HPEN npen, open;
	//int x, y;
	


	switch (message)
	{
	case WM_CREATE:
		g_hWnd = hWnd;
		palette = new Palette(Palette_x, Palette_y);
		pen = new GB_Pen(Pen_x, Pen_y, Pen_width, Pen_height);

		font = CreateFont(35, 0, 0, 0, 0, 0, 0, 0,
			HANGEUL_CHARSET, 0, 0, 0,
			VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
		win_brush = CreateSolidBrush(WINDOW_COLOR);

		//버튼 생성 및 할당
		buttons.push_back(new GB_BUTTON(L"테스트",100, 50, 30, 150, 50));
		buttons.push_back(new GB_BUTTON(L"┼", PLUS, PLUS_x, PLUS_y, PLUS_size));
		buttons.push_back(new GB_BUTTON(MINUS_text, MINUS, MINUS_x, MINUS_y, MINUS_size));
		break;
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// 메뉴 선택을 구문 분석합니다:
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
			
			// 서명 영역 출력
			paint_signed_area(hWnd, hdc);
			// 팔레트 출력
			palette->paint(hWnd, hdc);
			// 펜 형태 출력
			pen->paint(hWnd, hdc);
			// 버튼 출력

			//btn_test->paint(hWnd, hdc);
			for (const auto i : buttons)
				i->paint(hWnd, hdc);

			EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:

		delete(palette);

		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:
		// 팔레트가 눌렸는지 확인
		ret = palette->is_press(lParam);
		if (ret != -1)
		{
			pen->set_color(ret);
			InvalidateRect(hWnd, &pen->area, TRUE);
		}

		// 버튼이 눌렸는지 확인 및 버튼 처리
		switch (button_check(lParam))
		{
		case 0:
			break;
		case PLUS:
			pen->set_size_up();
			InvalidateRect(hWnd, &pen->area, TRUE);
			break;
		case MINUS:
			pen->set_size_down();
			InvalidateRect(hWnd, &pen->area, TRUE);
		default:
			break;
		}

	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
		mouse_proc(hWnd, message, lParam, pen->size, pen->col);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



// 리플레이 스레드
DWORD WINAPI drawing(LPVOID points)
{
	HDC hdc;
	HPEN npen;
	int x, y;
	hdc = GetDC(g_hWnd);
	is_replay = true;

	npen = CreatePen(PS_SOLID, 10, RGB(255, 255, 255));

	while (true)
	{
		InvalidateRect(g_hWnd, NULL, TRUE);
		for (size_t i = 0; i < (int)(g_Pinfo.size() - 1); i++)
		{
			if (g_Pinfo.size() == 0) break;
			switch (g_Pinfo[i].state)
			{
			case WM_LBUTTONDOWN:
				//MessageBox(hWnd, L"실행", L"L버튼", MB_OK);
				DeleteObject(npen);
				npen = CreatePen(PS_SOLID, g_Pinfo[i].cWidth, g_Pinfo[i].color);
				SelectObject(hdc, npen);

				x = LOWORD(g_Pinfo[i].lparm);
				y = HIWORD(g_Pinfo[i].lparm);

				MoveToEx(hdc, x, y, NULL);
				LineTo(hdc, x + 1, y + 1);  //점찍기
				break;

			case WM_MOUSEMOVE:
				LineTo(hdc, LOWORD(g_Pinfo[i].lparm), HIWORD(g_Pinfo[i].lparm));
				if (g_Pinfo[i + 1].state == WM_MOUSEMOVE)  // 다음벡터도 WM_MOUSEMOVE일 경우에만 sleep 
					Sleep(g_Pinfo[i + 1].ctime - g_Pinfo[i].ctime);
				break;
			case WM_LBUTTONUP:
				LineTo(hdc, LOWORD(g_Pinfo[i].lparm), HIWORD(g_Pinfo[i].lparm));
				break;

			default:
				break;
			}
		}
		Sleep(3000);
	}
	ReleaseDC(g_hWnd, hdc);
	is_replay = false;
	return 0;
}

// 서명영역인지 반환해주는 함수
bool is_area(LPARAM lParam)
{
   do
	{
		if (LOWORD(lParam) < BOUNDARY_LEFT + 3)     // left가 범위 밖이면 break
			break;
		if (BOUNDARY_RIGHT - 3 < LOWORD(lParam))    // right가 범위 밖이면 break
			break;
		if (HIWORD(lParam) < BOUNDARY_TOP + 3)    // top가 범위 밖이면 break
			break;
		if (BOUNDARY_BOTTOM - 3 < HIWORD(lParam))    // bottom가 범위 밖이면 break
			break;
		return true;
	} while (1);
	return false;
}


void paint_signed_area(HWND hWnd, HDC hdc)
{
	HBRUSH nbrush, obrush;

	nbrush = CreateSolidBrush(WINDOW_COLOR);
	obrush = (HBRUSH)SelectObject(hdc, nbrush);

	SetBkColor(hdc, WINDOW_COLOR);  // TextOut의 배경색을 윈도우와 동일하게 변경
	SetBkMode(hdc, OPAQUE);     // TextOut의 배경을 불투명으로 변경
									// TRANSPARENT 투명, OPAQUE 불투명
	Rectangle(hdc, BOUNDARY_LEFT, BOUNDARY_TOP, BOUNDARY_RIGHT, BOUNDARY_BOTTOM);

	SelectObject(hdc, font);

	TextOut(hdc, BOUNDARY_LEFT + 15, BOUNDARY_TOP - 20, L"서명", lstrlenW(L"서명"));
	
	SelectObject(hdc, obrush);
	DeleteObject(obrush);
}


void mouse_proc(HWND hWnd, UINT message, LPARAM lParam, int size, COLORREF col)
{
	static int pre_x, pre_y;
	static bool left = false;

	HDC hdc;
	PINFO temp_pinfo;
	HPEN npen, open;
	int x, y;

	if (!is_area(lParam))
	{
		left = false;
		return;
	}

	hdc = GetDC(hWnd);

	npen = CreatePen(PS_SOLID, size, col);
	open = (HPEN)SelectObject(hdc, npen);

	x = LOWORD(lParam);
	y = HIWORD(lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:

		left = true;
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x, y + 1);
		
		pre_x = x;
		pre_y = y;

		temp_pinfo.lparm = lParam;
		temp_pinfo.state = message;
		temp_pinfo.color = col;
		temp_pinfo.cWidth = size;
		temp_pinfo.ctime = (DWORD)GetTickCount64();
		g_Pinfo.push_back(temp_pinfo);
		break;

	case WM_MOUSEMOVE:

		if (left)
		{
			left = true;
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, pre_x, pre_y);

			pre_x = x;
			pre_y = y;

			temp_pinfo.lparm = lParam;
			temp_pinfo.state = message;
			temp_pinfo.color = col;
			temp_pinfo.cWidth = size;
			temp_pinfo.ctime = (DWORD)GetTickCount64();
			g_Pinfo.push_back(temp_pinfo);
		}
		break;

	case WM_LBUTTONUP:
		if (left)
		{
			temp_pinfo.lparm = lParam;
			temp_pinfo.state = message;
			temp_pinfo.color = col;
			temp_pinfo.cWidth = size;
			temp_pinfo.ctime = (DWORD)GetTickCount64();
			g_Pinfo.push_back(temp_pinfo);
		}

		left = false;
		break;
	}

	DeleteObject(open);
	ReleaseDC(hWnd, hdc);
	return;
}

// 버튼체크
DWORD button_check(LPARAM lParam)
{
	DWORD msg;
	for (const auto i : buttons)
	{
		msg = i->is_press(lParam);
		if (msg)
			return msg;
	}
	return 0;
}