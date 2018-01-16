using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MidiToDedu
{
    class MidiToDEDUConverter
    {
        static void Main(string[] args)
        {

            const string tone = "tone(tonePin,";
            const string delay = "delay(";
            const int MaxDataCnt = 3;

            double DoubleFromText;
            bool LastWasDelay = false;

            char[] commaSeparator = new char[] { '(', ',', ')' };

            string line;
            string substring;
            string[] stringcomponents;
            int DataTripletCounter = 0;
            int DataCounter = 0;
            int index;

            double[,] MyValues = new double[100, 3];

            // Read the file and display it line by line.  
            string BaseDir = "C:\\temp\\TEST\\";
            string File = "ctd2";
            string Ext = ".txt";

            System.IO.StreamReader Infile = new System.IO.StreamReader(BaseDir + File + Ext);
            System.IO.StreamWriter Outfile = new System.IO.StreamWriter(BaseDir + File + "_converted" + Ext);

            //InputFormat
            /*
            tone(tonePin, 195, 254.1664125);
            delay(338.88855);
            delay(124.999875);
            tone(tonePin, 195, 261.80529375);
            delay(349.073725);
            delay(109.25915);
             * */

            //OutputFormat:
            /*
            float ChansonDEDU[3][18] = {
                {196,196,196,247,247,261,261,349,247,196,196,294,247,196,330,294,247,261},
                {150,150,150,300,300,300,300,600,150,150,150,150,150,150,600,150,150,600},
                {100,200,100,200,200,200,200,200,100,200,100,200,100,400,400,200,100,200},
                };
            */

            while ((line = Infile.ReadLine()) != null)
            {

                if (line.IndexOf(tone) != -1)
                {
                    index = line.IndexOf(tone);
                    System.Console.WriteLine("Index: {0}", index);

                    LastWasDelay = false;

                    substring = line.Substring(index);
                    stringcomponents = substring.Split(commaSeparator);

                    foreach (string str in stringcomponents)
                    {
                        Console.WriteLine(str);
                        if (double.TryParse(str, out DoubleFromText))
                        {
                            Console.WriteLine(str);
                            Console.WriteLine(DoubleFromText);
                            MyValues[DataTripletCounter, DataCounter] = DoubleFromText;
                            DataCounter++;
                            if (DataCounter == MaxDataCnt)
                            {
                                DataCounter = 0;
                                DataTripletCounter++;
                            }
                        }
                    }
                }
                else if (line.IndexOf(delay) != -1)
                {
                    index = line.IndexOf(delay);
                    System.Console.WriteLine("Index: {0}", index);

                    substring = line.Substring(index);
                    stringcomponents = substring.Split(commaSeparator);
                    foreach (string str in stringcomponents)
                    {
                        Console.WriteLine(str);
                        if (double.TryParse(str, out DoubleFromText))
                        {

                            if (LastWasDelay == true)
                            {
                                Console.WriteLine(str);
                                Console.WriteLine(DoubleFromText);
                                MyValues[DataTripletCounter - 1, 2] += DoubleFromText;
                                DataCounter = 0; ;
                            }
                            else
                            {
                                Console.WriteLine(str);
                                Console.WriteLine(DoubleFromText);
                                MyValues[DataTripletCounter, DataCounter] = DoubleFromText - MyValues[DataTripletCounter, DataCounter - 1];
                                DataCounter++;
                                if (DataCounter == MaxDataCnt)
                                {
                                    DataCounter = 0;
                                    DataTripletCounter++;
                                }
                            }
                            LastWasDelay = true;
                        }
                    }
                }
            }

            Outfile.WriteLine("");
            Outfile.WriteLine("const PROGMEM float " + File + "[" + MaxDataCnt + "][" + DataTripletCounter + "] = {");
            Outfile.Write("    {");
            for (int i = 0; i < DataTripletCounter; i++)
            {
                if (i < DataTripletCounter - 1)
                    Outfile.Write(Math.Round(MyValues[i, 0], 1) + ",");
                else
                    Outfile.Write(Math.Round(MyValues[i, 0], 1));
            }
            Outfile.Write("},\n");
            Outfile.Write("    {");
            for (int i = 0; i < DataTripletCounter; i++)
            {
                if (i < DataTripletCounter - 1)
                    Outfile.Write(Math.Round(MyValues[i, 1], 1) + ",");
                else
                    Outfile.Write(Math.Round(MyValues[i, 1], 1));
            }
            Outfile.Write("},\n");
            Outfile.Write("    {");
            for (int i = 0; i < DataTripletCounter; i++)
            {
                if (i < DataTripletCounter - 1)
                    Outfile.Write(Math.Round(MyValues[i, 2], 1) + ",");
                else
                    Outfile.Write(Math.Round(MyValues[i, 2], 1));
            }
            Outfile.Write("},\n");
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
            Outfile.WriteLine("  RandomMin = XXXX;");
            Outfile.WriteLine("  RandomMax = XXXX;");
            Outfile.WriteLine("  return NombreDeNotes;");

            Infile.Close();
            Outfile.Close();

            System.Console.WriteLine("Export Complete");
            // Suspend the screen.  
            //System.Console.ReadLine();
        }
    }
}
