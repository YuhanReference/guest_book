// ��� ��ü���� ���̴� �ڵ�
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<vector>
#include<Windows.h>

typedef struct point_info
{
    LPARAM          lparm;      //��ǥ  
    int             cWidth;     //����
    COLORREF        color;      //����
    ULONGLONG           ctime;      //�ð�
    UINT            state;      //����{WM_LBUTTONDOWN }
}PINFO;

typedef struct scale_point_info
{
    std::vector<PINFO> pinfo;
    int x;
    int y;
    int width;
    int height;
}SPINFO;