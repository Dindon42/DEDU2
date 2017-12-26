
void GameMode()
{ 
  ActivateGreenLED(100);
  ActivateBlueLED(100);
  tone(Tone_Pin, 500, 500);

  //Attend l'input des joueurs.
  Game_Mode = 999;
  while (Game_Mode==999)
  {
    for (int i=0; i<=nbj_raw_max;i++)
    {
      val = digitalRead(InPinStart+InPinInterval*i);
      if (val == HIGH)
      {
        //Original_Game
        if (i<=0)
        {
          Game_Mode = 0;
        }
        else
        //New and improved
        {
          Game_Mode=1;
        }
        break;
      }
    }
  }

  //Tous les bleus et vert à OFF.
  DeactivateGreenLED();
  DeactivateBlueLED();
  
  if (Game_Mode==0)
  {
    ClignoteEtSon(4,500,200,0);
  }
  else if(Game_Mode==1)
  {
    ClignoteEtSon(9,900,200,5);
  }
  
  delay(500);
  TurnOffAllRedLights();
  delay(500);
  
}

void NombreJoueurs()
{
  //Illumine toutes les LED bleu et envoie un son
  ActivateBlueLED(100);
  tone(Tone_Pin, 1500, 500);

  //Attend l'input des joueurs.
  nbj = 0;
  while (nbj_raw == -1)
  {
    nbj_raw=FirstActive(nbj_raw_max);
  }
  nbj=nbj_raw+1;

  //Tous les bleus à OFF.
  DeactivateBlueLED();

  //Montre aux joueurs les sélections.
  ClignoteEtSon(nbj_raw,1500,200,0);
  delay(500);
  TurnOffAllRedLights();
  delay(500);
}


//Fonction de setup pour Vitesse
void Vitesse()
{
  //Vertes à ON
  ActivateGreenLED(100);
  tone(Tone_Pin, 2500, 500);

  vitesse = 0;
  while (vitesse_raw == -1)
  {
    vitesse_raw=FirstActive(nbj_raw_max);
  }
  vitesse=vitesse_raw+1;

  //Lumières vertes OFF
  DeactivateGreenLED();

  //Montre aux joueurs les sélections.
  ClignoteEtSon(vitesse_raw,2500,300,0);
  delay(500);
  TurnOffAllRedLights();
  delay(500);
}
