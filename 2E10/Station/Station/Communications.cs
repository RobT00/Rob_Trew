using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Threading;
using System.Text.RegularExpressions;

namespace Station
{
    class Communications
    {
        private SerialPort port = new SerialPort();

        private Dictionary<Regex, Action<int, GroupCollection>> buggyhash =
            new Dictionary<Regex, Action<int, GroupCollection>>();
        private Action<int, string> defaultHandler = null;

        // Three objects required in the following arrays to enable using buggy IDs
        // as indices (1 and 2)

        /// <summary>
        /// Flags indicating wether sent message has been received by the respective buggies
        /// </summary>
        private bool[] received = { false, false, false };
        /// <summary>
        /// Prevents changing the <c>received</c> flags while they are necessary for the logic
        /// </summary>
        private object[] receiveLocks = { new object(), new object(), new object() };
        /// <summary>
        /// A buggy can only send or await receipt of one message at a time
        /// </summary>
        private object[] sendLocks = { new object(), new object(), new object() };
        /// <summary>
        /// Prevent writing to the serial port from multiple threads simultaneously
        /// </summary>
        private object portLock = new object();

        public Communications()
        {
            port.PortName = "COM5";
            port.BaudRate = 9600;
            port.Open();

            port.Write("+++");
            Thread.Sleep(1100);
            port.WriteLine("ATID 3308, CH C, CN");
            Thread.Sleep(10000); // Wait for AT mode to expire

            port.DiscardInBuffer();
            port.DataReceived += recievedData;

            addCommand("ACK", (int ID) => { });
        }
        /// <summary>
        /// Sends command to the specified buggy
        /// </summary>
        /// <param name="buggy_id">Target buggy</param>
        /// <param name="command">Command to send</param>
        /// <param name="offlineHandler">Executed if the message is not received
        /// on the first try instead of the default user feedback</param>
        /// <returns>True if received on first attempt, false otherwise</returns>
        public bool send(int buggy_id, string command, Action offlineHandler = null)
        {
            int reps = 0;
            int sender_id = 0;
            lock (sendLocks[buggy_id])
            {
                lock (receiveLocks[buggy_id])
                {
                    received[buggy_id] = false;
                    while (!received[buggy_id])
                    {
                        reps++;

                        if (reps == 3 && !received[buggy_id])
                        {
                            if (offlineHandler != null)
                            {
                                offlineHandler();
                            }
                            else
                            {
                                Program.print("Command " + command + " not being recieved by buggy "
                                              + buggy_id);
                                Program.print("Will keep sending command");
                            }
                        }
                        lock (portLock)
                        {
                            port.Write(sender_id + " " + buggy_id + " " + command + "\n");
                        }
                        Monitor.Wait(receiveLocks[buggy_id], 200);
                    }
                }
            }
            if (reps > 2)
            {
                if (offlineHandler == null)
                {
                    Program.print("Command " + command + " received after " + reps + " attempts");
                }
                return false;
            }
            return true;
        }

        /// <summary>
        /// Handler for incoming data
        /// </summary>
        public void recievedData(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort test = (SerialPort)sender;
            String message = test.ReadLine();

            // Extract IDs and filter by them
            if (message.Length < 5)
                return;
            int sender_id = message[0] - '0';
            int reciever_id = message[2] - '0';
            string command = message.Substring(4);
            if (reciever_id != 0)
                return;
            if (sender_id != 1 && sender_id != 2)
                return;

            // Process command receipt acknowledgement
            if (command == "ACK")
            {
                lock (receiveLocks[sender_id])
                {
                    received[sender_id] = true;
                    Monitor.Pulse(receiveLocks[sender_id]);
                }
            }

            // Run matching handlers or the default handler if there is no matching handler
            bool matched = false;
            foreach (KeyValuePair<Regex, Action<int, GroupCollection>> pair in buggyhash)
            {
                Match match = pair.Key.Match(command);
                if (match.Success) {
                    matched = true;
                    Task.Run(() => pair.Value?.Invoke(sender_id, match.Groups));
                }
            }
            if (!matched)
            {
                Task.Run(() => defaultHandler?.Invoke(sender_id, command));
            }
        }
        public void addCommand(string command, Action<int> handler)
        {
            addCommand(new Regex("^" + command + "$"), (int ID, GroupCollection groups) => handler(ID));
        }
        public void addCommand(Regex command, Action<int, GroupCollection> handler)
        {
            buggyhash.Add(command, handler);
        }
        public void setDefaultHandler(Action<int, string> handler)
        {
            defaultHandler = handler;
        }
    }
}
