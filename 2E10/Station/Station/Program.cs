using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Station
{
    class Program
    {
        public static bool inputOn = false;
        /// <summary>
        /// Only one thread can print at a time
        /// This can prevent potential interleaving output from different threads and buggies
        /// </summary>
        private static object printLock = new Object();
        /// <summary>
        /// Stores the input history
        /// <c>inputBuffer.Last()</c> is the currently edited command
        /// </summary>
        private static List<string> inputBuffer = new List<string>();
        /// <summary>
        /// The index of the currently viewed command in <c>inputBuffer</c>
        /// </summary>
        private static int inputBufferIndex = -1;

        private static ConsoleColor inputColour = ConsoleColor.DarkGreen;
        private static ConsoleColor emptyColour = ConsoleColor.Black;

        static void Main(string[] args)
        {
            print("Initialising...", ConsoleColor.DarkYellow);
            Station station = new Station();
            inputOn = true;
            while (true)
            {
                string input = readInput();

                if (input == "EXIT")
                    Environment.Exit(0);
                if (input == "RESET")
                {
                    inputOn = false;
                    station.setUp();
                    inputOn = true;
                    continue;
                }

                if (input.Length < 3)
                {
                    print("Station: Message too short");
                    continue;
                }
                if (!Char.IsDigit(input[0]))
                {
                    print("Station: Start message with reciever ID");
                    continue;
                }

                int ID = input[0] - '0';
                if (station.getBuggyForID(ID) == null)
                {
                    print("Station: No buggy with given ID");
                }

                string command = input.Substring(2);
                if (!executeCommand(station, command, ID))
                {
                    print("Station: No such command");
                }
            }
        }

        /// <summary>
        /// Executes the action associated with the command
        /// </summary>
        /// <returns>
        /// True if execution successful.
        /// False if command not found
        /// </returns>
        private static bool executeCommand(Station station, string command, int buggyID)
        {
            switch (command)
            {
                case "PING":
                    station.getBuggyForID(buggyID)?.sendPing();
                    break;
                case "PONG":
                    station.getBuggyForID(buggyID)?.sendPong();
                    break;
                case "GO":
                    station.getBuggyForID(buggyID)?.go();
                    break;
                case "STOP":
                    station.getBuggyForID(buggyID)?.stop();
                    break;
                case "PARK":
                    station.getBuggyForID(buggyID)?.goPark();
                    break;

                default:
                    return false;
            }
            return true;
        }

        /// <summary>
        /// Print current input buffer
        /// </summary>
        private static void printInput()
        {
            if (!inputOn)
                return;
            clearInput();
            lock (printLock)
            {
                Console.CursorLeft = 0;
                Console.BackgroundColor = inputColour;
                Console.Write("> ");
                if (inputBufferIndex != -1)
                    Console.Write(inputBuffer[inputBufferIndex]);
                Console.BackgroundColor = emptyColour;
            }
        }

        /// <summary>
        /// Clear current line with black up to the length of the input buffer
        /// </summary>
        private static void clearInput()
        {
            lock (printLock)
            {
                Console.CursorLeft = 0;
                Console.BackgroundColor = emptyColour;
                int length = 2;
                if (inputBufferIndex != -1)
                    length += inputBuffer[inputBufferIndex].Length;
                for (int i = 0; i < length; i++)
                    Console.Write(" ");
                Console.CursorLeft = 0;
            }
        }

        /// <summary>
        /// Read a line from the Console, maintaining an input history and printing buffer in colour
        /// </summary>
        /// <returns>The line read</returns>
        private static string readInput()
        {
            clearInput();

            inputBuffer.Add("");
            inputBufferIndex = inputBuffer.Count - 1;
            printInput();
            while (true)
            {
                ConsoleKeyInfo key = Console.ReadKey(true);
                clearInput();
                // Discard modifier key presses with modifier keys
                if ((key.Modifiers & ConsoleModifiers.Alt) == ConsoleModifiers.Alt)
                    continue;
                if ((key.Modifiers & ConsoleModifiers.Control) == ConsoleModifiers.Control)
                    continue;
                // Navigate input history
                if (key.Key == ConsoleKey.UpArrow)
                {
                    inputBufferIndex = Math.Max(0, inputBufferIndex - 1);
                }
                else if (key.Key == ConsoleKey.DownArrow)
                {
                    inputBufferIndex = Math.Min(inputBuffer.Count - 1, inputBufferIndex + 1);
                }
                // Edit current buffer
                else
                {
                    // If trying to use a command from the command history, make that the current command
                    if (inputBufferIndex != inputBuffer.Count - 1) {
                        inputBuffer[inputBuffer.Count - 1] = inputBuffer[inputBufferIndex];
                        inputBufferIndex = inputBuffer.Count - 1;
                    }

                    // Separate inner if statement necessary so that 'Enter' and 'Backspace' keys
                    // are never handled by the last branch
                    if (key.Key == ConsoleKey.Enter)
                    {
                        if (inputBuffer.Last().Length != 0)
                        {
                            print(inputBuffer.Last(), inputColour);
                            break;
                        }
                    }
                    else if (key.Key == ConsoleKey.Backspace)
                    {
                        if (inputBuffer.Last().Length != 0) {
                            inputBuffer[inputBuffer.Count - 1] =
                                inputBuffer.Last().Substring(0, inputBuffer.Last().Length - 1);
                        }
                    }
                    else if (key.KeyChar != '\u0000')
                    {
                        inputBuffer[inputBuffer.Count - 1] += key.KeyChar;
                    }
                }

                printInput();
            }

            clearInput();
            return inputBuffer.Last();
        }

        /// <summary>
        /// Prints <c>message</c> with a black background
        /// Adds newline and redraws the input buffer
        /// </summary>
        public static void print(string message)
        {
            print(message, emptyColour);
        }
        /// <summary>
        /// Prints <c>message</c> with the specified background colour.
        /// Adds newline and redraws the input buffer
        /// </summary>
        public static void print(string message,
            ConsoleColor? backgroundColour,
            ConsoleColor? foregroundColour = ConsoleColor.Gray)
        {
            lock (printLock)
            {
                clearInput();
                Console.CursorLeft = 0;
                Console.BackgroundColor = backgroundColour ?? emptyColour;
                Console.ForegroundColor = foregroundColour ?? ConsoleColor.Gray;
                Console.WriteLine(message);
                printInput();
                Console.BackgroundColor = emptyColour;
                Console.ForegroundColor = ConsoleColor.Gray;
            }
        }
    }
}
