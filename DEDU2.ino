#include <Servo.h>
Servo myservo;

//Definitions
//Pins
int G = 3; //Green LED ALL
int B = 2; //Blue LED ALL

/////ENLEVER
int Tone_Pin = 9999; //Tone
//int Tone_Pin = 52; //Tone
/////ENLEVER

//Position à l'arrêt du Servo (bâton rentré)
int Servo_LowPos = 40;
int Servo_Pin = 53;

int const nbj_max=10;
int const nbj_raw_max=9;
int const OutPinStart = 31;
int const OutPinInterval = 2;
int const InPinStart = 24;
int const InPinInterval = 2;

int PlayerInputPins[nbj_max];
int PlayerOutputPins[nbj_max];



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
int nbj;
int nbj_raw;
int vitesse;
int vitesse_raw;
int Game_Mode;
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
  Serial.println("CECI EST UN TEST");
  ///ENLEVER
  
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

  // NBJ - Nombre de Joueurs
  // Attend que les joueurs choisissent le nombre en cliquant sur le bouton correspondant au nombre souhaité.
  // Pour 5 joueurs, cliquer sur la manette #5.  Les lumières de 1 à 5 vont s'allumer et on passe au mode suivant.
  // ----------------------------------------
  //NombreJoueurs();
  ///ENLEVER
  nbj=10;
  nbj_raw=9;

  //Debut VITESSE
  // Attend que les joueurs choisissent la vitesse du jeu.
  // 1 = lent, 10 = vite
  //Vitesse();
  ///ENLEVER
  vitesse=10;
  vitesse_raw=0;
  
  //TestModeEngage
  if (vitesse_raw==0 && nbj_raw==0)
  {
    TestMode();
  }
  else
  {
    //Choix de Version Originale ou Améliorée.
    //GameMode();
    Game_Mode == 0;

    if (Game_Mode == 1)
    {
      ChansonDEDU(2);
      delay(250);
    }
  }
}

//Setup complete.  MAIN loop.
void loop() {
start:

  TurnOffAllRedLights();
  delay(100);
  
  Delay_Fraudeur();
  
  // Debut REPARTITEUR
  r = random(100);

  if (r < 37) {
    PQP();
  }
  else if (r < 82) {
    goto DQP;
  }
  else if (r < 90) {
    goto TROMPEOEIL;
  }
  else if (r < 94) {
    goto FFA;
  }
  else {
    MarqueurHonte();
  }
  // fin REPARTITEUR


  //Debut DQP ---------------------------------

DQP:

  analogWrite(B, 100);
  for (int i = 1; i <= nbj; i++) {
    y = 29 + (2 * i);
    digitalWrite(y, HIGH);
  }


  z = nbj;

  do {
    for (int i = 1; i <= nbj; i++) {
      x = 22 + (2 * i);
      y = x + 7;
      if (digitalRead(y) == HIGH) {
        if (digitalRead(x) == HIGH) {
          digitalWrite(y, LOW);
          z--;
        }
      }
    }

  }
  while (z != 1);
  analogWrite(B, 10);

  for (int i = 1; i <= 80; i++) {
    Tone_Frequency = 2000 - 20 * i;
    tone(Tone_Pin, Tone_Frequency);
    delay(15);
  }
  noTone(Tone_Pin);
  delay (2500);
  TurnOffAllRedLights();
  analogWrite(B, 0);
  delay(500);
  goto start;

  //Fin DQP-----------------------------------------------------

  // debut TROMPEOEIL -----------------------------------

TROMPEOEIL:

  TurnOnAllRedLights();

  for (int e = 0; e <= 4000; e++) {
    for (int i = 1; i <= nbj; i++) {
      y = 22 + (2 * i);
      if (digitalRead(y) == HIGH) {
        goto bailout;
      }
    }
    delay(1);
  }

bailout:

  TurnOffAllRedLights();

  for (int e = 0; e <= 300; e++) {
    for (int i = 24; i <= 40; i += 2) {
      if (digitalRead(i) == HIGH) {
        z = i + 7;
        digitalWrite(z, HIGH);
        tone(Tone_Pin, 1500, 400);
      }
      delay(1);
    }
  }


  delay(1500);

  TurnOffAllRedLights();

  goto start;

  // fin TROMPEOEIL



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





