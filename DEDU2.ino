#include <Servo.h>
#include "pitches.h"

Servo myservo;

//Definitions
//Pins
int const myRandPin=0; //To initialize the random function
int const G = 3; //Green LED ALL
int const B = 2; //Blue LED ALL
int const Tone_Pin = 52; //Tone

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


int PlayerInputPins[nbj_max];
int PlayerOutputPins[nbj_max];

//TimeDebugging
unsigned long TimeStart;
bool SkipSetup=false;


//Variables internes.
int Pin;
int val;
int y;
int x;
int z;
int r;
int e;
int Tone_Frequency;

//Variables globales
int nbj=1;
int nbj_raw=0;
int vitesse=1;
int vitesse_raw=0;
int Game_Mode=0;
int InputState[nbj_max];
int OutputState[nbj_max];
int Equipes[10];
int NbEquipes;
int NbJoueursEq1;
int NbJoueursEq2;

int const ParamChansons=3;
int const NbNoteMax=100;

//Pour Chaque chanson:
//0 => Freq
//1 => Temps Actif
//2 => Temps Silence Après
float MaChanson[ParamChansons][NbNoteMax];
//Pour Chaque joueur: Silence,puis Musique.
float LeurTemps[ParamChansons-1][NbNoteMax];
float Scores[2];
int OrdreJoueurs[NbNoteMax];
float SongAvgBpm;
int RandomMin;
int RandomMax;

//One-time setup:
//Define input/output
//Set NBJ
//Set vitesse
void setup() 
{
  
  ///ENLEVER
  //Debugging lines if required.
  Serial.begin(9600);
  Serial.println("Debugging window:");
  //DEBUGGING: SKIP SETUP AND USE VALUES.
  SkipSetup = true;
  //Valeurs de base
  nbj=9;
  nbj_raw=8;
  vitesse=10;
  vitesse_raw=9;
  Game_Mode = 1;
  
  ///ENLEVER
  


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
      ChansonDEDU(3);
      delay(125);
    }
  }
}

//Setup complete.  MAIN loop.
void loop() 
{
  WaitForAllNonActive(nbj_raw);

  TurnOffAllRedLights();
  DeactivateBlueLED();
  DeactivateGreenLED();
  delay(100);

/// TEST AREA
JeuChanson();
/// END TEST
  
  Delay_Fraudeur();

  if(Game_Mode == 0)
  {
    
    Serial.println("Bienvenue chez DEDU");
    RepartiteurOriginal();
  }
  else
  {
    Serial.println("Bienvenue chez DEDU2");
    Repartiteur();
  }
}





