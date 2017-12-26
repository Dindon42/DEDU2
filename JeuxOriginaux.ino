void Delay_Fraudeur()
{
  //Debut DELAY et TESTFRAUDEUR --------------------------------------
  //Délai entre les jeux.
  //Pendant ce temps, si un joueur appuie sur sa manette, sa lumière rouge allume.  Même chose pour les voisins.
  
  int r = 50 + (12 - vitesse) * random(100); 
  /*ex.:
   * R=412 => 16s
   * R=574 => 22s
   * R=352 => 14s
   * 
   * 0.04s/R
  
  Serial.print("V=");
  Serial.print(vitesse);
  Serial.print("  R=");
  Serial.print(r);
  TakeTime();
  */
  
  int LoopsToGo=20;
  bool AtLeastOneActive = false;
  bool TriggerEnd = false;
  int x=0;
  
  //r = Nombre de fois où la boucle fraudeur va s'exécuter avant de passer au répartiteur.
  for (int a = 1; a <= r; a++)
  {
    AtLeastOneActive=ReadInputActivateOutput(nbj_raw);
    if (AtLeastOneActive)
    {
      TriggerEnd=true;
      x=1;
      //Play tone and raise flag.
      tone(Tone_Pin, 1500, 750);
      myservo.write(70);
    }
    if (TriggerEnd == true)
    {
      TriggerEnd=false;
      a=r-LoopsToGo;
    }
    //Internal delay
    delay(40);
  }

  //Fraudeurs identifiés
  if (x > 0)
  {
    delay(500);
    myservo.write(Servo_LowPos);
    delay(500);
    loop();
  }

  /*
  Serial.print("  DelayTime  ");
  Serial.println(TimeDiff());
  Delay_Fraudeur();
  */
  
}

void PQP()
{
  int Winner = -1;
  int r = random(5);
  //int NumWin = 0;

  //Random Low intensity green from time to time.
  if (r == 4) 
  {
    analogWrite(G, 1);
  }
  else 
  {
    analogWrite(G, 100);
  }

  
  do 
  {
    Winner=FirstActive(nbj_raw);
  }while (Winner == -1);
    
  //For future expansion if a tie exists.
  /*
  do
  {
    NumWin = CheckAllActive(nbj_raw);
    
    if (NumWin == 1)
    {
      for (int i=0 ; i<=nbj_raw ; i++)
      {
        if(InputState[i]==HIGH)
        {
          Winner = i;
        }
      }
    }
    else if(NumWin >= 2)
    {
      //WOW
    }
  }while (NumWin == 0);
  */

  analogWrite(G, 0);

  for (int a = 1 ; a <= 3 ; a++)  
  {
    digitalWrite(PlayerOutputPins[Winner],HIGH);
    
    for (int i = 1; i <= 120; i++)
    {
      Tone_Frequency = 500 + 30 * i;
      tone(Tone_Pin, Tone_Frequency, 3);
      delay(3);
    }
    noTone(Tone_Pin);
    delay (500);

    
    TurnOffAllRedLights();
    
    analogWrite(G, 20);
    delay(500);
    analogWrite(G, 0);
  }
  
  loop();
}

void MarqueurHonte()
{
  //Joueur chanceux
  int Winner = random(nbj);
  //Délai entre chaque clignotement
  int SpinDelay = 160 - nbj * 7;
  //Tout bleu pour commencer
  ActivateBlueLED(80);

  //Spin the wheel!
  for (SpinDelay ; SpinDelay >= 1; SpinDelay -= 5)
  {
    for (int i = 0; i <= nbj_raw; i++)
    {
      tone(Tone_Pin, 3500, 10);
      ActivateRedLight(i);
      delay(SpinDelay);
      DeactivateRedLight(i);
    }
  }
  
  noTone(Tone_Pin);

  //Low intensity
  ActivateBlueLED(6);

  //Identify the Winner
  for (int e = 1; e <= 4; e++) {
    tone(Tone_Pin, 3500, 10);
    ActivateRedLight(Winner);
    delay(500);
    DeactivateRedLight(Winner);
    delay(500);
  }

  //Blue off.
  DeactivateBlueLED();

  loop();
 }

void TrompeOeil()
{
  int NumActive = -1;
  int maxIter = random(1500,5000);
  int maxIter_Sheep = 3000;
  int Looser=-1;

  //Initialize Loosers Array
  int Loosers[nbj];
  for (int i=0 ; i<=nbj_raw;i++)
  {
    Loosers[i]=0;
  }
  
  TurnOnAllRedLights();

  for (int i = 0; i <= maxIter; i++)
  {
    Looser=FirstActive(nbj_raw);
    if (Looser >= 0) 
    {
      Loosers[Looser]=1;
      break;
    }
    delay(1);
  }

  if (Looser >= 0)
  {
    TurnOffNonActiveRedLights();
    tone(Tone_Pin, 1500, 200);
    
    for (int j = 0; j <= maxIter_Sheep; j++)
    {
      for (int i=0 ; i<=nbj_raw;i++)
      {
        if(ReadPlayerInput(i)==HIGH && Loosers[i]==0)
        {
          Loosers[i]=1;
          ActivateRedLight(i);
          tone(Tone_Pin, 1500, 200);
        }
      }
      delay(1);
    }
  }

  //Game End
  delay(250);
  TurnOffAllRedLights();

  loop();
}


//Dernier qui pèse
void DQP()
{
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
  
  loop();
}
