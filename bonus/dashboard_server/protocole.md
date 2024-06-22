# Game Dashboard Connection Protocol

This document explains the connection protocol between the server implemented in C and the web-based game dashboard. It covers the process of connecting the dashboard to the server, the data exchange format, and how the dashboard updates the display based on the received data.

## Overview

The Game Dashboard allows users to connect to a game server, fetch real-time game data, and display it in an interactive web interface. The server is written in C, and the web dashboard uses Node.js, Express, and Socket.io for real-time communication.

## Connection Protocol

### Dashboard Initialization

1. **User Input**: The user enters the server's hostname and port into the dashboard's connection form.
2. **Initial Message**: Upon connecting, the dashboard sends the message `"DASHBOARD\n"` to the server to request game data.

### Data Transmission from Server to Dashboard

1. **Server Side (C)**:
   - The server collects the current state of the game, including map elements, player information, team details, and various utility parameters.
   - The server formats this data as a JSON string.
   - The server sends this JSON string to the web dashboard via a socket connection.

2. **Dashboard Side (JavaScript)**:
   - The dashboard listens for incoming messages from the server.
   - Upon receiving a message, the dashboard parses the JSON string and updates the corresponding sections of the interface (Map, Player, Teams, Utils).

### Detailed Steps

#### Server (C)

1. **Initialize Game State**:
   - The server initializes the game state, ensuring all structures are set to default values.
   - Example function: `initialize_struct_defaults(struct_t *s)`.

2. **Create JSON Objects**:
   - The server creates JSON objects for each part of the game state (map, players, teams, utils).
   - Example functions:
     - `create_json_map(struct_t *s)`
     - `create_json_players(struct_t *s)`
     - `create_json_teams(struct_t *s)`
     - `create_json_utils(struct_t *s)`

3. **Send JSON Data**:
   - The server sends the JSON data to the web dashboard.
   - Example function: `send_info_web_debug(struct_t *s)`.

#### Dashboard (JavaScript)

1. **Connect to Server**:
   - The user inputs the hostname and port, and the dashboard establishes a connection to the server.
   - Example: `connectToServer()` function in `script.js`.

2. **Send Initial Message**:
   - The dashboard sends the initial message `"DASHBOARD\n"` to request game data.
   - Example: `socket.emit('send_message', { message: 'DASHBOARD\n', timestamp: Date.now() });`.

3. **Receive and Parse Data**:
   - The dashboard receives JSON data from the server, parses it, and updates the UI.
   - Example: `socket.on('server_response', (data) => { ... })` function in `script.js`.

## Summary

### Steps for Connecting and Data Exchange

1. **User**:
   - Enter hostname and port.
   - Click `Connect`.

2. **Dashboard**:
   - Send `"DASHBOARD\n"` to the server.
   - Listen for JSON data.
   - Parse JSON and update UI.

3. **Server**:
   - Initialize game state.
   - Create JSON objects for game data.
   - Send JSON data to the dashboard.

### Example Data Exchange

1. **Dashboard sends**: `"DASHBOARD\n"`
2. **Server responds**: JSON string containing game data:
   ```json
   {
       "map": [...],
       "players": [...],
       "teams": [...],
       "utils": { ... }
   }
   ```

## Conclusion

By following this protocol, the Game Dashboard and the game server can effectively communicate, ensuring real-time updates of game data in the web interface. This setup provides a seamless experience for users to interact with and monitor the game state.
