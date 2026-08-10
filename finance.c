#include <stdio.h>
#include "types.h"

//-------------------------------------------------------------HANDLING SQUARES--------------------------------------------------------------


//------------------------------------------------------------BUY PRPERTY-------------------------
void BuyProperty(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{

    int PropertyID = Player[CurrentPlayer].Position;
    Player[CurrentPlayer].Cash -= Square[PropertyID].PurchasePrice;
    Square[PropertyID].Owner = CurrentPlayer;
    Player[CurrentPlayer].PropertiesOwned++;

    printf("\n%s purchased %s for LKR %d.", PLAYER_NAME[Player[CurrentPlayer].PlayerID], SQUARES_NAME[PropertyID], Square[PropertyID].PurchasePrice);
    // printf("\nCurrent Balance : LKR %d\n", Player[CurrentPlayer].Cash);
}

//--------------------------------------------------------RENT PROPERTY-----------------------------
void RentProperty(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{

    int PropertyID = Player[CurrentPlayer].Position;
    int PropertyOwner = Square[PropertyID].Owner;
    int Payment = 0;

    if (Square[PropertyID].Hotel == YES)
    {
        Player[CurrentPlayer].Cash -= ((Square[PropertyID].CurrentRent) * 10);
        Player[PropertyOwner].Cash += ((Square[PropertyID].CurrentRent) * 10);
        Payment = (Square[PropertyID].CurrentRent) * 10;
        printf("\n(HOTEL)");
    }
    else
    {
        switch (Square[PropertyID].Houses)
        {
        case 0:
            Player[CurrentPlayer].Cash -= ((Square[PropertyID].CurrentRent) * 1);
            Player[PropertyOwner].Cash += ((Square[PropertyID].CurrentRent) * 1);
            Payment = (Square[PropertyID].CurrentRent) * 1;
            break;

        case 1:
            Player[CurrentPlayer].Cash -= ((Square[PropertyID].CurrentRent) * 2);
            Player[PropertyOwner].Cash += ((Square[PropertyID].CurrentRent) * 2);
            Payment = (Square[PropertyID].CurrentRent) * 2;
            break;

        case 2:
            Player[CurrentPlayer].Cash -= ((Square[PropertyID].CurrentRent) * 3);
            Player[PropertyOwner].Cash += ((Square[PropertyID].CurrentRent) * 3);
            Payment = (Square[PropertyID].CurrentRent) * 3;
            break;

        case 3:
            Player[CurrentPlayer].Cash -= ((Square[PropertyID].CurrentRent) * 5);
            Player[PropertyOwner].Cash += ((Square[PropertyID].CurrentRent) * 5);
            Payment = (Square[PropertyID].CurrentRent) * 5;
            break;

        case 4:
            Player[CurrentPlayer].Cash -= ((Square[PropertyID].CurrentRent) * 7);
            Player[PropertyOwner].Cash += ((Square[PropertyID].CurrentRent) * 7);
            Payment = (Square[PropertyID].CurrentRent) * 7;
            break;
        }
    }

    printf("\n%s paid LKR %d to %s.", PLAYER_NAME[Player[CurrentPlayer].PlayerID], Payment, PLAYER_NAME[Player[PropertyOwner].PlayerID]);
    if (Square[PropertyID].Hotel == YES)
    {
        printf("(HOTEL)");
    }
    else if (Square[PropertyID].Houses == 1)
    {
        printf("(HOUSE)");
    }
    else if (Square[PropertyID].Houses == 2)
    {
        printf("(TWO HOUSES)");
    }
    else if (Square[PropertyID].Houses == 3)
    {
        printf("(THREE HOUSES)");
    }
    else if (Square[PropertyID].Houses == 4)
    {
        printf("(FOUR HOUSES)");
    }
}

//--------------------------------------------------BUY RAILWAY-----------------------------------------
void BuyRailway(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{

    int PropertyID = Player[CurrentPlayer].Position;
    Player[CurrentPlayer].Cash -= Square[PropertyID].PurchasePrice;
    Square[PropertyID].Owner = CurrentPlayer;
    Player[CurrentPlayer].RailwayStationsOwned++;

    printf("\n%s purchased %s for LKR %d.", PLAYER_NAME[Player[CurrentPlayer].PlayerID], SQUARES_NAME[PropertyID], Square[PropertyID].PurchasePrice);
}

//-------------------------------------------------RENT RAILWAY-----------------------------------------

void RentRailway(PlayerType Player[], SquareType Square[], int CurrentPlayer)

{

    int PropertyID = Player[CurrentPlayer].Position;
    int Rent = Square[PropertyID].CurrentRent;
    int PropertyOwner = Square[PropertyID].Owner;
    int RailWaysOwned = Player[PropertyOwner].RailwayStationsOwned; // add railway station owner !!!!!!

    switch (RailWaysOwned)
    {
    case 1:
        Rent = Rent;
        break;
    case 2:
        Rent *= 2;
        break;
    case 3:
        Rent *= 4;
        break;
    case 4:
        Rent *= 8;
        break;

    default:
        break;
    }

    Player[CurrentPlayer].Cash -= Rent;
    Player[PropertyOwner].Cash += Rent;
    printf("\n%s paid LKR %d rent to %s.", PLAYER_NAME[Player[CurrentPlayer].PlayerID], Rent, PLAYER_NAME[Player[PropertyOwner].PlayerID]);
}

//-------------------------------------------------BUY UTILITY---------------------------------------

void BuyUtility(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{
    int UtilityID = Player[CurrentPlayer].Position;

    Player[CurrentPlayer].Cash -= Square[UtilityID].PurchasePrice;
    Square[UtilityID].Owner = CurrentPlayer;
    Player[CurrentPlayer].UtilitiesOwned++;

    printf("\n%s purchased %s for LKR %d.", PLAYER_NAME[Player[CurrentPlayer].PlayerID], SQUARES_NAME[UtilityID], Square[UtilityID].PurchasePrice);
}

void RentUtility(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{
    int Rent = 0;
    int Diece = Player[CurrentPlayer].CurrentDiceRoll;
    int UtilityID = Player[CurrentPlayer].Position;
    int UtilityOwner = Square[UtilityID].Owner;
    int UtilitiesOwned = Player[UtilityOwner].UtilitiesOwned; // add railway station owner !!!!!!

    switch (UtilitiesOwned)
    {
    case 1:
        Rent = Diece * 4;
        break;
    case 2:
        Rent = Diece * 10;
        break;
    default:
        break;
    }

    Player[CurrentPlayer].Cash -= Rent;
    Player[UtilityOwner].Cash += Rent;
    printf("\n%s paid LKR %d rent to %s.", PLAYER_NAME[Player[CurrentPlayer].PlayerID], Rent, PLAYER_NAME[Player[UtilityOwner].PlayerID]);
}
//-----------------------------------------------START OCTION---------------------------------------
void StartAuction(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{
    int PropertyID = Player[CurrentPlayer].Position;
    printf("\n\n--------------- Auction Started --------------------");
    // printf("\nAuction Started.");
    printf("\n\nProperty :");
    printf("\n%s", SQUARES_NAME[PropertyID]);
    printf("\n\nOpening Bid :");
    printf("\nLKR %d\n", (Square[PropertyID].PurchasePrice) / 2);

    int ActivePlayers = 0;
    int PlayerWithdrawn[PLAYERS] = {0};
    int CurrentBid = (Square[PropertyID].PurchasePrice) / 2;
    int Winner = -1;

    for (int i = 0; i < PLAYERS; i++)
    {
        if (Player[i].Bankrupt == NO)
            ActivePlayers++;
    }

    while (ActivePlayers > 1)
    {
        for (int i = 0; i < PLAYERS; i++)
        {
            if (Player[i].Bankrupt == YES)
                continue;

            if (PlayerWithdrawn[i] == YES)
                continue;

            if (ShouldBid(Player, Square, i, CurrentBid))
            {

                Winner = i;

                printf("\n%s bids LKR %d.", PLAYER_NAME[Player[i].PlayerID], CurrentBid);
                CurrentBid += 250;
            }
            else
            {
                PlayerWithdrawn[i] = YES;
                ActivePlayers--;

                printf("\n%s withdraws.", PLAYER_NAME[Player[i].PlayerID]);

                if (ActivePlayers <= 1)
                {

                    break;
                } // to stop print withdraw msg to winner
            }
        }
    }

    if (Winner == -1)
    {
        // printf("\nAuction end.");
        printf("\nThe property remains unowned.");
        printf("\n--------------- Auction End --------------------");
    }
    else
    {
        Square[PropertyID].Owner = Winner;
        Player[Winner].Cash -= CurrentBid - 250; // already increased current bid so need - 250

        switch (Square[PropertyID].GroupType)
        {
        case PROPERTY:
            Player[Winner].PropertiesOwned++;
            break;
        case RAILWAY:
            Player[Winner].RailwayStationsOwned++;
            break;
        case UTILITY:
            Player[Winner].UtilitiesOwned++;
            break;

        default:
            break;
        }
        printf("\n\n%s wins the auction for LKR %d\n", PLAYER_NAME[Player[Winner].PlayerID], CurrentBid - 250);
        printf("\n--------------- Auction End --------------------");
    }
}

//-------------------------------------------pay tax-------------------------
void PayTax(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{ // chsnge this laterrrr
    int TaxAmount = 100;
    Player[CurrentPlayer].Cash -= TaxAmount;
    printf("\n%s paid Income Tax of LKR %d.", PLAYER_NAME[Player[CurrentPlayer].PlayerID], TaxAmount);
}

//------------------------------build house--------------------------
void BuildHouse(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Property)
{
    Player[CurrentPlayer].Cash -= Square[Property].CurrentPriceOfHouse;
    Square[Property].Houses++;
    printf("\n%s built a house on %s for LKR %d. (%d/4)", PLAYER_NAME[Player[CurrentPlayer].PlayerID], SQUARES_NAME[Property], Square[Property].CurrentPriceOfHouse, Square[Property].Houses);
}

void BuildHotel(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Property)
{
    int HotelPrice = Square[Property].CurrentPriceOfHotel;

    Player[CurrentPlayer].Cash -= HotelPrice;

    Square[Property].Houses = 0;
    Square[Property].Hotel = 1;
    Player[CurrentPlayer].HotelsOwned++;

    printf("\n%s built a hotel on %s for LKR %d.", PLAYER_NAME[Player[CurrentPlayer].PlayerID], SQUARES_NAME[Property], HotelPrice);
}

//--------------------buy insurance------------------------

void BuyBasicInsurance(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Property, int GameRound)
{
    int PropertyValue;
    int InsurancePrice;

    PropertyValue = Square[Property].PurchasePrice + Square[Property].Houses * Square[Property].CurrentPriceOfHouse + Square[Property].Hotel * Square[Property].CurrentPriceOfHotel;

    InsurancePrice = PropertyValue * 5 / 100;

    Player[CurrentPlayer].Cash -= InsurancePrice;

    Square[Property].InsuranceActive = YES;
    Square[Property].InsuranceType = BASIC_INSURANCE;
    Square[Property].InsuranceExpireRound = GameRound + 20; // 
    printf("\n%s bought Basic Insurance for %s.",
           PLAYER_NAME[Player[CurrentPlayer].PlayerID], SQUARES_NAME[Property]);

    printf("\nInsurance Premium : LKR %d", InsurancePrice);
    printf("\nInsurance Expire Round : %d", Square[Property].InsuranceExpireRound);
}

void BuyComprehensiveInsurance(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Property, int GameRound)
{
    int PropertyValue;
    int InsurancePrice;

    PropertyValue = Square[Property].PurchasePrice + Square[Property].Houses * Square[Property].CurrentPriceOfHouse + Square[Property].Hotel * Square[Property].CurrentPriceOfHotel;

    InsurancePrice = PropertyValue * 10 / 100;

    Player[CurrentPlayer].Cash -= InsurancePrice;

    Square[Property].InsuranceActive = YES;
    Square[Property].InsuranceType = COMPREHENSIVE_INSURANCE;
    Square[Property].InsuranceExpireRound = GameRound + 20;

    printf("\n%s bought Comprehensive Insurance for %s.",
           PLAYER_NAME[Player[CurrentPlayer].PlayerID], SQUARES_NAME[Property]);

    printf("\nInsurance Premium : LKR %d", InsurancePrice);
    printf("\nInsurance Expire Round : %d", Square[Property].InsuranceExpireRound);
}

void BuyBusinessInterruptionInsurance(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Property, int GameRound)
{
    int PropertyValue;
    int InsurancePrice;

    PropertyValue = Square[Property].PurchasePrice + Square[Property].Houses * Square[Property].CurrentPriceOfHouse + Square[Property].Hotel * Square[Property].CurrentPriceOfHotel;

    InsurancePrice = PropertyValue * 15 / 100;

    Player[CurrentPlayer].Cash -= InsurancePrice;

    Square[Property].InsuranceActive = YES;
    Square[Property].InsuranceType = BUSINESS_INTERRUPTION_INSURANCE;
    Square[Property].InsuranceExpireRound = GameRound + 20;

    printf("\n%s bought Business Interruption Insurance for %s.",
           PLAYER_NAME[Player[CurrentPlayer].PlayerID], SQUARES_NAME[Property]);

    printf("\nInsurance Premium : LKR %d", InsurancePrice);
    printf("\nInsurance Expire Round : %d", Square[Property].InsuranceExpireRound);
}

//-----------------------renew insurance----------------------------
void RenewBasicInsurance(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Property, int GameRound)
{
    int PropertyValue;
    int InsurancePrice;

    PropertyValue = Square[Property].PurchasePrice + Square[Property].Houses * Square[Property].CurrentPriceOfHouse + Square[Property].Hotel * Square[Property].CurrentPriceOfHotel;

    InsurancePrice = PropertyValue * 5 / 100;

    Player[CurrentPlayer].Cash -= InsurancePrice;

    Square[Property].InsuranceActive = YES;
    Square[Property].InsuranceType = BASIC_INSURANCE;
    Square[Property].InsuranceExpireRound += 20; // 
    printf("\n%s renewed Basic Insurance for %s.",
           PLAYER_NAME[Player[CurrentPlayer].PlayerID], SQUARES_NAME[Property]);

    printf("\nInsurance Premium : LKR %d", InsurancePrice);
    printf("\nInsurance Expire Round : %d", Square[Property].InsuranceExpireRound);
}

void RenewComprehensiveInsurance(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Property, int GameRound)
{
    int PropertyValue;
    int InsurancePrice;

    PropertyValue = Square[Property].PurchasePrice + Square[Property].Houses * Square[Property].CurrentPriceOfHouse + Square[Property].Hotel * Square[Property].CurrentPriceOfHotel;

    InsurancePrice = PropertyValue * 10 / 100;

    Player[CurrentPlayer].Cash -= InsurancePrice;

    Square[Property].InsuranceActive = YES;
    Square[Property].InsuranceType = COMPREHENSIVE_INSURANCE;
    Square[Property].InsuranceExpireRound += 20; // 
    printf("\n%s renewed Comprehensive Insurance for %s.",
           PLAYER_NAME[Player[CurrentPlayer].PlayerID], SQUARES_NAME[Property]);

    printf("\nInsurance Premium : LKR %d", InsurancePrice);
    printf("\nInsurance Expire Round : %d", Square[Property].InsuranceExpireRound);
}

void RenewBusinessInterruptionInsurance(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Property, int GameRound)
{
    int PropertyValue;
    int InsurancePrice;

    PropertyValue = Square[Property].PurchasePrice + Square[Property].Houses * Square[Property].CurrentPriceOfHouse + Square[Property].Hotel * Square[Property].CurrentPriceOfHotel;

    InsurancePrice = PropertyValue * 15 / 100;

    Player[CurrentPlayer].Cash -= InsurancePrice;

    Square[Property].InsuranceActive = YES;
    Square[Property].InsuranceType = BUSINESS_INTERRUPTION_INSURANCE;
    Square[Property].InsuranceExpireRound += 20; // 
    printf("\n%s renewed Business Interruption Insurance for %s.", PLAYER_NAME[Player[CurrentPlayer].PlayerID], SQUARES_NAME[Property]);

    printf("\nInsurance Premium : LKR %d", InsurancePrice);
    printf("\nInsurance Expire Round : %d", Square[Property].InsuranceExpireRound);
}