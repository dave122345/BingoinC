#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NUM_PLAYERS 6
#define UNASSIGNED -1
//adding bingo_player struct to hold bingo_card, player number, etc.
typedef struct bingo_player {
    int player_number;
    int bingo_card[3][9];
} bingo_player;
// sorts two integers - lowest to highest
void sort2(int* pnum1, int* pnum2)
{
    int swap;
    if (*pnum1 > * pnum2)
    {
        swap = *pnum1;
        * pnum1 = *pnum2;
        * pnum2 = swap;
    }
}
// sorts three integers - lowest to highest
void sort3(int* pnum1, int* pnum2, int* pnum3)
{
    sort2(pnum1, pnum2);
    sort2(pnum1, pnum3);
    sort2(pnum2, pnum3);
}
// checks to see if a bingo card slot has a number assigned to it.
int is_assigned(int val)
{
    if (val == UNASSIGNED)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
void create_player(int player_number, bingo_player* player)
{
    int i, j, row;
    if (player == NULL)
    {
        return;
    }
    int number_card[3][7];
    player->player_number = player_number;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 9; j++)
            
        {
            if (j < 7)
            {
                number_card[i][j] = UNASSIGNED;
            }
            player->bingo_card[i][j] = UNASSIGNED;
            
        }//EO for
    }//EO For
    //number generation
    int num1, num2, num3, Randomcol;
    int gen = 0;
    //first column
    num1 = rand() % 8 + 1;
    num2 = num1;
    while (num2 == num1)
    {
        num2 = rand() % 8 + 1;
    }
    //Use sort2 function here - less code and keeps things simpler
    sort2(&num1, &num2);
    player->bingo_card[0][0] = num1;
    player->bingo_card[2][0] = num2;
    //ALL other columns
    for (j = 0; j < 7; j++)
    {
        number_card[0][j] = 10 + j * 10 + rand() % 9;
    }
    while (gen != 5)
    {
        Randomcol = rand() % 7;
        num1 = number_card[0][Randomcol];
        //use is_assigned() function here - better readability.
        if (!is_assigned(number_card[1][Randomcol]))
        {
            do
                
            {
                num2 = Randomcol * 10 + 10 + rand() % 9;
            } while (num2 == num1);
            number_card[1][Randomcol] = num2;
        }
        //use is_assigned() function here - better readability.
        else if (!is_assigned(number_card[2][Randomcol]))
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
   /* printf("number card\n");
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 7; j++)
        {
            printf("%d\t", number_card[i][j]);
        }
        printf("\n");
    }*/
    //last column
    num1 = 80 + rand() % 9;
    num2 = num1;
    while (num2 == num1)
    {
        num2 = 80 + rand() % 9;
    }
    //use sort2 - less code and better readability.
    sort2(&num1, &num2);
    player->bingo_card[0][8] = num1;
    player->bingo_card[2][8] = num2;
    
    //checking for the amounts of elements present in a column
    for (j = 0; j < 7; j++)
    {
        int Numelements = 1;
        if (is_assigned(number_card[1][j])) {
            if (is_assigned(number_card[2][j])) {
                
                Numelements = 3;
            }
            else {
                Numelements = 2;
            }
        }
        if (Numelements == 1) {
            row = rand() % 3;
            player->bingo_card[row][j + 1] = number_card[0][j];
        }
        else if (Numelements == 2) {
            row = rand() % 3;
            //in this case row is the unpopulated element
            // use sort2 function to sort numbers in the number_card array.
            sort2(&number_card[0][j], &number_card[1][j]);
            if (row == 0)
            {
                player->bingo_card[1][j + 1] = number_card[0][j];
                player->bingo_card[2][j + 1] = number_card[1][j];
            }
            else if (row == 1) {
                player->bingo_card[0][j + 1] = number_card[0][j];
                player->bingo_card[2][j + 1] = number_card[1][j];
            }
            else if (row == 2) {
                player->bingo_card[0][j + 1] = number_card[0][j];
                player->bingo_card[1][j + 1] = number_card[1][j];
            }
        }
        else {
            //checking for 3
            //use sort3 function to sort the values in the number_card array.
            sort3(&number_card[0][j], &number_card[1][j], &number_card[2][j]);
            player->bingo_card[0][j + 1] = number_card[0][j];
            player->bingo_card[1][j + 1] = number_card[1][j];
            player->bingo_card[2][j + 1] = number_card[2][j];
        }
    }//EO for
}
//helper function to print out player details.
void print_player(bingo_player* player)
{
    if (player == NULL)
    {
        return;
    }
    int i, j, row;
    printf("Player number: %d\n", player->player_number);
    
    //printing and testing
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 9; j++)
        {
            printf("%d\t", player->bingo_card[i][j]);
        }//EO for
        printf("\n");
    }//EO For
}
int has_duplicate(int* drawn, int draw)
{
    //searching to see if it is equal
    for (int d = 0; d < 100; d++)
    {
        if (drawn[d] == draw)
        {
            
           // printf("I AM LOOKING FOR EQUAL NUMBERS:\n");
              return 1;
        }
    }//EO equal serach
    return 0;
}//end of has_duplicate

int has_winning(bingo_player*player, int* drawn)
{
   
    //1 line condition check
    
    //2 line condition check
    //full house condition check

    return 0;
}//end of has_winning


int full_house(bingo_player*player, int* drawn)
{
    int Numcount = 0;
   
    for(int k = 0;k<90;k++)
    {
       
        if(drawn[k]!=-1)
        {
        
            for(int f = 0;f<3;f++){
               
                for(int e = 0;e<9;e++){
                    if(drawn[k] == player->bingo_card[f][e])
                    {
                        //printf("test\n");
                        Numcount++;
                    }//eo if
                }//eo for
            }//eo for
        }//eo if
    }//eo for

    if(Numcount == 15)
    {
        printf("FULLHOUSE ACHIEVED BY PLAYER %d\n", player->player_number);
    }
    return 0;
}//end of full_house

int Line_win(bingo_player*player, int* drawn)
{
    int Numcount = 0;
    
    for(int k = 0;k<90;k++)
    {
        
        if(drawn[k]!=-1)
        {
            
            for(int f = 0;f<3;f++){
                
                for(int e = 0;e<9;e++){
                    if(drawn[k] == player->bingo_card[f][e])
                    {
                        printf("test\n");
                        Numcount++;
                    }//eo if
                }//eo for
            }//eo for
        }//eo if
    }//eo for
    
    if(Numcount == 15)
    {
        printf("FULLHOUSE ACHIEVED BY PLAYER %d\n", player->player_number);
    }
    return 0;
}//end of Line_win


void main()
{
    //variables
    int drawn[100];
   // int equal = 0;
    int Numofplayers, option, d, draw;
    int count = 0;
    srand((unsigned int)(time(0)));//using current time for random gen
    //should print out number card for testing and assign the middle numbers to
   // number_card instead of bingo_card
    //start of game code
    
    for(d = 0;d<100;d++)
    {
       drawn[d] = -1;
        
    }
    
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
    int i;
    int p = 0;
    //store bingo player data in array of bingo_player structs.
    bingo_player* players[MAX_NUM_PLAYERS];
    
    while (p < Numofplayers)
    {
        players[p] = malloc(sizeof(bingo_player));
        create_player(p + 1, players[p]);
        p++;
    }
    for (i = 0; i < Numofplayers; i++)
    {
        print_player(players[i]);
    }
    //NEW STUFF CHECK FOR EQUAL NUMBERS
    printf("==Options enter the number you want to choose==\n");
    printf("1. Would you like to draw a number?\n");
    printf("Press 0 to exit\n");
    scanf("%d", &option);
    //playing the game
    while (option != 0)
    {
        printf("EYES DOWN\n");
        if (option == 1)
        {
            
            
           
            draw = rand() % 90;
            
            //checking for duplicates
            while(has_duplicate(drawn, draw))
            {
                draw = rand() % 90;
                
            }//end of while
            drawn[count] = draw;
            count++;
            
            
        }//end of if
        for(p = 0;p<Numofplayers;p++)
        {
            
            if(full_house(players[p], drawn))
            {
                break;
            }
            /* else if(line 1)
             {
             
             }
             else if(line 2)
             {
             
             }*/
            
            
        }//eo for players
        //menu
        printf("1. Would you like to draw a number?\n");
        printf("Press 0 to exit\n");
        scanf("%d", &option);
    }//end of while
 
    
    
    
    
    
    
    
    
    
    /*  for (d = 0; d < 100; d++)
    {
        printf("ARRAY NUMBER: %d\n", drawn[d]);
    }//EO For DRAW*/
    /*for (i = 0; i < 3; i++)
     {
     for (j = 0; j < 7; j++)
     {
     printf("NC %d\t", number_card[i][j]);
     }//EO for
     printf("\n");
     }//EO For*/
    
}//end of main
