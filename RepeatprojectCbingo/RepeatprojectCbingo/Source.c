#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NUM_PLAYERS 6
#define UNASSIGNED -1

typedef struct card_slot {
	int number;
	int drawn; // 0 = not drawn, 1 = drawn
} card_slot;


void main()
{
	//variables
	int i, j, row;
	//int BINGO_CARD[ROW][COL];
	int Numofplayers;
	int bingo_card[3][9];
	int number_card[3][7];
	srand((unsigned int)(time(0)));//using current time for random gen
	 //should print out number card for testing and assign the middle numbers to number_card instead of bingo_card
	 //int p = 0;



	 //start of game code
	printf("==WELCOME TO BINGO==\n");
	printf("How many players are there playing?\n");
	scanf("%d", &Numofplayers);
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
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 9; j++)
		{

			if (j < 7)
			{
				number_card[i][j] = UNASSIGNED;
			}
			bingo_card[i][j] = UNASSIGNED;
			//  printf("%d\t", bingo_card[i][j]);
			 /*bingo_card[i][j] = 20 + rand() % 9;
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
			  printf("%d\t", bingo_card[i][j]);*/

		}//EO for
		printf("\n");
	}//EO For

	//number generation
	int num1, num2, num3, Randomcol;
	int gen = 0;
	num1 = rand() % 8 + 1;
	num2 = num1;

	while (num2 == num1)
	{
		num2 = rand() % 8 + 1;

	}

	//  printf("%d %d\n", num1, num2);
	 //first column
	if (num1 < num2)
	{
		bingo_card[0][0] = num1;
		bingo_card[2][0] = num2;
	}

	else {
		bingo_card[2][0] = num1;
		bingo_card[0][0] = num2;
	}

	//printf("%d %d\n", bingo_card[0][0], bingo_card[2][0]);


	//ALL other columns
	for (j = 0; j < 7; j++)
	{

		number_card[0][j] = 10 + j * 10 + rand() % 9;

	}

	while (gen != 5)
	{
		Randomcol = rand() % 7;

		num1 = number_card[0][Randomcol];
		if (number_card[1][Randomcol] == UNASSIGNED)
		{


			do
			{
				num2 = Randomcol * 10 + 10 + rand() % 9;

			} while (num2 == num1);

			number_card[1][Randomcol] = num2;

		}
		else if (number_card[2][Randomcol] == UNASSIGNED)
		{

			num2 = number_card[1][Randomcol];

			do
			{
				num3 = Randomcol * 10 + 10 + rand() % 9;

			} while (num3 == num1 || num3 == num2);

			number_card[2][Randomcol] = num3;

		}

		else {
			continue;
		}
		//printf("TEST %d\n", Randomcol);
		gen++;
	}

	//last column
	num1 = 80 + rand() % 9;
	num2 = num1;
	while (num2 == num1)
	{
		num2 = 80 + rand() % 9;

	}
	if (num1 < num2)
	{
		bingo_card[0][8] = num1;
		bingo_card[2][8] = num2;
	}

	else {
		bingo_card[2][8] = num1;
		bingo_card[0][8] = num2;
	}

	// printf("%d %d\n", bingo_card[0][8], bingo_card[2][8]);



	 //checking for the amounts of elements present in a column
	for (j = 0; j < 7; j++)
	{
		int Numelements = 1;

		if (number_card[1][j] != UNASSIGNED) {

			if (number_card[2][j] == UNASSIGNED) {
				Numelements = 2;

			}
			else {
				Numelements = 3;
			}
		}//end of if 1

		if (Numelements == 1) {
			row = rand() % 2;
			bingo_card[row][j + 1] = number_card[0][j];
		}

		else if (Numelements == 2) {
			row = rand() % 2;
			//in this case row is the unpopulated element

	   // printf("CHECKING FOR 2 ELEMENTS\n");
			if (row == 1)
			{

				if (number_card[0][j] < number_card[1][j])
				{
					bingo_card[0][j + 1] = number_card[0][j];
					bingo_card[2][j + 1] = number_card[1][j];
				}
				else {
					bingo_card[2][j + 1] = number_card[0][j];
					bingo_card[0][j + 1] = number_card[1][j];

				}

			}
			else if (row == 0) {
				if (number_card[0][j] < number_card[1][j])
				{
					bingo_card[1][j + 1] = number_card[0][j];
					bingo_card[2][j + 1] = number_card[1][j];
				}
				else {
					bingo_card[2][j + 1] = number_card[0][j];
					bingo_card[1][j + 1] = number_card[1][j];

				}
			}

			else if (row == 2) {
				if (number_card[0][j] < number_card[1][j])
				{
					bingo_card[0][j + 1] = number_card[0][j];
					bingo_card[1][j + 1] = number_card[1][j];
				}
				else {
					bingo_card[1][j + 1] = number_card[0][j];
					bingo_card[0][j + 1] = number_card[1][j];

				}
			}


			else {

				bingo_card[row][j + 1] = number_card[0][j];
			}


		}
		else {
			//checking for 3

			bingo_card[0][j + 1] = number_card[0][j];
			bingo_card[1][j + 1] = number_card[1][j];
			bingo_card[2][j + 1] = number_card[2][j];


		}



	}//EO for

//printing and testing
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 9; j++)
		{
			printf("%d\t", bingo_card[i][j]);

		}//EO for
		printf("\n");
	}//EO For

   /*for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 7; j++)
		{
		   printf("NC %d\t", number_card[i][j]);
		}//EO for
		printf("\n");
	}//EO For*/

}//end of main