#include <Servo.h>
#include <avr/pgmspace.h>
Servo myservo;

//Definitions
//Pins
int const myRandPin=0; //To initialize the random function
int const G = 3; //Green LED ALL
int const B = 2; //Blue LED ALL

//ENLEVER!!!!!!!

int const Tone_Pin = 52; //Tone
//int const Tone_Pin = 52; //Tone

//Position à l'arrêt du Servo (bâton rentré)
int const Servo_LowPos = 40;
int const Servo_HighPos = 154;
int const Servo_Pin = 53;

int const nbj_max=10;
int const nbj_raw_max=9;
int const OutPinStart = 31;
int const OutPinInterval = 2;
int const InPinStart = 24;
int const InPinInterval = 2;


////Chansons.
int const NombreChansons=9;
//float MaChanson[3][100];
  const PROGMEM float ChansonDEDU[3][18] = {
    {196,196,196,247,247,261,261,349,247,196,196,294,247,196,330,294,247,261},
    {150,150,150,300,300,300,300,600,150,150,150,150,150,150,600,150,150,600},
    {100,200,100,200,200,200,200,200,100,200,100,200,100,400,400,200,100,200},
    };
  const PROGMEM float DeadOrAlive1[3][25] = {
    {293,293,293,293,293,293,261,233,261,233,261,233,261,261,233,261,233,261,233,261,293,293,293,174,195},
    {111.4,107.6,130.6,146,117.6,393.5,78.4,149.9,162.9,167.5,169.8,136,311.2,169.8,149.9,142.9,151.4,161.4,135.3,336.6,287.4,289.7,362.7,295.9,427.3},
    {110.8,114.6,91.6,85.5,236.1,132.4,143.8,72.4,59.3,79.7,57.9,76,112.8,71.8,73.3,79.3,81.9,65.5,75.9,114.3,125.5,154.7,100.2,130,87.5},
    };
  const PROGMEM float DeadOrAlive2[3][19] = {
    {195,195,195,233,233,174,174,261,233,195,195,293,293,233,233,174,174,261,233},
    {254.2,261.8,248.6,277.8,292.4,105.6,163.9,240.3,300,116,141,125,148.6,133.3,168.7,225,328.5,300.7,200.7},
    {209.7,196.5,162.5,166.7,152.1,116.7,97.2,189.4,120.4,106.2,79.4,99.1,73.6,88.9,97.9,154.6,136.3,127.1,66.9},
    };
  const PROGMEM float Darude[3][39] = {
    {247,247,247,247,247,247,247,247,247,247,247,247,330,330,330,330,330,330,330,294,294,294,294,294,294,294,220,247,247,247,247,247,247,247,247,247,247,247,247},
    {80,80,80,80,200,80,80,80,80,80,80,200,80,80,80,80,80,80,200,80,80,80,80,80,80,200,200,80,80,80,80,200,80,80,80,80,80,80,200},
    {50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50},
    };
  const PROGMEM float FurElise[3][35] = {
    {659,622,659,622,659,493,587,523,440,261,329,440,493,329,415,493,523,329,659,622,659,622,659,493,587,523,440,261,329,440,493,293,523,493,440},
    {106.4,100.8,92.5,92.5,78.5,108.9,125.4,106.4,174.8,114,119.1,121.6,144.4,114,125.4,100.1,184.9,13.9,100.1,106.4,88.7,88.7,125.4,129.2,114,115.3,241.9,125.4,114,100.1,241.9,119.1,107.7,111.5,342},
    {83.6,89.2,107.5,107.5,121.5,91.1,74.6,93.6,425.2,86,80.9,78.4,455.6,86,74.6,99.9,615.1,4.4,81.6,93.6,111.3,111.3,74.6,70.8,86,84.7,358.1,74.6,86,99.9,358.1,80.9,92.3,88.5,258},
    };
  const PROGMEM float FF6Over[3][33] = {
    {415,466,493,622,493,466,415,466,311,415,466,493,622,493,466,415,466,622,493,554,622,739,622,554,493,554,369,493,466,415,493,466,415},
    {134.6,118.6,109.8,125.7,1962.1,127.5,127.5,595,1615,118.6,116.9,125.7,118.6,1962.1,134.6,134.6,628.6,1630.9,134.6,109.8,143.4,127.5,1970.9,127.5,127.5,586.1,1597.3,109.8,134.6,2319.8,109.8,134.6,2295},
    {65.4,81.4,90.2,74.3,437.9,72.5,72.5,205,385,81.4,83.1,74.3,81.4,437.9,65.4,65.4,171.4,369.1,65.4,90.2,56.6,72.5,429.1,72.5,72.5,213.9,402.7,90.2,65.4,480.2,90.2,65.4,530},
    };
  const PROGMEM float FF6BT[3][18] = {
    {293,329,349,440,523,466,391,466,440,293,391,349,311,293,220,233,261,293},
    {112.7,73.6,73.6,93.6,121.5,93.6,100.8,92,259.9,252.7,259.9,135.9,113.5,728.5,121.5,114.3,113.5,841.2},
    {63.7,102.9,102.9,82.9,54.9,82.9,75.7,84.5,93.1,100.3,93.1,40.5,62.9,153.9,54.9,62.1,62.9,245.7},
    };
  const PROGMEM float Dammit[3][40] = {
    {130,130,146,146,164,97,97,146,146,164,110,110,146,146,164,87,87,164,164,146,130,130,146,146,164,97,97,146,146,164,110,110,146,146,164,87,87,164,164,146},
    {185.8,83.6,185.8,83.6,185.8,185.8,83.6,185.8,83.6,185.8,185.8,83.6,185.8,83.6,185.8,185.8,83.6,185.8,83.6,185.8,185.8,83.6,185.8,83.6,185.8,185.8,83.6,185.8,83.6,185.8,185.8,83.6,185.8,83.6,185.8,185.8,83.6,185.8,83.6,185.8},
    {89.4,54,89.4,54,89.4,89.4,54,89.4,54,89.4,89.4,54,89.4,54,89.4,89.4,54,89.4,54,89.4,89.4,54,89.4,54,89.4,89.4,54,89.4,54,89.4,89.4,54,89.4,54,89.4,89.4,54,89.4,54,143.6},
    };
  const PROGMEM float Menuet[3][32] = {
    {587,391,440,493,523,587,391,391,659,523,587,659,739,783,391,391,523,587,523,493,440,493,523,493,440,391,440,493,440,391,369,391},
    {200.2,75.6,121.6,121.6,113.3,255,141.7,101.5,237.3,122.8,112.2,114.5,114.5,233.7,94.4,103.9,325,65.9,69.7,109.8,120.4,249.1,116.9,109.8,113.3,120.4,260.9,139.3,120.4,125.1,120.4,622.2},
    {155.9,35.6,45.1,45.1,53.3,78.3,191.7,231.8,96,43.9,54.5,52.2,52.2,99.6,238.9,218.4,85.8,50.7,44.2,56.9,46.2,84.2,49.8,56.9,53.3,46.2,72.4,27.4,46.2,41.5,46.2,210.7},
    };
////

int PlayerInputPins[nbj_max];
int PlayerOutputPins[nbj_max];

//Time variables
unsigned long TimeStart;

bool SkipSetup=false;
int Tone_Frequency;

//Variables globales
int nbj=4;
int nbj_raw=3;
int vitesse=10;
int vitesse_raw=9;
int Game_Mode=1;
int InputState[nbj_max];
int OutputState[nbj_max];
int Equipes[10];
int NbEquipes;
int NbJoueursEq1;
int NbJoueursEq2;

int const ParamChansons=3;
int const NbNoteMax=42;

//Pour Chaque chanson:
//0 => Freq
//1 => Temps Actif
//2 => Temps Silence Après
float MaChanson[ParamChansons][NbNoteMax];
//Pour Chaque joueur: Silence,puis Musique.
float LeurTemps[ParamChansons-1][NbNoteMax];
float Scores[2];
int OrdreJoueurs[NbNoteMax];
int RandomMin;
int RandomMax;

//One-time setup:
//Define input/output
//Set NBJ
//Set vitesse
void setup() 
{
  int Pin;

  
  Serial.begin(9600);
  
  //Initialize random sequence based on floating value from an unconnected pin.
  randomSeed(analogRead(myRandPin));

  //Attach to servo and move it to initial position
  myservo.attach(Servo_Pin);
  myservo.write(Servo_LowPos);

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

  if (SkipSetup==false)
  {
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
  
    //Choix de Version Originale ou Améliorée.
    GameMode();
    if (Game_Mode == 1)
    {
      JoueChansonDEDU(3);
      delay(125);
    }
  }
}

//Setup complete.  MAIN loop.
void loop() 
{ 
  WaitForAllNonActive(nbj_raw);

  TurnOffAllLights();
  
  delay(100);
  
  Delay_Fraudeur();
  
  TurnOffAllLights();
  
  if(Game_Mode == 0)
  {
    
    RepartiteurOriginal();
  }
  else
  {
    Repartiteur();
  }
}





