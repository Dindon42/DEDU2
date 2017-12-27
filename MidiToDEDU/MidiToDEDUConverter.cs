using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MidiToDedu
{
    class Program
    {
        static void Main(string[] args)
        {
            int counter = 0;
            string line;

            // Read the file and display it line by line.  
            string BaseDir = "C:\\temp\\TEST\\";
            string File = "DeadOrAlive1";
            string Ext = ".txt";

            System.IO.StreamReader Infile = new System.IO.StreamReader(BaseDir+File+Ext);
            System.IO.StreamWriter Outfile = new System.IO.StreamWriter(BaseDir+File+"_converted"+ Ext);
            
            
            while ((line = Infile.ReadLine()) != null)
            {
                Outfile.WriteLine(line);
                counter++;
            }
            

            Outfile.WriteLine("");
            Outfile.WriteLine("");
            Outfile.WriteLine("");
            Outfile.WriteLine("");
            Outfile.WriteLine("");
            Outfile.WriteLine("");
            Outfile.WriteLine("");
            Outfile.WriteLine("case XXXX:");
            Outfile.WriteLine("  NombreDeNotes = sizeof(" + File + "[0]) / sizeof(float);");
            Outfile.WriteLine("  for (int i = 0; i < ParamChansons; i++)");
            Outfile.WriteLine("  {");
            Outfile.WriteLine("      for (int j = 0; j < NombreDeNotes; j++)");
            Outfile.WriteLine("      {");
            Outfile.WriteLine("          MaChanson[i][j] = "+ File + "[i][j];");
            Outfile.WriteLine("      }");
            Outfile.WriteLine("  }");
            Outfile.WriteLine("  RandomMin = 100;");
            Outfile.WriteLine("  RandomMax = 300;");
            Outfile.WriteLine("  return NombreDeNotes;");

            Infile.Close();
            Outfile.Close();

            System.Console.WriteLine("Export Complete");
            // Suspend the screen.  
            //System.Console.ReadLine();
        }
    }
}
