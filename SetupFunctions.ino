void NombreJoueurs()
{
  //Illumine toutes les LED bleu et envoie un son
  ActivateBlueLED(100);
  tone(Tone_Pin, 1500, 400);

  //Attend l'input des joueurs.
  do
  {
    nbj_raw=FirstActive(nbj_raw_max);
  }
  while (nbj_raw == -1);
  nbj=nbj_raw+1;

  //Tous les bleus à OFF.
  DeactivateBlueLED();

  //Montre aux joueurs les sélections.
  ClignoteEtSon(nbj_raw,500,200,0);
  delay(500);
  TurnOffAllRedLights();
  delay(500);
}


//Fonction de setup pour Vitesse
void Vitesse()
{
  //Vertes à ON
  ActivateGreenLED(100);
  tone(Tone_Pin, 1250, 400);

  do
  {
    vitesse_raw=FirstActive(nbj_raw_max);
  }while (vitesse_raw == -1);
  vitesse=vitesse_raw+1;

  //Lumières vertes OFF
  DeactivateGreenLED();

  //Montre aux joueurs les sélections.
  ClignoteEtSon(vitesse_raw,1000,300,0);
  delay(500);
  TurnOffAllRedLights();
  delay(500);
}
/*
//Fonction de setup pour Ecart Vitesse
void EcartVitesse()
{
  //Vertes à ON
  ActivateGreenLED(60);
  ActivateBlueLED(20);
  tone(Tone_Pin, 2500, 500);

  do
  {
    vitesse_ecart_raw=FirstActive(nbj_raw_max);
  }while (vitesse_ecart_raw == -1);
  vitesse_ecart=vitesse_ecart_raw+1;

  //Lumières vertes OFF
  DeactivateGreenLED();
  DeactivateBlueLED();

  //Montre aux joueurs les sélections.
  ClignoteEtSon(vitesse_raw,3000,400,0);
  delay(500);
  TurnOffAllRedLights();
  delay(500);
}
*/
//Game mode selection
void GameMode()
{ 
  ActivateGreenLED(100);
  ActivateBlueLED(100);
  tone(Tone_Pin, 750, 400);
  int Selection=-1;

  //Attend l'input des joueurs.
  do
  {
    Selection=FirstActive(nbj_raw_max);
  }while  (Selection==-1);
  
  //Original_Game
  if (Selection==0)
  {
    Game_Mode = 0;
  }
  else
  //New and improved
  {
    Game_Mode=1;
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
