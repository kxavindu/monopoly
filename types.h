#ifndef TYPES_H
#define TYPES_H



//game

#define PLAYERS 4
int RollDice();  
void GameStart();

typedef enum {
    AggressiveInvester,
    ConservativeBanker,
    RiskTaker,
    OppertunisticTrader
} PlayerName;


//prints

void MSG1();




typedef enum {
    GO,
    Pettah,
    CommunityDevelopmentFund,
    Maradana,
    IncomeTax,
    FortRailwayStation,
    Bambalapitiya,
    NationalEventCard1,
    Wellawatta,
    MountLavinia,
    Jail,
    Nugegoda,
    CeylonElectricityBoard,
    Maharagama,
    Kottawa,
    KandyRailwayStation,
    Negombo,
    SriLankaInsurance,
    Katunayake,
    JaEla,
    Freeparking,
    KandyCity,
    NationalEventCard2,
    Peradenya,
    Katugastota,
    GalleRailwayStation,
    Gallefort,
    Unawatuna,
    NationalWaterSupplyAndDrainageBoard,
    Hikkaduwa,
    GoToJail,
    JaffnaTown,
    Nallur,
    CeylincoInsurance,
    Trincomalee,
    JaffnaRailwayStation,
    NationalEventCard3,
    NuwaraEliya,
    BankOfCeylon,
    GalleFace


} SQ;



//board 
char SQUARES_NAME[40][50];

//players
char PLAYER_NAME[4][50];



#endif 
