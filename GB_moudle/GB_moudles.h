// ��� ��ü���� ���̴� �ڵ�
#pragma once

#include<vector>
#include<Windows.h>

typedef struct point_info
{
    LPARAM          lparm;      //��ǥ  
    int             cWidth;     //����
    COLORREF        color;      //����
    DWORD           ctime;      //�ð�
    UINT            state;      //����{WM_LBUTTONDOWN }
}PINFO;

