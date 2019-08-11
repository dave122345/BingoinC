#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define ROW 3
#define COL 9
#define MAX_NUM_PLAYERS 6

typedef struct card_slot {
	int number;
	int drawn; // 0 = not drawn, 1 = drawn
} card_slot;
void main()
{
	int i, j;
	//int BINGO_CARD[ROW][COL];
	int Numofplayers;
	int bingo_card[9][3];
	int p = 0;



	//start of game code
	printf("==WELCOME TO BINGO==\n");
	printf("How many players are there playing?\n");
	scanf_s("%d", &Numofplayers);
	//TEST
	//printf("%d", Numofplayers);
	
	//Input check
	while (Numofplayers < 1 || Numofplayers > MAX_NUM_PLAYERS)
	{
		printf("Invalid Input!");
		printf("How many players are there playing?\n");
		scanf("%d", &Numofplayers);
	}
		
		//bingo card generation
		
	//while (p!=Numofplayers) {
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 3; j++)
			{
				bingo_card[i][j] = rand() % 8 + 1;
				printf("%d\t", bingo_card[i][j]);
				bingo_card[i][j] = 20 + rand() % 9;
				printf("%d\t", bingo_card[i][j]);
				bingo_card[i][j] = 30 + rand() % 9;
				printf("%d\t", bingo_card[i][j]);
				bingo_card[i][j] = 40 + rand() % 9;
				printf("%d\t", bingo_card[i][j]);
				bingo_card[i][j] = 50 + rand() % 9;
				printf("%d\t", bingo_card[i][j]);
				bingo_card[i][j] = 60 + rand() % 9;
				printf("%d\t", bingo_card[i][j]);
				bingo_card[i][j] = 70 + rand() % 9;
				printf("%d\t", bingo_card[i][j]);
				bingo_card[i][j] = 80 + rand() % 9;
				printf("%d\t", bingo_card[i][j]);

			}//EO for
		}//EO For
	//	p++;
	//}//EO While
	
}//end of main