void ModeMusique(int idChanson, bool ModVitesse)
{
  int NombreNotes;
  float FacteurVitesse;
  int myRand;
  
  NombreNotes=SelectionChanson(idChanson);
  
  LOG_GENERAL("NombreNotes:");
  LOG_GENERAL(NombreNotes);
  LOG_GENERAL("\n");
  
  if (ModVitesse)
  {
    myRand= random(RandomMin,RandomMax);
    FacteurVitesse=(float) myRand/100;
  }
  else
  {
    FacteurVitesse=1;
  }


  LOG_GENERAL("FacteurVitesse:");
  LOG_GENERAL(FacteurVitesse);
  LOG_GENERAL("\n");

  for (int n=0 ; n< NombreNotes ; n++)
  {
    PlayNote(Tone_Pin, MaChanson[0][n], MaChanson[1][n]/FacteurVitesse, MaChanson[2][n]/FacteurVitesse);
  }
  
  delay(2500);
}

