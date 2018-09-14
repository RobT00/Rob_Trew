using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace Station
{
    class Buggy
    {
        private int ID;
        private Direction direction;
        private int lastGantry;
        private int lapsCompleted = 0;
        private int requiredLaps = 0;

        private Communications comms;
        private Station station;

        /// <summary>
        /// Whether or not the buggy should be moving
        /// </summary>
        private volatile bool motion = false;
        private Thread onlineThread = null;
        private volatile bool onlineThreadShouldRun = false;

        public Buggy(int ID, Direction direction, Station station, Communications comms)
        {
            this.ID = ID;
            this.direction = direction;
            this.comms = comms;
            this.station = station;

            if (direction == Direction.Clockwise)
                this.lastGantry = 2;
            else
                this.lastGantry = 1;
        }
        public void startOnlineCheck()
        {
            if (onlineThread != null)
                return;
            onlineThread = new Thread(new ThreadStart(() =>
            {
                while (onlineThreadShouldRun)
                {
                    try
                    {
                        Thread.Sleep(1000);
                        bool firstTry = syn();
                        if (!firstTry)
                        {
                            buggyAction("is back online!");
                            if (motion)
                            {
                                go();
                            }
                        }
                    } catch (ThreadInterruptedException) {}
                }
            }));
            onlineThreadShouldRun = true;
            onlineThread.Start();
        }
        public void stopOnlineCheck()
        {
            if (onlineThread == null)
                return;
            onlineThreadShouldRun = false;
            onlineThread.Interrupt();
            onlineThread.Join();
        }
        public void setRequiredLaps(int laps)
        {
            requiredLaps = laps;
        }
        public ConsoleColor getColour()
        {
            switch (ID)
            {
                case 1:
                    return ConsoleColor.DarkBlue;
                case 2:
                    return ConsoleColor.DarkRed;
                default:
                    return ConsoleColor.Magenta;
            }
        }

        private string getSectionName()
        {
            int section;
            if (direction == Direction.Clockwise)
                section = lastGantry;
            else
            {
                if (lastGantry == 1)
                    section = 3;
                else
                    section = lastGantry - 1;
            }

            if ((direction == Direction.Clockwise && lastGantry == 2 &&
                        (lapsCompleted == 0 || lapsCompleted >= requiredLaps))
                || (direction == Direction.AntiClockwise && lastGantry == 1))
                return "Park Lane";
            else
                return section.ToString();
        }

        public void go()
        {
            motion = true;
            comms.send(ID, "GO");
        }
        public void stop()
        {
            motion = false;
            comms.send(ID, "STOP");
        }
        public void sendPing()
        {
            comms.send(ID, "PING");
        }
        public void sendPong()
        {
            comms.send(ID, "PONG");
        }
        public bool syn(bool silent = false)
        {
            return comms.send(ID, "SYN", () =>
                    {
                        if (!silent)
                            buggyAction("is Offline! Will keep pinging");
                    });
        }
        public void goPark()
        {
            comms.send(ID, "PARK");
        }

        public void onGantry(int currentGantry)
        {
            // At gantry that terminates the buggy's lap
            if ((direction == Direction.Clockwise && currentGantry == 2)
                || (direction == Direction.AntiClockwise && currentGantry == 1))
            {
                lapsCompleted++;
            }
            // Missed the gantry that terminates the buggy's lap, updating late
            else if ((direction == Direction.Clockwise &&
                        (lastGantry == 1 && currentGantry != 2) ||
                        (lastGantry == 3 && currentGantry == 3))
                || (direction == Direction.AntiClockwise &&
                    lastGantry == 2 && currentGantry == 2))
            {
                lapsCompleted++;
            }
            // Lap detection needs the previous gantry ID, place this afterwards
            lastGantry = currentGantry;

            buggyAction("stopping at gantry " + currentGantry);
            buggyAction("entering track section: " + getSectionName());
            buggyAction("is now on lap " + (lapsCompleted + 1));

            stop();
            Thread.Sleep(1000);

            bool shouldGo = true;
            bool shouldPark = false;
            if (station.getNumberOfBuggies() < 2)
            {
                if (lapsCompleted >= requiredLaps && currentGantry == 2)
                    shouldPark = true;
            }
            else
            {
                if (direction == Direction.Clockwise)
                {
                    if (lapsCompleted >= requiredLaps && currentGantry == 2)
                        shouldPark = true;
                    else if (lastGantry == 3)
                    {
                        shouldGo = false;
                        station.buggySwitch(ID);
                    }
                }
                else if (direction == Direction.AntiClockwise)
                {
                    if (currentGantry == 1)
                    {
                        shouldPark = true;
                    }
                }
            }
            if (shouldGo)
                go();
            if (shouldPark)
                goPark();
        }
        public void onInvalidGantry()
        {
            buggyAction("interpreted gantry as invalid");
            stop();
            Thread.Sleep(1000);
            go();
        }
        public void onObstacle()
        {
            buggyAction("has detected an obstacle in section " + getSectionName());
        }
        public void onPathClear()
        {
            buggyAction("is now able to progress in section " + getSectionName());
            go();
        }
        public void onBuggyParked()
        {
            motion = false;
            if (direction == Direction.AntiClockwise)
            {
                station.buggySwitch(ID);
                buggyAction("is in the park lane");
            }
            else
            {
                if (station.getNumberOfBuggies() == 1)
                    buggyAction("parked! " + (lapsCompleted) + " lap(s) completed!");
                else // Buggy 1 has to go an extra lap in 2-buggy mode
                    buggyAction("parked! " + (lapsCompleted - 1) + " lap(s) completed!");
            }
            if (direction == Direction.Clockwise)
                Program.print("Challenge complete!", ConsoleColor.Yellow, ConsoleColor.Black);
        }
        public void onPingRecieved()
        {
            buggyAction("PING recieved");
        }
        public void onPongRecieved()
        {
            buggyAction("PONG recieved");
        }
        public void onGoing()
        {
            buggyAction("going");
            // buggyAction("is on the move in section " + getSectionName());
        }
        public void onStopped()
        {
            buggyAction("stopped");
            // buggyAction("has stopped in section " + getSectionName());
        }

        /// <summary>
        /// Prints the ID of the buggy and the given message
        /// </summary>
        private void buggyAction(String command = "")
        {
            Program.print("Buggy " + ID + " " + command, getColour());
        }
    }
}
