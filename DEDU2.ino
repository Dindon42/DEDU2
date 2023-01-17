//
//            _____                    _____                    _____                    _____          
//           /\    \                  /\    \                  /\    \                  /\    \         
//          /::\    \                /::\    \                /::\    \                /::\____\        
//         /::::\    \              /::::\    \              /::::\    \              /:::/    /        
//        /::::::\    \            /::::::\    \            /::::::\    \            /:::/    /         
//       /:::/\:::\    \          /:::/\:::\    \          /:::/\:::\    \          /:::/    /          
//      /:::/  \:::\    \        /:::/__\:::\    \        /:::/  \:::\    \        /:::/    /           
//     /:::/    \:::\    \      /::::\   \:::\    \      /:::/    \:::\    \      /:::/    /            
//    /:::/    / \:::\    \    /::::::\   \:::\    \    /:::/    / \:::\    \    /:::/    /      _____  
//   /:::/    /   \:::\ ___\  /:::/\:::\   \:::\    \  /:::/    /   \:::\ ___\  /:::/____/      /\    \ 
//  /:::/____/     \:::|    |/:::/__\:::\   \:::\____\/:::/____/     \:::|    ||:::|    /      /::\____\
//  \:::\    \     /:::|____|\:::\   \:::\   \::/    /\:::\    \     /:::|____||:::|____\     /:::/    /
//   \:::\    \   /:::/    /  \:::\   \:::\   \/____/  \:::\    \   /:::/    /  \:::\    \   /:::/    / 
//    \:::\    \ /:::/    /    \:::\   \:::\    \       \:::\    \ /:::/    /    \:::\    \ /:::/    /  
//     \:::\    /:::/    /      \:::\   \:::\____\       \:::\    /:::/    /      \:::\    /:::/    /   
//      \:::\  /:::/    /        \:::\   \::/    /        \:::\  /:::/    /        \:::\__/:::/    /    
//       \:::\/:::/    /          \:::\   \/____/          \:::\/:::/    /          \::::::::/    /     
//        \::::::/    /            \:::\    \               \::::::/    /            \::::::/    /      
//         \::::/    /              \:::\____\               \::::/    /              \::::/    /       
//          \::/____/                \::/    /                \::/____/                \::/____/        
//           ~~                       \/____/                  ~~                       ~~              
//
//  Dispositif Électronique de Distribution Universelle (DEDU)
//  Idée originale:  Éric Geoffroy (2012)
//  Nouvelles idées: Vincent Labrèche (2017+)


//===================================================================================================================\\
//===================================================================================================================\\
//===================================            DEFINES AND VARIABLES            ===================================\\
//===================================================================================================================\\
//===================================================================================================================\\


//===============\\
//GLOBAL INCLUDES\\
//===============\\

#include <Servo.h>
#include <avr/pgmspace.h>

//===================\\
//END GLOBAL INCLUDES\\
//===================\\


//============\\
//GAME DEFINES\\
//============\\

//GAME MODES
#define NbModes 5
#define Game_Mode_Original 0
#define Game_Mode_Medium 1
#define Game_Mode_Avance 2
#define Game_Mode_Expert 3
#define Game_Mode_Experimental 4

//GAME TYPES
#define NbGameTypes 5
#define Game_Type_GI 0    //Gagnant individuel
#define Game_Type_PI 1    //Perdant individuel
#define Game_Type_EQ 2    //Équipe
#define Game_Type_AU 3    //Autres
#define Game_Type_HO 4    //Honte
#define Game_Type_PIH 51  //Perdant individuel et honte
#define Game_Type_EQH 52  //Équipe et honte

#define MAX_GAMETYPE_ROI Game_Type_EQ  //Le roi peut choisir jusqu'aux jeux d'équipe: GI, PI ou EQ.

//GAME ID
#define NbJeux 26
//Ordre utilisé pour le mode DÉMO  doit être consécutif de 0 à NbJeux-1.
#define Game_id_PQP 0    //Premier Qui Pèse
#define Game_id_PQR 1    //Premier Qui Relâche
#define Game_id_TO 2     //Trompe Oeil
#define Game_id_DQP 3    //Dernier Qui Pèse
#define Game_id_DQP2 4   //Dernier Qui Pèse 2 (Flash)
#define Game_id_PC 5     //Patate Chaude
#define Game_id_PC2 6    //Patate Chaude 2 (Double Patate)
#define Game_id_MIN 7    //Minorité
#define Game_id_UC 8     //Ultimate Challenge
#define Game_id_JD 9     //Jean Dit
#define Game_id_ED 10    //Estime DEDU
#define Game_id_AR 11    //All Random
#define Game_id_MH 12    //Marqueur Honte
#define Game_id_TH 13    //Tourniquet de la Honte
#define Game_id_TV 14    //Tourniquet de la Victoire
#define Game_id_PB 15    //Press Battle
#define Game_id_DUEL 16  //Duel individuel
#define Game_id_PPV 17   //Pèse Plus Vite
#define Game_id_TDD 18   //Team DeDuel
#define Game_id_JC 19    //Jeu Chanson
#define Game_id_SEQ 20   //Séquence Globale
#define Game_id_TB 21    //The Button
#define Game_id_AR2 22   //All Random 2
#define Game_id_MIN2 23  //Minorité 2
#define Game_id_ROI 24   //Roi
#define Game_id_DEDU 25  //DEDU: Toujours le dernier jeu.

//================\\
//END GAME DEFINES\\
//================\\


//===================================\\
//===      DEBUGGING FLAGS        ===\\
//===================================\\
//===  ALL FALSE FOR NORMAL GAME  ===\\
//=== USE TO FACILITATE DEBUGGING ===\\
//===================================\\

//Remove comment on following line to enable logging (DEBUG only... Slows down the game).
//#define ENABLE_LOGGING

//Opt Generales
#define SkipSetup false
#define NoSound false
#define SkipLights false

//Opt Exclusive Game
#define ExclusiveGame false
#define ExclusiveGame_ID Game_id_ROI
#define ExclusiveGame_DemoMode false
#define ExclusiveGameDelay 0

//Opt Repartiteur
bool ExclusiveGameType=false;
int ExclusiveGameType_ID=Game_Type_GI;
#define OverrideGameTypeFromFraudeur false
#define SkipFraudeur false
#define SkipGame false
#define DelayIfSkipGame false
#define DoNotShowGameProb false

//Opt Musique
#define MusicMode false
#define MusicModeLumiere false
#define SelectedSong 6  //Set to -1 for random songs.
#define MusicRandFactVit false

//SETUP IF SKIPPED:
int nbj=10;
int vitesse=10;
int Game_Mode=Game_Mode_Experimental;
//Demo Mode
bool EnterDemo=false;
bool AllModes=false;
int JoueurHonte=-1;
int JoueurPuissant=-1;
int JoueurRoi=-1;

//=============================\\
//===  END DEBUGGING FLAGS  ===\\
//=============================\\


//=============================\\
//===     PROBS / JEUX      ===\\
//=============================\\

#define MinRoundsRoi 3
#define Score_Min_JoueurPuissant 3
int NumberOfRoundsForFullProb=4;
int CountJeux[NbJeux]={0};
int CountType[NbGameTypes]={0};
int TotalNbJeux=0;
bool NotMoreThanMaxProb=false;
int GameTypes[NbJeux]={0};
int GameProb[NbJeux][NbModes]={0};
int ProbIndivJeuxCurrent[NbJeux];
int ProbAccumuleeJeux[NbJeux];
int ProbIndivJeux[NbJeux];
int MinProbAcc=9999;
int MaxProbAcc=0;

//=============================\\
//===   END PROBS / JEUX    ===\\
//=============================\\


//===========================\\
//===   LOGGING ROUTINE   ===\\
//===========================\\

//Activate logging only if ENABLE_LOGGING defined above 
#ifdef ENABLE_LOGGING
  bool ActiveGameLogging[NbJeux]={false};
  #define LOG_GAME(i,a) if (ActiveGameLogging[i]) Serial.print(a);
  #define LOG_GENERAL(a) Serial.print(a);
#else
  #define LOG_GAME(i,a)
  #define LOG_GENERAL(a)
#endif
//=============================\\
//===  END LOGGING ROUTINE  ===\\
//=============================\\


//=========================\\
//===  PIN / SERVO DEF  ===\\
//=========================\\

#define RandomSeedPin 0 //Read from this pin (unconnected) to initialize the random function.
#define G 3 //GREEN LED - One PWM (Pulse With Modulation) pin for all 10 LED (allows variable output)
#define B 2 //BLUE  LED - One PWM (Pulse With Modulation) pin for all 10 LED (allows variable output)

//Player Pins
int PlayerInputPins[nbj_max]; //Manettes
int PlayerOutputPins[nbj_max]; //RED LED

//Sound Buzzer
int Tone_Pin=52;

//Servo DEDU Flag
Servo Servo_BrasDEDU;
#define Servo_Pin 53
#define Servo_LowPos 40 //Position à l'arrêt du Servo (bâton rentré)
#define Servo_HighPos 154 //Position haute (90 deg)

//=============================\\
//===  END PIN / SERVO DEF  ===\\
//=============================\\


//===============\\
//===  SETUP  ===\\
//===============\\

//Nombre de Joueurs
#define nbj_max 10
#define nbj_raw_max 9
int nbj_raw;

//Vitesse
int vitesse_raw;

//===================\\
//===  END SETUP  ===\\
//===================\\


//================\\
//===   MISC   ===\\
//================\\

//Time variables
unsigned long TimeStart;

//IO
bool InputState[nbj_max]={false};
bool OutputState[nbj_max]={false};

//Équipes
int Equipes[16];
int NbEquipes;
int NbJoueursEq1;
int NbJoueursEq2;

//Score
int GlobalScore[nbj_max]={0};

//Music
int Tone_Frequency;
int const ParamChansons=3;
int const NbNoteMax=50;
int OrdreJoueurs[NbNoteMax];

//Honte
#define DelaiPetiteHonte 90 - nbj * 5
#define DelaiHonte 160 - nbj * 7

//====================\\
//===   END MISC   ===\\
//====================\\


//===================\\
//===   MUSIQUE   ===\\
//===================\\

#define NombreChansons 11 //Pour jeux.  
int OrdreChansons[NombreChansons]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int ChansonFacteurRandomMin;
int ChansonFacteurRandomMax;
int ChansonPourJeu=0;
#define CHANSON_FinalCtd1ID 1
#define CHANSON_FinalCtd2ID 2
#define CHANSON_FF3Win 12
#define CHANSON_CAN 13

//Array chanson active
float MaChanson[ParamChansons][NbNoteMax];

//Pour Chaque chanson:
//Array 0 => Frequence de la note
//Array 1 => Durée de la note
//Array 2 => Temps de silence après la note
const PROGMEM float CAN[3][10] = {
    {392,466.2,466.2,311.1,349.2,392,415.3,466.2,523.3,349.2},
    {1979.2,1458.3,479.2,2916.7,979.2,979.2,979.2,979.2,979.2,2000},
    {20.8,50.7,20.8,83.3,20.8,20.8,20.8,20.8,20.8,0}
    };
const PROGMEM float FF3Win[3][9] = {
    {293.7,293.7,293.7,293.7,233.1,261.6,293.7,261.6,293.7},
    {150,166.7,166.7,1000,958.3,958.3,225,316.7,3000},
    {166.7,166.7,166.7,0,41.7,41.7,441.7,16.7,0}
    };
const PROGMEM float Figaro[3][46] = {
    {207.7,246.9,233.1,185,207.7,246.9,233.1,185,207.7,246.9,233.1,185,207.7,246.9,277.2,246.9,277.2,246.9,185,207.7,370,329.6,311.1,277.2,311.1,370,207.7,246.9,233.1,185,207.7,246.9,233.1,185,207.7,246.9,233.1,185,207.7,246.9,277.2,246.9,277.2,311.1,246.9,277.2},
    {885.4,885.4,1406.2,250,442.7,442.7,442.7,442.7,500,442.7,442.7,125,125,161.5,750,442.7,442.7,937.5,937.5,937.5,468.7,468.7,468.7,468.7,468.7,468.7,937.5,911.5,1432.3,250,442.7,442.7,442.7,442.7,442.7,442.7,442.7,125,125,166.7,937.5,442.7,442.7,963.5,963.5,2687.5},
    {114.6,114.6,93.7,250,57.3,57.3,57.3,20.8,36.5,57.3,67.7,62.5,41.7,67.7,250,52.1,62.5,57.3,67.7,62.5,31.2,31.2,31.2,31.2,31.2,31.2,62.5,88.5,67.7,250,57.3,57.3,57.3,57.3,57.3,72.9,57.3,41.7,41.7,57.3,62.5,57.3,62.5,31.2,36.5,0}
    };
const PROGMEM float ChansonDEDU[3][18]={
  {196,196,196,247,247,261,261,349,247,196,196,294,247,196,330,294,247,261},
  {150,150,150,300,300,300,300,600,150,150,150,150,150,150,600,150,150,600},
  {100,200,100,200,200,200,200,200,100,200,100,200,100,400,400,200,100,200}
  };
const PROGMEM float FurElise[3][34]={
  {659,622,659,622,659,493,587,523,440,261,329,440,493,329,415,493,523,659,622,659,622,659,493,587,523,440,261,329,440,493,293,523,493,440},
  {106.4,100.8,92.5,92.5,78.5,108.9,125.4,106.4,174.8,114,119.1,121.6,144.4,114,125.4,100.1,184.9,100.1,106.4,88.7,88.7,125.4,129.2,114,115.3,241.9,125.4,114,100.1,241.9,119.1,107.7,111.5,342},
  {83.6,89.2,107.5,107.5,121.5,91.1,74.6,93.6,425.2,86,80.9,78.4,455.6,86,74.6,99.9,615.1,81.6,93.6,111.3,111.3,74.6,70.8,86,84.7,358.1,74.6,86,99.9,358.1,80.9,92.3,88.5,258}
  };
const PROGMEM float FF6Over[3][33]={
  {415,466,493,622,493,466,415,466,311,415,466,493,622,493,466,415,466,622,493,554,622,739,622,554,493,554,369,493,466,415,493,466,415},
  {134.6,118.6,109.8,125.7,1962.1,127.5,127.5,595,1615,118.6,116.9,125.7,118.6,1962.1,134.6,134.6,628.6,1630.9,134.6,109.8,143.4,127.5,1970.9,127.5,127.5,586.1,1597.3,109.8,134.6,2319.8,109.8,134.6,2295},
  {65.4,81.4,90.2,74.3,437.9,72.5,72.5,205,385,81.4,83.1,74.3,81.4,437.9,65.4,65.4,171.4,369.1,65.4,90.2,56.6,72.5,429.1,72.5,72.5,213.9,402.7,90.2,65.4,480.2,90.2,65.4,530}
  };
const PROGMEM float Menuet[3][32]={
  {587,391,440,493,523,587,391,391,659,523,587,659,739,783,391,391,523,587,523,493,440,493,523,493,440,391,440,493,440,391,369,391},
  {200.2,75.6,121.6,121.6,113.3,255,141.7,101.5,237.3,122.8,112.2,114.5,114.5,233.7,94.4,103.9,325,65.9,69.7,109.8,120.4,249.1,116.9,109.8,113.3,120.4,260.9,139.3,120.4,125.1,120.4,622.2},
  {155.9,35.6,45.1,45.1,53.3,78.3,191.7,231.8,96,43.9,54.5,52.2,52.2,99.6,238.9,218.4,85.8,50.7,44.2,56.9,46.2,84.2,49.8,56.9,53.3,46.2,72.4,27.4,46.2,41.5,46.2,210.7}
  };
const PROGMEM float SWTheme[3][19]={
  {349,349,349,466,698,622,587,523,932,698,622,587,523,932,698,622,587,622,523},
  {64.8,64.8,64.8,756.5,756.5,82.1,82.1,77.8,791.1,341.5,77.8,77.8,77.8,791.1,376.1,77.8,77.8,77.8,825.7},
  {101.8,101.8,101.8,243.5,243.5,84.5,84.5,88.9,208.9,158.5,88.9,88.9,88.9,208.9,123.9,88.9,88.9,88.9,289.9}
  };
const PROGMEM float Cantina[3][35]={
  {440,587,440,587,440,587,440,415,440,440,415,440,391,369,391,349,349,293,440,587,440,587,440,587,440,415,440,391,391,369,391,523,466,440,391},
  {79.7,79.7,79.7,79.7,90.8,124,160.5,73,124,75.3,79.7,86.3,124,79.7,75.3,79.7,292.2,467.1,79.7,79.7,79.7,79.7,79.7,124,181.5,75.3,124,79.7,277.8,90.8,124,79.7,185.9,185.9,370.8},
  {170.3,170.3,170.3,170.3,34.2,126,89.5,52,126,49.7,45.3,38.7,126,45.3,49.7,45.3,82.8,157.9,170.3,170.3,170.3,170.3,45.3,126,68.5,49.7,126,170.3,97.2,34.2,126,45.3,64.1,64.1,165.6}
  };
const PROGMEM float Scatman2[3][26]={
  {349,349,349,349,415,391,415,391,349,261,391,415,391,349,261,415,391,415,391,311,233,391,415,391,311,233},
  {61.8,71.4,61.8,119.7,279.9,83,71.4,86.9,69.5,135.1,94.6,88.8,83,94.6,131.2,301.1,98.4,83,83,88.8,166,102.3,92.6,92.6,92.6,166},
  {55.4,64.2,62.3,61.9,161.3,137.6,149.2,41.8,151.1,839.2,126,131.8,45.7,126,401.8,140.1,122.2,137.6,45.7,131.8,732.4,120.6,127.9,38.3,125.6,132.2}
  };
const PROGMEM float Boten2[3][40]={
  {277,261,233,233,233,261,277,277,311,277,261,277,261,207,207,277,277,261,277,261,207,233,233,261,349,311,311,277,277,277,261,207,207,277,277,261,233,207,261,233},
  {315,378.4,732.8,87.5,238.4,105,343.4,203.4,330.3,124.7,225.1,135.6,586.2,234.1,94.1,175,317.2,330.3,109.4,175,142.2,470.3,203.4,111.6,328.1,185.9,374.1,310.6,67.8,196.9,417.8,181.6,124.7,98.4,317.2,374.1,94.1,225.3,94.1,496.6},
  {185,132,259.4,81.8,94.9,66.9,156.6,124.7,169.7,104.5,60.3,90.9,773.1,99.3,114.3,160.9,177.6,195.7,59.9,145.3,66.1,821.4,129.9,60.3,171.9,142.2,125.9,189.4,104.1,131.2,748.9,151.8,47.2,229.7,182.8,125.9,72.6,108,114.3,216.7}
  };
const PROGMEM float ctd1[3][20]={
  {554,493,554,369,587,554,587,554,493,587,554,587,369,493,440,493,440,415,493,440},
  {89.7,89.7,387.7,516.9,89.7,89.7,89.7,89.7,775.4,89.7,89.7,473.8,516.9,89.7,89.7,89.7,89.7,89.7,89.7,775.4},
  {59.8,64.1,227.7,688.2,64.1,64.1,217.9,217.9,763.1,64.1,64.1,141.5,624.1,64.1,64.1,217.9,217.9,217.9,217.9,247.8}
  };
const PROGMEM float ctd2[3][37]={
  {554,493,554,369,587,554,587,554,493,587,554,587,369,493,440,493,440,415,493,440,415,440,493,440,493,554,493,440,415,369,587,554,554,587,554,493,554},
  {76.6,76.6,494.4,621.2,76.6,76.6,76.6,76.6,748.1,76.6,76.6,498.8,498.8,76.6,76.6,76.6,76.6,76.6,76.6,625.6,76.6,76.6,748.1,76.6,76.6,207.8,192.5,203.4,183.8,492.2,444.1,1375.9,91.9,91.9,91.9,91.9,1400},
  {71.9,74.5,104.6,524.6,74.5,69.3,225.5,225.5,629.5,69.3,74.5,100.2,506.5,74.5,74.5,225.5,220.3,225.5,220.3,275.4,74.5,74.5,152.9,69.3,74.5,94.3,104.4,98.6,118.3,106.8,154.9,426.1,54,59.2,59.2,59.2,235.5}
  };
const PROGMEM float Tetris[3][37]={
  {659,493,523,587,523,493,440,440,523,659,587,523,493,523,587,659,523,440,440,587,698,880,783,698,659,523,659,587,523,493,493,523,587,659,523,440,440},
  {385.9,193,193,385.9,193,193,385.9,193,193,385.9,193,193,643.2,193,385.9,385.9,385.9,385.9,900.5,385.9,193,385.9,193,193,643.2,193,385.9,193,193,385.9,193,193,385.9,385.9,385.9,385.9,900.5},
  {216.5,108.2,108.2,216.5,108.2,108.2,216.5,108.2,108.2,216.5,92.6,123.9,260.4,108.2,216.5,216.5,216.5,216.5,605.5,216.5,108.2,216.5,108.2,108.2,260.4,108.2,216.5,108.2,108.2,216.5,108.2,108.2,216.5,216.5,225.9,207.1,222.7}
  };

//=====================\\
//===  END MUSIQUE  ===\\
//=====================\\


//=======================================================================================================================\\
//=======================================================================================================================\\
//===================================            END DEFINES AND VARIABLES            ===================================\\
//=======================================================================================================================\\
//=======================================================================================================================\\




//==============================================================\\
//====================        SETUP        =====================\\
//==============================================================\\
//  This code runs once, when the board is initially connected  \\
//==============================================================\\

void setup()
{
  bool ManualPinDef;  //Special feature: Permet de réassigner les manettes lorsqu'on joue à moins de 10 joueurs.
  
  //Logging
  #ifdef ENABLE_LOGGING
    Serial.begin(500000);
  #endif

  LOG_GENERAL("==============\n");
  LOG_GENERAL("SETUP STARTING\n");
  LOG_GENERAL("==============\n");
  
  //Disable sound if NoSound is set.
  if (NoSound)
  {
    Tone_Pin=9999;
  }
  
  //Set setup parameters in case setup is skipped.
  nbj_raw=nbj-1;
  vitesse_raw=vitesse-1;
  
  //Initialize random sequence based on floating value from an unconnected pin.
  randomSeed(analogRead(RandomSeedPin));

  //Attach to servo and move it to initial position
  Servo_BrasDEDU.attach(Servo_Pin);
  Servo_BrasDEDU.write(Servo_LowPos);

  //Toutes les lumières G et B
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  
  //Définir le type pour chaque jeu.
  DefineGameTypes();
  
  //Définir les pins des joueurs à leur valeur par défaut
  RedefinePlayerPins(true);
  

  //=========================\\
  //======  Main Setup  =====\\
  //=========================\\
  
  if (!SkipSetup && !MusicMode)
  {
    ResetJoueursSpeciaux();

    WaitForAllNonActive(nbj_raw_max);
    
    // NBJ - Nombre de Joueurs
    // Attend que les joueurs choisissent le nombre en cliquant sur le bouton correspondant au nombre souhaité.
    // Pour redéfinir les assignations de manettes, tenir le bouton enfoncé.
    ManualPinDef=NombreJoueurs();
    
    //Entrer en mode test si nbj=1
    if (nbj_raw==0)
    {
      TestMode();
    }
    
    // Vitesse de jeu
    // Attend que les joueurs choisissent la vitesse du jeu.
    // 1=lent, 10=vite, 7 ou 8 sont de bonnes valeurs pour un grand groupe.
    Vitesse();
    
    // Mode de jeu
    // 1 à 5, défini plus haut.
    // 6 à 10, Permet de choisir le mode DEMO (Delta) ou tenir enfoncé (ALL)
    GameMode();

    //Redéfinir les manettes si précédemment sélectionné
    if (ManualPinDef)
    {
      RedefinePlayerPins(false);
    }
  }

  //Définir la probabilité des jeux en fonction du mode sélectionné.
  DefineProbJeux();
  
  //Entrer dans le Mode DEMO si précédemment sélectionné.
  if (EnterDemo)
  {
    //Mode DEMO avec option DELTA (AllModes=false) ou ALL (AllModes=true)
    DemoMode(AllModes);
    
    //Reset joueurs speciaux après la démo.
    ResetJoueursSpeciaux();
  }
  
  //Défini le nombre de jeux nécessaire pour revenir aux probabilités de base.
  AdjustNumRoundsFullProb();
  //Ajustement initial des prob pour les jeux.  Quelques cas spéciaux.
  AjustementProbJeuxInit();

  //Remise à zéro des compteurs.
  for(int i=0; i<nbj_max; i++)
  {
    GlobalScore[i]=0;
  }
  for(int i=0; i<NbJeux; i++)
  {
    CountJeux[i]=0;
  }
  for(int i=0; i<NbGameTypes; i++)
  {
    CountType[i]=0;
  }
  
  //Ça y est, on commence!!
  if (!SkipSetup)
  {
    //Toune de DEDU pour initialiser la chose.
    JoueChanson(0,3,false, true);
  }
  
  //Logging setup params
  LogSetupParams();

  LOG_GENERAL("==============\n");
  LOG_GENERAL("  SETUP END   \n");
  LOG_GENERAL("==============\n");
}

//=================================================================\\
//====================     MAIN GAME LOOP     =====================\\
//=================================================================\\
//  This is where everything happens.  You cannot exit the loop.   \\
//=================================================================\\

void loop() 
{
  //Special Music Mode
  if (MusicMode)
  {
    EndlessMusicMode();
  }
  
  //Special exclusive game loop
  if (ExclusiveGame)
  {
    PlayExclusiveGame();
  }
  
  //====================\\
  //= NORMAL GAME LOOP =\\
  //====================\\
  
  //Fraudeur (délai entre les jeux)
  if (!SkipFraudeur)
  {
    WaitForAllNonActive(nbj_raw);
    TurnOffAllLights();
    Delai_Fraudeur(CalculDelaiFraudeur(true));
    TurnOffAllLights();
  }

  //Répartiteur (choix de jeu)  
  Repartiteur();
}
