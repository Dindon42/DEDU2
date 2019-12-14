float RelativeError(float TestValue,float TrueValue)
{
  float Score;
  
  if (TrueValue!=0)
  {
    Score=1 - (  abs( TrueValue-TestValue )/( TrueValue) );
  }
  else
  {
    Score=0;
  }

  
  if (Score<0) Score=0;

/*
  LOG_GENERAL("\n");
  LOG_GENERAL("\n");
  LOG_GENERAL("Test:");
  LOG_GENERAL(TestValue);
  LOG_GENERAL("\n");
  LOG_GENERAL("True:");
  LOG_GENERAL(TrueValue);
  LOG_GENERAL("\n");
  LOG_GENERAL("Score:");
  LOG_GENERAL(Score);
  LOG_GENERAL("\n");
  LOG_GENERAL("\n");
*/
  return Score;
}


void UpdateWinner(int iPlayer)
{
  GlobalScore[iPlayer]++;
}

void UpdateWinners(bool Winners[], int NbPlayers)
{
  for (int i=0; i<NbPlayers; i++)
  {
    if(Winners[i]) GlobalScore[i]++;
  }
}

void HighScoreSpecialEvent()
{
  if(Game_Mode!=Game_Mode_Experimental) return;
  int Score_Min = 5;
  int Score_Diff_Threshold=JoueurPuissant==-1 ? 2 : 0;
  int Score_1=-1;
  int Score_1_Player;
  int Score_2=-1;
  bool Score_1_Tied;
  for (int i=0; i<nbj_max; i++)
  {
    if(GlobalScore[i]==Score_1)
    {
      Score_1_Tied=true;
    }
    else if(GlobalScore[i]>Score_1)
    {
      Score_2=Score_1;
      Score_1=GlobalScore[i];
      Score_1_Player=i;
      Score_1_Tied=false;
    }
  }
  
  LOG_GENERAL("===========================\n");
  LOG_GENERAL("GLOBAL_SCORES_SPECIAL_EVENT\n");
  LOG_GENERAL("Score_1:");
  LOG_GENERAL(Score_1);
  LOG_GENERAL("\n");
  LOG_GENERAL("Score_1_Player:");
  LOG_GENERAL(Score_1_Player);
  LOG_GENERAL("\n");
  LOG_GENERAL("Score_2:");
  LOG_GENERAL(Score_2);
  LOG_GENERAL("\n");
  LOG_GENERAL("Score_1_Tied:");
  LOG_GENERAL(Score_1_Tied);
  LOG_GENERAL("\n");
  LOG_GENERAL("===========================\n");
  
  if(Score_1>Score_2+Score_Diff_Threshold && Score_1_Player!=JoueurPuissant && !Score_1_Tied && Score_1>Score_Min)
  {
    JoueurPuissant=Score_1_Player;
    LOG_GENERAL("===========================\n");
    LOG_GENERAL("NOUVEAU JOUEUR PUISSANT:");
    LOG_GENERAL(Score_1_Player);
    LOG_GENERAL("\n");
    TurnOffAllLights();
    if(!SkipLights)
    {
      for(int i=0; i<7; i++)
      {
        SetRedLight(Score_1_Player, i%2==0);
        delay(200);
      }
    }
    TurnOffAllLights();
  }
  LOG_GENERAL("JOUEUR PUISSANT:");
  LOG_GENERAL(JoueurPuissant);
  LOG_GENERAL("\n");
  LOG_GENERAL("===========================\n");
}

