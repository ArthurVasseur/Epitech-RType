# R-Type Protocol

The R-Type server accepts connections from TCP clients and communicates with them using packets.

R-Type uses a binary protocol.

<br>

## Data types

| Name       | Size (bytes) | Encodes                                       | Notes                                         |
|------------|--------------|-----------------------------------------------|-----------------------------------------------|
| Boolean    | 1            | Either true or false                          | True is encoded as 0x01, false as 0x00        |
| Byte       | 1            | An integer between -128 and 127               | Unsigned 8-bit integer                        |
| int        | 4            | An integer between -2147483648 and 2147483647 | Signed 32-bit integer                         |
| uint       | 4            | An integer between 0 and 4294967295           | Unsigned 32-bit integer                       |
| short      | 2            | An integer between 0 and 65 535               | Unsigned 16-bit integer                       |

**Magic number** value is 0x424242 as uint
<br>

## TCP

### Packet format
<br>
When sending / receiving a structure, the data structure is made up of:

| Type             | Notes                                                      |
|------------------|------------------------------------------------------------|
| uint             | Magic number                                               |
| uint             | Command Id                                                 |
| uint             | Packet size                                                |
| Byte array       | Contains a data structure corresponding to the command     |
<br>


### Client -> Server packets
| Command ID | Command Name      | Description                                                                       | Associated structure |
|------------|-------------------|-----------------------------------------------------------------------------------|----------------------|
| 1001       | signin            | Set user name                                                                     | **String**           |
| 1002       | sendMessage       | Send message to lobby                                                             | **Message**          |
| 1003       | startGame         | Start a game with all players in the lobby if player is game owner                |                      |
| 1004       | createLobby       | Create lobby                                                                      |                      |
| 1005       | joinLobby         | Join lobby                                                                        | **uint**             |
<br>

### Server -> Client packets
| Command ID | Command Name      | Description                                                                    | Associated structure |
|------------|-------------------|--------------------------------------------------------------------------------|----------------------|
|  2001      | PlayerConnect     | Acknowledge new player in lobby                                                | **String**           |
|  2002      | PlayerDisconnect  | Send a notification for the disconnection of a player                          | **String**           |
|  2003      | PlayerColor       | Send player's color                                                            | **PlayerColor**      |
|  2004      | Message           | Broadcast message to all users                                                 | **Message**          |
|  2005      | StartingGame      | Send a notification acknowledging game's beginning                             | **Port**             |
|  2006      | LobbyPort         | Send a the lobby port                                                          | **Port**             |
<br>


## UDP

### Packet format
<br>
When sending / receiving a structure, the data structure is made up of:

| Type             | Notes                                                      |
|------------------|------------------------------------------------------------|
| uint             | magic number                                               |
| uint             | packet ID                                                  |
| uint             | command                                                    |
| uint             | size                                                       |
| uint array       | data                                                       |
<br>

# Structures
<br>

## String
| Type             | Description                                                |
|------------------|------------------------------------------------------------|
| uint             | string size                                                |
| byte array       | sequence of ascii values                                   |
<br>

## Message
| Type             | Description                                                |
|------------------|------------------------------------------------------------|
| String           | sender                                                     |
| String           | message                                                    |
<br>

## PlayerColor
| Type             | Description                                                |
|------------------|------------------------------------------------------------|
| enum             | player color [RED,YELLOW,BLUE,GREEN]                       |
<br>
