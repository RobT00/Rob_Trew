using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Threading;

namespace TimeTest
{
    class Program
    {
        static void Main(string[] args)
        {
            SerialPort port = new SerialPort();
            port.PortName = "COM11";
            port.BaudRate = 9600;
            port.Open();

            port.Write("+++");
            Thread.Sleep(1100);
            port.WriteLine("ATID 3308, CH C, CN");
            Thread.Sleep(10000);

            port.DiscardInBuffer();

            while (true)
            {
                Stopwatch watchstop = new Stopwatch();
                watchstop.Start();
                port.Write("a");
                port.ReadChar();
                watchstop.Stop();
                Console.WriteLine(watchstop.ElapsedMilliseconds);
            }
        }
    }
}
