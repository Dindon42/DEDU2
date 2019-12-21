using System;
using System.IO;
using System.Text;
using Commons.Music.Midi;
using System.Collections.Generic;

namespace MidiToDedu
{
  class MidiToDEDUConverter
  {
    public class Note
    {
      public double Freq { get; set; }
      public int MidiNote { get; set; }
      public double Duration { get; set; }
      public double SilenceAfter { get; set; }
    }

    static void Main(string[] args)
    {
      SmfReader SMFR = new SmfReader();
      const int NOTEONSTART = 0x90;
      const int NOTEONEND = 0x9F;
      const int NOTEOFFSTART = 0x80;
      const int NOTEOFFEND = 0x8F;
      bool ExpectingNoteOff = false;
      bool ExpectingNoteOn = true;
      const double DefaultBPM = 120;
      const double DefaultTickToMicroSecond = 8.33333;

      // Read the file and display it line by line.  
      string BaseDir = @"C:\temp\";
      string File = "Figaro";
      string ExtOutput = ".txt";
      string ExtInput = ".mid";

      string Infile = BaseDir + File + ExtInput;
      System.IO.StreamWriter Outfile = new System.IO.StreamWriter(BaseDir + File + "_converted" + ExtOutput);
      List<Note> Chanson = new List<Note>();
      List<string> Warnings = new List<string>();

      using (FileStream FS = System.IO.File.OpenRead(Infile))
      {
        SMFR.Read(FS);

        double TickToMicroSecond = DefaultTickToMicroSecond;
        if (SMFR.Music.DeltaTimeSpec != 0) TickToMicroSecond = DefaultTickToMicroSecond * (DefaultBPM / (double) SMFR.Music.DeltaTimeSpec);

        foreach (MidiMessage M in SMFR.Music.Tracks[1].Messages)
        {
          var E = M.Event;

          //NOTE ON
          if (M.Event.EventType >= NOTEONSTART && M.Event.EventType <= NOTEONEND)
          {
            //Start new note
            if (ExpectingNoteOn)
            {
              //Close previous note.
              if(Chanson.Count!=0)
              {
                Chanson[Chanson.Count-1].SilenceAfter = M.DeltaTime * TickToMicroSecond;
              }
              Chanson.Add(new Note()
              {
                MidiNote = E.Msb,
                Freq = E.Frequency(),
                Duration = 0,
                SilenceAfter = 0
              });
            }
            //Close Previous note
            else
            {
              int PrevNote = Chanson.Count - 1;
              Warnings.Add("Unexpected note ON after note number: " + Chanson.Count + " MidiNote: " + Chanson[PrevNote].MidiNote);
              Chanson[PrevNote].Duration = M.DeltaTime * TickToMicroSecond;
              Chanson[PrevNote].SilenceAfter = 0;
            }
            ExpectingNoteOff = true;
            ExpectingNoteOn = false;
          }

          //NOTE OFF
          if (M.Event.EventType >= NOTEOFFSTART && M.Event.EventType <= NOTEOFFEND)
          {
            if (ExpectingNoteOff)
            {
              ExpectingNoteOff = false;
              ExpectingNoteOn = true;
              Chanson[Chanson.Count-1].Duration = M.DeltaTime * TickToMicroSecond;
            }
            else
            {
              Warnings.Add("Unexpected note OFF after note number: " + Chanson.Count + " MidiNote: " + Chanson[Chanson.Count-1].MidiNote);
            }
          }
        }
      }
      
      const int MaxDataCnt = 3;

      //OutputFormat:
      /*
      float ChansonDEDU[3][18] = {
          {196,196,196,247,247,261,261,349,247,196,196,294,247,196,330,294,247,261},
          {150,150,150,300,300,300,300,600,150,150,150,150,150,150,600,150,150,600},
          {100,200,100,200,200,200,200,200,100,200,100,200,100,400,400,200,100,200},
          };
      */
      int DataTripletCounter = Chanson.Count;
      Outfile.WriteLine("");
      Outfile.WriteLine("const PROGMEM float " + File + "[" + MaxDataCnt + "][" + DataTripletCounter + "] = {");
      Outfile.Write("    {");
      for (int i = 0; i < DataTripletCounter; i++)
      {
        Outfile.Write(Math.Round(Chanson[i].Freq, 1));
        if (i < DataTripletCounter - 1) Outfile.Write(",");
          
      }
      Outfile.Write("},\n");
      Outfile.Write("    {");
      for (int i = 0; i < DataTripletCounter; i++)
      {
        Outfile.Write(Math.Round(Chanson[i].Duration, 1));
        if (i < DataTripletCounter - 1) Outfile.Write(",");
      }
      Outfile.Write("},\n");
      Outfile.Write("    {");
      for (int i = 0; i < DataTripletCounter; i++)
      {
        Outfile.Write(Math.Round(Chanson[i].SilenceAfter, 1));
        if (i < DataTripletCounter - 1) Outfile.Write(",");
      }
      Outfile.Write("}\n");
      Outfile.WriteLine("    };");


      Outfile.WriteLine("");
      Outfile.WriteLine("");
      Outfile.WriteLine("");
      Outfile.WriteLine("");
      Outfile.WriteLine("");
      Outfile.WriteLine("");
      Outfile.WriteLine("");
      Outfile.WriteLine("case XXXX:");
      Outfile.WriteLine("  pf = (float*)" + File + ";");
      Outfile.WriteLine("  NombreDeNotes = sizeof(" + File + "[0]) / sizeof(float);");
      Outfile.WriteLine("  for (int i = 0; i < ParamChansons; i++)");
      Outfile.WriteLine("  {");
      Outfile.WriteLine("      for (int j = 0; j < NombreDeNotes; j++)");
      Outfile.WriteLine("      {");
      Outfile.WriteLine("          MaChanson[i][j] = pgm_read_float(pf+i*NombreDeNotes+j);");
      Outfile.WriteLine("      }");
      Outfile.WriteLine("  }");
      Outfile.WriteLine("  ChansonFacteurRandomMin = XXXX;");
      Outfile.WriteLine("  ChansonFacteurRandomMax = XXXX;");
      Outfile.WriteLine("  return NombreDeNotes;");
      Outfile.WriteLine("\n\n\n");
      Outfile.WriteLine("ErrorLog count: " + Warnings.Count);
      foreach (string w in Warnings)
      {
        Outfile.WriteLine(w);
      }



      Outfile.Close();

      System.Console.WriteLine("Export Complete");
      // Suspend the screen.  
      //System.Console.ReadLine();
    }
  }
}
