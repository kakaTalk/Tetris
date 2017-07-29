#include "keyCurControl.h"
static int speed = 10;
static int level = 0;

void DrawScoreBoard(void) {
	SetCurrentCursorPos(30, 4);
	printf("$ 현재 레벨: %d &", level);

	SetCurrentCursorPos(30, 6);
	printf("$ 현재 점수: %d &", speed);
}

int getnowLevel(void) {
	return level;
}
void setNowLevel(void) {
	level += 1;
}

void serControlSpeed(void) {
	 speed += 5;
}
int getcontrolSpeed(void) {
	return speed;
}