#ifndef TYPES_H
#define TYPES_H
#define MAX_ROUND 100
#define PLAYERS 4
#define SQUARES 40
#define GO_MONEY 2000
#define YES 1
#define NO 0
#define MIN_RENT_RESERVE 200
#define NO_MARKET 0
#define MARKET_BOOM 1
#define MARKET_DECLINE 2

//------------------------------------------------------------ENUMS--------------------------------------------------------------
typedef enum
{
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
    FreeParking,
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

typedef enum
{
    AggressiveInvester,
    ConservativeBanker,
    RiskTaker,
    OppertunisticTrader
} PlayerName;

typedef enum
{
    GO_SQUARE,
    PROPERTY,
    RAILWAY,
    UTILITY,
    TAX,
    JAIL,
    GO_TO_JAIL,
    FREE_PARKING,
    NATIONAL_EVENT,
    COMMUNITY_FUND,
    INSURANCE,
    BANK
} SquareGroupType;

typedef enum
{
    NONE,
    BROWN,
    LIGHT_BLUE,
    PINK,
    ORANGE,
    RED,
    YELLOW,
    GREEN,
    DARK_BLUE
} PropertyGroup;

typedef enum
{
    TOURISM_BOOM,
    FUEL_CRISIS,
    HEAVY_MONSOON,
    ECONOMIC_RECESSION,
    STOCK_MARKET_BOOM,
    GOVERNMENT_HOUSING_PROGRAMME,
    FOREIGN_INVESTMENT,
    POLITICAL_UNREST
} EconomicEvent;

typedef enum
{
    NO_INSURANCE,
    BASIC_INSURANCE,
    COMPREHENSIVE_INSURANCE,
    BUSINESS_INTERRUPTION_INSURANCE
} InsuranceType;

typedef enum
{
    NO_INSURANCE_COMPANY,
    SRI_LANKA_INSURANCE,
    CEYLINCO_INSURANCE
} InsuranceCompany;

//------------------------------------------------------------STRUCTURES--------------------------------------------------------------
typedef struct
{
    // Player Information
    int PlayerID;

    // Board
    int Position;
    int Tie; // if tie 1 , else 0
    int CurrentDiceRoll;
    int PlayerRound;

    // Money
    int Cash;
    int NetWorth;

    // Status
    int Bankrupt; // 0 = No, 1 = Yes
    int InJail;   // 0 = No, 1 = Yes
    int JailTurns;

    // Loans
    int LoanAmount;
    int LoanInterest;
    int LoanRounds;
    // Insurance
    int InsuranceType; // 0=None,1=Basic,2=Comprehensive,3=Business
    int InsuranceRounds;

    // owns
    int RailwayStationsOwned;
    int UtilitiesOwned;
    int PropertiesOwned; // Array to track the number of properties owned in each color group
    int HotelsOwned;

} PlayerType;

typedef struct
{
    SQ SquareID;

    SquareGroupType GroupType;
    PropertyGroup Group;

    // Property Information
    int Owner; // -1 = Unowned
    int PurchasePrice;
    int BaseRent;
    int CurrentRent;

    // Buildings
    int Houses;
    int Hotel;
    int PriceOfHouse;
    int PriceOfHotel;
    int CurrentPriceOfHouse;
    int CurrentPriceOfHotel;

    // Mortgage
    int Mortgaged;

    // Assignment Features
    int PropertyAge;
    int PropertyCondition;

    int MarketType;
    int MarketRounds;

    // insurance---
    int InsuranceActive;
    int InsuranceType;
    int InsuranceCompany;
    int InsuranceExpireRound;

} SquareType;

typedef struct
{
    int TourismBoom;
    int FuelCrisis;
    int HeavyMonsoon;
    int EconomicRecession;
    int StockMarketBoom;
    int GovernmentHousingProgramme;
    int ForeignInvestment;
    int PoliticalUnrest;

} EconomicEventType;

//------------------------------------------------------------FUNCTION PROTOTYPES--------------------------------------------------------------

//--------------------GAME--------------------
int RollDice();
void GameStart();
void GameRoundCal(PlayerType Player[], int *GameRound, int CurrentPlayer, SquareType Square[], EconomicEventType EconomicEvent);

void StartingPlayer(int PlayerSequence[]);

// board
extern char SQUARES_NAME[40][50];

// players

extern char PLAYER_NAME[4][50];

void InitializePlayers(PlayerType player[], int PlayerSequence[]);
void InitializeSquares(SquareType Square[]);
void MovePlayer(PlayerType Player[], SquareType Square[], int *GameRound, EconomicEventType EconomicEvent);

void ProcessSquare(PlayerType Player[], SquareType Square[], int CurrentPlayer , int GameRound);
void HandleGoToJail(PlayerType Player[], int CurrentPlayer);
int ShouldPayJailFine(PlayerType Player[], int CurrentPlayer);

void HandleProperty(PlayerType Player[], SquareType Square[], int CurrentPlayer);

int ShouldBuyProperty(PlayerType Player[], SquareType Square[], int CurrentPlayer);

void RentProperty(PlayerType Player[], SquareType Square[], int CurrentPlayer);
void BuyProperty(PlayerType Player[], SquareType Square[], int CurrentPlayer);

void HandleRailway(PlayerType Player[], SquareType Square[], int CurrentPlayer);
int ShouldBuyRailway(PlayerType Player[], SquareType Square[], int CurrentPlayer);
void BuyRailway(PlayerType Player[], SquareType Square[], int CurrentPlayer);
void RentRailway(PlayerType Player[], SquareType Square[], int CurrentPlayer);

void HandleUtility(PlayerType Player[], SquareType Square[], int CurrentPlayer);
int ShouldBuyUtility(PlayerType Player[], SquareType Square[], int CurrentPlayer);
void BuyUtility(PlayerType Player[], SquareType Square[], int CurrentPlayer);
void RentUtility(PlayerType Player[], SquareType Square[], int CurrentPlayer);

void StartAuction(PlayerType Player[], SquareType Square[], int CurrentPlayer);
int ShouldBid(PlayerType Player[], SquareType Square[], int CurrentPlayer, int CurrentBid);

void HandleTax(PlayerType Player[], SquareType Square[], int CurrentPlayer);
void PayTax(PlayerType Player[], SquareType Square[], int CurrentPlayer);

//--------------------BUILDING / MONOPOLY--------------------

void MonopolyFinder(SquareType Square[], int CurrentPlayer, int Monopoly[]);

void HandleEndTurnActions(PlayerType Player[], SquareType Square[], int CurrentPlayer);
void HandleBuildHouses(PlayerType Player[], SquareType Square[], int CurrentPlayer);
void ShouldBuildHouse(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Monopoly[]);
void BuildHouse(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Property);

//---------------------hotels------------------------------------------

void HandleBuildHotels(PlayerType Player[], SquareType Square[], int CurrentPlayer);
void BuildHotel(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Property);
void HandleBuildHotels(PlayerType Player[], SquareType Square[], int CurrentPlayer);
void ShouldBuildHotel(PlayerType Player[], SquareType Square[], int CurrentPlayer, int Monopoly[]);

//--------------------EVENTS--------------------

int GenerateInflation();

void HandleRoundEvents(PlayerType Player[], SquareType Square[], int GameRound, EconomicEventType EconomicEvent);

void HandleInflation(SquareType Square[]);
void HandleEconomicEvent(PlayerType Player[], SquareType Square[], EconomicEventType EconomicEvent);



//---------------------insurance -------------=

void HandleInsurance(PlayerType Player[], SquareType Square[],
                     int CurrentPlayer, int GameRound);

int ShouldBuyInsurance(PlayerType Player[], SquareType Square[],
                       int CurrentPlayer, int Property);

void BuyBasicInsurance(PlayerType Player[], SquareType Square[],
                       int CurrentPlayer, int Property, int GameRound);

void BuyComprehensiveInsurance(PlayerType Player[], SquareType Square[],
                               int CurrentPlayer, int Property, int GameRound);

void BuyBusinessInterruptionInsurance(PlayerType Player[], SquareType Square[],
                                      int CurrentPlayer, int Property,
                                      int GameRound);

int ShouldRenewInsurance(PlayerType Player[], SquareType Square[],
                       int CurrentPlayer, int Property, int GameRound);

void RenewBasicInsurance(PlayerType Player[], SquareType Square[],
                       int CurrentPlayer, int Property, int GameRound);

void RenewComprehensiveInsurance(PlayerType Player[], SquareType Square[],
                               int CurrentPlayer, int Property, int GameRound);

void RenewBusinessInterruptionInsurance(PlayerType Player[], SquareType Square[],
                                      int CurrentPlayer, int Property,
                                      int GameRound);


void CheckInsuranceExpiry(SquareType Square[], int GameRound);


#endif
