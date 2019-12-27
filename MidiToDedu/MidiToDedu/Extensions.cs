using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Commons.Music.Midi;

namespace MidiToDedu
{
  public static class Extensions
  {
    public static double Frequency(this MidiEvent E)
    {
      return Math.Pow(2, (double)(E.Msb-69)/(double)12) * 440;
    }
  }
}
