#ifdef ENABLE_LOGGING
  #define LOG_ED(a) LOG_GAME(Game_id_ED,a)
#else
  #define LOG_ED(a)
#endif
void EstimeDedu()
{
  //Tunables//
  //Control Game Length
  const int MaxMainGameCycles=12;
  const int AbsoluteMaxMainGameCycles=12;
  
  //Control DEDU speed
  const int Full_Cycle_Min=8;
  const int Full_Cycle_Max=15;
  
  //Control Init
  const int num_start_cycle=4;
  
  //Control sound
  bool NoTone=true;
  //END TUNABLES//
  
  //LOCALS
  int SavedTonePin=Tone_Pin;
  if (NoTone)
  {
    Tone_Pin=9999;
  }
  int Full_Cycle=(random(Full_Cycle_Min,Full_Cycle_Max))*100;
  int GameCounter=0;
  int GameCycles=0;
  const int newtone=25;
  const int newpos=10;
  const int tone_min=200;
  const int game_delay=1;
  bool GoingUp=true;
  int Win=random(0.2*Full_Cycle,0.8*Full_Cycle);
  int LightUp=Full_Cycle/nbj_max;
  int LightCount=0;
  int PlayersInGame=nbj;
  const int num_items=3;
  //0 Abs Score
  //1 Cycles
  //2 GameCounter At click
  int Scores[nbj][num_items];
  for (int i=0; i<nbj; i++)
  {
    for (int j=0; j<num_items; j++)
    {
      Scores[i][j]=-1;
    }
  }
  bool PreviousState[nbj_max]={false};
  bool CurrentState[nbj_max];
  LOG_ED("ESTIME DEDU!");
  LOG_ED("Win");
  LOG_ED(Win);
  LOG_ED("\n");
  LOG_ED("Full_Cycle");
  LOG_ED(Full_Cycle);
  LOG_ED("\n");
  
  //Signature: Dedu monte/descend et lumières individuelles consécutives.  Son Monte descend.
  //Après 1 cycle, le DEDU s'arrête sur le target de victoire et toutes les lumières s'allument.
  //Lancer le jeu avec ReadySound.  Éteindre toutes les lumières, puis commencer.
  for (int i=0; i<num_start_cycle; i++)
  {
    for (int j=0; j<Full_Cycle; j++)
    {
      if (GoingUp)
      {
        if (j%newpos==0) MoveDEDUFlag(((float)j/(float)Full_Cycle)*100);
        if (j%newtone==0) tone(Tone_Pin,tone_min+j,newtone);
      }
      else
      {
        if (j%newpos==0) MoveDEDUFlag((((float)Full_Cycle-(float)j)/(float)Full_Cycle)*100);
        if (j%newtone==0) tone(Tone_Pin,tone_min+Full_Cycle-j,newtone);
      }
      delay(game_delay);
      if (j%LightUp==0)
      {
        if (GoingUp)
        {
          ActivateRedLight(LightCount);
          LightCount++;
        }
        else
        {
          DeactivateRedLight(LightCount);
          LightCount--;
        }
      }
    }
    GoingUp=!GoingUp;
  }
  delay(500);
  TurnOnAllRedLights();
  for (int j=0; j<Win; j++)
  {
    if (GoingUp)
    {
      if (j%newpos==0) MoveDEDUFlag(((float)j/(float)Full_Cycle)*100);
      if (j%newtone==0) tone(Tone_Pin,tone_min+j,newtone);
    }
    delay(game_delay);
  }
  delay(newtone);
  for (int i=0; i<2; i++)
  {
    TurnOffAllRedLights();
    delay(500);
    TurnOnAllRedLights();
    PlayNote(tone_min+Win,500,0);
  }
  TurnOffAllRedLights();
  delay(500);
  MoveDEDUFlag(0);
  delay(500);
  
  //Une fois que le jeu démarre, le DEDU va monter/descendre.
  //À tout moment,  les joueurs peuvent cliquer (trans OFF ON) pour faire leur choix.
  //Enregistrer la valeur du DEDU lorsque le joueur pèse, illuminer sa lumière pour indiquer que le choix est fait.

  GoingUp=true;
  //MAIN GAME LOOP
  do
  {
    //Move DEDUFLAG
    if (GoingUp)
    {
      if (GameCounter%newpos==0) MoveDEDUFlag(((float)GameCounter/(float)Full_Cycle)*100);
      if (GameCounter%newtone==0) tone(Tone_Pin,tone_min+GameCounter,newtone);
    }
    else
    {
      if (GameCounter%newpos==0) MoveDEDUFlag((((float)Full_Cycle-(float)GameCounter)/(float)Full_Cycle)*100);
      if (GameCounter%newtone==0) tone(Tone_Pin,tone_min+Full_Cycle-GameCounter,newtone);
    }
    
    //Read current state
    for (int i=0;i<nbj;i++)
    {
      CurrentState[i]=ReadPlayerInput(i);
      //Detect player press.
      if (!PreviousState[i] && CurrentState[i] && Scores[i][0]==-1)
      {
        //RECORD PLAYER SCORE BASED ON GAMECOUNTER AND CYCLES.
        if (GoingUp) Scores[i][2]=GameCounter;
        else Scores[i][2]=Full_Cycle-GameCounter;
        Scores[i][0]=abs(Win-Scores[i][2]);
        Scores[i][1]=GameCycles;
        ActivateRedLight(i);
        PlayersInGame--;

        
        LOG_ED("\nPlayerPressing!\n");
        LOG_ED("Player:");
        LOG_ED(i);
        LOG_ED("\n");
        LOG_ED("AbsoluteScore:");
        LOG_ED(Scores[i][0]);
        LOG_ED("\n");
        LOG_ED("Scores[i][2]:");
        LOG_ED(Scores[i][2]);
        LOG_ED("\n");
        LOG_ED("GoingUp=");
        LOG_ED(GoingUp);
        LOG_ED("\n");
        LOG_ED("GameCounter=");
        LOG_ED(GameCounter);
        LOG_ED("\n");
        LOG_ED("GameCycles=");
        LOG_ED(GameCycles);
        LOG_ED("\n");
        LOG_ED("PlayersInGame=");
        LOG_ED(PlayersInGame);
        LOG_ED("\n");
        LOG_ED("\n");
      }
    }
    
    //Save current in previous state
    for (int i=0;i<nbj;i++)
    {
      PreviousState[i]=CurrentState[i];
    }
    
    //Increment Counter and Wait.
    GameCounter++;
    delay(game_delay);
    
    //Reset Condition
    if (GameCounter%Full_Cycle==0)
    {
      GameCounter=0;
      GameCycles++;
      GoingUp=!GoingUp;
      if (PlayersInGame<=0) GameCycles=MaxMainGameCycles;
    }
  //Une fois que tout le monde a choisi sa valeur ou que le DEDU a cyclé x fois, arrêter le jeu.
  }while((GameCycles<MaxMainGameCycles || PlayersInGame==nbj) && GameCycles<AbsoluteMaxMainGameCycles);

  //ResetTonePin
  Tone_Pin=SavedTonePin;
  
  //FLAG DOWN, LIGHTS OUT
  MoveDEDUFlag(0);
  TurnOffAllRedLights();

  
  int Winner=-1;
  //Deal with players who have not made their choices at game end.
  for (int i=0; i<nbj; i++)
  {
    if (Scores[i][0]!=-1)
    {
      if (Winner==-1)
      {
        Winner=i;
      }
      else if (Scores[i][0]<Scores[Winner][0] || (Scores[i][0]==Scores[Winner][0] && Scores[i][1]<Scores[Winner][1]))
      {
        Winner=i;
      }
    }
  }

  //No one clicked at game end.
  if (Winner==-1)
  {
    AllLoosersSoundAndLight();
  }
  else
  {
    int NumScored=0;
    bool Scored[nbj]={false};
    #define MAXVALUE 30000
    for (int i=0; i<nbj; i++)
    {
      if (Scores[i][0]==-1)
      {
        Scores[i][0]=MAXVALUE;
        Scores[i][1]=MAXVALUE;
        Scores[i][2]=0;
      }
    }
    
    do
    {
      int Player=-1;

      int WORSTSCORE=0;
      int WORSTCYCLE=0;
      //BEST SCORE IS 0 =>NO DIFFERENCE TO TARGET POS
      //SECOND COMES GAMECYCLES IF SAME SCORE, AGAIN BEST IS LOW
      //Scores[i][0]<Scores[Winner][0] || (Scores[i][0]==Scores[Winner][0] && Scores[i][1]<Scores[Winner][1])
      for (int i=0; i<nbj; i++)
      {
        LOG_ED("Current Worst:");
        LOG_ED(Player);
        LOG_ED(", WORSTSCORE:");
        LOG_ED(WORSTSCORE);
        LOG_ED(", WORSTCYCLE:");
        LOG_ED(WORSTCYCLE);
        LOG_ED("\n");
        LOG_ED("Player:");
        LOG_ED(i);
        LOG_ED(", Score:");
        LOG_ED(Scores[i][0]);
        LOG_ED(", GameCycles:");
        LOG_ED(Scores[i][1]);
        LOG_ED("\n");
        if (!Scored[i] && i!=Winner && (Scores[i][0]>WORSTSCORE || (Scores[i][0]==WORSTSCORE && Scores[i][1]>WORSTCYCLE)))
        {
          LOG_ED("Player is the current worst - updating values\n");
          Player=i;
          WORSTSCORE=Scores[i][0];
          WORSTCYCLE=Scores[i][1];
        }
      }
      
      //Player=random(nbj);
      LOG_ED("==============\n");
      LOG_ED("Final decision\n");
      LOG_ED("==============\n");
      LOG_ED("Player:");
      LOG_ED(Player);
      LOG_ED(", Score:");
      LOG_ED(Scores[Player][0]);
      LOG_ED(", GameCycles:");
      LOG_ED(Scores[Player][1]);
      LOG_ED("\n");
      LOG_ED("==============\n");

      Scored[Player]=true;
      NumScored++;

      //Ceremony for the player.
      ActivateGreenLED(20);
      MoveDEDUFlag(((float)Win/(float)Full_Cycle)*100);
      delay(1000);
      ActivateGreenLED(0);
      
      ActivateRedLight(Player);
      delay(500);
      MoveDEDUFlag(((float)Scores[Player][2]/(float)Full_Cycle)*100);
      tone(Tone_Pin,200,200);
      delay(500);
      DeactivateRedLight(Player);
      delay(500);
      ActivateRedLight(Player);
      tone(Tone_Pin,200,200);
      delay(500);
      DeactivateRedLight(Player);
      
      MoveDEDUFlag(((float)Win/(float)Full_Cycle)*100);
        
    }while (NumScored<(nbj-1));
    
    //WINNER
    ActivateGreenLED(20);
    MoveDEDUFlag(((float)Win/(float)Full_Cycle)*100);
    delay(1000);
    ActivateGreenLED(0);
    ActivateRedLight(Winner);
    delay(500);
    MoveDEDUFlag(((float)Scores[Winner][2]/(float)Full_Cycle)*100);
    WinnerSoundAndLight(Winner);
    UpdateWinner(Winner);
    
    MoveDEDUFlag(0);
    TurnOffAllLights();
  }
}



