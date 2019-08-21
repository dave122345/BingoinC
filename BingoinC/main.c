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

int count_numbers_in_row(bingo_player * player, int row)
{
    int count = 0;
    for(int i = 0;i < 9;i++)
    {
        if(is_assigned(player->bingo_card[row][i]))
        {
            count++;
        }
    }
    
    return(count);
}

int count_numbers_in_column(bingo_player * player, int col)
{
    return(is_assigned(player->bingo_card[0][col]) +
           is_assigned(player->bingo_card[1][col]) +
           is_assigned(player->bingo_card[2][col]));
}

void create_player(int player_number, bingo_player* player)
{
    int i, j, row;
    if (player == NULL)
    {
        return;
    }
    
    player->player_number = player_number;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 9; j++)
        {
            player->bingo_card[i][j] = UNASSIGNED;
        }//EO for
    }//EO For
    
    //number generation
    int num1, num2, Randomcol, randomrow;
    
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
    
    
    //ALL other columns
    
    // Each column will have at least one number
    for (int col = 1; col < 8; col++)
    {
        // Pick random row
        row = rand() % 3;
        
        // Max 5 numbers on each row
        while(count_numbers_in_row(player, row) >= 5)
        {
            row = rand() % 3;
            
        }
        
        player->bingo_card[row][col] = col * 10 + rand() % 9;
    }
    
    // Assign remaining numbers
    
    // Stop once there are 15 assigned.
    while(count_numbers_in_row(player, 0) +
          count_numbers_in_row(player, 1) +
          count_numbers_in_row(player, 2) < 15)
    {
        randomrow = rand() % 3;
        
        // Max 5 numbers on each row
        while(count_numbers_in_row(player, randomrow) >= 5)
        {
            randomrow = rand() % 3;
        }
        
        Randomcol = rand() % 7 + 1;
        
        while(is_assigned(player->bingo_card[randomrow][Randomcol]))   // ... in case this card slot already has a number assigned
        {
            Randomcol = rand() % 7 + 1;
        }
        
        num1 = Randomcol * 10 + rand() % 9;
        
        // Make sure this number isn't already on the card.
        while(num1 == player->bingo_card[0][Randomcol] ||
              num1 == player->bingo_card[1][Randomcol] ||
              num1 == player->bingo_card[2][Randomcol])
        {
            num1 = Randomcol * 10 + rand() % 9;
        }
        
        player->bingo_card[randomrow][Randomcol] = num1;
        
    }
    
    // Sort the numbers in each column.
    int count;
    for (i = 1;i < 8; i++)
    {
        count = count_numbers_in_column(player, i);
        
        if(count == 2)
        {
            if(!is_assigned(player->bingo_card[0][i]))
            {
                sort2(&player->bingo_card[1][i], &player->bingo_card[2][i]);
            }
            else if(!is_assigned(player->bingo_card[1][i]))
            {
                sort2(&player->bingo_card[0][i], &player->bingo_card[2][i]);
            }
            else
            {
                sort2(&player->bingo_card[0][i], &player->bingo_card[1][i]);
            }
        }
        else if(count == 3)
        {
            sort3(&player->bingo_card[0][i], &player->bingo_card[1][i], &player->bingo_card[2][i]);
        }
    }
}
//helper function to print out player details.
void print_player(bingo_player* player)
{
    if (player == NULL)
    {
        return;
    }
    int i, j;
    printf("Player number: %d\n", player->player_number);
    
    //printing and testing
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if(is_assigned(player->bingo_card[i][j]))
            {
                printf("%d\t", player->bingo_card[i][j]);
            }
            else
            {
                printf(" \t");
            }
            
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
    
    
    if(Numcount != 15)
    {
        int Fullhouse = 15 - Numcount;
        Numcount = 0;
        return(Fullhouse);
    }
   
    else if(Numcount == 15)
    {
        
        printf("FULLHOUSE ACHIEVED BY PLAYER %d\n", player->player_number);
    }
    return 0;
}//end of full_house

int Line_win(bingo_player*player, int* drawn, int Linenum)
{
    int Numcount = 0;
    
    for(int k = 0;k<90;k++)
    {
        
        if(drawn[k]!=-1)
        {
                for(int e = 0;e<9;e++){
                    if(drawn[k] == player->bingo_card[Linenum][e])
                    {
                       // printf("test for line\n");
                        Numcount++;
                    }//eo if
                }//end of for
        }//end of if
    }//end of line 1 for
   
    if(Numcount != 5)
    {
        
        int NumleftLine1 = 5 - Numcount;
        Numcount = 0;
         return(NumleftLine1);
    }//eo if
    
    else if(Numcount == 5)
    {
        printf("1 LINE WIN %d ACHIEVED BY PLAYER %d\n", Linenum + 1, player->player_number);
        
    }//eo if
    
    
    return 0;
}//end of Line_win


int Line_win2(bingo_player*player, int* drawn, int Linenum, int Linenum2)
{
    int Numcount = 0;
    
    for(int k = 0;k<90;k++)
    {
        
        if(drawn[k]!=-1)
        {
            for(int e = 0;e<9;e++){
                if(drawn[k] == player->bingo_card[Linenum][e] || drawn[k] == player->bingo_card[Linenum2][e])
                {
                    // printf("test for line\n");
                    Numcount++;
                }//eo if
            }//end of for
        }//end of if
    }//end of line 1 for
    
    if(Numcount != 10)
    {
        Numcount = 0;
    }//eo if
    
    else if(Numcount == 10)
    {
        printf("1 LINE WIN %d & LINE %d ACHIEVED BY PLAYER %d\n", Linenum + 1, Linenum2 + 1, player->player_number);
        
    }//eo if
    
    
    return 0;
}//end of Line_win2




void Outputstatus( int* drawn)
{
    
    for (int d = 0; d < 100; d++)
    {
       if( drawn[d] == -1)
       {
           //do nothing
       }
        
        else if(drawn[d] != -1)
        {
             printf("Drawn: %d\n", drawn[d]);
        }
    }//EO For DRAWN
    
    
    
    
    
    
    
    
}//end of Outputstatus

void save_game(int* drawn, int Numofplayers, bingo_player*players){
    
         printf("===SAVING GAME===\n");
    FILE* f = fopen("Savegame.dat", "wb");
        fwrite( drawn ,sizeof(int),100, f);
        fwrite( &Numofplayers ,sizeof(int),1, f);
        fwrite( players ,sizeof(bingo_player), Numofplayers, f);

    
    
    
    
   /* while(tmp != NULL){
        member current = *tmp;
        fwrite(&current, sizeof(struct member), 1, f);
        printf("Saved member %d to file.\n", current.number);
        tmp = tmp->next;
    }*/
}//end of saving






void main()
{
    //variables
    int drawn[100];
    int Fullhouse = 0;
    int NumleftLine1 = 0;
    int NumleftLine2 = 0;
    int NumleftLine3 = 0;
    int Mainmenuopt = -1;
    int fullhouseACH = 0;
     bingo_player* players[MAX_NUM_PLAYERS];
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
    printf("1. choose amount of players\n");
    printf("2. load game\n");
    printf("0 to exit\n");
    scanf("%d", &Mainmenuopt);
    while(Mainmenuopt != 0)
    {
    
    
    if(Mainmenuopt == 1)
    {
    printf("How many players are there playing?\n");
    scanf("%d", &Numofplayers);
    }
        
        if(Mainmenuopt == 2)
        {
            FILE* f = fopen("Savegame.dat", "rb");
            printf("Loading Game\n");
            fread(drawn, sizeof(int), 100, f);
             fread(&Numofplayers, sizeof(int), 1, f);
             fread(players, sizeof(bingo_player), Numofplayers, f);
        }
        
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
            printf("2. Output game status\n");
            printf("3. Save game\n");
            printf("Press 0 to exit to main menu without saving\n");
            scanf("%d", &option);
            printf("EYES DOWN\n");
            //playing the game
            while (option != 0)
            {
                //playing
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
                //Winning check
                for(p = 0;p<Numofplayers;p++)
                {
                    
                    if(full_house(players[p], drawn) == 0)
                    {
                        
                        break;
                        
                    }
                    else if(Line_win(players[p], drawn, 0) == 0)
                     {
                        
                         break;
                     }
                    else if(Line_win(players[p], drawn, 1) == 0)
                    {
                        
                        break;
                    }
                    else if(Line_win(players[p], drawn, 2) == 0)
                    {
                        
                        break;
                    }
                    
                    else if(Line_win2(players[p], drawn, 0, 1) == 0)
                    {
                        
                        break;
                    }
                    else if(Line_win2(players[p], drawn, 1, 2) == 0)
                    {
                        
                        break;
                    }
                    else if(Line_win2(players[p], drawn, 2, 0)== 0 )
                    {
                        
                        break;
                    }
                }//eo for winnings
                
                
                
                
                //output Status of hane
                if (option == 2)
                {
                    int Fullhouserem = 0;
                    int Linerem1 = 0;
                    int Linerem2 = 0;
                    int Linerem3 = 0;
            
                    
                    for(p = 0;p<Numofplayers;p++)
                    {
                        Fullhouserem = full_house(players[p], drawn);
                        Linerem1 = Line_win(players[p], drawn, 0);
                        Linerem2 = Line_win(players[p], drawn, 1);
                        Linerem3 = Line_win(players[p], drawn, 2);
                        
                       
                        printf("Player %d:", p + 1);
                        printf("Amount until full house: %d\n", Fullhouserem);
                        printf("amount until line one: %d/5\n", Linerem1);
                        printf("amount until line two: %d/5\n", Linerem2);
                        printf("amount until line three: %d/5\n", Linerem3);
                    }
                   
                     Outputstatus(drawn);
                }//EO output
                
                if(option == 3)
                {
                    save_game(drawn, Numofplayers, players[0]);
                    
                }
                //menu
               
                if(fullhouseACH == 1)
                {
                printf("==Options enter the number you want to choose==\n");
                printf("2. Output game status\n");
                printf("3. Save game\n");
                printf("Press 0 to exit to main menu without saving\n");
                scanf("%d", &option);
                }
                
              else if(fullhouseACH == 0)
                {
                    printf("==Options enter the number you want to choose==\n");
                    printf("1. Would you like to draw a number?\n");
                    printf("2. Output game status\n");
                    printf("3. Save game\n");
                    printf("Press 0 to exit to main menu without saving\n");
                    scanf("%d", &option);
                }
                
            }//end of sub menu while
    
        printf("==WELCOME TO BINGO==\n");
        printf("1. choose amount of players\n");
        printf("2. load game\n");
        printf("0 to exit\n");
        scanf("%d", &Mainmenuopt);
    }//end of main menu while
    
    
    
    
    
    
    
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
