#include "common.h"
#include "BlockStageControl.h"
#include "keyCurControl.h"

#define KEY_SENSITIVE 100
#define SYS_DELAY 20

static KeyDeleteRate = 0;

//기능 커서제거
void RemoveCursor(void) {
	CONSOLE_CURSOR_INFO curinfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
	curinfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}

//콘솔 맞춤
void SetCurrentCursorPos(int x, int y) { 
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//현재위치반환
COORD GetCurrnetCursorPos(void)
{
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curinfo;

	GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);

	curPoint.X = curinfo.dwCursorPosition.X;
	curPoint.Y = curinfo.dwCursorPosition.Y;

	return curPoint;
}


void getMoveBlock(void)
{
	int i;
	int true = 0;
	int before = KeyDeleteRate;

	for (i = 0; i < KEY_SENSITIVE; i++)
	{
		if (_kbhit() != 0)
		{
			switch (_getch())
			{
			case 224:
				break;
			case 75:
				LeftToMove();
				break;
			case 72:
				ChangBlock();
				break;
			case 77:
				RightToMove();
				break;
			case 32:
				KeyDeleteRate = 10000;
				true = 1;
				break;
			}
		}
		if (i % KeyDeleteRate == 0)
			Sleep(SYS_DELAY);
	}


}

void InitKeyDelayRate(int rate) {
		
		if (rate < 1)
			return;
		KeyDeleteRate = rate;
}
