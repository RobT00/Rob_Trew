# Command specifications

Each message consists of a sender ID, a receiver ID, and a command, separated by
a single space (` `). Messages are terminated by a newline (`\n`).

Valid IDs are `0`, `1` and `2`, where `0` represents the station and `1` and `2`
represent the two buggies.

### Commands sent by the buggy to the station:

Commands received by the station are parsed using regular expressions. They are
presented here in C# syntax

Command | Explanation
--- | ---
`ACK` | For automatic communication testing, sent for every command received. Expects no reply
`PONG` | Response to `PING`
`PING` | Response to `PONG`
`GOING` | Buggy is going after receiveing a `GO` command
`STOPPED` | Buggy stopped after receiving a `STOP` command
`GANTRY(?<GantryID>[123])` | Passing under Gantry with the corresponding ID
`GANTRY_INVALID` | The buggy detected a gantry, but its signature did not match that of any of the gantries
`IRLength: (?<Length>\d+)` | The length of the infrared pulse measured by the buggy's gantry sensor, sent purely for diagnostic purposes
`PARKED` | When the buggy has stopped after being requested to park with a `PARK` command
`OBSTACLE` | Informs the station that an obstacle has appeared in the path of the buggy and therefore it has temporarily stopped
`PATHCLEAR` | Informs the station that the obstacle has been removed and the buggy could now resume its travel
`INVALID: (?<Command>.*)` | An invalid command has been recieved from the station, addressed to the sending buggy

### Commands sent by the station to one of the buggies:

Command | Explanation
--- | ---
`SYN` | For automatic communication testing, expects nothing other than the default `ACK`
`PING` | For communications testing, expecting `PONG`
`PONG` | For communications testing, expecting `PING`
`GO` | Commands buggy to go, following the line
`STOP` | Commands buggy to stop immediately
`PARK` | Commands buggy to turn in the appropriate direction for the parking lane, then stop after parking
