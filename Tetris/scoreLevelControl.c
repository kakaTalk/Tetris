#include "keyCurControl.h"

void DrawScoreBoard(void) {
	SetCurrentCursorPos(30, 4);
	printf("$ 현재 레벨: %d &");

	SetCurrentCursorPos(30, 6);
	printf("$ 현재 점수: %d &");
}