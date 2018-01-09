void Delay_Fraudeur(int r)
{
  //Debut DELAY et TESTFRAUDEUR --------------------------------------
  //Délai entre les jeux.
  //Pendant ce temps, si un joueur appuie sur sa manette, sa lumière rouge allume.  Même chose pour les voisins.
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
      tone(Tone_Pin, 1500, 400);
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
    TurnOffAllLights();
    Delay_Fraudeur(random(25,70));
  }
}

void PQP()
{
  int Winner = -1;
  int r = random(5);
  //int NumWin = 0;

  //Init lights as GREEN.
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

  analogWrite(G, 0);

  //Winner found, lights on/off!
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

  //loop();
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

  //Init lights as red!
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
}


//Dernier qui pèse
void DQP()
{
  int z;
  int Perdant = -1;

  //init lights as purple
  ActivateBlueLED(100);
  TurnOnAllRedLights();
  
  z = nbj;

  do
  {
    z=z-ReadInputDeactivateOutputIfActive(nbj_raw);
  }while (z != 1);
  Perdant=FirstActiveOutput(nbj_raw);
  
  ActivateBlueLED(10);
  TurnOffNonActivePlayerRedLights();
  
  for (int i = 1; i <= 80; i++)
  {
    Tone_Frequency = 2000 - 20 * i;
    tone(Tone_Pin, Tone_Frequency);
    delay(10);
  }
  noTone(Tone_Pin);

  //Identify the Looser
  for (int e = 1; e <= 4; e++) {
    ActivateRedLight(Perdant);
    delay(500);
    DeactivateRedLight(Perdant);
    delay(500);
  }
  
  TurnOffAllRedLights();
  DeactivateBlueLED();
  delay(500);
}

  //Debut FFA

void FFA()
{
  float myRand1 = random(280,400)/100;
  int myRand2 = random(28,42);
  int r;

  if (Game_Mode==1)
  {
    JoueChansonDEDU(myRand1);
  }
  
  for (int e = 1; e <= myRand2; e++) {

    myservo.write(Servo_HighPos - random(20));

    TurnOnAllRedLights();
    delay(60 + random(200));
    TurnOffAllRedLights();

    ActivateBlueLED(80);
    delay(60 + random(200));
    DeactivateBlueLED();

    ActivateGreenLED(80);
    r = 60 + random(200);
    delay(r);
    DeactivateGreenLED();
  }


  DeactivateBlueLED();
  DeactivateGreenLED();
  TurnOffAllRedLights();
  myservo.write(Servo_LowPos);
  delay(500);
}
