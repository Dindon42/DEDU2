#include <Servo.h>
Servo myservo;

//Definitions
//Pins
int G = 3; //Green LED ALL
int B = 2; //Blue LED ALL
int Tone_Pin = 52; //Tone
//Position à l'arrêt du Servo (bâton rentré)
int Servo_LowPos = 40;
int Servo_Pin = 53;

int nbj_max=10;
int nbj_raw_max=9;
int OutPinStart = 31;
int OutPinInterval = 2;
int InPinStart = 24;
int InPinInterval = 2;

//Variables internes.
int val;
int x;
int y;
int z;
int r;
int e;
int tf;
int nbj;
int nbj_raw;
int vitesse;



//One-time setup:
//Define input/output
//Set NBJ
//Set vitesse
void setup() {

  //Attach to servo and move it to initial position
  myservo.attach(Servo_Pin);
  myservo.write(Servo_LowPos);

  //Pin definitions
  //LED ROUGE des joueurs
  for (int i=0; i<=nbj_raw_max;i++)
  {
    pinMode(OutPinStart+OutPinInterval*i, OUTPUT);
  }

  //Toutes lumières G et B
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  //Manettes.
  for (int i=0; i<=nbj_raw_max;i++)
  {
    pinMode(InPinStart+InPinInterval*i, INPUT);
  }

  // NBJ - Nombre de Joueurs
  // Attend que les joueurs choisissent le nombre en cliquant sur le bouton correspondant au nombre souhaité.
  // Pour 5 joueurs, cliquer sur la manette #5.  Les lumières de 1 à 5 vont s'allumer et on passe au mode suivant.
  // ----------------------------------------

  //Illumine toutes les LED bleu et envoie un son
  analogWrite(B, 100);
  YouSpinMeRound();
  delay(500);
  tone(Tone_Pin, 1500, 500);

  //Attend l'input des joueurs.
  nbj = 0;
  while (nbj == 0) {
    for (int i=0; i<=nbj_raw_max;i++)
    {
      val = digitalRead(InPinStart+InPinInterval*i);
      if (val == HIGH)
      {
        nbj_raw = i;
        nbj = i+1;
      }
    }
  }

  //Tous les bleus à OFF.
  analogWrite(B, 0);

  //Clignote
  for (int i = 0; i <= nbj_raw; i++)
  {
    //Light and sound for valid players.
    x = OutPinStart + i * OutPinInterval;
    digitalWrite(x, HIGH);
    tf = 1000 + 500 * i;
    tone(Tone_Pin, tf, 150);
    delay(150);
  }

  delay(500);

  //Turn off all lights.
  for (int i = 31; i <= 49; i += 2) { //turnOFFALL
    digitalWrite(i, LOW);
  }
  delay(500);

  //FIN NBJ -----------------------------------------------

  //Debut VITESSE-----------------------------------------------

  analogWrite(G, 100);
  tone(Tone_Pin, 2500, 500);

  vitesse = 0;

  while (vitesse == 0) {
    for (int i = 24; i <= 42; i = i + 2)
    { val = digitalRead(i);
      if (val == HIGH)
      {
        vitesse = i / 2 - 11;
      }
    }
  }

  analogWrite(G, 0);

  //Clignote
  for (int i = 1; i <= vitesse; i++) {
    x = 29 + (i * 2);
    digitalWrite(x, HIGH);
    tf = 1500 + 300 * i;
    tone(Tone_Pin, tf, 100);
    delay(150);
  }

  delay(1000);

  for (int i = 31; i <= 49; i += 2) { //turnOFFALL
    digitalWrite(i, LOW);
  }

}

//-------------------------------------------------------





void loop() {

start:


  for (int i = 31; i <= 49; i += 2) { //turnOFFALL
    digitalWrite(i, LOW);
  }
  delay(500);

  //Debut DELAY et TESTFRAUDEUR --------------------------------------

  r = 50 + (12 - vitesse) * random(100);
  x = 0;

  for (int a = 1; a <= r; a++) {
    for (int i = 1; i <= nbj; i++) {
      y = 22 + (2 * i);
      if (digitalRead(y) == HIGH) {
        z = y + 7;
        digitalWrite(z, HIGH);
        x = 1;
      }
      if (x > 0) {
        tone(Tone_Pin, 1500, 1000);
        myservo.write(70);
        delay(1000);
        myservo.write(Servo_LowPos);
        delay(500);
        goto start;
      }
    }
    delay(40);
  }


  //Fin DELAY et TESTFRAUDEUR --------------------------------------

  // Debut REPARTITEUR
  r = random(100);

  if (r < 37) {
    goto PQP;
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
    goto MARQUEURHONTE;
  }
  // fin REPARTITEUR


  //Debut PQP --------------------------------------

PQP:

  val = 0;
  r = random(5);
  if (r == 4) {
    analogWrite(G, 1);
  }
  else {
    analogWrite(G, 100);
  }

  do
  {
    for (int i = 1; i <= nbj; i++) {
      y = 22 + (2 * i);
      if (digitalRead(y) == HIGH) {
        val = y;
      } ;
    }
  }
  while (val == 0);

  analogWrite(G, 0);

  for (int a = 1 ; a <= 3 ; a++)  {
    if (val == 24) digitalWrite(31, HIGH);
    if (val == 26) digitalWrite(33, HIGH);
    if (val == 28) digitalWrite(35, HIGH);
    if (val == 30) digitalWrite(37, HIGH);
    if (val == 32) digitalWrite(39, HIGH);
    if (val == 34) digitalWrite(41, HIGH);
    if (val == 36) digitalWrite(43, HIGH);
    if (val == 38) digitalWrite(45, HIGH);
    if (val == 40) digitalWrite(47, HIGH);
    if (val == 42) digitalWrite(49, HIGH);


    for (int i = 1; i <= 120; i++) {
      tf = 500 + 30 * i;
      tone(Tone_Pin, tf, 3);
      delay(3);
    }
    noTone(Tone_Pin);
    delay (500);

    for (int i = 31; i <= 49; i += 2) { //turnOFFALL
      digitalWrite(i, LOW);
    }
    analogWrite(G, 20);
    delay(500);
    analogWrite(G, 0);
  }


  goto start;

  //FIN PQP----------------------------------------


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
    tf = 2000 - 20 * i;
    tone(Tone_Pin, tf);
    delay(15);
  }
  noTone(Tone_Pin);
  delay (2500);
  for (int i = 31; i <= 49; i += 2) { //turnOFFALL
    digitalWrite(i, LOW);
  }
  analogWrite(B, 0);
  delay(500);
  goto start;

  //Fin DQP-----------------------------------------------------

  // debut TROMPEOEIL -----------------------------------

TROMPEOEIL:

  for (int i = 31; i <= 49; i += 2) { //turnOFFALL
    digitalWrite(i, HIGH);
  }

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

  for (int i = 31; i <= 49; i += 2) { //turnOFFALL
    digitalWrite(i, LOW);
  }

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

  for (int i = 31; i <= 49; i += 2) { //turnOFFALL
    digitalWrite(i, LOW);
  }

  goto start;

  // fin TROMPEOEIL

  // Debut MARQUEURHONTE

MARQUEURHONTE:

  analogWrite(B, 80);
  e = 160 - nbj * 7;
  for (e ; e >= 1; e -= 5) {
    for (int i = 1; i <= nbj; i++) {
      y = 29 + (2 * i);
      tone(Tone_Pin, 3500, 10);
      digitalWrite(y, HIGH);
      delay(e);
      digitalWrite(y, LOW);
    }
  }
  noTone(Tone_Pin);
  analogWrite(B, 6);

  x = random(1, nbj);
  y = 29 + (2 * x);
  for (int e = 1; e <= 4; e++) {
    tone(Tone_Pin, 3500, 10);
    digitalWrite(y, HIGH);
    delay(500);
    digitalWrite(y, LOW);
    delay(500);
  }

  analogWrite(B, 0);

  goto start;

  // Fin MARQUEURHONTE

  //Debut FFA

FFA:

  for (int e = 1; e <= 35; e++) {

    r = 154 - random(20);
    myservo.write(r);

    for (int i = 31; i <= 49; i += 2) { //turnONALL
      digitalWrite(i, HIGH);
    }

    r = 60 + random(200);
    delay(r);

    for (int i = 31; i <= 49; i += 2) { //turnOFFALL
      digitalWrite(i, LOW);
    }

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

void YouSpinMeRound() {

    tone(Tone_Pin, 184, 206.25);
    delay(312.5);
    delay(156.25);
    tone(Tone_Pin, 184, 237.1875);
    delay(359.375);
    delay(109.375);
    tone(Tone_Pin, 184, 239.765625);
    delay(363.28125);
    delay(105.46875);
    tone(Tone_Pin, 220, 211.40625);
    delay(320.3125);
    delay(148.4375);
    tone(Tone_Pin, 220, 216.5625);
    delay(328.125);
    delay(140.625);
    tone(Tone_Pin, 164, 152.109375);
    delay(230.46875);
    delay(3.90625);
    tone(Tone_Pin, 164, 152.109375);
    delay(230.46875);
    delay(3.90625);
    tone(Tone_Pin, 246, 226.875);
    delay(343.75);
    delay(125.0);
    tone(Tone_Pin, 184, 229.453125);
    delay(347.65625);
    delay(121.09375);
    tone(Tone_Pin, 184, 97.96875);
    delay(148.4375);
    delay(85.9375);
    tone(Tone_Pin, 184, 118.59375);
    delay(179.6875);
    delay(54.6875);
    tone(Tone_Pin, 246, 116.015625);
    delay(175.78125);
    delay(58.59375);
    tone(Tone_Pin, 246, 110.859375);
    delay(167.96875);
    delay(66.40625);
    tone(Tone_Pin, 220, 108.28125);
    delay(164.0625);
    delay(70.3125);
    tone(Tone_Pin, 220, 97.96875);
    delay(148.4375);
    delay(85.9375);
    tone(Tone_Pin, 164, 239.765625);
    delay(363.28125);
    delay(105.46875);
    tone(Tone_Pin, 164, 239.765625);
    delay(363.28125);
    delay(105.46875);
    tone(Tone_Pin, 246, 239.765625);
    delay(363.28125);
    delay(105.46875);
    tone(Tone_Pin, 220, 239.765625);
    delay(500.28125);

}
