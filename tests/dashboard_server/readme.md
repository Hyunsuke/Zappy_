# Game Dashboard

A real-time game dashboard application featuring a dynamic map view, player information, team details, and utilities display. It supports dark and light modes, with the ability to connect to a server to fetch game data.

## Features

- **Real-time Data**: Fetch and display game data such as map elements, players, and teams in real-time.
- **Dynamic Map View**: Interactive map view displaying detailed information for each cell.
- **Player Information**: List and details of all players, dynamically updated.
- **Team Information**: List and details of all teams, dynamically updated.
- **Utilities Information**: Display various utility parameters of the game.
- **Dark Mode**: Toggle between light and dark themes.
- **Server Connection**: Connect to a server to fetch and display game data.

## Prerequisites

- Node.js
- npm (Node Package Manager)

## Installation

1. **Install dependencies**:
    ```sh
    npm install express socket.io net body-parser
    ```

## Usage

1. **Start the server**:
    ```sh
    node server.js
    ```

2. **Open your browser and navigate to**:
    ```
    http://localhost:3001
    ```

3. **Connect to the game server**:
    - Enter the hostname and port in the input fields at the top right and click `Connect`.

4. **Navigate through the dashboard**:
    - Use the top menu to switch between Map, Player, Team, and Utils sections.

5. **Refresh data**:
    - Click the `Refresh` button to fetch the latest data from the server.

6. **Toggle dark mode**:
    - Click the `Toggle Theme` button to switch between light and dark themes.

## Project Structure

```
.
├── public
│   ├── index.html
│   ├── style.css
│   ├── script.js
│   └── socket.io.js (loaded from the socket.io package)
├── server.js
├── package.json
├── web_debug.c
└── README.md
```

### File Descriptions

- **public/index.html**: The main HTML file for the dashboard application.
- **public/style.css**: The CSS file for styling the dashboard application.
- **public/script.js**: The JavaScript file for client-side logic and interactivity.
- **server.js**: The server-side code to handle socket connections and communication with the game server.
- **web_debug.c**: C code for handling game data and sending it to the web dashboard.
- **package.json**: The package configuration file, containing scripts and dependencies.

## Code Explanation

### server.js

```javascript
const express = require('express');
const http = require('http');
const socketIo = require('socket.io');
const net = require('net');
const bodyParser = require('body-parser');

const app = express();
const server = http.createServer(app);
const io = socketIo(server);

app.use(bodyParser.json());
app.use(express.static('public'));

let client = null;

io.on('connection', (socket) => {
    console.log('New client connected');

    socket.on('connect_to_server', ({ hostname, port }) => {
        client = new net.Socket();
        client.connect(port, hostname, () => {
            console.log('Connected to server');
            socket.emit('receive_message', { message: 'Connected to server' });
        });

        client.on('data', (data) => {
            socket.emit('server_response', { response: data.toString().replace(/\n/g, '\\n').replace(/\r/g, '\\r').replace(/\0/g, '\\0'), timestamp: Date.now() });
        });

        client.on('error', (err) => {
            console.error('Connection error: ', err);
            socket.emit('receive_message', { message: 'Connection error: ' + err.message });
        });
    });

    socket.on('send_message', ({ message, timestamp }) => {
        if (client) {
            const formattedMessage = message.replace(/\\n/g, '\n');
            client.write(formattedMessage, (err) => {
                if (err) {
                    console.error('Error sending message: ', err);
                    socket.emit('receive_message', { message: 'Error sending message: ' + err.message });
                } else {
                    console.log(`Message sent: ${formattedMessage}`);
                }
            });
        } else {
            socket.emit('receive_message', { message: 'Not connected to server' });
        }
    });

    socket.on('disconnect', () => {
        console.log('Client disconnected');
        if (client) {
            client.destroy();
        }
    });
});

const port = 3001;
server.listen(port, () => {
    console.log(`Server running at http://localhost:${port}/`);
});
```

### public/index.html

Contains the HTML structure for the dashboard application. Key features include:
- A connection form to enter the hostname and port.
- Sections for Map, Player, Team, and Utils data.
- A refresh button to fetch the latest data.
- A toggle theme button to switch between light and dark modes.

```html
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title>Game Dashboard</title>
    <link rel="stylesheet" href="style.css">
    <script src="/socket.io/socket.io.js"></script>
    <script src="script.js" defer></script>
</head>
<body class="dark-mode">
    <div class="top-menu">
        <div class="menu-buttons">
            <button onclick="showSection('map')">Map</button>
            <button onclick="showSection('player')">Player</button>
            <button onclick="showSection('team')">Team</button>
            <button onclick="showSection('utils')">Utils</button>
            <button id="refresh-btn" onclick="refreshData()">Refresh</button>
            <button id="toggle-theme" onclick="toggleTheme()">Toggle Theme</button>
        </div>
        <div class="connect-form">
            <input type="text" id="hostname" placeholder="Enter IP address">
            <input type="number" id="port" placeholder="Enter port">
            <button id="connect-btn" onclick="connectToServer()">Connect</button>
        </div>
    </div>
    <div class="container">
        <div id="map" class="section">
            <div class="map-container">
                <h2>Map</h2>
                <table id="map-table"></table>
            </div>
            <div class="details">
                <h2>Element Details</h2>
                <div id="element-details"></div>
            </div>
        </div>
        <div id="player" class="section">
            <div class="sidebar">
                <h2>Players</h2>
                <div id="player-list"></div>
            </div>
            <div class="details">
                <h2>Player Details</h2>
                <div id="player-details"></div>
            </div>
        </div>
        <div id="team" class="section">
            <div class="sidebar">
                <h2>Teams</h2>
                <div id="team-list"></div>
            </div>
            <div class="details">
                <h2>Team Details</h2>
                <div id="team-details"></div>
            </div>
        </div>
        <div id="utils" class="section">
            <h1>Utils</h1>
            <div id="utils-data"></div>
        </div>
    </div>
</body>
</html>
```

### public/style.css

Handles the styling for the dashboard application, including light and dark themes, button transitions, and layout adjustments.

```css
body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 0;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    height: 100vh;
    transition: background-color 0.3s, color 0.3s;
}

body.dark-mode {
    background-color: #121212;
    color: #e0e0e0;
}

body.light-mode {
    background-color: #f5f5f5;
    color: #121212;
}

.top-menu {
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 10px;
    background-color: #007BFF;
    color: white;
    width: 100%;
    position: fixed;
    top: 0;
}

.menu-buttons button {
    padding: 10px 20px;
    background-color: #007BFF;
    color: white;
    border: none;
    border-radius: 5px;
    cursor: pointer;
    margin: 0 5px;
}

.menu-buttons button:hover {
    background-color: #0056b3;
}

.connect-form {
    display: flex;
    align-items: center;
}

.connect-form input {
    margin-left: 10px;
    padding: 8px;
    border-radius: 5px;
    border: 2px solid #676767;
}

.connect-form button {
    padding: 10px 15px;
    background-color: #0056b3;
    color: white;
    border: none;
    border-radius: 5px;
    cursor: pointer;
    margin-left: 10px;
}

.connect-form button:hover {
    background-color: #003f7f;
}

.container {
    display: flex;
    flex-direction: column;
   

 align-items: center;
    padding: 20px;
    width: 100%;
    height: calc(100vh - 60px);
    margin-top: 60px;
}

.map-container,
.details,
.sidebar,
.utils {
    padding: 20px;
    border-radius: 8px;
    box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
}

body.dark-mode .map-container,
body.dark-mode .details,
body.dark-mode .sidebar,
body.dark-mode .utils {
    background-color: #2c2c2c;
    color: #e0e0e0;
}

body.light-mode .map-container,
body.light-mode .details,
body.light-mode .sidebar,
body.light-mode .utils {
    background-color: #ffffff;
    color: #121212;
}

.map-container,
.details,
.sidebar,
.utils {
    flex: 1;
    margin: 10px;
    max-width: 300px;
}

.section {
    display: none;
    width: 100%;
}

.section.active {
    display: flex;
    flex-wrap: wrap;
}

.section h1, .section h2 {
    margin-top: 0;
}

#map-table {
    width: 100%;
    border-collapse: collapse;
}

#map-table td, #map-table th {
    border: 1px solid #ddd;
    padding: 8px;
    text-align: center;
}

#map-table td {
    cursor: pointer;
}

#map-table td:hover {
    background-color: #f1f1f1;
}

#map-table th {
    background-color: #007BFF;
    color: white;
}

.player-item, .team-item {
    padding: 10px;
    border-bottom: 1px solid #ddd;
    cursor: pointer;
}

.player-item:hover, .team-item:hover {
    background-color: #f1f1f1;
}
```

### public/script.js

Handles client-side logic, including server connection, data fetching, and updating the dashboard sections.

```javascript
const socket = io();

function showSection(sectionId) {
    const sections = document.querySelectorAll('.section');
    sections.forEach(section => {
        section.classList.remove('active');
    });
    document.getElementById(sectionId).classList.add('active');
}

function connectToServer() {
    const hostname = document.getElementById('hostname').value;
    const port = document.getElementById('port').value;
    if (hostname && port) {
        socket.emit('connect_to_server', { hostname, port });
    } else {
        alert('Please enter both IP address and port.');
    }
}

socket.on('server_response', (data) => {
    const response = JSON.parse(data.response);
    updateDashboard(response);
});

function updateDashboard(data) {
    updateMap(data.map);
    updatePlayers(data.players);
    updateTeams(data.teams);
    updateUtils(data.utils);
}

function updateMap(map) {
    const mapTable = document.getElementById('map-table');
    mapTable.innerHTML = '';
    
    // Create table header
    const headerRow = document.createElement('tr');
    const emptyHeader = document.createElement('th');
    headerRow.appendChild(emptyHeader);
    for (let x = 0; x < map[0].length; x++) {
        const headerCell = document.createElement('th');
        headerCell.textContent = x;
        headerRow.appendChild(headerCell);
    }
    mapTable.appendChild(headerRow);

    // Create table body
    map.forEach((row, rowIndex) => {
        const tableRow = document.createElement('tr');
        const rowHeader = document.createElement('th');
        rowHeader.textContent = rowIndex;
        tableRow.appendChild(rowHeader);

        row.forEach((cell, cellIndex) => {
            const cellElement = document.createElement('td');
            cellElement.textContent = `(${rowIndex}, ${cellIndex})`;
            cellElement.addEventListener('click', () => showElementDetails(cell));
            tableRow.appendChild(cellElement);
        });

        mapTable.appendChild(tableRow);
    });
}

function showElementDetails(element) {
    const elementDetails = document.getElementById('element-details');
    elementDetails.innerHTML = `
        <p>Food: ${element.food}</p>
        <p>Linemate: ${element.linemate}</p>
        <p>Deraumere: ${element.deraumere}</p>
        <p>Sibur: ${element.sibur}</p>
        <p>Mendiane: ${element.mendiane}</p>
        <p>Phiras: ${element.phiras}</p>
        <p>Thystame: ${element.thystame}</p>
    `;
}

function updatePlayers(players) {
    const playerList = document.getElementById('player-list');
    playerList.innerHTML = '';
    players.forEach(player => {
        const playerDiv = document.createElement('div');
        playerDiv.textContent = `Player ${player.id_player}`;
        playerDiv.className = 'player-item';
        playerDiv.addEventListener('click', () => showPlayerDetails(player));
        playerList.appendChild(playerDiv);
    });
}

function showPlayerDetails(player) {
    const playerDetails = document.getElementById('player-details');
    playerDetails.innerHTML = `
        <p>ID: ${player.id_player}</p>
        <p>Food: ${player.food}</p>
        <p>Linemate: ${player.linemate}</p>
        <p>Deraumere: ${player.deraumere}</p>
        <p>Sibur: ${player.sibur}</p>
        <p>Mendiane: ${player.mendiane}</p>
        <p>Phiras: ${player.phiras}</p>
        <p>Thystame: ${player.thystame}</p>
        <p>Level: ${player.level_player}</p>
        <p>Direction: ${player.view_direction}</p>
        <p>Position: (${player.x}, ${player.y})</p>
    `;
}

function updateTeams(teams) {
    const teamList = document.getElementById('team-list');
    teamList.innerHTML = '';
    teams.forEach(team => {
        const teamDiv = document.createElement('div');
        teamDiv.textContent = `Team ${team.name}`;
        teamDiv.className = 'team-item';
        teamDiv.addEventListener('click', () => showTeamDetails(team));
        teamList.appendChild(teamDiv);
    });
}

function showTeamDetails(team) {
    const teamDetails = document.getElementById('team-details');
    teamDetails.innerHTML = `
        <p>Name: ${team.name}</p>
        <p>ID: ${team.team_id}</p>
    `;
}

function updateUtils(utils) {
    const utilsData = document.getElementById('utils-data');
    utilsData.innerHTML = `
        <p>Port: ${utils.port}</p>
        <p>Map Width: ${utils.map_width}</p>
        <p>Map Height: ${utils.map_height}</p>
        <p>Client Number: ${utils.client_nb}</p>
        <p>Time: ${utils.time}</p>
        <p>FD GUI: ${utils.fd_gui}</p>
        <p>FD Web Debug: ${utils.fd_web_debug}</p>
        <p>Object: ${utils.obj}</p>
        <p>Stop Server: ${utils.stop_server}</p>
        <p>Start Game: ${utils.start_game}</p>
        <p>Look String: ${utils.look_str}</p>
        <p>Length View: ${utils.len_view}</p>
        <p>View Number: ${utils.view_num}</p>
        <p>Next Player ID: ${utils.next_id_player}</p>
        <p>Next Team ID: ${utils.next_id_team}</p>
        <p>Clock: ${utils.clock}</p>
    `;
}

function refreshData() {
    socket.emit('send_message', { message: 'DASHBOARD\n', timestamp: Date.now() });
}

function toggleTheme() {
    document.body.classList.toggle('dark-mode');
}

document.getElementById('refresh-btn').addEventListener('click', refreshData);
document.getElementById('toggle-theme').addEventListener('click', toggleTheme);
document.getElementById('connect-btn').addEventListener('click', connectToServer);
```

## Contributing

Feel free to fork this repository and submit pull requests. For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.