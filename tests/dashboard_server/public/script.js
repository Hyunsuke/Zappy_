const socket = io();
let selectedElement = null;
let selectedPlayer = null;
let selectedTeam = null;

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
        socket.emit('send_message', { message: 'DASHBOARD\n', timestamp: Date.now() });
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

    if (selectedElement) {
        showElementDetails(selectedElement);
    }
    if (selectedPlayer) {
        showPlayerDetails(selectedPlayer);
    }
    if (selectedTeam) {
        showTeamDetails(selectedTeam);
    }
}

function updateMap(map) {
    const mapTable = document.getElementById('map-table');
    mapTable.innerHTML = '';

    const headerRow = document.createElement('tr');
    const emptyHeader = document.createElement('th');
    headerRow.appendChild(emptyHeader);
    for (let x = 0; x < map[0].length; x++) {
        const headerCell = document.createElement('th');
        headerCell.textContent = x;
        headerRow.appendChild(headerCell);
    }
    mapTable.appendChild(headerRow);

    map.forEach((row, rowIndex) => {
        const tableRow = document.createElement('tr');
        const rowHeader = document.createElement('th');
        rowHeader.textContent = rowIndex;
        tableRow.appendChild(rowHeader);

        row.forEach((cell, cellIndex) => {
            const cellElement = document.createElement('td');
            cellElement.textContent = `(${rowIndex}, ${cellIndex})`;
            cellElement.addEventListener('click', () => {
                selectedElement = cell;
                showElementDetails(cell);
            });
            tableRow.appendChild(cellElement);
        });

        mapTable.appendChild(tableRow);
    });

    if (selectedElement) {
        showElementDetails(selectedElement);
    }
}

function showElementDetails(element) {
    if (!element) return;
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
        playerDiv.addEventListener('click', () => {
            selectedPlayer = player;
            showPlayerDetails(player);
        });
        playerList.appendChild(playerDiv);
    });

    if (selectedPlayer) {
        showPlayerDetails(selectedPlayer);
    }
}

function showPlayerDetails(player) {
    if (!player) return;
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
        teamDiv.addEventListener('click', () => {
            selectedTeam = team;
            showTeamDetails(team);
        });
        teamList.appendChild(teamDiv);
    });

    if (selectedTeam) {
        showTeamDetails(selectedTeam);
    }
}

function showTeamDetails(team) {
    if (!team) return;
    const teamDetails = document.getElementById('team-details');
    teamDetails.innerHTML = `
        <p>Name: ${team.name}</p>
        <p>ID: ${team.team_id}</p>
        <p>Players: ${team.players_id.join(', ')}</p>
    `;
}

function updateUtils(utils) {
    const utilsData = document.getElementById('utils-data');
    utilsData.innerHTML = `
        <p>Port: ${utils.port !== undefined ? utils.port : "N/A"}</p>
        <p>Map Width: ${utils.map_width !== undefined ? utils.map_width : "N/A"}</p>
        <p>Map Height: ${utils.map_height !== undefined ? utils.map_height : "N/A"}</p>
        <p>Client Number: ${utils.client_nb !== undefined ? utils.client_nb : "N/A"}</p>
        <p>Time: ${utils.time !== undefined ? utils.time : "N/A"}</p>
        <p>fd_gui: ${utils.fd_gui !== undefined ? utils.fd_gui : "N/A"}</p>
        <p>fd_web_debug: ${utils.fd_web_debug !== undefined ? utils.fd_web_debug : "N/A"}</p>
        <p>Object: ${utils.obj !== undefined ? utils.obj : "N/A"}</p>
        <p>Stop Server: ${utils.stop_server !== undefined ? utils.stop_server : "N/A"}</p>
        <p>Start Game: ${utils.start_game !== undefined ? utils.start_game : "N/A"}</p>
        <p>Look String: ${utils.look_str !== undefined ? utils.look_str : "N/A"}</p>
        <p>Length of View: ${utils.len_view !== undefined ? utils.len_view : "N/A"}</p>
        <p>View Number: ${utils.view_num !== undefined ? utils.view_num : "N/A"}</p>
        <p>Next Player ID: ${utils.next_id_player !== undefined ? utils.next_id_player : "N/A"}</p>
        <p>Next Team ID: ${utils.next_id_team !== undefined ? utils.next_id_team : "N/A"}</p>
        <p>Clock: ${utils.clock !== undefined ? utils.clock : "N/A"}</p>
    `;
}

function refreshData() {
    console.log("Refreshing data...");
}

function toggleMode() {
    const body = document.body;
    body.classList.toggle('dark-mode');
    body.classList.toggle('light-mode');

    const modeBtn = document.getElementById('mode-btn');
    if (body.classList.contains('dark-mode')) {
        modeBtn.textContent = 'Light Mode';
    } else {
        modeBtn.textContent = 'Dark Mode';
    }
}
