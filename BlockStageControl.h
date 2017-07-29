#pragma once
void InitNewBlockPOs(int x, int y);
void chooseBlock();
int GetCurrentBlockIdx(void);

void showBlock(char blockInfo[][4]);

void DelenteBlock(char blockInfo[][4]);

int BlockDown(void);
void LeftToMove(void);
void ChangBlock(void);
void RightToMove(void);
void setCurrentBlock(int block);
int checkBlockDown(int posX, int posY, char blockModel[][4]);

void AddCurrentBlockInfoToBoard(void);
int IsGameOver(void);
void checkFullBlock(void);
void DrawRe(void);
#pragma once
