void ROI()
{
  int NouveauRoi=-1;
  int Score[nbj];
  unsigned long GameTimer=0;
  #define ROI_GAMEDELAY 1
  #define PerPlayerDelay
  bool PlayerInGame[nbj];
  bool PreviousState[nbj];
  bool VoteRecorded[nbj];
  //Signature Lumineuse
  //Musique glorieuse
  //Musique pendant 

  //Initialization
  for(int i=0; i<nbj; i++)
  {
    if(i==JoueurRoi) 
    {
      PlayerInGame[i]=false;
    }
    else
    {
      PlayerInGame[i]=true;
    }
  }
  
  do
  {
    //Reset Score at start of each round.
    for(int i=0; i<nbj; i++)
    {
      Score[i]=0;
    }
    
    //Scroll through all players.  Wait a decent amount of time at each to record vote.
    for(int VotePlayer=0; VotePlayer<nbj ; VotePlayer++)
    {
      //Skip Les joueurs qui ont éliminé dans les rondes précédentes.
      if(!PlayerInGame[VotePlayer]) continue;
      
      ActivateRedLight(VotePlayer);
      //Reset GameTimer at each player
      GameTimer=0;
      
      VoteRecorded[i]=0;
      do
      {
        //Scan through all players to see if they vote.
        for(int i=0; i<nbj; i++)
        {
          //Read new state
          CurrentState=ReadPlayerInput(i);
          if(CurrentState


          
          //Save State
          PreviousState[i]=CurrentState;
        }


        
        delay(ROI_GAMEDELAY);
      }while(GameTimer<PerPlayerDelay)
      DeactivateRedLight(VotePlayer);
    }
    
  }while(NouveauRoi==-1);
}

