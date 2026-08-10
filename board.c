#include "types.h"
#include <stdio.h>

//------------------------------------------------------------SQUARES NAMES ARRAY--------------------------------------------------------------
char SQUARES_NAME[40][50] = {
    "Go",
    "Pettah",
    "Community Development Fund",
    "Maradana",
    "Income Tax",
    "Colombo Fort Railway Station",
    "Bambalapitiya",
    "National Event Card 1",
    "Wellawatta",
    "Mount Lavinia",
    "Jail",
    "Nugegoda",
    "Ceylon Electricity Board",
    "Maharagama",
    "Kottawa",
    "Kandy Railway Station",
    "Negombo",
    "Sri Lanka Insurance",
    "Katunayake",
    "Ja-Ela",
    "Free Parking",
    "Kandy City",
    "National Event Card 2",
    "Peradenya",
    "Katugastota",
    "Galle Railway Station",
    "Galle Fort",
    "Unawatuna",
    "National Water Supply and Drainage Board",
    "Hikkaduwa",
    "Go To Jail",
    "Jaffna Town",
    "Nallur",
    "Ceylinco Insurance",
    "Trincomalee",
    "Jaffna Railway Station",
    "National Event Card 3",
    "Nuwara Eliya",
    "Bank Of Ceylon",
    "Galle Face"};

//------------------------------------------------------------INITIALIZE SQUARES--------------------------------------------------------------
void InitializeSquares(SquareType Square[])
{

    for (int i = 0; i < 40; i++)
    {
        Square[i].SquareID = i;

        Square[i].Group = NONE;

        Square[i].Owner = -1;

        Square[i].PurchasePrice = 0;
        Square[i].BaseRent = 0;

        Square[i].Houses = 0;
        Square[i].Hotel = 0;

        Square[i].Mortgaged = 0;

        Square[i].PropertyAge = 0;
        Square[i].PropertyCondition = 100;

        Square[i].MarketType = NO_MARKET;
        Square[i].MarketRounds = 0;
        // change this later
        Square[i].CurrentPriceOfHouse = 200;
        Square[i].CurrentPriceOfHotel = 200;
    }

    //---------------------------------------------------------------GO------------------------------------------------------------------

    Square[GO].GroupType = GO_SQUARE;

    //-----------------------------------------------------------Properties---------------------------------------------------------------

    Square[Pettah].GroupType = PROPERTY;
    Square[Pettah].Group = BROWN;
    Square[Pettah].PurchasePrice = 1500;
    Square[Pettah].BaseRent = 100;
    Square[Pettah].CurrentRent = 100;

    Square[Maradana].GroupType = PROPERTY;
    Square[Maradana].Group = BROWN;
    Square[Maradana].PurchasePrice = 1800;
    Square[Maradana].BaseRent = 120;
    Square[Maradana].CurrentRent = 120;

    Square[Bambalapitiya].GroupType = PROPERTY;
    Square[Bambalapitiya].Group = LIGHT_BLUE;
    Square[Bambalapitiya].PurchasePrice = 2500;
    Square[Bambalapitiya].BaseRent = 180;
    Square[Bambalapitiya].CurrentRent = 180;

    Square[Wellawatta].GroupType = PROPERTY;
    Square[Wellawatta].Group = LIGHT_BLUE;
    Square[Wellawatta].PurchasePrice = 2700;
    Square[Wellawatta].BaseRent = 200;
    Square[Wellawatta].CurrentRent = 200;

    Square[MountLavinia].GroupType = PROPERTY;
    Square[MountLavinia].Group = LIGHT_BLUE;
    Square[MountLavinia].PurchasePrice = 3000;
    Square[MountLavinia].BaseRent = 220;
    Square[MountLavinia].CurrentRent = 220;

    Square[Nugegoda].GroupType = PROPERTY;
    Square[Nugegoda].Group = PINK;
    Square[Nugegoda].PurchasePrice = 3500;
    Square[Nugegoda].BaseRent = 260;
    Square[Nugegoda].CurrentRent = 260;

    Square[Maharagama].GroupType = PROPERTY;
    Square[Maharagama].Group = PINK;
    Square[Maharagama].PurchasePrice = 3800;
    Square[Maharagama].BaseRent = 280;
    Square[Maharagama].CurrentRent = 280;

    Square[Kottawa].GroupType = PROPERTY;
    Square[Kottawa].Group = PINK;
    Square[Kottawa].PurchasePrice = 4000;
    Square[Kottawa].BaseRent = 300;
    Square[Kottawa].CurrentRent = 300;

    Square[Negombo].GroupType = PROPERTY;
    Square[Negombo].Group = ORANGE;
    Square[Negombo].PurchasePrice = 4500;
    Square[Negombo].BaseRent = 350;
    Square[Negombo].CurrentRent = 350;

    Square[Katunayake].GroupType = PROPERTY;
    Square[Katunayake].Group = ORANGE;
    Square[Katunayake].PurchasePrice = 4700;
    Square[Katunayake].BaseRent = 370;
    Square[Katunayake].CurrentRent = 370;

    Square[JaEla].GroupType = PROPERTY;
    Square[JaEla].Group = ORANGE;
    Square[JaEla].PurchasePrice = 5000;
    Square[JaEla].BaseRent = 400;
    Square[JaEla].CurrentRent = 400;

    Square[KandyCity].GroupType = PROPERTY;
    Square[KandyCity].Group = RED;
    Square[KandyCity].PurchasePrice = 5500;
    Square[KandyCity].BaseRent = 450;
    Square[KandyCity].CurrentRent = 450;

    Square[Peradenya].GroupType = PROPERTY;
    Square[Peradenya].Group = RED;
    Square[Peradenya].PurchasePrice = 5800;
    Square[Peradenya].BaseRent = 480;
    Square[Peradenya].CurrentRent = 480;

    Square[Katugastota].GroupType = PROPERTY;
    Square[Katugastota].Group = RED;
    Square[Katugastota].PurchasePrice = 6000;
    Square[Katugastota].BaseRent = 500;
    Square[Katugastota].CurrentRent = 500;

    Square[Gallefort].GroupType = PROPERTY;
    Square[Gallefort].Group = YELLOW;
    Square[Gallefort].PurchasePrice = 6500;
    Square[Gallefort].BaseRent = 600;
    Square[Gallefort].CurrentRent = 600;

    Square[Unawatuna].GroupType = PROPERTY;
    Square[Unawatuna].Group = YELLOW;
    Square[Unawatuna].PurchasePrice = 6800;
    Square[Unawatuna].BaseRent = 620;
    Square[Unawatuna].CurrentRent = 620;

    Square[Hikkaduwa].GroupType = PROPERTY;
    Square[Hikkaduwa].Group = YELLOW;
    Square[Hikkaduwa].PurchasePrice = 7000;
    Square[Hikkaduwa].BaseRent = 650;
    Square[Hikkaduwa].CurrentRent = 650;

    Square[JaffnaTown].GroupType = PROPERTY;
    Square[JaffnaTown].Group = GREEN;
    Square[JaffnaTown].PurchasePrice = 8000;
    Square[JaffnaTown].BaseRent = 750;
    Square[JaffnaTown].CurrentRent = 750;

    Square[Nallur].GroupType = PROPERTY;
    Square[Nallur].Group = GREEN;
    Square[Nallur].PurchasePrice = 8300;
    Square[Nallur].BaseRent = 780;
    Square[Nallur].CurrentRent = 780;

    Square[Trincomalee].GroupType = PROPERTY;
    Square[Trincomalee].Group = GREEN;
    Square[Trincomalee].PurchasePrice = 8500;
    Square[Trincomalee].BaseRent = 800;
    Square[Trincomalee].CurrentRent = 800;

    Square[NuwaraEliya].GroupType = PROPERTY;
    Square[NuwaraEliya].Group = DARK_BLUE;
    Square[NuwaraEliya].PurchasePrice = 10000;
    Square[NuwaraEliya].BaseRent = 1000;
    Square[NuwaraEliya].CurrentRent = 1000;

    Square[GalleFace].GroupType = PROPERTY;
    Square[GalleFace].Group = DARK_BLUE;
    Square[GalleFace].PurchasePrice = 12000;
    Square[GalleFace].BaseRent = 1200;
    Square[GalleFace].CurrentRent = 1200;

    //--------------------------------------------------------------Railway Stations----------------------------------------------------------------------

    Square[FortRailwayStation].GroupType = RAILWAY;
    Square[FortRailwayStation].PurchasePrice = 2000;
    Square[FortRailwayStation].CurrentRent = 250; // change this later !!!!!!!!!

    Square[KandyRailwayStation].GroupType = RAILWAY;
    Square[KandyRailwayStation].PurchasePrice = 2000; // change when sir gives the price
    Square[KandyRailwayStation].CurrentRent = 250;

    Square[GalleRailwayStation].GroupType = RAILWAY;
    Square[GalleRailwayStation].PurchasePrice = 2000;
    Square[GalleRailwayStation].CurrentRent = 250;

    Square[JaffnaRailwayStation].GroupType = RAILWAY;
    Square[JaffnaRailwayStation].PurchasePrice = 2000;
    Square[JaffnaRailwayStation].CurrentRent = 250;

    //----------------------------------------------------------------Utilities----------------------------------------------------------------------

    Square[NationalWaterSupplyAndDrainageBoard].GroupType = UTILITY;
    Square[NationalWaterSupplyAndDrainageBoard].PurchasePrice = 1500; // change when sir gives the price

    Square[CeylonElectricityBoard].GroupType = UTILITY;
    Square[CeylonElectricityBoard].PurchasePrice = 1500;

    //-------------------------------------------------------------------Taxes----------------------------------------------------------------------

    Square[IncomeTax].GroupType = TAX;

    //--------------------------------------------------------------Jail/ GO TO JAIL----------------------------------------------------------------------
    Square[Jail].GroupType = JAIL;
    Square[GoToJail].GroupType = GO_TO_JAIL;

    //----------------------------------------------------------------Free Parking----------------------------------------------------------------------
    Square[FreeParking].GroupType = FREE_PARKING;

    //--------------------------------------------------------------National Event Cards----------------------------------------------------------------------
    Square[NationalEventCard1].GroupType = NATIONAL_EVENT;
    Square[NationalEventCard2].GroupType = NATIONAL_EVENT;
    Square[NationalEventCard3].GroupType = NATIONAL_EVENT;

    //-----------------------------------------------------------------Community Fund----------------------------------------------------------------------

    Square[CommunityDevelopmentFund].GroupType = COMMUNITY_FUND;

    //--------------------------------------------------------------------Insurance----------------------------------------------------------------------

    Square[SriLankaInsurance].GroupType = INSURANCE;
    Square[CeylincoInsurance].GroupType = INSURANCE;

    //----------------------------------------------------------------------Bank----------------------------------------------------------------------

    Square[BankOfCeylon].GroupType = BANK;

    //-----------------------------------------------------------------------base rent froget--------------------------------------------
}

//------------------------------------------------------------PROCESS SQUARE--------------------------------------------------------------
void ProcessSquare(PlayerType Player[], SquareType Square[], int CurrentPlayer, int GameRound)
{
    switch (Square[Player[CurrentPlayer].Position].GroupType)
    {

    case PROPERTY:
        HandleProperty(Player, Square, CurrentPlayer);
        HandleEndTurnActions(Player, Square, CurrentPlayer);
        // update players status
        break;

    case RAILWAY:
        HandleRailway(Player, Square, CurrentPlayer);
        HandleEndTurnActions(Player, Square, CurrentPlayer);
        break;

    case UTILITY:
        HandleUtility(Player, Square, CurrentPlayer);
        HandleEndTurnActions(Player, Square, CurrentPlayer);
        break;

    case TAX:
        HandleTax(Player, Square, CurrentPlayer); // todo
        HandleEndTurnActions(Player, Square, CurrentPlayer);
        break;

    case JAIL:
        HandleEndTurnActions(Player, Square, CurrentPlayer);
        break;

    case GO_TO_JAIL:
        HandleGoToJail(Player, CurrentPlayer);
        HandleEndTurnActions(Player, Square, CurrentPlayer);
        break;

    case FREE_PARKING:
        HandleEndTurnActions(Player, Square, CurrentPlayer);
        break;

    case NATIONAL_EVENT:
        // HandleNationalEvent(Player, CurrentPlayer);   /todo
        HandleEndTurnActions(Player, Square, CurrentPlayer);
        break;

    case COMMUNITY_FUND:
        // HandleCommunityFund(Player, CurrentPlayer);  //todo
        HandleEndTurnActions(Player, Square, CurrentPlayer);
        break;

    case INSURANCE:
        HandleInsurance(Player, Square, CurrentPlayer, GameRound); // todo
        HandleEndTurnActions(Player, Square, CurrentPlayer);
        break;

    case BANK:
        // HandleBank(Player, CurrentPlayer);   //todo
        HandleEndTurnActions(Player, Square, CurrentPlayer);
        break;

    case GO_SQUARE:
        HandleEndTurnActions(Player, Square, CurrentPlayer);
        break;
    }
}

//-----------------------------------------------------------HANDLING SQUARES----------------------------------------------------------------

//-------handle property---------         ( players behaviours not defined yet !!)
void HandleProperty(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{
    if (Square[Player[CurrentPlayer].Position].Owner == -1)
    {
        if (ShouldBuyProperty(Player, Square, CurrentPlayer))
        {

            BuyProperty(Player, Square, CurrentPlayer);
        }
        else
        {
            StartAuction(Player, Square, CurrentPlayer);
        }
    }
    else if (Square[Player[CurrentPlayer].Position].Owner == CurrentPlayer)
    {
        // making houses ike things
    }
    else
    {
        RentProperty(Player, Square, CurrentPlayer);
    }
};

//-------handle Railway---------
void HandleRailway(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{

    if (Square[Player[CurrentPlayer].Position].Owner == -1)
    {
        if (ShouldBuyRailway(Player, Square, CurrentPlayer)) // done
        {

            BuyRailway(Player, Square, CurrentPlayer); // make Buyrailway in finance.c
        }
        else
        {
            StartAuction(Player, Square, CurrentPlayer);
        }
    }
    else if (Square[Player[CurrentPlayer].Position].Owner == CurrentPlayer)
    {
        // making houses ike things ,getting loans
    }
    else
    {
        RentRailway(Player, Square, CurrentPlayer); // make rentrailway in finance.c
    }
};

//-------handle utility--------
void HandleUtility(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{

    if (Square[Player[CurrentPlayer].Position].Owner == -1)
    {
        if (ShouldBuyUtility(Player, Square, CurrentPlayer)) // done
        {

            BuyUtility(Player, Square, CurrentPlayer); // make Buyutility in finance.c
        }
        else
        {
            StartAuction(Player, Square, CurrentPlayer);
        }
    }
    else if (Square[Player[CurrentPlayer].Position].Owner == CurrentPlayer)
    {
        // making houses ike things ,getting loans
    }
    else
    {
        RentUtility(Player, Square, CurrentPlayer); // make Rentutility in finance.c
    }
};

//--------HandleGoToJail------------
void HandleGoToJail(PlayerType Player[], int CurrentPlayer)
{
    Player[CurrentPlayer].Position = Jail;
    Player[CurrentPlayer].InJail = YES;
    Player[CurrentPlayer].JailTurns = 0;
    printf("\n%s landed on Go To Jail.", PLAYER_NAME[Player[CurrentPlayer].PlayerID]);
    printf("\n%s was sent to Jail.", PLAYER_NAME[Player[CurrentPlayer].PlayerID]);
};

//--------Handle tax------------
void HandleTax(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{

    PayTax(Player, Square, CurrentPlayer);
}

//--------Handle End Turn Actions-------------
void HandleEndTurnActions(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{
    HandleBuildHouses(Player, Square, CurrentPlayer); // make in finance
    HandleBuildHotels(Player, Square, CurrentPlayer);
}

//---------end round actions---------------

void HandleRoundEvents(PlayerType Player[], SquareType Square[], int CurrentRound, EconomicEventType EconomicEvent)
{

    if (CurrentRound % 10 == 0 || CurrentRound % 15 == 0 || CurrentRound % 20 == 0)
    {
        printf("\n\n========================================");
        printf("\nCurrent Market Conditions");
        printf("\n========================================");
    }

    //------------every round -------------------------------

    

    // UpdateMarketRounds(Square, Event);

    //-----------------------EVERY 10 ROUNDS--------------------

    if (CurrentRound % 10 == 0)
    {

        HandleInflation(Square);

        // HandleMarket(Square, Event);

        // HandleDisaster(Player, Square);
    }

    //---------------------EVERY 15 ROUNDS------------------------

    if (CurrentRound % 15 == 0)
    {
        HandleEconomicEvent(Player, Square, EconomicEvent);

        // HandleRegionalDevelopment(Square, Event);
    }

    //-------------------EVERY 20 ROUNDS---------------------

    if (CurrentRound % 20 == 0)
    {
        // HandleGovernmentRegulation(Square, Event);
    }


   //------------every round -------------------------------

    CheckInsuranceExpiry(Square, CurrentRound);
}

//------handle Building Houses-----------

void HandleBuildHouses(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{

    int Monopoly[9] = {0};
    int HaveMonopoly = 0;
    int SquareIDOfHouse = -1; // should buy will change this if have monopoly
    MonopolyFinder(Square, CurrentPlayer, Monopoly);

    for (int i = 0; i <= DARK_BLUE; i++)
    {
        if (Monopoly[i] > 0)
        {
            HaveMonopoly = 1;
        }
    }

    if (HaveMonopoly)
    {
        ShouldBuildHouse(Player, Square, CurrentPlayer, Monopoly);
    }
}

void HandleBuildHotels(PlayerType Player[], SquareType Square[], int CurrentPlayer)
{
    int Monopoly[9] = {0};

    MonopolyFinder(Square, CurrentPlayer, Monopoly);

    ShouldBuildHotel(Player, Square, CurrentPlayer, Monopoly);
}

void HandleInsurance(PlayerType Player[], SquareType Square[], int CurrentPlayer, int GameRound)
{
    for (int i = 0; i < SQUARES; i++)
    {
        if (Square[i].GroupType == PROPERTY && Square[i].Owner == CurrentPlayer && Square[i].InsuranceActive == NO)
        {
            int BuyInsurance = ShouldBuyInsurance(Player, Square, CurrentPlayer, i);
            if (BuyInsurance)
            {
                switch (BuyInsurance)
                {
                case 1:
                    BuyBasicInsurance(Player, Square, CurrentPlayer, i, GameRound);
                    break;

                case 2:
                    BuyComprehensiveInsurance(Player, Square, CurrentPlayer, i, GameRound);
                    break;

                case 3:
                    BuyBusinessInterruptionInsurance(Player, Square, CurrentPlayer, i, GameRound);
                    break;
                }
                // break;
            }
        }

        if (Square[i].GroupType == PROPERTY && Square[i].Owner == CurrentPlayer && Square[i].InsuranceActive == YES)
        {
            int RenewInsurance = ShouldRenewInsurance(Player, Square, CurrentPlayer, i , GameRound);
            if (RenewInsurance)
            {
                switch (RenewInsurance)
                {
                case 1:
                    RenewBasicInsurance(Player, Square, CurrentPlayer, i, GameRound);
                    break;

                case 2:
                    RenewComprehensiveInsurance(Player, Square, CurrentPlayer, i, GameRound);
                    break;

                case 3:
                    RenewBusinessInterruptionInsurance(Player, Square, CurrentPlayer, i, GameRound);
                    break;
                }
                // break;
            }
        }
    }
}
//----insurance expire msg ---------------

void CheckInsuranceExpiry(SquareType Square[], int GameRound)
{
   //printf("\n--------------INSURANCE NOTICES--------------");
   printf("\n");

    for (int i = 0; i < SQUARES; i++)
    {
        if (Square[i].InsuranceActive == YES)
        {
            if (Square[i].InsuranceExpireRound - GameRound == 3)
            {
                printf("\nINSURANCE NOTICE: Insurance for %s expires in 3 rounds.", SQUARES_NAME[i]);
            }

            if (GameRound >= Square[i].InsuranceExpireRound)
            {
                printf("\nINSURANCE EXPIRED: Insurance for %s has expired.",
                       SQUARES_NAME[i]);

                Square[i].InsuranceActive = NO;
                Square[i].InsuranceType = NO_INSURANCE;
                Square[i].InsuranceExpireRound = 0;
            }
        }
    }
    printf("\n");
}