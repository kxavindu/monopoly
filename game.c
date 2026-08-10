#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "types.h"

//void StartingPlayer();
void GameLoop(PlayerType Player[], SquareType Square[] , EconomicEventType EconomicEvent);
//void GameRoundCal(PlayerType Player[], int *GameRound, int , S);

//----------------------------------------------------------------GAME START--------------------------------------------------------------
void GameStart()
{

    printf("\nMONOPOLY-LK Simulation\n\n");
    printf("Player 1 : Aggressive Invester\nPlayer 2 : Conservative Banker\nPlayer 3 : Risk Taker\nPlayer 4 : Oppertunistic Trader\n\n");
    printf("Each Player begins with LKR 30,000.\n\n");

    int PlayerSequence[PLAYERS] = {0, 1, 2, 3};
    StartingPlayer(PlayerSequence);

    PlayerType Player[PLAYERS];
    SquareType Square[SQUARES];
    EconomicEventType EconomicEvent;

    InitializePlayers(Player, PlayerSequence);  // passing two pointers of arrays to initialize
    InitializeSquares(Square);

    GameLoop(Player,Square,EconomicEvent);
}

//----------------------------------------------------------------ROLL DICE--------------------------------------------------------------
int RollDice()
{
    return rand() % 6 + 1;
}



/* hama value eakakm 100 n guna krl tie ewata withk ayema tie una value eka ekathu karanawa ethakot lesiyen loku eke idn kuda ekata ilakkma tika
hoyaganna puluwan */



//-----------------------------------------------------------CHOOSE STARTING PLAYER --------------------------------------------------------------
void StartingPlayer(int PlayerSequence[])
{

    int DiceRolls[PLAYERS] = {0};
    int TieDetecter[PLAYERS] = {0};
    int DividedDiceValues[PLAYERS] = {0};
    int Tie;

    for (int i = 0; i < PLAYERS; i++)
    {
        DiceRolls[i] = RollDice() + RollDice();
        printf("%s rolls %d.\n", PLAYER_NAME[i], DiceRolls[i]);
        DividedDiceValues[i] = DiceRolls[i];
    }

    do
    {

        Tie = 0;
        for (int i = 0; i < PLAYERS; i++)
        {
            TieDetecter[i] = 0;
        }

        for (int i = 0; i < PLAYERS; i++)
        {
            for (int j = 0; j < PLAYERS; j++)
            {
                if (DividedDiceValues[i] == DividedDiceValues[j] && i != j)
                {
                    TieDetecter[i] = 1;
                    TieDetecter[j] = 1;
                    Tie = 1;
                }
            }
        }

        if (Tie == 1)
        {

            printf("\nThere is a tie between the following players:\n");
            for (int i = 0; i < PLAYERS; i++)
            {

                if (TieDetecter[i] == 1)
                {
                    printf("- %s\n", PLAYER_NAME[i]);
                }
                DividedDiceValues[i] = DividedDiceValues[i] * 100;
            }
            printf("will roll again\n\n");
        }

        for (int i = 0; i < PLAYERS; i++)
        {
            if (TieDetecter[i] == 1)
            {
                DiceRolls[i] = RollDice() + RollDice();
                printf("%s rolls %d.\n", PLAYER_NAME[i], DiceRolls[i]);
                DividedDiceValues[i] = DividedDiceValues[i] + DiceRolls[i];
            }
        }

    } while (Tie == 1);

    for (int i = 0; i < PLAYERS - 1; i++)
    {
        for (int j = 0; j < PLAYERS - i - 1; j++)
        {
            if (DividedDiceValues[PlayerSequence[j]] < DividedDiceValues[PlayerSequence[j + 1]])
            {
                int temp = PlayerSequence[j];
                PlayerSequence[j] = PlayerSequence[j + 1];
                PlayerSequence[j + 1] = temp;
            }
        }
    }

    printf("\n%s will begin the game.\n", PLAYER_NAME[PlayerSequence[0]]);
    printf("\nTurn Order:\n");
    for (int i = 0; i < PLAYERS; i++)
    {
        printf("%s\n", PLAYER_NAME[PlayerSequence[i]]);
    }
}

/* Always player 0 is starting game but end of the game player one is getting name of player who win starting game */



//----------------------------------------------------------------GAME LOOP-----------------------------------------------------------------------
void GameLoop(PlayerType Player[],SquareType Square[] ,EconomicEventType EconomicEvent)
{
    int GameRound = 1;
    for(; GameRound <= MAX_ROUND ;)
    {
        MovePlayer(Player,Square ,&GameRound ,EconomicEvent);
        //printf("\n\n");
    }
}




//----------------------------------------------------------------GAME ROUND CALCULATOR--------------------------------------------------------------
void GameRoundCal(PlayerType Player[], int *GameRound, int CurrentPlayer , SquareType Square[] ,EconomicEventType EconomicEvent)
{
    int GRC = 0;
    for (int i = 0; i < PLAYERS; i++)
    {
        if (Player[i].PlayerRound >= Player[CurrentPlayer].PlayerRound || Player[i].InJail || Player[i].Bankrupt)
        {
            GRC++;
        }
    }

    if (GRC == PLAYERS && Player[CurrentPlayer].PlayerRound > *GameRound)
    {
        *GameRound = Player[CurrentPlayer].PlayerRound;

        //for events using this
        HandleRoundEvents(Player, Square, *GameRound - 1 ,EconomicEvent);
        
         printf("\n================================================\n");
         printf("Round %d Summery\n", *GameRound - 1);
         printf("================================================\n");

         for (int i = 0; i < PLAYERS; i++)
         {
            printf("\n%s\n\n", PLAYER_NAME[Player[i].PlayerID]);
            printf("Cash : LKR %d\n\n", Player[i].Cash);
            printf("Net Worth : LKR %d\n\n", Player[i].NetWorth);
            printf("Properties : %d\n\n", Player[i].PropertiesOwned);
            printf("Hotels : %d\n\n", Player[i].HotelsOwned);
            printf("Outstanding Loan Amount : LKR %d\n\n", Player[i].LoanAmount);
            printf("------------------------------------------------\n\n");

         }

    }
}
