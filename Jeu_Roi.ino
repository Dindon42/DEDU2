
#ifdef ENABLE_LOGGING
  #define LOG_ROI(a) LOG_GAME(Game_id_ROI,a)
#else
  #define LOG_ROI(a)
#endif
void ROI()
{
  int NouveauRoi=-1;
  int Score[nbj];
  unsigned long GameTimer=0;
  #define ROI_GAMEDELAY 1
  #define PerPlayerDelay 2000
  bool PlayersInGame[nbj];
  bool PreviousState[nbj];
  bool VoteRecorded[nbj];
  bool HasReleased[nbj];
  bool ExtraRoundAllPlayersTied=true;
  #define AbsoluteMaxScore nbj+1
  //Signature Lumineuse
  //Musique glorieuse
  //Musique pendant 

  //Initialization
  for(int i=0; i<nbj; i++)
  {
    if(i==JoueurRoi) 
    {
      PlayersInGame[i]=false;
    }
    else
    {
      PlayersInGame[i]=true;
    }
    PreviousState[i]=false;
  }

  //Main Game
  do
  {
    int PlayersStartOfRound=CountActivePlayers(PlayersInGame, nbj);
    //Reset Score at start of each round.
    for(int i=0; i<nbj; i++)
    {
      Score[i]=0;
    }
    
    //Scroll through all players.  Wait a decent amount of time at each to record vote.
    for(int VotePlayer=0; VotePlayer<nbj ; VotePlayer++)
    {
      //Skip Les joueurs qui ont éliminé dans les rondes précédentes.
      if(!PlayersInGame[VotePlayer]) continue;
      
      ActivateRedLight(VotePlayer);
      //Reset GameTimer at each player
      GameTimer=0;
      for(int i=0; i<nbj; i++)
      {
        VoteRecorded[i]=false;
        HasReleased[i]=false;
      }
      
      LOG_ROI("Vote For Player: ");
      LOG_ROI(VotePlayer);
      LOG_ROI("\n");
      //Main Vote For Player Loop
      do
      {
        //Scan through all players to see if they vote.
        for(int i=0; i<nbj; i++)
        {
          //Read new state
          bool CurrentState=ReadPlayerInput(i);

          //Record that player has released
          if(!CurrentState && !HasReleased[i])
          {
            HasReleased[i]=true;
          }
          
          //Check condition to count score.
          if(CurrentState && !PreviousState[i] && !VoteRecorded[i] && HasReleased[i])
          {
            LOG_ROI("Player ");
            LOG_ROI(i);
            LOG_ROI(" has voted\n");
            Score[VotePlayer]++;
            VoteRecorded[i]=true;
          }
          
          //Save State
          PreviousState[i]=CurrentState;
        }
        delay(ROI_GAMEDELAY);
        GameTimer++;
      }while(GameTimer<PerPlayerDelay);
      DeactivateRedLight(VotePlayer);
      delay(300);
    }
    delay(1000);

    //Print scores
    for(int i=0; i<nbj; i++)
    {
      LOG_ROI("Player ");
      LOG_ROI(i);
      LOG_ROI(" Score: ");
      LOG_ROI(Score[i]);
      LOG_ROI("\n");
    }
    
    //One round complete - computing.
    int MaxScore=0;
    int MaxPlayer=-1;
    int NumTiedPlayers=-1;
    for(int i=0; i<nbj; i++)
    {
      //Do not compute Players that are out of game.
      if(!PlayersInGame[i]) continue;
      
      if(Score[i]>MaxScore)
      {
        NumTiedPlayers=1;
        MaxScore=Score[i];
        MaxPlayer=i;
        LOG_ROI("New Max Score: ");
        LOG_ROI(MaxScore);
        LOG_ROI("\n");
        LOG_ROI("Player: ");
        LOG_ROI(MaxPlayer);
        LOG_ROI("\n");
      }
      else if(Score[i]==MaxScore)
      {
        LOG_ROI("Player: ");
        LOG_ROI(i);
        LOG_ROI("tied for max score\n");
        NumTiedPlayers++;
      }
    }
    
    //Activate red lights for players in game.
    for(int i=0; i<nbj; i++)
    {
      if(PlayersInGame[i]) ActivateRedLight(i);
    }
    
    bool AllPlayersTied=NumTiedPlayers==PlayersStartOfRound;
    //Compute what to do if all players are tied.
    if (AllPlayersTied && ExtraRoundAllPlayersTied)
    {
      LOG_ROI("All Players tied. Doing an extra round.\n");
      TiedSoundAndLight();
      //Record that we have exhausted our extra round.
      ExtraRoundAllPlayersTied=false;
    }
    else
    {
      //All players are tied? AGAIN??  Pick at random between them.
      if(AllPlayersTied && !ExtraRoundAllPlayersTied)
      {
        LOG_ROI("All Players tied and they had expended the extra round.\n");
        int JoueurActifChanceux=random(PlayersStartOfRound);
        int ActiveCounter=0;
        for(int i=0; i<nbj; i++)
        {
          if(ActiveCounter==JoueurActifChanceux && PlayersInGame[i])
          {
            NouveauRoi=i;
            break;
          }
          else if(PlayersInGame[i])
          {
            ActiveCounter++;
          }
        }
        
        TiedSoundAndLight();
        LumiereHonte(NouveauRoi, (DelaiPetiteHonte+DelaiHonte)/2, false, true);
      }
      //Not single winner, Not all players tied.  Eliminate non-Max-score players.
      else
      {
        LOG_ROI("Ceremonie d'élimination\n");
        //Run Through the scores
        for(int iScore=0; iScore<MaxScore; iScore++)
        {
          bool PlayersToDeactivate[nbj];
          int numPlayersToDeactivate=0;
          //Run through the players for each score up to Max.
          for(int i=0; i<nbj; i++)
          {
            PlayersToDeactivate[i]=false;
            //Deactivate this player.
            if(Score[i]==iScore && PlayersInGame[i])
            {
              PlayersToDeactivate[i]=true;
              numPlayersToDeactivate++;
              PlayersInGame[i]=false;
            }
          }
          
          MoveDEDUFlag(iScore*((float)100/(float)AbsoluteMaxScore));
          delay(500);
          
          if(numPlayersToDeactivate>0)
          {
            delay(800);
            for(int j=0; j<5; j++)
            {
              for(int i=0; i<nbj; i++)
              {
                if(PlayersToDeactivate[i])
                {
                  SetRedLight(i, !ReadPlayerOutput(i));
                }
              }
              delay(300);
            }
          }
        }

        //We have reached maxscore. The remaining players have won the round.
        MoveDEDUFlag(0);
        delay(1500);
        
        //Single winner condition (No Tied Players)
        if(NumTiedPlayers==1)
        {
          LOG_ROI("Single Victor.\n");
          NouveauRoi=MaxPlayer;
          
          WinnerSoundAndLight(NouveauRoi);
          
          LumiereHonte(NouveauRoi, DelaiPetiteHonte, false, true);
        }
        else
        {
          OneUp();
          //Prep Next Round.
          delay(1200);
          TurnOffAllRedLights();
        }
        
      }
      //Reset ExtraRound if we get to here.
      if(!ExtraRoundAllPlayersTied) ExtraRoundAllPlayersTied=true;
    }
    LOG_ROI("END OF ROUND.\n");
    LOG_ROI("NouveauRoi");
    LOG_ROI(NouveauRoi);
    LOG_ROI("\n");
    delay(500);
  }while(NouveauRoi==-1);
  //Enregistrer le nouveu roi.
  JoueurRoi=NouveauRoi;
}

