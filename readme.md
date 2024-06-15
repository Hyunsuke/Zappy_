### Introduction

# Introduction to the Zappy Project

Welcome to the Zappy project! This documentation will guide you through setting up, using, and debugging the Zappy project. The goal of this project is to create a network game where several teams confront each other on a tile map containing resources. The winning team is the first one where at least 6 players reach the maximum elevation.

## Project Overview

### Objective

The primary objective of Zappy is to manage a world and its inhabitants. The game involves multiple teams competing on a tile-based map. Players must gather resources, elevate their status, and ultimately achieve the highest level of elevation to win.

### Components

Zappy consists of three main components:
1. **Server (`zappy_server`)**: Manages the game world and handles communication between clients.
2. **Graphical Client (`zappy_gui`)**: Provides a visual representation of the game world and its inhabitants.
3. **AI Client (`zappy_ai`)**: Controls the inhabitants (players) autonomously, following game rules and strategies.

### Key Features

- **Resource Management**: Players collect various resources such as food and stones (linemate, deraumere, sibur, mendiane, phiras, thystame).
- **Elevation Ritual**: Players perform rituals to elevate their status, requiring specific resources and team members at the same level.
- **Map Navigation**: The game world is a continuous map where players can move seamlessly from one edge to another.
- **Sound Transmission**: Players can broadcast messages that other players can hear, aiding in team communication.

### Game Mechanics

1. **Geography**: The game world, Trantor, is a flat, continuous map with no relief features. Players can traverse the map endlessly in all directions.
2. **Resources**: The server spawns resources at regular intervals, and players must collect these resources to survive and elevate their status.
3. **Elevation**: The primary goal is to elevate in the Trantorian hierarchy by gathering the necessary resources and players on the same tile.

### Binaries and Usage

The project includes the following binaries:

- **`zappy_server`**: Manages the game world.
    ```sh
    ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq
    ```

- **`zappy_gui`**: Visualizes the game world.
    ```sh
    ./zappy_gui -p port -h machine
    ```

- **`zappy_ai`**: Controls the inhabitants autonomously.
    ```sh
    ./zappy_ai -p port -n name -h machine
    ```

### Communication Protocol

The server and clients communicate via TCP sockets. The communication protocol ensures that clients can send requests and receive responses efficiently. Here is an overview of the communication process:

1. **Client Connection**: The client connects to the server's port.
2. **Initial Handshake**:
    - Server sends: `WELCOME\n`
    - Client sends: `TEAM_NAME\n`
    - Server responds with: `CLIENT_NUM\n X Y\n`
3. **Command Execution**: Clients send commands, and the server executes them in the order received.

### Commands

Players respond to specific actions with defined commands. Each command has an associated time limit and expected response:

- **Move Up**: `Forward` (7/f) - `ok`
- **Turn Right**: `Right` (7/f) - `ok`
- **Turn Left**: `Left` (7/f) - `ok`
- **Look Around**: `Look` (7/f) - `[tile1, tile2, ...]`
- **Check Inventory**: `Inventory` (1/f) - `[linemate n, sibur n, ...]`
- **Broadcast Message**: `Broadcast text` (7/f) - `ok`
- **Connect to New Slot**: `Connect_nbr` - `value`
- **Fork Player**: `Fork` (42/f) - `ok`
- **Eject Players**: `Eject` (7/f) - `ok/ko`
- **Take Object**: `Take object` (7/f) - `ok/ko`
- **Set Object Down**: `Set object` (7/f) - `ok/ko`
- **Start Incantation**: `Incantation` (300/f) - `Elevation underway / ko`

In case of an unknown or incorrect command, the server must respond with `ko`.

## Conclusion

The Zappy project provides a complex and engaging environment where players must strategically gather resources, communicate, and elevate their status to win. This documentation aims to assist you in setting up, using, and debugging the project effectively. For detailed instructions on specific tasks, refer to the respective pages in this wiki.

---

For any questions or further assistance, feel free to open an issue or contact the project maintainers. Happy gaming and development!