#include <stdio.h>
#include "types.h"

/*

"Aggressive Invester" player id = 0,
"Conservative Banker" player id = 1,
"Risk Taker" player id = 2,
"Oppertunistic Trader"* player id = 3/

*/

//------------------------------------------------------------PLAYER NAMES ARRAY--------------------------------------------------------------
char PLAYER_NAME[4][50] = {
    "Aggressive Invester",
    "Conservative Banker",
    "Risk Taker",
    "Oppertunistic Trader"};

//------------------------------------------------------------INITIALIZE PLAYERS--------------------------------------------------------------
void InitializePlayers(PlayerType Player[], int PlayerSequence[])
{

    for (int i = 0; i < PLAYERS; i++)
    {
        Player[i].PlayerID = PlayerSequence[i];
        Player[i].Position = 0;
        Player[i].Cash = 30000;
        Player[i].PlayerRound = 1;
        Player[i].Bankrupt = 0;
        Player[i].InJail = 0;
        Player[i].JailTurns = 0;
        Player[i].PropertiesOwned = 0;
        Player[i].HotelsOwned = 0;
        Player[i].RailwayStationsOwned = 0;
        Player[i].UtilitiesOwned = 0;
        Player[i].LoanAmount = 0;
        Player[i].LoanInterest = 0;
        Player[i].LoanRounds = 0;
        Player[i].NetWorth = 0;
        // printf("%d\n", Player[i].PlayerID);
    }
}

//------------------------------------------------------------MOVE PLAYER--------------------------------------------------------------
void MovePlayer(PlayerType Player[], SquareType Square[], int *GameRound, EconomicEventType EconomicEvent)
{

    for (int i = 0; i < PLAYERS; i++)
    {
        if (*GameRound > MAX_ROUND)
        {
            break;
        }

        //------in jail check ------
        if (Player[i].InJail == YES)
        {
            if (Player[i].JailTurns >= 3)
            {

                Player[i].InJail = NO;
                Player[i].JailTurns = 0;

                if (Player[i].PlayerRound < *GameRound)
                {
                    Player[i].PlayerRound = *GameRound;
                }

                printf("\n%s released from jail by staying three rounds.", PLAYER_NAME[Player[i].PlayerID]);
            }
            else if (ShouldPayJailFine(Player, i))
            {
                Player[i].InJail = NO;
                Player[i].JailTurns = 0;
                Player[i].Cash -= 300;

                if (Player[i].PlayerRound < *GameRound)
                {
                    Player[i].PlayerRound = *GameRound;
                }

                printf("\n%s released from jail by paying fine.", PLAYER_NAME[Player[i].PlayerID]);
            }
        }

        int FirstRoll = RollDice();
        int SecondRoll = RollDice();

        //------checking double roll-----

        if (FirstRoll == SecondRoll)
        {
            Player[i].Tie = YES;
        }
        else
        {
            Player[i].Tie = NO;
        }

        printf("\n%s rolled %d+%d = %d.", PLAYER_NAME[Player[i].PlayerID], FirstRoll, SecondRoll, FirstRoll + SecondRoll);

        if (Player[i].InJail)
        {

            if (Player[i].Tie)
            {

                Player[i].InJail = NO;
                Player[i].JailTurns = 0;

                if (Player[i].PlayerRound < *GameRound)
                {
                    Player[i].PlayerRound = *GameRound;
                }

                printf("\n%s released from jail by rolling doubles.", PLAYER_NAME[Player[i].PlayerID]);
            }
            else
            {
                Player[i].JailTurns += 1;
                printf("\n%s stays on jail (%d/3).\n", PLAYER_NAME[Player[i].PlayerID], Player[i].JailTurns);
                continue;
            }
        }

        //------move players-----------------

        int OldPosition = Player[i].Position;
        Player[i].Position += (FirstRoll + SecondRoll);
        Player[i].CurrentDiceRoll = FirstRoll + SecondRoll;

        int NewPosition = Player[i].Position;

        if (NewPosition >= SQUARES)
        {
            NewPosition %= SQUARES;
        }

        printf("\n%s moves from Square %d to Square %d.", PLAYER_NAME[Player[i].PlayerID], OldPosition, NewPosition);
        printf("\n%s landed on %s.", PLAYER_NAME[Player[i].PlayerID], SQUARES_NAME[NewPosition]);

        /*if (NewPosition == GoToJail)
        {
            printf("\n%s send to jail.", PLAYER_NAME[Player[i].PlayerID]);
        } */

        if (Player[i].Position >= SQUARES)
        {
            Player[i].PlayerRound += 1;
            Player[i].Position %= SQUARES;
            Player[i].Cash += GO_MONEY;

            printf("\n\n%s passed GO.", PLAYER_NAME[Player[i].PlayerID]);
            printf("\nCollected LKR 2,000.");
            printf("\nCurrent Balance : LKR %d\n", Player[i].Cash);

            GameRoundCal(Player, GameRound, i, Square, EconomicEvent);
        }

        ProcessSquare(Player, Square, i, *GameRound);
        printf("\n");
    }
}

//--------------------------------------------------------FIND MONOPOLY-----------------------------------------------

void MonopolyFinder(SquareType Square[], int CurrentPlayer, int Monopoly[])
{

    for (int Group = BROWN; Group <= DARK_BLUE; Group++)
    {
        int HasMonopoly = 0;

        for (int i = 0; i < SQUARES; i++)
        {
            if (Square[i].Group != Group)
                continue;

            if (Square[i].Owner != CurrentPlayer)
            {
                HasMonopoly = -1;
                break;
            }

            HasMonopoly++;
        }

        if (HasMonopoly == -1)
            continue;

        if ((Group == BROWN || Group == DARK_BLUE) && HasMonopoly == 2)
        {
            Monopoly[Group] = YES;
        }
        else if (HasMonopoly == 3)
        {
            Monopoly[Group] = YES;
        }
    }
}

//------------------------------------------------------------DECISIONS (start with should) ---------------------------------------------------------------

//----------JAIL FINE-------------
int ShouldPayJailFine(PlayerType Player[], int CurrentPlayer)

{
    switch (Player[CurrentPlayer].PlayerID)
    {
    case AggressiveInvester:
        if (Player[CurrentPlayer].Cash >= 300)
        {
            return YES;
        }
        else
        {
            return NO;
        }

    case OppertunisticTrader:
        if (Player[CurrentPlayer].Cash > 20000)
        {
            return YES;
        }
        else
        {
            return NO;
        }

    default:
        return NO;
    }
}

//---------BUY PROPERTY----------
int ShouldBuyProperty(PlayerType Player[], SquareType Square[], int CurrentPlayer)

{

    switch (Player[CurrentPlayer].PlayerID)
    {
    case AggressiveInvester:
        if (Player[CurrentPlayer].Cash - Square[Player[CurrentPlayer].Position].PurchasePrice >= MIN_RENT_RESERVE) // change min rent reserve later
            return YES;
        else
            return NO;
        break;

    case ConservativeBanker:

        // Buy only if at least 50% of current cash remains.x
        if ((Player[CurrentPlayer].Cash - Square[Player[CurrentPlayer].Position].PurchasePrice) >= (Player[CurrentPlayer].Cash / 2))
        {
            return YES;
        }
        return NO;
        break;

    case RiskTaker:
        if ((Player[CurrentPlayer].Cash >= Square[Player[CurrentPlayer].Position].PurchasePrice))
        {
            return YES;
        }
        return NO;
        break;

    case OppertunisticTrader:
        /*
               TODO

               Buy only when projected appreciation
               exceeds construction costs.

               After implementing:
                   - Inflation
                   - Market Boom / Decline
                   - Regional Development
                   - Government Regulations

               replace this with the proper calculation.
           */

        return NO;
        break;
    }
    return NO;
}

//--------Buy Railway----------

int ShouldBuyRailway(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{

    switch (Player[CurrentPlayer].PlayerID)
    {
    case AggressiveInvester:
        if (1)
        {
            return YES;
        }
        return NO;
        break;

    case ConservativeBanker:

        if (0)
        {
            return YES;
        }
        return NO;
        break;

    case RiskTaker:
        if (1)
        {
            return YES;
        }
        return NO;
        break;

    case OppertunisticTrader:
        if (0)
        {
            return YES;
        }
        return NO;
        break;
    }
    return NO;
}

//-----Buy Utillity----------

int ShouldBuyUtility(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{
    switch (Player[CurrentPlayer].PlayerID)
    {
    case AggressiveInvester:
        if (0)
        {
            return YES;
        }
        return NO;
        break;

    case ConservativeBanker:

        if (1)
        {
            return YES;
        }
        return NO;
        break;

    case RiskTaker:
        if (0)
        {
            return YES;
        }
        return NO;
        break;

    case OppertunisticTrader:
        if (1)
        {
            return YES;
        }
        return NO;
        break;
    }
    return NO;
}

int ShouldBid(PlayerType Player[], SquareType Square[], int CurrentPlayer, int CurrentBid)
{
    int PropertyID = Player[CurrentPlayer].Position;

    switch (Player[CurrentPlayer].PlayerID)
    {
    case AggressiveInvester:

        if (Player[CurrentPlayer].Cash >= CurrentBid &&
            CurrentBid <= (Square[PropertyID].PurchasePrice * 120) / 100)
        {
            return YES;
        }
        return NO;

    case ConservativeBanker:

        if (Player[CurrentPlayer].Cash >= CurrentBid &&
            CurrentBid <= (Square[PropertyID].PurchasePrice * 120) / 100)
        {
            return YES;
        }
        return NO;

    case RiskTaker:

        if (Player[CurrentPlayer].Cash >= CurrentBid &&
            CurrentBid <= (Square[PropertyID].PurchasePrice * 120) / 100)
        {
            return YES;
        }
        return NO;

    case OppertunisticTrader:

        if (Player[CurrentPlayer].Cash >= CurrentBid &&
            CurrentBid <= (Square[PropertyID].PurchasePrice * 120) / 100)
        {
            return YES;
        }
        return NO;
    }

    return NO;
}

void ShouldBuildHouse(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Monopoly[])
{
    switch (Player[CurrentPlayer].PlayerID)
    {
    case AggressiveInvester:
        for (int GROUP = BROWN; GROUP <= DARK_BLUE; GROUP++)
        {
            int built_something = 1;
            while (built_something)
            {
                built_something = 0;

                for (int i = 0; i < SQUARES; i++)
                {
                    if (Square[i].Group != GROUP)
                    {
                        continue;
                    }

                    if (Monopoly[GROUP] > 0 && Player[CurrentPlayer].Cash >= Square[i].CurrentPriceOfHouse && Square[i].Houses < 4 && Square[i].Hotel == 0)
                    {
                        BuildHouse(Player, Square, CurrentPlayer, i);
                        built_something = 1;
                    }
                }
            }
        }
        break;

    case ConservativeBanker:

        for (int GROUP = BROWN; GROUP <= DARK_BLUE; GROUP++)
        {
            int built_something = 1;
            while (built_something)
            {
                built_something = 0;

                for (int i = 0; i < SQUARES; i++)
                {
                    if (Square[i].Group != GROUP)
                    {
                        continue;
                    }

                    if (Monopoly[GROUP] > 0 && Player[CurrentPlayer].Cash >= Square[i].CurrentPriceOfHouse && Square[i].Houses < 4 && Square[i].Hotel == 0)
                    {
                        BuildHouse(Player, Square, CurrentPlayer, i);
                        built_something = 1;
                    }
                }
            }
        }

        break;

    case RiskTaker:

        for (int GROUP = BROWN; GROUP <= DARK_BLUE; GROUP++)
        {
            int built_something = 1;
            while (built_something)
            {
                built_something = 0;

                for (int i = 0; i < SQUARES; i++)
                {
                    if (Square[i].Group != GROUP)
                    {
                        continue;
                    }

                    if (Monopoly[GROUP] > 0 && Player[CurrentPlayer].Cash >= Square[i].CurrentPriceOfHouse && Square[i].Houses < 4 && Square[i].Hotel == 0)
                    {
                        BuildHouse(Player, Square, CurrentPlayer, i);
                        built_something = 1;
                    }
                }
            }
        }

        break;

    case OppertunisticTrader:

        for (int GROUP = BROWN; GROUP <= DARK_BLUE; GROUP++)
        {
            int built_something = 1;
            while (built_something)
            {
                built_something = 0;

                for (int i = 0; i < SQUARES; i++)
                {
                    if (Square[i].Group != GROUP)
                    {
                        continue;
                    }

                    if (Monopoly[GROUP] > 0 && Player[CurrentPlayer].Cash >= Square[i].CurrentPriceOfHouse && Square[i].Houses < 4 && Square[i].Hotel == 0)
                    {
                        BuildHouse(Player, Square, CurrentPlayer, i);
                        built_something = 1;
                    }
                }
            }
        }

        break;
    }
}

void ShouldBuildHotel(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Monopoly[])

{
    switch (Player[CurrentPlayer].PlayerID)
    {
    case AggressiveInvester:

        for (int GROUP = BROWN; GROUP <= DARK_BLUE; GROUP++)
        {
            for (int i = 0; i < SQUARES; i++)
            {
                if (Square[i].GroupType != PROPERTY || Square[i].Group != GROUP)
                {
                    continue;
                }

                if (Monopoly[GROUP] > 0 && Square[i].Houses == 4 && Square[i].Hotel == 0 && Player[CurrentPlayer].Cash >= Square[i].CurrentPriceOfHotel)
                {
                    BuildHotel(Player, Square, CurrentPlayer, i);
                }
            }
        }

        break;

    case ConservativeBanker:

        for (int GROUP = BROWN; GROUP <= DARK_BLUE; GROUP++)
        {
            for (int i = 0; i < SQUARES; i++)
            {
                if (Square[i].GroupType != PROPERTY ||
                    Square[i].Group != GROUP)
                {
                    continue;
                }

                if (Monopoly[GROUP] > 0 &&
                    Square[i].Houses == 4 &&
                    Square[i].Hotel == 0 &&
                    Player[CurrentPlayer].Cash >=
                        Square[i].CurrentPriceOfHotel)
                {
                    BuildHotel(Player, Square, CurrentPlayer, i);
                }
            }
        }

        break;

    case RiskTaker:

        for (int GROUP = BROWN; GROUP <= DARK_BLUE; GROUP++)
        {
            for (int i = 0; i < SQUARES; i++)
            {
                if (Square[i].GroupType != PROPERTY ||
                    Square[i].Group != GROUP)
                {
                    continue;
                }

                if (Monopoly[GROUP] > 0 &&
                    Square[i].Houses == 4 &&
                    Square[i].Hotel == 0 &&
                    Player[CurrentPlayer].Cash >=
                        Square[i].CurrentPriceOfHotel)
                {
                    BuildHotel(Player, Square, CurrentPlayer, i);
                }
            }
        }

        break;

    case OppertunisticTrader:

        for (int GROUP = BROWN; GROUP <= DARK_BLUE; GROUP++)
        {
            for (int i = 0; i < SQUARES; i++)
            {
                if (Square[i].GroupType != PROPERTY ||
                    Square[i].Group != GROUP)
                {
                    continue;
                }

                if (Monopoly[GROUP] > 0 &&
                    Square[i].Houses == 4 &&
                    Square[i].Hotel == 0 &&
                    Player[CurrentPlayer].Cash >=
                        Square[i].CurrentPriceOfHotel)
                {
                    BuildHotel(Player, Square, CurrentPlayer, i);
                }
            }
        }

        break;
    }
}

int ShouldBuyInsurance(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Property)

{

    int PropertyValue = Square[Property].PurchasePrice + Square[Property].Houses * Square[Property].CurrentPriceOfHouse + Square[Property].Hotel * Square[Property].CurrentPriceOfHotel;
    int TypeOfInsurance = 0;
    switch (Player[CurrentPlayer].PlayerID)
    {
    case AggressiveInvester:

        if (PropertyValue * 10 / 100 <= Player[CurrentPlayer].Cash)
        {
            TypeOfInsurance = 2;
        }

        switch (TypeOfInsurance)
        {
        case 1:
            return BASIC_INSURANCE;

        case 2:
            return COMPREHENSIVE_INSURANCE;

        case 3:
            return BUSINESS_INTERRUPTION_INSURANCE;
        }
        break;

    case ConservativeBanker:

        if (PropertyValue * 10 / 100 <= Player[CurrentPlayer].Cash)
        {
            TypeOfInsurance = 2;
        }

        switch (TypeOfInsurance)
        {
        case 1:
            return COMPREHENSIVE_INSURANCE;

        case 2:
            return BASIC_INSURANCE;

        case 3:
            return BUSINESS_INTERRUPTION_INSURANCE;
        }

        break;

    case RiskTaker:

        if (PropertyValue * 10 / 100 <= Player[CurrentPlayer].Cash)
        {
            TypeOfInsurance = 2;
        }

        switch (TypeOfInsurance)
        {
        case 1:
            return BUSINESS_INTERRUPTION_INSURANCE;

        case 2:
            return COMPREHENSIVE_INSURANCE;

        case 3:
            return BASIC_INSURANCE;
        }

        break;

    case OppertunisticTrader:

        if (PropertyValue * 10 / 100 <= Player[CurrentPlayer].Cash)
        {
            TypeOfInsurance = 2;
        }

        switch (TypeOfInsurance)
        {
        case 1:
            return BASIC_INSURANCE;

        case 2:
            return COMPREHENSIVE_INSURANCE;

        case 3:
            return BUSINESS_INTERRUPTION_INSURANCE;
        }

        break;
    }

    return NO_INSURANCE;
}

int ShouldRenewInsurance(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Property, int GameRound)

{

    int PropertyValue = Square[Property].PurchasePrice + Square[Property].Houses * Square[Property].CurrentPriceOfHouse + Square[Property].Hotel * Square[Property].CurrentPriceOfHotel;
    int TypeOfInsurance = Square[Property].InsuranceType;

    // to check insurance notice return NO ;

    switch (Player[CurrentPlayer].PlayerID)
    {
    case AggressiveInvester:

       /* if (PropertyValue * 10 / 100 > Player[CurrentPlayer].Cash)
        {
            return NO_INSURANCE;
        }
        if (Square[Property].InsuranceExpireRound > GameRound + 2 )
        {
            return NO_INSURANCE;
        }
        */

        switch (TypeOfInsurance)
        {
        case 1:

            return BASIC_INSURANCE;

        case 2:
            return COMPREHENSIVE_INSURANCE;

        case 3:
            return BUSINESS_INTERRUPTION_INSURANCE;
        }
        break;

    case ConservativeBanker:

        /* if (PropertyValue * 10 / 100 > Player[CurrentPlayer].Cash)
        {
            return NO_INSURANCE;
        }
        if (Square[Property].InsuranceExpireRound > GameRound + 1)
        {
            return NO_INSURANCE;
        }

        */

        switch (TypeOfInsurance)
        {
        case 1:
            return COMPREHENSIVE_INSURANCE;

        case 2:
            return BASIC_INSURANCE;

        case 3:
            return BUSINESS_INTERRUPTION_INSURANCE;
        }

        break;

    case RiskTaker:

        /* if (PropertyValue * 10 / 100 > Player[CurrentPlayer].Cash)
        {
            return NO_INSURANCE;
        }
        if (Square[Property].InsuranceExpireRound > GameRound + 1)
        {
            return NO_INSURANCE;
        }
        */

        switch (TypeOfInsurance)
        {
        case 1:
            return BUSINESS_INTERRUPTION_INSURANCE;

        case 2:
            return COMPREHENSIVE_INSURANCE;

        case 3:
            return BASIC_INSURANCE;
        }

        break;

    case OppertunisticTrader:

        /* if (PropertyValue * 10 / 100 > Player[CurrentPlayer].Cash)
        {
            return NO_INSURANCE;
        }
        if (Square[Property].InsuranceExpireRound > GameRound + 1)
        {
            return NO_INSURANCE;
        }
        */

        switch (TypeOfInsurance)
        {
        case 1:
            return BASIC_INSURANCE;

        case 2:
            return COMPREHENSIVE_INSURANCE;

        case 3:
            return BUSINESS_INTERRUPTION_INSURANCE;
        }

        break;
    }

    return NO_INSURANCE;
}