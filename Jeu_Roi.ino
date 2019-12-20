void ROI()
{
  int NouveauRoi=-1;
  int Score[nbj];
  unsigned long GameTimer=0;
  #define ROI_GAMEDELAY 1
  #define PerPlayerDelay 4000
  bool PlayersInGame[nbj];
  bool PreviousState[nbj];
  bool VoteRecorded[nbj];
  bool HasReleased[nbj];
  bool ExtraRoundAllPlayersTied=true;
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
        VoteRecorded[i]=0;
        HasReleased[i]=false;
      }

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
          if(CurrentState && !PreviousState && !VoteRecorded[i] && HasReleased[i])
          {
            Score[i]++;
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
    
    //One round complete - computing.
    int MaxScore=0;
    int MaxPlayer=-1;
    int NumTiedPlayers=0;
    for(int i=0; i<nbj; i++)
    {
      //Do not compute Players that are out of game.
      if(!PlayersInGame[i]) continue;
      
      if(Score[i]>MaxScore)
      {
        NumTiedPlayers=0;
        MaxScore=Score[i];
        MaxPlayer=i;
      }
      else if(Score[i]==MaxScore)
      {
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
      TiedSoundAndLight();
      //Record that we have exhausted our extra round.
      ExtraRoundAllPlayersTied=false;
    }
    else
    {
      //Single winner condition (No Tied Players)
      if(NumTiedPlayers==0)
      {
        NouveauRoi=MaxPlayer;
FanfareFF3();
        WinnerSoundAndLight(NouveauRoi);
        
        LumiereHonte(NouveauRoi, DelaiPetiteHonte, false, true);
      }
      //All players are tied? AGAIN??  Pick at random between them.
      else if(AllPlayersTied && !ExtraRoundAllPlayersTied)
      {
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
        //Run Through the scores
        for(int iScore=0; iScore<MaxScore; iScore++)
        {
          int init=random(nbj);
          //Run through the players for each score up to Max.
          for(int cur=init; cur<init+nbj; cur++)
          {
            int i=cur%nbj;
            //Deactivate this player.
            if(Score[i]==iScore)
            {
              LooserSoundAndLight(i, true);
              PlayersInGame[i]=false;
            }
          }
        }
      }
      //Reset ExtraRound if we get to here.
      if(!ExtraRoundAllPlayersTied) ExtraRoundAllPlayersTied=true;
    } 
  }while(NouveauRoi==-1);

  //Enregistrer le nouveu roi.
  JoueurRoi=NouveauRoi;
}

