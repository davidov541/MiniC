using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace WriteBinaryFile
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] nums = { 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000 };
            TextWriter tw = new StreamWriter("binfile.txt", false, Encoding.Unicode);
            for (int i = 0; i < nums.Length; i++)
            {
                tw.Write((char)nums[i]);
            }
            tw.Close();
        }
    }
}
