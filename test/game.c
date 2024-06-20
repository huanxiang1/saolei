#define  _CRT_SECURE_NO_WARNINGS 1
#include"game.h"



//初始化雷盘
void Initboard(char board[ROWS][COLS], int rows, int cols, char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}


//打印棋盘
void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	//打印列号
	for (i = 0; i <= row; i++)
	{
		if (i == 0)
			printf("+ ");
		else
			printf("%d ", i);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		//打印行号
		printf("%d ", i);
		for (j = 1; j <=col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

//布置雷
void SetMine(char board[ROWS][COLS], int row, int col)
{
	//雷的个数
	int count = EASY_COUNT;
	while (count)
	{
		int x = rand() % row + 1;//生成1-row
		int y = rand() % col + 1;//生成1-row
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}

//'1'-'0'=1
//'3'-'0'=3

int get_mine_count(char mine[ROWS][COLS],int x, int y)
{
		return mine[x - 1][y] +
		mine[x - 1][y - 1] +
		mine[x][y - 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] +
		mine[x][y + 1] +
		mine[x - 1][y + 1] - 8 * '0';
}

//排雷
void FineMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int win = 0;
	while(win<row*col-EASY_COUNT)
	{
		printf("Please enter the coordinates of the demining:>");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			//坐标合法
			//1.踩雷了
			if (mine[x][y] == '1')
			{
				printf("boom!!!!\n");
				DisplayBoard(mine, row, col);
				break;
			}
			//2.不是雷
			else
			{
				//计算x，y坐标周围有几个雷
				int count = get_mine_count(mine, x, y);
				if(count == 0)
				{
					show[x][y] = ' ';				
				}
				else
				{
					show[x][y] = count + '0';
					
				}
				DisplayBoard(show, row, col);
				win++;
			}
		}
		else
		{
			printf("the number is illeagle,please input again!\n");
			break;
		}
	}
	if (win == row * col - EASY_COUNT)
	{
		printf("you are the winner!\n");
		DisplayBoard(mine, row, col);
	}
}