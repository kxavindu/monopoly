#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "types.h"

void StartingPlayer();

int PlayerSequence[PLAYERS] = {0,1,2,3};

void GameStart()
{
    MSG1();
    StartingPlayer();
}

// Dice
int RollDice()
{
    return rand() % 6 + 1;
}

//hama value eakakm 100 n guna krl tie ewata withk ayema tie una value eka ekathu karanawa ethakot lesiyen loku eke idn kuda ekata ilakkma tika 
//hoyaganna puluwan


void StartingPlayer()
{


    int DiceRolls[PLAYERS] = {0};
    int TieDetecter[PLAYERS] = {0};
    int DividedDiceValues[PLAYERS] = {0};
    int Tie;
   

    for (int i = 0; i < PLAYERS; i++)
    {
        DiceRolls[i] = RollDice() + RollDice();
        printf("%s rolled a %d\n", PLAYER_NAME[i], DiceRolls[i]);
        DividedDiceValues[i] = DiceRolls[i];
        
    }


 do{

    Tie = 0;
    for (int i = 0; i < PLAYERS; i++)
    {
        TieDetecter[i] = 0;

    }

    for (int i = 0; i < PLAYERS; i++)
    {
        for (int j = 0; j < PLAYERS; j++)
        {
            if (DiceRolls[i] == DiceRolls[j] && i != j)
            {
                TieDetecter[i] = 1;
                TieDetecter[j] = 1;
                Tie = 1;

            }
        }
    }


    if (Tie == 1){

        printf("\nThere is a tie between the following players:\n");
        for(int i = 0; i < PLAYERS; i++)
        {
        
            if (TieDetecter[i] == 1)
            {
                printf("- %s\n", PLAYER_NAME[i]);
            }
            DividedDiceValues[i] = DividedDiceValues[i]*100;
        }
        printf("\nwill roll again\n");
        
       

    }

   

    for (int i = 0; i < PLAYERS; i++)
    {
        if (TieDetecter[i] == 1)
        {
            DiceRolls[i] = RollDice() + RollDice();
            printf("%s rolls %d\n", PLAYER_NAME[i], DiceRolls[i]);
            DividedDiceValues[i] = DividedDiceValues[i] + DiceRolls[i];
        }


    }

     

     
   


    }while (Tie == 1);


    

    for(int i = 0; i < PLAYERS; i++)
    {
        printf("%d\n", DividedDiceValues[i]);
    }


     for (int i = 0; i < PLAYERS - 1; i++) {
        for (int j = 0; j < PLAYERS - i - 1; j++) {
            if (DividedDiceValues[PlayerSequence[j]] < DividedDiceValues[PlayerSequence[j + 1]]) {
                int temp = PlayerSequence[j];
                PlayerSequence[j] = PlayerSequence[j + 1];
                PlayerSequence[j + 1] = temp;
            }
        }
    }
    
    printf("\n%s will begin the game.\n", PLAYER_NAME[PlayerSequence[0]]);
    printf("Turn Order:");
    for(int i = 0; i < PLAYERS; i++)
    {
        printf("%s is player %d\n", PLAYER_NAME[PlayerSequence[i]], i + 1);
    }

}