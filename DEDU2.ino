#include <Servo.h>
#include <avr/pgmspace.h>
int const NbJeux = 20;
int const NbModes=4;
int const NbGameTypes=5;
//Ordre utilisé pour le mode DÉMO  doit être consécutif de 0 à NbJeux-1.
int const Game_id_PQP=0;
int const Game_id_PQR=1;
int const Game_id_TO=2;
int const Game_id_DQP=3;
int const Game_id_DQP2=4;
int const Game_id_PC=5;
int const Game_id_PC2=6;
int const Game_id_MIN=7;
int const Game_id_UC=8;
int const Game_id_JD=9;
int const Game_id_AR=10;
int const Game_id_MH=11;
int const Game_id_TH=12;
int const Game_id_TV=13;
int const Game_id_PB=14;
int const Game_id_Duel=15;
int const Game_id_PPV=16;
int const Game_id_TDD=17;
int const Game_id_JC=18;
int const Game_id_FFA=19;

//=========================\\
//==         DEDU        ==\\
//=========================\\

//DEBUGGING FLAGS => ALL FALSE FOR NORMAL GAME.
//Comment out the following line too.
//#define ENABLE_LOGGING

//Opt Gen
bool SkipSetup=false;
bool nosound=false;
bool SkipLights=false;

//Opt Game
bool ExclusiveGame=true;
int ExclusiveGame_ID=Game_id_JD;

//Opt Repartiteur
bool SkipFraudeur=false;
bool SkipGame=false;
bool DelayIfSkipGame=false;
bool DoNotShowGameProb=false;

//Opt Mus
bool MusicMode=false;
int SelectMusic=-1;
bool MusicRandFactVit=false;

//SETUP IF SKIPPED:
int nbj=10;
int vitesse=10;
int Game_Mode=3;
//Demo Mode
bool EnterDemo=false;
bool AllModes=false;
int JoueurHonte=-1;
//DEBUG END
//=========================\\

//Prob, Jeux
int NumberOfRoundsForFullProb=4;
int CountJeux[NbJeux]={0};
int CountType[NbGameTypes]={0};
int TotalNbJeux=0;
bool NotMoreThanMaxProb=false;
int GameTypes[NbJeux] ={0};
int GameProb[NbJeux][NbModes]={0};
int ProbIndivJeuxCurrent[NbJeux];
int ProbAccumuleeJeux[NbJeux];
int ProbIndivJeux[NbJeux];
int MinProbAcc=9999;
int MaxProbAcc=0;

#ifdef ENABLE_LOGGING
  bool ActiveGameLogging[NbJeux]={false};
  #define LOG_GAME(i,a) if( ActiveGameLogging[i] ) Serial.print(a);
  #define LOG_GENERAL(a) Serial.print(a);
#else
  #define LOG_GAME(i,a)
  #define LOG_GENERAL(a)
#endif

//Definitions
//Pins
int const myRandPin=0; //To initialize the random function
int const G = 3; //Green LED ALL
int const B = 2; //Blue LED ALL

int Tone_Pin=52;

Servo Servo_BrasDEDU;
//Position à l'arrêt du Servo (bâton rentré)
int const Servo_LowPos = 40;
int const Servo_HighPos = 154;
int const Servo_Pin = 53;

//Pour setup
int const nbj_max=10;
int const nbj_raw_max=9;
int nbj_raw;
int vitesse_raw;

//Pins
int const OutPinStart = 31;
int const OutPinInterval = 2;
int const InPinStart = 24;
int const InPinInterval = 2;
int PlayerInputPins[nbj_max];
int PlayerOutputPins[nbj_max];

//Time variables
unsigned long TimeStart;

int Tone_Frequency;

//Globales.
int InputState[nbj_max]={LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};
int OutputState[nbj_max]={LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};
int Equipes[10];
int NbEquipes;
int NbJoueursEq1;
int NbJoueursEq2;

int const ParamChansons=3;
int const NbNoteMax=42;

int DelaiPetiteHonte=1;
int DelaiHonte=1;

//Pour Chaque chanson:
//0 => Freq
//1 => Temps Actif
//2 => Temps Silence Après
float MaChanson[ParamChansons][NbNoteMax];
float ChansonMod[ParamChansons][NbNoteMax];
//Pour Chaque joueur: Silence,puis Musique.
float LeurTemps[ParamChansons-1][NbNoteMax];
float Scores[2];
int OrdreJoueurs[NbNoteMax];
int RandomMin;
int RandomMax;


////Chansons.
int const NombreChansons=13;
int ChansonPourJeu=0;
int OrdreChansons[NombreChansons]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  const PROGMEM float ChansonDEDU[3][18]={
    {196,196,196,247,247,261,261,349,247,196,196,294,247,196,330,294,247,261},
    {150,150,150,300,300,300,300,600,150,150,150,150,150,150,600,150,150,600},
    {100,200,100,200,200,200,200,200,100,200,100,200,100,400,400,200,100,200},
    };
  const PROGMEM float DeadOrAlive1[3][25]={
    {293,293,293,293,293,293,261,233,261,233,261,233,261,261,233,261,233,261,233,261,293,293,293,174,195},
    {111.4,107.6,130.6,146,117.6,393.5,78.4,149.9,162.9,167.5,169.8,136,311.2,169.8,149.9,142.9,151.4,161.4,135.3,336.6,287.4,289.7,362.7,295.9,427.3},
    {110.8,114.6,91.6,85.5,236.1,132.4,143.8,72.4,59.3,79.7,57.9,76,112.8,71.8,73.3,79.3,81.9,65.5,75.9,114.3,125.5,154.7,100.2,130,87.5},
    };
  const PROGMEM float DeadOrAlive2[3][19]={
    {195,195,195,233,233,174,174,261,233,195,195,293,293,233,233,174,174,261,233},
    {254.2,261.8,248.6,277.8,292.4,105.6,163.9,240.3,300,116,141,125,148.6,133.3,168.7,225,328.5,300.7,424.7},
    {209.7,196.5,162.5,166.7,152.1,116.7,97.2,189.4,120.4,106.2,79.4,99.1,73.6,88.9,97.9,154.6,136.3,127.1,100.9},
    };
  const PROGMEM float FurElise[3][34]={
    {659,622,659,622,659,493,587,523,440,261,329,440,493,329,415,493,523,659,622,659,622,659,493,587,523,440,261,329,440,493,293,523,493,440},
    {106.4,100.8,92.5,92.5,78.5,108.9,125.4,106.4,174.8,114,119.1,121.6,144.4,114,125.4,100.1,184.9,100.1,106.4,88.7,88.7,125.4,129.2,114,115.3,241.9,125.4,114,100.1,241.9,119.1,107.7,111.5,342},
    {83.6,89.2,107.5,107.5,121.5,91.1,74.6,93.6,425.2,86,80.9,78.4,455.6,86,74.6,99.9,615.1,81.6,93.6,111.3,111.3,74.6,70.8,86,84.7,358.1,74.6,86,99.9,358.1,80.9,92.3,88.5,258},
    };
  const PROGMEM float FF6Over[3][33]={
    {415,466,493,622,493,466,415,466,311,415,466,493,622,493,466,415,466,622,493,554,622,739,622,554,493,554,369,493,466,415,493,466,415},
    {134.6,118.6,109.8,125.7,1962.1,127.5,127.5,595,1615,118.6,116.9,125.7,118.6,1962.1,134.6,134.6,628.6,1630.9,134.6,109.8,143.4,127.5,1970.9,127.5,127.5,586.1,1597.3,109.8,134.6,2319.8,109.8,134.6,2295},
    {65.4,81.4,90.2,74.3,437.9,72.5,72.5,205,385,81.4,83.1,74.3,81.4,437.9,65.4,65.4,171.4,369.1,65.4,90.2,56.6,72.5,429.1,72.5,72.5,213.9,402.7,90.2,65.4,480.2,90.2,65.4,530},
    };
  const PROGMEM float Menuet[3][32]={
    {587,391,440,493,523,587,391,391,659,523,587,659,739,783,391,391,523,587,523,493,440,493,523,493,440,391,440,493,440,391,369,391},
    {200.2,75.6,121.6,121.6,113.3,255,141.7,101.5,237.3,122.8,112.2,114.5,114.5,233.7,94.4,103.9,325,65.9,69.7,109.8,120.4,249.1,116.9,109.8,113.3,120.4,260.9,139.3,120.4,125.1,120.4,622.2},
    {155.9,35.6,45.1,45.1,53.3,78.3,191.7,231.8,96,43.9,54.5,52.2,52.2,99.6,238.9,218.4,85.8,50.7,44.2,56.9,46.2,84.2,49.8,56.9,53.3,46.2,72.4,27.4,46.2,41.5,46.2,210.7},
    };
  const PROGMEM float SWTheme[3][19]={
    {349,349,349,466,698,622,587,523,1864,698,622,587,523,1864,698,622,587,622,523},
    {64.8,64.8,64.8,756.5,756.5,82.1,82.1,77.8,791.1,341.5,77.8,77.8,77.8,791.1,376.1,77.8,77.8,77.8,825.7},
    {101.8,101.8,101.8,243.5,243.5,84.5,84.5,88.9,208.9,158.5,88.9,88.9,88.9,208.9,123.9,88.9,88.9,88.9,289.9},
    };
  const PROGMEM float Cantina[3][35]={
    {440,587,440,587,440,587,440,415,440,440,415,440,391,369,391,349,349,293,440,587,440,587,440,587,440,415,440,391,391,369,391,523,466,440,391},
    {79.7,79.7,79.7,79.7,90.8,124,160.5,73,124,75.3,79.7,86.3,124,79.7,75.3,79.7,292.2,467.1,79.7,79.7,79.7,79.7,79.7,124,181.5,75.3,124,79.7,277.8,90.8,124,79.7,185.9,185.9,370.8},
    {170.3,170.3,170.3,170.3,34.2,126,89.5,52,126,49.7,45.3,38.7,126,45.3,49.7,45.3,82.8,157.9,170.3,170.3,170.3,170.3,45.3,126,68.5,49.7,126,170.3,97.2,34.2,126,45.3,64.1,64.1,165.6},
    };
  const PROGMEM float Scatman1[3][36]={
    {523,349,415,349,523,349,415,349,415,523,349,415,349,523,349,415,349,415,466,311,391,311,466,311,391,311,391,466,311,391,311,466,311,391,311,391},
    {87.9,87.9,76.2,87.9,87.9,87.9,87.9,62.5,87.9,87.9,87.9,87.9,87.9,87.9,87.9,87.9,64.5,87.9,87.9,87.9,72.3,87.9,87.9,87.9,87.9,52.7,87.9,87.9,87.9,76.2,87.9,87.9,87.9,87.9,87.9,87.9},
    {132.7,132.7,52.5,132.7,132.7,132.7,132.7,29.4,132.7,132.7,132.7,40.8,132.7,132.7,132.7,132.7,27.5,132.7,132.7,132.7,56.4,132.7,132.7,132.7,132.7,39.2,132.7,132.7,132.7,52.5,132.7,132.7,132.7,132.7,29.3,118.9},
    };
  const PROGMEM float Scatman2[3][26]={
    {349,349,349,349,415,391,415,391,349,261,391,415,391,349,261,415,391,415,391,311,233,391,415,391,311,233},
    {61.8,71.4,61.8,119.7,279.9,83,71.4,86.9,69.5,135.1,94.6,88.8,83,94.6,131.2,301.1,98.4,83,83,88.8,166,102.3,92.6,92.6,92.6,166},
    {55.4,64.2,62.3,61.9,161.3,137.6,149.2,41.8,151.1,839.2,126,131.8,45.7,126,401.8,140.1,122.2,137.6,45.7,131.8,732.4,120.6,127.9,38.3,125.6,132.2},
    };
  const PROGMEM float Boten2[3][40]={
    {277,261,233,233,233,261,277,277,311,277,261,277,261,207,207,277,277,261,277,261,207,233,233,261,349,311,311,277,277,277,261,207,207,277,277,261,233,207,261,233},
    {315,378.4,732.8,87.5,238.4,105,343.4,203.4,330.3,124.7,225.1,135.6,586.2,234.1,94.1,175,317.2,330.3,109.4,175,142.2,470.3,203.4,111.6,328.1,185.9,374.1,310.6,67.8,196.9,417.8,181.6,124.7,98.4,317.2,374.1,94.1,225.3,94.1,496.6},
    {185,132,259.4,81.8,94.9,66.9,156.6,124.7,169.7,104.5,60.3,90.9,773.1,99.3,114.3,160.9,177.6,195.7,59.9,145.3,66.1,821.4,129.9,60.3,171.9,142.2,125.9,189.4,104.1,131.2,748.9,151.8,47.2,229.7,182.8,125.9,72.6,108,114.3,216.7},
    };
  const PROGMEM float ctd1[3][20]={
    {554,493,554,369,587,554,587,554,493,587,554,587,369,493,440,493,440,415,493,440},
    {89.7,89.7,387.7,516.9,89.7,89.7,89.7,89.7,775.4,89.7,89.7,473.8,516.9,89.7,89.7,89.7,89.7,89.7,89.7,775.4},
    {59.8,64.1,227.7,688.2,64.1,64.1,217.9,217.9,763.1,64.1,64.1,141.5,624.1,64.1,64.1,217.9,217.9,217.9,217.9,247.8},
    };
  const PROGMEM float ctd2[3][37]={
    {554,493,554,369,587,554,587,554,493,587,554,587,369,493,440,493,440,415,493,440,415,440,493,440,493,554,493,440,415,369,587,554,554,587,554,493,554},
    {76.6,76.6,494.4,621.2,76.6,76.6,76.6,76.6,748.1,76.6,76.6,498.8,498.8,76.6,76.6,76.6,76.6,76.6,76.6,625.6,76.6,76.6,748.1,76.6,76.6,207.8,192.5,203.4,183.8,492.2,444.1,1375.9,91.9,91.9,91.9,91.9,1400},
    {71.9,74.5,104.6,524.6,74.5,69.3,225.5,225.5,629.5,69.3,74.5,100.2,506.5,74.5,74.5,225.5,220.3,225.5,220.3,275.4,74.5,74.5,152.9,69.3,74.5,94.3,104.4,98.6,118.3,106.8,154.9,426.1,54,59.2,59.2,59.2,235.5},
    };

//One-time setup:
void setup()
{
  int Pin;
  
  #ifdef ENABLE_LOGGING
    Serial.begin(500000);
  #endif

  LOG_GENERAL("==============\n");
  LOG_GENERAL("SETUP STARTING\n");
  LOG_GENERAL("==============\n");
  //TONE
  if (nosound)
  {
    Tone_Pin = 9999;
  }
  else
  {
    Tone_Pin = 52; //Tone
  }
  
  //In case setup was skipped.
  nbj_raw=nbj-1;
  vitesse_raw=vitesse-1;
  
  //Initialize random sequence based on floating value from an unconnected pin.
  randomSeed(analogRead(myRandPin));

  //Attach to servo and move it to initial position
  Servo_BrasDEDU.attach(Servo_Pin);
  Servo_BrasDEDU.write(Servo_LowPos);

  //Pin definitions
  //LED ROUGE des joueurs
  for (int i=0; i<=nbj_raw_max;i++)
  {
    Pin=OutPinStart+OutPinInterval*i;
    pinMode(Pin, OUTPUT);
    PlayerOutputPins[i]=Pin;
  }

  //Toutes lumières G et B
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  //Manettes.
  for (int i=0; i<=nbj_raw_max;i++)
  {
    Pin=InPinStart+InPinInterval*i;
    pinMode(Pin, INPUT);
    PlayerInputPins[i]=Pin;
  }

  DefineGameTypes();
  
  //Ajustement du délai pour Honte
  AjustementDelaiHonte();
  
  if (!SkipSetup && !MusicMode)
  {
    JoueurHonte=-1;
    
    WaitForAllNonActive(nbj_raw_max);
    
    // NBJ - Nombre de Joueurs
    // Attend que les joueurs choisissent le nombre en cliquant sur le bouton correspondant au nombre souhaité.
    // Pour 5 joueurs, cliquer sur la manette #5.  Les lumières de 1 à 5 vont s'allumer et on passe au mode suivant.
    // ----------------------------------------
    NombreJoueurs();
    //TestModeEngage if player = 1
    if (nbj_raw==0)
    {
      TestMode();
    }
    
    //Debut VITESSE
    // Attend que les joueurs choisissent la vitesse du jeu.
    // 1 = lent, 10 = vite
    Vitesse();
    
    //Choix de complexité du jeu.
    GameMode();
  }
  LogSetupParams();

  AdjustNumRoundsFullProb();
  
  DefineProbJeux();
  //Ajustement initial des prob pour les jeux.  Quelques cas spéciaux.
  AjustementProbJeuxInit();

  if(EnterDemo)
  {
    DemoMode(AllModes);
    //Reset joueurhonte après la démo.
    JoueurHonte=-1;
  }
  else if(!SkipSetup)
  {
    //Toune de DEDU pour initialiser la chose.
    JoueChanson(0,3,false);
  }
  
  LOG_GENERAL("==============\n");
  LOG_GENERAL("  SETUP END   \n");
  LOG_GENERAL("==============\n");
  
}

//Setup complete.  MAIN loop.
void loop() 
{
  int r;
  
  //Special exclusivegamemode loop
  if(ExclusiveGame)
  {
    LOG_GENERAL("\n");
    LOG_GENERAL("EXCLUSIVE MODE");
    LOG_GENERAL("\n");
    #ifdef ENABLE_LOGGING
      ActiveGameLogging[ExclusiveGame_ID]=true;
    #endif
    PlayGame(ExclusiveGame_ID);
    loop();
  }

  //Special MusicModeLoop
  if(MusicMode)
  {
    LOG_GENERAL("\n");
    LOG_GENERAL("MUSIC MODE");
    LOG_GENERAL("\n");
    if (SelectMusic==-1)
    {
      LOG_GENERAL("Random Song:");
      r = random(NombreChansons);
    }
    else
    {
      LOG_GENERAL("Selected Song:");
      r=SelectMusic;
    }
    LOG_GENERAL(r);
    LOG_GENERAL("\n");
    JoueChanson(r, 1, MusicRandFactVit);
    delay(2500);
    loop();
  }
  
  //Normal loop starts here.
  WaitForAllNonActive(nbj_raw);

  TurnOffAllLights();
  
  if (!SkipFraudeur)
  {
    //FacteurVitesse
    r = random(25,50) + (11 - vitesse) * random(100);
    Delay_Fraudeur(r);
  }
  
  TurnOffAllLights();
  
  Repartiteur();
}





