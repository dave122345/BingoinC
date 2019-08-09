#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>


//#define ROW 3
//#define COL 9
#define MAX_NUM_PLAYERS 6

typedef struct card_slot {
	int number;
	int drawn; // 0 = not drawn, 1 = drawn
} card_slot;
void main()
{
	int i, j, n;
	//int BINGO_CARD[ROW][COL];
	int Numofplayers;
	int bingo_card[9][3];



	//start of game code
	printf("==WELCOME TO BINGO==\n");
	printf("How many players are there playing?\n");
	scanf_s("%d", &Numofplayers);
	//TEST
	//printf("%d", Numofplayers);
	while (Numofplayers != MAX_NUM_PLAYERS)
	{
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 3; j++)
			{
				bingo_card[i][j] = rand() % 50;
				printf("%d %d\n", bingo_card[i][j]);
			}
		}//EO For

	}//EO while
}//end of main