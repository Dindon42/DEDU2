#include <Servo.h>
Servo myservo;

//Definitions
//Pins
int const myRandPin=0; //To initialize the random function
int const G = 3; //Green LED ALL
int const B = 2; //Blue LED ALL
int const Tone_Pin = 52; //Tone

//Position à l'arrêt du Servo (bâton rentré)
int const Servo_LowPos = 40;
int const Servo_Pin = 53;

int const nbj_max=10;
int const nbj_raw_max=9;
int const OutPinStart = 31;
int const OutPinInterval = 2;
int const InPinStart = 24;
int const InPinInterval = 2;


int PlayerInputPins[nbj_max];
int PlayerOutputPins[nbj_max];

//Debugging
unsigned long TimeStart;


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



//One-time setup:
//Define input/output
//Set NBJ
//Set vitesse
void setup() 
{
  
  ///ENLEVER
  //Debugging lines if required.
  Serial.begin(9600);
  Serial.println("Bienvenue chez DEDU");
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

  WaitForAllNonActive(nbj_raw_max);
  
  // NBJ - Nombre de Joueurs
  // Attend que les joueurs choisissent le nombre en cliquant sur le bouton correspondant au nombre souhaité.
  // Pour 5 joueurs, cliquer sur la manette #5.  Les lumières de 1 à 5 vont s'allumer et on passe au mode suivant.
  // ----------------------------------------
  NombreJoueurs();
/*  
  ///ENLEVER
  nbj=10;
  nbj_raw=9;
*/
  //TestModeEngage
  if (nbj_raw==0)
  {
    TestMode();
  }

  //Debut VITESSE
  // Attend que les joueurs choisissent la vitesse du jeu.
  // 1 = lent, 10 = vite
  Vitesse();
/*  
  ///ENLEVER
  vitesse=10;
  vitesse_raw=9;
*/

/*
int vitesse_ecart=1;
int vitesse_ecart_raw=0;
  //Debut Ecart VITESSE
  // Attend que les joueurs choisissent l'ecart de vitesse du jeu.
  // 1 = lent, 10 = vite
  EcartVitesse(); 
  ///ENLEVER
  vitesse_ecart=10;
  vitesse_ecart_raw=9;
*/

  //Choix de Version Originale ou Améliorée.
  GameMode();
/*
  ///ENLEVER
  Game_Mode == 0;
*/
  if (Game_Mode == 1)
  {
    ChansonDEDU(3);
    delay(125);
  }
}

//Setup complete.  MAIN loop.
void loop() {
start:

  WaitForAllNonActive(nbj_raw);


  TurnOffAllRedLights();
  delay(100);
  
/// TEST AREA
//DQP();
/// END TEST
  
  Delay_Fraudeur();
  
  // Debut REPARTITEUR
  r = random(101);

  if (r < 37)
  {
    PQP();
  }
  else if (r < 82)
  {
    DQP();
  }
  else if (r < 90)
  {
    TrompeOeil();
  }
  else if (r < 94)
  {
    goto FFA;
  }
  else {
    MarqueurHonte();
  }
  // fin REPARTITEUR

  //Debut FFA

FFA:

  ChansonDEDU(1);
  
  for (int e = 1; e <= 35; e++) {

    r = 154 - random(20);
    myservo.write(r);

    for (int i = 31; i <= 49; i += 2) { //turnONALL
      digitalWrite(i, HIGH);
    }

    r = 60 + random(200);
    delay(r);

    TurnOffAllRedLights();

    analogWrite(B, 80);
    r = 60 + random(200);
    delay(r);
    analogWrite(B, 0);

    analogWrite(G, 80);
    r = 60 + random(200);
    delay(r);
    analogWrite(G, 0);
  }


  analogWrite(B, 0);
  analogWrite(G, 0);
  myservo.write(Servo_LowPos);
  delay(500);

  goto start;

  //FIN FFA
}





