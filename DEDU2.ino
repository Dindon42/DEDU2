#include <Servo.h>
Servo myservo;

//Definitions
//Pins
int G = 3; //Green LED ALL
int B = 2; //Blue LED ALL
int t = 52; //Tone
//Position à l'arrêt du Servo (bâton rentré)
int Servo_LowPos = 40;

//Variables internes.
int val;
int x;
int y;
int z;
int r;
int e;
int tf;
int nbj;
int vitesse;


//One-time setup: 
//Define input/output
//Set NBJ
//Set vitesse
void setup() {

  //Attach to servo and move it to initial position
  myservo.attach(53);
  myservo.write(Servo_LowPos);

  //Pin definitions
  pinMode(31, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(49, OUTPUT);

  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  pinMode(24, INPUT);
  pinMode(26, INPUT);
  pinMode(28, INPUT);
  pinMode(30, INPUT);
  pinMode(32, INPUT);
  pinMode(34, INPUT);
  pinMode(36, INPUT);
  pinMode(38, INPUT);
  pinMode(40, INPUT);
  pinMode(42, INPUT);

  // NBJ - Nombre de Joueurs
  // Attend que les joueurs choisissent le nombre en cliquant sur le bouton correspondant au nombre souhaité.
  // Pour 5 joueurs, cliquer sur la manette #5.  Les lumières de 1 à 5 vont s'allumer et on passe au nombre suivant.
  // ----------------------------------------

  //Illumine toutes les LED bleu et envoie un son
  analogWrite(B, 100);
  tone(t, 1500, 500);

  //Attend l'input des joueurs.
  nbj = 0;
  while (nbj == 0) {
    for (int i = 24; i <= 42; i = i + 2)
    { val = digitalRead(i);
      if (val == HIGH)
      {
        nbj = i / 2 - 11;
      }
    }
  }

  analogWrite(B, 0);

  //Clignote
  for (int i = 1; i <= nbj; i++) {
    x = 29 + (i * 2);
    digitalWrite(x, HIGH);
    tf = 1000 + 500 * i;
    tone(t, tf, 150);
    delay(150);
  }

  delay(500);

  for (int i = 31; i <= 49; i += 2) { //turnOFFALL
    digitalWrite(i, LOW);
  }
  delay(500);

  //FIN NBJ -----------------------------------------------

  //Debut VITESSE-----------------------------------------------

  analogWrite(G, 100);
  tone(t, 2500, 500);

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
    tone(t, tf, 100);
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
        tone(t, 1500, 1000);
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
      tone(t, tf, 3);
      delay(3);
    }
    noTone(t);
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
    tone(t, tf);
    delay(15);
  }
  noTone(t);
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
        tone(t, 1500, 400);
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
      tone(t, 3500, 10);
      digitalWrite(y, HIGH);
      delay(e);
      digitalWrite(y, LOW);
    }
  }
  noTone(t);
  analogWrite(B, 6);

  x = random(1, nbj);
  y = 29 + (2 * x);
  for (int e = 1; e <= 4; e++) {
    tone(t, 3500, 10);
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
