#include <stdio.h>
#include <stdlib.h>
#include "types.h"

/*void HandleRoundEvents(PlayerType Player[], SquareType Square[], int CurrentRound, EconomicEventType EconomicEvent)
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
}
    */

//---------Inflation--------------------------------

int GenerateInflation()
{
    int InflationRates[6] = {-3, 0, 2, 5, 8, 12};

    return InflationRates[rand() % 6];
}

void HandleInflation(SquareType Square[])
{
    int Inflation = GenerateInflation();

    printf("\n\nInflation");
    printf("\n------------");
    printf("\nInflation Rate : %d%%", Inflation);

    for (int i = 0; i < SQUARES; i++)
    {
        if (Square[i].GroupType == PROPERTY)
        {
            Square[i].PurchasePrice = Square[i].PurchasePrice * (100 + Inflation) / 100;

            Square[i].CurrentRent = Square[i].CurrentRent * (100 + Inflation) / 100;

            Square[i].CurrentPriceOfHouse = Square[i].CurrentPriceOfHouse * (100 + Inflation) / 100;

            Square[i].CurrentPriceOfHotel = Square[i].CurrentPriceOfHotel * (100 + Inflation) / 100;

            // addmore later
        }
    }

    // printf("\n==============================\n");
}


//-----------------econ event -----------------------(permanant)---

void HandleEconomicEvent(PlayerType Player[], SquareType Square[], EconomicEventType EconomicEvent)
{
    int Event = rand() % 8;

    switch (Event)
    {
    case TOURISM_BOOM:

        printf("\n\nTourism Boom");
        printf("\n------------");

        printf("\nHotels receive double rent");
        printf("\nSouthern coastal properties (+15%%)");

        for (int i = 0; i < SQUARES; i++)
        {
            if (Square[i].Hotel == YES)
            {
                Square[i].CurrentRent = Square[i].CurrentRent * 2;
            }

            if (Square[i].SquareID == Gallefort || Square[i].SquareID == Unawatuna || Square[i].SquareID == Hikkaduwa)
            {
                Square[i].PurchasePrice = Square[i].PurchasePrice * 115 / 100;
            }
        }

        break;

    case FUEL_CRISIS:

        printf("\n\nFuel Crisis");
        printf("\n-----------");

        printf("\nRailway rent doubles");
        printf("\nProperty development costs increase by 20%%");

        for (int i = 0; i < SQUARES; i++)
        {
            if (Square[i].GroupType == RAILWAY)
            {
                Square[i].CurrentRent =
                    Square[i].CurrentRent * 2;
            }

            if (Square[i].GroupType == PROPERTY)
            {
                Square[i].CurrentPriceOfHouse =
                    Square[i].CurrentPriceOfHouse * 120 / 100;

                Square[i].CurrentPriceOfHotel =
                    Square[i].CurrentPriceOfHotel * 120 / 100;
            }
        }

        break;

    case HEAVY_MONSOON:

        printf("\n\nHeavy Monsoon");
        printf("\n-------------");

        printf("\nFlood risk increases");
        printf("\nInsurance premiums increase");
        printf("\nCoastal properties lose 10%% value");

        for (int i = 0; i < SQUARES; i++)
        {
            if (Square[i].SquareID == Gallefort || Square[i].SquareID == Unawatuna || Square[i].SquareID == Hikkaduwa)
            {
                Square[i].PurchasePrice =
                    Square[i].PurchasePrice * 90 / 100;
            }
        }

        // insurance price eka wadi krnna mathaka athuwa-----------------------------

        break;

    case ECONOMIC_RECESSION:

        printf("\n\nEconomic Recession");
        printf("\n------------------");

        printf("\nProperty values decrease by 15%%");
        printf("\nRent decreases by 10%%");
        printf("\nLoan interest increases by 15%%");

        for (int i = 0; i < SQUARES; i++)
        {
            if (Square[i].GroupType == PROPERTY)
            {
                Square[i].PurchasePrice = Square[i].PurchasePrice * 85 / 100;

                Square[i].CurrentRent = Square[i].CurrentRent * 90 / 100;
            }
        }

        for (int i = 0; i < PLAYERS; i++)
        {
            Player[i].LoanInterest = Player[i].LoanInterest * 115 / 100;
        }

        break;

    case STOCK_MARKET_BOOM:

        printf("\n\nStock Market Boom");
        printf("\n-----------------");

        printf("\nProperty values increase by 10%%");
        printf("\nLoan interest decreases by 10%%");

        for (int i = 0; i < SQUARES; i++)
        {
            if (Square[i].GroupType == PROPERTY)
            {
                Square[i].PurchasePrice = Square[i].PurchasePrice * 110 / 100;
            }
        }

        for (int i = 0; i < PLAYERS; i++)
        {
            Player[i].LoanInterest = Player[i].LoanInterest * 90 / 100;
        }

        break;

    case GOVERNMENT_HOUSING_PROGRAMME:

        printf("\n\nGovernment Housing Programme");
        printf("\n----------------------------");

        printf("\nHouse construction costs reduce by 25%%");

        for (int i = 0; i < SQUARES; i++)
        {
            if (Square[i].GroupType == PROPERTY)
            {
                Square[i].CurrentPriceOfHouse = Square[i].CurrentPriceOfHouse * 75 / 100;
            }
        }

        break;

    case FOREIGN_INVESTMENT:

        printf("\n\nForeign Investment");
        printf("\n------------------");

        printf("\nCommercial properties increase by 20%%");

        for (int i = 0; i < SQUARES; i++)

        // pettah ,maradana,fort set as comercial properties
        {
            if (Square[i].SquareID == Pettah || Square[i].SquareID == Maradana || Square[i].SquareID == FortRailwayStation)
            {
                Square[i].PurchasePrice = Square[i].PurchasePrice * 120 / 100;
            }
        }

        break;

    case POLITICAL_UNREST:

        printf("\n\nPolitical Unrest");
        printf("\n----------------");

        printf("\nRiot probability doubles");
        printf("\nHotel occupancy decreases");
        printf("\nHotel rent decreases by 50%%");
        printf("\nBusiness interruption claims increase");

        for (int i = 0; i < SQUARES; i++)
        {
            if (Square[i].Hotel == YES)
            {
                Square[i].CurrentRent = Square[i].CurrentRent * 50 / 100;
            }
        }

        //make riot probability double and business interruption claims increase

        break;
    }
}

