#include "GB_moudles.h"

#define ScrnSave_Timer 7000			// ȭ�麸ȣ�� Ÿ�̸�
#define ScrnSaveToTime 30 * 1000	// ȭ�麸ȣ����� �ð� 30��

void ScrnTimer(HWND hWnd);			// ȭ�麸ȣ�� Ÿ�̸� �缳��
void ScrnSavePaint(HWND hWnd);		// ȭ�麸ȣ�� �׸���