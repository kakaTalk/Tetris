#pragma once
#include "common.h"
//커서제거
void RemoveCursor(void);

//콘솔 맞춤
void SetCurrentCursorPos(int x, int y);

//현재위치반환
COORD GetCurrnetCursorPos(void);

void getMoveBlock(void);
void InitKeyDelayRate(int rate);
#pragma once
