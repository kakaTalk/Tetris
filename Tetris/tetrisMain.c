#include "keyCurControl.h"
#include "BlockStageControl.h"
#include "common.h"
#include "DrawGameBoard.h"

#define START_CURPOS_X      5*2
#define START_CURPOS_Y        0
#define SYS_DELAY           100

int main(void)
{
	int boolean = TRUE;
	int speed = 10;
	DrawScoreBoard();
	//���� �� �׸� 
	DrawGameBoard();

	//Ŀ������
	RemoveCursor();

	//���Ӽӵ� ����
	InitKeyDelayRate(speed);


	while (1)
	{
		InitNewBlockPOs(START_CURPOS_X, START_CURPOS_Y);

		chooseBlock();

		if (!IsGameOver())
			break;

		while (1)
		{
			if (BlockDown() == FALSE)
			{
	
				InitKeyDelayRate(speed);
				break;
			}
			getMoveBlock();
		}
	}
	return 0;
}