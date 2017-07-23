#include "keyCurControl.h"
#include "common.h"
#include "BlockInfo.h"
#include "BlockStageControl.h"
#include "DrawGameBoard.h"

#define GBOARD_WIDTH 10
#define GBOARD_HEIGHT 20

#define GBOARD_ORGIN_X 4
#define GBOARD_ORGIN_y 2

static int rotateSte = 0;
static int arr[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2] = { 0, };
static int currentBlockModel;
static int curPosX, curPosY;

//static int rotateState

void InitNewBlockPOs(int x, int y)
{
	if (x < 0 || y < 0)
		return;
	curPosX = x;
	curPosY = y;      
	
	SetCurrentCursorPos(x, y);   
}

void chooseBlock()
{
	srand((unsigned int)time(NULL));
	currentBlockModel = (rand() % 6) * 4;
}

int GetCurrentBlockIdx(void)
{
	return currentBlockModel + rotateSte;
}

void setCurrentBlock(int block) {
	currentBlockModel = block;
}

void showBlock(char blockInfo[][4]) {
	int x, y;
	COORD curPos = GetCurrnetCursorPos();
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{

			SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
			if (blockInfo[y][x] == 1)
				printf("■");
		}
	}
	SetCurrentCursorPos(curPos.X, curPos.Y);
}

void DelenteBlock(char blockInfo[][4]) {

	int x, y;
	COORD curPos = GetCurrnetCursorPos();

	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{

			SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
			if (blockInfo[y][x] == 1)
				printf("  ");
		}
	}
	SetCurrentCursorPos(curPos.X, curPos.Y);
}

int BlockDown(void)
{
	if (!checkBlockDown(curPosX, curPosY + 1, blockModel[GetCurrentBlockIdx()]))
	{
		AddCurrentBlockInfoToBoard();
		checkFullBlock();
		return FALSE;
	}


		DelenteBlock(blockModel[GetCurrentBlockIdx()]);
		curPosY += 1;

		SetCurrentCursorPos(curPosX, curPosY);
		showBlock(blockModel[GetCurrentBlockIdx()]);

		return TRUE;
}

void RightToMove(void) {

	if (!checkBlockDown(curPosX + 2, curPosY, blockModel[GetCurrentBlockIdx()]))
		return ;

	DelenteBlock(blockModel[GetCurrentBlockIdx()]);
	curPosX += 2;
	
	SetCurrentCursorPos(curPosX, curPosY);
	showBlock(blockModel[GetCurrentBlockIdx()]);

}

void LeftToMove(void) {

	if (!checkBlockDown(curPosX - 2, curPosY, blockModel[GetCurrentBlockIdx()]))
		return ;

	DelenteBlock(blockModel[GetCurrentBlockIdx()]);
	curPosX -= 2;

	SetCurrentCursorPos(curPosX, curPosY);
	showBlock(blockModel[GetCurrentBlockIdx()]);
}

void ChangBlock() {
	int nextRotste;
	int beforeRotSte = rotateSte;

	DelenteBlock(blockModel[GetCurrentBlockIdx()]);

	nextRotste = rotateSte + 1;
	nextRotste %= 4;
	rotateSte = nextRotste;

	if (!checkBlockDown(curPosX, curPosY, blockModel[GetCurrentBlockIdx()])) {
		rotateSte = beforeRotSte;
		return;
	}
	SetCurrentCursorPos(curPosX, curPosY);
	showBlock(blockModel[GetCurrentBlockIdx()]);

}

//재일 중요
int checkBlockDown(int posX, int posY, char blockModel[][4])
{
	int x, y;

	int arrX = (posX - GBOARD_ORGIN_X) / 2;
	int arrY = (posY - GBOARD_ORGIN_y);


	for (x = 0; x < 4; x++)
	{
		for (y = 0; y < 4; y++)
		{
			if (blockModel[y][x] == 1 && arr[arrY + y][arrX + x] == 1)
				return FALSE;
		}
	}
	return TRUE;
}

void AddCurrentBlockInfoToBoard(void)
{
	int x, y;
	int arrX, arrY;

	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{

			arrX = (curPosX - GBOARD_ORGIN_X) / 2;
			arrY = (curPosY - GBOARD_ORGIN_y);

			if (blockModel[GetCurrentBlockIdx()][y][x] == 1)
				arr[arrY + y][arrX + x] = 1;
		}
	}
}

int IsGameOver(void)
{
	if (!checkBlockDown(curPosX, curPosY + 1, blockModel[GetCurrentBlockIdx()]))
	{
		return FALSE;
	}
	else
		return TRUE;
}

void DrawGameBoard(void) {
	int x, y;

	for (y = 0; y <= GBOARD_HEIGHT; y++) {
		SetCurrentCursorPos(GBOARD_ORGIN_X, GBOARD_ORGIN_y + y);

		if (y == GBOARD_HEIGHT) {
			printf("└");
		}
		else
			printf("│");
	}

	for (y = 0; y <= GBOARD_HEIGHT; y++) {

		SetCurrentCursorPos(GBOARD_ORGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORGIN_y + y);

		if (y == GBOARD_HEIGHT) {
			printf("┘");
		}
		else
			printf("│");
	}

	for (x = 1; x < GBOARD_WIDTH + 1; x++) {
		SetCurrentCursorPos(GBOARD_ORGIN_X + x * 2, GBOARD_ORGIN_y + GBOARD_HEIGHT);
		printf("─");
	}

	SetCurrentCursorPos(0, 0);

	//오른쪽 좌 1로 벽 확인
	for (y = 0; y < GBOARD_HEIGHT; y++) {
		arr[y][0] = 1;
		arr[y][GBOARD_WIDTH + 1] = 1;
	}

	//밑에도 1로 벽확인
	for (x = 0; x < GBOARD_WIDTH + 2; x++)
	{
		arr[GBOARD_HEIGHT][x] = 1;
	}
}

void checkFullBlock(void) {

	int x, y, e;
	int line;
	int findTop = -1;


	for (y = GBOARD_HEIGHT - 1; y > 0; y--) {
		for (x = 1; x < GBOARD_WIDTH + 1; x++) {
			if (arr[y][x] != 1)
				break;
		}

		if ((GBOARD_WIDTH + 1) == x) {

			findTop = -1;

			for (e = 0; e < GBOARD_HEIGHT; e++) {
				for (x = 1; x < GBOARD_WIDTH + 1; x++) {
					if (arr[e][x] == 1) {
						findTop = e;
						break;
					}
				}

				if (findTop != -1)
					break;
			}

			for (line = y; line >= findTop; line--) {
				memcpy(&arr[line][1], &arr[line - 1][1], sizeof(int) * GBOARD_WIDTH);
			}
			y++;
		}
	}
	DrawRe();
}

void DrawRe(void) {
	int x, y;
	int arrX, arrY;

	for (y = 0; y < GBOARD_HEIGHT;y++) {
		for (x = 1; x < GBOARD_WIDTH + 1; x++) {

			arrX = x * 2 + GBOARD_ORGIN_X;
			arrY = (y + GBOARD_ORGIN_y);

			SetCurrentCursorPos(arrX, arrY);

			if (arr[y][x] == 1)
				printf("■");
			else
				printf("  ");
		}
	}
}