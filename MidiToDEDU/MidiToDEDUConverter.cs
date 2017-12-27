using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            int counter = 0;
            string line;

            // Read the file and display it line by line.  
            System.IO.StreamReader Infile = new System.IO.StreamReader(@"C:\temp\TEST\TEST.txt");
            System.IO.StreamWriter Outfile = new System.IO.StreamWriter(@"C:\temp\TEST\TEST2.txt");

            while ((line = Infile.ReadLine()) != null)
            {
                Outfile.WriteLine(line);
                System.Console.WriteLine(line);
                counter++;
            }

            Infile.Close();
            Outfile.Close();
            System.Console.WriteLine("There were {0} lines.", counter);
            // Suspend the screen.  
            System.Console.ReadLine();
        }
    }
}
