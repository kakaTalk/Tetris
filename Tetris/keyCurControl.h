#pragma once
#include "common.h"
//Ŀ������
void RemoveCursor(void);

//�ܼ� ����
void SetCurrentCursorPos(int x, int y);

//������ġ��ȯ
COORD GetCurrnetCursorPos(void);

void getMoveBlock(void);
void InitKeyDelayRate(int rate);
#pragma once
