void Delay_Fraudeur()
{
  //Debut DELAY et TESTFRAUDEUR --------------------------------------
  //Délai entre les jeux.
  //Pendant ce temps, si un joueur appuie sur sa manette, sa lumière rouge allume.  Même chose pour les voisins.
  
  //Spd = 10, average 250 iterations of the loop-> 10 sec;
  //Spd = 6, average 400 iterations -> 15 sec; 
  //Spd = 1, average 650 iterations -> 20 sec; 
  r = 150 + (12 - vitesse) * random(100);
  
  /*
  unsigned long TimeStart=millis();
  Serial.print("R:");
  Serial.println(r);
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
  //Serial.println((millis()-TimeStart)/1000);
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
      Serial.println("WOW");
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
  int Winner = random(0, nbj_raw);
  
  //Délai entre chaque clignotement
  int SpinDelay = 160 - nbj * 7;

  //Tout bleu pour commencer
  analogWrite(B, 80);

  //Spin the wheel!
  for (SpinDelay ; SpinDelay >= 1; SpinDelay -= 5)
  {
    for (int i = 1; i <= nbj; i++)
    {
      tone(Tone_Pin, 3500, 10);
      digitalWrite(PlayerOutputPins[i], HIGH);
      delay(SpinDelay);
      digitalWrite(PlayerOutputPins[i], LOW);
    }
  }
  
  noTone(Tone_Pin);

  //Low intensity
  analogWrite(B, 6);

  //Identify the Winner
  for (int e = 1; e <= 4; e++) {
    tone(Tone_Pin, 3500, 10);
    digitalWrite(PlayerOutputPins[Winner], HIGH);
    delay(500);
    digitalWrite(PlayerOutputPins[Winner], LOW);
    delay(500);
  }

  //Blue off.
  analogWrite(B, 0);

  loop();
 }


