using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace Station
{
    class Station
    {
        private Buggy buggy1 = null;
        private Buggy buggy2 = null;
        private Communications comms;
        private int numberOfBuggies = 0;

        public Station()
        {
            comms = new Communications();

            // Set up command handlers
            comms.setDefaultHandler(defaultCommandHandler);
            comms.addCommand("PING", (int ID) => getBuggyForID(ID)?.onPingRecieved());
            comms.addCommand("PONG", (int ID) => getBuggyForID(ID)?.onPongRecieved());
            comms.addCommand("GOING", (int ID) => getBuggyForID(ID)?.onGoing());
            comms.addCommand("STOPPED", (int ID) => getBuggyForID(ID)?.onStopped());
            comms.addCommand(new Regex(@"^GANTRY(?<GantryID>[123])$"),
                    (int ID, GroupCollection groups) =>
                    {
                        getBuggyForID(ID)?.onGantry(Int32.Parse(groups["GantryID"].Value));
                    });
            comms.addCommand("GANTRY_INVALID", (int ID) => getBuggyForID(ID)?.onInvalidGantry());
            comms.addCommand("PARKED", (int ID) => getBuggyForID(ID)?.onBuggyParked());
            comms.addCommand("OBSTACLE", (int ID) => getBuggyForID(ID)?.onObstacle());
            comms.addCommand("PATHCLEAR", (int ID) => getBuggyForID(ID)?.onPathClear());
            comms.addCommand(new Regex(@"^IRLength: (?<Length>\d+)$"),
                    (int ID, GroupCollection groups) =>
                    {
                        Program.print("Buggy " + ID + " Pulse length: " + groups["Length"].Value,
                                      getBuggyForID(ID)?.getColour());
                    });
            comms.addCommand(new Regex(@"^INVALID: (?<Command>.*)$"),
                    (int ID, GroupCollection groups) =>
                    {
                        Program.print("Buggy " + ID + " received invalid command: "
                                      + groups["Command"].Value,
                                      getBuggyForID(ID)?.getColour());
                    });

            setUp();
        }
        public Buggy getBuggyForID(int ID)
        {
            switch (ID)
            {
                case 1:
                    return buggy1;
                case 2:
                    return buggy2;
                default:
                    return null;
            }
        }

        private void defaultCommandHandler(int ID, string command)
        {
            Program.print("Invalid message recieved from buggy " + ID + ": " + command);
        }

        /// <summary>
        /// Changes over the buggies at the end of each lap
        /// </summary>
        /// <param name="ID">The buggy that just finished the lap</param>
        public void buggySwitch(int ID)
        {
            if (ID == 1)
                getBuggyForID(2)?.go();
            else if (ID == 2)
                getBuggyForID(1)?.go();
            else
                Program.print("Something goofed...", ConsoleColor.Magenta);
        }
        public void setNumberOfLaps(int laps)
        {
            if (getNumberOfBuggies() == 1)
                buggy1.setRequiredLaps(laps);
            else
            {
                buggy1.setRequiredLaps(laps + 1); // Buggy 1 needs to go an extra lap in 2-buggy mode
                buggy2.setRequiredLaps(laps);
            }
        }
        public void setNumberOfBuggies(int buggies)
        {
            numberOfBuggies = buggies;
        }
        public int getNumberOfBuggies()
        {
            return numberOfBuggies;
        }

        /// <summary>
        /// Sets up the environment for a fresh run
        /// Clears for any previously existing buggies, inputs number of buggies and laps,
        /// initialises new buggies and ensures they are online
        /// </summary>
        public void setUp()
        {
            // Clear any previous buggies
            if (buggy1 != null)
                buggy1.stopOnlineCheck();
            if (buggy2 != null)
                buggy2.stopOnlineCheck();

            // Input new demo parameters
            int buggies = 3;
            int laps = 0;
            while (buggies > 2 || buggies <= 0)
            {
                Console.WriteLine("How many buggies are you using? ");
                Int32.TryParse(Console.ReadLine(), out buggies);
            }
            while (laps <= 0)
            {
                Console.WriteLine("How many laps would you like to do? ");
                Int32.TryParse(Console.ReadLine(), out laps);
            }

            // Initialise new buggies
            buggy1 = new Buggy(1, Direction.Clockwise, this, comms);
            buggy1.syn(silent: true);
            Program.print("Buggy 1 OK", buggy1.getColour());
            buggy1.startOnlineCheck();
            if (buggies == 2)
            {
                buggy2 = new Buggy(2, Direction.AntiClockwise, this, comms);
                buggy2.syn(silent: true);
                Program.print("Buggy 2 OK", buggy2.getColour());
                buggy2.startOnlineCheck();
            }
            else
                buggy2 = null;
            setNumberOfBuggies(buggies);
            setNumberOfLaps(laps);
        }
    }
}
