int CalculDelaiFraudeur(bool iNormalDelay)
{
  if(iNormalDelay)  return random(50,80) + (11 - vitesse) * random(100);
  else return random(25,50) + (11 - vitesse) * random(50);
}

void Delai_Fraudeur(unsigned int NumRoundsToWait)
{
  bool PreviousState[nbj];
  //Debut DELAI et TESTFRAUDEUR --------------------------------------
  
  //Boucle d'attente entre les jeux.
  //Normalement: faire un countdown tranquille pendant que le temps s'écoule.
  //Si qqn clique, illuminer sa lumière et monter le DEDU.
  //Si d'autres cliquent, illuminer leur lumière.
  //Si le roi clique, illuminer les LED en alternance 0,1,2,3,0...
  //À la fin, envoyer le choix du roi.
  unsigned int RoundCounter=0;
  unsigned int LightOffCounter=0;
  #define FraudeurExtraRoundsMin  60
  #define FraudeurExtraRoundsMax 100
  #define PetitFraudeurExtraRoundsMin  5
  #define PetitFraudeurExtraRoundsMax 20
  int ExtraDelai;
  #define RoiLumiere false
  int SelectedGameType=-1;
  unsigned int GameTypeSelLightOffCounter=0;
  #define Delai_GameTypeSel 10
  
  bool Fraudeur=false;
  
  LOG_GENERAL("NumRoundsToWait: ");
  LOG_GENERAL(NumRoundsToWait);
  LOG_GENERAL("\n"); 
  LOG_GENERAL("JoueurRoi: ");
  LOG_GENERAL(JoueurRoi);
  LOG_GENERAL("\n"); 
  
  do
  {
    for (int i=0; i<nbj; i++)
    {
      bool CurrentState = ReadPlayerInput(i);

      if(CurrentState && !PreviousState[i] && i==JoueurRoi && !Fraudeur)
      {
        SelectedGameType++;
        if(SelectedGameType>MAX_GAMETYPE_ROI)
        {
          SelectedGameType=-1;
          TurnOffAllRedLights();
        }
        
        GameTypeSelLightOffCounter=RoundCounter+Delai_GameTypeSel;
        
        if(NumRoundsToWait-RoundCounter<40)
        {
          LOG_GENERAL("Rectification NumRoundsToWait\n");
          NumRoundsToWait=RoundCounter+40;
        }
        
        if(NumRoundsToWait<GameTypeSelLightOffCounter)
        {
          NumRoundsToWait+=random(PetitFraudeurExtraRoundsMin, PetitFraudeurExtraRoundsMax);
        }

        //Activate all lights that correspond to the selected mode.
        if(RoiLumiere)
        {
          for(int i=0; i<=SelectedGameType; i++)
          {
            ActivateRedLight(i);
          }
        }
        else(MoveDEDUFlag(SelectedGameType+1));
      }
      
      if (CurrentState && !PreviousState[i] && i!=JoueurRoi && !ReadPlayerOutput(i))
      {
        //Nouveau Fraudeur
        //Activate the output
        if(!Fraudeur) 
        {
          LOG_GENERAL("Premier Fraudeur\n");
          TurnOffAllRedLights();
          ExtraDelai=random(FraudeurExtraRoundsMin, FraudeurExtraRoundsMax);
          MoveDEDUFlag(random(25,60));
          tone(Tone_Pin, 1500, 200);
          LightOffCounter = RoundCounter+ExtraDelai;
        }
        else
        {
          ExtraDelai=random(PetitFraudeurExtraRoundsMin, PetitFraudeurExtraRoundsMax);
          LightOffCounter += ExtraDelai;
        }
        ActivateRedLight(i);
        MultGameProb(Game_id_ROI,1.05);
        
        LOG_GENERAL("Ajout Delai: ");
        LOG_GENERAL(ExtraDelai);
        LOG_GENERAL("\n");        
        
        if(NumRoundsToWait-RoundCounter<40)
        {
          LOG_GENERAL("Rectification NumRoundsToWait\n");
          NumRoundsToWait=RoundCounter+40;
        }
        NumRoundsToWait += ExtraDelai;
        
        Fraudeur=true;
      }
      PreviousState[i] = CurrentState;
    }
    
    if(!Fraudeur && RoundCounter>GameTypeSelLightOffCounter)
    {
      TurnOffAllRedLights();
    }

    if(RoundCounter > LightOffCounter && Fraudeur)
    {
      Fraudeur=false;
      TurnOffAllRedLights();
      MoveDEDUFlag(0);
      LOG_GENERAL("Retour à la normale\n");
      LOG_GENERAL("NumRoundsToWait: ");
      LOG_GENERAL(NumRoundsToWait);
      LOG_GENERAL("\n");
      LOG_GENERAL("RoundCounter: ");
      LOG_GENERAL(RoundCounter);
      LOG_GENERAL("\n");
    }
    
    //Internal delay
    delay(40);
    RoundCounter++;
  }while(RoundCounter<NumRoundsToWait);

  LOG_GENERAL("===============\n");
  LOG_GENERAL("FRAUDEURTERMINE\n");
  LOG_GENERAL("===============\n");
  
  if(!OverrideGameTypeFromFraudeur)
  {
    ExclusiveGameType=SelectedGameType!=-1;
    ExclusiveGameType_ID=SelectedGameType;
  }
  
  LOG_GENERAL("ExclusiveGameType: ");
  LOG_GENERAL(ExclusiveGameType);
  LOG_GENERAL("\n"); 
  LOG_GENERAL("ExclusiveGameType_ID: ");
  LOG_GENERAL(ExclusiveGameType_ID);
  LOG_GENERAL("\n"); 
}