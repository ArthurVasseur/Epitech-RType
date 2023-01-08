# Epitech-RType
Epitech third year project, recreating RType game with a multiplayer mode

Install [xmake](https://xmake.io/#/)

# Build

Build the project with `xmake`.

```bash
xmake
```

Creating cmake project files.

```bash
xmake project -k cmakelists
```

Creating Visual Studio project files.

```bash
xmake project -k vsxmake
```

# Project informations

This project was completed in two months by a team of four people.
I was responsible for developing the game engine (ECS + implementation of rendering, input, audio, lobby, networing systems) and the networking portion (designing the TCP & UDP protocol and implementing it).
The other members of the group worked on the gameplay and the main menu.

## Server
- The server has a lobby system, it can manage as many as possible.
- The server is multithreaded, it can handle more than one game at a time.
- The server use a TCP protocol for the lobby and an UDP protocol for the game.

## Client

- The client contains anything necessary to display the game and handle player input.
- The client is made with SFML.


# Project guidelines

The first part of the project focus on building the core foundations of your game engine, and develop your
first R-Type prototype (sic).
The game MUST be playable at the end of this part: with a nice star-field in background, players spaceships
confront waves of enemy Bydos, everyone shooting missiles to try to get down the opponent.
The game MUST be a network game: each player use a distinct client on the network, connecting to a server
having final authorithy on what is really happening in the game.
The underlying game engine MUST be correctly structured, with visible subsystems and/or layers for Ren-
dering, Networking, Logic, etc.

## Server

The server implements all the game logic. It acts as the authoritative source of game logic events in the
game.
It MUST be multithreaded. The server MUST NOT block or wait for clients messages, as the game MUST
run frame after frame on the server !
Your abstractions’ quality will be strongly evaluated during the final defense, so pay close attention to them.
You MAY use Asio or Boost.Asio for networking, or rely on OS-specific network layer with an appropriate
encapsulation (keeping in mind the need for the server to be cross-platform).

## Client

The client is the display terminal of the game.
It MUST contain anything necessary to display the game and handle player input.
It is strongly recommended that the client also run the game logic code, to prevent having too much issues
due to network lag. In any case the server MUST have authority on what happens in the end.
You may use the SFML for rendering/audio/input/network, but other libraries can be used (such as SDL for
example). However, libraries with a too broad scope, or existing game engines (UE, Unity, Godot, etc.) are
forbidden.

## Protocol 

You MUST design a binary protocol for client/server communications.
A binary protocol, in contrast with a text protocol, is a protocol where all data is transmitted in binary format,
either raw (as-is from memory) or with some specific encoding optimized for data transmission.
Put it in other terms, prior to transmission, data is NOT converted to clear-text strings separated by end-
of-line or other character (typical null-terminated _const char*_ or std::string). For example an integer is
transmitted as-is, and not as a textual representation of the number: this is considered to be “binary” mode.

You MUST use UDP for communications between the server and the clients. A second connection using
TCP can be tolerated, but you MUST provide a strong justification. In any event, ALL in-game communica-
tions MUST use UDP.

Think about your protocol completeness, and in particular, the handling of erroneous messages. Such mal-
formed messages or packets MUST NOT lead the client or server to crash.
You MUST document your protocol. See the previous section on documentation for more information
about what is expected for the protocol documentation.

## Game Engine

You’ve now been experimenting with C++ and Object-Oriented Design for a year. That experience means it
should now be obvious to you to create abstractions and write re-usable code.
Therefore, before you begin work on your game, it is important that you start by creating a game engine !
The game engine is the core foundation of any video game: it determines how you represent an object
in-game, how the coordinate system works, and how the various systems of your game (graphics, physics,
network. . . ) communicate.
When designing your game engine, decoupling is the most important thing you should focus on. The graph-
ics system of your game only needs an entity’s appearance and position to render it. It doesn’t need to know
about how much damage it can deal or the speed at which it can move! Similarly, a physics system doesn’t
need to know what an entity looks like to update its position. Think of the best ways to decouple the various
systems in your engine.
To do so, we recommend taking a look at the Entity-Component-System architectural pattern, as well as
the Mediator design pattern. But there are many other ways to implement a game engine ! Be creative !

## General

The client MUST display a slow horizontal scrolling background representing space with stars, planets. . .
This is the star-field.
The star-field scrolling must NOT be tied to the CPU speed. Instead, you MUST use timers.
Players MUST be able to move using the arrow keys.
The server MUST be multithreaded.
If a client crashes for any reason, the server MUST continue to work and MUST notify other clients in the same game that a client crashed.
R-Type sprites are freely available on the Internet, but a set of sprites is available with this subject.
The four players in a game MUST be distinctly identifiable (via color, sprite, etc.)
There MUST be Bydos slaves in your game.
- Monsters MUST be able to spawn randomly on the right of the screen.
- The server MUST notify each client when a monster spawns, is destroyed, fires, kills a player, and soon. . .
Finally, think about basic sound design in your game. This is important for a good gameplay experience.
This is the minimum, you MUST add anything you feel will get your game closer to the original.